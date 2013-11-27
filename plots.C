void plots() 
{
  gROOT->Reset();

  TCanvas *c0 = new TCanvas("plots","plots", 600, 780);
  TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);

  new TFile ("PTgluino_500_100.root","READ");
  Top_Gluino->Draw("hist");
  Top_Gluino->GetYaxis()->SetRangeUser(0,4000);
  Top_Gluino->GetXaxis()->SetTitle("P_{T}");
  Top_Gluino->GetYaxis()->SetTitle("Entries");
  Top_Gluino->SetLineColor(2);
  Top_Gluino->SetTitle("P_{T} of top from gluino for same mass splitting between stop and LSP, but different gluino mass");
  Top_Gluino->GetYaxis()->SetRangeUser(0,7000);
  gStyle->SetOptStat(0);
  leg->AddEntry(Top_Gluino, "P_{T} from gluino with m_{g} = 1 TeV, m_{stop} = 500 GeV, m_{LSP} = 100 GeV", "l");
  std::cout << "Mlsp 300 entries: " << Top_Gluino->GetEntries() << std::endl;

  new TFile ("PTgluino_800_500_100.root", "READ");
  std::cout << "Mlsp 200 entries: " << Top_Gluino->GetEntries() << std::endl;
  Top_Gluino->Draw("SAME hist");
  Top_Gluino->SetLineColor(4);
  leg->AddEntry(Top_Gluino, "P_{T} of stop from gluino with m_{g} = 800 GeV, m_{stop} = 500 GeV, m_{LSP} = 100 GeV", "l");
  Top_Gluino->Draw("SAME hist");

  new TFile ("PTgluino_600_500_100.root", "READ");
  std::cout << "Mlsp 100 entries: " << Top_Gluino->GetEntries() << std::endl;
  Top_Gluino->Draw("SAME hist");
  Top_Gluino->SetLineColor(6);
  leg->AddEntry(Top_Gluino, "P_{T} of top from gluino with m_{g} = 600 GeV, m_{stop} = 500 GeV, m_{LSP} = 100 GeV", "l");
  leg->Draw();
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  Top_Gluino->Draw("SAME hist");
}
