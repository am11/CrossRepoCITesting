FROM ubuntu:latest

RUN echo "deb http://ftp.us.debian.org/debian unstable" >> /etc/apt/sources.list.d/unstable.list
RUN apt update && apt install -t unstable -y debootstrap fakechroot fakeroot
RUN debootstrap --version
RUN fakeroot fakechroot debootstrap "--variant=fakechroot" --arch armhf jammy /tmp/test1 http://ports.ubuntu.com/
