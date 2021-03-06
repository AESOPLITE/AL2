//////////////////////////////////////////////////////////////////////////////////////////
///    Author: Pierre-Simon Mangeard, psmangeard@gmail.com
///    Department of Physics and Astronomy, University of Delaware, January 7, 2017
//////////////////////////////////////////////////////////////////////////////////////////

#include "LoadMCparameters.h"

void LoadMCparameters(string filename,int*TckReg,int*TrigReg,int*GReg, float*TckZPos, float*TrigThresh, float*GuardThresh,int*ShellReg)
{
// Read the file filename and load the region numbers in the geometry file of Fluka
//The 8 layers of the tracker arrive first
//Then the 4 triggers
//Then the guard
//Then the shell and insulation

 //Number of lines in the file
 int n=16;
 //Prefix 5 character
 string pre[16]={"TckL1","TckL2","TckL3","TckL4","TckL5","TckL6","TckL7","TckL8","Trig1","Trig2","Trig3","Trig4","Guard","Isofoam","Shell","Win"};

 //Create stream from filename
 ifstream file;
 //cout << "Filename of MC param is: " << filename << endl;
 file.open(filename, ios_base::in); // open file
 int j=0;
 for(string line; getline(file, line); )   //read stream line by line
   {
    //cout << line << endl;
    istringstream in(line);      //make a stream for the line itself
    string prefix;
    in >> prefix;                  //and read the first whitespace-separated token
    int tmp;
    in >> tmp;
    float val;
    in >> val;
    //check prefix to load the appropriate region variable
    for(int i=0;i<n;i++)
      {
       if(prefix.compare(pre[i]) == 0)
        {
         if(i<8) {TckReg[i]=tmp;TckZPos[i]=val;j++;}
         else if(i<8+4) {TrigReg[i-8]=tmp;TrigThresh[i-8]=val;j++;}
         else if(i==8+4) {GReg[0]=tmp;GuardThresh[0]=val;j++;}
         else if(i>12)  {ShellReg[i-13]=tmp;j++;}
        }//if
      }//i
   }//line
//	cout << "In LoadMCParameters, isofoam region: " << ShellReg[0] <<", shell region: " << ShellReg[1] << endl;
  if (j!=n) cout << "Error when loading the MC parameters: Wrong number of parameters in the file " << filename << "; j=" <<j << ", n=" << n  <<endl;
}
