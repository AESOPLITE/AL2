////////////////////////////////////////////////////////////////////////////////////////// 
///    Author: Pierre-Simon Mangeard, psmangeard@gmail.com
///    Department of Physics and Astronomy, University of Delaware, February 10 , 2018
////////////////////////////////////////////////////////////////////////////////////////// 

#include "headers.h"
#include "ALEvent.h"
#include "LoadDataparameters.h"
#include "TChain.h"
#include "TPaveStats.h"
#include "TGaxis.h"


ClassImp(ALTckhit)
ClassImp(ALEvent)

void Occupancy(string fp,string s,string c);

/*int doy(int y,int m,int d);


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
*/

void Occupancy(string fp,string s,string c)
{
 //s: File name   
 //c: trigger coincidence: used for output filenames only    

 string file[1]={""};
 string filepath[1]={""};
 string coinc[1]={""};

 file[0]=s;
 coinc[0]=c;   
 filepath[0]=fp;
 int Ncut=1;
 
 //string scut[1]={"All (1+ hit)"};
 string scut[4]={"All","T1&T4&T3","T1&T4&T3&7 layers","T1&T4&T3&7 layers & used hits"};
 
 //string sBoard[7]={"A","B","C","D","E","H","G"};	
 //string sBoard[7]={"H","B","C","D","E","I","A"};	
 //string sBoard[7]={"G","B","H","D","E","I","A"};	
 //string sBoard[7]={"C","B","A","D","E","I","G"};	
 string sBoard[8]={"C","H","B","A","E","F","G","D"};	
	

//////////////////////////// 
//Occupancy histograms
//////////////////////////// 
    
 TH1F** LOcc=new TH1F*[Ncut];
 TH1F** ClusOcc=new TH1F*[Ncut];
 TH1F*** ChipOcc=new TH1F**[Ncut];
 TH1F*** fStripOcc=new TH1F**[Ncut];
 TH1F*** StripOcc=new TH1F**[Ncut];
 TH1F*** CoordOcc=new TH1F**[Ncut];
 
 int NL=8;
 
 double*** LvsChipperL=new double**[NL];
 for(int i=0;i<NL;i++) 
   {
    LvsChipperL[i]=new double*[NL];
    for(int j=0;j<NL;j++) 
      { 
       LvsChipperL[i][j]=new double[12]; 
       for(int k=0;k<12;k++) 
         { 
          LvsChipperL[i][j][k]=0;   
         }       
      }
   } 
   
 TH2F**ChipperLEff=new TH2F*[NL];
 for(int i=0;i<NL;i++) 
   {
    ChipperLEff[i]=new TH2F(Form("Efficiency for events with layer %i hitted",i),Form("Efficiency for events with layer %i hitted",i),12,0,12,NL,0,NL);
    ChipperLEff[i]->GetXaxis()->SetTitle("Chip (0 to 11)");
    ChipperLEff[i]->GetYaxis()->SetTitle("Layer (0 to 7)");
    ChipperLEff[i]->SetTitle(Form("Efficiency for events with hit(s) on L%i (Board %s)",i,sBoard[i].c_str()));   
   } 
    
    
 TH2F*Chip2Doccupancy=new TH2F(Form("%% of Occupancy"),Form("%% of Occupancy"),12,0,12,NL,0,NL);
 Chip2Doccupancy->GetXaxis()->SetTitle("Chip (0 to 11)");
 Chip2Doccupancy->GetYaxis()->SetTitle("Layer (0 to 7)");
 Chip2Doccupancy->SetTitle(Form("%% of Occupancy per chip"));   

 
 for(int i=0;i<Ncut;i++)
   {  
    LOcc[i]=new TH1F(Form("Layer occupancy, %s",scut[i].c_str()),Form("Layer occupancy, %s",scut[i].c_str()),10,0,10);
    LOcc[i]->GetXaxis()->SetTitle("Layer (0 to 7)");
    LOcc[i]->GetYaxis()->SetTitle("% of total number of events");
    LOcc[i]->SetLineColor(1+i);
    LOcc[i]->SetLineWidth(1);  
    LOcc[i]->SetMinimum(0);  

    ClusOcc[i]=new TH1F(Form("Cluster occupancy, %s",scut[i].c_str()),Form("Cluster occupancy, %s",scut[i].c_str()),10,0,10);
    ClusOcc[i]->GetXaxis()->SetTitle("Layer (0 to 7)");
    ClusOcc[i]->GetYaxis()->SetTitle("Cluster number");
    ClusOcc[i]->SetLineColor(1+i);
    ClusOcc[i]->SetLineWidth(1);  
    ClusOcc[i]->SetMinimum(0);  
    
    ChipOcc[i]=new TH1F*[NL];
    fStripOcc[i]=new TH1F*[NL];
    StripOcc[i]=new TH1F*[NL];
    CoordOcc[i]=new TH1F*[NL];
    for(int j=0;j<NL;j++)
      {    
       ChipOcc[i][j]=new TH1F(Form("Chip ID L%d, %s",j,scut[i].c_str()),Form("Chip ID L%d, %s",j,scut[i].c_str()),15,0,15);
       ChipOcc[i][j]->GetXaxis()->SetTitle("Chip ID");
       ChipOcc[i][j]->GetYaxis()->SetTitle("Entries");
       ChipOcc[i][j]->SetLineColor(1+i);
       ChipOcc[i][j]->SetLineWidth(1);
       ChipOcc[i][j]->GetXaxis()->SetRangeUser(0,15);  
       ChipOcc[i][j]->SetMinimum(0);  
       fStripOcc[i][j]=new TH1F(Form("First strip ID L%d, %s",j,scut[i].c_str()),Form("First strip ID L%d, %s",j,scut[i].c_str()),769,0,769);
       fStripOcc[i][j]->GetXaxis()->SetTitle("First strip ID");
       fStripOcc[i][j]->GetYaxis()->SetTitle("Entries");
       fStripOcc[i][j]->SetLineColor(1+i);
       fStripOcc[i][j]->SetLineWidth(1);
       fStripOcc[i][j]->GetXaxis()->SetRangeUser(0,769);  
       fStripOcc[i][j]->SetMinimum(0);  
       StripOcc[i][j]=new TH1F(Form("Strip L%d, %s",j,scut[i].c_str()),Form("Strip L%d, %s",j,scut[i].c_str()),769,0,769);
       StripOcc[i][j]->GetXaxis()->SetTitle("Strip");
       StripOcc[i][j]->GetYaxis()->SetTitle("Entries");
       StripOcc[i][j]->SetLineColor(1+i);
       StripOcc[i][j]->SetLineWidth(1);
       StripOcc[i][j]->GetXaxis()->SetRangeUser(0,769);  
       StripOcc[i][j]->SetMinimum(0);  
       CoordOcc[i][j]=new TH1F(Form("Cluster coord. L%d, %s",j,scut[i].c_str()),Form("Cluster coord. L%d, %s",j,scut[i].c_str()),200,-100,100);
       if(j==0||j==5||j==7)CoordOcc[i][j]->GetXaxis()->SetTitle("X (mm)");
       else CoordOcc[i][j]->GetXaxis()->SetTitle("Y (mm)");
       CoordOcc[i][j]->GetYaxis()->SetTitle("Entries");
       CoordOcc[i][j]->SetLineColor(1+i);
       CoordOcc[i][j]->SetLineWidth(1);
       CoordOcc[i][j]->GetXaxis()->SetRangeUser(-100,100);    
       CoordOcc[i][j]->SetMinimum(0);
      }//j
   }//i

    
 //Create TChain to merge the files for a given energy
 TChain*chain=new TChain("Data");

 chain->Add(Form("%s/%s.EVENT_RK.root",filepath[0].c_str(),file[0].c_str()));
    
 //Define variables to read event
 ALEvent *e = new ALEvent();     
 //Set address to access event data
 chain->SetBranchAddress("event",&e); 
 
 // Get number of event in Tree
 int nentries=chain->GetEntries();
 cout << "Number  of events: " << nentries << endl;  
      
 for (int j=0;j<nentries;j++)
   {
    chain->GetEntry(j); //Load the entry i in the variable e 

    if(j%10000==0) cout << "Event: " << j <<endl;
    //cout << "Event: " << j <<endl;
    int nnhits = (int) e->get_Nhits();
    //cout << "nnhits: " << nnhits <<endl;
 
     int runnumber= e->get_runnumber();
    //if (runnumber!=7082 && runnumber!=7083 && runnumber!=7084) continue;
    //if (runnumber>7085) continue;
    //if (e->get_hPSE1b()<19) continue;
    
    ////////////////////////////////////
    //OCCUPANCY
    //////////////////////////////////// 
    if(e->get_EneT1()[0]>1000)      continue;
    if(e->get_EneT2()[0]<100)      continue;
    if(e->get_EneT3()[0]>=1000)      continue;
    if(e->get_EneT4()[0]>=1000)      continue;
    if(e->get_Eneg()[0]>15)      continue;
    //if(e->get_deflecPR()!=0)      continue;

    //if(e->get_TrTrig1()!=1)      continue; 
    //if(e->get_TrTrig0()!=1)      continue; 
     
     
    //if(e->get_EneT1().at(0)<0 ||e->get_EneT4().at(0)<0)
    // {   
    //  continue;
    // }
    
    int* Ltmp=new int[NL];
    for(int i=0;i<NL;i++)Ltmp[i]=0;
    int** LCtmp=new int*[NL];
    for(int i=0;i<NL;i++)
      {
       LCtmp[i]=new int[12]; 
       for(int jk=0;jk<12;jk++)
         {
          LCtmp[i][jk]=0;
         }
      }   
      
    unsigned int  Ti=(unsigned int) e->get_Ti(); 
    //internal trigger
    int* Lay=new int[NL];
    for(int ij=0;ij<NL;ij++) Lay[ij]=(int)((Ti >>ij) & 0x01);   
    //cout << "after Lay " <<endl;

    for(int i=0;i<nnhits;i++)
      { 
       //cout << "in loop: "<< i <<endl;
   
       //if(e->get_hits().at(i)->get_flagPR()!=1)continue;
       int L=e->get_hits().at(i)->get_L();
       //cout << "after get_L" <<endl;

       int fStripID=e->get_hits().at(i)->get_fstripID();
       //cout << "after get_fstripID" <<endl;

       fStripOcc[0][L]->Fill(fStripID);
       StripOcc[0][L]->Fill(fStripID);
       int nstrips=e->get_hits().at(i)->get_nstrips();
       //cout << "after nstrips" <<endl;

       for(int ij=1;ij<=nstrips;ij++) StripOcc[0][L]->Fill(fStripID+ij);
       //cout << "after nstrips loop" <<endl;

       int chip=e->get_hits().at(i)->get_chip();
       ChipOcc[0][L]->Fill(chip);
       float x=e->get_hits().at(i)->get_x();
       float y=e->get_hits().at(i)->get_y();
       float coord=y;//B plan per default
       if(L==0||L==5||L==7)  coord=x;//NB plane
       //cout << "after if L" <<endl;

       CoordOcc[0][L]->Fill(10*coord);
       //Cluster occupancy
       ClusOcc[0]->Fill(L);
       //Layer occupancy
       Ltmp[L]++;
       LCtmp[L][chip]++;
       if(Ltmp[L]==1)
        {
         LOcc[0]->Fill(L);
        } 
       if(LCtmp[L][chip]==1)
        {
         Chip2Doccupancy->Fill(chip,L,1);
         for(int ijk=0;ijk<NL;ijk++)
           {
            if(Lay[ijk]==1)   LvsChipperL[ijk][L][chip]++;
           } 
        }
       //cout << "before second cut" <<endl;
       /* 
       //Second cut
       //T1 and T4 and 1+ hit
       if(e->get_EneT1().at(0)>0 && e->get_EneT4().at(0)>0)
        {   
        // cout << "in second cut" <<endl;
        // cout << "fStripID: " << fStripID<<endl;

         fStripOcc[1][L]->Fill(fStripID);
         StripOcc[1][L]->Fill(fStripID);
         //cout << "before loop" <<endl;

         for(int ij=1;ij<=nstrips;ij++) StripOcc[1][L]->Fill(fStripID+ij);
         //cout << "after loop" <<endl;

         ChipOcc[1][L]->Fill(chip);
         CoordOcc[1][L]->Fill(10*coord);
         ClusOcc[1]->Fill(L);
         if(Ltmp[L]==1) LOcc[1]->Fill(L);
        // cout << "end second cut" <<endl;

		}	
       //cout << "before third cut" <<endl;
	      		
        //Third cut
        //8 layers with hits
        if(e->get_EneT1().at(0)>0 && e->get_EneT4().at(0)>0 && e->get_Ti()==127)
         {  
          fStripOcc[2][L]->Fill(fStripID);
          StripOcc[2][L]->Fill(fStripID);
          for(int ij=1;ij<=nstrips;ij++) StripOcc[2][L]->Fill(fStripID+ij);
          ChipOcc[2][L]->Fill(chip);
          CoordOcc[2][L]->Fill(10*coord);
          ClusOcc[2]->Fill(L);
          if(Ltmp[L]==1) LOcc[2]->Fill(L);
		 }	
        //cout << "before fourth cut" <<endl;
 
        //Fourth cut
        //only hits used in reconstructionBoard[i].c_str()
        if(e->get_EneT1().at(0)>0 && e->get_EneT4().at(0)>0 && e->get_Ti()==127&&e->get_hits().at(i)->get_flagPR()==1)
         {   
          fStripOcc[3][L]->Fill(fStripID);
          StripOcc[3][L]->Fill(fStripID);
          for(int ij=1;ij<=nstrips;ij++) StripOcc[3][L]->Fill(fStripID+ij);
          ChipOcc[3][L]->Fill(chip);
          CoordOcc[3][L]->Fill(10*coord);
          ClusOcc[3]->Fill(L);
          if(Ltmp[L]==1) LOcc[3]->Fill(L);
         }//fourth cut*/ 
      }//i 
    //cout << "after nnhits " <<endl;
  
   }//j
   

//Normalize to get hardware trigger efficiency   
 //float scaler=100./nentries;
 float scaler=1;
 for(int i=0;i<Ncut;i++)
   {    
    LOcc[i]->Scale(scaler);
  //  LOcc[i]->SetMaximum(scaler);
    //ClusOcc[i]->Scale(scaler);
    // ClusOcc[i]->SetMaximum(scaler);
   
    for(int j=0;j<NL;j++)
       {
        //ChipOcc[i][j]->Scale(scaler);
       // ChipOcc[i][j]->SetMaximum(scaler);
        //fStripOcc[i][j]->Scale(scaler);
       // fStripOcc[i][j]->SetMaximum(scaler);
       // CoordOcc[i][j]->Scale(scaler);
       // CoordOcc[i][j]->SetMaximum(scaler);
        //StripOcc[i][j]->Scale(scaler);
        //StripOcc[i][j]->SetMaximum(scaler);
      }    
   }
  
  
  for(int i=0;i<NL;i++) 
   {
    for(int j=0;j<NL;j++) 
      { 
       double tmpChip=0;
       for(int k=0;k<12;k++) 
         { 
          ChipperLEff[i]->Fill(k,j,100.*LvsChipperL[i][j][k]/LOcc[0]->GetBinContent(1));
          tmpChip+=LvsChipperL[i][j][k];
         }     
       //ChipperLEff[i]->Fill(12,j,100.*tmpChip/LOcc[0]->GetBinContent(1));
         
      }
   } 
 
//////////////////////////////   
// Display  
//////////////////////////////   
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(1);
 gStyle->SetPalette( kDarkBodyRadiator);
 gStyle->SetPalette(kTemperatureMap);
 TGaxis::SetMaxDigits(4);

//////////////////////////////    

 string PDFFile=Form("%s/Occupancies_%s_%s.pdf",filepath[0].c_str(),file[0].c_str(),coinc[0].c_str());


//////////////////////////////    
 TCanvas*CanLOcc=new TCanvas("Layer occupancy","Layer occupancy",200,10,1400,600);  
 TLegend* leg=new TLegend(0.12,0.12,0.6,0.4);
 leg->SetBorderSize(0);leg->SetFillStyle(0);
 for(int i=0;i<Ncut;i++) leg->AddEntry(LOcc[i],Form("%s",scut[i].c_str()),"l");
 CanLOcc->Divide(2,1);
 CanLOcc->cd(1);
 LOcc[0]->GetYaxis()->SetTitleOffset(1.5);
 LOcc[0]->Draw("hist");
 for(int i=1;i<Ncut;i++)LOcc[i]->Draw("hist same");
 leg->Draw("same");
 CanLOcc->cd(2);
 ClusOcc[0]->GetYaxis()->SetTitleOffset(1.5);
 ClusOcc[0]->Draw("hist");
 for(int i=1;i<Ncut;i++)ClusOcc[i]->Draw("hist same");
 CanLOcc->Print(Form("%s(",PDFFile.c_str()),Form("Title:Occupancy"));    
 
 
 TCanvas**CanHOcc2=new TCanvas*[NL];
 
 for(int i=0;i<NL;i++)
   {
    CanHOcc2[i]=new TCanvas(Form("Hit occupancy, L%d",i),Form("Hit occupancy, L%d",i),200,10,1400,600);  
    CanHOcc2[i]->cd();
    StripOcc[0][i]->GetYaxis()->SetTitleOffset(1.5);
//     //StripOcc[0][i]->SetMaximum(4*StripOcc[0][i]->GetEntries()/StripOcc[0][i]->GetNbinsX());
    StripOcc[0][i]->Draw("hist");
    for(int j=1;j<Ncut;j++)StripOcc[j][i]->Draw("hist same");
    CanHOcc2[i]->Print(Form("%s",PDFFile.c_str()),Form("Title:Occupancy All L%d, (B%s)",i,sBoard[i].c_str()));
   }
 
 
 
 
 TCanvas**CanHOcc=new TCanvas*[NL];
 
 for(int i=0;i<NL;i++)
   {
    CanHOcc[i]=new TCanvas(Form("Hit occupancy, L%d",i),Form("Hit occupancy, L%d",i),200,10,1400,1200);  
    CanHOcc[i]->Divide(2,2);
    CanHOcc[i]->cd(1);
    ChipOcc[0][i]->GetYaxis()->SetTitleOffset(1.5);
    ChipOcc[0][i]->Draw("hist");
    for(int j=1;j<Ncut;j++)ChipOcc[j][i]->Draw("hist same");
    leg->Draw("same");
    CanHOcc[i]->cd(2);
    fStripOcc[0][i]->GetYaxis()->SetTitleOffset(1.5);
    //fStripOcc[0][i]->SetMaximum(3*fStripOcc[0][i]->GetEntries()/fStripOcc[0][i]->GetNbinsX());
    fStripOcc[0][i]->Draw("hist");
    for(int j=1;j<Ncut;j++)fStripOcc[j][i]->Draw("hist same");
    CanHOcc[i]->cd(3);
    CoordOcc[0][i]->GetYaxis()->SetTitleOffset(1.5);
    //CoordOcc[0][i]->SetMaximum(3*CoordOcc[0][i]->GetEntries()/CoordOcc[0][i]->GetNbinsX());
    CoordOcc[0][i]->Draw("hist");
    for(int j=1;j<Ncut;j++)CoordOcc[j][i]->Draw("hist same");
    CanHOcc[i]->cd(4);
    StripOcc[0][i]->GetYaxis()->SetTitleOffset(1.5);
    //StripOcc[0][i]->SetMaximum(3*StripOcc[0][i]->GetEntries()/StripOcc[0][i]->GetNbinsX());
    StripOcc[0][i]->Draw("hist");
    for(int j=1;j<Ncut;j++)StripOcc[j][i]->Draw("hist same");
    //if(i==6)CanHOcc[i]->Print(Form("%s)",PDFFile.c_str()),Form("Title:Occupancy L%d (B%s)",i,sBoard[i].c_str()));    
    if (i<NL-1) CanHOcc[i]->Print(Form("%s",PDFFile.c_str()),Form("Title:Occupancy L%d, (B%s)",i,sBoard[i].c_str()));    
    else CanHOcc[i]->Print(Form("%s)",PDFFile.c_str()),Form("Title:Occupancy L%d, (B%s)",i,sBoard[i].c_str()));    
   }
/*
  gStyle->SetPaintTextFormat("4.1f");
  
  TCanvas**CanLvsCperL=new TCanvas*[NL];
  
  for(int i=0;i<NL;i++)
   {
    CanLvsCperL[i]=new TCanvas(Form("CanLvsCperL %d",i),Form("CanLvsCperL %d",i),200,10,1500,900);
    CanLvsCperL[i]->cd();
    gPad->SetGridx(1);
    gPad->SetGridy(1);
    ChipperLEff[i]->GetXaxis()->SetNdivisions(12,0,0);
    ChipperLEff[i]->GetYaxis()->SetNdivisions(NL,0,0);
    ChipperLEff[i]->Draw("colz text");
    ChipperLEff[i]->SetContour(60);
    ChipperLEff[i]->SetMarkerSize(2);
    ChipperLEff[i]->SetMaximum(15);
    ChipperLEff[i]->SetMinimum(0);
    CanLvsCperL[i]->Print(Form("%s",PDFFile.c_str()),Form("Title:Chip occupancy, fired L%d, (B%s)",i,sBoard[i].c_str()));    
   }    
 
 Chip2Doccupancy->Scale(100./nentries);
 TCanvas*CanChip2Doccupancy=new TCanvas("2D Chip occupancy","2D Chip occupancy",200,10,1500,900);
 CanChip2Doccupancy->cd();
 gPad->SetGridx(1);
 gPad->SetGridy(1);
 Chip2Doccupancy->GetXaxis()->SetNdivisions(12,0,0);
 Chip2Doccupancy->GetYaxis()->SetNdivisions(NL,0,0);
 Chip2Doccupancy->Draw("colz text");
 Chip2Doccupancy->SetContour(60);
 Chip2Doccupancy->SetMarkerSize(2);
 Chip2Doccupancy->SetMaximum(10);
 Chip2Doccupancy->SetMinimum(0);
 CanChip2Doccupancy->Print(Form("%s)",PDFFile.c_str()),Form("Title:2D Chip occupancy"));    
 */   

}

