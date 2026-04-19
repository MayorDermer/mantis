# Use a stable Ubuntu base
FROM ubuntu:latest

# Install basic tools
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    cmake \
    ca-certificates \
    libboost-program-options-dev \
    && rm -rf /var/lib/apt/lists/*

# Set a working directory
WORKDIR /work

# Clone a repo (example)
RUN git clone https://github.com/nlohmann/json.git

# Build it (example with CMake)
RUN cmake -S json -B json/build \
    && cmake --build json/build -j 10\
    && cmake --install json/build

ADD mantis "mantis"
ADD mantis "mantis"
RUN if [ -d "mantis/build" ]; then rm -rf mantis/build; fi
RUN cmake -S mantis -B mantis/build \
    && cmake --build mantis/build -j 10 \
    && cmake --install mantis/build
RUN ldconfig
# Default shell when container starts
CMD ["/bin/bash"]
