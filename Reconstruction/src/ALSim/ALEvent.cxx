//////////////////////////////////////////////////////////////////////////////////////////
///    Author: Pierre-Simon Mangeard, psmangeard@gmail.com
///    Department of Physics and Astronomy, University of Delaware, October 28, 2016
///				Sarah Mechbal, smechbal@ucsc.edu
////   Department of Physics, University of California Santa Cruz
//////////////////////////////////////////////////////////////////////////////////////////

#include "ALEvent.h"
ClassImp(ALEvent)
ClassImp(ALTckhit)

//Constructors
ALEvent::ALEvent()// Default
{
 eventnumber=0; //Event number
 //runnumber=0; //Run number
 bpdnumber=0; //BPD file number

 
 //PSE1 Line
 yPSE1=-1;//Year from PSE1 line linked to the event
 mPSE1=-1;//Month from PSE1 line linked to the event
 dPSE1=-1;//Day from PSE1 line linked to the event
 hPSE1=-1;//Hour from PSE1 line linked to the event
 miPSE1=-1;//Minute from PSE1 line linked to the event
 sPSE1=-1;//Second from PSE1 line linked to the event
 N=-1;//N: 92
 Code=-1;//Code: 221
 nEcho=-1;//nEcho: 0
 Last=-1;//Last: 32
 FirstNibble=-1;//ZERO FirstNibble: 15
 runnumber=0;//Run: 1
 Trigger=-1;//Trigger: 50 
 Stamp=-1;//Stamp: 17206 
 Go1=-1;//Go1: 2 
 yPSE1b=-1;//Year from Date/Time PSE1 line linked to the event
 mPSE1b=-1;//Month from Date/Time PSE1 line linked to the event
 dPSE1b=-1;//Day from Date/Time PSE1 line linked to the event
 hPSE1b=-1;//Hour from Date/Time PSE1 line linked to the event
 miPSE1b=-1;//Minute from Date/Time PSE1 line linked to the event
 sPSE1b=-1;//Second from Date/Time PSE1 line linked to the event

 Status=0;  //8-bit trigger word: T4 T3 T2 T1 Guard Trackertrigger1 Trackertrigger0 PMTsecondary PMTprimary  
 T4=false;
 T3=false;
 T2=false;
 T1=false;
 TrTrig1=false;
 TrTrig0=false;
 PMTTrig2=false;
 PMTTrig1=false;
 G=false;  //Keep it here in case it is used in the future

 //The 5 PHA and ToF are empty vectors when ALEvent is constructed
 //EneT1;//PHA0: 350 
 //EneT2;//PHA1: 3
 //EneT3;//PHA2: 402 
 //EneT4;//PHA3: 3 
 //EneG; //PHA4: 7 
 //ToF;  //PHA5: -1473
 
 //PSE2 Line
 yPSE2=-1;//Year from PSE2 line linked to the event
 mPSE2=-1;//Month from PSE2 line linked to the event
 dPSE2=-1;//Day from PSE2 line linked to the event
 hPSE2=-1;//Hour from PSE2 line linked to the event
 miPSE2=-1;//Minute from PSE2 line linked to the event
 sPSE2=-1;//Second from PSE2 line linked to the event
 
 sTraxtrig=-1;//sTraxTrig: 0032
 TraxTrig=-1;//TraxTrig: 50
 TraxComm=-1;//TraxComm: 132
 TraxPatt=-1;//TraxPatt: 215 
 TotalTrax=-1;//TotalTrax: 8 
 TotalBytes=-1;//TotalBytes: 14500 FINI

 //PEHF1,2,3,4 lines
 //HOUSE KEEPING lines
 //If time of line 1 and time of line 4 are different then there is an issue
 //PEHF1: 09/29/2022 16:28:46 Date: 01/01/2001 01:01:43 Run: 1 Source: FF00FF
 //PEHF2: 09/29/2022 16:28:46 ComLast: 0AB6 ComCount: 149 ComErr: 0 GenErr: 2 Go: 5 Go1: 0 AvgROTime: 224
 //PEHF3: 09/29/2022 16:28:46 Rates:  149 1323 396 75 318 TrCom: 224 Tr1Pct: 80 Tr2Pct: 20 UARTErr: 0 UARTTim: 0
 //PEHF4: 09/29/2022 16:28:46 Chips:  10 24 12 24 4 4 2 2 OrRates:  41 17 196 261 8 9 11 12 Temps:  27.0 25.0 24.5 TrackStats:  18.0 3.0 18.0 3.0 0.0 100.0 Samples: 41506 PctLive: 99.0
//PEHF4: 11/10/2023 19:22:54 Chips:  7 7 7 6 6 5 5 5 OrRates:  15 341 179 119 4 6 7 7 Temps:  35.0 24.5 22.1 TrackStats:  0 0 0 0 PctMaBzy: 0.0 PctTrLive: 0.0 Samples: 39352 PctADCLive: 99.0

 yEPHK1=-1;//Year from PEHF1 line linked to the event
 mEPHK1=-1;//Month from PEHF1 line linked to the event
 dEPHK1=-1;//Day from PEHF1 line linked to the event
 hEPHK1=-1;//Hour from PEHF1 line linked to the event
 miEPHK1=-1;//Minute from PEHF1 line linked to the event
 sEPHK1=-1;//Second from PEHF1 line linked to the event
 
 yEPHK1b=-1;//Year from PEHF1 line Date linked to the event
 mEPHK1b=-1;//Month from PEHF1 line Date linked to the event
 dEPHK1b=-1;//Day from PEHF1 line Date linked to the event
 hEPHK1b=-1;//Hour from PEHF1 line Date linked to the event
 miEPHK1b=-1;//Minute from PEHF1 line Date linked to the event
 sEPHK1b=-1;//Second from PEHF1 line Date linked to the event
 
 yEPHK4=-1;//Year from PEHF4 line linked to the event
 mEPHK4=-1;//Month from PEHF4 line linked to the event
 dEPHK4=-1;//Day from PEHF4 line linked to the event
 hEPHK4=-1;//Hour from PEHF4 line linked to the event
 miEPHK4=-1;//Minute from PEHF4 line linked to the event
 sEPHK4=-1;//Second from PEHF4 line linked to the event 
 
 //PEHF1
 RunEPHK=-1; 
 SourceEPHK="NA";   //Source of the EVENT PSOC HOUSEKEEPING
 //PEHF2
 ComLast="NA";     //Last Command
 ComCount=-1;    //Command Count 
 ComErr=-1;      //Command Error Count
 GenErr=-1;      //General Error Count
 Go=-1;          //NUmber of events
 Go1EPHK=-1;      //Number of missing events
 AvgROTime=-1;   //Average Readout time in microsec
 //PEHF3datalinePMHF2
 T1r=-1;
 T2r=-1;
 T3r=-1;
 T4r=-1;
 Gr=-1;  

 TrCom=-1;    //Tracker Command Count
 Tr1Pct=-1;   //Percentage of tracker trigger 1
 Tr2Pct=-1;   //Percentage of tracker trigger 2 
 UARTErr=-1;   //Tracker UART Error Count
 UARTTim=-1;   //Tracker UART Timeout Count 
 //PEHF4
 for(int i=0;i<8;i++) NhperCh[i]=-1;   //hits per event*10
 for(int i=0;i<8;i++) Lrate[i]=-1;    
 for(int i=0;i<8;i++) Ldummy[i]=-1;     //From ASI line 

 //Temps:  
 PSOCDieTemp=-999;
 TempL0=-999;
 TempL7=-999; 
 for(int i=0;i<6;i++) TrackStats[i]=0;////1 if ASI line was present
 PctMaBzy=-1;
 PctTrLive=-1;
 Samples=-1; //Number of sample used to calculate PctLive
 PctADCLive=-1; //PSOC Live time percentage using N Samples between the last 2 events
 
 //PMHF1 MAIN PSOC HOUSEKEEPING 
 //PMHF1: 07/19/2022 13:29:16 Date: 07/19/2022 13:29:07 DeltaT: 5716.00 Source: FF00FF LastCmd: 0320 CountCmd: 2 ErrCmd: 0 ErrGen: 12 Missing: 0 FIFOPct: 0 Drop232: 0 DropUSB: 0 
 yMPHK1=-1;//Year from PMHF1 line linked to the event
 mMPHK1=-1;//Month from PMHF1 line linked to the event
 dMPHK1=-1;//Day from PMHF1 line linked to the event
 hMPHK1=-1;//Hour from PMHF1 line linked to the event
 miMPHK1=-1;//Minute from PMHF1 line linked to the event 
 sMPHK1=-1;//Second from PMHF1 line linked to the event
 yMPHK1b=-1;//Year from PMHFb1 line linked to the event
 mMPHK1b=-1;//Month from PMHF1b line linked to the event
 dMPHK1b=-1;//Day from PMHF1b line linked to the event
 hMPHK1b=-1;//Hour from PMHF1b line linked to the event
 miMPHK1b=-1;//Minute from PMHF1b line linked to the event 
 sMPHK1b=-1;//Second from PMHF1b line linked to the event
 DeltaT=-999;
 SourceMPHK="NA";
 LastCmdMPHK=-1;
 CountCmdMPHK=-1;
 ErrCmdMPHK=-1;
 ErrGenMPHK=-1;
 MissingMPHK=-1;
 FIFOPctMPHK=-1;
 Drop232MPHK=-1;
 DropUSBMPHK=-1;
    
 //PMHF2
 //PMHF2: 07/19/2022 13:29:16 BarCounts: 29028110 149972000 29255638 149731314 BarRates:  198586.8 -274361.6 -200137.7 -272696.6 400.0 0.00 400.0 0.00
 //int BarCounts[4];
 //int BarRate[4];
 P1MPHK=-999; 
 P2MPHK=-999; 
 Temp1MPHK=-999; 
 Temp2MPHK=-999; 
 //PMHF3
 //PMHF3: 07/19/2022 13:29:16 Dp: 2010065 Dt: -2099950 IntPress: 750.24 IntTemp: 42.3 BoardTemp: 43.0 DieTemp: 44.0 Analog: 3.47 147.33 3.32 91.66 5.01 840.30 5.25 4.25 15.24 3.61 2730.47 121.43 
 yMPHK3=-1;//Year from PMHF3 line linked to the event
 mMPHK3=-1;//Month from PMHF3 line linked to the event
 dMPHK3=-1;//Day from PMHF3 line linked to the event
 hMPHK3=-1;//Hour from PMHF3 line linked to the event
 miMPHK3=-1;//Minute from PMHF3 line linked to the event 
 sMPHK3=-1;//Second from PMHF3 line linked to the event
 Dp=-999;
 Dt=-999;
 IntPress=-999;
 IntTemp=-999;
 BoardTemp=-999;
 DieTemp=-999;
 Dig3V=-999;
 Dig3C=-999;
 Ana3V=-999;
 Ana3C=-999;
 Dig5V=-999;
 Dig5C=-999;
 Ana5V=-999;
 Ana5C=-999;
 Dig15V=-999;
 TckV=-999;
 TckC=-999;
 TckbiasC=-999;
 
 ///////////////////////////////////////////////
  

 yPHA=-1;//Year from PHA line linked to the event
 mPHA=-1;//Month from PHA line linked to the event
 dPHA=-1;//Day from PHA line linked to the event
 hPHA=-1;//Hour from PHA line linked to the event
 miPHA=-1;//Minute from PHA line linked to the event
 sPHA=-1;//Second from PHA line linked to the event
 GoPHA=-1;//Go counter from PHA line linked to the event
 tPHA=-1;//timer from from PHA line linked to the event
 yEVT=-1;//Year from EVT line linked to the event
 mEVT=-1;//Month from EVT line linked to the event
 dEVT=-1;//Day from EVT line linked to the event
 hEVT=-1;//Hour from EVT line linked to the event
 miEVT=-1;//Minute from EVT line linked to the event
 sEVT=-1;//Second from EVT line linked to the event
 EVT="";//Data from EVT line linked to the event
 GoEVT=-1;//Go counter from EVT line linked to the event
 tEVT=-1;//timer from from EVT line linked to the event
 nHitLEVT=-999;//nHitL from EVT line linked to the event added 12/05/2017
 CCEVT=-999;//CC from EVT line linked to the event   added 12/05/2017
 PatternEVT=-999;//CC from EVT line linked to the event   added 12/05/2017
 Q1EVT=-999;//Q1 from EVT line linked to the event   added 12/05/2017
 TrigEVT=-999;//Q1 from EVT line linked to the event   added 12/05/2017

 for(int i=0;i<8;i++) L[i]=string();//Data from  ASI lines of the event
 for(int i=0;i<8;i++) flagL[i]=0;////1 if ASI line was present

 //////////////////////////
 ///////MC variable////////
 //////////////////////////

 ncase=0;
 typeMC=-99; //type of particle
 EkMC=0;   //kinetic energy of the particle
 pMC=0;		//momentum at point of injection
 X0MC=Y0MC=Z0MC=0;//Coordinates of the partcle at the injection point
 CX0MC=CY0MC=CZ0MC=0; //Incidence cosines of the partcle at the injection point

 typePP=-99;
 EkPP=0;
 ZenPP=0;
 AziPP=0;
 CoLatSP=0;
 CoLonSP=0;

 Nhits=0; //Number of hits in the event
 Nhnoisy=0;//Number of hits with noisy channel added 23/10/2019

 typereco=-999; //type of particle
 Ekreco=-999;   //kinetic energy of the particle
 p0reco=-999;  //momentum of the particle
 X0reco=Y0reco=Z0reco=0;//Coordinates of the partcle at the injection point
 CX0reco=CY0reco=CZ0reco=0; //Incidence cosines of the partcle at the injection point
 ndf=0;
 chi2=cl=-1;
 d0=phi0=cpa=dz=tanl=0;
 phi0_init=cpa_init=tanl_init=0;
 d0err2=phi0err2=cpaerr2=dzerr2=tanlerr2=0;
 Cov_init=Cov_last=0;

 EkPR=-999;
 p0PR =-999;
 aPR=bPR=cPR=0;
 interPR=slopePR=0;
 chi2BPR=chi2NBPR=clBPR=clNBPR=-1;
 deflecPR=0;
 XT1PR =-999;
 XT3PR =-999;
 XT4PR =-999;
 XGPR =-999;
 YT1PR =-999;
 YT3PR =-999;
 YT4PR =-999;
 YGPR =-999;
 thBiPR=-999;//theta incoming in BP from PR
 thBoPR=-999;//theta outcoming in BP from PR
 thNBPR=-999;//theta  in BP from PR

 for(int i=0;i<8;i++) NLPR[i]=0;		//number of hits per layer after PR selections

 //Triggers: default is false
 //T1=false;
 //T2=false;
 //T3=false;
 //T4=false;
 guard=false;
 Ti=0;
 Tic=0;
 TiPR=0;
 NphCK=0;

 //HOUSEKEEPING FROM COUNTERS 1 AND 3
 //Data FROM "CT1" LINE
 yCT1=-1;//Year from CT1 line linked to the event (last read CT1 line)
 mCT1=-1;//Month from CT1 line linked to the event (last read CT1 line)
 dCT1=-1;//Day from CT1 line linked to the event (last read CT1 line)
 hCT1=-1;//Hour from CT1 line linked to the event (last read CT1 line)
 miCT1=-1;//Minute from CT1 line linked to the event (last read CT1 line)
 sCT1=-1;//Second from CT1 line linked to the event (last read CT1 line)
 TempCT1=-999; //Temperature measured on the board CT1

 OnTimeCT1=-1;//1/second counter which now gives time since power on (the on-chip batteries have failed; this used to keep incrementing with power off)
 LastCT1=-1;//The last command received by the payload, expressed as a decimal number (it is in HeX on the GUI display)
 CountCT1=-1;//Count of commands received by the payload since power on

 //Barometer information: NOT INTERPRETED from line CT1
 Baro1T=-999;//Barometer 1 Temperature
 Baro1P=-999;//Barometer 1 Pressure
 Baro2T=-999;//Barometer 2 Temperature
 Baro2P=-999;//Barometer 2 Pressure
 //Barometer information: INTERPRETED from line CT1
 TempB1=-999;//Barometer 1 Temperature
 TempB2=-999;//Barometer 2 Temperature
 PressB1=-999;//Barometer 1 Pressure
 PressB2=-999;//Barometer 2 Pressure

 GOCT1=-999;
 coinCT1=-199;

 //Voltages
 Volt5VCT1=-999;  // Positive 5V from line CT1
 Volt15VCT1=-999; // Positive 15V from line CT1

 //Data FROM "CT3" LINE
 yCT3=-1;//Year from CT3 line linked to the event (last read CT3 line)
 mCT3=-1;//Month from CT3 line linked to the event (last read CT3 line)
 dCT3=-1;//Day from CT3 line linked to the event (last read CT3 line)
 hCT3=-1;//Hour from CT3 line linked to the event (last read CT3 line)
 miCT3=-1;//Minute from CT3 line linked to the event (last read CT3 line)
 sCT3=-1;//Second from CT3 line liNoisyClusnked to the event (last read CT3 line)
 TempCT3=-999; //Temperature measured on the board CT3

 OnTimeCT3=-1;//1/second counter which now gives time since power on (the on-chip batteries have failed; this used to keep incrementing with power off)
 LastCT3=-1;//The last command received by the payload, expressed as a decimal number (it is in HeX on the GUI display)
 CountCT3=-1;//Count of commands received by the payload since power on

 Volt5VCT3=-999;  // Positive 5V from line CT3
 Volt15VCT3=-999; // Positive 15V from line CT3

 //TRIGGER RATES (PHA AND LOGIC) from CT3
 T1L=-1;
 T1A=-1;
 T2L=-1;
 T2A=-1;
 T3L=-1;
 T3A=-1;
 T4L=-1;
 T4A=-1;
 GRDL=-1;
 GRDA=-1;

 //HOUSEKEEPING FROM POW
 yPOW=-1;//Year from POW line linked to the event (last read POW line)
 mPOW=-1;//Month from POW line linked to the event (last read POW line)
 dPOW=-1;//Day from POW line linked to the event (last read POW line)
 hPOW=-1;//Hour from POW line linked to the event (last read POW line)
 miPOW=-1;//Minute from POW line linked to the event (last read POW line)
 sPOW=-1;//Second from POW line linked to the event (last read POW line)
 OnTimePOW=-1;//1/second counter which now gives time since power on (the on-chip batteriePEHFs have failed; this used to keep incrementing with power off)
 MainC=-999;
 MainV=-999;
 HeatC=-999;
 HeatV=-999;
 TrackC=-999;
 TrackV=-999;
 IntPiV=-999;
 IntPiC=-999;
 //From VCI line
 yVCI=-1;//Year from VCI line linked to the event (last read VCI line)
 mVCI=-1;//Month from VCI line linked to the event (last read VCI line)
 dVCI=-1;//Day from VCI line linkedNoisyClus to the event (last read VCI line)
 hVCI=-1;//Hour from VCI line linked to the event (last read VCI line)
 miVCI=-1;//Minute from VCI line linked to the event (last read VCI line)
 sVCI=-1;//Second from VCI line linked to the event (last read VCI line)

}


