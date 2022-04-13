////////////////////////////////////////////////////////////////////////////////////////////////////////
///    Author: Sarah Mechbal, smechbal@ucsc.edu
///    Santa Cruz Institute for Particle Physics, University of California, Santa Cruz, August 2019
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "headers.h"
#include "ALEvent.h"
#include "LoadDataparameters.h"
#include "LoadMCparameters.h"
#include "TChain.h"
#include "TPaveStats.h"
#include "TGaxis.h"

ClassImp(ALTckhit)
ClassImp(ALEvent)

void ROOTtoTXT_DATA()
{	

 string Inppath="/media/psmangeard/DATA/Documents/UDEL/AESOPLITE2/NewPSOCRuns";
//string startfile="NL2685_2688_2700.BPD";
 string startfile="NL6034.BPD";
 string endfile=".EVENT_RK";
 string directory= "/media/psmangeard/DATA/Documents/UDEL/AESOPLITE2/NewPSOCRuns";

 

 //output file
 ofstream outputTXT;
 outputTXT.open(Form("%s/%s%s.txt", Inppath.c_str(),startfile.c_str(),endfile.c_str()));
 outputTXT << "runnumber"  << " " ;				     
 outputTXT << "eventnumber"  << " " ;				     
 outputTXT << "CX0reco" << " " ;
 outputTXT << "CY0reco"  << " " ;
 outputTXT << "CZ0reco"  << " " ;					 
 outputTXT << "T1"  << " " ;
 outputTXT << "T2"  << " " ;
 outputTXT << "T3"  << " " ;
 outputTXT << "T4"  << " " ;
 outputTXT << "ToF"  << " " ;
 outputTXT << "p0PR"  << " " ;
 outputTXT << "deflecPR"  << " " ;
 outputTXT << "chi2NB"  << " " ;
 outputTXT << "chi2B"  << " " ;
 outputTXT << "NL"  << " " ;			     
 outputTXT << "NLB"  << " " ;
 outputTXT << "NLNB"  << " " ;
 outputTXT << "Nhits"  << " " ;
 outputTXT << "Ti" << " ";
 outputTXT << "TiPR" << " ";
 outputTXT << "trigB"  << " " ;
 outputTXT << "trigNB"  << " " ;
 outputTXT << "goodTrackB"  << " " ;
 outputTXT << "p0reco"  << " " ;
 outputTXT << "chi2reco"  << " " ;
 outputTXT << "Guard" << " ";
 outputTXT << "NhitsB" << " ";
 outputTXT << "NhitsNB" << " ";
 outputTXT << "NL0" << " ";
 outputTXT << "NL1" << " ";
 outputTXT << "NL2" << " ";
 outputTXT << "NL3" << " ";
 outputTXT << "NL4" << " ";
 outputTXT << "NL5" << " ";
 outputTXT << "NL6" << " ";
 outputTXT << "NL7" << " ";
 outputTXT << "Status" << " ";
 outputTXT << Form("%s", "XT1PR") << " ";
 outputTXT << Form("%s", "YT1PR") << " ";
 outputTXT << Form("%s", "XT3PR") << " ";
 outputTXT << Form("%s", "YT3PR") << " ";
 outputTXT << Form("%s", "XT4PR") << " ";
 outputTXT << Form("%s", "YT4PR") << " ";    
 outputTXT << Form("%s", "XGPR") << " ";
 outputTXT << Form("%s", "YGPR") << " ";    
 outputTXT <<endl;			     
    			      
 TFile*filein=new TFile(Form("%s/%s%s.root",Inppath.c_str(),startfile.c_str(),endfile.c_str()),"READ");

 //Get Tree from the calibrated file   
 TTree *tree = (TTree*)filein->Get("Data");
 ALEvent *e = new ALEvent();
 tree->SetBranchAddress("event",&e);  
 // Get number of event in Tree
 int nentries=tree->GetEntries();

 for (int m=0;m<nentries;m++)
   {
    tree->GetEntry(m); //Load the entry i in the variable e

    ////////////////////////////
    //SCINTILLATORS
    ////////////////////////////

    double E1=0;
    double E2=0;
    double E3=0;
    double E4=0; 	
    double Guard=0;
    double ToF=0;
    
    //T1
    int nT1=e->get_EneT1().size();
    if(nT1>0){for(int k=0;k<nT1;k++) E1+=e->get_EneT1().at(k);}
    //T2
    int nT2=e->get_EneT2().size();
    if(nT2>0){for(int k=0;k<nT2;k++) E2+=e->get_EneT2().at(k);}
    //T3
    int nT3=e->get_EneT3().size();
    if(nT3>0){for(int k=0;k<nT3;k++) E3+=e->get_EneT3().at(k);}
    //T4
    int nT4=e->get_EneT4().size();
    if(nT4>0){for(int k=0;k<nT4;k++) E4+=e->get_EneT4().at(k);}
    //Guard
    int nTG = e->get_Eneg().size();
    if(nTG>0){for(int k=0; k<nTG; k++) Guard+=e->get_Eneg().at(k);}

    //Guard
    int nToF = e->get_PHA6().size();
    if(nToF>0){for(int k=0; k<nToF; k++) ToF+=e->get_PHA6().at(k);}

    ////////////////////////////
    //INTERNAL TRIGGER
    ////////////////////////////

    bool  trigNB = false;
    bool trigB = false;
    bool goodTrackB = false;
    bool trig = false;
    //Number of layers with hit(s) in bending/non-bending plane

    int NLB = e->get_Layer(1) + e->get_Layer(2) + e->get_Layer(3) + e->get_Layer(4)+ e->get_Layer(6); 
    int NLNB =  e->get_Layer(0) + e->get_Layer(5) + e->get_Layer(7);

    int NLB_PR = e->get_LayerPR(1) + e->get_LayerPR(2) + e->get_LayerPR(3) + e->get_LayerPR(4)+ e->get_LayerPR(6);
    int NLNB_PR =  e->get_LayerPR(0) + e->get_LayerPR(5) + e->get_LayerPR(7);

    if (NLNB==3) {trigNB=true;}
    if((e->get_Layer(1) + e->get_Layer(2) + e->get_Layer(3)) == 3) {trigB=true;}        
    if(NLB >= 3) {goodTrackB=true;}	       //good track in bending plane
    if(trigNB || trigB) trig = true;
    //Number of layers with hit(s)
    int NL= e->get_NLayers();
    int NL_PR = e->get_NLayersPR();
  
    unsigned Status= e->get_Status();
    float XT1PR=e->get_XT1PR(); 
    float YT1PR=e->get_YT1PR(); 
    float XT3PR=e->get_XT3PR(); 
    float YT3PR=e->get_YT3PR(); 
    float XT4PR=e->get_XT4PR(); 
    float YT4PR=e->get_YT4PR();
    float XGPR=e->get_XGPR(); 
    float YGPR=e->get_YGPR();   
    ////////////////////////////
    //NUMBER OF HIT PER LAYERS
    ////////////////////////////
    int NL0=e->get_NLPR(0); 
    int NL1=e->get_NLPR(1); 
    int NL2=e->get_NLPR(2); 
    int NL3=e->get_NLPR(3); 
    int NL4=e->get_NLPR(4); 
    int NL5=e->get_NLPR(5); 
    int NL6=e->get_NLPR(6); 
    int NL7=e->get_NLPR(7); 
    int Nhits = NL0 + NL1 + NL2 + NL3 + NL4 + NL5 + NL6 + NL7;
    int NhitsB = NL1 + NL2 + NL3 + NL4 + NL6;
    int NhitsNB = NL0 + NL5 + NL7;
    ////////////////////////////////////
    //TRIGGER CUT
    ////////////////////////////////////
    outputTXT << Form("%5d",e->get_runnumber())  << " ";
    outputTXT << Form("%5d",e->get_eventnumber())  << " ";
    outputTXT << Form("%1.4f",(float)e->get_CX0reco())  << " ";
    outputTXT << Form("%1.4f",(float)e->get_CY0reco())  << " ";
    outputTXT << Form("%1.4f",(float)e->get_CZ0reco())  << " ";
    outputTXT << Form("%5.2f",(float)E1)  << " ";
    outputTXT << Form("%5.2f",(float)E2)  << " ";
    outputTXT << Form("%5.2f",(float)E3)  << " ";
    outputTXT << Form("%5.2f",(float)E4)  << " ";
    outputTXT << Form("%5.2f",(float)ToF)  << " ";
    outputTXT << Form("%7.2f",TMath::Sign(1,e->get_deflecPR())*1000*e->get_p0PR())  << " ";
    outputTXT << Form("%7.3e",e->get_deflecPR())  << " ";
    outputTXT << Form("%5.2f",e->get_chi2NBPR())  << " ";
    outputTXT << Form("%5.2f",e->get_chi2BPR())  << " ";
    outputTXT << Form("%d", NL_PR) << " ";
    outputTXT << Form("%d", NLB_PR) << " ";
    outputTXT << Form("%d", NLNB_PR) << " ";
    outputTXT << Form("%d", Nhits) << " ";
    outputTXT << Form("%3d",(int)e->get_Ti())  << " ";
    outputTXT << Form("%3d",(int)e->get_TiPR())  << " ";
    outputTXT << Form("%d", (int)trigB) << " ";
    outputTXT << Form("%d", (int)trigNB) << " ";
    outputTXT << Form("%d", (int)goodTrackB) << " ";
    outputTXT << Form("%6.2f",TMath::Sign(1,e->get_typereco())*e->get_p0reco())  << " ";
    outputTXT << Form("%5.2f",e->get_chi2())  << " ";
    outputTXT << Form("%5.2f",(float)Guard)  << " ";
    outputTXT << Form("%d", NhitsB) << " ";
    outputTXT << Form("%d", NhitsNB) << " ";
    outputTXT << Form("%d", NL0) << " ";
    outputTXT << Form("%d", NL1) << " ";
    outputTXT << Form("%d", NL2) << " ";
    outputTXT << Form("%d", NL3) << " ";
    outputTXT << Form("%d", NL4) << " ";
    outputTXT << Form("%d", NL5) << " ";
    outputTXT << Form("%d", NL6) << " ";
    outputTXT << Form("%d", NL7) << " ";
    outputTXT << Form("%d", Status) << " ";
    outputTXT << Form("%5.2f", XT1PR) << " ";
    outputTXT << Form("%5.2f", YT1PR) << " ";
    outputTXT << Form("%5.2f", XT3PR) << " ";
    outputTXT << Form("%5.2f", YT3PR) << " ";
    outputTXT << Form("%5.2f", XT4PR) << " ";
    outputTXT << Form("%5.2f", YT4PR) << " ";
    outputTXT << Form("%5.2f", XGPR) << " ";
    outputTXT << Form("%5.2f", YGPR) << " ";
    outputTXT <<endl;
   }//m number of entries
 outputTXT.close();
 filein->Close();
}
