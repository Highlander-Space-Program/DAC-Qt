# DAC-Qt
Qt-based DAC real-time visualization, control, and configuration tool

Dependencies:
- Qt 6
- Qt Charts
- nlohmann_json

Running:
1. Build and run in Qt Creator

## Setup (Mac)
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

## Setup (Windows)

#### Install and Setup winget
This is based off of the link below
https://learn.microsoft.com/en-us/windows/package-manager/winget/

Start by installing or updating App Installer
https://apps.microsoft.com/detail/9nblggh4nns1?rtc=1&hl=en-us&gl=US#activetab=pivot:overviewtab

To add the source if it isn't already added, run this command
```winget source add --name winget --arg https://cdn.winget.microsoft.com/cache```

To test if it worked, it should be at 1.6 or above
```winget --version```

#### Install choco
Open Powershell as Administrator, and run the following:
```Get-ExecutionPolicy```
If it return 'Restricted', run:
    Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
Else:
    continue

Run:
```Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))```

Verify it by running
```choco --version```
    
#### Install vscode
Go to the following link and click the installer. 
Select any options you like while installing. 
I checked all options yes, including the desktop shortcut, to allow windows to open with code, and the defaults they had.
https://code.visualstudio.com/download

#### Install git (and git bash)
Within an admin powershell, run:
    ```winget install Git.Git```

Open powershell as admin and type git to verify installation

#### (Recommended) Make vscode always run as Admin
To use the git bash terminal in VSCode as admin, VSCode must be run as admin.
As this is almost always necessary, the following steps will make the shortcut default to that.

Go to the shortcut (either on desktop or in windows search) and right click 
Select Properties
Go to the Compatibility tab
Select Run this program as an administrator

#### (Recommended) Set git bash as default vscode terminal
Open VSCode, and open the Command Palette with Ctrl + Shift + P.
Type Terminal: Select Default Profile and select it.
Choose the Git Bash terminal from the list.

To open new a terminal, type Ctrl + Shift + P and then select Terminal: Create New Terminal
This should be a git bash terminal.

#### Install cmake, conan, g++, Qt 6 
In a git bash terminal being Run with Administrator,
1. make an account and install Qt 6. Go to the following link and create an account with your school email. Select QT Edu for Developers
https://www.qt.io/qt-educational-license#application

2. Verify your email and you will be redirected to the download page. Select your OS.
https://www.qt.io/download-qt-installer-oss

3. Log into your QT account in the installer. Continue through each page, until you see an option for custom installation (in the Installation Folder). Ensure it is checked and then continue.

4. Click the Qt drop down and ensure that the latest stable version is checked, and then ensure that Qt Charts is also checked (under Additional Libraries). Continue through the rest of the install.

```winget install -e --id Kitware.CMake```
```winget install -e --id JFrog.Conan```
```choco install visualstudio2022buildtools -y --execution-timeout=10800 --package-parameters "--allWorkloads --includeRecommended --includeOptional --passive --locale en-US"``` (This will also take a while, for my computer with a slow network it was about 2 hours)
```echo 'export PATH=$PATH:/c/Program\ Files\ \(x86\)/Microsoft\ Visual\ Studio/2022/BuildTools/VC/Tools/MSVC/14.39.33519/bin/Hostx64/x64' >> ~/.bashrc```
```source ~/.bashrc```
```echo 'export CMAKE_PREFIX_PATH=/c/Qt/6.6.2/mingw_64' >> ~/.bashrc```

To see if the installation worked properly, try the following. All of these should return values and not error:
```cmake --version```
```conan --version```
```g++ --version```
```nmake --version```
```ninja --version```

```mkdir build```
```conan profile detect```
This step is very important. Ensure that the profile it creates has cpp 17 or higher, or cpr wont install properly. If you need to change it, run the following commands:
```nano ~/.conan2/profiles/default```

```conan install . -if=build --build-require --build=missing```
```cmake . -G "Visual Studio 17 2022" -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DINFLUXCXX_TESTING=OFF -DINFLUXCXX_WITH_BOOST=ON -Bbuild -DCMAKE_CXX_STANDARD=17 --toolchain ./build/conan_toolchain.cmake```

```echo 'export CMAKE_PREFIX_PATH=/c/Users/bmarc/Desktop/UCR/SPACE/DAC-Qt/build' >> ~/.bashrc```


in extern/inf/build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=/c/Users/bmarc/Desktop/UCR/SPACE/DAC-Qt/extern/influxdb-cxx/build/conan_toolchain.cmake -DINFLUXCXX_TESTING=OFF -DINFLUXCXX_WITH_BOOST=ON -DCMAKE_POLICY_DEFAULT_CMP0091=NEW

#### Install LabJack libraries:
Go to the following link and install the executable. 
Select any options you like while installing. I didn't change anything off of default.
https://labjack.com/pages/support?doc=/software-driver/installer-downloads/ljm-software-installers-t4-t7-digit/
If this link is broken, look up `labjack windows 11 t7 install downloads`

#### Install dependencies
git submodule update --init --recursive

## Compile and run
cmake . -Bbuild -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake
cmake --build build



## Troubleshooting

### Mac
With an error like: dyld[94071]: Library not loaded: /usr/local/lib/libusb-1.0.0.dylib

### Windows
First ensure packages are up to date
```choco upgrade all```



### Linux
  