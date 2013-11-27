// General macro for ROOT histos
// D.Smith

void Plotting()
{

  gROOT->Reset()

  TCanvas *c0 = new TCanvas("plots","HT_1000", 600, 780);
  TLegend *leg = new TLegend(0.5,0.8,0.9,0.88);
  
  gStyle->SetOptStat(0);
  gStyle->SetTitleFontSize(0.06);

  TString dirname = ".";
  TString rootname = "HT_1000_500_100.root";
  rootname = dirname + "/" + rootname;
  delete gROOT->GetListOfFiles()->FindObject(rootname);

  std::cout << "Rootname: " << rootname << std::endl;

  TFile *rootfile = new TFile(rootname);

  rootfile->GetListOfKeys()->Print();
  rootfile->ls();

  TH1F *h1  = (TH1F*)rootfile->Get("HT");
  c0->cd();
  h1->Draw("hist");
  h1->SetTitle("HT as constructed manually");
  h1->GetXaxis()->SetTitle("HT");
  h1->GetYaxis()->SetTitle("Entries");
  h1->GetXaxis()->SetRangeUser(0,2000);
  h1->GetYaxis()->SetRangeUser(0,2000);
  // h1->Rebin(); // Only if neccessary

  Double_t entries = h1->GetEntries();
  std::cout << "# entries for histo: " << entries << std::endl;

  leg->AddEntry(h1, "HT for m_{g} = 1 TeV, m_{stop} = 500 GeV, m_{lsp} = 100 GeV", "l");
  leg->AddEntry((TObject*)0,"HT = #sum^{Njets} E_{T}","");
  leg->Draw();
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);

}



