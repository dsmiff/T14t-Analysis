// Collective plot for four leading jets
// D.Smith

void JetPlots()
{

  gROOT->Reset();
  gStyle->SetOptStat(0);
  
  TCanvas *c0 = new TCanvas("Jets","Jets",600, 780);;
  TLegend *leg = new TLegend(0.7,0.8,0.9,0.88);

  TString dirname = ".";
  TString rootname = "LeadingJetPt.root";
  rootname = dirname + "/" + rootname;
  delete gROOT->GetListOfFiles()->FindObject(rootname);
  
  std::cout << "Rootname: " << rootname << std::endl;

  TFile *rootfile = new TFile(rootname);
  rootfile->GetListOfKeys()->Print();
  rootfile->ls();
  
  TH1F *h1 = (TH1F*)rootfile->Get("_JetPt1");
  h1->Draw("hist");
  h1->SetLineColor(9);
  h1->SetTitle("Jet P_{T}s for the first four jets, m_{stop} = 500 GeV & m_{lsp} = 100 GeV");
  h1->GetXaxis()->SetTitle("P_{T}");
  h1->GetYaxis()->SetTitle("Entries");
  h1->GetYaxis()->SetRangeUser(0,4800);

  TH1F *h2 = (TH1F*)rootfile->Get("_JetPt2");
  h2->Draw("SAME hist");
  h2->SetLineColor(2);

  TH1F *h3 = (TH1F*)rootfile->Get("_JetPt3");
  h3->Draw("SAME hist");
  h3->SetLineColor(6);
  
  TH1F *h4 = (TH1F*)rootfile->Get("_JetPt4");
  h4->Draw("SAME hist");
  h4->SetLineColor(3);
  
  leg->AddEntry(h1,"1st Jet", "l");
  leg->AddEntry(h2, "2nd Jet" , "l");
  leg->AddEntry(h3, "3rd Jet", "l");
  leg->AddEntry(h4, "4th Jet", "l");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->Draw();

}
  
