// Test macro for comparitive plot before using the main

void ComparitivePlotTest()
{

  gROOT->Reset();

  TCanvas *c0 = new TCanvas("MGvsPY_test", "MGvsPY_test", 600, 780);
  TLegend *leg = new TLegend(0.5, 0.8, 0.9, 0.88);
  TPad *c0_1 = new TPad("pd1","pd1", 0., 0.3, 1., 1.);
  c0_1->SetBottomMargin(0.005);
  c0_1->SetRightMargin(0.05);
  c0_1->Draw();
  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.1);

  TPad *c1_1 = new TPad("pd2", "pd2", 0., 0.02, 1., 0.3);
  c1_1->SetTopMargin(0.05);
  c1_1->SetBottomMargin(0.26);
  c1_1->SetRightMargin(0.05);
  c1_1->SetGridx(1);
  c1_1->SetGridy(1);
  c1_1->Draw();

  TString dirname = ".";
  TString rootname1 = "JetPT_pyth_500_100.root";
  TString rootname2 = "JetPT_500_100.root";
  
  rootname1 = dirname + "/" + rootname1;
  rootname2 = dirname + "/" + rootname2;
  delete gROOT->GetListOfFiles()->FindObject(rootname1);
  delete gROOT->GetListOfFiles()->FindObject(rootname2);

  // Check we've laoded the right histos

  std::cout << "Rootname1: " << rootname1 << std::endl;
  std::cout << "Rootname2: " << rootname2 << std::endl;

  // Open new TFile
  TFile *rootfile = new TFile(rootname1);
  TFile *rootfile2 = new TFile(rootname2);

  rootfile->GetListOfKeys()->Print();
  rootfile->ls();

  rootfile2->GetListOfKeys()->Print();
  rootfile2->ls();

  // Declare new histos to test comparitive plot

  TH1F *h1 = (TH1F*)rootfile->Get("jetPt");
  Double_t entries1 = h1->GetEntries();
  h1->Draw("hist");
  h1->RebinX(5);
  h1->Scale(1/entries1);
  

  TH1F *h2 = (TH1F*)rootfile2->Get("jetPt");
  Double_t entries2 = h2->GetEntries();
  h2->Draw("SAME");
  h2->RebinX(5);
  h2->SetLineColor(2);
  h2->Scale(1/entries2);               // Only interested in shape of distbn

  // Check the no. of entries are the same from the .root file

  std::cout << "# entries for histo1: " << entries1 << std::endl;
  std::cout << "# entries for histo2: " << entries2 << std::endl;





}
