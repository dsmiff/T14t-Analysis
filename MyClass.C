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
                                                                                                                         

// Declaring histograms

TH1D* h_jetPt = new TH1D("jetPt", "jetPt", 200, 0., 200.);
TH1D* h_genjetPt = new TH1D("genjetPt", "genjetPt", 200, 0., 200.);
TH1D* ttbar_jetpt = new TH1D("ttbar_jetpt", "ttbar_jetpt", 200, 0., 200.);
TH1D* ttbar_genjetpt = new TH1D("ttbar_genjetpt", "ttbar_genjetpt", 200, 0., 200.);
TH1D* tmass = new TH1D("tmass", "tmass", 200, 0., 400.);
TH1D* TopPt = new TH1D("TopPt", "TopPt", 200, 0., 800.);
TH1D* Top_Gluino = new TH1D("Top_Gluino", "Top_Gluino", 200, 0., 800.);
TH1D* Top_Stop = new TH1D("Top_Stop", "Top_Stop", 200, 0., 800.);
TH1D* MET_histo = new TH1D("MET_histo", "MET_histo", 200, 0., 2500.);
TH1D* delR = new TH1D("delR", "delR", 0.1, 0, 1.5);
// TH2D* Pt_top_vs_delR = new TH2D("Pt_top_vs_delR","Pt_top_vs_delR",200, 0., 400., 200, 0., 5.);


Long64_t nentries = fChain->GetEntries();
Long64_t nents = b_Particle_PID->GetEntries();

 // Declaring particles involved

TLorentzVector t, tbar, gluino, LSP1, LSP2, stop;
Double_t Rcut = 0.5;
Double_t dR[100], top_mass[50], Pt_top[sizeof(Particle_PT)];
Double_t MET;

// Delphes (tree) has 2000 entries, loop through each entry:

for(int i = 0; i<nentries; i++){
  fChain->GetEntry(i);
      std::cout << "\nNEW EVENT [" << i << " of " << nentries << "]" << std::endl;
      std::cout << "Jet Size: " << Jet_size << std::endl;     // Could this indicate how many jets per event?
      std::cout << "Gen Jet Size: " << GenJet_size << std::endl;

for(unsigned int e=0; e<sizeof(MissingET_MET); e++){
 // std::cout << "MET: " << MissingET_MET[e] << std::endl; // Which PID gives the most MET?
  if(MissingET_MET[e]> 5){
  MET_histo->Fill(MissingET_MET[e]);
 }
}

int nstop = 0;
int ngluino = 0;

for(unsigned int q=0; q<sizeof(Particle_PT); q++){

    if(abs(Particle_PID[q]) == 6 && Particle_Status[q] == 2) {             
      std::cout << "Found a top quark" << std::endl;
      TopPt->Fill(Particle_PT[q]);                                            // This has contributions from gluino and stop
      Pt_top[q] = Particle_PT[q];
      std::cout << "'---> Top Pt [" << q << "] : " << Pt_top[q] << std::endl;
      std::cout << "       '---> Mother PID: " << Particle_PID[Particle_M1[q]] << std::endl;
    }

    if(abs(Particle_PID[q]) == 6 && Particle_PID[Particle_M1[q]] == 1000021){           // 1000021 is a gluino
      Top_Gluino->Fill(Particle_PT[q]);
      ngluino++;
    }
    if(abs(Particle_PID[q]) == 6 && abs(Particle_PID[Particle_M1[q]]) == 1000006){      //  1000006 is a stop
      Top_Stop->Fill(Particle_PT[q]);         
    nstop++;
      }
}
    // Compute MET

for(unsigned int r=0; r<sizeof(Particle_PID); r++){
    if(abs(Particle_PID[r]) == 1000022 && r <= 10) {
     // std::cout << "Found LSP [" << r << "]" << std::endl;
      LSP1.SetPx(Particle_Px[r]);
      LSP1.SetPy(Particle_Py[r]);
      LSP1.SetPz(Particle_Pz[r]);
      LSP1.SetE(Particle_E[r]);
 //     std::cout << "LSP1 Px: " << LSP1.Px() << std::endl;
 //     std::cout << "LSP1 Py: " << LSP1.Py() << std::endl;
 //     std::cout << "LSP1 Pz: " << LSP1.Pz() << std::endl;
    }
    if(abs(Particle_PID[r]) == 1000022 && r >= 10){         // this needs to be redone
   //   std::cout << "Found LSP [" << r << "]" << std::endl;
      LSP2.SetPx(Particle_Px[r]);
      LSP2.SetPy(Particle_Py[r]);
      LSP2.SetPz(Particle_Pz[r]);
      LSP2.SetE(Particle_E[r]);
 //     std::cout << "LSP2 Px: " << LSP2.Px() << std::endl;
 //     std::cout << "LSP2 Py: " << LSP2.Py() << std::endl;
 //     std::cout << "LSP2 Pz: " << LSP2.Pz() << std::endl;
    }
     }
      MET = sqrt(pow(LSP1.Px() + LSP2.Px(),2) + pow(LSP1.Py() + LSP2.Py(),2) + pow(LSP1.Pz() + LSP2.Pz(),2));
      std::cout << "MET: " << MET << std::endl;             // Read out Px, Py, Pz to compute myself and check


  if(ngluino != nstop){
    std::cout << "WRONG" << ngluino << nstop << std::endl;
  }


  for(unsigned int k=0; k<sizeof(Jet_PT); k++){
    if (Jet_PT[k] > 10.){
    h_jetPt->Fill(Jet_PT[k]);
    }
    if(GenJet_PT[k] > 10.){
      h_genjetPt->Fill(GenJet_PT[k]);
    }
    //    std::cout << " Jet_PT[" << k << "]: " << Jet_PT[k]<< std::endl;
    //std::cout << " GenJet_PT[" << k << "]: " << GenJet_PT[k] << std::endl;
    //std::cout << " PID: " << Particle_PID[k] << std::endl;
    if (abs(Particle_PID[k] == 6)){
    ttbar_jetpt->Fill(Jet_PT[k]);
    ttbar_genjetpt->Fill(GenJet_PT[k]);
    }
}






/*
  for(unsigned int j=0; j<sizeof(Jet_Eta); j++){
  
  dR[j] = sqrt((pow((Jet_Eta[j] - GenJet_Eta[j]),2) + (pow((Jet_Phi[j] - GenJet_Phi[j]),2))));
  //  std::cout << "Size of Delta R : " << sizeof(dR) << std::endl;
  //std::cout << "Delta R : " << dR[j] << std::endl;


   if(Particle_PID[j] == 6){
    // std::cout << "dR[" << j << "] (PID = 6) :"<< dR[j] << std::endl;
    if((dR[j] < Rcut) && (dR[j] > 0.)){
      std::cout << "Found a top quark" << std::endl;
      t.SetPx(Particle_Px[j]);
      t.SetPy(Particle_Py[j]);
      t.SetPz(Particle_Pz[j]);
      t.SetE(Particle_E[j]);
      top_mass[j] = t.M();
      tmass->Fill(top_mass[j]);
      delR->Fill(dR[j]);
   //   std::cout << " Particle Mother M1: " << Particle_M1[j] << std::endl;
   //   std::cout << " Particle Mother M2: " << Particle_M2[j] << std::endl;
     // std::cout << " ---> Top mass: "  << t.M() << std::endl;
    // }
    }
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
 } */
}


