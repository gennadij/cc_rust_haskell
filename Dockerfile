FROM ubuntu:24.04 AS builder_haskell
RUN apt update \
  && apt install -y curl
# RUN curl -sSL https://get.haskellstack.org/ | sh
# WORKDIR /app
# COPY haskell/exact-square-root-rest-api-server .
# RUN stack install --local-bin-path ./build/bin
# # RUN stack setup && stack build --allow-different-user


# FROM httpd:2.4
# WORKDIR /app
# COPY --from=builder_haskell /app/build/bin/* .
# COPY ./webclient/web-content/ /usr/local/apache2/htdocs/
# COPY start_rest_server.sh .
