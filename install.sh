#!/bin/bash
set -x
set -e

function pdep() {
    echo "Instaling dependency: $1"
}

# Use sudo only if not root
if [ "$(id -u)" -eq 0 ]; then
    SUDO=""
else
    SUDO="sudo"
fi

#nlohmann_json
pdep "nlohmann_json"

git clone https://github.com/nlohmann/json.git && cd json && mkdir -p build \
&& cd build && cmake .. && make -j $(nproc) install \
&& cd ../.. && rm -rf json

# pybind11
pdep "pybind11"
$SUDO apt-get install -y python3-pybind11 pybind11-dev


# boos po
pdep "boost program options"
$SUDO apt-get install -y libboost-program-options-dev

echo "Installing mantis..."
git clone https://github.com/MayorDermer/mantis.git
cd mantis && mkdir -p build \
&& cd build && cmake .. && make -j $(nproc) install \
&& cd ../.. && rm -rf mantis

$SUDO ldconfig

echo "Mantis installation complete"