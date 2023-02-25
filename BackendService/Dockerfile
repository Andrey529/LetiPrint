FROM maven:3.8.3-openjdk-17

WORKDIR /target
COPY . .
RUN mvn -DVadim=Vadim clean install

ENTRYPOINT ["java", "-jar", "backend.jar"]