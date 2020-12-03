# Project 1 - CSCI759

Code by Adam Caulfield (ac7717@rit.edu) for CSCI759 Project 1    

Based on code from:
      Copyright SpiRITlab - Computations on Encrypted Data
      https://gitlab.com/SpiRITlab/coed

To run has very similar steps to the base code we were given as a starting point with the addition of installing OpenMP in step 1 and the name of the executable in step 3.


1. Install dependencies with `bootstrap.sh` script.
```bash
cd ../../
bash bootstrap.sh
```
Install right C++ and OpenMP (Ubuntu 18.04)
```bash
sudo apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y software-properties-common \
	apt-key adv --keyserver keyserver.ubuntu.com --recv-keys EA8CACC073C3DB2A \
	add-apt-repository ppa:jonathonf/gcc-9.0 -y \
	apt-get install libomp-dev \
	apt-get update \
	apt-get install -y pkg-config libz-dev git build-essential m4 gcc-9 g++-9 \
	apt-get autoremove -y \
	apt-get clean
```

2. Return to /Project1 directory and run:
```bash
cmake .
make
```

3. We will place executable in `../../deps/bin`. Therefore, the project main can be run by executing:
```bash
../../deps/bin/Project1
```