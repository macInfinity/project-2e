# Inspiration for this Dockerfile came from:
# https://devblogs.microsoft.com/cppblog/c-development-with-docker-containers-in-visual-studio-code/
FROM debian

RUN apt -y update && apt -y install
RUN apt -y install gcc valgrind vim make

RUN mkdir /project
WORKDIR /project

