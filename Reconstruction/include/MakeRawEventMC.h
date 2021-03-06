////////////////////////////////////////////////////////////////////////////////////////// 
///    Author: Pierre-Simon Mangeard, psmangeard@gmail.com
///    Department of Physics and Astronomy, University of Delaware, January 10, 2017
////////////////////////////////////////////////////////////////////////////////////////// 



#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <TROOT.h>
#include <Riostream.h>
#include "TChain.h"
#include "TCanvas.h"
#include "TObject.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TMath.h"
#include "TLegend.h"
#include "TLeaf.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLinearFitter.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TCut.h"
#include "TLine.h"
#include "TArrow.h"
#include "TBox.h"
#include "TPDF.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TPostScript.h"
#include "TPaveText.h"
#include "TString.h"
#include "TH1F.h"
#include "TSystem.h"
#include "THStack.h"
#include "TNtuple.h"
#include "TFormula.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TH3F.h"
#include "TRandom3.h"
#include "TRandom2.h"
#include "TRandom1.h"
#include "ALEvent.h"
#include "LoadMCparameters.h"
#include "tools.h"

//ClassImp(ALTckhit)
//ClassImp(ALEvent)

int MakeRawEventMC(int ,int ,int,int,string,string,string,string,string,string);

//int MakeRawEventMC(int typeT,int Ene,int cycle,string Inppath,string Inppath2,string Outpath,string startfile,string endfile);
int MakeRawEventMCDisc(int ,int ,int,int,string,string,string,string,string,string);
int MakeRawEventMCDiscPL(int,int,string,string,string,string,string,string);


/*
float Discretize(int L,vector<float> x, vector<float> y,vector<float> z,vector<float> cz,vector<float>type,vector<float> Edep,int*chip,int* fstrip,int* fstripID,int*nstrip,float offsetLL, float offsetRL,bool MCflag);
float StriptoCoord(int strip,float OffsetLL,float OffsetRL,bool MCflag);
int CoordtoStrip(float Coord,float SecCoord,float OffsetLL,float OffsetRL,bool MCflag);
*/
