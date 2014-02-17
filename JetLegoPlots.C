// Script to analyse Jet Lego plots
// D Smith

void JetLegoPlots()
{

  gROOT->Reset();
  gStyle->SetOptStat(kFALSE);

  TCanvas *c0 = new TCanvas("JetLegoPlots","JetLegoPlots",600, 780);
  TLegend *leg = new TLegend(0.5, 0.8,0.9,0.88);

  TString dirname = ".";
  TString rootname = "JetLego.root";
  rootname = dirname + "/" + rootname;

  delete gROOT->GetListOfFiles()->FindObject(rootname);

  TFile *rootfile1 = new TFile(rootname);
  rootfile1->GetListOfKeys()->Print();
  rootfile1->ls();

  TFile *rootfile2 = new TFile(rootname);
  rootfile2->GetListOfKeys()->Print();
  rootfile2->ls();

  TFile *rootfile3 = new TFile(rootname);
  rootfile3->GetListOfKeys()->Print();
  rootfile3->ls();

  TFile *rootfile4 = new TFile(rootname);
  rootfile4->GetListOfKeys()->Print();
  rootfile4->ls();

  gStyle->SetPalette(1);

  TH1F *h1 = (TH1F*)rootfile1->Get("JetLego1"); // Highest Pt jet
  h1->GetXaxis()->SetRangeUser(0,500);
  h1->GetXaxis()->SetTitle("Jet P_{T}");
  h1->GetYaxis()->SetTitle("#eta");
  h1->SetTitleSize(0.05, "X");
  h1->SetTitleSize(0.05, "Y");
  h1->SetTitleSize(0.05, "Z");
  h1->GetZaxis()->SetTitle("Entries");
  h1->SetTitleOffset(0.7, "Z");
  h1->SetTitle("Jet Pt vs Jet Eta Lego Plot");
  h1->SetFillColor(9);
  h1->Draw("LEGO1 0");

  TH1F *h2 = (TH1F*)rootfile2->Get("JetLego2");
  h2->SetFillColor(2);
  h2->Draw("SAME LEGO1 0");

  TH1F *h3 = (TH1F*)rootfile3->Get("JetLego3");
  h3->SetFillColor(6);
  h3->Draw("SAME LEGO1 0");

  TH1F *h4 = (TH1F*)rootfile4->Get("JetLego4");
  h4->SetFillColor(3);
  h4->Draw("SAME LEGO1 0");

  leg->AddEntry(h1, "1st Jet", "f");
  leg->AddEntry(h2, "2nd Jet", "f");
  leg->AddEntry(h3, "3rd Jet", "f");
  leg->AddEntry(h4, "4th Jet", "f");
  leg->SetFillStyle(0);
  leg->Draw();


}
