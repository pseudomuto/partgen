FROM debian:buster-slim

RUN apt-get update -y && \
  apt-get install -y --no-install-recommends build-essential ca-certificates clang clang-format curl git && \
  apt-get autoclean && \
  apt-get autoremove && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/*

RUN curl -fsSLo cmake.sh https://github.com/Kitware/CMake/releases/download/v3.19.6/cmake-3.19.6-Linux-x86_64.sh && \
  /bin/sh cmake.sh --prefix=/usr/local --skip-license && \
  rm cmake.sh

WORKDIR /app
COPY . .
