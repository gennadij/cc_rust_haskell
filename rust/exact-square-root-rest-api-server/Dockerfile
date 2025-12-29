FROM ubuntu:24.04 AS builder_rust
RUN apt update \
&& apt install -y cmake build-essential curl git vim
# install rust
RUN curl https://sh.rustup.rs -sSf | sh -s -- -y --default-toolchain stable
ENV PATH="/root/.cargo/bin:${PATH}"
WORKDIR /app
COPY . .
RUN cargo install --path . --root ./build

FROM debian
WORKDIR /app
COPY --from=builder_rust /app/build/bin/* .
EXPOSE 8083
ENTRYPOINT ["/app/exact-square-root-rest-api-server"]