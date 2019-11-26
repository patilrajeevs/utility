# utility
Utilities to be used across multiple projects created

# Usage :
mkdir build
cd build

#from the build dir, execute cmake and make
cmake ..
make

#Do install the libraries on the host, these are static libraries.
#This will copy the required header files and shared libraries into the system 
sudo make install

