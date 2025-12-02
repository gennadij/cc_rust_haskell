# Dockerfile for c++ and rust and haskel development environment
FROM ubuntu:24.04
RUN apt update \
&& apt install -y cmake build-essential curl cargo
## install stack
RUN curl -sSL https://get.haskellstack.org/ | sh \
&& stack setup
#RUN useradd -ms /bin/bash dev
#USER dev
