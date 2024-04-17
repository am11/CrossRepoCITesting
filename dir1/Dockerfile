FROM ubuntu:latest

RUN apt update && apt install -y debootstrap
RUN debootstrap "--variant=fakeroot" --arch armhf jammy /tmp/test1 http://ports.ubuntu.com/
