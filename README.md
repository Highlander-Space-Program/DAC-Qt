# DAC-Qt
Qt-based DAC real-time visualization, control, and configuration tool

Dependencies:
- Qt 6
- Qt Charts
- nlohmann_json

Running:
1. Build and run in Qt Creator

Setup (Mac)
xcode-select --install
git submodule update --init --recursive
brew reinstall spdlog cpr curl libusb
mkdir build
cd build
cmake ..
make
export DYLD_LIBRARY_PATH=/usr/local/lib
./appDAC-Qt.app/Contents/MacOS/appDAC-Qt

*restart terminal*

## Troubleshooting
With an error like: dyld[94071]: Library not loaded: /usr/local/lib/libusb-1.0.0.dylib
  