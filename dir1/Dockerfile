FROM ubuntu:latest

RUN apt update && apt install -y debootstrap fakechroot
RUN debootstrap "--variant=fakechroot" --arch armhf jammy /tmp/test1 http://ports.ubuntu.com/
