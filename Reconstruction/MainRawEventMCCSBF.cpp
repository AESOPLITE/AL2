#include "MainRawEventMCCSBF.h"
#include "headers.h"
using namespace std;


//This function transforms the rootfiles from the output of write99toroot to RawEvent
//This function reconstructs the raw events file per file

int main(int argc, char*argv[])
{

 if(argc!=6)
  {
   cout << "Wrong number of parameters!!!!" << endl;
   cout << "The program needs 4 input parameters:"<< endl;
   cout << "First is Fluka type of simulated particles" <<endl;
   cout << "Second is random seed configuration" << endl;
   cout << "Third is first cycle to reconstruct (Starts at 1)" <<endl;
   cout << "Fourth is the number of cycle to reconstruct" <<endl;
   cout << "Fifth is MC source tag" <<endl;
 return -1;
  }
 //Fluka type of particle
 int type=(int) atoi(argv[1]); //3 for electrons
 //int Ene=(int) atoi(argv[2]);   //Energy in MeV
 int Ene=0;
 int seed=(int) atoi(argv[2]);  //Random seed config
 int Ncycles=(int) atoi(argv[3]);   //first cycle to reconstruct
 int Ncycles2=(int) atoi(argv[4]);   //last cycle
 string source=argv[5];

 source='.';
 //Input files
 // string Inppath="/data/smechbal/Fluka/NonUniB/V8";
 //string Inppath="/data/psmangeard/AESOPLITE2/MC/Fluka4/TestAL2/AL2";
 string Inppath="/data/psmangeard/AESOPLITE2/MC/Fluka4/V3";
 string Inppath2="rootfiles";
 string startfile="AL2NonUniB_V3";
 string endfile="_fort.99";

 //Output files
 //string Outpath="/data2/smechbal/MCproduction/AESOPLITE/rootfiles/NonUniB/V8";
 string Outpath="/data/psmangeard/AESOPLITE2/AL2/CSBF/V3";

 //for(int j=0;j<1;j++)//Number of cycles
 for(int j=Ncycles;j<Ncycles+Ncycles2;j++)//Number of cycles
   {
    cout << Form("%s/%d/%s/%s/%s_%d_%d%03d%s.root",Inppath.c_str(),type,source.c_str(),Inppath2.c_str(),startfile.c_str(),type,seed,j,endfile.c_str()) <<endl;
    //Create the RawEvent
  MakeRawEventMCDisc(type,Ene,seed,j,Inppath,source,Inppath2,Outpath,startfile,endfile);
   }//j


 return 0;
}
