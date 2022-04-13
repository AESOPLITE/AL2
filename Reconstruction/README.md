 Analysis package for AESOPLITE 2: MC simulations with FLUKA, data with BPD files from MIPFlit, pattern recognition, track reconstructions with Runge-Kutta

Pre-requisite packages for installation:

ROOT, libx11-dev, libxpm-dev

Instructions to install and use the package:

**Download the package, in the power directory, type:

 source ./setup

**Install the libraries and compile source code by typing:

cd src
make

**Come back to the main directory and copy pcm file to lib:

cd ..
cp src/*/*pcm lib

**Update the include repository with the new header files:
cp src/*/*h include

**Create the main executable file by typing:

xmkmf
make

**Executable file can be found in the main repository:

./Main

All paths have been changed to relative ones, there should be no modifications necessary in the makefile.
