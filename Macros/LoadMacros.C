#include <TROOT.h>
#include <iostream>

void LoadMacros()

{

//Load shared libraries and compile them if necessary
//You can have "++" to force to compile the code every time

gROOT->ProcessLine(".L ALTckhit.cxx+");
gROOT->ProcessLine(".L ALEvent.cxx+");
gROOT->ProcessLine(".L LoadDataparameters.cxx+");
gROOT->ProcessLine(".L LoadMCparameters.cxx+");

//Load the main analysis files, compile if needed
//You can have "++" to force to compile the code every time

//gROOT->ProcessLine(".L DisplayEventsMC.C++");
gROOT->ProcessLine(".L DisplayEvents.C++");
//gROOT->ProcessLine(".L ROOTtoTXT.C+");
//gROOT->ProcessLine(".L ROOTtoTXTCSBF.C+");
//gROOT->ProcessLine(".L ROOTtoTXT_DATA.C+");
gROOT->ProcessLine(".L ROOTtoTXT_DATA23.C+");
gROOT->ProcessLine(".L AnalyseExample.C+");

}

