#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <time.h>

static char* s_resLow;
static char* s_resHigh;

static void report(const char* label)
{
    pthread_attr_t attr;
    void* low;
    size_t size;
    struct timespec t0, t1;
    int local;

    clock_gettime(CLOCK_MONOTONIC, &t0);
    pthread_getattr_np(pthread_self(), &attr);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    pthread_attr_getstack(&attr, &low, &size);
    pthread_attr_destroy(&attr);

    char* high = (char*)low + size;
    printf("%s: main stack [%p, %p) size=%zu KiB, &local=%p, getattr took %.1f ms\n",
           label, low, (void*)high, size / 1024, (void*)&local,
           (t1.tv_sec - t0.tv_sec) * 1e3 + (t1.tv_nsec - t0.tv_nsec) / 1e6);

    if (s_resLow != NULL && (char*)low < s_resHigh && high > s_resLow)
        printf("%s: *** REPORTED STACK OVERLAPS THE PROT_NONE RESERVATION ***\n", label);
}

int main(void)
{
    struct rlimit rl;
    getrlimit(RLIMIT_STACK, &rl);
    printf("RLIMIT_STACK cur=%llu KiB\n", (unsigned long long)rl.rlim_cur / 1024);

    report("initial");

    size_t resSize = (size_t)1 << 30;
    void* res = mmap(NULL, resSize, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
    if (res != MAP_FAILED)
    {
        s_resLow = (char*)res;
        s_resHigh = s_resLow + resSize;
        printf("reserved 1 GiB PROT_NONE at [%p, %p)\n", (void*)s_resLow, (void*)s_resHigh);
    }

    report("after reserve");

    puts("--- /proc/self/maps ---");
    FILE* maps = fopen("/proc/self/maps", "r");
    char line[512];
    while (maps != NULL && fgets(line, sizeof(line), maps) != NULL)
        fputs(line, stdout);

    return 0;
}
