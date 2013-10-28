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
TH1D* tmass = new TH1D("tmass", "tmass", 200, 0., 400.);

Long64_t nentries = fChain->GetEntries();
Long64_t nents = b_Particle_PID->GetEntries();

TLorentzVector t, tbar, gluino, LSP;
Double_t Rcut = 0.5;
Double_t dR[100], top_mass[50];

 

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
    //std::cout << " Jet_PT[" << k << "]: " << Jet_PT[k]<< std::endl;
    //std::cout << " PID: " << Particle_PID[k] << std::endl;
    if (abs(Particle_PID[k] == 6)){
    ttbar_jetpt->Fill(Jet_PT[k]);
    ttbar_genjetpt->Fill(GenJet_PT[k]);
    }
}


  for(unsigned int j=0; j<sizeof(Jet_Eta); j++){
  
  dR[j] = sqrt((pow((Jet_Eta[j] - GenJet_Eta[j]),2) + (pow((Jet_Phi[j] - GenJet_Phi[j]),2))));

   if(Particle_PID[j] == 6){
     std::cout << "dR[" << j << "] (PID = 6) :"<< dR[j] << std::endl;
    if((dR[j] < Rcut) && (dR[j] > 0.)){
      std::cout << "Found a top quark" << std::endl;
      t.SetPx(Particle_Px[j]);
      t.SetPy(Particle_Py[j]);
      t.SetPz(Particle_Pz[j]);
      t.SetE(Particle_E[j]);
      top_mass[j] = t.M();
      tmass->Fill(top_mass[j]);
      std::cout << "Top mass: "  << t.M() << std::endl;
     }
    }
    
  if(Particle_PID[j] == -6){
     std::cout << "dR[" << j << "] (PID = -6) :"<< dR[j] << std::endl;
    if((dR[j] < Rcut) && (dR[j] > 0.)){
      std::cout << "Found an anti top quark" << std::endl;
      tbar.SetPx(Particle_Px[j]);
      tbar.SetPy(Particle_Py[j]);
      tbar.SetPz(Particle_Pz[j]);
      tbar.SetE(Particle_E[j]);
      std::cout << "Anti top mass: " << tbar.M() << std::endl;
   } 
  }
 }
}



TCanvas *c1 = new TCanvas("c1", "c1", 200, 10, 600, 400);
TCanvas *c2 = new TCanvas("c2", "c2", 200, 10, 600, 400);

c1->Clear();
ttbar_jetpt->SetLineColor(8);
h_jetPt->Draw("hist");
ttbar_jetpt->Draw("histsame");
c1->Print("ttbargetjetpt.pdf");

c2->Clear();
tmass->Draw("hist");
c2->Print("top_mass.pdf");

}

int  run(){

  MyClass m;
  
  m.Loop();

  return 0;
}





