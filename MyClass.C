#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TGraph.h>
#include <TMath.h>
#include <TRefArray.h>
#include <TLegend.h>
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


// Declaring histograms

TH1D* h_jetPt = new TH1D("jetPt", "jetPt", 200, 0., 200.);
TH1D* ttbar_jetpt = new TH1D("ttbar_jetpt", "ttbar_jetpt", 200, 0., 200.);
TH1D* ttbar_genjetpt = new TH1D("ttbar_genjetpt", "ttbar_genjetpt", 200, 0., 200.);
TH1D* tmass = new TH1D("tmass", "tmass", 200, 0., 400.);
TH1D* TopPt = new TH1D("TopPt", "TopPt", 200, 0., 800.);
TH1D* Top_Gluino = new TH1D("Top_Gluino", "Top_Gluino", 200, 0., 800.);
TH1D* Top_Stop = new TH1D("Top_Stop", "Top_Stop", 200, 0., 800.);
TH1D* MET_histo = new TH1D("MET_histo", "MET_histo", 200, 0., 2500.);


Long64_t nentries = fChain->GetEntries();
Long64_t nents = b_Particle_PID->GetEntries();

 // Declaring things to use

TLorentzVector t, tbar, gluino, LSP, stop;
Double_t Rcut = 0.5;
Double_t dR[100], top_mass[50];
Double_t MET[nentries];

// Delphes (tree) has 2000 entries
// Loop through each Delphes entry:

for(int i = 0; i<nentries; i++){
  fChain->GetEntry(i);
      std::cout << "\nNEW EVENT [" << i << " of " << nentries << "]" << std::endl;

  for(unsigned int e=0; e<sizeof(GenJet_PT); e++){
    MET[i] += abs(GenJet_PT[e]);
    MET_histo->Fill(MET[i]);
  }
     std::cout << "MET[" << i << "]: " << MET[i] << std::endl;

int nstop = 0;
int ngluino = 0;

for(unsigned int q=0; q<sizeof(Particle_PT); q++){

    if(abs(Particle_PID[q]) == 6 && Particle_Status[q] == 2) {
      TopPt->Fill(Particle_PT[q]);
      std::cout << "Top Pt [" << q << "] : " << Particle_PT[q] << std::endl;
      std::cout << "Top Mother: " << Particle_M1[q] << std::endl;
      std::cout << "Mother PID: " << Particle_PID[Particle_M1[q]] << std::endl;
    }
    if(abs(Particle_PID[q]) == 6 && Particle_PID[Particle_M1[q]] == 1000021){
      Top_Gluino->Fill(Particle_PT[q]);
      ngluino++;
    }
    if(abs(Particle_PID[q]) == 6 && abs(Particle_PID[Particle_M1[q]]) == 1000006){
      Top_Stop->Fill(Particle_PT[q]);
    nstop++;
      }
  }
  if(ngluino != nstop){
    std::cout << "WRONG" << ngluino << nstop << std::endl;
  }







  // For each Delphes entry, there are numerous entries in the branches and leaves- loop through each one:
  // NOT PART OF THE MAIN ANALYSIS

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
  
//  dR[j] = sqrt((pow((Jet_Eta[j] - GenJet_Eta[j]),2) + (pow((Jet_Phi[j] - GenJet_Phi[j]),2))));

   if(Particle_PID[j] == 6){
    // std::cout << "dR[" << j << "] (PID = 6) :"<< dR[j] << std::endl;
   // if((dR[j] < Rcut) && (dR[j] > 0.)){
    //  std::cout << "Found a top quark" << std::endl;
      t.SetPx(Particle_Px[j]);
      t.SetPy(Particle_Py[j]);
      t.SetPz(Particle_Pz[j]);
      t.SetE(Particle_E[j]);
      top_mass[j] = t.M();
      tmass->Fill(top_mass[j]);
   //   std::cout << " Particle Mother M1: " << Particle_M1[j] << std::endl;
   //   std::cout << " Particle Mother M2: " << Particle_M2[j] << std::endl;
     // std::cout << " ---> Top mass: "  << t.M() << std::endl;
    // }
    }
    
  if (Particle_PID[j] == -6){
    // std::cout << "dR[" << j << "] (PID = -6) :"<< dR[j] << std::endl;
    if((dR[j] < Rcut) && (dR[j] > 0.)){
     // std::cout << "Found an anti top quark" << std::endl;
      tbar.SetPx(Particle_Px[j]);
      tbar.SetPy(Particle_Py[j]);
      tbar.SetPz(Particle_Pz[j]);
      tbar.SetE(Particle_E[j]);
      //std::cout << " ---> Anti top mass: " << tbar.M() << std::endl;
   } 
  }

  if (Particle_PID[j] == 1000021){
   //   std::cout << " Found a gluino" << std::endl;
    gluino.SetPx(Particle_Px[j]);
    gluino.SetPy(Particle_Py[j]);
    gluino.SetPz(Particle_Pz[j]);
    gluino.SetE(Particle_E[j]);
  //  std::cout << " ----> Gluino mass: " << gluino.M() << std::endl;
  //  std::cout << " ----> Gluino status: " << Particle_Status[j] << std::endl;
  }

  if (Particle_PID[j] == 1000022){
  //  std::cout << " Found LSP" << std::endl;
    LSP.SetPx(Particle_Px[j]);
    LSP.SetPy(Particle_Py[j]);
    LSP.SetPz(Particle_Pz[j]);
    LSP.SetE(Particle_E[j]);
 //   std::cout << " ----> LSP mass: " << LSP.M() << std::endl;
 //   std::cout << " ----> LSP status: " << Particle_Status[j] << std::endl;
  }

  if (Particle_PID[j] == 100006){
 //   std::cout << "Foud stop quark" << std::endl;
    stop.SetPx(Particle_Px[j]);
    stop.SetPy(Particle_Py[j]);
    stop.SetPz(Particle_Pz[j]);
    stop.SetE(Particle_E[j]);
  //  std::cout << "----> Stop mass: " << stop.M() << std::endl;
  }
 }
}


