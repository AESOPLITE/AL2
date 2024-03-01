//////////////////////////////////////////////////////////////////////////////////////////
///    Author: Pierre-Simon Mangeard, psmangeard@gmail.com
///    Department of Physics and Astronomy, University of Delaware, September 8, 2017
//////////////////////////////////////////////////////////////////////////////////////////

#include "MakeRawBPDEvent_511d.h"


//////////////////////////////////////////////////////////////////////////////////////////
//Test readout with internal trigger on
//////////////////////////////////////////////////////////////////////////////////////////
int MakeRawBPDEventIT(string filename)
{

  cout << "In MakeRawBPDEventIT"  <<endl;

 //Get input filename and ASIC Length and EVT Length
 vector<string> input;
 //Split the line
 input=split(&filename,' ');
 int ASILength =stoi(input.at(1));
 int EVTLength =stoi(input.at(2));
 //Open input file
 ifstream filestr;
 filestr.open(input.at(0));
 //if(!filestr.is_open())
 // {
 //  cout << "The file " <<input.at(0) << " is not open ... "<< endl ;
 //  return -1;
 // }

 //Output root file
 TFile*fileout=new TFile(Form("%s.root",input.at(0).c_str()),"RECREATE");
 cout << "Output file is created" <<endl;

 // Create a TTree
 TTree *tree = new TTree("BPD","BPD Raw event");
 ALEvent *e = new ALEvent();

 // Create a branch with event
 tree->Branch("event",&e);
 
 //Temporary variable for internal triggers
 int*Titmp=new int[8];
 for (int i=0;i<8;i++)Titmp[i]=0;
 int*Tictmp=new int[8];
 for (int i=0;i<8;i++)Tictmp[i]=0;

 int nL=0;
 int iL=0;
 vector<ALTckhit*> Hh;

///////////////////////////////////////////////
//Define variables needed during the reading of the file
///////////////////////////////////////////////

 //Line number
 int kLine=0;
 //Event number
 int kEvent=0;

 //vector of the last "PHA" lines: NOW SPE1
 vector <string> prevPHAline;
 //Number of "PHA" lines kept in memory
 int NPHAMem=5;
 //Last "EVT" lines
 string prevEVTline=" ";
 double prevGo=-999;


 //LAST CT1 and CT3 line info
  //HOUSEKEEPING FROM COUNTERS 1 AND 3
 //Data FROM "CT1" LINE
 int yCT1=-1;//Year from CT1 line linked to the event (last read CT1 line)
 int mCT1=-1;//Month from CT1 line linked to the event (last read CT1 line)
 int dCT1=-1;//Day from CT1 line linked to the event (last read CT1 line)
 int hCT1=-1;//Hour from CT1 line linked to the event (last read CT1 line)
 int miCT1=-1;//Minute from CT1 line linked to the event (last read CT1 line)
 int sCT1=-1;//Second from CT1 line linked to the event (last read CT1 line)
 float TempCT1=-999; //Temperature measured on the board CT1

 int OnTimeCT1=-1;//1/second counter which now gives time since power on (the on-chip batteries have failed; this used to keep incrementing with power off)
 int LastCT1=-1;//The last command received by the payload, expressed as a decimal number (it is in HeX on the GUI display)
 int CountCT1=-1;//Count of commands received by the payload since power on

 //Barometer information: NOT INTERPRETED f for (int i=0;i<8;i++)Ldummy[i]=-1;rom line CT1
 float Baro1T=-999;//Barometer 1 Temperature
 float Baro1P=-999;//Barometer 1 Pressure
 float Baro2T=-999;//Barometer 2 Temperature
 float Baro2P=-999;//Barometer 2 Pressure
 //Barometer information: INTERPRETED from line CT1
 float TempB1=-999;//Barometer 1 Temperature
 float TempB2=-999;//Barometer 2 Temperature
 float PressB1=-999;//Barometer 1 Pressure
 float PressB2=-999;//Barometer 2 Pressure

 float GOCT1=-999;
 float coinCT1=-999;

 //Voltages
 float Volt5VCT1=-999;  // Positive 5V from line CT1
 float Volt15VCT1=-999; // Positive 15V from line CT1

 //Data FROM "CT3" LINE
 int yCT3=-1;//Year from CT3 line linked to the event (last read CT3 line)
 int mCT3=-1;//Month from CT3 line linked to the event (last read CT3 line)
 int dCT3=-1;//Day from CT3 line linked to the event (last read CT3 line)
 int hCT3=-1;//Hour from CT3 line linked to the event (last read CT3 line)
 int miCT3=-1;//Minute from CT3 line linked to the event (last read CT3 line)
 int sCT3=-1;//Second from CT3 line linked to the event (last read CT3 line)
 float TempCT3=-999; //Temperature measured on the board CT3

 int OnTimeCT3=-1;//1/second counter which now gives time since power on (the on-chip batteries have failed; this used to keep incrementing with power off)
 int LastCT3=-1;//The last command received by the payload, expressed as a decimal number (it is in HeX on the GUI display)
 int CountCT3=-1;//Count of commands received by the payload since power on
 //Voltages
 float Volt5VCT3=-999;  // Positive 5V from line CT3
 float Volt15VCT3=-999; // Positive 15V from line CT3
 //TRIGGER RATES (PHA AND LOGIC) from CT3
 float T1L=-1;
 float T1A=-1;
 float T2L=-1;
 float T2A=-1;
 float T3L=-1;
 float T3A=-1;
 float T4L=-1;
 float T4A=-1;
 float GRDL=-1;
 float GRDA=-1;

  //HOUSEKEEPING FROM POW
 int yPOW=-1;
 int mPOW=-1;
 int dPOW=-1;
 int hPOW=-1;
 int miPOW=-1;
 int sPOW=-1;
 int OnTimePOW=-1;
 float MainC=-999;
 float MainV=-999;
 float HeatC=-999;
 float HeatV=-999;
 float TrackC=-999;
 float TrackV=-999;

 //From VCI line
 int yVCI=-1;
 int mVCI=-1;
 int dVCI=-1;
 int hVCI=-1;
 int miVCI=-1;
 int sVCI=-1;
 int* LrVCI=new int[8];
 for (int ijk=0;ijk<8;ijk++)LrVCI[ijk]=0;
 int NCT1words=25; //CT1 line
 int NCT3words=21; //CT3 line
 int NPOWwords=16; //POW line
 int NVCIwords=33; //VCI line

 //number of words per line
 //int NPHAwords=13; //PHA line for MIPFlit3.30
 //int NPHAwords=11; //PHA line for MIPFlit3.31
 int NPHAwords=12; //PHA line for MIPFlit3.72
 
 int NPSE1words=39;  //SPE1 line MPIFLit 5.03e, 5.03f,5.09u
 int NPSE2words=16;  //SPE2 line MPIFLit 5.09u
 int NPEHF1words=10;  //PEHF1 line MPIFLit 5.09u
 int NPEHF2words=17;  //PEHF2 line MPIFLit 5.09u
 int NPEHF3words=19;  //PEHF3 line MPIFLit 5.09u
 int NPEHF4words=38  ;  //PEHF4 line MPIFLit 5.09u
 int NPMHF1words=26 ;//PMHF1 line MPIFLit 5.09u
 int NPMHF2words=17 ;//PMHF2 line MPIFLit 5.09u
 int NPMHF3words=28 ;//PMHF3 line MPIFLit 5.09u
 
 int NEVTwords=0;
 if(EVTLength==0)  NEVTwords=4; //EVT line from MIPFlit3.30 to 3.35
 if(EVTLength==1)  NEVTwords=16; //Was increased at the same time of ASIC Length
 if(EVTLength==2)  NEVTwords=18; //Was increased at the same time of ASIC Length from NL0155

 int NASIwords= 5; //ASI line

 //PEHF HousekeepingNL4130.BPD.EVENT_RK.root
 int yEPHK1=-1;//Year from PEHF1 line linked to the event
 int mEPHK1=-1;//Month from PEHF1 line linked to the event
 int dEPHK1=-1;//Day from PEHF1 line linked to the event
 int hEPHK1=-1;//Hour from PEHF1 line linked to the event
 int miEPHK1=-1;//Minute from PEHF1 line linked to the event 
 int sEPHK1=-1;//Second from PEHF1 line linked to the event
 
 int yEPHK1b=-1;//Year from PEHF1 line Date linked to the event
 int mEPHK1b=-1;//Month from PEHF1 line Date linked to the event
 int dEPHK1b=-1;//Day from PEHF1 line Date linked to the event
 int hEPHK1b=-1;//Hour from PEHF1 line Date linked to the event
 int miEPHK1b=-1;//Minute from PEHF1 line Date linked to the event
 int sEPHK1b=-1;//Second from PEHF1 line Date linked to the event
  
 int yEPHK4=-1;//Year from PEHF4 line linked to the event
 int mEPHK4=-1;//Month from PEHF4 line linked to the event
 int dEPHK4=-1;//Day from PEHF4 line linked to the event
 int hEPHK4=-1;//Hour from PEHF4 line linked to the event
 int miEPHK4=-1;//Minute from PEHF4 line linked to the event
 int sEPHK4=-1;//Second from PEHF4 line linked to the event 
 
 //PEHF1
 int RunEPHK=-1; 
 string SourceEPHK="NA";   //Source of the EVENT PSOC HOUSEKEEPING
 //PEHF2
 string ComLast="NA";     //Last Command
 int ComCount=-1;    //Command Count NL4130.BPD.EVENT_RK.root
 int ComErr=-1;     //Command Error Count
 int GenErr=-1;      //General Error Count
 int Go=-1;          //NUmber of eventsNL4130.BPD.EVENT_RK.root
 int Go1EPHK=-1;      //Number of missing events
 int AvgROTime=-1;   //Average Readout time in microsec
 //PEHF3
 int T1r=-1; //Single rate T1
 int T2r=-1; //Single rate T2
 int T3r=-1; //Single rate T3
 int T4r=-1; //Single rate T4
 int Gr=-1;  //Single rate Guard
 int TrCom=-1;   //Tracker Command Count
 int Tr1Pct=-1;   //Percentage of tracker trigger 1
 int Tr2Pct=-1;   //Percentage of tracker trigger 2 
 int UARTErr=-1;   //Traeventcker UART Error Count
 int UARTTim=-1;   //Tracker UART Timeout Count 
 //PEHF4
 int*NhperCh=new int[8]; 
 for (int i=0;i<8;i++)NhperCh[i]=0;
 int*Lrate=new int[8];
 for (int i=0;i<8;i++)Lrate[i]=0;
 int*Ldummy=new int[8];
 for (int i=0;i<8;i++)Ldummy[i]=-1;
 
 //Temperatures:
 float PSOCDieTemp=-99;
 float TempL0=-999;
 float TempL7=-999; 

 float*TrackStats=new float[6];
 for (int i=0;i<6;i++)TrackStats[i]=0;

 int Samples=-1; //Number of sample used to calculate PctLive
 //float PctLive=-1;//PSOC Live time percentage using N Samples between the last 2 
 float PctMaBzy=-1;
 float PctTrLive=1;
 float PctADCLive=-1;
 
 
 //PMHF1 MAIN PSOC HOUSEKEEPING 
 //PMHF1: 07/19/2022 13:29:16 Date: 07/19/2022 13:29:07 DeltaT: 5716.00 Source: FF00FF LastCmd: 0320 CountCmd: 2 ErrCmd: 0 ErrGen: 12 Missing: 0 FIFOPct: 0 Drop232: 0 DropUSB: 0 
 int yMPHK1=-1;//Year from PMHF1 line linked to the event
 int mMPHK1=-1;//Month from PMHF1 line linked to the event
 int dMPHK1=-1;//Day from PMHF1 line linked to the event
 int hMPHK1=-1;//Hour from PMHF1 line linked to the event
 int miMPHK1=-1;//Minute from PMHF1 line linked to the event 
 int sMPHK1=-1;//Second from PMHF1 line linked to the event
 int yMPHK1b=-1;//Year from PMHFb1 line linked to the event
 int mMPHK1b=-1;//Month from PMHF1b line linked to the event
 int dMPHK1b=-1;//Day from PMHF1b line linked to the event
 int hMPHK1b=-1;//Hour from PMHF1b line linked to the event
 int miMPHK1b=-1;//Minute from PMHF1b line linked to the event 
 int sMPHK1b=-1;//Second from PMHF1b line linked to the event
 float DeltaT=-999;
 string SourceMPHK="NA";
 int LastCmdMPHK=-1;
 int CountCmdMPHK=-1;
 int ErrCmdMPHK=-1;
 int ErrGenMPHK=-1;
 int MissingMPHK=-1;
 int FIFOPctMPHK=-1;
 int Drop232MPHK=-1;
 int DropUSBMPHK=-1;
    
 //PMHF2
 //PMHF2: 07/19/2022 13:29:16 BarCounts: 29028110 149972000 29255638 149731314 BarRates:  198586.8 -274361.6 -200137.7 -272696.6 400.0 0.00 400.0 0.00
 //int BarCounts[4];
 //int BarRate[4];
 float P1MPHK=-999; 
 float P2MPHK=-999; 
 float Temp1MPHK=-999; 
 float Temp2MPHK=-999; 
 //PMHF3
 //PMHF3: 07/19/2022 13:29:16 Dp: 2010065 Dt: -2099950 IntPress: 750.24 IntTemp: 42.3 BoardTemp: 43.0 DieTemp: 44.0 Analog: 3.47 147.33 3.32 91.66 5.01 840.30 5.25 4.25 15.24 3.61 2730.47 121.43 
 int yMPHK3=-1;//Year from PMHF3 line linked to the event
 int mMPHK3=-1;//Month from PMHF3 line linked to the event
 int dMPHK3=-1;//Day from PMHF3 line linked to the event
 int hMPHK3=-1;//Hour from PMHF3 line linked to the event
 int miMPHK3=-1;//Minute from PMHF3 line linked to the event 
 int sMPHK3=-1;//Second from PMHF3 line linked to the event
 int Dp=-999;
 int Dt=-999;
 float IntPress=-999;
 float IntTemp=-999;
 float BoardTemp=-999;
 float DieTemp=-999;
 float Dig3V=-999;
 float Dig3C=-999;
 float Ana3V=-999;
 float Ana3C=-999;
 float Dig5V=-999;
 float Dig5C=-999;
 float Ana5V=-999;
 float Ana5C=-999;
 float Dig15V=-999;
 float TckV=-999;
 float TckC=-999;
 float TckbiasC=-999; 
 
//Number of Layers read
 int kASI=0;
 int kEVT=0;
 int kPHA=0;
 int kPSE1=0;
 int flagGoodGo=0; 
 int NoisyClus=0;


//Start to read the file
 for (string line; getline(filestr,line);)
   {
    // if(kEvent>3) return -1;
    //Here the full line is read and stored in the string object "line"
    //if(kEvent>5) continue;

    kLine++;
    // if(kLine%1000==0)Ldummy
    //cout<< "Line " << kLine << " is read" <<endl;
    //cout<< line <<endl;

//////////////////////////////////////
/////////
//Compare the first 3 char of the line to "CT1"
///////////////////////////////////////////////

 /*   if (line.compare(0,3,"CT1",3)==0)
     {
      ///////////////////////////////////////////////
      //Extract the data from the last CT1 line
      ///////////////////////////////////////////////
      vector<string> datalineCT1;
      //Split the line
      datalineCT1=split(&line,' ');
      if((int)datalineCT1.size()!=NCT1words)
        {
         cout << "Number of words in the CT1 line is wrong : " << (int)datalineCT1.size() << " (Should be " << NCT1words  << "): "<< endl;
         cout << line <<endl;
         continue;
        }
      //Extract CT1 date
      //cout << "extract CT1 date" <<endl;
      //cout << dataline.at(1) <<endl;
      extractdate(&yCT1,&mCT1,&dCT1,&datalineCT1.at(1));
      //cout << "extract CT1 date is done" <<endl;
      //cout << "extract CT1 time" <<endl;
      extracttime(&hCT1,&miCT1,&sCT1,&datalineCT1.at(2));

      //Format from Paul's email of Feb. 8, 2018

      OnTimeCT1=s2i(&datalineCT1.at(3));MakeRawBPDEvent_503f.cxx
      LastCT1=s2i(&datalineCT1.at(4));
      CountCT1= s2i(&datalineCT1.at(5));
      Baro1T=s2f(&datalineCT1.at(8));
      Baro1P=s2f(&datalineCT1.at(9));
      Baro2T=s2f(&datalineCT1.at(10));
      Baro2P=s2f(&datalineCT1.at(11));
      GOCT1=s2f(&datalineCT1.at(14));
      coinCT1=s2f(&datalineCT1.at(15));
      PressB1=s2f(&datalineCT1.at(16));
      TempB1=s2f(&datalineCT1.at(17));
      PressB2=s2f(&datalineCT1.at(18));
      TempB2=s2f(&datalineCT1.at(19));
      TempCT1=s2f(&datalineCT1.at(20));
      Volt5VCT1=s2f(&datalineCT1.at(21));
      Volt15VCT1=s2f(&datalineCT1.at(22));
     }
 */    
///////////////////////////////////////////////
//Compare the first 3 char of the line to "CT3"
///////////////////////////////////////////////
/*
    if (line.compare(0,3,"CT3",3)==0)
     {
      ///////////////////////////////////////////////
      //Extract the data from the last CT3 line
      ///////////////////////////////////////////////
      vector<string> datalineCT3;
      //Split the line
      datalineCT3=split(&line,' ');

      if((int)datalineCT3.size()!=NCT3words)
        {
         cout << "Number of words in the CT3 line is wrong : " << (int)datalineCT3.size() << " (Should be " << NCT3words  << "): "<< endl;
         cout << line <<endl;
         continue;
        }

      //Extract CT3 date
      //cout << "extract CT3 date" <<endl;
      //cout << dataline.at(1) <<endl;
      extractdate(&yCT1,&mCT1,&dCT3,&datalineCT3.at(1));
      //cout << "extract CT3 date is done" <<endl;
      //cout << "extract CT3 time" <<endl;
      extracttime(&hCT3,&miCT3,&sCT3,&datalineCT3.at(2));

      //Format from Paul's email of Feb. 8, 2018

      OnTimeCT3=s2i(&datalineCT3.at(3));
      LastCT3=s2i(&datalineCT3.at(4));
      CountCT3= s2i(&datalineCT3.at(5));
      T1L=s2f(&datalineCT3.at(6));
      T1A=s2f(&datalineCT3.at(7));
      T2L=s2f(&datalineCT3.at(8));
      T2A=s2f(&datalineCT3.at(9));
      T3L=s2f(&datalineCT3.at(10));
      T3A=s2f(&datalineCT3.at(11));
      T4L=s2f(&datalineCT3.at(12));
      T4A=s2f(&datalineCT3.at(13));
      GRDL=s2f(&datalineCT3.at(14));
      GRDA=s2f(&datalineCT3.at(15));
      TempCT3=s2f(&datalineCT3.at(16));
      Volt5VCT3=s2f(&datalineCT3.at(17));
      Volt15VCT3=s2f(&datalineCT3.at(18));

     }
     */ 
///////////////////////////////////////////////
//Compare the first 3 char of the line to "POW" int NPMHF1words=26 ;//PMHF1 line MPIFLit 5.09u

///////////////////////////////////////////////
/*
    if (line.compare(0,3,"POW",3)==0)
     {
      ///////////////////////////////////////////////
      //Extract the data from the last POW line
      ///////////////////////////////////////////////
      vector<string> datalinePOW;
      //Split the line
      datalinePOW=split(&line,' ');

      if((int)datalinePOW.size()!=NPOWwords)
        {
         cout << "Number of words in the POW line is wrong : " << (int)datalinePOW.size() << " (Should be " << NPOWwords  << "): "<< endl;
         cout << line <<endl;
         continue;
        }

      //Extract datalinePOW date
      //cout << "extract datalinePOW date" <<endl;
      //cout << dataline.at(1) <<endl;
      extractdate(&yPOW,&miPOW,&dPOW,&datalinePOW.at(1));
      //cout << "extract POW date is done" <<endl;
      //cout << "extract POW time" <<endl;
      extracttime(&hPOW,&miPOW,&sPOW,&datalinePOW.at(2));

      //Format from Paul's email of Feb. 8, 2018

      OnTimePOW=s2i(&datalinePOW.at(3));
      MainV=s2f(&datalinePOW.at(4));
      MainC=s2f(&datalinePOW.at(5));
      HeatV=s2f(&datalinePOW.at(6));
      HeatC=s2f(&datalinePOW.at(7));
      TrackV=s2f(&datalinePOW.at(8));
      TrackC=s2f(&datalinePOW.at(9));
     }
*/
///////////////////////////////////////////////
//Compare the first 3 char of the line to "VCI"
///////////////////////////////////////////////
/*NL4130.BPD.EVENT_RK.root
    if (line.compare(0,3,"VCI",3)==0)
     {
      ///////////////////////////////////////////////
      //Extract the data from the last VCI line
      ///////////////////////////////////////////////
      vector<string> datalineVCI;
      //Split the line
      datalineVCI=split(&line,' ');

      if((int)datalineVCI.size()!=NVCIwords)
       {
        cout << "Number of words in the VCI line is wrong : " << (int)datalineVCI.size() << " (Should be " << NVCIwords  << "): "<< endl;
        cout << line <<endl;
        continue;
       }

      //Extract datalineVCI date
      //cout << "extract datalineVCI date" <<endl;
      //cout << dataline.at(1) <<endl;
      extractdate(&yVCI,&mVCI,&dVCI,&datalineVCI.at(1));
      //cout << "extract POW date is done" <<endl;
      //cout << "extract POW time" <<endl;
      extracttime(&hVCI,&miVCI,&sVCI,&datalineVCI.at(2));

      //Format from Paul's email of April 26, 2019
      for(int ijk=0;ijk<7;ijk++) LrVCI[ijk]=s2i(&datalineVCI.at(19+ijk));

     }
*/

///////////////////////////////////////////////
//Compare the first 3 char of the line to "PHA" 
///////////////////////////////////////////////
/*
    if (line.compare(0,3,"PHA",3)==0)
     {
      //cout << "In PHA line" <<endl;
      //Each PHA Line creates one event
      //If not the first PHA Line fill the previous event in the tree
      if(kEvent!=0)
       {
        int t=0;
        int tc=0;
        for (int ij=0;ij<7;ij++) t+=Titmp[ij]*(int)TMath::Power(2,ij);
        for (int ij=0;ij<7;ij++) tc+=Tictmp[ij]*(int)TMath::Power(2,ij);
        e->set_Nhnoisy(NoisyClus);
        e->set_Ti(t);
        e->set_Tic(tc);
        tree->Fill();
        //reset event
        kEVT=0;
        kASI=0;
        kPHA=0;
        flagGoodGo=0;
        NoisyClus=0;
        delete e;
       }

      //Define new event
      e=new ALEvent();
      //Increment the number of read events
      kEvent++;
      kPHA=1;
      e->set_eventnumber(kEvent);

      //Define internal tracker trigger
      Titmp=new int[7];
      for(int ij=0;ij<7;ij++)Titmp[ij]=0;
      Tictmp=new int[7];
      for(int ij=0;ij<7;ij++)Tictmp[ij]=0;
      ///////////////////////////////////////////////
      //Extract the data from the last PHA line
      ///////////////////////////////////////////////
      vector<string> datalinePHA;

      //Split the line
      datalinePHA=split(&line,' ');

      if((int)datalinePHA.size()!=NPHAwords)
        {
         cout << "Number of words in the PHA line is wrong : " << (int)datalinePHA.size() << " (Should be " << NPHAwords  << "): "<< endl;
         cout << line <<endl;
         continue;
        }
      int year=0;
      int month=0;
      int day=0;
      int hour=0;
      int minute=0;
      int second=0;

      //Extract PHA date
      year=month=day=0;
      //cout << "extract PHA date" <<endl;
      //cout << dataline.at(1) <<endl;
      extractdate(&year,&month,&day,&datalinePHA.at(1));
      //cout << "extract PHA date is done" <<endl;
      //Extract PHA time
      hour=minute=second=0;
      //cout << "extract PHA time" <<endl;
      extracttime(&hour,&minute,&second,&datalinePHA.at(2));
      //cout << "extract PHA time is done" <<endl;
      //Fill the event structure with PHA time variables
      e->set_yPHA(year);
      e->set_mPHA(month);
      e->set_dPHA(day);
      e->set_hPHA(hour);
      e->set_miPHA(minute);
      e->set_sPHA(second);
      //cout << "PHA time was added to the event" <<endl;
      //Fill the trigger information from the PHA line
      e->add_EneT1(s2lf(&datalinePHA.at(3)));
      e->add_EneT2(s2lf(&datalinePHA.at(4)));
      e->add_EneT3(s2lf(&datalinePHA.at(5)));
      e->add_EneT4(s2lf(&datalinePHA.at(6)));
      e->add_Eneg(s2lf(&datalinePHA.at(7)));
      e->add_PHA6(s2lf(&datalinePHA.at(8)));
      e->set_GoPHA(s2lf(&datalinePHA.at(9)));
      e->set_tPHA(s2lf(&datalinePHA.at(10)));


      //Set the housekeeping variables (It can be defautl value at the beginning of a run)
      //CT1
      e->set_yCT1(yCT1);
      e->set_mCT1(mCT1);
      e->set_dCT1(dCT1);
      e->set_hCT1(hCT1);
      e->set_miCT1(miCT1);
      e->set_sCT1(sCT1);
      e->set_OnTimeCT1(OnTimeCT1);
      e->set_LastCT1(LastCT1);
      e->set_CountCT1(CountCT1);
      e->set_TempCT1(TempCT1);
      e->set_Volt5VCT1(Volt5VCT1);
      e->set_Volt15VCT1(Volt15VCT1);
      e->set_Baro1T(Baro1T);
      e->set_Baro1P(Baro1P);
      e->set_Baro2T(Baro2T);
      e->set_Baro2P(Baro2P);
      e->set_GOCT1(GOCT1);
      e->set_coinCT1(coinCT1);
      e->set_PressB1(PressB1);
      e->set_TempB1(TempB1);
      e->set_PressB2(PressB2);
      e->set_TempB2(TempB2);


      //CT3
      e->set_yCT3(yCT3);
      e->set_mCT3(mCT3);
      e->set_dCT3(dCT3);
      e->set_hCT3(hCT3);
      e->set_miCT3(miCT3);
      e->set_sCT3(sCT3);
      e->set_OnTimeCT3(OnTimeCT3);
      e->set_LastCT3(LastCT3);
      e->set_CountCT3(CountCT3);
      e->set_TempCT3(TempCT3);
      e->set_Volt5VCT3(Volt5VCT3);
      e->set_Volt15VCT3(Volt15VCT3);
      e->set_T1L(T1L);
      e->set_T1A(T1A);
      e->set_T2L(T2L);
      e->set_T2A(T2A);
      e->set_T3L(T3L);
      e->set_T3A(T3A);
      e->set_T4L(T4L);
      e->set_T4A(T4A);
      e->set_GRDL(GRDL);
      e->set_GRDA(GRDA);

      //POW
      e->set_yPOW(yPOW);
      e->set_mPOW(mPOW);
      e->set_dPOW(dPOW);
      e->set_hPOW(hPOW);
      e->set_miPOW(miPOW);
      e->set_sPOW(sPOW);
      e->set_OnTimePOW(OnTimePOW);
      e->set_MainC(MainC);
      e->set_MainV(MainV);
      e->set_HeatC(HeatC);
      e->set_HeatV(HeatV);
      e->set_TrackC(TrackC);
      e->set_TrackV(TrackV);

      //VCI
      e->set_yVCI(yVCI);
      e->set_mVCI(mVCI);
      e->set_dVCI(dVCI);
      e->set_hVCI(hVCI);
      e->set_miVCI(miVCI);
      e->set_sVCI(sVCI);

      for(int ijk=0;ijk<7;ijk++)  e->set_Lrate(ijk,LrVCI[ijk]);
     
     }//end read line starting with PHA
*/
///////////////////////////////////////////////
//Compare the first 4 char of the line to "PSE1" 
///////////////////////////////////////////////
    
    if (line.compare(0,4,"PSE1",4)==0)
     {
      //cout << line <<endl;
      //MIPFLIT 5.03u
      //  0       1        2      3   4    5    6      7  8   9   10 11       12       13  14  15     16   17  18     19     20  21      22         23    24        25    26   27   28   29   30    31   32   33   34  35  36   37   38                                                                                                                                                                  
      //PSE1: 07/19/2022 13:29:18 N: 104 Code: 221 nEcho: 0 Last: 36 ZERO FirstNibble: 15 Run: 1 Trigger: 418 Stamp: 169077 Go1: 6 Date/Time: 07/19/2022 13:29:07 Status: 119 PHA0: 351 PHA1: 522 PHA2: 481 PHA3: 3 PHA4: 8 PHA5: -502
      //  0       1        2      3   4    5    6  7  8   9   10 11       12       13     14       15    16      17  18     19      20  21   22         23      24      25         26  27  28   29   30    31   32   33   34  35   36   37   38     39                                                                                                                                                                  
      //PSE1: 01/04/2022 17:01:44 N: 220 Type: 221 X: 0 Last: 75 ZERO FirstNibble: 15 ***Strange  Run: 1536 Trigger: 3022 Stamp: 629085 Go1: 3058 Date/Time: 28_01_01 01:21:39 Status: 29 PHA0: 665 PHA1: 120 PHA2: 957 PHA3: 4064 PHA4: 4076 PHA5: -60
            
      //cout << "In PSE1 line" <<endl;
      //Each PSE1 Line creates one event
      //If not the first PSE1 Line fill the previous event in the tree
      if(kEvent!=0)
       {
        int t=0;
        int tc=0;
        for (int ij=0;ij<8;ij++) t+=Titmp[ij]*(int)TMath::Power(2,ij);
        for (int ij=0;ij<8;ij++) tc+=Tictmp[ij]*(int)TMath::Power(2,ij);
        e->set_Nhnoisy(NoisyClus);
        e->set_Ti(t);
        e->set_Tic(tc);
        tree->Fill();
        //reset event
        kEVT=0;
        kASI=0;

        kPSE1=0;
        flagGoodGo=0;
        NoisyClus=0;
        for (int ijk=0;ijk<8;ijk++)Ldummy[ijk]=-1;
        delete e;
       }
      //Define new event
      e=new ALEvent();       
      //Increment the number of read events
      kEvent++;
      kPSE1=1;
      e->set_eventnumber(kEvent);
      //Define internal tracker trigger
      Titmp=new int[8];
      for(int ij=0;ij<8;ij++)Titmp[ij]=0;
      Tictmp=new int[8];
      for(int ij=0;ij<8;ij++)Tictmp[ij]=0;
      ///////////////////////////////////////////////
      //Extract the data from the last PSE1 line
      ///////////////////////////////////////////////
      vector<string> datalinePSE1;

      //Split the line
      datalinePSE1=split(&line,' ');
      if((int)datalinePSE1.size()!=NPSE1words)
        {
         cout << "Number of words in the PSE1 line is wrong : " << (int)datalinePSE1.size() << " (Should be " << NPSE1words  << "): "<< endl;
         cout << line <<endl;
         e->add_EneT1(-1);
         e->add_EneT2(-1);
         e->add_EneT3(-1);
         e->add_EneT4(-1);
         e->add_Eneg(-1);
         e->add_ToF(-1);
         continue;

        } 
              
      int year=0;
      int month=0;
      int day=0;
      int hour=0;
      int minute=0;
      int second=0;
      //flagGoodGo=1;
      e->set_runnumber(s2lf(&datalinePSE1.at(15)));

      //Extract PSE1 date
      year=month=day=0;
      //cout << "extract PHA date" <<endl;
      //cout << dataline.at(1) <<endl;
      extractdate(&year,&month,&day,&datalinePSE1.at(1));
      //cout << "extract PHA date is done" <<endl;
      //Extract PHA time
      hour=minute=second=0;
      //cout << "extract PHA time" <<endl;
      extracttime(&hour,&minute,&second,&datalinePSE1.at(2));
      //cout << "extract PHA time is done" <<endl;
      //Fill the event structure with PHA time variables
      e->set_yPSE1(year);
      e->set_mPSE1(month);
      e->set_dPSE1(day);
      e->set_hPSE1(hour);
      e->set_miPSE1(minute);
      e->set_sPSE1(second);
      
      //Extract PSE1 date
      year=month=day=0;
      extractdate(&year,&month,&day,&datalinePSE1.at(23));
      //Extract PHA time
      hour=minute=second=0;
      extracttime(&hour,&minute,&second,&datalinePSE1.at(24));
      e->set_yPSE1b(year);
      e->set_mPSE1b(month);
      e->set_dPSE1b(day);
      e->set_hPSE1b(hour);
      e->set_miPSE1b(minute);
      e->set_sPSE1b(second);
      //  0       1        2      3   4    5    6      7  8   9   10 11       12       13  14  15     16   17  18     19     20  21      22         23    24        25    26   27   28   29   30    31   32   33   34  35  36   37   38                                                                                                                                                                  
      //PSE1: 07/19/2022 13:29:18 N: 104 Code: 221 nEcho: 0 Last: 36 ZERO FirstNibble: 15 Run: 1 Trigger: 418 Stamp: 169077 Go1: 6 Date/Time: 07/19/2022 13:29:07 Status: 119 PHA0: 351 PHA1: 522 PHA2: 481 PHA3: 3 PHA4: 8 PHA5: -502
      e->set_Status(unsigned(s2i(&datalinePSE1.at(26))));
      e->add_EneT1(s2lf(&datalinePSE1.at(28)));
      e->add_EneT2(s2lf(&datalinePSE1.at(30)));
      e->add_EneT3(s2lf(&datalinePSE1.at(32)));
      e->add_EneT4(s2lf(&datalinePSE1.at(34)));
      e->add_Eneg(s2lf(&datalinePSE1.at(36)));
      e->add_ToF(s2lf(&datalinePSE1.at(38)));
      e->set_Go1(s2lf(&datalinePSE1.at(21)));
      e->set_Stamp(s2lf(&datalinePSE1.at(19)));
      e->set_N(s2lf(&datalinePSE1.at(4)));//N: 92
      e->set_Code(s2lf(&datalinePSE1.at(6)));//Code: 221
      e->set_nEcho(s2lf(&datalinePSE1.at(8)));//nEcho: 0
      e->set_Last(s2lf(&datalinePSE1.at(10)));//Last: 32
      e->set_FirstNibble(s2lf(&datalinePSE1.at(13)));//ZERO FirstNibble: 15
      e->set_Trigger(s2lf(&datalinePSE1.at(17)));//triggered event number in run runnumber

      //Set the housekeeping variables (It can be defautl value at the beginning of a run)
      //cout << "Date PEHF1: " << yPEHF1 <<"/"<< mPEHF1 << "/" << dPEHF1  << endl;
      //cout << "T1r: " <<T1r << endl;
      e->set_yEPHK1(yEPHK1);
      e->set_mEPHK1(mEPHK1);
      e->set_dEPHK1(dEPHK1);
      e->set_hEPHK1(hEPHK1);
      e->set_miEPHK1(miEPHK1);
      e->set_sEPHK1(sEPHK1);
      
      e->set_yEPHK1b(yEPHK1b);
      e->set_mEPHK1b(mEPHK1b);
      e->set_dEPHK1b(dEPHK1b);
      e->set_hEPHK1b(hEPHK1b);
      e->set_miEPHK1b(miEPHK1b);
      e->set_sEPHK1b(sEPHK1b);   

      e->set_yEPHK4(yEPHK4);
      e->set_mEPHK4(mEPHK4);
      e->set_dEPHK4(dEPHK4);
      e->set_hEPHK4(hEPHK4);
      e->set_miEPHK4(miEPHK4);
      e->set_sEPHK4(sEPHK4);   
      
      //PEHF1
      e->set_RunEPHK(RunEPHK); 
      //e->set_RunEHF(32); 
      e->set_SourceEPHK(SourceEPHK);
      //PEHF2
      e->set_ComLast(ComLast);   
      e->set_ComCount(ComCount);
      e->set_ComErr(ComErr);
      e->set_GenErr(GenErr);
      e->set_Go(Go);
      e->set_Go1EPHK(Go1EPHK);
      e->set_AvgROTime(AvgROTime);
      //PEHF3
      e->set_T1r(T1r);
      e->set_T2r(T2r);
      e->set_T3r(T3r);
      e->set_T4r(T4r);
      e->set_Gr(Gr);
      e->set_TrCom(TrCom);
      e->set_Tr1Pct(Tr1Pct);
      e->set_Tr2Pct(Tr2Pct);
      e->set_UARTErr(UARTErr);
      e->set_UARTTim(UARTTim);
      //PEHF4
      for(int ijk=0;ijk<8;ijk++)  e->set_NhperCh(ijk,NhperCh[ijk]);
      for(int ijk=0;ijk<8;ijk++)  e->set_Lrate(ijk,Lrate[ijk]);
      e->set_PSOCDieTemp(PSOCDieTemp);
      e->set_TempL0(TempL0);
      e->set_TempL7(TempL7);
      for(int ijk=0;ijk<6;ijk++)  e->set_TrackStats(ijk,TrackStats[ijk]);
      e->set_Samples(Samples);
      e->set_PctMaBzy(PctMaBzy);
      e->set_PctTrLive(PctTrLive);
      e->set_PctADCLive(PctADCLive);
      
      e->set_yMPHK1(yMPHK1);
      e->set_mMPHK1(mMPHK1);
      e->set_dMPHK1(dMPHK1);
      e->set_hMPHK1(hMPHK1);
      e->set_miMPHK1(miMPHK1);
      e->set_sMPHK1(sMPHK1);
      
      e->set_yMPHK1b(yMPHK1b);
      e->set_mMPHK1b(mMPHK1b);
      e->set_dMPHK1b(dMPHK1b);
      e->set_hMPHK1b(hMPHK1b);
      e->set_miMPHK1b(miMPHK1b);
      e->set_sMPHK1b(sMPHK1b);   

      e->set_yMPHK3(yMPHK3);
      e->set_mMPHK3(mMPHK3);
      e->set_dMPHK3(dMPHK3);
      e->set_hMPHK3(hMPHK3);
      e->set_miMPHK3(miMPHK3);
      e->set_sMPHK3(sMPHK3); 

      e->set_DeltaT(DeltaT);
      e->set_SourceEPHK(SourceEPHK);
      e->set_LastCmdMPHK(LastCmdMPHK);
      e->set_CountCmdMPHK(CountCmdMPHK);
      e->set_ErrCmdMPHK(ErrCmdMPHK);
      e->set_ErrGenMPHK(ErrGenMPHK);
      e->set_MissingMPHK(MissingMPHK);
      e->set_FIFOPctMPHK(FIFOPctMPHK);
      e->set_Drop232MPHK(Drop232MPHK);
      e->set_DropUSBMPHK(DropUSBMPHK); 
      
      e->set_P1MPHK(P1MPHK); 
      e->set_P2MPHK(P2MPHK); 
      e->set_Temp1MPHK(Temp1MPHK); 
      e->set_Temp2MPHK(Temp2MPHK); 

      e->set_Dp(Dp);
      e->set_Dt(Dt);
      e->set_IntPress(IntPress);
      e->set_IntTemp(IntTemp);
      e->set_BoardTemp(BoardTemp);
      e->set_DieTemp(DieTemp);
      e->set_Dig3V(Dig3V);
      e->set_Dig3C(Dig3C);
      e->set_Ana3V(Ana3V);
      e->set_Ana3C(Ana3C);
      e->set_Dig5V(Dig5V);
      e->set_Dig5C(Dig5C);
      e->set_Ana5V(Ana5V);
      e->set_Ana5C(Ana5C);
      e->set_Dig15V(Dig15V);
      e->set_TckV(TckV);
      e->set_TckC(TckC);
      e->set_TckbiasC(TckbiasC); 
      
      //ASI
      for(int ijk=0;ijk<8;ijk++)  e->set_Ldummy(ijk,Ldummy[ijk]);

      
      /*
      //CT1
      e->set_yCT1(yCT1);

      e->set_mCT1(mCT1);
      e->set_dCT1(dCT1);
      e->set_hCT1(hCT1);
      e->set_miCT1(miCT1);
      e->set_sCT1(sCT1);
      e->set_OnTimeCT1(OnTimeCT1);
      e->set_LastCT1(LastCT1);
      e->set_CountCT1(CountCT1);     

      e->set_TempCT1(TempCT1);
      e->set_Volt5VCT1(Volt5VCT1);
      e->set_Volt15VCT1(Volt15VCT1);
      e->set_Baro1T(Baro1T);
      e->set_Baro1P(Baro1P);float
      e->set_Baro2T(Baro2T);&MPHK1
      e->set_Baro2P(Baro2P);
      e->set_GOCT1(GOCT1);
      e->set_coinCT1(coinCT1);
      e->set_PressB1(PressB1);
      e->set_TempB1(TempB1);
      e->set_PressB2(PressB2);
      e->set_TempB2(TempB2);


      //CT3
      e->set_yCT3(yCT3);
      e->set_mCT3(mCT3);
      e->set_dCT3(dCT3);
      e->set_hCT3(hCT3);
      e->set_miCT3(miCT3);
      e->set_sCT3(sCT3);
      e->set_OnTimeCT3(OnTimeCT3);
      e->set_LastCT3(LastCT3);
      e->set_CountCT3(CountCT3);
      e->set_TempCT3(TempCT3);
      e->set_Volt5VCT3(Volt5VCT3);
      e->set_Volt15VCT3(Volt15VCT3);
      e->set_T1L(T1L);
      e->set_T1A(T1A);
      e->set_T2L(T2L);
      e->set_T2A(T2A);
      e->set_T3L(T3L);
      e->set_T3A(T3A); e=new ALEvent();
      ee->set_P1MPHK(P1MPHK); 
      e->set_P2MPHK(P1MPHK); &MPHK1
      e->set_Temp1MPHK(P1MPHK); 
      e->set_Temp2MPHK(P1MPHK); 
      ->set_T4L(T4L);  
      e->set_T4A(T4A);
      e->set_GRDL(GRDL);
      e->set_GRDA(GRDA);

      //POW
      e->set_yPOW(yPOW);
      e->set_mPOW(mPOW);
      e->set_dPOW(dPOW);
      e->set_hPOW(hPOW);
      e->set_miPOW(miPOW);
      e->set_sPOW(sPOW);
      e->set_OnTimePOW(OnTimePOW);

      e->set_MainC(MainC);
      e->set_MainV(MainV);
      e->set_HeatC(HeatC);
      e->set_HeatV(HeatV);
      e->set_TrackC(TrackC);
      e->set_TrackV(Track e=new ALEvent();V);

      //VCI
      e->set_yVCI(yVCI);
      e->set_mVCI(mVCI);
      e->set_dVCI(dVCI);
      e->set_hVCI(hVCI);
      e->set_miVCI(miVCI);
      e->set_sVCI(sVCI);
      
      for(int ijk=0;ijk<8;ijk++)  e->set_Lrate(ijk,LrVCI[ijk]);
      */
      
     }//end read line starting with PSE1

     
///////////////////////////////////////////////
//Compare the first 4 char of the line to "PSE2" 
///////////////////////////////////////////////

    if (line.compare(0,4,"PSE2",4)==0)
     {
      //MIPFLIT 5.03u
      //    0         1        2        3       4      5        6   7       8    9       10   11      12     13       14    15
      //PSE2: 07/19/2022 13:29:18 sTraxTrig: 01A2 TraxTrig: 418 TraxComm: 9 TraxPatt: 215 TotalTrax: 8 TotalBytes: 82110 FINI
      ///////////////////////////////////////////////
      //Extract the data from the last VCI line
      ///////////////////////////////////////////////
      if(kPSE1!=1)continue;
      vector<string> datalinePSE2;
      //Split the line
      datalinePSE2=split(&line,' ');

      if((int)datalinePSE2.size()!=NPSE2words)
       {
        cout << "Number of words in the PSE2 line is wrong : " << (int)datalinePSE2.size() << " (Should be " << NPSE2words  << "): "<< endl;
        cout << line <<endl;
        continue;

       }
      int year=0;
      int month=0;
      int day=0;
      int hour=0;
      int minute=0;
      int second=0;
      extractdate(&year,&month,&day,&datalinePSE2.at(1));
      hour=minute=second=0;
      extracttime(&hour,&minute,&second,&datalinePSE2.at(2));

      e->set_yPSE2(year);
      e->set_mPSE2(month);
      e->set_dPSE2(day);
      e->set_hPSE2(hour);
      e->set_miPSE2(minute);
      e->set_sPSE2(second);
      
     }//end read line starting with PSE1
     
     
///////////////////////////////////////////////
//Compare the first 3 char of the line to "EVT"
///////////////////////////////////////////////
/*    if (line.compare(0,3,"EVT",3)==0)
     {
     // cout << "In EVT line" <<endl;

      //An EVT line is always associated to the previous PHA line
      //If several EVT lines follow one PHA line then the last EVT line is recorded
      ///////////////////////////////////////////////
      //Extract the data from the EVT line
      ///////////////////////////////////////////////
      vector<string> datalineEVT;
      kEVT++;
      //Split the line
      datalineEVT=split(&line,' ');
      double oldGo=prevGo;
      string oldline=prevEVTline;
      prevEVTline=line;
      if((int)datalineEVT.size()!=NEVTwords)
       {
        cout << "Number of words in the EVT line is wrong : " << (int)datalineEVT.size() << " (Should be " << NEVTwords  << "): "<< endl;
        cout << line <<endl;
       }

       if(EVTLength==1)
        {
         prevGo=s2lf(&datalineEVT.at(11));
        }
       if(EVTLength==2)
        {
         prevGo=s2lf(&datalineEVT.at(13));
        }

     // if(prevGo!=(oldGo+1))continue;
      flagGoodGo=1;
      //cout << oldline << endl;
     // cout << line <<endl;
      //cout << "Line: "<< kLine<<", oldGO=" << oldGo << ", prevGo=" <<prevGo<<endl;

      if(kPHA!=1)continue;
      if(kEVT!=1) {continue;} //Does not fill if the EVT line doesnt follow directly a PHA line

      int year=0;
      int month=0;
      int day=0;
      int hour=0;
      int minute=0;
      int second=0;
      //Extract EVT date
      //cout << "extract EVT date" <<endl;
      //cout << dataline.at(1) <<endl;
      extractdate(&year,&month,&day,&datalineEVT.at(1));
      //cout << "extract EVT date is done" <<endl;
      //Extract PHA time
      hour=minute=second=0;
      //cout << "extract EVT time" <<endl;
      extracttime(&hour,&minute,&second,&datalineEVT.at(2));

      //cout << "extract EVT time is done" <<endl;
      //Fill the event structure with EVT time variables
      e->set_yEVT(year);
      e->set_mEVT(month);
      e->set_dEVT(day);
      e->set_hEVT(hour);
      e->set_miEVT(minute);
      e->set_sEVT(second);
      //cout << "EVT time was added to the event" <<endl;
      //Fill data
      e->set_EVT(datalineEVT.at(3));
      if(EVTLength==1)
       {
        e->set_GoEVT(s2lf(&datalineEVT.at(11)));
        e->set_tEVT(s2lf(&datalineEVT.at(13)));
       }
      if(EVTLength==2)
       {
        e->set_nHitLEVT(s2i(&datalineEVT.at(5)));
        e->set_CCEVT(s2i(&datalineEVT.at(7)));
        e->set_PatternEVT(s2i(&datalineEVT.at(9)));
        e->set_Q1EVT(s2i(&datalineEVT.at(11)));
        e->set_GoEVT(s2lf(&datalineEVT.at(13)));
        e->set_tEVT(s2lf(&datalineEVT.at(15)));
        e->set_TrigEVT(s2lf(&datalineEVT.at(17)));
       }
        //cout << "GoEVT "<<s2f(&datalineEVT.at(11)) << endl;
      // cout << "EVT data was added to the event" <<endl;
     }//end read line starting with EVT
*/
     

///////////////////////////////////////////////
//Compare the first 3 char of the line to "ASI"
///////////////////////////////////////////////
    if (line.compare(0,4,"ASI:",4)==0)
     {
      //cout << "In ASI line" <<endl;
      if (kASI==8) continue;//Skip the ASI lines after 8 lines
      //Define vector of string "dataline"
      //The vector will contains the words of the line
      vector<string> dataline;
      dataline=split(&line,' '); //split the line in a vector of words
      kASI++;
      if((int)dataline.size()!=NASIwords)
       {
        cout << "Number of words in the ASI line is wrong : " << (int)dataline.size() << " (Should be " << NASIwords  << "): "<< endl;
        cout << line <<endl;
        return -1;
       }
      
      //cout << line <<endl;
      //cout <<kPSE1<< endl;
      if(kPSE1!=1)continue;
      //cout <<'Before flagGoodGo'<< endl;

      //if(flagGoodGo==0) continue;
      //cout << "after  flagGoodGo" <<endl;
      //Extract ASI date
      int yearASI=0;
      int monthASI=0;
      int dayASI=0;
      //cout << "extract ASI date" <<endl;
      //cout << dataline.at(1) <<endl;
      extractdate(&yearASI,&monthASI,&dayASI,&dataline.at(1));
      //cout << "extract ASI date is done" <<endl;
      //Extract ASI time
      int hourASI=0;
      int minuteASI=0;
      int secondASI=0;
      //cout << "extract ASI time" <<endl;
      extracttime(&hourASI,&minuteASI,&secondASI,&dataline.at(2));
      //cout << "extract ASI time is done" <<endl;
      int tmpNoisyClus=0;

      int ilay=-1; 
      //Decode ASIC code
      if(ASILength==0)DecodeASIShort(dataline.at(3),&Hh,Titmp);
      if(ASILength==1)DecodeASILong(dataline.at(3),&Hh,Titmp,Tictmp,&tmpNoisyClus,&ilay);

      if(ilay!=-1) Ldummy[ilay]=s2i(&dataline.at(4));
      
      for(int ij=0;ij<(int)Hh.size();ij++)
        {
         //e->set_L(Hh.at(ij)->getL(),dataline.at(3));
         e->set_flagL(Hh.at(ij)->get_L(),1);
         Hh.at(ij)->set_year(yearASI);
         Hh.at(ij)->set_m(monthASI);
         Hh.at(ij)->set_d(dayASI);
         Hh.at(ij)->set_hour(hourASI);
         Hh.at(ij)->set_mi(minuteASI);
         Hh.at(ij)->set_s(minuteASI);
         e->add_hit(Hh.at(ij));
        }
      NoisyClus+=tmpNoisyClus;


      //Clear hits
      Hh.clear();
     }//end read line starting with ASI

///////////////////////////////////////////////
//Compare the first 5 char of the line  "PEHF1" 
///////////////////////////////////////////////     &MPHK1
    if (line.compare(0,5,"PEHF1",5)==0|| line.compare(0,5,"PEHL1",5)==0)
     {
      //MIPFLIT 5.03u
      //    0         1        2        3       4         5      6   7    8      9   
      // PEHF1: 07/19/2022 13:29:16   Date: 07/19/2022 13:29:06 Run: 1 Source: FF00FF
      ///////////////////////////////////////////////
      //Extract the data from the last PEHF1 line
      ///////////////////////////////////////////////
      vector<string> datalinePEHF1;
      //Split the line
      datalinePEHF1=split(&line,' ');
      //cout << "in PEHF1: " << (int)datalinePEHF1.size() << endl;
      
      if((int)datalinePEHF1.size()!=NPEHF1words)
       {
        cout << "Number of words in the PEHF1 line is wrong : " << (int)datalinePEHF1.size() << " (Should be " << NPEHF1words  << "): "<< endl;
        cout << line <<endl;
        continue;
       }
      
      yEPHK1=mEPHK1=dEPHK1=0;
      extractdate(&yEPHK1,&mEPHK1,&dEPHK1,&datalinePEHF1.at(1));
      hEPHK1=miEPHK1=sEPHK1=0;
      extracttime(&hEPHK1,&miEPHK1,&sEPHK1,&datalinePEHF1.at(2));
      yEPHK1b=mEPHK1b=dEPHK1b=0;
      extractdate(&yEPHK1b,&mEPHK1b,&dEPHK1b,&datalinePEHF1.at(4));
      hEPHK1b=miEPHK1b=sEPHK1b=0;
      extracttime(&hEPHK1b,&miEPHK1b,&sEPHK1b,&datalinePEHF1.at(5));      
      RunEPHK=s2i(&datalinePEHF1.at(7));
      SourceEPHK=   datalinePEHF1.at(9);
   
      //cout << "end of PHEF1" <<endl;   
    }
///////////////////////////////////////////////
//Compare the first 5 char of the line to "PEHF2" 
///////////////////////////////////////////////     
    if (line.compare(0,5,"PEHF2",5)==0 || line.compare(0,5,"PEHL2",5)==0 )
     {
      //MIPFLIT 5.03u
      //   0         1         2     3       4      5       6    7     8    9   10 11  12  13   14  15       16 
      //PEHF2: 07/19/2022 13:29:16 ComLast: 0320 ComCount: 162 ComErr: 0 GenErr: 1 Go: 417 Go1: 6 AvgROTime: 243
      
      vector<string> datalinePEHF2;
      //Split the line
      datalinePEHF2=split(&line,' '); 
      //cout << "in PEHF2: " << (int)datalinePEHF2.size() << endl;

      if((int)datalinePEHF2.size()!=NPEHF2words)
       {
        cout << "Number of words in the PEHF2 line is wrong : " << (int)datalinePEHF2.size() << " (Should be " << NPEHF2words  << "): "<< endl;
        cout << line <<endl;
        continue;
       }
      
      ComLast= datalinePEHF2.at(4);     //Last Command
      ComCount=s2i(&datalinePEHF2.at(6));    //Command Count 
      ComErr=s2i(&datalinePEHF2.at(8));     //Command Error Count
      GenErr=s2i(&datalinePEHF2.at(10));      //General Error Count
      Go=s2i(&datalinePEHF2.at(12));          //NUmber of events
      Go1EPHK=s2i(&datalinePEHF2.at(14));      //Number of missing events
      AvgROTime=s2i(&datalinePEHF2.at(16));   //Average Readout time in microsec
     }   
///////////////////////////////////////////////
//Compare the first 5 char of the line to "PEHF3" 
///////////////////////////////////////////////     
    if (line.compare(0,5,"PEHF3",5)==0|| line.compare(0,5,"PEHL3",5)==0)
     {
      //MIPFLIT 5.03u
      //   0         1         2     3      4   5   6  7  8    9   10  11      12   13    14  15     16   17     18
      //PEHF3: 07/19/2022 13:29:16 Rates:  20 2243 10 72 23 TrCom: 255 Tr1Pct: 63 Tr2Pct: 29 UARTErr: 0 UARTTim: 0

      vector<string> datalinePEHF3;
      //Split the line
      datalinePEHF3=split(&line,' '); 
      //cout << "in PEHF3: " << (int)datalinePEHF3.size() << endl;

      if((int)datalinePEHF3.size()!=NPEHF3words)
       {
        cout << "Number of words in the PEHF3 line is wrong : " << (int)datalinePEHF3.size() << "(Should be " << NPEHF3words  << "): "<< endl;
        cout << line <<endl;
        continue;
       }         
      T1r=s2i(&datalinePEHF3.at(4)); 
      T2r=s2i(&datalinePEHF3.at(5)); 
      T3r=s2i(&datalinePEHF3.at(6));
      T4r=s2i(&datalinePEHF3.at(7));
      Gr=s2i(&datalinePEHF3.at(8));  
      TrCom=s2i(&datalinePEHF3.at(10));  
      Tr1Pct=s2i(&datalinePEHF3.at(12)); 
      Tr2Pct=s2i(&datalinePEHF3.at(14));  
      UARTErr=s2i(&datalinePEHF3.at(16));   
      UARTTim=s2i(&datalinePEHF3.at(18));  
  
     }
///////////////////////////////////////////////
//Compare the first 5 char of the line to "PEHF4" 
///////////////////////////////////////////////     
    if (line.compare(0,5,"PEHF4",5)==0|| line.compare(0,5,"PEHL4",5)==0)
     {
      //MIPFLIT 5.10n
      //    0        1        2      3     4 5 6 7 8 9 10 11  12     13 14 15  16 17 18 19 20 21     22   23   24      25      26272829  30        31   32       33      34    35      36        37
      //PEHF4: 11/10/2023 19:22:54 Chips:  7 7 7 6 6 5 5 5 OrRates:  15 341 179 119 4 6 7 7 Temps:  35.0 24.5 22.1 TrackStats:  0 0 0 0 PctMaBzy: 0.0 PctTrLive: 0.0 Samples: 39352 PctADCLive: 99.0
      ///////////////////////////////////////////////
      //Extract the data from the last PEHF1 line
      ///////////////////////////////////////////////
      vector<string> datalinePEHF4;
      //Split the line
      datalinePEHF4=split(&line,' ');
      //cout << "in PEHF4: " << (int)datalinePEHF4.size() << endl;

      if((int)datalinePEHF4.size()!=NPEHF4words)
       {
        cout << "Number of words in the PEHF4 line is wrong : " << (int)datalinePEHF4.size() << " (Should be " << NPEHF4words  << "): "<< endl;
        cout << line <<endl;
        continue;
       }
      yEPHK4=mEPHK4=dEPHK4=0;
      extractdate(&yEPHK4,&mEPHK4,&dEPHK4,&datalinePEHF4.at(1));
      hEPHK4=miEPHK4=sEPHK4=0;
      extracttime(&hEPHK4,&miEPHK4,&sEPHK4,&datalinePEHF4.at(2));
       
      for (int ijk=0;ijk<8;ijk++)NhperCh[ijk]=s2i(&datalinePEHF4.at(4+ijk));
      for (int ijk=0;ijk<8;ijk++)Lrate[ijk]=s2i(&datalinePEHF4.at(13+ijk));

      //Temperatures:
      PSOCDieTemp=s2lf(&datalinePEHF4.at(22));
      TempL0=s2lf(&datalinePEHF4.at(23));
      TempL7=s2lf(&datalinePEHF4.at(24)); 

      for (int ijk=0;ijk<4;ijk++)TrackStats[ijk]=s2lf(&datalinePEHF4.at(26+ijk));

      Samples=s2i(&datalinePEHF4.at(35)); 
      PctMaBzy=s2lf(&datalinePEHF4.at(31));
      PctTrLive=s2lf(&datalinePEHF4.at(33));
      PctADCLive=s2lf(&datalinePEHF4.at(37));
  
     }     

///////////////////////////////////////////////
//Compare the first 5 char of the line to "PMHF1" 
///////////////////////////////////////////////     
    if (line.compare(0,5,"PMHF1",5)==0)
     {
      //MIPFLIT 5.03u
      //    0         1        2     3       4         5      6        7        8     9        10     11    12      13    14  15   16    17     18  19     20  21    22    23   24    25 
      //PMHL1: 07/19/2022 14:24:23 Date: 07/19/2022 14:23:37 DeltaT: 9126.00 Source: LoRate LastCmd: 0320 CountCmd: 36 ErrCmd: 0 ErrGen: 46 Missing: 0 FIFOPct: 0 Drop232: 0 DropUSB: 0 
      ///////////////////////////////////////////////
      //Extract the data from the last PEHF1 line
      ///////////////////////////////////////////////&MPHK1
      vector<string> datalinePMHF1;
      //Split the line
      datalinePMHF1=split(&line,' ');
      //cout << "in PMHF1: " << (int)datalinePMHF1.size() << endl;
      
      if((int)datalinePMHF1.size()!=NPMHF1words && (int)datalinePMHF1.size()!=NPMHF1words+1)
       {
        cout << "Number of words in the PEHF1 line is wrong : " << (int)datalinePMHF1.size() << " (Should be " << NPMHF1words  << "): "<< endl;
        cout << line <<endl;
        continue;
       }
      
      yMPHK1=mMPHK1=dMPHK1=0;
      extractdate(&yMPHK1,&mMPHK1,&dMPHK1,&datalinePMHF1.at(1));
      hMPHK1=miMPHK1=sMPHK1=0;
      extracttime(&hMPHK1,&miMPHK1,&sMPHK1,&datalinePMHF1.at(2));
      yMPHK1b=mMPHK1b=dMPHK1b=0;
      extractdate(&yMPHK1b,&mMPHK1b,&dMPHK1b,&datalinePMHF1.at(4));
      hMPHK1b=miMPHK1b=sMPHK1b=0;
      extracttime(&hMPHK1b,&miMPHK1b,&sMPHK1b,&datalinePMHF1.at(5));      
      DeltaT=s2lf(&datalinePMHF1.at(7));
      SourceEPHK=   datalinePMHF1.at(9);
      LastCmdMPHK=s2i(&datalinePMHF1.at(11));
      CountCmdMPHK=s2i(&datalinePMHF1.at(13));
      ErrCmdMPHK=s2i(&datalinePMHF1.at(15));
      ErrGenMPHK=s2i(&datalinePMHF1.at(17));
      MissingMPHK=s2i(&datalinePMHF1.at(19));
      FIFOPctMPHK=s2i(&datalinePMHF1.at(21));
      Drop232MPHK=s2i(&datalinePMHF1.at(23));
      DropUSBMPHK=s2i(&datalinePMHF1.at(25));
    }     
///////////////////////////////////////////////
//Compare the first 5 char of the line to "PMHF2" 
///////////////////////////////////////////////     
    if (line.compare(0,5,"PMHF2",5)==0)
     {
      //MIPFLIT 5.03u 
      //    0         1        2      3           4         5           6        7        8         9        10     11       12      13    14      15    16
      //PMHF2: 07/19/2022 14:23:39 BarCounts: 136696868 706309924 137766248 705174808 BarRates:  32977.4 170411.4 33235.2 170137.8 750.11 28.52 750.10 28.86
      ///////////////////////////////////////////////
      //Extract the data from the last PEHF3 line
      ///////////////////////////////////////////////
      vector<string> datalinePMHF2;
      //Split the line
      datalinePMHF2=split(&line,' ');
      if((int)datalinePMHF2.size()!=NPMHF2words&& (int)datalinePMHF2.size()!=NPMHF2words+1)
       {
        cout << "Number of words in the PEHF2 line is wrong : " << (int)datalinePMHF2.size() << " (Should be " << NPMHF2words  << "): "<< endl;
        cout << line <<endl;
        continue;
       }
       
      P1MPHK=s2lf(&datalinePMHF2.at(13)); 
      P2MPHK=s2lf(&datalinePMHF2.at(15)); 
      Temp1MPHK=s2lf(&datalinePMHF2.at(14)); 
      Temp2MPHK=s2lf(&datalinePMHF2.at(16)); 
      

    }     
///////////////////////////////////////////////
//Compare the first 5 char of the line to "PMHF3" 
///////////////////////////////////////////////     
    if (line.compare(0,5,"PMHF3",5)==0)
     {
      //MIPFLIT 5.03u
      //    0         1        2    3     4    5      6        7        8     9        10     11      12      13    14        15     16    17    18    19   20    21    22   23   24    25    26      27 
      //PMHF3: 07/19/2022 14:23:39 Dp: 1987350 Dt: -2334944 IntPress: 750.18 IntTemp: 48.0 BoardTemp: 48.5 DieTemp: 49.0    Analog: 3.47 147.08 3.32 92.41 5.01 859.30 5.26 4.33 15.25 3.60 2730.47 121.43 
      //    0         1        2    3     4    5      6        7        8     9        10     11      12      13    14        15     16    17    18    19      20    21       22    23     24    25    26      27         
      //PMHL3: 07/19/2022 14:36:15 Dp: -6865998 Dt: -6005838 IntPress: 0.00 IntTemp: 100.0 BoardTemp: 66.0 DieTemp: 45847.0 Analog: 24.22 84.91 56.32 1614.69 81.76 1622.85 22.13 2845.05 46.53 37.07 4256.33 604.57 

         ///////////////////////////////////////////////
      //Extract the data from the last PMHF3 line
      ///////////////////////////////////////////////
      vector<string> datalinePMHF3;
      //Split the line
      datalinePMHF3=split(&line,' ');
      if((int)datalinePMHF3.size()!=NPMHF2words && (int)datalinePMHF3.size()!=NPMHF3words+1)
       {
        cout << "Number of words in the PEHF3 line is wrong : " << (int)datalinePMHF3.size() << " (Should be " << NPMHF3words  << "): "<< endl;
        cout << line <<endl;
        continue;
       }
      
      yMPHK3=mMPHK3=dMPHK3=0;
      extractdate(&yMPHK3,&mMPHK3,&dMPHK3,&datalinePMHF3.at(1));
      hMPHK3=miMPHK3=sMPHK3=0;
      extracttime(&hMPHK3,&miMPHK3,&sMPHK3,&datalinePMHF3.at(2));
      Dp=s2lf(&datalinePMHF3.at(4));
      Dt=s2lf(&datalinePMHF3.at(6));
      IntPress=s2lf(&datalinePMHF3.at(8));
      IntTemp=s2lf(&datalinePMHF3.at(10));
      BoardTemp=s2lf(&datalinePMHF3.at(12));
      DieTemp=s2lf(&datalinePMHF3.at(14));
      Dig3V=s2lf(&datalinePMHF3.at(16));
      Dig3C=s2lf(&datalinePMHF3.at(17));
      Ana3V=s2lf(&datalinePMHF3.at(18));
      Ana3C=s2lf(&datalinePMHF3.at(19));
      Dig5V=s2lf(&datalinePMHF3.at(20));
      Dig5C=s2lf(&datalinePMHF3.at(21));
      Ana5V=s2lf(&datalinePMHF3.at(22));
      Ana5C=s2lf(&datalinePMHF3.at(23));
      Dig15V=s2lf(&datalinePMHF3.at(24));
      TckV=s2lf(&datalinePMHF3.at(25));
      TckC=s2lf(&datalinePMHF3.at(26));
      TckbiasC=s2lf(&datalinePMHF3.at(27)); 
      
      
    }     
     
   }//end read file


 //Fill last event
 int t=0;
 int tc=0;
 for (int ij=0;ij<8;ij++) t+=Titmp[ij]*(int)TMath::Power(2,ij);
 for (int ij=0;ij<8;ij++) tc+=Tictmp[ij]*(int)TMath::Power(2,ij);
 e->set_Nhnoisy(NoisyClus);
 e->set_Ti(t);
 e->set_Tic(tc);
 tree->Fill();
 //reset event
 delete e;


 //Write tree in output file
 tree->Write(0,TObject::kOverwrite);

 //Close the filefloat
 filestr.close();
 cout << "The file "<<filename  << " is closed"<< endl;
 fileout->Close();
 cout << "The output file "<<Form("%s.root",input.at(0).c_str())  << " is closed"<< endl;

 return 0;
}





