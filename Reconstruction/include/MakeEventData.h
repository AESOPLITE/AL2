////////////////////////////////////////////////////////////////////////////////////////// 
///    Author: Pierre-Simon Mangeard, psmangeard@gmail.com
///    Department of Physics and Astronomy, University of Delaware, September 11, 2017
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
#include "RKfitter.h"
#include "FieldMap.h"
#include "Histogram.h"
#include "RungeKutta4.h"
#include "TkrData.h"
//ClassImp(ALTckhit)
//ClassImp(ALEvent)


int MakeEventData(string,int,float*,float*,float*,float*,string);





