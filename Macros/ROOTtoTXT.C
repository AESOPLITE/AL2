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

void ROOTtoTXT(int t, int nene, int ncycles)
{	
 int DataType = 1;				//0 for data, 1 for MC
 //Number of reconstruction types to study 
 const int NReco=1;
 string RecoInd[NReco]={"RK"};
 //Number of energies
 int Nene;
 if(t==11 || t==10) Nene=16;
 else  if(t==3|| t==4) Nene=24;
 else if(t==1) Nene=10;
 //Energies
 int*Ene=new int[Nene];
 //Number of cycles per energy
 int Ncycles=ncycles;
 //Input file 
 string Inppath="/data/psmangeard/AESOPLITE2/AL2/TestOutput/V2";
 string startfile="AL2NonUniB_V2";
 string endfile="_fort.99";
 string source = "rootfiles";
 string directory= "/data/psmangeard/AESOPLITE2/AL2/TestOutput/V2";
 int seed =0;

 //type of particle
 int type=t;
 string stype;	
 if(t==3)stype="electron";
 if(t==4)stype="positron";
 if(t==11)stype="muon-";
 if(t==10)stype="muon+";
 if(t==1)stype="protons";
 if(t==6)stype="alpha";

 if(t==3 || t==4)
  {		 
   Ene[0]= 10;
   Ene[1]= 15;
   Ene[2]= 20;
   Ene[3]= 25;
   Ene[4]= 30;
   Ene[5]= 40;
   Ene[6]= 50;
   Ene[7]= 60;
   Ene[8]= 70;
   Ene[9]= 80;
   Ene[10]= 90;
   Ene[11]= 100;
   Ene[12]= 150;
   Ene[13]= 200;
   Ene[14]= 250;
   Ene[15]= 300;
   Ene[16]= 400;
   Ene[17]= 500;
   Ene[18]= 600;
   Ene[19]= 700;
   Ene[20]= 800;
   Ene[21]= 900;
   Ene[22]= 1000;
   Ene[23]= 1500;

  
  }

 //muons	
 if(t==11||t==10)
  {
   Ene[0]=100;
   Ene[1]=200;
   Ene[2]=300;
   Ene[3]=400;
   Ene[4]=500;
   Ene[5]=600;
   Ene[6]=700;
   Ene[7]=800;
   Ene[8]=900;
   Ene[9]=1000;
   Ene[10]=1250;
   Ene[11]=1500;
   Ene[12]=1750;
   Ene[13]=2000;
   Ene[14]=5000;
   Ene[15]=10000;
  }	
   //protons        
 if(t==1)
  {
   Ene[0]=100;
   Ene[1]=200;
   Ene[2]=300;
   Ene[3]=500;
   Ene[4]=700;
   Ene[5]=1000;
   Ene[6]=2000;
   Ene[7]=3000;
   Ene[8]=10000;
   Ene[9]=20000;
  }
 string UNIT="MeV";	

 for(int i=0; i<NReco; i++)
   {
    for(int j=20; j<nene; j++)
      {
       for (int l=0;l<Ncycles;l++)
         {
          //output file
          ofstream outputTXT;
          cout << "Ene = " << Ene[j] << endl;
	  cout << Form("%s/%d/%s/RecoEvent_%s_%d_%d%s%04d%s_%s.txt", Inppath.c_str(),type,source.c_str(),startfile.c_str(),type,Ene[j],UNIT.c_str(),l+1,endfile.c_str(),RecoInd[i].c_str()) <<endl;
          outputTXT.open(Form("%s/%d/%s/RecoEvent_%s_%d_%d%s%04d%s_%s.txt", Inppath.c_str(),type,source.c_str(),startfile.c_str(),type,Ene[j],UNIT.c_str(),l+1,endfile.c_str(),RecoInd[i].c_str()));
          outputTXT << "cyc"  << " " ;
          outputTXT << "ncase"  << " " ;
          outputTXT << "tyMC"  << " " ;
          outputTXT << "EkMC"  << " " ;
          outputTXT << "pMC"  << " " ;
          outputTXT << "X0MC" << " " ;
          outputTXT << "Y0MC" << " " ;
          outputTXT << "Z0MC" << " " ;
          outputTXT << "CX0MC" << " " ;
          outputTXT << "CY0MC"  << " " ;
          outputTXT << "CZ0MC"  << " " ;
          outputTXT << "CX0reco" << " " ;
          outputTXT << "CY0reco"  << " " ;
          outputTXT << "CZ0reco"  << " " ;					       
          outputTXT << "T1"  << " " ;
          outputTXT << "T2"  << " " ;
          outputTXT << "T3"  << " " ;
          outputTXT << "T4"  << " " ;
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
          outputTXT <<endl;			       
						
          TFile*filein=new TFile(Form("%s/%d/%s/RecoEvent_%s_%d_%dMeV%d%03d%s_%s.root",Inppath.c_str(),type,source.c_str(),startfile.c_str(),type,Ene[j],seed,l+1,endfile.c_str(),RecoInd[i].c_str()),"READ");

          //Get Tree from the calibrated file	
          TTree *tree = (TTree*)filein->Get("MC");
          ALEvent *e = new ALEvent();
          tree->SetBranchAddress("Revent",&e);  
          // Get number of event in Tree
          int nentries=tree->GetEntries();

          for (int m=0;m<nentries;m++)
            {
             tree->GetEntry(m); //Load the entry i in the variable e
             if(m%100000==0) cout << "Reco Type: " << RecoInd[i] << "  Energy: " << Ene[j] << UNIT << ", Cycle: " << l+1 <<  "  Event: " << m <<endl;			 

             ////////////////////////////
             //SCINTILLATORS
             ////////////////////////////
  
             double E1=0;
             double E2=0;
             double E3=0;
             double E4=0;	  
             double Guard=0;
             //T1
             int nT1=e->get_EneT1().size();
             if(nT1>0){for(int k=0;k<nT1;k++) E1+=1000.*e->get_EneT1().at(k);}
             //T2
             int nT2=e->get_EneT2().size();
             if(nT2>0){for(int k=0;k<nT2;k++) E2+=1000.*e->get_EneT2().at(k);}
             //T3
             int nT3=e->get_EneT3().size();
             if(nT3>0){for(int k=0;k<nT3;k++) E3+=1000.*e->get_EneT3().at(k);}
             //T4
             int nT4=e->get_EneT4().size();
             if(nT4>0){for(int k=0;k<nT4;k++) E4+=1000.*e->get_EneT4().at(k);}
             //Guard
             int nTG = e->get_Eneg().size();
             if(nTG>0){for(int k=0; k<nTG; k++) Guard+=1000.*e->get_Eneg().at(k);}
  
  
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
             if(NLB >= 3) {goodTrackB=true;}		 //good track in bending plane
             if(trigNB || trigB) trig = true;
             //Number of layers with hit(s)
             int NL= e->get_NLayers();
             int NL_PR = e->get_NLayersPR();

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
 	     outputTXT << Form("%4d",l+1)  << " ";
             outputTXT << Form("%7d",e->get_ncase())  << " ";
	     outputTXT << Form("%5d",e->get_typeMC())  << " ";
	     outputTXT << Form("%5.5f",(float)e->get_EkMC())  << " ";
             outputTXT << Form("%5.5f",(float)e->get_pMC())  << " ";
             outputTXT << Form("%5.2f",(float)e->get_X0MC())  << " ";
             outputTXT << Form("%5.2f",(float)e->get_Y0MC())  << " ";
             outputTXT << Form("%5.2f",(float)e->get_Z0MC())  << " ";
             outputTXT << Form("%1.4f",(float)e->get_CX0MC())  << " ";
             outputTXT << Form("%1.4f",(float)e->get_CY0MC())  << " ";
             outputTXT << Form("%1.4f",(float)e->get_CZ0MC())  << " ";
             outputTXT << Form("%1.4f",(float)e->get_CX0reco())  << " ";
             outputTXT << Form("%1.4f",(float)e->get_CY0reco())  << " ";
             outputTXT << Form("%1.4f",(float)e->get_CZ0reco())  << " ";
             outputTXT << Form("%5.2f",(float)E1)  << " ";
             outputTXT << Form("%5.2f",(float)E2)  << " ";
             outputTXT << Form("%5.2f",(float)E3)  << " ";
             outputTXT << Form("%5.2f",(float)E4)  << " ";
             outputTXT << Form("%6.3f",TMath::Sign(1,e->get_deflecPR())*1000*e->get_p0PR())  << " ";
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
             outputTXT << Form("%6.3f",TMath::Sign(1,e->get_typereco())*e->get_p0reco())  << " ";
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
             outputTXT <<endl;
            }//m number of entries
          outputTXT.close();
          filein->Close();
         } //end l number of cycles
      } //end j energy
   }//end i reco type
} //end function 




