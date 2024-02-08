////////////////////////////////////////////////////////////////////////////////////////// 
///    Author: Pierre-Simon Mangeard, psmangeard@gmail.com
///    Department of Physics and Astronomy, University of Delaware, September 8, 2017
////////////////////////////////////////////////////////////////////////////////////////// 

#include "LoadDataparameters.h"
#include "MainRawBPDEvent.h"
using namespace std;

int main(int argc, char* argv[]);

    
//This function read and parse the BPD files
//This function reconstructs the raw events file per file 
//The first paramter contains the file paths 
//This will create one root file per BPD file
//The x,y,z coordinates won't be calculated here
int main(int argc, char* argv[])
{
//Check number of parameters 
 if(argc!=3)
  {
   cout << "Wrong number of parameters!!!!" << endl;
   cout << "The program needs 2 input parameters:"<< endl;
   cout << "The first parameter is the filename that contains the BPD files paths"<< endl;
   cout << "The second parameter is the reconstruction ID flag" << endl;
   return -1;
  }
 

//Open input file
 ifstream filestr;
 filestr.open(argv[1]);
 int geoconf=12; 
 string RecoID = argv[2];
 string filename;
 cout<< "Hello MainRawBPDEvent" <<endl; 
 if(filestr.is_open())
  {
   cout << "The file " << argv[1] << " is open ... (bug in this message)"<< endl ;
  }   
 else
  {
   cout << "The file "<<argv[1] << " is not open (bug in this message)"<< endl;
   return -1;
  }
 //Load configuration parameter
 float* zL=new float[8];
 float*OffsetLL=new float[8];
 float*OffsetRL=new float[8];
 float*TrigThresh=new float[5];
 for(int i=0;i<8;i++)zL[i]=OffsetLL[i]=OffsetRL[i]=0;
 for(int i=0;i<5;i++)TrigThresh[i]=0;
 string paramfile=Form("./src/ALSim/Dataparameters%d.dat",geoconf); 
 LoadDataparameters(paramfile,zL,OffsetLL,OffsetRL,TrigThresh);
 for(int i=0;i<8;i++)
   {
    cout << "L"<<i <<", zL:" << zL[i] ;
    cout << ", OffsetLL:" << OffsetLL[i] ;
    cout << ", OffsetRL:" << OffsetRL[i] << endl;
   }  
 cout << "T1 threshold: " << TrigThresh[0] <<endl;
 cout << "T2 threshold: " << TrigThresh[1] <<endl;
 cout << "T3 threshold: " << TrigThresh[2] <<endl;
 cout << "T4 threshold: " << TrigThresh[3] <<endl;
 cout << "Guard threshold: " << TrigThresh[4] <<endl;
  //Start to read the file
 for (string line; getline(filestr,line);)
   {
    //Here the full line is read and cout<< "Hello MainRawBPDEvent" <<endl; 
 //stored in the string object "line" 
    cout << line <<endl; //Print the file path
 vector<string> input;
 //Split the line 
 input=split(&line,' ');
 //Open input file
  filename = (input.at(0));

   cout << "The file " <<input.at(0) << " is not open ... "<< endl ;
   
    //First step
    //Read the text file .BPD
    //Parse the information to create events
    //The events are stored in a root file line.root 
    MakeRawBPDEventIT(line);
    
    //Temporary Second Step
    //Read the rootfile previously created
    //Determine the coordinates of the clusters
    //in the X,Y,Z coordinates
    //this is where misalignement must be taken into account
    MakeEventData(line,geoconf,zL,OffsetLL,OffsetRL,TrigThresh,RecoID);

   }//line 
 
	cout << "Done processing data" << endl;
        filestr.close();
 //create file that indicates job is donei
 //Output root file
 TFile*fileout=new TFile(Form("%s.txt",filename.c_str()),"RECREATE");
 cout << "Output file is created" <<endl;
 
 return 0;
}