//////////////////////////////////////////////////////////////////////////////////////////
//Decode the hexadecimal ASI data
//////////////////////////////////////////////////////////////////////////////////////////

int DecodeASIShort(string data,vector<ALTckhit*>* Hh,int*Ti)
{

//For data of August 10, 2017

//Get string length

 int datalength=data.length();
 //Check the number of character
 //It must be 5 + a multiple of 3
 //The last character is always a " " so we remove 1 to the datalength
//cout <<endl;
 //cout << "ASI Data length " << data.length();
 //cout << " ASI Data: " << data <<endl;
 if((datalength-5)%3!=0)
  {
   cout << "The length of the data string does not pass the requirement: (datalength-5)%3==0 : Length=" <<datalength <<endl;
   cout << data <<endl;
   //for(int i=0;i<data.size();i++)
   //    cout << data[i]<<endl;
   cout << "No hit is added"<< endl;
   return 0;
  }

///////////////////////////////////////
//The first 5 digits have a static format
///////////////////////////////////////
//Read the first 2 digits: 1 byte (8 bits)
//They corresponds to the FPGA address of the layer

 string FPGAadd=data.substr(0,2);
 int LL=0;
 int L=0;
 LL=stoi(FPGAadd,0,16);
//Convert FPGA address to Layer number from 1 to 7
 switch(LL)
  {
   case 8: L=0;break;
   case 1: L=1;break;
   case 2: L=2;break;
   case 3: L=3;break;
   case 4: L=4;break;
   case 5: L=5;break;
   case 6: L=6;break;
  }//switch
 // cout << "Layer: " << L <<endl;

//Read the 3rd and 4th digit: 1 byte (8 bits)
//From left to right
//Event tag first part: 5 bits: clock counter running in the trackerboard FPGA
//The counters are synched at 0 when a reset/synch signal is received by the FPGA.
//Event tag second part: 2 bits: ASIC trigger tag
//Error flag: 1 bit: is set to 1 in case of trigger tag mismatch

 string Eventtag=data.substr(2,2); //Not used for now

//Read the 5th digit: 4 bits
//Number of chips reporting cluster data

 string sNchip=data.substr(4,1);
 //convert to integer
 int Nchip=stoi(sNchip,0,16);

 //cout << "Nchip: " << Nchip <<endl;
 // If there is not cluster in the layer
 if (Nchip==0) return 1;
///////////////////////////////////////
//From now the format is dynamical
//However it always comes 3 digits per 3 digits
///////////////////////////////////////
 //Define the digits index to read
 int index=0;
 //Start with 5 for the first ch3ip header
 index=5;
 if(index>=datalength||index+3>=datalength) return 0;//Number of bytes incorrect

 //Variables to combine with the chip boundary clusters

 int* laststr=new int [12];
 int* firststr=new int [12];
 for(int i=0;i<12;i++) laststr[i]=-1;  //will be equal to the j index  of the cluster that has a strip 63
 for(int i=0;i<12;i++) firststr[i]=-1;  //will be equal to the j index  of the cluster that has a strip 0

 vector<ALTckhit*>tmpHV;
 ALTckhit*tmpH;

 for(int i=0;i<Nchip;i++)//Loop over the number of chips reporting cluster data
   {

    //Read the 3-digit ASIC header: 12 bits
    //1 bit: cluster overflow
    //1 bit: unused
    //4 bits: number of clusters
    //1 bit: chip error
    //1 bit: parity error
    //4 bits: chip address

    //Read the number of clusters
    //The number of clusters is 4 bits contained in 2 digits
    //The 2 lowest-order bits of the first digit (4 bits) and
    //the 2 highest-order bits of the second digit (4 bits)
    //First read the 2 digits
    if(index>=datalength||index+2>=datalength) return 0;//Number of bytes incorrect
    string sNclus=data.substr(index,2);
    //convert to 16-bit integer
    uint16_t intNclus= (uint16_t)stoi(sNclus,0,16);
    //Shift the 4 bits to the lowest position: shift of 2 is needed
    //then keep only the last 4 bits: Make a AND with 0x000F
    int Nclus=(int)((intNclus >> 2) &0x000F);

    //Read cluster overflow: Shift of 7 bits
    int Clusoverflow=(int)((intNclus >> 7) &0x0001);
    //Read chip error: Shift of 1 bit
    int chiperr=(int)((intNclus >> 1) &0x0001);
    //Read parity: Shift of 0 bit
    int parityerr=(int)(intNclus &0x0001);

    //cout << "Chip error: " << chiperr <<endl;
    //cout << "Parity error: " << parityerr <<endl;

    //if(chiperr==1) continue;
    //if(parityerr==1) continue;

    //Read the chip address  between 0 and 15
    if(index+2>=datalength||index+3>=datalength) return 0; //Number of bytes incorrect
    string sChipadd=data.substr(index+2,1);
    //cout << sChipadd << endl;
    //convert to integer
    int Chipadd=stoi(sChipadd,0,16);

   // cout << "Chip: "<< Chipadd << ", NClus: " << Nclus <<endl;

    index+=3;
    if(index>=datalength||index+3>=datalength) return 0;//Number of bytes incorrect
    for(int j=0;j<Nclus;j++)//Loop over the number of clusters
      {
       tmpH=new ALTckhit();
       //Read the 3-digit cluster data: 12 bits
       //6 bits: number of strips minus 1 (0 to 63)
       //6 bits: address of the first strip (0 to 63)
       if(index>=datalength||index+3>=datalength) return 0;//Number of bytes incorrect
       string sClus=data.substr(index,3);
       //convert to 16-bit integer
      //cout << sClus <<endl;
       if(sClus.empty() || sClus==" ")
        {
         tmpH->set_L(L);
         tmpH->set_chip(Chipadd);
         tmpH->set_nstrips(-1);
         tmpH->set_fstrip(-1);
         tmpH->set_fstripID(-1);
         tmpH->set_overflow(Clusoverflow,-1.);
         tmpH->set_chiperr(chiperr,-1.);
         tmpH->set_parityerr(parityerr,-1.);
         //Fill up the vector
         Hh->push_back(tmpH);
         //Increment the index to the next 3-digit word
         index+=3;
         continue;
        }
       uint16_t Clus;

       Clus=(uint16_t)stoi(sClus,0,16);

       //Mask to read the address of the first strip
       //First shift of 6 bits to the right
       //then read the last 6 bits
       int Nstrip=(int)((Clus >>6) & 0x003F);

       //Mask to read the address of the first strip(last 6 bits): 0x003F
       int Stripadd=(int)(Clus & 0x003F);

       //cout << "Nstrip: "<< Nstrip+1 << ", Stripadd: " << Stripadd <<endl;

       //Determine the strip ID
       //Equation from Sarah's email of September 4 2017.
       //From  0 to 767 : Lowest index strip of the cluster
       //int  firstStripNumber=64*(Chipadd+1)-Stripadd-1-Nstrip;
       int  firstStripNumber=64*(Chipadd+1)-Stripadd-1;

       tmpH->set_L(L);
       tmpH->set_chip(Chipadd);
       tmpH->set_nstrips(Nstrip);
       tmpH->set_fstrip(Stripadd);
       tmpH->set_fstripID(firstStripNumber);

       tmpH->set_overflow(Clusoverflow,-1.);
       tmpH->set_chiperr(chiperr,-1.);
       tmpH->set_parityerr(parityerr,-1.);

       //First  strip from left to right is hit
       //if(Stripadd+Nstrip==63) firststr[Chipadd]=tmpHV.size();
       if(Stripadd==63) firststr[Chipadd]=tmpHV.size();
       //Last strip from left to right is hit
       //if(Stripadd==0) laststr[Chipadd]=tmpHV.size();
       if(Stripadd-Nstrip==0) laststr[Chipadd]=tmpHV.size();

       //Internal trigger for Layer L set to 1
       Ti[L]=1;
       tmpH->set_noisy(0);
       //Mask of bad strips
       for(int k=0;k<Nstrip;k++)
         {
          int tmpstrip=firstStripNumber+k;
          //if(L==3&&tmpstrip==9){tmpH->set_noisy(1);}
          if(L==4&&tmpstrip==357){tmpH->set_noisy(1);}
          if(L==4&&tmpstrip==358){tmpH->set_noisy(1);}
          //if(L==5&&tmpstrip==691){tmpH->set_noisy(1);}
          //if(L==6&&tmpstrip==576){tmpH->set_noisy(1);}
         }

       //Fill up the vector
       tmpHV.push_back(tmpH);

       //Increment the index to the next 3-digit word
       index+=3;
      }//j
   }//i
 //Loop over the clusters and merge at the boundaries if needed
 for(int i=0;i<(int) tmpHV.size();i++)
   {
    int chip=tmpHV.at(i)->get_chip();
    int fstrip=tmpHV.at(i)->get_fstrip();
    int nstrips=tmpHV.at(i)->get_nstrips();
    int noisy=tmpHV.at(i)->get_nstrips();

    if(fstrip==0 && chip<11 && chip!=5) //The last strip is touched not chip 5 nor 11
     {
      int ij= firststr[chip+1];
      //There is a cluster on the first strip of the next chip
      if(ij!=-1)
       {
        if (noisy==0)
          tmpHV.at(i)->set_noisy(tmpHV.at(ij)->get_noisy());

        tmpHV.at(i)->set_nstrips(nstrips+tmpHV.at(ij)->get_nstrips()+1);
        tmpHV.at(i)->set_nstripsNC(tmpHV.at(ij)->get_nstrips());
        tmpHV.at(i)->set_overflow((unsigned int)1,tmpHV.at(ij)->get_overflow(0));
        tmpHV.at(i)->set_chiperr((unsigned int)1,tmpHV.at(ij)->get_chiperr(0));
        tmpHV.at(i)->set_parityerr((unsigned int)1,tmpHV.at(ij)->get_parityerr(0));

       }
      Hh->push_back(tmpHV.at(i));
     }
     else if(fstrip+nstrips==63 && chip>0 && chip!=6) //The first strip is touched not chip 0 nor 6
     {
      int ij= laststr[chip-1];
      //There is not a cluster on the last strip of the previous chip: This is a real hit
      if(ij==-1)
       {
        if(!(noisy==1 && nstrips==0))  //Do not add cluster with 1 single inner strip that is noisy
          Hh->push_back(tmpHV.at(i));
       }
      //If there is a cluster on the last strip of the previous we don't record the information.
      //The information is filled  with the other cluster.
     }
    else //Fill the non boudary clusters
     {
       if(!(noisy==1 && nstrips==0))  //Do not add cluster with 1 single inner strip that is noisy
        Hh->push_back(tmpHV.at(i));
     }
   }//i


 return 1;
}



