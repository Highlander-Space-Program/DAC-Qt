# Ensure the script is running with Administrator privileges
Write-Host "Checking for Administrator privileges..."
If (-NOT ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
    Write-Warning "Please run this script as an Administrator!"
    Exit
} else {
    Write-Host "Running with Administrator privileges."
}

# Check for winget availability
try {
    winget --version
} catch {
    Write-Host "winget is not installed. Please install App Installer from https://apps.microsoft.com/detail/9nblggh4nns1?rtc=1&hl=en-us&gl=US#activetab=pivot:overviewtab"
    Exit
}

# Check for pip availability
try {
    pip --version
} catch {
    Write-Host "pip is not installed. Please install the latest version of Python from https://www.python.org/downloads/windows/ and ensure pip is selected during installation."
    Exit
}

# Install winget and choco, if necessary
# Note: Instructions for setting up winget and Chocolatey have been omitted for brevity.

# Install dependencies
Write-Host "Installing CMake with winget..."
winget install -e --id Kitware.CMake
Write-Host "CMake installation complete."

Write-Host "Installing Conan with winget..."
pip install conan
Write-Host "Conan installation complete."

Write-Host "Installing Visual Studio Build Tools with Chocolatey. This may take some time..."
choco install visualstudio2022buildtools -y --execution-timeout=10800 --package-parameters "--allWorkloads --includeRecommended --includeOptional --passive --locale en-US"
Write-Host "Visual Studio Build Tools installation complete."

Write-Host "Updating PATH and CMAKE_PREFIX_PATH environment variables..."
echo 'export PATH=$PATH:/c/Program\ Files\ \(x86\)/Microsoft\ Visual\ Studio/2022/BuildTools/VC/Tools/MSVC/14.39.33519/bin/Hostx64/x64' >> $env:UserProfile/.bashrc
. $env:UserProfile/.bashrc
echo 'export CMAKE_PREFIX_PATH=/c/Qt/6.6.2/mingw_64' >> $env:UserProfile/.bashrc
Write-Host "Environment variables updated."

# Initialize submodules
Write-Host "Initializing git submodules..."
git submodule update --init --recursive
Write-Host "Git submodules initialized."

# Clean up and prepare the build directory
Write-Host "Preparing the build directory..."
$buildDir = "C:\Users\bmarc\Desktop\UCR\SPACE\DAC-Qt\build"
if (Test-Path $buildDir) {
    Remove-Item -Path $buildDir -Recurse -Force
    Write-Host "Existing build directory removed."
}
New-Item -Path $buildDir -ItemType Directory
Write-Host "New build directory created."

cd $buildDir
Write-Host "Creating build directory and running Conan profile detect..."
conan profile list
Write-Host "Conan profile detection complete."

# Compile the application
# Write-Host "Compiling the application with CMake..."
# cmake .. -G "Visual Studio 17 2022" -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DINFLUXCXX_TESTING=OFF -DINFLUXCXX_WITH_BOOST=ON -Bbuild -DCMAKE_CXX_STANDARD=17 --toolchain ./build/conan_toolchain.cmake
# Write-Host "Compilation complete."

# Note: Users must manually follow steps for Qt 6 installation and setting VSCode as admin
Write-Host "Setup complete. Please follow the manual steps for Qt 6 installation, open QT Creator, select the CMakeLists file as your project, select the Projects tab on the left side of the QT Creator, select any of the MinGW options. Click build, then run."