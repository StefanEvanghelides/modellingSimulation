# python:3.9-slim uses Debian Buster, which has a CMake version
# that is incompatible with matplot++'s CMakeLists.txt files
FROM debian:bullseye-slim as RUNNING

RUN apt-get update \
    && apt install -y g++ build-essential cmake gnuplot

COPY Makefile /app/
COPY CMakeLists.txt /app/
COPY accuracy/ /app/accuracy/
COPY plotting/ /app/plotting/
COPY video/ /app/video/
COPY src/ /app/src/

# Manually copy matplotplusplus dependency
COPY dependencies/matplotplusplus-1.0.1-Linux/lib/ /usr/lib/
COPY dependencies/matplotplusplus-1.0.1-Linux/include/ /usr/include/

RUN cmake --version
RUN cd app && mkdir build && cd build && cmake ..
RUN cd app/build && make

CMD [bash -c "cd app && ./build/src/run"]

