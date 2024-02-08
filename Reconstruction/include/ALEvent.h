//////////////////////////////////////////////////////////////////////////////////////////
///    Author: Pierre-Simon Mangeard, psmangeard@gmail.com
///    Department of Physics and Astronomy, University of Delaware, October 28, 2016
///				Sarah Mechbal, smechbal@ucsc.edu
////   Department of Physics, University of California Santa Cruz
////   November 16,2022: Major upgrade and cleaning for AESOP-Lite 2
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ALEVENT__
#define __ALEVENT__
#include "headers.h"
#include "ALTckhit.h"
#include "tools.h"


class ALEvent:public TObject
{
 private:

   int eventnumber; //Event number
   int bpdnumber; //bpd file number

   //Data FROM "PSE1" LINE, trigger information

   int yPSE1;//Year from PSE1 line linked to the event
   int mPSE1;//Month from PSE1 line linked to the event
   int dPSE1;//Day from PSE1 line linked to the event
   int hPSE1;//Hour from PSE1 line linked to the event
   int miPSE1;//Minute from PSE1 line linked to the event
   int sPSE1;//Second from PSE1 line linked to the event
   int N;//N: 92
   int Code;//Code: 221
   int nEcho;//nEcho: 0
   int Last;//Last: 32
   int FirstNibble;//ZERO FirstNibble: 15
   int runnumber;//run number
   int Trigger;//triggered event number in run runnumber
   int Stamp;//time

   int Go1;//Number of missing events due to Readout dead time
   int yPSE1b;//Year from Date/Time PSE1 line linked to the event
   int mPSE1b;//Month from Date/Time PSE1 line linked to the event
   int dPSE1b;//Day from Date/Time PSE1 line linked to the event
   int hPSE1b;//Hour from Date/Time PSE1 line linked to the event
   int miPSE1b;//Minute from Date/Time PSE1 line linked to the event
   int sPSE1b;//Second from Date/Time PSE1 line linked to the event
   unsigned Status;      //8-bit trigger word: T4 T3 T2 T1 Guard Trackertrigger1 Trackertrigger0 PMTsecondary PMTprimary  
   //Online Triggers status from Status:
   bool T4;
   bool T3;
   bool T2;
   bool T1;
   bool TrTrig1;
   bool TrTrig0;
   bool PMTTrig2;
   bool PMTTrig1;
   bool G;

   //Data FROM "PSE2" LINE, some tracker information
   
   int yPSE2=-1;//Year from PSE2 line linked to the event
   int mPSE2=-1;//Month from PSE2 line linked to the event
   int dPSE2=-1;//Day from PSE2 line linked to the event
   int hPSE2=-1;//Hour from PSE2 line linked to the event
   int miPSE2=-1;//Minute from PSE2 line linked to the event
   int sPSE2=-1;//Second from PSE2 line linked to the event
  
   int sTraxtrig=-1;//sTraxTrig: 0032
   int TraxTrig=-1;//TraxTrig: 50
   int TraxComm=-1;//TraxComm: 132
   int TraxPatt=-1;//TraxPatt: 215 
   int TotalTrax=-1;//TotalTrax: 8 
   int TotalBytes=-1;//TotalBytes: 14500 FINI

 
   //PEHF1,2,3,4 lines
   //EVENT PSOC HOUSE KEEPING lines
   //If time of line 1 and time of line 4 are different then there is an issue
   //PEHF1: 09/29/2022 16:28:46 Date: 01/01/2001 01:01:43 Run: 1 Source: FF00FF
   //PEHF2: 09/29/2022 16:28:46 ComLast: 0AB6 ComCount: 149 ComErr: 0 GenErr: 2 Go: 5 Go1: 0 AvgROTime: 224
   //PEHF3: 09/29/2022 16:28:46 Rates:  149 1323 396 75 318 TrCom: 224 Tr1Pct: 80 Tr2Pct: 20 UARTErr: 0 UARTTim: 0
//PEHF4: 11/10/2023 19:22:54 Chips:  7 7 7 6 6 5 5 5 OrRates:  15 341 179 119 4 6 7 7 Temps:  35.0 24.5 22.1 TrackStats:  0 0 0 0 PctMaBzy: 0.0 PctTrLive: 0.0 Samples: 39352 PctADCLive: 99.0

   int yEPHK1;//Year from PEHF1 line linked to the event
   int mEPHK1;//Month from PEHF1 line linked to the event
   int dEPHK1;//Day from PEHF1 line linked to the event
   int hEPHK1;//Hour from PEHF1 line linked to the event
   int miEPHK1;//Minute from PEHF1 line linked to the event 
   int sEPHK1;//Second from PEHF1 line linked to the event
   int yEPHK1b;//Year from PEHF1 line Date linked to the event
   int mEPHK1b;//Month from PEHF1 line Date linked to the event
   int dEPHK1b;//Day from PEHF1 line Date linked to the event
   int hEPHK1b;//Hour from PEHF1 line Date linked to the event
   int miEPHK1b;//Minute from PEHF1 line Date linked to the event
   int sEPHK1b;//Second from PEHF1 line Date linked to the event
  
   int yEPHK4;//Year from PEHF4 line linked to the event
   int mEPHK4;//Month from PEHF4 line linked to the event
   int dEPHK4;//Day from PEHF4 line linked to the event
   int hEPHK4;//Hour from PEHF4 line linked to the event
   int miEPHK4;//Minute from PEHF4 line linked to the event
   int sEPHK4;//Second from PEHF4 line linked to the event 
 
   //PEHF1  EVENT PSOC HOUSEKEEPING HIGH RATE
   int RunEPHK; 
   string SourceEPHK;   //Source of the EVENT PSOC HOUSEKEEPING
   //PEHF2
   string ComLast;     //Last Command
   int ComCount;    //Command Count 
   int ComErr;     //Command Error Count
   int GenErr;      //General Error Count
   int Go;          //NUmber of events
   int Go1EPHK;      //Number of missing events
   int AvgROTime;   //Average Readout time in microsec
   //PEHF3
   int T1r; //Single rate T1
   int T2r; //Single rate T2
   int T3r; //Single rate T3
   int T4r; //Single rate T4
   int Gr;  //Single rate Guard
   int TrCom;   //Tracker Command Count
   int Tr1Pct;   //Percentage of tracker trigger 1
   int Tr2Pct;   //Percentage of tracker trigger 2 
   int UARTErr;   //Tracker UART Error Count
   int UARTTim;   //Tracker UART Timeout Count 
   //PEHF4
   int NhperCh[8];   //hits per layer event*10
   int Lrate[8];     //Tracker Layer rate 
   int Ldummy[8];     //dummy Layerfrom ASI
 
   //Temperatures:
   float PSOCDieTemp;
   float TempL0;
   float TempL7; 
   //TrackStats
   float TrackStats[6]; //Tracker Stat
   // It contains:
   //average number of Channel-A TOF hits per event
   //average number of Channel-B TOF hits per event
   //maximum number of Channel-A TOF hits in one event
   //maximum number of Channel-B TOF hits in one event
   //percent Main-PSOC busy fraction
   //percent trigger live fraction
    
   int Samples; //Number of sample used to calculate PctLive  
   float PctMaBzy;
   float PctTrLive;
   float PctADCLive;
  
   
   
   //PMHF1 MAIN PSOC HOUSEKEEPING 
   //PMHF1: 07/19/2022 13:29:16 Date: 07/19/2022 13:29:07 DeltaT: 5716.00 Source: FF00FF LastCmd: 0320 CountCmd: 2 ErrCmd: 0 ErrGen: 12 Missing: 0 FIFOPct: 0 Drop232: 0 DropUSB: 0 
   int yMPHK1;//Year from PMHF1 line linked to the event
   int mMPHK1;//Month from PMHF1 line linked to the event
   int dMPHK1;//Day from PMHF1 line linked to the event
   int hMPHK1;//Hour from PMHF1 line linked to the event
   int miMPHK1;//Minute from PMHF1 line linked to the event 
   int sMPHK1;//Second from PMHF1 line linked to the event
   int yMPHK1b;//Year from PMHFb1 line linked to the event
   int mMPHK1b;//Month from PMHF1b line linked to the event
   int dMPHK1b;//Day from PMHF1b line linked to the event
   int hMPHK1b;//Hour from PMHF1b line linked to the event
   int miMPHK1b;//Minute from PMHF1b line linked to the event 
   int sMPHK1b;//Second from PMHF1b line linked to the event
   float DeltaT;
   string SourceMPHK;
   int LastCmdMPHK;
   int CountCmdMPHK;
   int ErrCmdMPHK;
   int ErrGenMPHK;
   int MissingMPHK;//PSOC Live time percentage using N Samples between the last 2 events
   int FIFOPctMPHK;
   int Drop232MPHK;
   int DropUSBMPHK;
    
