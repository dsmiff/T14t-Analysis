void plots() 
{
  gROOT->Reset();

  TCanvas *c0 = new TCanvas("plots","plots", 600, 780);
  TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);

  new TFile ("PT_pyth_500_100.root","READ");
  Top_Stop->Draw("hist");
  Top_Stop->GetYaxis()->SetRangeUser(0,4000);
  Top_Stop->GetXaxis()->SetTitle("P_{T}");
  Top_Stop->GetYaxis()->SetTitle("Entries");
  Top_Stop->SetLineColor(2);
  Top_Stop->SetTitle("P_{T} of top from stop for same mass splitting between stop and LSP, but different gluino mass");
  gStyle->SetOptStat(0);
  leg->AddEntry(Top_Stop, "P_{T} from gluino with m_{g} = 1 TeV, m_{stop} = 500 GeV, m_{LSP} = 100 GeV", "l");
  std::cout << "Mlsp 300 entries: " << Top_Stop->GetEntries() << std::endl;

  new TFile ("PT_800_500_100.root", "READ");
  std::cout << "Mlsp 200 entries: " << Top_Stop->GetEntries() << std::endl;
  Top_Stop->Draw("SAME hist");
  Top_Stop->SetLineColor(4);
  leg->AddEntry(Top_Stop, "P_{T} of stop from stop with m_{g} = 800 GeV, m_{stop} = 500 GeV, m_{LSP} = 100 GeV", "l");
  Top_Stop->Draw("SAME hist");

  new TFile ("PT_600_500_100.root", "READ");
  std::cout << "Mlsp 100 entries: " << Top_Stop->GetEntries() << std::endl;
  Top_Stop->Draw("SAME hist");
  Top_Stop->SetLineColor(6);
  leg->AddEntry(Top_Stop, "P_{T} of top from stop with m_{g} = 600 GeV, m_{stop} = 500 GeV, m_{LSP} = 100 GeV", "l");
  leg->Draw();
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  Top_Stop->Draw("SAME hist");
}
