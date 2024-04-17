FROM ubuntu:latest

RUN apt update && apt install -y debootstrap fakechroot
RUN fakeroot fakechroot debootstrap "--variant=minbase" --arch armhf jammy /tmp/test1 http://ports.ubuntu.com/
