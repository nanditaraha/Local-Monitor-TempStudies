//This just fits the data of LM for 60 hr - channel4

void Gain_simp(){

  TString fileName("amp_profile_60hr.root");// 60 hrs
  TFile *file = TFile::Open(fileName,"READ");
  TProfile * hAmp1_4 = (TProfile*)file->Get("hAmp1_4");
  hAmp1_4->Rebin(16);
  TF1 *f = new TF1("f","[0]-x*[1] + [2]*cos(2*3.1415*(x-[3])/([4]*60))",0, 3600);
  TH1D *h = hAmp1_4->ProjectionX();

  //TF1 *f = new TF1("f","cos(x)",0, 100);
  f->SetParameters(1603,7.17/3970.86,1,-3.76,23.6);
  f->SetParNames("A_{0}","m","A","#phi","T");
  //hAmp1_4->Draw();
  h->Fit("f");
  double b = sqrt(f->GetChisquare()/f->GetNDF());

  for(int i=1;i<166;i++) h->SetBinError(i,h->GetBinError(i)*b*0.82);
  h->Fit("f");
  //f->Draw("sames");

}
