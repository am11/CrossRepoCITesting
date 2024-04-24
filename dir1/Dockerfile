FROM ubuntu:latest

RUN echo "deb [trusted=yes] http://ftp.us.debian.org/debian unstable main contrib non-free" >> /etc/apt/sources.list.d/unstable.list
RUN apt update && apt install -t unstable -y debootstrap fakechroot fakeroot && apt purge -y arch-test
RUN debootstrap --version
RUN update-binfmts --display
RUN fakeroot fakechroot debootstrap "--variant=fakechroot" --arch armhf jammy /tmp/test1 http://ports.ubuntu.com/ || true
RUN cat /tmp/test1/debootstrap/debootstrap.log
