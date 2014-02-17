void DelR_TopPT()
{

  gROOT->Reset();
  TCanvas *c1 = new TCanvas("c1","c1", 600, 400);
  TCanvas *c2 = new TCanvas("c2","c2", 600, 400);
  TCanvas *c3 = new TCanvas("c3", "c3", 600, 400);
  TCanvas *c4 = new TCanvas("c4", "c4", 600, 400);
  TLegend *leg = new TLegend(0.5, 1.0, 0.8, 0.5);


  TString dirname = ".";
  TString rootname = "DeltaR_TopPT_500_300.root";
  rootname = dirname + "/" + rootname;

  delete gROOT->GetListOfFiles()->FindObject(rootname);
  
  std::cout << "Rootname: " << rootname << std::endl;

  TFile *rootfile = new TFile(rootname);

  rootfile->GetListOfKeys()->Print();
  rootfile->ls();

  // First root histo extrated is Delta R(W,b) vs Parent top Pt

  TH1F *h1 = (TH1F*)rootfile->Get("DeltaR_W_b1");
  TH1F *h2 = (TH1F*)rootfile->Get("DeltaR_W_b2");
  TH1F *h3 = (TH1F*)rootfile->Get("DeltaR_W_b3");
  TH1F *h4 = (TH1F*)rootfile->Get("DeltaR_W_b4");
  Double_t nentries = h1->GetEntries();
  std::cout << "h1 entries:  " << nentries << std::endl;

  c1->cd();
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);

  h1->SetTitle("");
  h1->GetXaxis()->SetTitle("t_{1} p_{T} [GeV]");
  h1->GetYaxis()->SetRangeUser(0,6);
  h1->GetYaxis()->SetTitle("#Delta R(W,b)");
  h1->Draw("CONTZ");

  leg->AddEntry((TObject*)0, "pp #rightarrow #tilde{g}#tilde{g} #rightarrow #tilde{t} t #tilde{t} t","");
  leg->AddEntry((TObject*)0, "#tilde{t} #rightarrow t #chi_{0}","");
  leg->AddEntry((TObject*)0, "m_{stop} = 500 GeV", "");
  leg->AddEntry((TObject*)0, "m_{lsp} = 300 GeV", "");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->Draw();


  // Second DeltaR(W,b) vs top Pt

  c2->cd();
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);

  h2->SetTitle("");
  h2->GetXaxis()->SetTitle("t_{2} p_{T} [GeV]");
  h2->GetYaxis()->SetRangeUser(0,6);
  h2->GetYaxis()->SetTitle("#Delta R(W,b)");
  h2->Draw("CONTZ");
  leg->Draw();

  // Third DeltaR(W,b) vs top pt

  c3->cd();
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);

  h3->SetTitle("");
  h3->GetXaxis()->SetTitle("t_{3} p_{T} [GeV]");
  h3->GetYaxis()->SetRangeUser(0,6);
  h3->GetYaxis()->SetTitle("#Delta R(W,b)");
  h3->Draw("CONTZ");
  leg->Draw();


  // Fourth DeltaR(W,b) vs top pt

  c4->cd();
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);

  h4->SetTitle("");
  h4->GetXaxis()->SetTitle("t_{4} p_{T} [GeV]");
  h4->GetYaxis()->SetRangeUser(0,6);
  h4->GetYaxis()->SetTitle("#Delta R(W,b)");
  h4->Draw("CONTZ");
  leg->Draw();




}
