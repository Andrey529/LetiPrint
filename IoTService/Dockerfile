# Build stage
FROM gcc:latest as build
WORKDIR /build

ENV BUILD_TYPE=Debug
ENV DEBIAN_FRONTEND noninteractive

# Install all packages
RUN apt-get update && \
    apt-get install -y cmake curl libcurl4-openssl-dev \
        vim \
        locales \
        whois \
        cups \
        cups-client \
        cups-bsd \
        printer-driver-all \
        printer-driver-gutenprint \
        hpijs-ppds \
        hp-ppd  \
        hplip \
        printer-driver-foo2zjs \
        sudo \
        libreoffice \
        git-core && \
    git clone https://github.com/WiringPi/WiringPi.git && \
    cd WiringPi && \
    git pull origin && \
    ./build && \
    gpio -v

COPY cups_server/cupsd.conf /etc/cups/cupsd.conf

ADD ./include /app/include
ADD ./src /app/src
ADD ./CMakeLists.txt /app

WORKDIR /app/build

# Build binaries and run cups server
RUN cmake .. && \
    cmake --build .

EXPOSE 631

ENTRYPOINT ["/bin/sh", "-c", "/usr/sbin/cupsd -F & ./IoTService ${PRINTER_NAME} ${DOWNLOAD_DIRECTORY} ${DOWNLOAD_LINK}"]

## Run stage
#FROM ubuntu:20.04
#
## Add user
#RUN groupadd -r sample && useradd -r -g sample sample
#USER sample
#
#WORKDIR /app
#
#COPY --from=build /usr/lib/x86_64-linux-gnu/ /usr/lib
#COPY --from=build /lib/x86_64-linux-gnu /lib/
#COPY --from=build /app/build/IoTService .
#ENTRYPOINT ["./IoTService"]