   //PMHF2
   //PMHF2: 07/19/2022 13:29:16 BarCounts: 29028110 149972000 29255638 149731314 BarRates:  -198586.8 -274361.6 -200137.7 -272696.6 400.0 0.00 400.0 0.00
   //int BarCounts[4];
   //int BarRate[4];
   float P1MPHK; 
   float P2MPHK; 
   float Temp1MPHK; 
   float Temp2MPHK; 

   //PMHF3
   //PMHF3: 07/19/2022 13:29:16 Dp: 2010065 Dt: -2099950 IntPress: 750.24 IntTemp: 42.3 BoardTemp: 43.0 DieTemp: 44.0 Analog: 3.47 147.33 3.32 91.66 5.01 840.30 5.25 4.25 15.24 3.61 2730.47 121.43 
   int yMPHK3;//Year from PMHF3 line linked to the event
   int mMPHK3;//Month from PMHF3 line linked to the event
   int dMPHK3;//Day from PMHF3 line linked to the event
   int hMPHK3;//Hour from PMHF3 line linked to the event
   int miMPHK3;//Minute from PMHF3 line linked to the event 
   int sMPHK3;//Second from PMHF3 line linked to the event
   int Dp;
   int Dt;
   float IntPress;
   float IntTemp;
   float BoardTemp;
   float DieTemp;
   float Dig3V;
   float Dig3C;
   float Ana3V;
   float Ana3C;
   float Dig5V;
   float Dig5C;
   float Ana5V;
   float Ana5C;
   float Dig15V;
   float TckV;
   float TckC;
   float TckbiasC;

   //Data FROM "PSE1" LINE, trigger information
   int yPHA;//Year from PSE1 line linked to the event
   int mPHA;//Month from PSE1 line linked to the event
   int dPHA;//Day from PSE1 line linked to the event
   int hPHA;//Hour from PSE1 line linked to the event
   int miPHA;//Minute from PSE1 line linked to the event
   int sPHA;//Second from PSE1 line linked to the event
   double GoPHA;//Go counter
   double tPHA;//timer

   //Data FROM "EVT" LINE, tracker information
   int yEVT;//Year from EVT line linked to the event
   int mEVT;//Month from EVT line linked to the event
   int dEVT;//Day from EVT line linked to the event
   int hEVT;//Hour from EVT line linked to the event
   int miEVT;//Minute from EVT line linked to the event
   int sEVT;//Second from EVT line linked to the event
   string EVT; //Data from EVT line linked to the event
   double GoEVT;//Go counter
   double tEVT;//timer

   int nHitLEVT;//nHitL from EVT line linked to the event added 12/05/2017
   int CCEVT;//CC from EVT line linked to the event   added 12/05/2017
   int PatternEVT;//CC from EVT line linked to the event   added 12/05/2017
   int Q1EVT;//Q1 from EVT line linked to the event   added 12/05/2017
   double TrigEVT;//Q1 from EVT line linked to the event   added 12/05/2017

   //Data FROM "ASI" LINE
   string L[8];//Data from  ASI lines of the event
   int flagL[8];//1 if ASI line was present

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
   //Read FROM "PSE1" LINE
   //From April 4th 2022
   //unsigned Status;      //8-bit trigger word: 000 Guard Trackertrigger1 Trackertrigger0 PMTsecondary PMTprimary  
   //individual boolen trigger
   //bool TrTrig1;
   //bool TrTrig0;
   //bool PMTTrig2;
   //bool PMTTrig1;
   //Time
   //int Stamp; //added on June 21st 2022 
   //PSOC time from PSE1 line Data/Time
   //int yPSO;//Year from PSE1 line linked to the event
   //int mPSO;//Month from PSE1 line linked to the event
   //int dPSO;//Day from PSE1 line linked to the event
   //int hPSO;//Hour from PSE1 line linked to the event
   //int miPSO;//Minute from PSE1 line linked to the event
   //int sPSO;//Second from PSE1 line linked to the event
   //int Go1; //Number of missing events due to Readout dead time
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   //Monte Carlo information: Truth variable names finish with MC
   int ncase;
   int typeMC; 					//type of particle
   double EkMC;   				//kinetic energy of the particle at injection point
   double pMC;	        			//momentum of particle at injection point
   double X0MC,Y0MC,Z0MC;			//Coordinates of the partcle at the injection point
   double CX0MC,CY0MC,CZ0MC; 			//Incidence cosines of the partcle at the injection point
   int typePP;

   double EkPP;
   double ZenPP;
   double AziPP;
   double CoLatSP;
   double CoLonSP;
   int Nhits; 					//Number of hits in the event (MC && data)

   int Nhnoisy;//Number of hits with noisy channel added 23/10/2019

   //Pattern Recognition info

   double EkPR, p0PR;				//kinetic energy and momentum of particle from least squares fit
   double chi2NBPR, chi2BPR, clNBPR, clBPR;	//chi2 of parabolic/linear fit in bending/nonbending plane
   double aPR, bPR, cPR;			//parameters of parabolic fit ( y(x) = c + bx + ax*x)
   double slopePR, interPR;			//parameters of linear fit
   double deflecPR;                       	//deflection from layer 2 to layer 6 in the beding plane: Difference of the slope of straight line

   //Extrapolated positions of the PR track in the scintillators
   float XT1PR;
   float XT3PR;
   float XT4PR;
   float XGPR;
   float YT1PR;
   float YT3PR;
   float YT4PR;
   float YGPR;
   float thBiPR;//theta incoming in BP from PR
   float thBoPR;//theta outcoming in BP from PR
   float thNBPR;//theta  in BP from PR
   int NLPR[8];    //Number of hits per layer with max 3 strips that pass geometry cuts for PR
   int TiPR;//Same as Ti for hits with a maximum of 3 strips and pass geometry cuts

   //Reconstruction information: variables finish with reco
   int typereco;                    		//type of particle
   double Ekreco, p0reco;           		//kinetic energy and momentum of the particle
   double X0reco,Y0reco,Z0reco;     		//Coordinates of the partocle at the injection point
   double CX0reco,CY0reco,CZ0reco;  		//Incidence cosines of the particle at the injection point
   int ndf;                         		// number of degrees of freedom
   double chi2, cl;                 		//chi2 of fit and confidence level (cl = Prob(chi2, ndf)
   double d0, phi0, cpa, dz, tanl;  		//reconstructed helical track parameters
   double phi0_init, cpa_init, tanl_init;  	//initial helical track parameters
   double d0err2, phi0err2, cpaerr2, dzerr2, tanlerr2; //err^2 of track parameters
   TMatrixD Cov_init, Cov_last;			//covariance matrix at initialization and last site

   //Hits information
   std::vector<ALTckhit*> hits;

   //NEW: all segments informations for MC (full position & directional cosines & momentum & age & type)
   std::vector<float> posX;
   std::vector<float> posY;
   std::vector<float> posZ;
   std::vector<float> posCX;
   std::vector<float> posCY;
   std::vector<float> posCZ;
   std::vector<float> posType;
   std::vector<float> posAge;
   std::vector<float> posP;
   //External Triggers
   bool guard;
   //Energy for MC, PHA pulse height for data
   std::vector<double> EneT1;
   std::vector<double> EneT2;
   std::vector<double> EneT3;
   std::vector<double> EneT4;
   std::vector<double> Eneg;
   std::vector<double> ToF; //Time of flight
   //For MC, position of particles in the scintillators
   std::vector<double> XT1;
   std::vector<double> XT3;
   std::vector<double> XT4;
   std::vector<double> YT1;
   std::vector<double> YT3;
   std::vector<double> YT4;
   //For MC, energy deposit in insulation and shell
   std::vector<double> EneIsofoam;
   std::vector<double> EneShell;

   //Timing for MC, Not available for data
   std::vector<double> timeT1;
   std::vector<double> timeT2;
   std::vector<double> timeT3;
   std::vector<double> timeT4;
   std::vector<double> timeg;
   std::vector<double> timeIsofoam;
   std::vector<double> timeShell;

