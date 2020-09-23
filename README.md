# mavlink_experiments
Simple Qt app for experiments with MAVLink protocol and testing

## Dependencies
* C++11 compatible compiler
* Qt5 development modules: Core Network SerialPort
* CMake 2.8.11 or greater
  
### Ubuntu users can use apt:
```bash
sudo apt-get install g++ cmake qtbase5-dev libqt5serialport5-dev
```
### Fedora/CentOS/RHEL users can use dnf:
```bash
sudo dnf install g++ cmake qt5-devel qt5-qtserialbus-devel qt5-qtlocation
```
## Cloning
```bash
git clone --recurse-submodules https://github.com/MishkaRogachev/mavlink_experiments
```
Don't forget submodules

## Building
```bash
mkdir build
cd build
cmake ..
make
```
