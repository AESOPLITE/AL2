////////////////////////////////////////////////////////////////////////////////////////// 
///    Author: Pierre-Simon Mangeard, psmangeard@gmail.com
///    Department of Physics and Astronomy, University of Delaware, October 5 , 2017
////////////////////////////////////////////////////////////////////////////////////////// 

#include "headers.h"
#include "ALEvent.h"
#include "LoadDataparameters.h"
#include "LoadMCparameters.h"
#include "TChain.h"
#include "TPaveStats.h"
#include "TGaxis.h"
#include "TF2.h"

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TMath.h"
#include "TArc.h"
#include "Fit/Fitter.h"

ClassImp(ALTckhit)
ClassImp(ALEvent)

//void DisplayEventsDefault(string file,string  coinc,int);RecoEvent_AL2NonUniB_V0_3_100MeV0001_fort.99_RK.root
//void DisplayEvents(string file,string tag,string  coinc,int);
//void DisplayOneEvent(string file,string tag,string  coinc,int,int);

//void TrackinTrigger(string file,string  coinc,int);

void DisplayEvents();


int doy(int y,int m,int d);


int doy(int y,int m,int d)
{
 int iuruu=0;
 int day=0;
 int monday[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},
                    {31,29,31,30,31,30,31,31,30,31,30,31}};
 if((y % 4) ==0 )iuruu=1 ;
 if(m!=1)
  {
   for(int i=0;i<m-1;i++)
    {
       day+=monday[iuruu][i]; 
    }  //m
  }//if
 day+=d; 
 return day;
}


