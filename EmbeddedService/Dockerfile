# Build stage
FROM gcc:latest as build
WORKDIR /build

ENV BUILD_TYPE=Debug
ENV DEBIAN_FRONTEND noninteractive

# Install all packages
RUN apt-get update && \
    apt-get install -y sudo cmake git-core && \
    git clone https://github.com/WiringPi/WiringPi.git && \
    cd WiringPi && \
    git pull origin && \
    ./build && \
    gpio -v

ADD ./src /app/src
ADD ./CMakeLists.txt /app

WORKDIR /app/build

# Build binaries and run cups server
RUN cmake .. && \
    cmake --build .

ENTRYPOINT ["./EmbeddedService"]
