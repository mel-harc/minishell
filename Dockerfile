FROM ubuntu:latest

WORKDIR /usr/src/app

RUN apt-get update && \
    apt-get install -y build-essential libreadline-dev

COPY . .

RUN make

CMD ["./minishell"]