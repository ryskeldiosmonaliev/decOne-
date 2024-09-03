# Base image
FROM ubuntu:22.04

# Install necessary packages
RUN apt-get update && apt-get install -y \
    bc \
    nano \
    check \
    lcov \
    make \
    pkg-config \
    wget \
    zsh \
    w3m \
    valgrind \
    && rm -rf /var/lib/apt/lists/* 

# Install Oh My Zsh
RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.2.0/zsh-in-docker.sh)"

# Change default shell to zsh
RUN chsh -s $(which zsh)

# Change working directory
WORKDIR /home/src

# Copy files and directories
COPY ./arithmetic_operations/ ./arithmetic_operations/
COPY ./comparison_operators/ ./comparison_operators/
COPY ./other_functions/ ./other_functions/
COPY ./common_helpers/ ./common_helpers/
COPY ./big_dec/ ./big_dec/
COPY ./convertors_and_parsers/ ./convertors_and_parsers/
COPY ./tests/ ./tests/
COPY ./Makefile ./Makefile
COPY ./s21_decimal.h ./s21_decimal.h

# Set Zsh as the default shell
ENTRYPOINT zsh