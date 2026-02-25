FROM ubuntu:24.04

LABEL org.opencontainers.image.source="https://github.com/EmbeddedOps/stm32_embeddedops_sample"
LABEL org.opencontainers.image.description="STM32 firmware build environment (ARM GCC, CMake, Ceedling)"
LABEL org.opencontainers.image.licenses="MIT"

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8

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