   //MC: Number of optical photons produced in T2 (20/05/2019: For testing CK in MC, not sure it is working fine in Fluka yet)
   int NphCK;

   //Internal Triggers
   //Tracker layer for 0 to 7. top layer is 0
   //integer value coded with 7 bits values
   //\Sum\Limits_{k=0}^{7} 2^k
   int Ti;
   int Tic;//Same as Ti for hits with a maximum of 3 strips
 

   //HOUSEKEEPING FROM COUNTERS 1 AND 3
   //Data FROM "CT1" LINE
   int yCT1;//Year from CT1 line linked to the event (last read CT1 line)
   int mCT1;//Month from CT1 line linked to the event (last read CT1 line)
   int dCT1;//Day from CT1 line linked to the event (last read CT1 line)
   int hCT1;//Hour from CT1 line linked to the event (last read CT1 line)
   int miCT1;//Minute from CT1 line linked to the event (last read CT1 line)
   int sCT1;//Second from CT1 line linked to the event (last read CT1 line)
   float TempCT1; //Temperature measured on the board CT1

   int OnTimeCT1;//1/second counter which now gives time since power on (the on-chip batteries have failed; this used to keep incrementing with power off)
   int LastCT1;//The last command received by the payload, expressed as a decimal number (it is in HeX on the GUI display)
   int CountCT1;//Count of commands received by the payload since power on

   //Barometer information: NOT INTERPRETED from line CT1
   float Baro1T;//Barometer 1 Temperature
   float Baro1P;//Barometer 1 Pressure
   float Baro2T;//Barometer 2 Temperature
   float Baro2P;//Barometer 2 Pressure
   //Barometer information: INTERPRETED from line CT1
   float TempB1;//Barometer 1 Temperature
   float TempB2;//Barometer 2 Temperature
   float PressB1;//Barometer 1 Pressure
   float PressB2;//Barometer 2 Pressure

   float GOCT1;
   float coinCT1;

   //Voltages
   float Volt5VCT1;  // Positive 5V from line CT1
   float Volt15VCT1; // Positive 15V from line CT1

   //Data FROM "CT3" LINE
   int yCT3;//Year from CT3 line linked to the event (last read CT3 line)
   int mCT3;//Month from CT3 line linked to the event (last read CT3 line)
   int dCT3;//Day from CT3 line linked to the event (last read CT3 line)
   int hCT3;//Hour from CT3 line linked to the event (last read CT3 line)
   int miCT3;//Minute from CT3 line linked to the event (last read CT3 line)
   int sCT3;//Second from CT3 line linked to the event (last read CT3 line)
   float TempCT3; //Temperature measured on the board CT3

   int OnTimeCT3;//1/second counter which now gives time since power on (the on-chip batteries have failed; this used to keep incrementing with power off)
   int LastCT3;//The last command received by the payload, expressed as a decimal number (it is in HeX on the GUI display)
   int CountCT3;//Count of commands received by the payload since power on

   //Voltages
   float Volt5VCT3=-999;  // Positive 5V from line CT3
   float Volt15VCT3=-999; // Positive 15V from line CT3

   //TRIGGER RATES (PHA AND LOGIC) from CT3
   float T1L;
   float T1A;
   float T2L;
   float T2A;
   float T3L;
   float T3A;
   float T4L;
   float T4A;
   float GRDL;
   float GRDA;

   //Data from "VCI" LINE added 23/10/2019
   int yVCI;//Year from VCI line linked to the event (last read VCI line)
   int mVCI;//Month from VCI line linked to the event (last read VCI line)
   int dVCI;//Day from VCI line linked to the event (last read VCI line)
   int hVCI;//Hour from VCI line linked to the event (last read VCI line)
   int miVCI;//Minute from VCI line linked to the event (last read VCI line)
   int sVCI;//Second from VCI line linked to the event (last read VCI line)
   //int Lrate[8];    //Tracker Layer rate  from the last VCI read line



   //HOUSEKEEPING FROM POW
   int yPOW;//Year from POW line linked to the event (last read POW line)
   int mPOW;//Month from POW line linked to the event (last read POW line)
   int dPOW;//Day from POW line linked to the event (last read POW line)
   int hPOW;//Hour from POW line linked to the event (last read POW line)
   int miPOW;//Minute from POW line linked to the event (last read POW line)
   int sPOW;//Second from POW line linked to the event (last read POW line)
   int OnTimePOW;//1/second counter which now gives time since power on (the on-chip batteries have failed; this used to keep incrementing with power off)
   float MainC;
   float MainV;
   float HeatC;
   float HeatV;
   float TrackC;
   float TrackV;
   float IntPiV;
   float IntPiC;
 
 public:
   //Constructors
   ALEvent();// Default
   //Destructor
   ~ALEvent(){};
   ///////////////////////////////
   // Methods
   ///////////////////////////////
   void Copy(ALEvent*);
   ////////////////////////////////
   //"setting" member methods
   ////////////////////////////////
   void set_eventnumber(int a){eventnumber=a;}
   void set_bpdnumber(int a){bpdnumber=a;}

   //PSE1 line
   void set_yPSE1(int a){yPSE1=a;}
   void set_mPSE1(int a){mPSE1=a;}
   void set_dPSE1(int a){dPSE1=a;}
   void set_hPSE1(int a){hPSE1=a;}
   void set_miPSE1(int a){miPSE1=a;}
   void set_sPSE1(int a){sPSE1=a;}
   void set_N(int a){N=a;}
   void set_Code(int a){Code=a;}
   void set_nEcho(int a){nEcho=a;}
   void set_Last(int a){Last=a;}
   void set_FirstNibble(int a){FirstNibble=a;}
   void set_runnumber(int a){runnumber=a;}
   void set_Trigger(int a){Trigger=a;}
   void set_Stamp(int a){Stamp=a;}
   void set_Go1(int a){Go1=a;}
 
   void set_yPSE1b(int a){yPSE1b=a;}
   void set_mPSE1b(int a){mPSE1b=a;}
   void set_dPSE1b(int a){dPSE1b=a;}
   void set_hPSE1b(int a){hPSE1b=a;}
   void set_miPSE1b(int a){miPSE1b=a;}
   void set_sPSE1b(int a){sPSE1b=a;}
   
   void set_Status(unsigned a)
       {
        Status=a;
        T4=bool(Status &0x80);
        T3=bool(Status &0x40);
        T2=bool(Status &0x20);
        T1=bool(Status &0x10);
        TrTrig1=bool(Status & 0x08);
        TrTrig0=bool(Status & 0x04);
        PMTTrig2=bool(Status & 0x02);
        PMTTrig1=bool(Status & 0x01);
       }  
   
   //PSE2 line   
   void set_yPSE2(int a){yPSE2=a;}
   void set_mPSE2(int a){mPSE2=a;}
   void set_dPSE2(int a){dPSE2=a;}
   void set_hPSE2(int a){hPSE2=a;}
   void set_miPSE2(int a){miPSE2=a;}
   void set_sPSE2(int a){sPSE2=a;}
     
   void set_sTraxtrig(int a){sTraxtrig=a;}
   void set_TraxTrig(int a){TraxTrig=a;}
   void set_TraxComm(int a){TraxComm=a;}
   void set_TraxPatt(int a){TraxPatt=a;} 
   void set_TotalTrax(int a){TotalTrax=a;} 
   void set_TotalBytes(int a){TotalBytes=a;}

   //PEHF1,2,3,4 lines
   //HOUSE KEEPING lines

   void set_yEPHK1(int a){yEPHK1=a;}
   void set_mEPHK1(int a){mEPHK1=a;}
   void set_dEPHK1(int a){dEPHK1=a;}
   void set_hEPHK1(int a){hEPHK1=a;}
   void set_miEPHK1(int a){miEPHK1=a;}
   void set_sEPHK1(int a){sEPHK1=a;}
 
   void set_yEPHK1b(int a){yEPHK1b=a;}
   void set_mEPHK1b(int a){mEPHK1b=a;}
   void set_dEPHK1b(int a){dEPHK1b=a;}
   void set_hEPHK1b(int a){hEPHK1b=a;}
   void set_miEPHK1b(int a){miEPHK1b=a;}
   void set_sEPHK1b(int a){sEPHK1b=a;}
  
   void set_yEPHK4(int a){yEPHK4=a;}
   void set_mEPHK4(int a){mEPHK4=a;}
   void set_dEPHK4(int a){dEPHK4=a;}
   void set_hEPHK4(int a){hEPHK4=a;}
   void set_miEPHK4(int a){miEPHK4=a;}
   void set_sEPHK4(int a){sEPHK4=a;}
 