int DecodeASILong(string data,vector<ALTckhit*>* Hh,int*Ti,int*Tic,int* Nhitnoisy,int*ilay)
{

//For data from November, 2017

//Get string length
 int noisyhit=0;
 int datalength=data.length();
 //Check the number of characters
 //It must be 9 + a multiple of 3
 //The last character is always a " " so we remove 1 to the datalength
//cout <<endl;
 //cout << "ASI Data length " << data.length();
 //cout << " ASI Data: " << data <<endl;
 if((datalength-9)%3!=0)
  {
   //cout << "The length of the data string does not pass the requirement: (datalength-9)%3==0 : Length=" <<datalength <<endl;
   //cout << data <<endl;
   //for(int i=0;i<data.size();i++)
   //    cout << data[i]<<endl;
   //cout << "No hit is added"<< endl;
   return 0;
  }

///////////////////////////////////////
//The first 9 digits have a static format
///////////////////////////////////////

//Read the first 2 digits: 1 byte (8 bits)
//They correspond to length of the following bytes
// It is the lentgh of the ASIC string + 1
 string ASICstrlgth=data.substr(0,2);

//Read the 3rd and 4th digits: 1 byte (8 bits)
//It should always be "E7"
 string Indentifier=data.substr(2,2);


//Read the 5th and 6th digits: 1 byte (8 bits)
//They correspond to the FPGA address of the layer

 string FPGAadd=data.substr(4,2);
 int LL=0;
 int L=0;
 LL=stoi(FPGAadd,0,16);
//Convert FPGA address to Layer number
 switch(LL)
  {
   case 8: L=0;break;
   case 0: L=0;break;
   case 1: L=1;break;
   case 2: L=2;break;
   case 3: L=3;break;
   case 4: L=4;break;
   case 5: L=5;break;
   case 6: L=6;break;
   case 7: L=7;break;
  }//switch
  //cout << "Layer: " << L <<endl;

  *ilay=L;
//Read the 7th and 8th digits: 1 byte (8 bits)
//From left to right
//Event tag first part: 5 bits: clock counter running in the trackerboard FPGA
//The counters are synched at 0 when a reset/synch signal is received by the FPGA.
//Event tag second part: 2 bits: ASIC trigger tag
//Error flag: 1 bit: is set to 1 in case of trigger tag mismatch

 string Eventtag=data.substr(6,2); //Not used for now

//Read the 9th digit: 4 bits
//Number of chips reporting cluster data

 string sNchip=data.substr(8,1);
 //convert to integer
 int Nchip=stoi(sNchip,0,16);

// cout << "Nchip: " << Nchip <<endl;
 // If there is not cluster in the layer
 if (Nchip==0) return 1;
///////////////////////////////////////
//From now the format is dynamical
//However it always comes 3 digits per 3 digits
///////////////////////////////////////
 //Define the digits index to read
 int index=0;
 //Start with 9 for the first chip header
 index=9;


 if(index>=datalength||index+3>=datalength) return 0;//Number of bytes incorrect


 //Variables to combine with the chip boundary clusters

 int* laststr=new int [12];
 int* firststr=new int [12];
 for(int i=0;i<12;i++) laststr[i]=-1;  //will be equal to the j index  of the cluster that has a strip 63
 for(int i=0;i<12;i++) firststr[i]=-1;  //will be equal to the j index  of the cluster that has a strip 0

 vector<ALTckhit*>tmpHV;
 ALTckhit*tmpH;
 for(int i=0;i<Nchip;i++)//Loop over the number of chips reporting cluster data
   {

    //Read the 3-digit ASIC header: 12 bits
    //1 bit: cluster overflow
    //1 bit: unused
    //4 bits: number of clusters
    //1 bit: chip error
    //1 bit: parity error
    //4 bits: chip address

    //Read the number of clusters
    //The number of clusters is 4 bits contained in 2 digits
    //The 2 lowest-order bits of the first digit (4 bits) and
    //the 2 highest-order bits of the second digit (4 bits)
    //First read the 2 digits
    if(index>=datalength||index+2>=datalength) return 0;//Number of bytes incorrect
    string sNclus=data.substr(index,2);
    //convert to 16-bit integer
    uint16_t intNclus= (uint16_t)stoi(sNclus,0,16);
    //Shift the 4 bits to the lowest position: shift of 2 is needed
    //then keep only the last 4 bits: Make a AND with 0x000F
    int Nclus=(int)((intNclus >> 2) &0x000F);

    //Read cluster overflow: Shift of 7 bits
    int Clusoverflow=(int)((intNclus >> 7) &0x0001);
    //Read chip error: Shift of 1 bit
    int chiperr=(int)((intNclus >> 1) &0x0001);
    //Read parity overflow: Shift of 0 bit
    int parityerr=(int)(intNclus &0x0001);

    //cout << "Chip error: " << chiperr <<endl;
    //cout << "Parity error: " << parityerr <<endl;

    //if(chiperr==1) continue;
    //if(parityerr==1) continue;

    //Read the chip address  between 0 and 15
    if(index+2>=datalength||index+3>=datalength) return 0; //Number of bytes incorrect
    string sChipadd=data.substr(index+2,1);
    //cout << sChipadd << endl;
    //convert to integer
    int Chipadd=stoi(sChipadd,0,16);

    //cout << "Chip: "<< Chipadd << ", NClus: " << Nclus <<endl;

    index+=3;
    if(index>=datalength||index+3>=datalength) return 0;//Number of bytes incorrect


    for(int j=0;j<Nclus;j++)//Loop over the number of clusters
      {
       tmpH=new ALTckhit();
       //Read the 3-digit cluster data: 12 bits
       //6 bits: number of strips minus 1 (0 to 63)
       //6 bits: address of the first strip (0 to 63)
       if(index>=datalength||index+3>=datalength) return 0;//Number of bytes incorrect
       string sClus=data.substr(index,3);
       //convert to 16-bit integer
       //cout << sClus <<endl;
       if(sClus.empty() || sClus==" ")
        {
         tmpH->set_L(L);
         tmpH->set_chip(Chipadd);
         tmpH->set_nstrips(-1);
         tmpH->set_fstrip(-1);
         tmpH->set_fstripID(-1);
         tmpH->set_overflow(Clusoverflow,-1.);
         tmpH->set_chiperr(chiperr,-1.);
         tmpH->set_parityerr(parityerr,-1.);
        //Fill up the vector
         //Hh->push_back(tmpH);
         //Increment the index to the next 3-digit word
         index+=3;
         continue;
        }
       uint16_t Clus;

       Clus=(uint16_t)stoi(sClus,0,16);

       //Mask to read the address of the first strip
       //First shift of 6 bits to the right
       //then read the last 6 bits
       int Nstrip=(int)((Clus >>6) & 0x003F);

       //Mask to read the address of the first strip(last 6 bits): 0x003F
       int Stripadd=(int)(Clus & 0x003F);

      // cout << "Nstrip: "<< Nstrip+1 << ", Stripadd: " << Stripadd <<endl;

       //Determine the strip ID
       //Equation from Sarah's email of September 4 2017.
       //From 0 to 767
       int  firstStripNumber=64*(Chipadd+1)-Stripadd-1-Nstrip;
       //int  firstStripNumber=64*(Chipadd+1)-Stripadd-1;

       tmpH->set_L(L);
       tmpH->set_chip(Chipadd);
       tmpH->set_nstrips(Nstrip);
       tmpH->set_fstrip(Stripadd);
       tmpH->set_fstripID(firstStripNumber);

       tmpH->set_overflow(Clusoverflow,-1.);
       tmpH->set_chiperr(chiperr,-1.);
       tmpH->set_parityerr(parityerr,-1.);

       //First  strip from left to right is hit
       if(Stripadd+Nstrip==63) firststr[Chipadd]=tmpHV.size();
       //if(Stripadd==63) firststr[Chipadd]=tmpHV.size();
       //Last strip from left to right is hit
       if(Stripadd==0) laststr[Chipadd]=tmpHV.size();
       //if(Stripadd-Nstrip==0) laststr[Chipadd]=tmpHV.size();

       //Internal trigger for Layer L set to 1
       Ti[L]=1;
       tmpH->set_noisy(0);

       //Flag is 1: Don't use the hit
       int flagN=0;
       //if(L==4&&firstStripNumber==357&&Nstrip<=1)flagN=1;
       //if(L==4&&firstStripNumber==358&&Nstrip==0)flagN=1;

       //Mask of bad strips
       for(int k=0;k<Nstrip+1;k++)
         {
          //For flight configuration 2018
	        int tmpstrip=firstStripNumber+k;
          //if(L==4&&tmpstrip==357){tmpH->set_noisy(1);}
          //if(L==4&&tmpstrip==358){tmpH->set_noisy(1);}
         }

       //Fill up the vector
       if(flagN==0) tmpHV.push_back(tmpH);

       //Increment the index to the next 3-digit word
       index+=3;
      }//j
   }//i

 //Loop over the clusters and merge at the boundaries if needed
 for(int i=0;i<(int) tmpHV.size();i++)
   {
    int chip=tmpHV.at(i)->get_chip();
    int fstrip=tmpHV.at(i)->get_fstrip();
    int noisy=tmpHV.at(i)->get_noisy();
    int nstrips=tmpHV.at(i)->get_nstrips();

    if(fstrip==0 && chip<11 && chip!=5) //The last strip is touched not chip 5 nor 11
    //if(fstrip-nstrips==0 && chip<11 && chip!=5) //The last strip is touched not chip 5 nor 11
     {
      int ij= firststr[chip+1];
      //There is a cluster on the first strip of the next chip
      if(ij!=-1)
       {
        if(noisy==0){ tmpHV.at(i)->set_noisy(noisy+tmpHV.at(ij)->get_noisy());noisy=noisy+tmpHV.at(ij)->get_noisy();}
        nstrips=nstrips+tmpHV.at(ij)->get_nstrips()+1;
        tmpHV.at(i)->set_nstrips(nstrips);
        tmpHV.at(i)->set_nstripsNC(tmpHV.at(ij)->get_nstrips());
        tmpHV.at(i)->set_overflow((unsigned int)1,tmpHV.at(ij)->get_overflow(0));
        tmpHV.at(i)->set_chiperr((unsigned int)1,tmpHV.at(ij)->get_chiperr(0));
        tmpHV.at(i)->set_parityerr((unsigned int)1,tmpHV.at(ij)->get_parityerr(0));
       }
      Hh->push_back(tmpHV.at(i));
      if(nstrips<3)Tic[L]=1;
      noisyhit+=noisy;
     }
    else if(fstrip+nstrips==63 && chip>0 && chip!=6) //The first strip is touched not chip 0 nor 6
     //else if(fstrip==63 && chip>0 && chip!=6) //The first strip is touched not chip 0 nor 6
     {
      int ij= laststr[chip-1];
      //There is not a cluster on the last strip of the previous chip: This is a real hit
      if(ij==-1)
       {
        Hh->push_back(tmpHV.at(i));
        if(nstrips<3)Tic[L]=1;
        noisyhit+=noisy;
       }

      //If there is a cluster on the last strip of the previous we don't record the information.
      //The information is filled  with the other cluster.
     }
    else //Fill the non boudary clusters
     {
      Hh->push_back(tmpHV.at(i));
      if(nstrips<3)Tic[L]=1;
      noisyhit+=noisy;

     }
   }//i
 *Nhitnoisy=noisyhit;
 return 1;
}



