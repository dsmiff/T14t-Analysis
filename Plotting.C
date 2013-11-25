// General macro for ROOT histos
// D.Smith

void Plotting()
{

  gROOT->Reset()

  TCanvas *c0 = new TCanvas("plots","MET", 600, 780);
  TLegend *leg = new TLegend(0.5,0.8,0.9,0.88);
  
  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.06);

  TString dirname = ".";
  TString rootname = "MET_pyth_500_100.root";
  rootname = dirname + "/" + rootname;
  delete gROOT->GetListOfFiles()->FindObject(rootname);

  std::cout << "Rootname: " << rootname << std::endl;

  TFile *rootfile = new TFile(rootname);

  rootfile->GetListOfKeys()->Print();
  rootfile->ls();

  TH1F *h1  = (TH1F*)rootfile->Get("MET_histo");
  c0->cd();
  h1->Draw("hist");
  h1->SetTitle("MET > 5 GeV, as defined by Delphes");
  h1->GetXaxis()->SetTitle("MET");
  h1->GetYaxis()->SetTitle("Entries");
  // h1->Rebin(); // Only if neccessary

  Double_t entries = h1->GetEntries();
  std::cout << "# entries for histo: " << entries << std::endl;

  leg->AddEntry(h1, "MET for m_{stop} = 500 GeV, m_{lsp} = 100 GeV", "l");
  leg->Draw();
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);

}



