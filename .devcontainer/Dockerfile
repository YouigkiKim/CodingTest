FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04

# g++/gdb는 기본 이미지에 포함되어 있지만, 누락에 대비해 명시적으로 설치한다.
RUN apt-get update \
    && apt-get install -y --no-install-recommends g++ gdb python3 \
    && rm -rf /var/lib/apt/lists/*