//*******************************************************************
// Split the string str into a vector of string
// The separator is the character between each word of the string str
// Each string of the vector contains a word of the string
// The vector is ordered from the first to the last word
// The vector index starts from 0
//*******************************************************************
vector<string> split (string* str,char separator)
{

  vector<string> output;
  string::size_type prev_pos=0, pos=0;

  while ((pos =str->find(separator,pos))!=string::npos)
    {
      string substring(str->substr(prev_pos,pos-prev_pos));
      if(!substring.empty())output.push_back(substring);//Check that substring is not empty before filling the vectors
      prev_pos=++pos;
    }
  output.push_back(str->substr(prev_pos,pos-prev_pos)); //Last word
  return output;
}

//*******************************************************************
// Transform the string str into a double
//*******************************************************************
double s2lf(string* str)
{
  istringstream buffer(*str);
  double temp;
  buffer >> temp;
  return temp;
}

//*******************************************************************
// Transform the string str into a float
//*******************************************************************
float s2f(string* str)
{
  istringstream buffer(*str);
  float temp;
  buffer >> temp;
  return temp;
}

//*******************************************************************
// Transform the string str to int
//*******************************************************************
int s2i(string* str)
{
  istringstream buffer(*str);
  int temp;
  buffer >> temp;
  return temp;

}