void ALEvent::Copy(ALEvent* e)
{
 //cout << "Start Copy" << endl;
 //Single variables
 eventnumber =e->get_eventnumber();
 bpdnumber =e->get_bpdnumber();
 
 //PSE1 line
 yPSE1=e->get_yPSE1();
 mPSE1=e->get_mPSE1();
 dPSE1=e->get_dPSE1();
 hPSE1=e->get_hPSE1();
 miPSE1=e->get_miPSE1();
 sPSE1=e->get_sPSE1();
 N=e->get_N();
 Code=e->get_Code();
 nEcho=e->get_nEcho();
 Last=e->get_Last();
 FirstNibble=e->get_FirstNibble();
 runnumber =e->get_runnumber();
 Trigger=e->get_Trigger();
 Stamp=e->get_Stamp();
 Go1=e->get_Go1();
 
 yPSE1b=e->get_yPSE1b();
 mPSE1b=e->get_mPSE1b();
 dPSE1b=e->get_dPSE1b();
 hPSE1b=e->get_hPSE1b();
 miPSE1b=e->get_miPSE1b();
 sPSE1b=e->get_sPSE1b();
   
 this->set_Status(e->get_Status());

   
 //PSE2 line   
 yPSE2=e->get_yPSE2();
 mPSE2=e->get_mPSE2();
 dPSE2=e->get_dPSE2();
 hPSE2=e->get_hPSE2();
 miPSE2=e->get_miPSE2();
 sPSE2=e->get_sPSE2();
     
 sTraxtrig=e->get_sTraxtrig();
 TraxTrig=e->get_TraxTrig();
 TraxComm=e->get_TraxComm();
 TraxPatt=e->get_TraxPatt();
 TotalTrax=e->get_TotalTrax();
 TotalBytes=e->get_TotalBytes();  
 
 
 
 yPHA=e->get_yPHA();
 mPHA=e->get_mPHA();
 dPHA=e->get_dPHA();
 hPHA=e->get_hPHA();
 miPHA=e->get_miPHA();
 sPHA=e->get_sPHA();
 GoPHA=e->get_GoPHA(); 

 tPHA=e->get_tPHA();
 yEVT=e->get_yEVT();
 mEVT=e->get_mEVT();
 dEVT=e->get_dEVT();
 hEVT=e->get_hEVT();
 miEVT=e->get_miEVT();
 sEVT=e->get_sEVT();
 GoEVT=e->get_GoEVT();
 tEVT=e->get_tEVT();
 EVT=e->get_EVT();
 nHitLEVT=e->get_nHitLEVT();
 CCEVT=e->get_CCEVT();
 PatternEVT=e->get_PatternEVT();
 Q1EVT=e->get_Q1EVT();
 TrigEVT=e->get_TrigEVT();
 //cout << "Copy: before layer" << endl;

 for(int i=0;i<8;i++)L[i]=e->get_L(i);
 for(int i=0;i<8;i++)flagL[i]=e->get_flagL(i);


 Status=e->get_Status();
 G =e->get_G();
 TrTrig1=e->get_TrTrig1();
 TrTrig0=e->get_TrTrig0();
 PMTTrig2=e->get_PMTTrig2();
 PMTTrig1=e->get_PMTTrig1();



 //PEHF1,2,3,4 lines
 //HOUSE KEEPING lines
 // cout << "Copy: before EVENT PSOC HOUSEKEEPING " << endl;

 yEPHK1 =e->get_yEPHK1();
 mEPHK1 =e->get_mEPHK1();
 dEPHK1 =e->get_dEPHK1();
 hEPHK1 =e->get_hEPHK1();
 miEPHK1 =e->get_miEPHK1();
 sEPHK1 =e->get_sEPHK1();
 
 yEPHK1b  =e->get_yEPHK1b();
 mEPHK1b  =e->get_mEPHK1b();
 dEPHK1b  =e->get_dEPHK1b();
 hEPHK1b  =e->get_hEPHK1b();
 miEPHK1b =e->get_miEPHK1b();
 sEPHK1b  =e->get_sEPHK1b();
  
 yEPHK4 =e->get_yEPHK4();
 mEPHK4 =e->get_mEPHK4();
 dEPHK4 =e->get_dEPHK4();
 hEPHK4 =e->get_hEPHK4();
 miEPHK4=e->get_miEPHK4();
 sEPHK4 =e->get_sEPHK4();
 
 //PEHF1
 RunEPHK =e->get_RunEPHK(); 
 SourceEPHK =e->get_SourceEPHK();  //Source of the EVENT PSOC HOUSEKEEPING
 //PEHF2
 ComLast =e->get_ComLast();    //Last Command
 ComCount =e->get_ComCount();   //Command Count 
 ComErr =e->get_ComErr();        //Command Error Count
 GenErr =e->get_GenErr();         //General Error Count
 Go =e->get_Go();                 //NUmber of events
 Go1EPHK =e->get_Go1EPHK();         //Number of missing events
 AvgROTime =e->get_AvgROTime();   //Average Readout time in microsec
 //PEHF3
 T1r =e->get_T1r();  //Single rate T1
 T2r =e->get_T2r();  //Single rate T2
 T3r =e->get_T3r();  //Single rate T3
 T4r =e->get_T4r();  //Single rate T4
 Gr =e->get_Gr();   //Single rate Guard
 TrCom =e->get_TrCom();    //Tracker Command Count
 Tr1Pct =e->get_Tr1Pct();   //Percentage of tracker trigger 1
 Tr2Pct =e->get_Tr2Pct();   //Percentage of tracker trigger 2 
 UARTErr =e->get_UARTErr(); //Tracker UART Error Count
 UARTTim =e->get_UARTTim(); //Tracker UART Timeout Count 
 //PEHF4

 for(int i=0;i<8;i++)NhperCh[i]=e->get_NhperCh(i);//hits per layer event*10
 for(int i=0;i<8;i++)Lrate[i]=e->get_Lrate(i);

 //Temperatures:
 PSOCDieTemp=e->get_PSOCDieTemp();
 TempL0 =e->get_TempL0();
 TempL7 =e->get_TempL7();
 //TrackStats
 for(int i=0;i<6;i++)TrackStats[i]=e->get_TrackStats(i);

 Samples=e->get_Samples(); //Number of sample used to calculate PctLive
 PctMaBzy=e->get_PctMaBzy(); 
 PctTrLive=e->get_PctTrLive(); 
 PctADCLive=e->get_PctADCLive(); 

 // cout << "Copy: before MAIN PSOC HOUSEKEEPING " << endl;

 //PMHF1 MAIN PSOC HOUSEKEEPING 
 yMPHK1 =e->get_yMPHK1();
 mMPHK1 =e->get_mMPHK1();
 dMPHK1 =e->get_dMPHK1();
 hMPHK1 =e->get_hMPHK1();
 miMPHK1 =e->get_miMPHK1(); 
 sMPHK1 =e->get_sMPHK1();
 yMPHK1b =e->get_yMPHK1b();
 mMPHK1b =e->get_mMPHK1b();
 dMPHK1b =e->get_dMPHK1b();
 hMPHK1b =e->get_hMPHK1b();
 miMPHK1b =e->get_miMPHK1b(); 
 sMPHK1b =e->get_sMPHK1b();
 DeltaT =e->get_DeltaT();
 SourceMPHK =e->get_SourceMPHK();
 LastCmdMPHK =e->get_LastCmdMPHK();
 CountCmdMPHK =e->get_CountCmdMPHK();
 ErrCmdMPHK =e->get_ErrCmdMPHK();
 ErrGenMPHK =e->get_ErrGenMPHK();
 MissingMPHK =e->get_MissingMPHK();
 FIFOPctMPHK =e->get_FIFOPctMPHK();
 Drop232MPHK =e->get_Drop232MPHK();
 DropUSBMPHK =e->get_DropUSBMPHK();
    
 //PMHF2
 //PMHF2: 07/19/2022 13:29:16 BarCounts: 29028110 1 49972000 29255638 149731314 BarRates:  -198586.8 -274361.6 -200137.7 -272696.6 400.0 0.00 400.0 0.00
 P1MPHK =e->get_P1MPHK();
 P2MPHK =e->get_P2MPHK();
 Temp1MPHK =e->get_Temp1MPHK();
 Temp2MPHK =e->get_Temp2MPHK();
 //PMHF3
 //PMHF3: 07/19/2022 13:29:16 Dp: 2010065 Dt: -2099950 IntPress: 750.24 IntTemp: 42.3 BoardTemp: 43.0 DieTemp: 44.0 Analog: 3.47 147.33 3.32 91.66 5.01 840.30 5.25 4.25 15.24 3.61 2730.47 121.43 
 yMPHK3 =e->get_yMPHK3();
 mMPHK3 =e->get_mMPHK3();
 dMPHK3 =e->get_dMPHK3();
 hMPHK3 =e->get_hMPHK3();
 miMPHK3 =e->get_miMPHK3();
 sMPHK3 =e->get_sMPHK3();
 Dp =e->get_Dp();
 Dt =e->get_Dt();
 IntPress =e->get_IntPress();
 IntTemp =e->get_IntTemp();
 BoardTemp =e->get_BoardTemp();
 DieTemp =e->get_DieTemp();
 Dig3V =e->get_Dig3V();
 Dig3C =e->get_Dig3C();
 Ana3V =e->get_Ana3V();
 Ana3C =e->get_Ana3C();
 Dig5V =e->get_Dig5V();
 Dig5C =e->get_Dig5C();
 Ana5V =e->get_Ana5V();
 Ana5C =e->get_Ana5C();
 Dig15V =e->get_Dig15V();
 TckV =e->get_TckV();
 TckC =e->get_TckC();
 TckbiasC =e->get_TckbiasC();
  
 
 //Dummy layers from ASI from 5.11d
 for(int i=0;i<8;i++)Ldummy[i]=e->get_Ldummy(i);
 
 
 ncase =e->get_ncase();
 typeMC =e->get_typeMC();
 EkMC =e->get_EkMC();
 pMC = e->get_pMC();
 X0MC =e->get_X0MC();
 Y0MC =e->get_Y0MC();
 Z0MC =e->get_Z0MC();
 CX0MC =e->get_CX0MC();
 CY0MC =e->get_CY0MC();
 CZ0MC =e->get_CZ0MC();
 typePP=e->get_typePP();
 EkPP=e->get_EkPP();
 ZenPP=e->get_ZenPP();
 AziPP=e->get_AziPP();
 CoLatSP=e->get_CoLatSP();
 CoLonSP=e->get_CoLonSP();
 Nhits =e->get_Nhits();
 Nhnoisy =e->get_Nhnoisy();
 typereco =e->get_typereco();
 Ekreco =e->get_Ekreco();
 p0reco =e->get_p0reco();
 X0reco =e->get_X0reco();
 Y0reco =e->get_Y0reco();
 Z0reco =e->get_Z0reco();
 CX0reco =e->get_CX0reco();
 CY0reco =e->get_CY0reco();
 CZ0reco =e->get_CZ0reco();
 ndf =e->get_ndf();
 chi2 =e->get_chi2();
 cl =e->get_cl();
 d0 =e->get_d0();
 phi0 =e->get_phi0();
 cpa =e->get_cpa();
 dz =e->get_dz();
 tanl =e->get_tanl();
 phi0_init=get_phi0_init();
 cpa_init=get_cpa_init();
 tanl_init=get_tanl_init();
 d0err2 =e->get_d0err2();
 phi0err2 =e->get_phi0err2();
 cpaerr2 =e->get_cpaerr2();
 dzerr2 =e->get_dzerr2();
 tanlerr2 =e->get_tanlerr2();
 Cov_init = e->get_Cov_init();
 Cov_last = e->get_Cov_last();

 EkPR = e->get_EkPR();
 p0PR = e->get_p0PR();
 aPR = e->get_aPR();
 bPR = e->get_bPR();
 cPR = e->get_cPR();
 interPR = e->get_interPR();
 slopePR = e->get_slopePR();
 chi2BPR = e->get_chi2BPR();
 chi2NBPR = e->get_chi2NBPR();
 clBPR = e->get_clBPR();
 clNBPR = e->get_clNBPR();
 deflecPR = e->get_deflecPR();
 XT1PR =e->get_XT1PR();
 XT3PR =e->get_XT3PR();
 XT4PR =e->get_XT4PR();
 XGPR =e->get_XGPR();
 YT1PR =e->get_YT1PR();
 YT3PR =e->get_YT3PR();
 YT4PR =e->get_YT4PR();
 YGPR =e->get_YGPR();

 thBiPR=e->get_thBiPR();
 thBoPR=e->get_thBoPR();
 thNBPR=e->get_thNBPR();

 // cout << "Copy: before NLPR" << endl;

 for(int i=0;i<8;i++)NLPR[i]=e->get_NLPR(i);

 //T1 =e->get_T1();
 //T2 =e->get_T2();
 //T3 =e->get_T3();
 //T4 =e->get_T4();
 guard =e->get_guard();
 Ti =e->get_Ti();
 Tic =e->get_Tic();
 TiPR =e->get_TiPR();
 NphCK=e->get_NphCK();

 for(int i=0;i<(int)(e->get_posX()).size();i++) posX.push_back((e->get_posX()).at(i));
 for(int i=0;i<(int)(e->get_posY()).size();i++) posY.push_back((e->get_posY()).at(i));
 for(int i=0;i<(int)(e->get_posZ()).size();i++) posZ.push_back((e->get_posZ()).at(i));
 for(int i=0;i<(int)(e->get_posCX()).size();i++) posCX.push_back((e->get_posCX()).at(i));
 for(int i=0;i<(int)(e->get_posCY()).size();i++) posCY.push_back((e->get_posCY()).at(i));
 for(int i=0;i<(int)(e->get_posCZ()).size();i++) posCZ.push_back((e->get_posCZ()).at(i));
 for(int i=0;i<(int)(e->get_posType()).size();i++) posType.push_back((e->get_posType()).at(i));
 for(int i=0;i<(int)(e->get_posAge()).size();i++) posAge.push_back((e->get_posAge()).at(i));
 for(int i=0;i<(int)(e->get_posP()).size();i++) posP.push_back((e->get_posP()).at(i));


 // cout << "Copy: before Vectors" << endl;

 //Vectors of double
 for(int i=0;i<(int)(e->get_EneT1()).size();i++) EneT1.push_back((e->get_EneT1()).at(i));
 for(int i=0;i<(int)(e->get_EneT2()).size();i++) EneT2.push_back((e->get_EneT2()).at(i));
 for(int i=0;i<(int)(e->get_EneT3()).size();i++) EneT3.push_back((e->get_EneT3()).at(i));
 for(int i=0;i<(int)(e->get_EneT4()).size();i++) EneT4.push_back((e->get_EneT4()).at(i));
 for(int i=0;i<(int)(e->get_Eneg()).size();i++) Eneg.push_back((e->get_Eneg()).at(i));
 for(int i=0;i<(int)(e->get_ToF()).size();i++) ToF.push_back((e->get_ToF()).at(i));
 for(int i=0;i<(int)(e->get_timeT1()).size();i++) timeT1.push_back((e->get_timeT1()).at(i));
 for(int i=0;i<(int)(e->get_timeT2()).size();i++) timeT2.push_back((e->get_timeT2()).at(i));
 for(int i=0;i<(int)(e->get_timeT3()).size();i++) timeT3.push_back((e->get_timeT3()).at(i));
 for(int i=0;i<(int)(e->get_timeT4()).size();i++) timeT4.push_back((e->get_timeT4()).at(i));
 for(int i=0;i<(int)(e->get_timeg()).size();i++) timeg.push_back((e->get_timeg()).at(i));
 for(int i=0;i<(int)(e->get_EneIsofoam()).size();i++) EneIsofoam.push_back((e->get_EneIsofoam()).at(i));
 for(int i=0;i<(int)(e->get_EneShell()).size();i++) EneShell.push_back((e->get_EneShell()).at(i));
 for(int i=0;i<(int)(e->get_timeIsofoam()).size();i++) timeIsofoam.push_back((e->get_timeIsofoam()).at(i));
 for(int i=0;i<(int)(e->get_timeShell()).size();i++) timeShell.push_back((e->get_timeShell()).at(i));
 for(int i=0;i<(int)(e->get_XT1()).size();i++) XT1.push_back((e->get_XT1()).at(i));
 for(int i=0;i<(int)(e->get_XT3()).size();i++) XT3.push_back((e->get_XT3()).at(i));
 for(int i=0;i<(int)(e->get_XT4()).size();i++) XT4.push_back((e->get_XT4()).at(i));
 for(int i=0;i<(int)(e->get_YT1()).size();i++) YT1.push_back((e->get_YT1()).at(i));
 for(int i=0;i<(int)(e->get_YT3()).size();i++) YT3.push_back((e->get_YT3()).at(i));
 for(int i=0;i<(int)(e->get_YT4()).size();i++) YT4.push_back((e->get_YT4()).at(i));
 //Vectors of ALTckhit
 for(int i=0;i<(int)(e->get_hits()).size();i++) hits.push_back((e->get_hits()).at(i));
 //HOUSEKEEPING FROM COUNTERS 1 AND 3
 yCT1  = e->get_yCT1();
 mCT1  = e->get_mCT1();
 dCT1  = e->get_dCT1();
 hCT1  = e->get_hCT1();
 miCT1  = e->get_miCT1();
 sCT1  = e->get_sCT1();
 TempCT1  = e->get_TempCT1();
 OnTimeCT1  = e->get_OnTimeCT1();
 LastCT1  = e->get_LastCT1();
 CountCT1  = e->get_CountCT1();
 Baro1T  = e->get_Baro1T();
 Baro1P  = e->get_Baro1P();
 Baro2T  = e->get_Baro2T();
 Baro2P  = e->get_Baro2P();
 TempB1  = e->get_TempB1();
 TempB2  = e->get_TempB2();
 PressB1  = e->get_PressB1();
 PressB2  = e->get_PressB2();
 GOCT1=  e->get_GOCT1();
 coinCT1=  e->get_coinCT1();
 Volt5VCT1  = e->get_Volt5VCT1();
 Volt15VCT1  = e->get_Volt15VCT1();
 yCT3  = e->get_yCT3();
 mCT3  = e->get_mCT3();
 dCT3  = e->get_dCT3();
 hCT3  = e->get_hCT3();
 miCT3  = e->get_miCT3();
 sCT3  = e->get_sCT3();
 TempCT3  = e->get_TempCT3();
 OnTimeCT3  = e->get_OnTimeCT3();
 LastCT3  = e->get_LastCT3();
 CountCT3  = e->get_CountCT3();
 T1L  = e->get_T1L();
 T1A  = e->get_T1A();
 T2L  = e->get_T2L();
 T2A  = e->get_T2A();
 T3L  = e->get_T3L();
 T3A  = e->get_T3A();
 T4L  = e->get_T4L();
 T4A  = e->get_T4A();
 GRDL  = e->get_GRDL();
 GRDA  = e->get_GRDA();

 Volt5VCT3  = e->get_Volt5VCT3();
 Volt15VCT3  = e->get_Volt15VCT3();
 //HOUSEKEEPING FROM POW
 yPOW= e->get_yPOW();
 mPOW= e->get_mPOW();
 dPOW= e->get_dPOW();
 hPOW= e->get_hPOW();
 miPOW= e->get_miPOW();
 sPOW= e->get_sPOW();
 OnTimePOW= e->get_OnTimePOW();
 MainC= e->get_MainC();
 MainV= e->get_MainV();
 HeatC= e->get_HeatC();
 HeatV= e->get_HeatV();
 TrackC= e->get_TrackC();
 TrackV= e->get_TrackV();
 IntPiV= e->get_IntPiV();
 IntPiC=e->get_IntPiC();
 
 //from VCI line
 yVCI= e->get_yVCI();
 mVCI= e->get_mVCI();
 dVCI= e->get_dVCI();
 hVCI= e->get_hVCI();
 miVCI= e->get_miVCI();
 sVCI= e->get_sVCI();
 
 //  cout << "Copy: before Lrate" << endl;

 //for(int i=0;i<8;i++)Lrate[i]=e->get_Lrate(i);
 //cout << "Copy: after Lrate" << endl;

}
////////////////////////////////
//Methods to get number of layerS and layer with hits
////////////////////////////////

