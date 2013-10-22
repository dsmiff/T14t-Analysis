#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TGraph.h>
#include <TMath.h>
#include <iostream>
#include <TLorentzVector.h>

using namespace std;

void MyClass::Loop()
{
// To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   

// Idea is to create a TLorentzVector, then to access the particular branch to separate and extract particle properties and assign them to the TLorentzVector. 
// All branches and leaves are declared in MyClass.h
// Here b_Particle_PID is a branch, for example

  Long64_t nentries = fChain->GetEntries();
  Long64_t nents = b_Particle_PID->GetEntries();

  cout << "Working so far, printing values..." << endl;
  cout << "Number of entries: " << nentries << endl;
  cout << "Branch entries: " << nents << endl;

  Int_t n = 2000;
  Double_t mass[n], PID[n] ;

TH1D* h_jetPt = new TH1D("jetPt", "jetPt", 200, 0., 200.);

// Delphes (tree) has 2000 entries
// Loop through each Delphes entry:

for(int i = 0; i<nentries; i++){
  fChain->GetEntry(i);

  // std::cout << "AlphaQED: " << Event_AlphaQED[i] << std::endl;
 std::cout << "\nNEW EVENT" << std::endl;

  // For each Delphes entry, there are numerous entries in the branches and leaves- loop through each one:

  for(unsigned int k=0; k<sizeof(Jet_PT); k++){
    if (Jet_PT[k] < 10.) continue;
    h_jetPt->Fill(Jet_PT[k]);
    std::cout << " Jet_PT[" << k << "]: " << Jet_PT[k]<< std::endl;
  }
}


TCanvas *c1 = new TCanvas("c1", "c1", 200, 10, 600, 400);

h_jetPt->Draw("hist");
c1->Print("myTestPlot_jetPt.pdf");





// Run for loop

//  for(int i=0; i < nentries; i++){
  //   fChain->GetEntry(i);

  // cout << "Entry : " << i << endl;
    
  //    for(int j=0; j < ; j++){
  //  h.Fill(b_Particle_PID->GetBinContent(i));
  // }
  // }
  //  h.Draw();


}

int  run(){

  MyClass m;
  
  m.Loop();

  return 0;
}