void DisplayEvents()
{
 const int nbl=8;
 double B = 0.3;		//average magnetic field in T
 double c = TMath::C();
 //Load configuration parameter
 float* TckZPos=new float[8];
 float*OffsetLL=new float[8];
 float*OffsetRL=new float[8];
 float*TrigThresh=new float[5];
 for(int i=0;i<nbl;i++)TckZPos[i]=OffsetLL[i]=OffsetRL[i]=0;
 for(int i=0;i<5;i++)TrigThresh[i]=0;
 int geoconf=7;
 string paramfile=Form("Dataparameters%d.dat",geoconf); 

 LoadDataparameters(paramfile,TckZPos,OffsetLL,OffsetRL,TrigThresh);

 for(int i=0;i<nbl;i++)
   {
    cout << "L"<<i <<", TckZPos:" << TckZPos[i] ;
    cout << ", OffsetLL:" << OffsetLL[i] ;
    cout << ", OffsetRL:" << OffsetRL[i] << endl;
   } 

 string Inppath="/media/psmangeard/DATA/Documents/UDEL/AESOPLITE2/NewPSOCRuns";
 //string startfile="NL2685_2688_2700.BPD";
 string startfile="NL2984.BPD";
 string endfile=".EVENT_RK";
 string directory= "/media/psmangeard/DATA/Documents/UDEL/AESOPLITE2/NewPSOCRuns";

 //float mass=0.000511;//electon mass in GeV
 //if(t==11 || t==10)     mass=0.10566;//muon mass in GeV
 //if(t==1)     mass=0.93827;//proton mass in GeV
 //if(t==6)     mass=3.7273;//alpha-particle mass in GeV

 
 TFile *fileout=new TFile(Form("%s/DisplayEvent_%s%s.root",Inppath.c_str(),startfile.c_str(),endfile.c_str()),"RECREATE");
 TCanvas *can=new TCanvas();
 
 
 int firstpage=0;
 TFile*filein=new TFile(Form("%s/%s%s.root",Inppath.c_str(),startfile.c_str(),endfile.c_str()),"READ");

 //Get Tree from the calibrated file   
 TTree *tree = (TTree*)filein->Get("Data");
 ALEvent *e = new ALEvent();
 tree->SetBranchAddress("event",&e);  
 
 // Get number of event in Tree
 int nentries=tree->GetEntries();
 cout << "Number  of events: " << nentries << endl;
 
 float ZMax=50;
 float ZMin=-50;
 
 bool FLAGFIT=false ;
 
 //Loop over events
 //for(int i=0;i<nentries;i++)
 for(int i=0;i<1000;i++)
   {
    tree->GetEntry(i);
    if(i%10000==0) cout << "Event: " << i <<endl;
    int nnhits=e->get_Nhits();
    uint8_t Ti=(uint8_t)e->get_Ti();
    //cout << "Extract number of hits done: "<<nnhits  <<endl;
    double deflection=e->get_deflecPR();

    ///////////////////////////////    
    //Load MC variables
    ///////////////////////////////
    //Plot events that go through T1/T3, but not through all 7 layers
    int  nhits = e->get_Nhits();
    //check trigger requirements
    bool TShell;
    bool T1=e->get_T1();
    bool T2=e->get_T2();
    bool T3=e->get_T3();
    bool T4=e->get_T4();
    bool guard=e->get_guard();
    bool Lhit[nbl] = {false,false,false,false,false,false,false,false};
    double EFoam=0;
    double EShell=0;
    double tFoam=0;
    double tShell=0;
    double E1=0;
    double tT1=0;
    double E2=0;
    double E3=0;
    double E4=0;
    double EG=0;
    //Insulation Foam
    int nTFoam=e->get_EneIsofoam().size();
    int nTShell=e->get_EneShell().size();
    if(nTFoam>0 && nTShell>0)TShell=true;
    else TShell=false; 	
    //Number of layers with hit(s)
    int NL= e->get_NLayers();
    int NLB = e->get_Layer(1) + e->get_Layer(2) + e->get_Layer(3) + e->get_Layer(4) +  e->get_Layer(6) ;
    int NLNB =  e->get_Layer(0) + e->get_Layer(5) + e->get_Layer(7);
    //Reconstruction variables
    float pPR=1000*fabs(e->get_p0PR());   //in MeV
    float ePR=e->get_EkPR();
    double deflecPR = e->get_deflecPR();      
    double chiNBPR = e->get_chi2NBPR();
    double chiBPR = e->get_chi2BPR();
    double Ekreco = e->get_Ekreco();			     //in MeV
    double preco = e->get_p0reco();
    double ndf = e->get_ndf();
    double chireco = e->get_chi2();
    double phi0 = e->get_phi0();
    double tanl = e->get_tanl();
    double cpa_reco = e->get_cpa();
    double sigma_cpa = TMath::Sqrt(e->get_cpaerr2());       //in GeV
    double e0MC;
    double p0MC;
    double cpa_MC;
    int typeMC = e->get_typeMC();
    int QMC;
    if(typeMC==3 || typeMC==11) QMC = -1;
    if(typeMC==4 || typeMC==10) QMC = 1;    
    //Angular variables at the source
    double CX0 = e->get_CX0MC();
    double CY0 = e->get_CY0MC();
    double CZ0 = e->get_CZ0MC();     
    //Calculate zenith angle in degrees
    double acosCZ = TMath::ACos(CZ0);
    double zen = 180 - (180.0/TMath::Pi())*acosCZ; 
     
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
     
    ///////////////////////////////
    //Energy Deposits
    ///////////////////////////////
    //Insulation Foam
    //if(nTFoam==0) continue;
    //for(int j=0;j<1;j++) 
    //  {
    //   EFoam+=1000.*e->get_EneIsofoam().at(j);
    //   tFoam=e->get_timeIsofoam().at(j);
    //  }
    //Shell
    //if(nTShell==0) continue;
    //for(int j=0;j<1;j++){EShell+=1000.*e->get_EneShell().at(j);}
    //T1
    int nT1=e->get_EneT1().size();
    for(int j=0;j<nT1;j++) {E1+=e->get_EneT1().at(j);}
    //T2
    int nT2=e->get_EneT2().size();
    for(int j=0;j<nT2;j++) {E2+=e->get_EneT2().at(j);}
    //T3
    int nT3=e->get_EneT3().size();
    for(int j=0;j<nT3;j++) {E3+=e->get_EneT3().at(j);}
    //T4
    int nT4=e->get_EneT4().size();
    for(int j=0;j<nT4;j++) {E4+=e->get_EneT4().at(j);}
    //Guard
    int nTG=e->get_Eneg().size();
    for(int j=0;j<nTG;j++) {EG+=e->get_Eneg().at(j);}
    for(int j=0;j<nnhits;j++)
      {
       int L= e->get_hits().at(j)->get_L();
       Lhit[L] = true;
      }
      
    //All positions vectors
      

    ///////////////////////////////	
    //Events selection
    ///////////////////////////////
 
    //cout << "Event " << i << ", NLNB = " << NLNB << ", NLB = " << NLB << endl;      
    if(e->get_deflecPR()!=0) FLAGFIT=true;

    //if(NLB==0 || NLNB==0) continue;
    //if(e->get_deflecPR()==0) continue;
    //if(EG>0) continue;
    //if(E1<=0) continue;
    //if(E2>128) continue;
    //if(E3<=200) continue;
    //if(E4<=0) continue;

    ///////////////////////////////    
    //Extract hits information
    ///////////////////////////////
 
    TGraph *grALLNB=new TGraph();
    grALLNB->SetMarkerStyle(5);
    grALLNB->SetMarkerColor(kBlack);
    grALLNB->SetMarkerSize(2);
    TGraph *grALLB=new TGraph();
    grALLB->SetMarkerStyle(5);
    grALLB->SetMarkerColor(kBlack);
    grALLB->SetMarkerSize(2);
    TGraph *grNB=new TGraph();
    grNB->SetMarkerStyle(kCircle);
    grNB->SetMarkerColor(kOrange+7);
    grNB->SetMarkerSize(2);
    TGraph *grB=new TGraph();
    grB->SetMarkerStyle(kCircle);
    grB->SetMarkerColor(kOrange+7);
    grB->SetMarkerSize(2);
    TGraph *grNBPR=new TGraph();
    grNBPR->SetMarkerStyle(kCircle);
    grNBPR->SetMarkerColor(kGreen);
    TGraph *grBPR=new TGraph();
    grBPR->SetMarkerStyle(kCircle);
    grBPR->SetMarkerColor(kGreen);

    for(int j=0;j<nnhits;j++)
      {
       int L= e->get_hits().at(j)->get_L();
       float x=e->get_hits().at(j)->get_x();
       float y=e->get_hits().at(j)->get_y();
       float z=e->get_hits().at(j)->get_z();
       int nstrip = e->get_hits().at(j)->get_nstrips();
       int fstripID=e->get_hits().at(j)->get_fstripID();		
       if (L==7 && fstripID==575 &&nstrip==1) cout << "Event " << i <<", bad chip, L7!" << endl;
       
       float xPR=e->get_hits().at(j)->get_xPR();
       float yPR=e->get_hits().at(j)->get_yPR();
       float zPR=e->get_hits().at(j)->get_zPR();
       float xreco=e->get_hits().at(j)->get_xreco();
       float yreco=e->get_hits().at(j)->get_yreco();
       float zreco=e->get_hits().at(j)->get_zreco();		
       bool flagPR=e->get_hits().at(j)->get_flagPR();
       bool fUsed = e->get_hits().at(j)->get_fUsed();
		
       if(L==0 || L==5 || L==7)//Non bending plane
        {
         grALLNB->SetPoint(grALLNB->GetN(),x,z);
	 if(flagPR)
          {
           grNB->SetPoint(grNB->GetN(),x,z);
           grNBPR->SetPoint(grNBPR->GetN(),xPR,zPR);
          }
		   
        }
       else if(L==1 || L==2|| L==3 || L==4 || L==6) //Bending plane
        {
         grALLB->SetPoint(grALLB->GetN(),y,z);
	 if(flagPR) 
	  {
           grB->SetPoint(grB->GetN(),y,z);
	   grBPR->SetPoint(grBPR->GetN(),yPR,zPR);
	  }
        }
   ///    if(L==0) 
///	{
 ///	 //MC variables at highest layer
	// e0MC = (e->get_hits().at(j)->get_eMC());               //energy at L0 in GeV
	// p0MC = 1000*TMath::Sqrt((e0MC*e0MC) - (mass*mass));
	//}
      }//j 	 

    //if(chireco > 10000) continue;

    int nZpos = e->get_posZ().size();
    for(int j=0;j<nZpos;j++)
      {
       float xpos = e->get_posX().at(j);
       float ypos = e->get_posY().at(j);		 
       float zpos = e->get_posZ().at(j);
       //cout << "xpos  = " << xpos << ", ypos = " << ypos << ", zpos = " << zpos << endl;
       // grALLNB->SetPoint(grALLNB->GetN(),xpos,zpos);
       // grALLB->SetPoint(grALLB->GetN(),ypos,zpos);
      }//j
    //cout << "done with hit extraction" << endl;
  
    ///////////////////////////////    
    //Extract Reconstructed track information
    ///////////////////////////////    
    
    TF1* fNB=new TF1("fNB","pol1",-125,125);
    fNB->SetLineColor(kBlue);
    fNB->SetLineWidth(1);
    fNB->SetLineStyle(1);    

    float zz0=0;
    //TF1* fB=new TF1("fB","pol2",-20,20);
    TF1* fB= new TF1("fB","[2]*(x+[3])*(x+[3])+[1]*(x+[3])+[0]",-100,100);
    fB->FixParameter(3,zz0);
    fB->SetLineColor(kBlue);
    fB->SetLineWidth(1);
    fB->SetLineStyle(1);    
    //cout << "Extraction of non-bending plane fit parameters done" <<endl;


    //Non bending plane
    float p0=e->get_interPR();
    float p1=e->get_slopePR();
    // cout << "p0 = "  << p0 << ", p1 = " << p1 <<endl;
    //if(p1==0) continue;
    fNB->FixParameter(0,-p0/p1);
    fNB->FixParameter(1,1./p1);

    //Bending plane
    float a=e->get_aPR();
    float b=e->get_bPR();
    float c=e->get_cPR();
    //ax^2+bx+c
    fB->FixParameter(0,c);
    fB->FixParameter(1,b);
    fB->FixParameter(2,a); 
		
    //cout << "a = "  << a << ", b = " << b << ", c = " << c << endl;


    //cout << "Extraction of bending plane fit parameters done" <<endl;

    TF1*incomingB=new TF1("incomingB","pol1",-200,200);
    TF1*incomingBout=new TF1("incomingBout","pol1",-200,200);
    TF1*outcomingB=new TF1("outcomingB","pol1",-200,200);
    float zzz[3]={TckZPos[4],TckZPos[3],TckZPos[2]};
    float curv[3]={3,3,3};
    TF1* fcurv=new TF1("fcurv","2*[0]/TMath::Power(1+TMath::Power(2*[0]*x+[1],2),3./2.)",-20,20);
    float lim=TckZPos[1];//z position of 1st layer
    float limo=TckZPos[6];//z position of 7th layer
    float aa=fB->Eval(lim);
    float diff=2*a*lim+2*a*zz0+b;
    float aaout=fB->Eval(limo);
    float diffout=2*a*limo+2*a*zz0+b;  
    if(FLAGFIT)
     {
      //Incoming Straight particle  

      incomingB->SetLineStyle(2);
      incomingB->SetLineWidth(1);
      incomingB->SetLineColor(kBlue);

      incomingB->FixParameter(0,-(aa-diff*lim)/diff);
      incomingB->FixParameter(1,1./diff);
    
      incomingBout->SetLineStyle(2);
      incomingBout->SetLineWidth(1);
      incomingBout->SetLineColor(kGray);
      incomingBout->FixParameter(0,-(aa-diff*lim)/diff);
      incomingBout->FixParameter(1,1./diff);    
    
      //Outcoming Straight particle    

      outcomingB->FixParameter(0,-(aaout-diffout*limo)/diffout);
      outcomingB->FixParameter(1,1./diffout);
      outcomingB->SetLineStyle(2);
      outcomingB->SetLineWidth(1);
      outcomingB->SetLineColor(kBlue);
     
    
      //Signed curvature at the 3 points in and around magnets
      fcurv->SetParameter(0,a);
      fcurv->SetParameter(1,2*a*zz0+b);
      for(int ij=0;ij<3;ij++)
        {
         curv[ij]= fcurv->Eval(zzz[ij]);   
        }  
     }
    ///////////////////////////////    
    //Event Display 
    ///////////////////////////////
    //cout << "Start display "  << endl;
    can=new TCanvas(Form("Event %d",e->get_eventnumber()),Form("Event %d",e->get_eventnumber()),200,10,1600,1440);
    //can=new TCanvas(Form("Event %d",e->get_eventnumber()),Form("Event %d",e->get_eventnumber()),200,10,920,370);

    can->Divide(2,1);
    //Detector layout
    //Layers
    TLine**Line=new TLine*[nbl];
    TLine**LinePR=new TLine*[nbl];
	  
    double shift8L=-2.48285;	    
    //Magnets 
    TBox*boxM1=new TBox(-15,-9.61682+shift8L,-6.703,-9.61682+4.59994+shift8L);
    TBox*boxM2=new TBox(-15,-16.2513+shift8L,-6.703,-16.2513+4.59994+shift8L);
    TBox*boxM3=new TBox(6.703,-9.61682+shift8L,15,-9.61682+4.59994+shift8L);
    TBox*boxM4=new TBox(6.703,-16.2513+shift8L,15,-16.2513+4.59994+shift8L);
    boxM1->SetFillColor(kGray);
    boxM2->SetFillColor(kGray);
    boxM3->SetFillColor(kGray);
    boxM4->SetFillColor(kGray);
    //cout << "could it be here?" << endl;
    //T1
    TBox*boxT1=new TBox(-13.,33.782,13.,33.782+0.5);
    boxT1->SetFillColor(kRed);
    if(T1)boxT1->SetFillColor(kGreen);
    TPaveText*PHT1=new TPaveText(15,32,25,36);
    PHT1->AddText(Form("T1=%4d",int(E1)));
    //PHT1->AddText(Form("T1"));
    PHT1->SetFillStyle(0);PHT1->SetBorderSize(0);
    //T2
    TGraph* grT2 = new TGraph();
    grT2->SetPoint(0,-6.5,2.024);//Bottom
    grT2->SetPoint(1,6.5,2.024);//Botton
    grT2->SetPoint(2,13.5,29.964);//Top
    grT2->SetPoint(3,-13.5,29.964);//Top
    grT2->SetPoint(4,-6.5,2.024);//Bottom again
    grT2->SetFillStyle(0);
    grT2->SetLineWidth(3);
    grT2->SetLineColor(kRed);
    //if(T2)grT2->SetLineColor(kGreen); 
    if(E2>192)grT2->SetLineColor(kGreen); 
    TPaveText*PHT2=new TPaveText(15,11,25,15);
    PHT2->AddText(Form("T2=%4d",int(E2)));
    //PHT2->AddText(Form("T2"));

    PHT2->SetFillStyle(0);PHT2->SetBorderSize(0);     
    //T3
    TBox*boxT3=new TBox(-3.5,0.,3.5,0.5);
    boxT3->SetFillColor(kRed);
    //if(T3)boxT3->SetFillColor(kGreen);
    if(E3>200)boxT3->SetFillColor(kGreen); 
    TPaveText*PHT3=new TPaveText(15,-1,25,3);
    PHT3->AddText(Form("T3=%4d",int(E3)));
    //PHT3->AddText(Form("T3"));
    PHT3->SetFillStyle(0);PHT3->SetBorderSize(0);
    //Guard
    TBox*boxG1=new TBox(-13.5,-0.5588,-3.5,-0.5588+0.5);
    boxG1->SetFillColor(kRed);
    //if(guard)boxG1->SetFillColor(kGreen);
    if(EG>200)boxG1->SetFillColor(kGreen); 

    TBox*boxG2=new TBox(+3.5,-0.5588,13.5,-0.5588+0.5);
    boxG2->SetFillColor(kRed);
//    if(guard)boxG2->SetFillColor(kGreen);     
    if(EG>200)boxG2->SetFillColor(kGreen); 
    TPaveText*PHG=new TPaveText(15,-3,25,1);
    PHG->AddText(Form("G=%4d", int(EG)));
    //PHG->AddText(Form("Guard")); 
    PHG->SetFillStyle(0);PHG->SetBorderSize(0);
    
    //T4
    TBox*boxT4=new TBox(-18.,-25.59012+shift8L,18.,-25.59012+1+shift8L);
    boxT4->SetFillColor(kRed);
    if(T4)boxT4->SetFillColor(kGreen);
    TPaveText*PHT4=new TPaveText(15,-25+shift8L,25,-21+shift8L);
    PHT4->AddText(Form("T4=%4d",int(E4)));
    //PHT4->AddText(Form("T4"));
    PHT4->SetFillStyle(0);PHT4->SetBorderSize(0);
    
    //Non Bending plot   
    can->cd(1);
    
    TMultiGraph* multi=new TMultiGraph();
    multi->SetTitle(Form("Event %d",e->get_eventnumber()));
    if(NLNB>0) multi->Add(grALLNB,"p");
    if(NLNB>0) multi->Add(grNB,"p");
    //multi->Add(grNBPR,"p");	
    multi->Add(grT2,"");
    multi->Draw("a");
    multi->GetXaxis()->SetTitle("X (cm)");
    multi->GetYaxis()->SetTitle("Z (cm)");
    multi->GetYaxis()->SetTitleOffset(1.1);
    multi->GetXaxis()->SetLimits(-30,30);
    multi->SetMaximum(ZMax);
    multi->SetMinimum(ZMin);
    gPad->Modified(); gPad->Update();    
    
    TLine * Line0=new TLine(0,ZMin,0,ZMax);
    Line0->SetLineColor(kGray);
    Line0->SetLineStyle(3);
    Line0->SetLineWidth(1);
    Line0->Draw("same");
    
    //T1
    boxT1->Draw("l same");
    PHT1->Draw();
    //T2
    PHT2->Draw();
    //T3
    boxT3->SetLineWidth(1);
    boxT3->SetLineColor(1);
    boxT3->Draw("l same");
    PHT3->Draw();
    //Guard
    boxG1->SetLineWidth(1);
    boxG2->SetLineWidth(1);
    boxG1->SetLineColor(1);
    boxG2->SetLineColor(1);
    boxG1->Draw("l same");
    boxG2->Draw("l same");
    PHG->Draw();
    //T4
    boxT4->Draw("l same");
    PHT4->Draw();
    
    //Magnet
    boxM1->Draw("l same");
    boxM2->Draw("l same");
    boxM3->Draw("l same");
    boxM4->Draw("l same");           
    
    //Layers
    for(int ijk=0;ijk<nbl;ijk++)
      {
       if(ijk==0 || ijk==5 || ijk==7)
        {
         Line[ijk]=new TLine(-9,TckZPos[ijk],9,TckZPos[ijk]);
         Line[ijk]->SetLineColor(kRed);  
         Line[ijk]->SetLineWidth(1.5);  
  	}

       else
        {
         Line[ijk]=new TLine(-9,TckZPos[ijk],9,TckZPos[ijk]);
         Line[ijk]->SetLineColor(kBlack);  
         Line[ijk]->SetLineWidth(1.5);  
   	}
       Line[ijk]->Draw("same");  	
      }//ijk	 


    //Non bending straight line
    if(FLAGFIT)
      {
       if(fNB->GetParameter(1)>0) fNB->DrawF1(fNB->GetX(-30),fNB->GetX(40),"same");
       else fNB->DrawF1(fNB->GetX(40),fNB->GetX(-30),"same");
      }
   

    TPaveText*ThetaNB;
    int sh=15;
    
    //cout << "Before NB thetaIn"   <<endl; 
    
    //if(fNB->GetX(40)+sh<30)ThetaNB=new TPaveText(fNB->GetX(40),40,fNB->GetX(40)+sh,44);
    //else ThetaNB=new TPaveText(fNB->GetX(40)-sh,40,fNB->GetX(40),44);
    if(FLAGFIT)
     {
      ThetaNB=new TPaveText(0,42,sh,46);
      ThetaNB->SetFillStyle(0);ThetaNB->SetBorderSize(0);
      ThetaNB->AddText(Form("#theta_{NB}= %6.4f",TMath::ATan(p1)));
      ThetaNB->Draw();
     }
    
    //cout << "After NB thetaIn"   <<endl; 

    //TPaveText*Shell=new TPaveText(-23,40,10,50);
    //Shell->AddText(Form("Total energy loss in before L0 %4.2f MeV",EShell+EFoam+E1+E2+E3));
    //Shell->AddText(Form("Number of layers with hit NL = %d",NL));    
    //Shell->AddText(Form("Total number of hits = %d, nhits_{PR} = %d",nnhits,Nhits));
    //Shell->SetFillStyle(0);Shell->SetBorderSize(0);
    //Shell->Draw();   
	 
    //cout << "bending side plot" << endl;
    //Bending plot   
    can->cd(2);
    //Triclk to the Inverse bending track for display
    int Nn=500;
    Double_t*x=new Double_t[Nn]; 
    Double_t*y=new Double_t[Nn];
    Double_t dx=(lim-limo)/Nn;
    Double_t x1=limo;
    x[0] = x1;
    y[0] = fB->Eval(x[0]);
    for (int ij=1; ij<Nn; ij++) 
      {
       x1   = x1+dx;
       x[ij] = x1;
       y[ij] = fB->Eval(x[ij]);
      }

    TGraph *gr = new TGraph(Nn,y,x);
    gr->SetLineColor(kBlue);
    gr->SetLineWidth(2);

    TMultiGraph *multiB=new TMultiGraph();
    //multiB->SetTitle("Bending plane");
    if(NLB>0) multiB->Add(grALLB,"p");
    if(NLB>0) multiB->Add(grB,"p");
    //multiB->Add(grBPR,"p");	
    multiB->Add(grT2,"");
    if(NLB>0) multiB->Add(gr,"l");
    multiB->Draw("a");
    multiB->GetXaxis()->SetTitle("Y (cm)");
    multiB->GetYaxis()->SetTitle("Z (cm)");
    multiB->GetYaxis()->SetTitleOffset(1.1);
    multiB->GetXaxis()->SetLimits(-30,30);
    multiB->SetMaximum(ZMax);
    multiB->SetMinimum(ZMin);
    gPad->Modified();gPad->Update();
    
    Line0->Draw("same");

    //Magnet
    boxM1->Draw("l same");
    boxM2->Draw("l same");
    boxM3->Draw("l same");
    boxM4->Draw("l same");       

    //T1
    boxT1->Draw("l same");
    //T2
    //T3
    boxT3->SetLineWidth(1);
    boxT3->SetLineColor(1);
    boxT3->Draw("l same");
    //Guard
    boxG1->SetLineWidth(1);
    boxG1->SetLineColor(1);
    boxG2->SetLineWidth(1);
    boxG2->SetLineColor(1);
    boxG1->Draw("l same");
    boxG2->Draw("l same");
    //T4
    boxT4->Draw("l same");
	 
    PHT1->Draw();
    PHT2->Draw();	 
    PHT3->Draw();
    PHG->Draw();
    PHT4->Draw();

    for(int ijk=0;ijk<nbl;ijk++)
      {
       if(ijk==0 || ijk==5 || ijk==7)
        {
         Line[ijk]=new TLine(-9,TckZPos[ijk],9,TckZPos[ijk]);
         Line[ijk]->SetLineColor(kBlack);  
         Line[ijk]->SetLineWidth(1.5);  
 	}
       else
        {
         Line[ijk]=new TLine(-9,TckZPos[ijk],9,TckZPos[ijk]);
         Line[ijk]->SetLineColor(kRed);  
         Line[ijk]->SetLineWidth(1.5);  
        }
       Line[ijk]->Draw("same");  	
      }	 
	 
	//cout << "line 677"   <<endl; 
	
    if(FLAGFIT)
     {	
      if(incomingB->GetParameter(1)>0) incomingB->DrawF1(incomingB->GetX(lim),incomingB->GetX(40),"same");
      else incomingB->DrawF1(incomingB->GetX(40),incomingB->GetX(lim),"same");
    
      if(incomingBout->GetParameter(1)>0) incomingBout->DrawF1(incomingBout->GetX(lim),incomingBout->GetX(-30),"same");
      else incomingBout->DrawF1(incomingBout->GetX(-30),incomingBout->GetX(lim),"same");
       
      if(outcomingB->GetParameter(1)<0) outcomingB->DrawF1(outcomingB->GetX(limo),outcomingB->GetX(-30),"same");
      else outcomingB->DrawF1(outcomingB->GetX(-30),outcomingB->GetX(limo),"same");
     
      //cout << "Before B thetaIn"   <<endl; 

      TPaveText*ThetaIn;
      //if(incomingB->GetX(40)+sh<25)ThetaIn=new TPaveText(incomingB->GetX(40),40,incomingB->GetX(40)+sh,44);
      //else ThetaIn=new TPaveText(incomingB->GetX(40)-sh,40,incomingB->GetX(40),44);
    
      ThetaIn=new TPaveText(0,42,sh,46);    
      ThetaIn->SetFillStyle(0);ThetaIn->SetBorderSize(0);
      ThetaIn->AddText(Form("#theta_{Bin}= %6.3f",TMath::ATan(diff)));

      //cout << "after B thetaIn"   <<endl; 
    
      TPaveText*ThetaOut;
      //if(outcomingB->GetX(-30)+sh<25) ThetaOut=new TPaveText(outcomingB->GetX(-30),-34,outcomingB->GetX(-30)+sh,-30);
      // else  ThetaOut=new TPaveText(outcomingB->GetX(-30)-sh,-34,outcomingB->GetX(-30),-30);
    
      ThetaOut=new TPaveText(0,-36,sh,-32);
      ThetaOut->SetFillStyle(0);ThetaOut->SetBorderSize(0);
      ThetaOut->AddText(Form("#theta_{Bout}= %6.3f",TMath::ATan(diffout)));
    
      if(FLAGFIT)ThetaIn->Draw();
      if(FLAGFIT)ThetaOut->Draw();
      //cout << "after B thetaOut"   <<endl; 

    
      TPaveText*Def=new TPaveText(-28,-47,0,-40);
      //Def->AddText(Form("Deflection: %6.4f",(float)deflection));
      float Def2=0;
      Def2=TMath::ATan(diffout)-TMath::ATan(diff);
      deflection=Def2;
      //Def->AddText(Form("p_{MC} at L_{0}= %3.1f MeV/c",(float)p0MC));
      Def->AddText(Form("p_{PR} at L_{0}= %3.1f MeV/c",(float)pPR));
      //Def->AddText(Form("p_{RK} at L_{0}= %3.1f MeV/c",(float)preco));
      Def->SetFillStyle(0);Def->SetBorderSize(0);
      Def->Draw();
	  
      TPaveText*Cur=new TPaveText(10,-23,25,-16);
      Cur->AddText(Form("Curvature at L1=%5.4f",curv[2]));
      Cur->AddText(Form("Curvature at L2=%5.4f",curv[1]));
      Cur->AddText(Form("Curvature at L3=%5.4f",curv[0]));
      Cur->SetFillStyle(0);Cur->SetBorderSize(0);   
      //Cur->Draw();
	  
      TPaveText*Tchi2B;
      Tchi2B=new TPaveText(10,35,24,50);
      Tchi2B->SetFillStyle(0);Tchi2B->SetBorderSize(0);
      Tchi2B->SetTextColor(kBlue);
      Tchi2B->AddText(Form("#chi^{2}= %3.3f",e->get_chi2()));
      Tchi2B->AddText(Form("#chi^{2}_{B}= %3.3f",e->get_chi2BPR()));
      Tchi2B->AddText(Form("#chi^{2}_{NB}= %3.3f",e->get_chi2NBPR()));
      //if(FLAGFIT) Tchi2B->Draw(); 
	 
      TPaveText*ZenAngle;
      ZenAngle=new TPaveText(-20,42,-10,50);
      ZenAngle->SetFillStyle(0);ZenAngle->SetBorderSize(0);
      ZenAngle->SetTextColor(kBlue);
      ZenAngle->AddText(Form("Zen. angle #theta_{0}= %3.2f^{#circ}",zen));
      //ZenAngle->Draw(); 	 
   
      //if(incomingB->GetX(33.25)<-14 ||incomingB->GetX(33.25)>14)continue;
      //fileout->cd();
      //can->Write();
     }
    
    if(firstpage==0) can->Print(Form("%s/DisplayEvent_%s%s.pdf(",Inppath.c_str(),startfile.c_str(),endfile.c_str()),Form("Title:Event %d",e->get_eventnumber()));
    else can->Print(Form("%s/DisplayEvent_%s%s.pdf",Inppath.c_str(),startfile.c_str(),endfile.c_str()),Form("Title:Event %d",e->get_eventnumber()));

    firstpage=-1;
    delete can;
   }//i
	
fileout->Close();
can=new TCanvas();
can->Print(Form("%s/DisplayEvent_%s%s.pdf)",Inppath.c_str(),startfile.c_str(),endfile.c_str()));

}//end function