int ALEvent::get_NLayers()
 {
  uint8_t tmpTi=(uint8_t)Ti;
 // cout << "get_NLayers tmpTi = " << unsigned(tmpTi) << endl;
  int NL=0;
  for(int ij=0;ij<8;ij++) NL+=(int)((tmpTi >>ij) & 0x01);
  return NL;
 }
int ALEvent::get_Layer(int i)
 {
  uint8_t tmpTi=(uint8_t)Ti;
  int Ni=0;
  if(i<8) Ni=(int)((tmpTi >>i) & 0x01);
 // cout << " Layer " << i << " Ni = " << Ni << endl;
  return Ni;
 }
void ALEvent::get_Layers(int*Lay)
 {
  uint8_t tmpTi=(uint8_t)Ti;
  // cout << "get_Layers tmpTi = " << unsigned(tmpTi) << endl;
  for(int ij=0;ij<8;ij++) Lay[ij]=(int)((tmpTi >>ij) & 0x01);
 }


 int ALEvent::get_NLayersc()
  {
   uint8_t tmpTi=(uint8_t)Tic;
  // cout << "get_NLayers tmpTi = " << unsigned(tmpTi) << endl;
   int NL=0;
   for(int ij=0;ij<8;ij++) NL+=(int)((tmpTi >>ij) & 0x01);
   return NL;
  }
 int ALEvent::get_Layerc(int i)
  {
   uint8_t tmpTi=(uint8_t)Tic;
   int Ni=0;
   if(i<8) Ni=(int)((tmpTi >>i) & 0x01);
  // cout << " Layer " << i << " Ni = " << Ni << endl;
   return Ni;
  }
 void ALEvent::get_Layersc(int*Lay)
  {
   uint8_t tmpTi=(uint8_t)Tic;
   // cout << "get_Layers tmpTi = " << unsigned(tmpTi) << endl;
   for(int ij=0;ij<8;ij++) Lay[ij]=(int)((tmpTi >>ij) & 0x01);
  }


int ALEvent::get_NLayersPR()
 {
  uint8_t tmpTi=(uint8_t)TiPR;
 // cout << "get_NLayers tmpTi = " << unsigned(tmpTi) << endl;
  int NL=0;
  for(int ij=0;ij<8;ij++) NL+=(int)((tmpTi >>ij) & 0x01);
  return NL;
 }
int ALEvent::get_LayerPR(int i)
 {
  uint8_t tmpTi=(uint8_t)TiPR;
  int Ni=0;
  if(i<8) Ni=(int)((tmpTi >>i) & 0x01);
 // cout << " Layer " << i << " Ni = " << Ni << endl;
  return Ni;
 }
void ALEvent::get_LayersPR(int*Lay)
 {
  uint8_t tmpTi=(uint8_t)TiPR;
  // cout << "get_Layers tmpTi = " << unsigned(tmpTi) << endl;
  for(int ij=0;ij<8;ij++) Lay[ij]=(int)((tmpTi >>ij) & 0x01);
 }