   //PEHF1
   void set_RunEPHK(int a){RunEPHK=a;} 
   void set_SourceEPHK(string a){SourceEPHK=a;}   //Source of the EVENT PSOC HOUSEKEEPING
   //PEHF2
   void set_ComLast(string a){ComLast=a;}     //Last Command
   void set_ComCount(int a){ComCount=a;}      //Command Count 
   void set_ComErr(int a){ComErr=a;}          //Command Error Count
   void set_GenErr(int a){GenErr=a;}          //General Error Count
   void set_Go(int a){Go=a;}                  //NUmber of events
   void set_Go1EPHK(int a){Go1EPHK=a;}         //Number of missing events
   void set_AvgROTime(int a){AvgROTime=a;}    //Average Readout time in microsec
   //PEHF3
   void set_T1r(int a){T1r=a;}  //Single rate T1
   void set_T2r(int a){T2r=a;}  //Single rate T2
   void set_T3r(int a){T3r=a;}  //Single rate T3
   void set_T4r(int a){T4r=a;}  //Single rate T4
   void set_Gr(int a){Gr=a;}    //Single rate Guard
   void set_TrCom(int a){TrCom=a;}     //Tracker Command Count
   void set_Tr1Pct(int a){Tr1Pct=a;}   //Percentage of tracker trigger 1
   void set_Tr2Pct(int a){Tr2Pct=a;}   //Percentage of tracker trigger 2 
   void set_UARTErr(int a){UARTErr=a;} //Tracker UART Error Count
   void set_UARTTim(int a){UARTTim=a;} //Tracker UART Timeout Count 
   //PEHF4
   void set_NhperCh(int k, int a){if(k<8)NhperCh[k]=a;}  //hits per layer event*10
   void set_Lrate(int k, int a){if(k<8)Lrate[k]=a;}      //Tracker Layer rate  
   //Temperatures:
   void set_PSOCDieTemp(float a){PSOCDieTemp=a;}
   void set_TempL0(float a){TempL0=a;}
   void set_TempL7(float a){TempL7=a;}
   //TrackStats
   void set_TrackStats(int k, float a){if(k<6)TrackStats[k]=a;} //Tracker Stat
   void set_Samples(int a){Samples=a;}  //Number of sample used to calculate PctLive
   void set_PctADCLive(float a){PctADCLive=a;} 
   void set_PctMaBzy(float a){PctMaBzy=a;} 
   void set_PctTrLive(float a){PctTrLive=a;} 

   //PMHF1 MAIN PSOC HOUSEKEEPING 
   //PMHF1: 07/19/2022 13:29:16 Date: 07/19/2022 13:29:07 DeltaT: 5716.00 Source: FF00FF LastCmd: 0320 CountCmd: 2 ErrCmd: 0 ErrGen: 12 Missing: 0 FIFOPct: 0 Drop232: 0 DropUSB: 0 
   void set_yMPHK1(int a){yMPHK1=a;}//Year from PMHF1 line linked to the event
   void set_mMPHK1(int a){mMPHK1=a;}//Month from PMHF1 line linked to the event
   void set_dMPHK1(int a){dMPHK1=a;}//Day from PMHF1 line linked to the event
   void set_hMPHK1(int a){hMPHK1=a;}//Hour from PMHF1 line linked to the event
   void set_miMPHK1(int a){miMPHK1=a;}//Minute from PMHF1 line linked to the event 
   void set_sMPHK1(int a){sMPHK1=a;}//Second from PMHF1 line linked to the event
   void set_yMPHK1b(int a){yMPHK1b=a;}//Year from PMHFb1 line linked to the event
   void set_mMPHK1b(int a){mMPHK1b=a;}//Month from PMHF1b line linked to the event
   void set_dMPHK1b(int a){dMPHK1b=a;}//Day from PMHF1b line linked to the event
   void set_hMPHK1b(int a){hMPHK1b=a;}//Hour from PMHF1b line linked to the event
   void set_miMPHK1b(int a){miMPHK1b=a;}//Minute from PMHF1b line linked to the event 
   void set_sMPHK1b(int a){sMPHK1b=a;}//Second from PMHF1b line linked to the event
   void set_DeltaT(float a){DeltaT=a;}
   void set_SourceMPHK(string a){SourceMPHK=a;}
   void set_LastCmdMPHK(int a){LastCmdMPHK=a;}
   void set_CountCmdMPHK(int a){CountCmdMPHK=a;}
   void set_ErrCmdMPHK(int a){ErrCmdMPHK=a;}
   void set_ErrGenMPHK(int a){ErrGenMPHK=a;}
   void set_MissingMPHK(int a){MissingMPHK=a;}
   void set_FIFOPctMPHK(int a){FIFOPctMPHK=a;}
   void set_Drop232MPHK(int a){Drop232MPHK=a;}
   void set_DropUSBMPHK(int a){DropUSBMPHK=a;}
    
   //PMHF2
   //PMHF2: 07/19/2022 13:29:16 BarCounts: 29028110 149972000 29255638 149731314 BarRates:  -198586.8 -274361.6 -200137.7 -272696.6 400.0 0.00 400.0 0.00
   void set_P1MPHK(float a){P1MPHK=a;}
   void set_P2MPHK(float a){P2MPHK=a;}
   void set_Temp1MPHK(float a){Temp1MPHK=a;} 
   void set_Temp2MPHK(float a){Temp2MPHK=a;}

   //PMHF3
   //PMHF3: 07/19/2022 13:29:16 Dp: 2010065 Dt: -2099950 IntPress: 750.24 IntTemp: 42.3 BoardTemp: 43.0 DieTemp: 44.0 Analog: 3.47 147.33 3.32 91.66 5.01 840.30 5.25 4.25 15.24 3.61 2730.47 121.43 
   void set_yMPHK3(int a){yMPHK3=a;}//Year from PMHF3 line linked to the event
   void set_mMPHK3(int a){mMPHK3=a;}//Month from PMHF3 line linked to the event
   void set_dMPHK3(int a){dMPHK3=a;}//Day from PMHF3 line linked to the event
   void set_hMPHK3(int a){hMPHK3=a;}//Hour from PMHF3 line linked to the event
   void set_miMPHK3(int a){miMPHK3=a;}//Minute from PMHF3 line linked to the event 
   void set_sMPHK3(int a){sMPHK3=a;}//Second from PMHF3 line linked to the event
   void set_Dp(int a){Dp=a;}
   void set_Dt(int a){Dt=a;}
   void set_IntPress(float a){IntPress=a;}
   void set_IntTemp(float a){IntTemp=a;}
   void set_BoardTemp(float a){BoardTemp=a;}
   void set_DieTemp(float a){DieTemp=a;}
   void set_Dig3V(float a){Dig3V=a;}
   void set_Dig3C(float a){Dig3C=a;}
   void set_Ana3V(float a){Ana3V=a;}
   void set_Ana3C(float a){Ana3C=a;}
   void set_Dig5V(float a){Dig5V=a;}
   void set_Dig5C(float a){Dig5C=a;}
   void set_Ana5V(float a){Ana5V=a;}
   void set_Ana5C(float a){Ana5C=a;}
   void set_Dig15V(float a){Dig15V=a;}
   void set_TckV(float a){TckV=a;}
   void set_TckC(float a){TckC=a;}
   void set_TckbiasC(float a){TckbiasC=a;}
    
   void set_yPHA(int a){yPHA=a;}
   void set_mPHA(int a){mPHA=a;}
   void set_dPHA(int a){dPHA=a;}
   void set_hPHA(int a){hPHA=a;}
   void set_miPHA(int a){miPHA=a;}
   void set_sPHA(int a){sPHA=a;}
   void set_GoPHA(double a){GoPHA=a;}
   void set_tPHA(double a){tPHA=a;}
   void set_yEVT(int a){yEVT=a;}
   void set_mEVT(int a){mEVT=a;} 
   void set_dEVT(int a){dEVT=a;}
   void set_hEVT(int a){hEVT=a;}
   void set_miEVT(int a){miEVT=a;}
   void set_sEVT(int a){sEVT=a;}
   void set_EVT(string a){EVT=a;}
   void set_GoEVT(double a){GoEVT=a;}
   void set_tEVT(double a){tEVT=a;}

