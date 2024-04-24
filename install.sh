#!/bin/bash

# Exit script if any command fails
set -e

# Function to install pip for Linux
install_pip_linux() {
    echo "Installing pip for Linux..."
    sudo apt-get update
    sudo apt-get install -y python3-pip
}

# Function to install pip for macOS using Homebrew
install_pip_macos() {
    echo "Installing Python (and pip) for macOS using Homebrew..."
    # Ensure Homebrew is installed
    if ! command -v brew &> /dev/null; then
        echo "Homebrew not found, installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    # Install Python. Pip comes with Python.
    brew install python
    brew install ninja
}

# Function to check if pip, conan, and cmake are correctly installed
check_installations() {
    
    if ! command -v pip &> /dev/null; then
        echo "pip could not be found. Exiting..."
        exit 1
    fi
    echo 'Pip found!'

    if ! command -v cmake &> /dev/null; then
        echo "cmake could not be found. Exiting..."
        exit 1
    fi
    echo 'Cmake found!'

    if command -v conan &> /dev/null; then
        conan_version_output=$(conan --version)
        echo "Conan version output: $conan_version_output"  # For debugging
        conan_version=$(echo "$conan_version_output" | grep -oE 'Conan version [0-9]+\.[0-9]+\.[0-9]+' | grep -oE '[0-9]+\.[0-9]+\.[0-9]+')
        if [ -z "$conan_version" ]; then
            echo "Failed to parse Conan version. Exiting..."
            exit 1
        elif [ "$conan_version" != "1.63.0" ]; then
            echo "Conan version 1.63.0 is required. Found version $conan_version. Exiting..."
            exit 1
        fi
    else
        echo "Conan could not be found. Exiting..."
        exit 1
    fi

}

# Function to install cmake for both macOS and Linux
install_cmake() {
    echo "Installing cmake..."
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        sudo apt-get install -y cmake
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        brew install cmake
    fi
}

# Main installation routine for Linux and macOS
install_main() {
    git submodule update --init --recursive

    # Attempt to install pip and cmake if missing
    if ! command -v pip &> /dev/null; then
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            install_pip_linux
        elif [[ "$OSTYPE" == "darwin"* ]]; then
            install_pip_macos
        fi
    fi

    if ! command -v cmake &> /dev/null; then
        install_cmake
    fi

    # Install Conan, checking for version after installation
    pip install conan==1.63.0

    check_installations

    # Continue with build and setup
    mkdir -p build

    echo 'Changing directory to build'
    cd build

    echo 'Running CMake...'
    cmake ..
    echo 'Cmake Complete!'
    echo 'Running Make...'
    make
    echo 'Make Complete!'
    if [[ "$OSTYPE" == "darwin"* ]]; then
        export DYLD_LIBRARY_PATH=/usr/local/lib
        echo 'export DYLD_LIBRARY_PATH=/usr/local/lib' >> ~/.bashrc
    else
        export LD_LIBRARY_PATH=/usr/local/lib
        echo 'export LD_LIBRARY_PATH=/usr/local/lib' >> ~/.bashrc
    fi
    source ~/.bashrc
    if [[ "$OSTYPE" == "darwin"* ]]; then
        ./appDAC-Qt.app/Contents/MacOS/appDAC-Qt
    else
        ./appDAC-Qt
    fi
}

# Check for operating system and run appropriate commands
case "$OSTYPE" in
    linux-gnu*)
        echo "Detected Linux OS..."
        install_main
        ;;
    darwin*)
        echo "Detected macOS..."
        xcode-select --install || true # Proceed even if xcode-select fails
        install_main
        ;;
    cygwin | msys)
        echo "Detected Windows..."
        powershell.exe -NoProfile -ExecutionPolicy Bypass -File "$(pwd -W)/windows_install.ps1"
        ;;
    *)
        echo "Unsupported OS."
        exit 1
        ;;
esac
