FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        ninja-build \
        git \
        python3 \
        gcc-arm-none-eabi \
        libnewlib-arm-none-eabi \
        ruby \
        ruby-dev \
    && rm -rf /var/lib/apt/lists/*

RUN gem install ceedling --no-document

# Verify tooling
RUN arm-none-eabi-gcc --version && cmake --version && ceedling version

WORKDIR /workspace
