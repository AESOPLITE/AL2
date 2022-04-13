 Analysis package for AESOPLITE 2: MC simulations with FLUKA, data with BPD files from MIPFlit, pattern recognition, track reconstructions with Runge-Kutta

Pre-requisite packages for installation:

ROOT, libx11-dev, libxpm-dev

Instructions to install and use the package:

**Download the package, in the power directory, type:

>>source ./setup

**Install the libraries and compile source code by typing:

>>cd src
>>make

**Come back to the main directory and copy pcm file to lib:

>>cd ..
>>cp src/*/*pcm lib

**After modifications, update the include repository with the new header files:

>>cp src/*/*h include


**Edit Imakefile to prepare the executable:

At the time of the initial commit, it prepares the makefile for MainRawBPDEvent

**Create the makefile and the main executable file by typing:

>>xmkmf
>>make

All paths have been changed to relative ones, there should be no modifications necessary in the makefile.

**Edit the file DataFilepaths.txt with the BPD files that you want to reconstruct

"""
/yourdatapathdirectory/NL6033.BPD 1 2

/yourdatapathdirectory/NL6034.BPD 1 2
"""

The arguments 1 and 2 are flags related to parsing the BPD file. Keep them as they are for now. 

**Be sure that the BPD files have a unix format with the command line:

>>dos2unix /yourdatapathdirectory/NL6033.BPD

**Executable file can be found in the main repository:

>>./MainRawBPDEvent DataFilepaths.txt RK

RK is the tag for Runger-Kutta

The reconstruction will give you two output ROOT files per BPD files:

/yourdatapathdirectory/NL6033.BPD.root
/yourdatapathdirectory/NL6033.BPD.EVENT_RK.root

The files NL6033.BPD.EVENT_RK.root contain the reconstructed events.


The subdirectory AL2/Macros contains the macro the read the output file, select events and print a text file with the desire information.
See the corresponding README.md



