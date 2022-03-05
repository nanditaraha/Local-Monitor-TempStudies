{

  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);

  TFile *fl = TFile::Open("gm2Crystal_1599.root");
  crystalHitTreeIF->cd();
  
  Int_t n1 = crystalHits->Draw("trace:Iteration$","Entry$==4441 &&channelNum==0","");
  Double_t *v1 = monitors->GetVal(1);
  Double_t *v2 = monitors->GetVal(0);
  TGraph *g = new TGraph(n1, v1, v2);
  TGraph *g1 = new TGraph(n1, v1, v2);
  TF1 *f1=new TF1("f1","pol0");
  TF1 *f=new TF1("f","pol0");
  f->SetRange(0,40);
  f1->SetRange(400,440);
  f1->SetLineColor(kCyan);
  g->Fit("f","RQ");
  g1->Fit("f1","RQ");
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(g);  
  mg->Add(g1);
  mg->Draw();

}
