FROM alpine:latest

RUN apk add --no-cache clang
WORKDIR /app

COPY . /app

RUN clang ./server.c

ENTRYPOINT ./a.out