   void set_nHitLEVT(int a){nHitLEVT=a;}
   void set_CCEVT(int a){CCEVT=a;}
   void set_PatternEVT(int a){PatternEVT=a;}
   void set_Q1EVT(int a){Q1EVT=a;}
   void set_TrigEVT(double a){TrigEVT=a;}

   void set_L(int k, string a){if(k<8)L[k]=string(a);}
   void set_flagL(int k, int a){if(k<8)flagL[k]=a;}
   void set_Ldummy(int k, int a){if(k<8)Ldummy[k]=a;}

   ////////////////////////////////


   ////////////////////////////////
   void set_ncase(int a){ncase=a;}
   void set_typeMC(int a){typeMC=a;}
   void set_EkMC(double a){EkMC=a;}
   void set_pMC(double a){pMC=a;}
   void set_X0MC(double a){X0MC=a;}
   void set_Y0MC(double a){Y0MC=a;}
   void set_Z0MC(double a){Z0MC=a;}
   void set_CX0MC(double a){CX0MC=a;}
   void set_CY0MC(double a){CY0MC=a;}
   void set_CZ0MC(double a){CZ0MC=a;}
   void set_typePP(int a){typePP=a;}
   void set_EkPP(double a) {EkPP=a;}
   void set_ZenPP(double a){ZenPP=a;}
   void set_AziPP(double a){AziPP=a;}
   void set_CoLatSP(double a){CoLatSP=a;}
   void set_CoLonSP(double a){CoLonSP=a;}

   ////////////////////////////////
   // HIts information
   ////////////////////////////////
   void set_Nhits(int a){Nhits=a;}
   void add_Nhits(){Nhits++;}

   void set_Nhnoisy(int a){Nhnoisy=a;};
   void add_Nhnoisy(){Nhnoisy++;};


   ////////////////////////////////
   //Pattern Recognition
   ////////////////////////////////
   void set_EkPR(double a){EkPR=a;}
   void set_p0PR(double a){p0PR=a;}
   void set_aPR(double b){aPR=b;}
   void set_bPR(double a){bPR=a;}
   void set_cPR(double a){cPR=a;}
   void set_interPR(double a){interPR=a;}
   void set_slopePR(double a){slopePR=a;}
   void set_chi2BPR(double a){chi2BPR=a;}
   void set_chi2NBPR(double a){chi2NBPR=a;}
   void set_clBPR(double a){clBPR=a;}
   void set_clNBPR(double a){clNBPR=a;}
   void set_deflecPR(double a){deflecPR=a;}
   void set_XT1PR(float a){XT1PR=a;}
   void set_XT3PR(float a){XT3PR=a;}
   void set_XT4PR(float a){XT4PR=a;}
   void set_XGPR(float a){XGPR=a;}
   void set_YT1PR(float a){YT1PR=a;}
   void set_YT3PR(float a){YT3PR=a;}
   void set_YT4PR(float a){YT4PR=a;}
   void set_YGPR(float a){YGPR=a;}
   void set_thBiPR(float a){thBiPR=a;}
   void set_thBoPR(float a){thBoPR=a;}
   void set_thNBPR(float a){thNBPR=a;}
   void set_NLPR(int k, int a){if(k<8)NLPR[k]=a;}

   ////////////////////////////////
   //Reconstrution
   ////////////////////////////////
   void set_typereco(int a){typereco=a;}
   void set_Ekreco(double a){Ekreco=a;}
   void set_p0reco(double a){p0reco=a;}
   void set_X0reco(double a){X0reco=a;}
   void set_Y0reco(double a){Y0reco=a;}
   void set_Z0reco(double a){Z0reco=a;}
   void set_CX0reco(double a){CX0reco=a;}
   void set_CY0reco(double a){CY0reco=a;}
   void set_CZ0reco(double a){CZ0reco=a;}
   void set_ndf(int a){ndf=a;}
   void set_chi2(double a){chi2=a;}
   void set_cl(double a){cl=a;}
   void set_d0(double a){d0=a;}
   void set_phi0(double a){phi0=a;}
   void set_cpa(double a){cpa=a;}
   void set_dz(double a){dz=a;}
   void set_tanl(double a){tanl=a;}
   void set_phi0_init(double a){phi0_init=a;}
   void set_cpa_init(double a){cpa_init=a;}
   void set_tanl_init(double a){tanl_init=a;}
   void set_d0err2(double a){d0err2=a;}
   void set_phi0err2(double a){phi0err2=a;}
   void set_cpaerr2(double a){cpaerr2=a;}
   void set_dzerr2(double a){dzerr2=a;}
   void set_tanlerr2(double a){tanlerr2=a;}
   void set_Cov_init(TMatrixD a){Cov_init=a;}
   void set_Cov_last(TMatrixD a){Cov_last=a;}


   void add_hit(ALTckhit* h){hits.push_back(h);Nhits++;}

   //Set Pattern Reco variable at the position of the hit of index k
   void set_hxPR(int k, float a){if(k<(int)hits.size())(hits.at(k))->set_xPR(a);}
   void set_hyPR(int k, float a){if(k<(int)hits.size())(hits.at(k))->set_yPR(a);}
   void set_hzPR(int k, float a){if(k<(int)hits.size())(hits.at(k))->set_zPR(a);}
   void set_hcxPR(int k, float a){if(k<(int)hits.size())(hits.at(k))->set_cxPR(a);}
   void set_hcyPR(int k, float a){if(k<(int)hits.size())(hits.at(k))->set_cyPR(a);}
   void set_hczPR(int k, float a){if(k<(int)hits.size())(hits.at(k))->set_czPR(a);}

   //Set reconstruted variable at the position of the hit of index k
   void set_hxreco(int k,float a){if(k<(int)hits.size())(hits.at(k))->set_xreco(a);}
   void set_hyreco(int k,float a){if(k<(int)hits.size())(hits.at(k))->set_yreco(a);}
   void set_hzreco(int k,float a){if(k<(int)hits.size())(hits.at(k))->set_zreco(a);}
   void set_hagereco(int k,float a){if(k<(int)hits.size())(hits.at(k))->set_agereco(a);}
   void set_hcxreco(int k,float a){if(k<(int)hits.size())(hits.at(k))->set_cxreco(a);}
   void set_hcyreco(int k,float a){if(k<(int)hits.size())(hits.at(k))->set_cyreco(a);}
   void set_hczreco(int k,float a){if(k<(int)hits.size())(hits.at(k))->set_czreco(a);}
   void set_hereco(int k,float a){if(k<(int)hits.size())(hits.at(k))->set_ereco(a);}

   //set all positions in vector
   void add_posX(float a){posX.push_back(a);}
   void add_posY(float a){posY.push_back(a);}
   void add_posZ(float a){posZ.push_back(a);}
   void add_posCX(float a){posCX.push_back(a);}
   void add_posCY(float a){posCY.push_back(a);}
   void add_posCZ(float a){posCZ.push_back(a);}
   void add_posType(float a){posType.push_back(a);}
   void add_posAge(float a){posAge.push_back(a);}
   void add_posP(float a){posP.push_back(a);}
   void set_T1(bool a){T1=a;}
   void set_T2(bool a){T2=a;}
   void set_T3(bool a){T3=a;}
   void set_T4(bool a){T4=a;}
   void set_guard(bool a){guard=a;}
   void add_EneT1(double a){EneT1.push_back(a);}
   void add_EneT2(double a){EneT2.push_back(a);}
   void add_EneT3(double a){EneT3.push_back(a);}
   void add_EneT4(double a){EneT4.push_back(a);}
   void add_Eneg(double a){Eneg.push_back(a);}
   void add_ToF(double a){ToF.push_back(a);}
   void add_XT1(double a){XT1.push_back(a);}
   void add_XT3(double a){XT3.push_back(a);}
   void add_XT4(double a){XT4.push_back(a);}
   void add_YT1(double a){YT1.push_back(a);}
   void add_YT3(double a){YT3.push_back(a);}
   void add_YT4(double a){YT4.push_back(a);}
   void add_timeT1(double a){timeT1.push_back(a);}
   void add_timeT2(double a){timeT2.push_back(a);}
   void add_timeT3(double a){timeT3.push_back(a);}
   void add_timeT4(double a){timeT4.push_back(a);}
   void add_timeg(double a){timeg.push_back(a);}
   void set_Ti(int a){Ti=a;}
   void set_Tic(int a){Tic=a;}
   void set_TiPR(int a){TiPR=a;}
   void add_EneIsofoam(double a){EneIsofoam.push_back(a);}
   void add_EneShell(double a){EneShell.push_back(a);}
   void add_timeIsofoam(double a){timeIsofoam.push_back(a);}
   void add_timeShell(double a){timeShell.push_back(a);}
   void set_NphCK(int a){NphCK=a;}

