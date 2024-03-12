FROM gcc:latest

WORKDIR /app

COPY . /app

RUN gcc ./server.c

ENTRYPOINT ./a.out
