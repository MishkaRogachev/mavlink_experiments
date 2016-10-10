# mavlink_experiments
Simple Qt app for experiments with MAVLink protocol and testing

### Dependencies
* C++11 compatible compiler
* Qt5 development modules: Core Network SerialPort
* CMake 2.8.11 or greater
  
#### Ubuntu users can use apt:
```
  sudo apt-get install g++ cmake qtbase5-dev libqt5serialport5-dev
```
### Cloning
```
git clone --recursive https://github.com/MishkaRogachev/mavlink_experiments
```
Don't forget submodules

### Building
```
mkdir build
cd build
cmake ..
make
```