   //HOUSEKEEPING FROM COUNTERS 1 AND 3
   void set_yCT1(int a){yCT1=a;}
   void set_mCT1(int a){mCT1=a;}
   void set_dCT1(int a){dCT1=a;}
   void set_hCT1(int a){hCT1=a;}
   void set_miCT1(int a){miCT1=a;}
   void set_sCT1(int a){sCT1=a;}
   void set_TempCT1(float a){TempCT1=a;}
   void set_OnTimeCT1(int a){OnTimeCT1=a;}
   void set_LastCT1(int a){LastCT1=a;}
   void set_CountCT1(int a){CountCT1=a;}
   void set_Baro1T(float a){Baro1T=a;}
   void set_Baro1P(float a){Baro1P=a;}
   void set_Baro2T(float a){Baro2T=a;}
   void set_Baro2P(float a){Baro2P=a;}
   void set_TempB1(float a){TempB1=a;}
   void set_TempB2(float a){TempB2=a;}
   void set_PressB1(float a){PressB1=a;}
   void set_PressB2(float a){PressB2=a;}
   void set_Volt5VCT1(float a){Volt5VCT1=a;}
   void set_Volt15VCT1(float a){Volt15VCT1=a;}
   void set_GOCT1(float a){GOCT1=a;}
   void set_coinCT1(float a){coinCT1=a;}

   //Data FROM "CT3" LINE
   void set_yCT3(int a){yCT3=a;}
   void set_mCT3(int a){mCT3=a;}
   void set_dCT3(int a){dCT3=a;}
   void set_hCT3(int a){hCT3=a;}
   void set_miCT3(int a){miCT3=a;}
   void set_sCT3(int a){sCT3=a;}
   void set_TempCT3(float a){TempCT3=a;}
   void set_OnTimeCT3(int a){OnTimeCT3=a;}
   void set_LastCT3(int a){LastCT3=a;}
   void set_CountCT3(int a){CountCT3=a;}
   void set_T1L(float a){T1L=a;}
   void set_T1A(float a){T1A=a;}
   void set_T2L(float a){T2L=a;}
   void set_T2A(float a){T2A=a;}
   void set_T3A(float a){T3A=a;}
   void set_T3L(float a){T3L=a;}
   void set_T4A(float a){T4A=a;}
   void set_T4L(float a){T4L=a;}
   void set_GRDL(float a){GRDL=a;}
   void set_GRDA(float a){GRDA=a;}
   void set_Volt5VCT3(float a){Volt5VCT3=a;}
   void set_Volt15VCT3(float a){Volt15VCT3=a;}


   void set_yPOW(int a){yPOW=a;}
   void set_mPOW(int a){mPOW=a;}
   void set_dPOW(int a){dPOW=a;}
   void set_hPOW(int a){hPOW=a;}
   void set_miPOW(int a){miPOW=a;}
   void set_sPOW(int a){sPOW=a;}
   void set_OnTimePOW(int a){OnTimePOW=a;}

   void set_MainC(float a){MainC=a;}
   void set_MainV(float a){MainV=a;}
   void set_HeatC(float a){HeatC=a;}
   void set_HeatV(float a){HeatV=a;}
   void set_TrackC(float a){TrackC=a;}
   void set_TrackV(float a){TrackV=a;}
   void set_IntPiV(float a){IntPiV=a;}
   void set_IntPiC(float a){IntPiC=a;}
   
   //Data FROM "VCI" LINE

   void set_yVCI(int a){yVCI=a;}
   void set_mVCI(int a){mVCI=a;}
   void set_dVCI(int a){dVCI=a;}
   void set_hVCI(int a){hVCI=a;}
   void set_miVCI(int a){miVCI=a;}
   void set_sVCI(int a){sVCI=a;}
   //void set_Lrate(int k, int a){if(k<8)Lrate[k]=a;}



   ////////////////////////////////
   //"Getting" member methods
   ////////////////////////////////
   int get_eventnumber(){return eventnumber;}
   int get_bpdnumber(){return bpdnumber;}

   //PSE1 line
   int get_yPSE1(){return yPSE1;}
   int get_mPSE1(){return mPSE1;}
   int get_dPSE1(){return dPSE1;}
   int get_hPSE1(){return hPSE1;}
   int get_miPSE1(){return miPSE1;}
   int get_sPSE1(){return sPSE1;}
   int get_N(){return N;}
   int get_Code(){return Code;}
   int get_nEcho(){return nEcho;}
   int get_Last(){return Last;}
   int get_FirstNibble(){return FirstNibble;}
   int get_runnumber(){return runnumber;}
   int get_Trigger(){return Trigger;}
   int get_Stamp(){return Stamp;}
   int get_Go1(){return Go1;}
 
   int get_yPSE1b(){return yPSE1b;}
   int get_mPSE1b(){return mPSE1b;}
   int get_dPSE1b(){return dPSE1b;}
   int get_hPSE1b(){return hPSE1b;}
   int get_miPSE1b(){return miPSE1b;}
   int get_sPSE1b(){return sPSE1b;}
   
   unsigned get_Status(){return Status;}
   bool get_G(){return G;}
   bool get_T4(){return T4;}
   bool get_T3(){return T3;}
   bool get_T2(){return T2;}
   bool get_T1(){return T1;}
   bool get_TrTrig1(){return TrTrig1;}
   bool get_TrTrig0(){return TrTrig0;}
   bool get_PMTTrig2(){return PMTTrig2;}
   bool get_PMTTrig1(){return PMTTrig1;}
   
   //PSE2 line   
   int get_yPSE2(){return yPSE2;}
   int get_mPSE2(){return mPSE2;}
   int get_dPSE2(){return dPSE2;}
   int get_hPSE2(){return hPSE2;}
   int get_miPSE2(){return miPSE2;}
   int get_sPSE2(){return sPSE2;}
     
   int get_sTraxtrig(){return sTraxtrig;}
   int get_TraxTrig(){return TraxTrig;}
   int get_TraxComm(){return TraxComm;}
   int get_TraxPatt(){return TraxPatt;} 
   int get_TotalTrax(){return TotalTrax;} 
   int get_TotalBytes(){return TotalBytes;}   
   
   
   
   
   //PEHF1,2,3,4 lines
   //HOUSE KEEPING lines
   //EVENT PSOC House Keeping

   int get_yEPHK1(){return yEPHK1;}
   int get_mEPHK1(){return mEPHK1;}
   int get_dEPHK1(){return dEPHK1;}
   int get_hEPHK1(){return hEPHK1;}
   int get_miEPHK1(){return miEPHK1;}
   int get_sEPHK1(){return sEPHK1;}
 
   int get_yEPHK1b(){return yEPHK1b;}
   int get_mEPHK1b(){return mEPHK1b;}
   int get_dEPHK1b(){return dEPHK1b;}
   int get_hEPHK1b(){return hEPHK1b;}
   int get_miEPHK1b(){return miEPHK1b;}
   int get_sEPHK1b(){return sEPHK1b;}
  
   int get_yEPHK4(){return yEPHK4;}
   int get_mEPHK4(){return mEPHK4;}
   int get_dEPHK4(){return dEPHK4;}
   int get_hEPHK4(){return hEPHK4;}
   int get_miEPHK4(){return miEPHK4;}
   int get_sEPHK4(){return sEPHK4;}
 
