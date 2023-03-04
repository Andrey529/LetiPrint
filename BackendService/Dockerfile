FROM maven:3.8.3-openjdk-17 AS build

WORKDIR /build
COPY . .
RUN mvn clean package -DskipTests

FROM openjdk:17.0.2-jdk

WORKDIR /java
COPY --from=build /build/target/BackendService-0.0.1-SNAPSHOT.jar /java/java.jar
COPY --from=build /build/src/main/resources/storage /java
ENV pathFile /java
EXPOSE 8010
ENTRYPOINT ["java", "-jar", "/java/java.jar"]