// Printing histograms


TCanvas *c1 = new TCanvas("c1", "c1", 200, 10, 600, 400);
TCanvas *c2 = new TCanvas("c2", "c2", 200, 10, 600, 400);
TCanvas *c3 = new TCanvas("c3", "c3", 200, 10, 600, 400);
TCanvas *c4 = new TCanvas("c4", "c4", 200, 10, 600, 400);
TCanvas *c5 = new TCanvas("c5", "c5", 200, 10, 600, 400);
TCanvas *c6 = new TCanvas("c6", "c6", 200, 10, 600, 400);
TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);


c1->Clear();
ttbar_jetpt->SetLineColor(8);
h_jetPt->Draw("hist");
ttbar_jetpt->Draw("histsame");
c1->Print("ttbargetjetpt.pdf");

c2->Clear();
tmass->Draw("hist");
c2->Print("top_mass.pdf");

c3->Clear();
TopPt->Draw("hist");
c3->Print("TopPt.pdf");

c4->Clear();
Top_Gluino->Draw("hist");
Top_Gluino->SetTitle("P_{T} from stop (825 GeV) and gluino (1 TeV) ");
Top_Gluino->GetXaxis()->SetTitle("P_{T} of top");
Top_Gluino->GetYaxis()->SetTitle("Entries");
Top_Stop->Draw("SAME");
Top_Stop->SetLineColor(2);
Top_Stop->Draw("SAME");
leg->AddEntry(Top_Gluino, "PT of top from gluino", "l");
leg->AddEntry(Top_Stop, "PT of top from stop", "l");
leg->Draw();
c4->Print("PtTopGluino.pdf");

// Saving histo of PT of stop from top 

c5->Clear();
TFile *PTstop_top = new TFile("PT_200_100.root", "RECREATE");
Top_Stop->Draw("hist");
Top_Stop->Write();

// MET histo

 c6->Clear();
 TFile *f = new TFile("MET_200_100.root", "RECREATE");
 MET_histo->Draw("hist");
 MET_histo->Write();
 c6->Print("MET.pdf");



}

int  run(){

  MyClass m;
  
  m.Loop();

  return 0;
}





