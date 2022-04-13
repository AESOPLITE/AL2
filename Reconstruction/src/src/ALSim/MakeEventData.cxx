//////////////////////////////////////////////////////////////////////////////////////////
///    Author: Pierre-Simon Mangeard, psmangeard@gmail.com
///    Department of Physics and Astronomy, University of Delaware, September 11, 2017
//////////////////////////////////////////////////////////////////////////////////////////

#include "MakeEventData.h"
#include "MakeRawBPDEvent_503f.h"
#include "ALPatternRecognition.h"
#include "LoadDataparameters.h"
#include "TBox.h"
#include "headers.h"

int MakeEventData(string filename,int geoconfig,float* zL,float* OffsetLL,float* OffsetRL,float* TrigThresh,string RecoID)
{

/*
 //Set Magnetic field map for Kalman filter reconstruction
 TBField *bfield = new TBField();
 bfield->SetUseUniformBfield(false);

 bool FlagMagF=false;
 FlagMagF=bfield->SetMagField();
 if(FlagMagF)cout << "Field Map loaded" << endl;
 else
  {
   cout << "There is an issue when loading the Field Map" << endl;
   return 1;
  }
*/
 //Set Magnetic field map for Runge-Kutta method
 string fN = "./src/RKFitter/fieldmap5mm.bin";
 FieldMap *fM = new FieldMap(fN, "binary", 81);
 //Maximum of configuration to try fitting

 int MAXB=1000;
 int MAXNB=1000;

 //Strip pitch in cm
 float  strippitch=0.0228;

 float zz0=0;//in cm

 TCanvas*can;
 TMultiGraph*multi;
 TMultiGraph*multiB;
 TF1*tmpf;
 TF1*tmpfB;
 TF1*tmpfB2;

 //Input root file
 //Get input filename and ASIC Length and EVT Length
 vector<string> input;
 //Split the line
 input=split(&filename,' ');

 TFile*file=new TFile(Form("%s.root",input.at(0).c_str()),"READ");
 cout << "Input file is open" <<endl;

 //Input root file
 TFile*fileout=new TFile(Form("%s.EVENT_%s.root",input.at(0).c_str(),RecoID.c_str()),"RECREATE");
 cout << "Output file is created" <<endl;

 //Get Tree from the input file
 TTree *tree = (TTree*)file->Get("BPD");
 //Define variables to read event
 ALEvent *e = new ALEvent();
 //Set address to access event data
 tree->SetBranchAddress("event",&e);
 // Create a TTree
 TTree *DEtree = new TTree("Data"," Data Event");
 //Define variables to make the Reco event
 ALEvent *de=new ALEvent();
 // Create a branch with event
 DEtree->Branch("event",&de);
 // Get number of events in Tree
 int nentries=tree->GetEntries();
 cout << "Number  of events: " << nentries << endl;
 //Loop over the events
 // This is the main loop
 for (int k=0;k<nentries;k++)

   {
    tree->GetEntry(k); //Load the entry k in the variable e
    //cout << "Make Event Data: "<<k <<endl;
    //Copy the raw event into a Data event with same structure
    if(k%10000==0) cout << "Event Number " << e->get_eventnumber() << endl;
	de=new ALEvent();
    
    //cout << "Before Copy"   <<endl;

    de->Copy(e);

    //Set boolean flag for triggers

    if(de->get_EneT1().at(0)>TrigThresh[0]) de->set_T1(true);
    if(de->get_EneT2().at(0)>TrigThresh[1]) de->set_T2(true);
    if(de->get_EneT3().at(0)>TrigThresh[2]) de->set_T3(true);
    if(de->get_EneT4().at(0)>TrigThresh[3]) de->set_T4(true);
    if(de->get_Eneg().at(0)>TrigThresh[4]) de->set_guard(true);
    
    //cout << "Before get Ti"   <<endl;

     uint8_t Ti=(uint8_t)de->get_Ti();
    //Number of layers wih hit(s)
    //cout << "Before get get_NLayers"   <<endl;

     int NL=de->get_NLayers();
    //if(NL>7) cout << "ERROR ON NUMBER OF LAYERS" <<endl;
    int* Lay=new int[8];
    de->get_Layers(Lay);

    int NLB=0;
    int NLNB=0;
    
    //cout << "Before NLB"   <<endl;

    //B layer with hits
    NLB+=(int)((Ti >>1) & 0x01);
    NLB+=(int)((Ti >>2) & 0x01);
    NLB+=(int)((Ti >>3) & 0x01);
    NLB+=(int)((Ti >>4) & 0x01);
    NLB+=(int)((Ti >>6) & 0x01);
   
    //cout << "Before NB"   <<endl;
    //NB layer with hits
    NLNB+=(int)((Ti >>0) & 0x01);
    NLNB+=(int)((Ti >>5) & 0x01);
    NLNB+=(int)((Ti >>7) & 0x01);

    //loop over the number of clusters
    int nnhits = (int)de->get_Nhits();
    //cout << "nnhits:"  <<nnhits  <<endl;
    for(int i=0;i<nnhits;i++)
      {
       float x=-999.;
       float y=-999.;
       float z=-999.;
       float offsetLL=0;//Left ladder offset
       float offsetRL=0;//Right ladder offset
       float center=0;
       int L=((de->get_hits()).at(i))->get_L();//0 to 7
       de->get_hits().at(i)->set_k(i);
       int nstrips=((de->get_hits()).at(i))->get_nstrips(); //0 if only one strip
       int fstripID=((de->get_hits()).at(i))->get_fstripID();

       //Determine the coordinate x,y,z parameters
       //Get the values from configuration file read at the beginning of the function
       z=zL[L];
       offsetLL=OffsetLL[L];
       offsetRL=OffsetRL[L];

       //Determine the coordinates from the strips
       //Equations from Sarah's email of September 4 2017.
       //Just calculate the mean value of the strip positions
       //Assume that the center of the coodinnates is 0 is equidistant from the
       //two ladders
       center=(offsetRL+(offsetLL+384.*strippitch))/2.;
       //In non-bending plane: Coordinate X in cm
       if(L==0||L==5||L==7)
        {
         //First 6 chips: 0 to 5; strip number 1 to 384
         if(fstripID>0 &&fstripID<=384)
          {
           x=(fstripID-0.5)*strippitch+offsetLL-center;
          }
         //Last 6 chips: 6 to 11; strip number 385 to 768
         if(fstripID>384)
          {
           x=(fstripID-384.5)*strippitch+offsetRL-center;
          }

         //Calculate the center of the cluster depending on the number of strips

         x+=nstrips*strippitch/2.;
         y=-999.;
        }

       //In bending plane: Coordinate Y in cm
       if(L==1||L==2||L==3||L==4||L==6)
        {
         //First 6 chips: 0 to 5; strip number 1 to 384
         if(fstripID>0 &&fstripID<=384)
          {
           y=(fstripID-0.5)*strippitch+offsetLL-center;

          }
         //Last 6 chips: 6 to 11; strip number 385 to 768
         if(fstripID>384)
          {
           y=(fstripID-384.5)*strippitch+offsetRL-center;

          }
         y+=nstrips*strippitch/2.;

         x=-999.;
        }


       //Fill the coordinates
       ((de->get_hits()).at(i))->set_x(x);
       ((de->get_hits()).at(i))->set_y(y);
       ((de->get_hits()).at(i))->set_z(z);
      }  //i nnhits


      ////////////////////////////////////
      //Pattern Recognition   Sarah's Code
      ////////////////////////////////////
//   if (NL<7) continue;
   int DataType = 1;
   ALPatternRecognition* PR = new ALPatternRecognition();
   int EventPR = PR->FindPattern(de,DataType,zL,OffsetLL,OffsetRL,TrigThresh);
   cout << "Event " << k <<", NL = " << NL << " After PR, EventPR: " << EventPR << endl;
   
   if(EventPR==0) {
         DEtree->Fill();
      //Free memory
      delete de;
      continue;
      }

/*
   /////////////////////
   //KALMAN FILTER
   /////////////////////
    else {
    ALKalman* KF = new ALKalman(de);
    int EventKF=  KF->DoKF(de, DataType, 1, TwoIter);
    if(EventKF==0) {               // delete KF;
        DEtree->Fill();
        delete de;
        continue;
        }
    }

*/



     //////////////////////////////
     //Runge-Kutta reconstruction//
     //////////////////////////////

      else
       {
        double event = de->get_eventnumber();
        double*zLayers=new double[8];
        double e0MC=0;
        double p0MC=0;
        double x0MC=0;
        double y0MC=0;
        double z0MC=0;
        double cx0MC=0;
        double cy0MC=0;
        double cz0MC=0;
        double kappa_MC=0;
        double p0PR=0;
        double x0PR=0;
        double y0PR=0;
        double z0PR=0;
        double cx0PR=0;
        double cy0PR=0;
        double cz0PR=0;
        double kappa_PR=0;
        double QPR = 0;

        for(int i=0;i<8;i++)zLayers[i]=0;
        int lTop = 99;
        for(int j=0;j<nnhits;j++)
           {
            double zz=10.0*(de->get_hits().at(j))->get_z();           //in mm
            int L = int(de->get_hits().at(j)->get_mregMC())%11;       //layer number
            bool flagPR = de->get_hits().at(j)->get_flagPR();         //was hit selected by PR?
            if(!flagPR) {
               // cout << "    hit " << j << " L=" << L << " bad flagPR " << endl;
                continue;
            }
            zLayers[L] = zz;
            if(L < lTop)
               {lTop = L;



                //PR variables at highest layer
                p0PR = de->get_p0PR();
                double deflecPR = de->get_deflecPR();
                QPR = TMath::Sign(1,deflecPR);
                x0PR=(de->get_hits().at(j)->get_xPR())*10.;  // Randomly move the starting point and direction
                y0PR=(de->get_hits().at(j)->get_yPR())*10.;  // Randomly move the starting point and direction
                z0PR=(de->get_hits().at(j)->get_zPR())*10.;
                cx0PR= de->get_hits().at(j)->get_cxPR();
                cy0PR= de->get_hits().at(j)->get_cyPR();
                cz0PR= de->get_hits().at(j)->get_czPR();
                kappa_PR = QPR/p0PR;                        // TVector3 p0(e0MC*cx0MC, e0MC*cy0MC, e0MC*cz0MC)

                //cout << "Event " << event <<endl;
                //cout << "x0MC = " << x0MC << "  y0MC = " << y0MC << "  cx0MC = " << cx0MC << "  cy0MC = " << cy0MC << " kappaMC = " << kappa_MC << endl;
                //cout << "x0PR = " << x0PR << "  y0PR = " << y0PR << "  cx0PR = " << cx0PR << "  cy0PR = " << cy0PR << " kappaPR = " << kappa_PR << endl;
                }
            }   //end loop over hits
        if (lTop > 10) {
            cout << "MakeEventData: error, no top layer found!  lTop=" << lTop << endl;
 	    DEtree->Fill();
	    continue;
        }
        cout << "MakeEventData: event " << event << ", the topmost layer is " << lTop << endl;

         // Create a data list to pass to the fitting routine
        char oLayer[8] = { 'n','b','b','b','b','n','b','n' };    // Orientation, nonbending or bending
        TkrData *Td = new TkrData((int)event);
        for (int lyr = 0; lyr < 8; lyr++) {Td->addLyr(oLayer[lyr], 10.0*zL[lyr], OffsetLL[lyr], OffsetRL[lyr]);}

        for(int j=0;j<nnhits;j++)
           {
            bool flagPR = de->get_hits().at(j)->get_flagPR();
            bool fGhost = de->get_hits().at(j)->get_fGhost();
            if(!flagPR) continue;
            if(fGhost) continue;
            int k = de->get_hits().at(j)->get_k();
            int L = int(de->get_hits().at(j)->get_mregMC())%11;
            int nstrip = de->get_hits().at(j)->get_nstrips() + DataType;
            int fstripID=de->get_hits().at(j)->get_fstripID();
            //coordinates fom MC or data
            double xx=(de->get_hits().at(j)->get_x())*10.;           //in mm
            double yy=(de->get_hits().at(j)->get_y())*10.;           //in mm
            double zz=(de->get_hits().at(j)->get_z())*10.;           //in mm
            //coordinate from PR fit
            double xPR=(de->get_hits().at(j)->get_xPR())*10.;        //in mm
            double yPR=(de->get_hits().at(j)->get_yPR())*10.;        //in mm
            double zPR=(de->get_hits().at(j)->get_zPR())*10.;        //in mm
            //Fill in hits informations onto TkrData class
            if (L==7 && fstripID==575 &&nstrip==1) xx = xPR;
            if(L==0||L==5||L==7) Td->addHit(L,xx, nstrip, xx, yy, xPR, yPR);
            else Td->addHit(L,yy, nstrip, xx, yy, xPR, yPR);
            cout  << k << ", l=" << L <<", x= " << xx << " ,xPR=" << xPR << " y= " << yy << ", yPR " << yPR << " z= " << zz << ", zPR " << zPR << endl;
            } // end loop on hits

        Td->print(" check ");

        //Do RK fit
        bool verbose = false;
        bool MCS = false;
        double stepSize = 5;
        int alg = 0;
        double dl = 10.0;
        double arg = 1.0 - cx0PR*cx0PR - cy0PR*cy0PR;
        if (arg < 0.) {
            cout << "MainRecoEventData: bad direction cosines:" << " cx=" << cx0PR << " cy=" << cy0PR << endl;
            DEtree->Fill();
	    continue;
        }
        double cz = -sqrt(arg);
        double z0RK = z0PR - dl*cz;
        RKfitter *rkf = new RKfitter(verbose, z0RK, fM, Td, MCS, stepSize, alg);
        vector<int> hits = {0,0,0,0,0,0,0,0};
        //kappa_PR = kappa_MC;   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        double guess[5] = {x0PR-dl*cx0PR,y0PR-dl*cy0PR,cx0PR,cy0PR,kappa_PR};
        cout << "Call RK fit with z0=" << z0RK << " guess=" << guess[0] << " " << guess[1] << " " << guess[2] << " " << guess[3] << " " << guess[4] << "  1/kappa=" << 1.0/kappa_PR << endl;
        rkf->fitIt(false, guess, hits);

        //Get fit parameters and fill event TTree

        rkf->print("test fit");
       // rkf->plotEvent(QMC*p0MC, QPR*p0PR);

        double a[5];
        rkf->tkrParams(a);
        double e[5];
        rkf->errors(e);
        double p0reco = abs(1./ a[4]);      //fitted momentum in GeV
        double chi2 = rkf->chiSqr();            //chi2 of fit
        int typereco = TMath::Sign(1,a[4]);     //positive or negative particle?
        double cxL0 = a[1];                     //directional cosine at beginning of track
        double cyL0 = a[2];
        double err_cpa = e[4];
        double cpa = typereco/p0reco;
        for(int m=0;m<nnhits;m++)
           {
            bool flagPR = de->get_hits().at(m)->get_flagPR();
            if(!flagPR) continue;
			      int lyr = int(de->get_hits().at(m)->get_L());

            double r[3];
            rkf->getIntercept(lyr, r);
            double xreco = r[0];
            double yreco = r[1];
            de->get_hits().at(m)->set_xreco(0.10*xreco);		//in cm
            de->get_hits().at(m)->set_yreco(0.10*yreco);		//in cm
            de->get_hits().at(m)->set_fUsed(true);
            if(lyr==0)
                {
                de->get_hits().at(m)->set_cxreco(cxL0);
                de->get_hits().at(m)->set_cyreco(cyL0);
                }
            }


        //Fill in reconstruction variables in TTree
        de->set_p0reco(p0reco*1000);        //save p0reco in MeV
        de->set_chi2(chi2);
        de->set_typereco(typereco);
        de->set_cpa(cpa);
        de->set_cpaerr2(err_cpa);
        delete rkf;


        } //end RK


    /////////////////////
    //Fill the output file
    /////////////////////
    DEtree->Fill();
    //Free memory
    delete de;
   }//k End loop on events
 delete e;
 //Write tree in output file
 fileout->cd();
 DEtree->Write(0,TObject::kOverwrite);
 //Close files
 fileout->Close();
 file->Close();

 return 0;
}
