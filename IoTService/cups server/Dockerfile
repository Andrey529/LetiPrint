FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get install -y \
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
  printer-driver-foo2zjs

COPY ./cupsd.conf /etc/cups/cupsd.conf

EXPOSE 631

ENTRYPOINT ["/usr/sbin/cupsd", "-f"]