   //PEHF1
   int get_RunEPHK(){return RunEPHK;} 
   string get_SourceEPHK(){return SourceEPHK;}   //Source of the EVENT PSOC HOUSEKEEPING
   //PEHF2
   string get_ComLast(){return ComLast;}    //Last Command
   int get_ComCount(){return ComCount;}     //Command Count 
   int get_ComErr(){return ComErr;}         //Command Error Count
   int get_GenErr(){return GenErr;}         //General Error Count
   int get_Go(){return Go;}                 //NUmber of events
   int get_Go1EPHK(){return Go1EPHK;}         //Number of missing events
   int get_AvgROTime(){return AvgROTime;}   //Average Readout time in microsec
   //PEHF3
   int get_T1r(){return T1r;}  //Single rate T1
   int get_T2r(){return T2r;}  //Single rate T2
   int get_T3r(){return T3r;}  //Single rate T3
   int get_T4r(){return T4r;}  //Single rate T4
   int get_Gr(){return Gr;}    //Single rate Guard
   int get_TrCom(){return TrCom;}     //Tracker Command Count
   int get_Tr1Pct(){return Tr1Pct;}   //Percentage of tracker trigger 1
   int get_Tr2Pct(){return Tr2Pct;}   //Percentage of tracker trigger 2 
   int get_UARTErr(){return UARTErr;} //Tracker UART Error Count
   int get_UARTTim(){return UARTTim;} //Tracker UART Timeout Count 
   //PEHF4
   int get_NhperCh(int k)
       {if(k<8){return NhperCh[k];}
        else {return -1;} } //hits per layer event*10
   int get_Lrate(int k)
       {if(k<8){return Lrate[k];}
        else {return -1;} }
   int get_Ldummy(int k)
       {if(k<8){return Ldummy[k];}
        else {return -1;} }
   //Temperatures:
   float get_PSOCDieTemp(){return PSOCDieTemp;}
   float get_TempL0(){return TempL0;}
   float get_TempL7(){return TempL7;}
   //TrackStats
   float get_TrackStats(int k)
        {if(k<6) {return TrackStats[k];} 
	 else {return -1;}}//Tracker Stat
   int get_Samples(){return Samples;}  //Number of sample used to calculate PctLive
   float get_PctADCLive(){return PctADCLive;} //PSOC Live time percentage using N Samples between the last 2 events   
   float get_PctMaBzy(){return PctMaBzy;}
   float get_PctTrLive(){return PctTrLive;} 

   //PMHF1 MAIN PSOC HOUSEKEEPING 
   //PMHF1: 07/19/2022 13:29:16 Date: 07/19/2022 13:29:07 DeltaT: 5716.00 Source: FF00FF LastCmd: 0320 CountCmd: 2 ErrCmd: 0 ErrGen: 12 Missing: 0 FIFOPct: 0 Drop232: 0 DropUSB: 0 
   int get_yMPHK1(){return yMPHK1;}//Year from PMHF1 line linked to the event
   int get_mMPHK1(){return mMPHK1;}//Month from PMHF1 line linked to the event
   int get_dMPHK1(){return dMPHK1;}//Day from PMHF1 line linked to the event
   int get_hMPHK1(){return hMPHK1;}//Hour from PMHF1 line linked to the event
   int get_miMPHK1(){return miMPHK1;}//Minute from PMHF1 line linked to the event 
   int get_sMPHK1(){return sMPHK1;}//Second from PMHF1 line linked to the event
   int get_yMPHK1b(){return yMPHK1b;}//Year from PMHFb1 line linked to the event
   int get_mMPHK1b(){return mMPHK1b;}//Month from PMHF1b line linked to the event
   int get_dMPHK1b(){return dMPHK1b;}//Day from PMHF1b line linked to the event
   int get_hMPHK1b(){return hMPHK1b;}//Hour from PMHF1b line linked to the event
   int get_miMPHK1b(){return miMPHK1b;}//Minute from PMHF1b line linked to the event 
   int get_sMPHK1b(){return sMPHK1b;}//Second from PMHF1b line linked to the event
   float get_DeltaT(){return DeltaT;}
   string get_SourceMPHK(){return SourceMPHK;}
   int get_LastCmdMPHK(){return LastCmdMPHK;}
   int get_CountCmdMPHK(){return CountCmdMPHK;}
   int get_ErrCmdMPHK(){return ErrCmdMPHK;}
   int get_ErrGenMPHK(){return ErrGenMPHK;}
   int get_MissingMPHK(){return MissingMPHK;}
   int get_FIFOPctMPHK(){return FIFOPctMPHK;}
   int get_Drop232MPHK(){return Drop232MPHK;}
   int get_DropUSBMPHK(){return DropUSBMPHK;}
    
   //PMHF2
   //PMHF2: 07/19/2022 13:29:16 BarCounts: 29028110 149972000 29255638 149731314 BarRates:  -198586.8 -274361.6 -200137.7 -272696.6 400.0 0.00 400.0 0.00
   float get_P1MPHK(){return P1MPHK;}
   float get_P2MPHK(){return P2MPHK;}
   float get_Temp1MPHK(){return Temp1MPHK;} 
   float get_Temp2MPHK(){return Temp2MPHK;}

   //PMHF3
   //PMHF3: 07/19/2022 13:29:16 Dp: 2010065 Dt: -2099950 IntPress: 750.24 IntTemp: 42.3 BoardTemp: 43.0 DieTemp: 44.0 Analog: 3.47 147.33 3.32 91.66 5.01 840.30 5.25 4.25 15.24 3.61 2730.47 121.43 
   int get_yMPHK3(){return yMPHK3;}//Year from PMHF3 line linked to the event
   int get_mMPHK3(){return mMPHK3;}//Month from PMHF3 line linked to the event
   int get_dMPHK3(){return dMPHK3;}//Day from PMHF3 line linked to the event
   int get_hMPHK3(){return hMPHK3;}//Hour from PMHF3 line linked to the event
   int get_miMPHK3(){return miMPHK3;}//Minute from PMHF3 line linked to the event 
   int get_sMPHK3(){return sMPHK3;}//Second from PMHF3 line linked to the event
   int get_Dp(){return Dp;}
   int get_Dt(){return Dt;}
   float get_IntPress(){return IntPress;}
   float get_IntTemp(){return IntTemp;}
   float get_BoardTemp(){return BoardTemp;}
   float get_DieTemp(){return DieTemp;}
   float get_Dig3V(){return Dig3V;}
   float get_Dig3C(){return Dig3C;}
   float get_Ana3V(){return Ana3V;}
   float get_Ana3C(){return Ana3C;}
   float get_Dig5V(){return Dig5V;}
   float get_Dig5C(){return Dig5C;}
   float get_Ana5V(){return Ana5V;}
   float get_Ana5C(){return Ana5C;}
   float get_Dig15V(){return Dig15V;}
   float get_TckV(){return TckV;}
   float get_TckC(){return TckC;}
   float get_TckbiasC(){return TckbiasC;}
   
   int get_yPHA(){return yPHA;}
   int get_mPHA(){return mPHA;}
   int get_dPHA(){return dPHA;}
   int get_hPHA(){return hPHA;}
   int get_miPHA(){return miPHA;}
   int get_sPHA(){return sPHA;}
   double get_GoPHA(){return GoPHA;}
   double get_tPHA(){return tPHA;}
   int get_yEVT(){return yEVT;}
   int get_mEVT(){return mEVT;}
   int get_dEVT(){return dEVT;}
   int get_hEVT(){return hEVT;}
   int get_miEVT(){return miEVT;}
   int get_sEVT(){return sEVT;}
   double get_GoEVT(){return GoEVT;}
   double get_tEVT(){return tEVT;}
   string get_EVT(){return EVT;}

   int get_nHitLEVT(){return nHitLEVT;}
   int get_CCEVT(){return CCEVT;}
   int get_PatternEVT(){return PatternEVT;}
   int get_Q1EVT(){return Q1EVT;}
   double get_TrigEVT(){return TrigEVT;}

   string get_L(int k){if(k<8)return L[k];else return "";}
   int get_flagL(int k){if(k<8)return flagL[k];else return 0;}

   ////////////////////////////////

   ////////////////////////////////

   int get_ncase(){return ncase;}
   int get_typeMC(){return typeMC;}
   double get_EkMC(){return EkMC;}
   double get_pMC(){return pMC;}
   double get_X0MC(){return X0MC;}
   double get_Y0MC(){return Y0MC;}
   double get_Z0MC(){return Z0MC;}
   double get_CX0MC(){return CX0MC;}
   double get_CY0MC(){return CY0MC;}
   double get_CZ0MC(){return CZ0MC;}
   int get_typePP(){return typePP;}
   double get_EkPP() {return EkPP;}
   double get_ZenPP(){return ZenPP;}
   double get_AziPP(){return AziPP;}
   double get_CoLatSP(){return CoLatSP;}
   double get_CoLonSP(){return CoLonSP;}

   ////////////////////////////////
   int get_Nhits(){return Nhits;}
   int get_Nhnoisy(){return Nhnoisy;}


   ////////////////////////////////