// Printing histograms


TCanvas *c1 = new TCanvas("c1", "c1", 200, 10, 600, 400);
TCanvas *c2 = new TCanvas("c2", "c2", 200, 10, 600, 400);
TCanvas *c3 = new TCanvas("c3", "c3", 200, 10, 600, 400);
TCanvas *c4 = new TCanvas("c4", "c4", 200, 10, 600, 400);
TCanvas *c5 = new TCanvas("c5", "c5", 200, 10, 600, 400);
TCanvas *c6 = new TCanvas("c6", "c6", 200, 10, 600, 400);
//TCanvas *c7 = new TCanvas("c7", "c7", 200, 10, 600, 400);
TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);


c1->Clear();
ttbar_jetpt->SetLineColor(8);
h_jetPt->Draw("hist");
h_jetPt->SetLineColor(2);
h_jetPt->Draw();
h_genjetPt->Draw("histsame");
//ttbar_jetpt->Draw("histsame");
c1->Print("gen_jetpt.pdf");

c2->Clear();
tmass->Draw("hist");
c2->Print("top_mass.pdf");

c3->Clear();
TopPt->Draw("hist");
c3->Print("TopPt.pdf");

c4->Clear();
TFile *PTgluino_stop = new TFile("PTgluino_500_100.root","RECREATE");
Top_Gluino->Draw("hist");
Top_Gluino->Write();
Top_Gluino->SetTitle("P_{T} from stop (800 GeV) and gluino (1 TeV) ");
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
TFile *PTstop_top = new TFile("PT_500_100.root", "RECREATE");
Top_Stop->Draw("hist");
Top_Stop->Write();

// MET histo

 c6->Clear();
 TFile *f = new TFile("MET_500_100.root", "RECREATE");
 MET_histo->Draw("hist");
 MET_histo->Write();
 c6->Print("MET.pdf");

// Plot delta R

//c7->Clear();
//Pt_top_vs_delR->Fill(Pt_top,delR);
//Pt_top_vs_delR->Draw("hist");
//c7->Print("Pt_top_vs_delR.pdf");



}

int  run(){

  MyClass m;
  
  m.Loop();

  return 0;
}





