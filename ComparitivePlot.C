// Should work for comparitive plots where only rootname and name of histo would need to changed 
// Dominic Smith Nov 13

void ComparitivePlot()
{
  gROOT->Reset();

  TCanvas *c0 = new TCanvas("MGvsPY","MGvsPY", 600, 780);
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
  TString rootname1 = "JetPt1_mg2.root";
  TString rootname2 = "JetPt1_mg1_prep.root";
  rootname1 = dirname + "/" + rootname1;
  rootname2 = dirname + "/" + rootname2;
  delete gROOT->GetListOfFiles()->FindObject(rootname1);
  delete gROOT->GetListOfFiles()->FindObject(rootname2);

  std::cout << "Rootname: " << rootname1 << std::endl;
  std::cout << "Rootname2: " << rootname2 << std::endl;

  TFile *rootfile = new TFile(rootname1);
  TFile *rootfile2 = new TFile(rootname2);
  
  rootfile->GetListOfKeys()->Print();
  rootfile->ls();

  rootfile2->GetListOfKeys()->Print();
  rootfile2->ls();

  TH1F *h1 = (TH1F*)rootfile->Get("jetPt");
  c0_1->cd();
  h1->Draw("hist");
  h1->RebinX(5);
  h1->SetLineColor(2);
  h1->GetXaxis()->SetRangeUser(0,800);
  Double_t entries1 = h1->GetEntries();
  std::cout << "# Entries for manual MadGraph generated events: " << entries1 << std::endl;
  h1->Scale(1/entries1);
  h1->SetTitle("Jet P_{T} disbn for top from stops for manual MadGraph and Prep MG generated events");
  h1->GetYaxis()->SetTitle("Entries normalised");


  TH1F *h2 = (TH1F*)rootfile2->Get("jetPt");
  h2->Draw("SAME L");
  h2->RebinX(5);
  h2->SetLineColor(9);
  Double_t entries2 = h2->GetEntries();
  std::cout << "# Entries for MadGraph generated histo: " << entries2 << std::endl;
  h2->Scale(1/entries2);


  leg->AddEntry(h1, "Manual MadGraph generated events for top P_{T}, m_{t} = 500 GeV & m_{lsp} = 100 GeV", "l");
  leg->AddEntry(h2, "Prep MadGraph generated events for top P_{T}, m_{t} = 500 GeV & m_{lsp} = 100 GeV", "l");
  leg->SetTextSize(0.025);
  leg->Draw();
 

  // Create ratio histo

  c1_1->cd();
  TH1D *ratio = h1->Clone();
  TLine *l = new TLine(0,1,600,1);
  ratio->Divide( h2 );
  ratio->SetTitle("");
  ratio->SetMarkerStyle(4);
  ratio->SetMarkerSize(0.7);
  ratio->SetLineWidth(1);
  ratio->SetLineColor(1);
  ratio->GetXaxis()->SetTitle("P_{T}");
  ratio->GetYaxis()->SetTitle("Ratio");
  ratio->SetTitleSize(0.1, "Y");
  ratio->SetTitleSize(0.1, "X");
  ratio->SetLabelSize(0.07, "XY");
  ratio->SetTitleOffset(0.25, "Y");
  ratio->Draw("E1");
  l->SetLineColor(2);
  l->Draw("SAME");

  TF1 *fit = new TF1("fit","pol0",ratio->GetXaxis()->GetBinLowEdge(1),ratio->GetXaxis()->GetBinUpEdge(ratio->GetNbinsX()));
  gStyle->SetOptFit(1);
  ratio->Fit(fit);


}
