The repository contains the ROOT macros to read,select and/or display events

The file LoadMacros.C loads and compile if needed the classes ALEvent and ALTckhit as weel as some useful parameters.
It also compiles the macros that you want to load at the start of a ROOT session.

For examples:

gROOT->ProcessLine(".L ROOTtoTXT_DATA.C+");

This macro allows you to print some events informtion in a text file event per event.

gROOT->ProcessLine(".L DisplayEvents.C+");

This macro allows you to display some events.

Details about thiese macros can be found in their code.
File to read, Event selection, output format are hardcoded in the C file.


To Link the macros at the beginning ot the ROOT session:

>> root -l -b -x LoadMacro.C


You can then call the macros and functions defined in the 

>>root [1] ROOTtoTXT_DATA()