//*******************************************************************
// Two functions for sorting in ascending order a array
//*******************************************************************

/*Function for partitioning the array*/

int Partition(int low,int high,float arr[])
{
 float high_vac,low_vac,pivot;
 pivot=arr[low];
 while(high>low)
   {
    high_vac=arr[high];
  //  cout << "high_vac : " << high_vac << " pivot " << pivot<< endl;
    while(pivot<high_vac)
     {
      if(high<=low) break;
      high--;
      high_vac=arr[high];
     }
    arr[low]=high_vac;
    low_vac=arr[low];
    while(pivot>=low_vac)// modification
     {
      if(high<=low) break;
      low++;
      low_vac=arr[low];
     }
    arr[high]=low_vac;
   }
 arr[low]=pivot;
 return low;
}

void Quick_sort(int low,int high,float arr[])
{
 //cout << "in Quick_sort " << low <<" " << high<<endl;
 int Piv_index;
 if(low<high)
  {
   Piv_index=Partition(low,high,arr);
   // cout << "Piv_index " << Piv_index <<endl;

   Quick_sort(low,Piv_index-1,arr);
   Quick_sort(Piv_index+1,high,arr);
  }
}



//*******************************************************************
// Extract year,month and day from the string str
//*******************************************************************
void extractdate(int *y,int*m,int*d,string*str)
{
	  vector<string> date;
	  date=split(str,'/'); //separator is '/'
	  *y=s2i(&date.at(2));
	  *m=s2i(&date.at(0));
	  *d=s2i(&date.at(1));
}

//*******************************************************************
// Extract hour,minute and seconde from the string str
//*******************************************************************
void extracttime(int *h,int*m,int*s,string*str)
{
	  vector<string> time;
	  time=split(str,':');// separator is ':'
	  *h=s2i(&time.at(0));
	  *m=s2i(&time.at(1));
	  *s=s2i(&time.at(2));
}