   double get_EkPR(){return EkPR;}
   double get_p0PR(){return p0PR;}
   double get_aPR(){return aPR;}
   double get_bPR(){return bPR;}
   double get_cPR(){return cPR;}
   double get_interPR(){return interPR;}
   double get_slopePR(){return slopePR;}
   double get_chi2BPR(){return chi2BPR;}
   double get_chi2NBPR(){return chi2NBPR;}
   double get_clBPR(){return clBPR;}
   double get_clNBPR(){return clNBPR;}
   double get_deflecPR(){return deflecPR;}
   float get_XT1PR(){return XT1PR;}
   float get_XT3PR(){return XT3PR;}
   float get_XT4PR(){return XT4PR;}
   float get_XGPR(){return XGPR;}
   float get_YT1PR(){return YT1PR;}
   float get_YT3PR(){return YT3PR;}
   float get_YT4PR(){return YT4PR;}
   float get_YGPR(){return YGPR;}
   float get_thBiPR(){return thBiPR;}
   float get_thBoPR(){return thBoPR;}
   float get_thNBPR(){return thNBPR;}
   int get_NLPR(int k){if(k<8)return NLPR[k];else return 0;}

   ////////////////////////////////
   int get_typereco(){return typereco;}
   double get_Ekreco(){return Ekreco;}
   double get_p0reco(){return p0reco;}
   double get_X0reco(){return X0reco;}
   double get_Y0reco(){return Y0reco;}
   double get_Z0reco(){return Z0reco;}
   double get_CX0reco(){return CX0reco;}
   double get_CY0reco(){return CY0reco;}
   double get_CZ0reco(){return CZ0reco;}
   int get_ndf(){return ndf;}
   double get_chi2(){return chi2;}
   double get_cl(){return cl;}
   double get_d0(){return d0;}
   double get_phi0(){return phi0;}
   double get_cpa(){return cpa;}
   double get_dz(){return dz;}
   double get_tanl(){return tanl;}
   double get_phi0_init(){return phi0_init;}
   double get_cpa_init(){return cpa_init;}
   double get_tanl_init(){return tanl_init;}
   double get_d0err2(){return d0err2;}
   double get_phi0err2(){return phi0err2;}
   double get_cpaerr2(){return cpaerr2;}
   double get_dzerr2(){return dzerr2;}
   double get_tanlerr2(){return tanlerr2;}
   TMatrixD get_Cov_init(){return Cov_init;}
   TMatrixD get_Cov_last(){return Cov_last;}
   std::vector<ALTckhit*>& get_hits(){return hits;}
   std::vector<float>&  get_posX(){return posX;}
   std::vector<float>&  get_posY(){return posY;}
   std::vector<float>&  get_posZ(){return posZ;}
   std::vector<float>&  get_posCX(){return posCX;}
   std::vector<float>&  get_posCY(){return posCY;}
   std::vector<float>&  get_posCZ(){return posCZ;}
   std::vector<float>&  get_posType(){return posType;}
   std::vector<float>&  get_posAge(){return posAge;}
   std::vector<float>&  get_posP(){return posP;}


   bool get_guard(){return guard;}
   std::vector<double>&  get_EneT1(){return EneT1;}
   std::vector<double>&  get_EneT2(){return EneT2;}
   std::vector<double>&  get_EneT3(){return EneT3;}
   std::vector<double>&  get_EneT4(){return EneT4;}
   std::vector<double>&  get_Eneg(){return Eneg;}
   std::vector<double>&  get_ToF(){return ToF;}

   std::vector<double>&  get_XT1(){return XT1;}
   std::vector<double>&  get_XT3(){return XT3;}
   std::vector<double>&  get_XT4(){return XT4;}
   std::vector<double>&  get_YT1(){return YT1;}
   std::vector<double>&  get_YT3(){return YT3;}
   std::vector<double>&  get_YT4(){return YT4;}

   std::vector<double>&  get_timeT1(){return timeT1;}
   std::vector<double>&  get_timeT2(){return timeT2;}
   std::vector<double>&  get_timeT3(){return timeT3;}
   std::vector<double>&  get_timeT4(){return timeT4;}
   std::vector<double>&  get_timeg(){return timeg;}
   int get_Ti(){return Ti;}
   int get_Tic(){return Tic;}
   int get_TiPR(){return TiPR;}
   std::vector<double>&  get_EneIsofoam(){return EneIsofoam;}
   std::vector<double>&  get_EneShell(){return EneShell;}
   std::vector<double>&  get_timeIsofoam(){return timeIsofoam;}
   std::vector<double>&  get_timeShell(){return timeShell;}


   int get_NphCK(){return NphCK;}


   //HOUSEKEEPING FROM COUNTERS 1 AND 3
   int get_yCT1(){return yCT1;}
   int get_mCT1(){return mCT1;}
   int get_dCT1(){return dCT1;}
   int get_hCT1(){return hCT1;}
   int get_miCT1(){return miCT1;}
   int get_sCT1(){return sCT1;}
   float get_TempCT1(){return TempCT1;}
   int get_OnTimeCT1(){return OnTimeCT1;}
   int get_LastCT1(){return LastCT1;}
   int get_CountCT1(){return CountCT1;}
   float get_Baro1T(){return Baro1T;}
   float get_Baro1P(){return Baro1P;}
   float get_Baro2T(){return Baro2T;}
   float get_Baro2P(){return Baro2P;}
   float get_TempB1(){return TempB1;}
   float get_TempB2(){return TempB2;}
   float get_PressB1(){return PressB1;}
   float get_PressB2(){return PressB2;}
   float get_Volt5VCT1(){return Volt5VCT1;}
   float get_Volt15VCT1(){return Volt15VCT1;}
   float get_GOCT1(){return GOCT1;}
   float get_coinCT1(){return coinCT1;}

   int get_yCT3(){return yCT3;}
   int get_mCT3(){return mCT3;}
   int get_dCT3(){return dCT3;}
   int get_hCT3(){return hCT3;}
   int get_miCT3(){return miCT3;}
   int get_sCT3(){return sCT3;}
   float get_TempCT3(){return TempCT3;}
   int get_OnTimeCT3(){return OnTimeCT3;}
   int get_LastCT3(){return LastCT3;}
   int get_CountCT3(){return CountCT3;}
   float get_T1L(){return T1L;}
   float get_T1A(){return T1A;}
   float get_T2L(){return T2L;}
   float get_T2A(){return T2A;}
   float get_T3L(){return T3L;}
   float get_T3A(){return T3A;}
   float get_T4L(){return T4L;}
   float get_T4A(){return T4A;}
   float get_GRDL(){return GRDL;}
   float get_GRDA(){return GRDA;}
   float get_Volt5VCT3(){return Volt5VCT3;}
   float get_Volt15VCT3(){return Volt15VCT3;}

   int get_yPOW(){return yPOW;}
   int get_mPOW(){return mPOW;}
   int get_dPOW(){return dPOW;}
   int get_hPOW(){return hPOW;}
   int get_miPOW(){return miPOW;}
   int get_sPOW(){return sPOW;}
   int get_OnTimePOW(){return OnTimePOW;}

   float get_MainC(){return MainC;}
   float get_MainV(){return MainV;}
   float get_HeatC(){return HeatC;}
   float get_HeatV(){return HeatV;}
   float get_TrackC(){return TrackC;}
   float get_TrackV(){return TrackV;}
   float get_IntPiV(){return IntPiV;}
   float get_IntPiC(){return IntPiC;}
   
   //From VCI line
   int get_yVCI(){return yVCI;}
   int get_mVCI(){return mVCI;}
   int get_dVCI(){return dVCI;}
   int get_hVCI(){return hVCI;}
   int get_miVCI(){return miVCI;}
   int get_sVCI(){return sVCI;}

   //int get_Lrate(int k){if(k<8)return Lrate[k];else return 0;}


   ////////////////////////////////
   //Methods to get number of layers and layer with hits
   ////////////////////////////////
   int  get_NLayers();
   int get_Layer(int);
   void get_Layers(int*);
   ////////////////////////////////
   //Methods to get number of layers and layer with hits (with max of 3 strips per hits )
   ////////////////////////////////
   int  get_NLayersc();
   int get_Layerc(int);
   void get_Layersc(int*);
   ////////////////////////////////
   //Methods to get number of layers and layer with hits (with max of 3 strips per hits )and pass geometry cuts
   ////////////////////////////////
   int  get_NLayersPR();
   int get_LayerPR(int);
   void get_LayersPR(int*);
   ////////////////////////////////
   ClassDef(ALEvent,1)

};

#endif
