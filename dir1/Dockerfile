FROM ubuntu:latest

RUN apt update && apt install -y debootstrap fakechroot fakeroot
RUN debootstrap --version
RUN fakeroot fakechroot debootstrap "--variant=fakechroot" --arch armhf jammy /tmp/test1 http://ports.ubuntu.com/
