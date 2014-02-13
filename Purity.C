// Purity test of some sort between GenJet PT and Jet PT 
// for the anti-kt clustering algorithm

void Purity()
{

  gROOT->Reset();
  
  TCanvas *c0 = new TCanvas("GenJetPtvsJetPT", "GenJetPtvsJetPT", 600, 780);
  TLegend *leg = new TLegend(0.5, 0.4, 0.9, 0.88);
  TPad *c0_1 = new TPad("pd1", "pd1", 0., 0.3, 1., 1.);

  c0_1->SetBottomMargin(0.005);
  c0_1->SetRightMargin(0.05);
  c0_1->Draw();
  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.045);

  TPad *c1_1 = new TPad("pd2", "pd2", 0., 0.02, 1., 0.3);
  c1_1->SetTopMargin(0.05);
  c1_1->SetBottomMargin(0.26);
  c1_1->SetRightMargin(0.05);
  c1_1->SetGridx(1);
  c1_1->SetGridy(1);
  c1_1->Draw();


  TString dirname = ".";
  TString rootname1 = "LeadingJetPT_MG_500_300.root";
  rootname1 = dirname + "/" + rootname1;

  delete gROOT->GetListOfFiles()->FindObject(rootname1);
  
  std::cout << "Rootname: " << rootname1 << std::endl;

  TFile *rootfile = new TFile(rootname1);

  rootfile->GetListOfKeys()->Print();
  rootfile->ls();

  // 1st Leading Jet

  TH1F *h1 = (TH1F*)rootfile->Get("_JetPt1");
  c0_1->cd();
  h1->Draw("hist");
  h1->SetTitle("Leading Jet P_{T} distributions");
  h1->GetYaxis()->SetTitle("Events");
  h1->SetTitleSize(0.05, "Y");
  h1->SetLineColor(4);
  Double_t entries1 = h1->GetEntries();
  std::cout << "No. entries for Jet PT (1): " << entries1 << std::endl;
  h1->Scale(1/entries1);
  


  TH1F *h2 = (TH1F*)rootfile->Get("GenJetPt1");
  h2->Draw("SAME L");
  h2->SetLineColor(2);
  Double_t entries2 = h2->GetEntries();
  std::cout << "No. entries for Gen Jet PT (1): " << entries2 << std::endl;
  h2->Scale(1/entries1);

  leg->AddEntry(h1, "1st Jet P_{T}", "l");
  leg->AddEntry(h2, "1st Gen Jet P_{T}", "l");
  leg->AddEntry((TObject*)0, "", "");
  leg->AddEntry((TObject*)0, "m_{stop} = 500 GeV", "");
  leg->AddEntry((TObject*)0, "m_{lsp} = 300 GeV", "");
  leg->SetTextSize(0.045);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->Draw();
  

  c1_1->cd();
  TH1D *h1_h2 = h2->Clone();
  h1_h2->Divide(h1);
  h1_h2->SetLineColor(1);
  h1_h2->GetXaxis()->SetTitle("P_{T}^{jet}");
  h1_h2->GetYaxis()->SetTitle("#epsilon_{jet}");
  h1_h2->GetYaxis()->CenterTitle();
  h1_h2->SetTitleSize(0.14, "Y");
  h1_h2->SetTitleSize(0.11, "X");
  h1_h2->SetTitle("");
  h1_h2->SetTitleOffset(0.25, "Y");
  h1_h2->Draw();


  
}
  


