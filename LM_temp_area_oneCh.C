
{ 
  //All variables - file name, scaling binning etc. list....
  TString file_name = "amp_profile_9days.root";//"amp_profile_16409_16514_myV1.root";//"amp_profile_18413.root";//
  TString file_temp = "temp_9days_set1.csv";//"temp_16409_16514.csv";//"temp_9days_1.csv";//"temp_18413.csv";//
  TString file_save = "amp_temp_Ch28_9days.root";//"amp_temp_16409_16514_Ch28.root";//"amp_temp_18413.root";//
  
  int scale_bin = 1172; // for 9 days//4; //for 60 hr// 1810; //for 16409// Must see from histogram

  //Temperature ranges:
  double start_temp = 31.6, end_temp = 33; //for 9 days//start_temp =29.4, end_temp = 30;//for 60 h//
  double temp_bin = 0.05;

  TFile *file = TFile::Open(file_name,"READ");
  //double init_time = hAmp1_25->GetXaxis()->GetXmin();//1530.998422e6;//unix time in sec
  //double init_time = 1.53100e+09;//unix time in sec
  double init_time = hAmp1_8->GetBinCenter(scale_bin);//1530.998422e6;//unix time in sec

  gStyle->SetPalette(1);

      
  TH1D *a =  (TH1D*)hAmp1_8->ProjectionX();
  TH1D *pa2 =  (TH1D*)hAmp2_8->ProjectionX();
  TH1D *ar = new TH1D();

  //a->Draw(); 

  
  a->Scale(1/a->GetBinContent(scale_bin));
  pa2->Scale(1/pa2->GetBinContent(scale_bin));

  ar = (TH1D*)pa2->Clone();
  ar->Divide(a);
  
  //ar->Draw();
  
  
  TGraph *g = new TGraph(file_temp, "%lg %*lg %lg"," ");
  Double_t *time_min=g->GetX();
  //Double_t *room_temp=g->GetY();
  Double_t *table_temp=g->GetY();
  Int_t Nt=g->GetN();  
  
  //Scale for this run: 0.984 to 0.998
  TH2D* area_tempAll = new TH2D("area_tempAll","",(end_temp-start_temp)/temp_bin,start_temp,end_temp, 750, 0.98, 1.01);;// for 60 hr table - ratio
  TH2D* area1_tempAll = new TH2D("area1_tempAll","",(end_temp-start_temp)/temp_bin,start_temp,end_temp,750, 0.98, 1.01);;// for 60 hr table - amp1
  TH2D* area2_tempAll = new TH2D("area2_tempAll","",(end_temp-start_temp)/temp_bin,start_temp,end_temp,750, 0.98, 1.01);;// for 60 hr table - amp2
  //if(hAmp1_8->FindBin(1.525775e9)){
  for(int j = 0; j<Nt; j++)
    {
      //Double_t x = room_temp[i]; //Note this is laser room or Hall of calo
      Double_t x = table_temp[j];
      
      Double_t t = time_min[j]*60+init_time;//time converted to sec - if amp plots are in unix times
      
      //Double_t t = time_min[j];//if amp plots in mins
      
      Double_t y = ar->GetBinContent(ar->FindBin(t));//area ratio for time t....
      //Double_t y_err = ar->GetBinError(ar->FindBin(t));
      
      Double_t y1 = a->GetBinContent(a->FindBin(t)); //amp1
      //Double_t y1_err = a->GetBinError(a->FindBin(t));
      
      Double_t y2 = pa2->GetBinContent(pa2->FindBin(t));//amp2
      //Double_t y2_err = pa2->GetBinError(pa2->FindBin(t));
      if(y1>0){
	area_tempAll->Fill(x,y);
	area1_tempAll->Fill(x,y1);
	area2_tempAll->Fill(x,y2);
      }
    }
  //}
  //area_tempAll->Draw();
  TProfile *area_tempAll_p = area_tempAll->ProfileX();//ratio
  TProfile *area_temp_p1 = area1_tempAll->ProfileX();//a1
  TProfile *area_temp_p2 = area2_tempAll->ProfileX();//a2
  
  area_tempAll_p->GetXaxis()->SetTitle("Temperature (^{o}C)");
  area_temp_p1->GetXaxis()->SetTitle("Temperature (^{o}C)");
  area_temp_p2->GetXaxis()->SetTitle("Temperature (^{o}C)");
  /*

  TFile *f = new TFile(file_save,"RECREATE");
  area_tempAll_p->Write("Ch28_ratio");
  area_temp_p1->Write("Ch28_a1");
  area_temp_p2->Write("Ch28_a2");
  */
  /*Very very imp. note and concept - 
    If error bars are too less and reduced chi2 very large. Find probabilty p of the fit function use f->GetProb().
    If p<5% change error bars e to e*sqrt(reduced chi2).
    Also note - can never change error bars on a TProfile. Change to histogram first. h = Ch8_ratio->ProjectionX();
    
    //Small code snippet here to do this:
    
    h = Ch8_ratio->ProjectionX();
    TF1 *f1 = new TF1("f1","pol1");
    h->Fit("f1");
    if(f1->GetProb()<0.05) 
    {
    b=sqrt(f1->GetChisquare()/f1->GetNDF())
    for(int i = 1; i<28;i++) h->SetBinError(i,h->GetBinError(i)*b)
    }
   */
}
