# Use a stable Ubuntu base
FROM ubuntu:latest

# Set a working directory
WORKDIR /work

# Install basic tools
RUN apt-get update && apt-get install -y \
    git \
    ca-certificates 

ADD ./install.sh "install.sh"

RUN bash ./install.sh && rm ./install.sh &&rm -rf /var/lib/apt/lists/* 

RUN ldconfig
# Default shell when container starts
CMD ["/bin/bash"]
