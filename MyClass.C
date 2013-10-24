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


TH1D* h_jetPt = new TH1D("jetPt", "jetPt", 200, 0., 200.);
TH1D* ttbar_jetpt = new TH1D("ttbar_jetpt", "ttbar_jetpt", 200, 0., 200.);
TH1D* ttbar_genjetpt = new TH1D("ttbar_genjetpt", "ttbar_genjetpt", 200, 0., 200.);

  Long64_t nentries = fChain->GetEntries();
  Long64_t nents = b_Particle_PID->GetEntries();

TLorentzVector t, tbar, gluino, LSP;
Double_t deltaR[48]; 

  cout << "Working so far, printing values..." << endl;
  cout << "Number of entries: " << nentries << endl;
  cout << "Branch entries: " << nents << endl;
  

// Delphes (tree) has 2000 entries
// Loop through each Delphes entry:

for(int i = 0; i<nentries; i++){
  fChain->GetEntry(i);

    std::cout << "\nNEW EVENT" << std::endl;

  // For each Delphes entry, there are numerous entries in the branches and leaves- loop through each one:

  for(unsigned int k=0; k<sizeof(Jet_PT); k++){
    if (Jet_PT[k] < 10.) continue;
    h_jetPt->Fill(Jet_PT[k]);
    std::cout << " Jet_PT[" << k << "]: " << Jet_PT[k]<< std::endl;
    std::cout << " PID: " << Particle_PID[k] << std::endl;
    if (abs(Particle_PID[k] == 6)){
    ttbar_jetpt->Fill(Jet_PT[k]);
    ttbar_genjetpt->Fill(GenJet_PT[k]);
    }
}
/*
    for(unsigned int l=0; l<sizeof(Particle_PID); l++){
      if(Particle_PID[l] == 6){
    cout << " Found a top quark" << endl;
  t.SetPx(Particle_Px[l]);
  t.SetPy(Particle_Py[l]);
  t.SetPz(Particle_Pz[l]);
  t.SetE(Particle_E[l]);
  }
      else if(Particle_PID[l] == -6){
    cout << " Found an anti-top quark" << endl;
  tbar.SetPx(Particle_Px[l]);
  tbar.SetPy(Particle_Py[l]);
  tbar.SetPz(Particle_Pz[l]);
  tbar.SetE(Particle_E[l]);  
  }
 } */

  for(unsigned int p=0; p<sizeof(Particle_PID); p++){
    if(Particle_PID[p] == 10000021){
      std::cout << "Found an LSP" << std::endl;
    LSP.SetPx(Particle_Px[p]);
    LSP.SetPy(Particle_Py[p]);
    LSP.SetPz(Particle_Pz[p]);
    LSP.SetE(Particle_E[p]);
    }
  }

  for(unsigned int a=0; a<sizeof(Jet_DeltaEta); a++){
    deltaR[a] = sqrt((pow((Jet_DeltaEta[a]),2) + (pow((Jet_DeltaPhi[a]),2))));
    std::cout << "Delta R[" << a << "] : " << deltaR[a] << std::endl;
  }

}



TCanvas *c1 = new TCanvas("c1", "c1", 200, 10, 600, 400);

c1->Clear();
ttbar_jetpt->SetLineColor(8);
h_jetPt->Draw("hist");
ttbar_jetpt->Draw("histsame");
c1->Print("ttbargetjetpt.pdf");

}

int  run(){

  MyClass m;
  
  m.Loop();

  return 0;
}





