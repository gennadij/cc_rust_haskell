# Dockerfile for c++ and rust and haskel development environment
FROM ubuntu:24.04
RUN apt update \
&& apt install -y cmake build-essential curl git vim
# protobuf-compiler
## install stack
# RUN curl -sSL https://get.haskellstack.org/ | sh \
# && stack setup
# install rust
# RUN curl https://sh.rustup.rs -sSf | sh -s -- -y --default-toolchain stable
# ENV PATH="/root/.cargo/bin:${PATH}"
#RUN useradd -ms /bin/bash dev
#USER dev
