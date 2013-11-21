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
#include <TObject.h>
#include <iostream>

using namespace std;
 
int MyClass::GetNJets(){

  int nJet = 0;
  for (int i = 0; i < sizeof(Jet_PT); ++i)
  {
    if (Jet_PT[i]<10.) continue;
    nJet++;
  }
  std::cout << "NJets: " << nJet << std::endl;
 } 


void MyClass::Loop()
{
                                                                                                                         
// Declaring histograms

  TH1::SetDefaultSumw2();

  JetPT = new TH1D("jetPt", "jetPt", 200, 0., 200.);
  h_genjetPt = new TH1D("genjetPt", "genjetPt", 200, 0., 200.);
  ttbar_jetpt = new TH1D("ttbar_jetpt", "ttbar_jetpt", 200, 0., 200.);
  ttbar_genjetpt = new TH1D("ttbar_genjetpt", "ttbar_genjetpt", 200, 0., 200.);
  tmass = new TH1D("tmass", "tmass", 200, 0., 400.);
  TopPt = new TH1D("TopPt", "TopPt", 200, 0., 800.);
  Top_Gluino = new TH1D("Top_Gluino", "Top_Gluino", 200, 0., 800.);
  Top_Stop = new TH1D("Top_Stop", "Top_Stop", 200, 0., 800.);
  MET_histo = new TH1D("MET_histo", "MET_histo", 200, 0., 2500.);
  delR = new TH1D("delR", "delR", 0.1, 0, 1.5);
  JetET = new TH1D("JetET", "JetET", 200, 0., 1500.);
  delphi_gluino = new TH1D("delphi_gluino","delphi_gluino", 200, -5, 5);


Long64_t nentries = fChain->GetEntries();
Long64_t nents = b_Particle_PID->GetEntries();

for(int i = 0; i<nentries; i++){
  fChain->GetEntry(i);
      std::cout << "\nNEW EVENT [" << i << " of " << nentries << "]" << std::endl;






for(unsigned int e=0; e<sizeof(MissingET_MET); e++){
 // std::cout << "MET: " << MissingET_MET[e] << std::endl; // Which PID gives the most MET?
  if(MissingET_MET[e]> 5){
  MET_histo->Fill(MissingET_MET[e]);
 }
}

int nstop = 0;
int ngluino = 0;
int njets = 0;
Double_t HT = 0.0;
Double_t Jet_ET[kMaxEvent];
Double_t dR[100], Pt_top[sizeof(Particle_PT)];



for(unsigned int q=0; q<sizeof(Particle_PT); q++){

    if(abs(Particle_PID[q]) == 6 && Particle_Status[q] == 2) {             
   //   std::cout << "Found a top quark" << std::endl;
      TopPt->Fill(Particle_PT[q]);                                            // This has contributions from gluino and stop
      Pt_top[q] = Particle_PT[q];
   //   std::cout << "'---> Top Pt [" << q << "] : " << Pt_top[q] << std::endl;
    //  std::cout << "       '---> Mother PID: " << Particle_PID[Particle_M1[q]] << std::endl;
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
  if(ngluino != nstop){
    std::cout << "WRONG" << ngluino << nstop << std::endl;
  }



// Assigning particles their TLorentzVectors
// Need count ticker for non desirable particles, otherwise if statement loops infinitely  

  int nlsp = 0;
  int nglu = 0;
  int ntop = 0;
  int nstp = 0;

for(unsigned int r=0; r<sizeof(Particle_PID); ){


int count = 0;

    if(abs(Particle_PID[r]) == 1000022 && nlsp ==0){
      LSP1.SetPx(Particle_Px[r]);
      LSP1.SetPy(Particle_Py[r]);
      LSP1.SetPz(Particle_Pz[r]);
      LSP1.SetE(Particle_E[r]);
      nlsp++;
      count++;
      r++;
  }
    if(abs(Particle_PID[r]) == 1000022 && nlsp == 1){   
      LSP2.SetPx(Particle_Px[r]);
      LSP2.SetPy(Particle_Py[r]);
      LSP2.SetPz(Particle_Pz[r]);
      LSP2.SetE(Particle_E[r]);
      nlsp++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 1000021 && nglu == 0){
      g1.SetPx(Particle_Px[r]);
      g1.SetPy(Particle_Py[r]);
      g1.SetPz(Particle_Pz[r]);
      g1.SetE(Particle_E[r]);
      nglu++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 1000021 && nglu == 1){
      g2.SetPx(Particle_Px[r]);
      g2.SetPy(Particle_Py[r]);
      g2.SetPz(Particle_Pz[r]);
      g2.SetE(Particle_E[r]);
      nglu++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 1000006 && nstp ==0){
      stop1.SetPx(Particle_Px[r]);
      stop1.SetPy(Particle_Py[r]);
      stop1.SetPz(Particle_Pz[r]);
      stop1.SetE(Particle_E[r]);
      nstp++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 1000006 && nstp ==1){
      stop2.SetPx(Particle_Px[r]);
      stop2.SetPy(Particle_Py[r]);
      stop2.SetPz(Particle_Pz[r]);
      stop2.SetE(Particle_E[r]);
      nstp++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 6 && ntop == 0){
      top1.SetPx(Particle_Px[r]);
      top1.SetPy(Particle_Py[r]);
      top1.SetPz(Particle_Pz[r]);
      top1.SetE(Particle_E[r]);
      ntop++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 6 && ntop ==1){
      top2.SetPx(Particle_Px[r]);
      top2.SetPy(Particle_Py[r]);
      top2.SetPz(Particle_Pz[r]);
      top2.SetE(Particle_E[r]);
      ntop++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 6 && ntop ==2){
      top3.SetPx(Particle_Px[r]);
      top3.SetPy(Particle_Py[r]);
      top3.SetPz(Particle_Pz[r]);
      top3.SetE(Particle_E[r]);
      ntop++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 6 && ntop == 3){
      top4.SetPx(Particle_Px[r]);
      top4.SetPy(Particle_Py[r]);
      top4.SetPz(Particle_Pz[r]);
      top4.SetE(Particle_E[r]);
      ntop++;
      count++;
      r++;
    }
    if(count == 0){
      r++;
    }
  }
// Check there are two of each for gluinos and LSPs
  if( nglu != nlsp){
    std::cout << "Not an equal amount of LSPs and Gluinos" << std::endl;
  }

   MET = sqrt(pow(LSP1.Px() + LSP2.Px(),2) + pow(LSP1.Py() + LSP2.Py(),2) + pow(LSP1.Pz() + LSP2.Pz(),2));







  for(unsigned int k=0; k<sizeof(Jet_PT); k++){
    if(Jet_PT[k] > 20. && Jet_Mass[k] > 0.1){
//   std::cout << "Jet Pt[" << k << "] : " << Jet_PT[k]<< std::endl;
//   std::cout << "Jet Mass: " << Jet_Mass[k] << std::endl;
    Jet_ET[k] = sqrt(pow(Jet_PT[k],2) + pow(Jet_Mass[k],2));
  //  std::cout << "Jet ET[" << k << "] : " << Jet_ET[k]  << std::endl;
    HT+=Jet_ET[k];
    JetPT->Fill(Jet_PT[k]);
    njets++;
    }
    if(GenJet_PT[k] > 10.){
      h_genjetPt->Fill(GenJet_PT[k]);
    }
    if(abs(Particle_PID[k]) == 6){
   //   std::cout << "Jet PT for t: " << Jet_PT[k] << std::endl;
    ttbar_jetpt->Fill(Jet_PT[k]);
    ttbar_genjetpt->Fill(GenJet_PT[k]);
    } 
}
 // std::cout << "Number of jets per event: " << njets << std::endl;
  std::cout << HT << std::endl;
  JetET->Fill(HT);













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
TCanvas *c7 = new TCanvas("c7", "c7", 200, 10, 600, 400);
TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);


c1->Clear();
JetPT->Draw("hist");
JetPT->SetTitle("P_{T} of Jets");
JetPT->Draw();
JetPT->GetXaxis()->SetTitle("P_{T} of jets");
JetPT->GetYaxis()->SetTitle("Entries");
//h_genjetPt->Draw("histsame");
//ttbar_jetpt->Draw("histsame");
//c1->Print("jetpt.pdf");

c2->Clear();
tmass->Draw("hist");
//c2->Print("top_mass.pdf");

c3->Clear();
TopPt->Draw("hist");
//c3->Print("TopPt.pdf");

c4->Clear();
TFile *PTgluino_stop = new TFile("PTgluino_500_300.root","RECREATE");
Top_Gluino->Draw("hist");
Top_Gluino->Write();
Top_Gluino->SetTitle("P_{T} from stop (500 GeV) and gluino (1 TeV) ");
Top_Gluino->GetXaxis()->SetTitle("P_{T} of top");
Top_Gluino->GetYaxis()->SetTitle("Entries");
Top_Stop->Draw("SAME");
Top_Stop->SetLineColor(2);
Top_Stop->Draw("SAME");
leg->AddEntry(Top_Gluino, "PT of top from gluino", "l");
leg->AddEntry(Top_Stop, "PT of top from stop", "l");
leg->Draw();
c4->Print("PtTopGluino.pdf");


TFile *PTstop_top = new TFile("PT_pyth_500_100.root", "RECREATE");
Top_Stop->Write();

TFile *f = new TFile("MET_pyth_500_100.root", "RECREATE");
MET_histo->Draw("hist");
MET_histo->Write();


c7->Clear();
TFile *g = new TFile("JetET.root", "RECREATE");
JetET->Write();
c7->Print("JetET.pdf");

TFile *delphi_gluino = new TFile("delphi_gluino.root", "RECREATE");
delphi_gluino->Write();




}
/*
int  run(){

  MyClass m;
  
  m.Loop();

  return 0;
}
*/




