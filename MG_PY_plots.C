void MG_PY_plots()
{
  gROOT->Reset();

  TCanvas *c0 = new TCanvas("MGvsPY","MGvsPY", 600, 780);

  TString dirname = ".";
  TString rootname1 = "PT_pyth_500_100.root";
  TString rootname2 = "PT_500_100.root";
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

  TH1F *h1 = (TH1F*)rootfile->Get("Top_Stop");
  h1->Draw();
  Double_t norm_factor1 = h1->GetIntegral();
  std::cout << "NORM: " << norm_factor1 << std::endl;
  h1->Scale(1/norm_factor1);
  h1->Draw();


  TH1F *h2 = (TH1F*)rootfile2->Get("Top_Stop");
  h2->Draw("SAME");
  h2->SetLineColor(6);
  Double_t norm_factor2 = h2->GetIntegral();
  std::cout << "NORM2: " << norm_factor2 << std::endl;
  h2->Scale(1/norm_factor1);
  h2->Draw("SAME");



}
