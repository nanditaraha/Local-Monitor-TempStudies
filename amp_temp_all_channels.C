/* 
Plots a graph of temp drop with derised channels as input
*/
#include "TFile.h"
#include "TTree.h"
#include <vector>
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TBenchmark.h"
#include "TStyle.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include<TProfile.h>
#include<TDirectory.h>


void amp_ch()
{ 
  
  TString filename = "amp_profile_60hr.root";//"amp_profile_9days.root";
  TFile *file = TFile::Open(filename,"READ");
  TString file_temp = "temp_60h_1.csv";//"temp_9days.csv";
  //"temp_16409_16514.csv";//"temp_9days_1.csv";//"temp_18413.csv";//


  const int N = 30;
  const int N1 = 5;

  double a_mean1[N]={0};
  double a_err1[N]={0};
  double a_mean2[N]={0};
  double a_err2[N]={0};
  double ar_mean[N]={0};
  double ar_err[N]={0};
  TProfile *a[N];//for A1
  TProfile *pa2[N];//for A2
  TH1D *a1[N];//ProjectionX of A1
  TH1D *ar[N];//A2:A1
  double ch[N] = {0};
  double ch_e[N] = {0};
  
  double a_new1[N1]={0};
  double a_new_err1[N1]={0};
  //Amp1 - values
  //double a_old1[N1]={0.004347,0.004634,0.003823,0.004198,0.003826};//{0};
  //double a_old_err1[N1]={0.000052*1.6,0.000061*1.6,0.000044*1.6,0.000038*1.6,0.000039*1.6};//{0};
 
  //Amp2 - valus
  //double a_old1[N1]={0.008518,0.007684,0.007610,0.007198,0.006871};
  //double a_old_err1[N1]={0.000090*1.5,0.000079*1.5,0.000086*1.5,0.000057*1.5,0.000069*1.5};

  //A2:A1 - values
  //double a_old1[N1]={0.003781,0.003125,0.003436,0.002636,0.002785};
  //double a_old_err1[N1]={0.000081*1.6,0.000057*1.6,0.000077*1.6,0.000060*1.6,0.000073*1.6};

  double ch1[N1] = {0};
  double ch_e1[N1] = {0};
  
  //TGraphErrors *all_ch_a1; //Graph of all channels
  //TGraphErrors *all_ch_a2; //Graph of all channels
  //TGraphErrors *all_ch_ar; //Graph of all channels

  int scale_bin = 4; //for 60 hr//1172; // for 9 days// 1810; //for 16409// Must see from histogram

  //Temperature ranges:
  double start_temp = start_temp =29.4, end_temp = 30;//for 60 h//31.6, end_temp = 33; //for 9 days//
  double temp_bin = 0.05;

  
  gStyle->SetPalette(1);
  TString amp1,amp2, channel,name2, name1; 
  
  int ch_comp=0;//Channel to compare old and new;

  for(int new_ch=0;new_ch<N;new_ch++){  
    amp1.Form("hAmp1_%d",new_ch);
    amp2.Form("hAmp2_%d",new_ch);
    ch[new_ch]=new_ch+1;
    //printf("OK---\n");
    a[new_ch] =  (TProfile*)file->Get(amp1.Data()) ;
    pa2[new_ch] =  (TProfile*)file->Get(amp2.Data()) ;
    double init_time = a[new_ch]->GetBinCenter(scale_bin);  
    //a[new_ch]->Rebin(18);
    //pa2[new_ch]->Rebin(18);
    //a[new_ch]->Draw();
    a[new_ch]->Scale(1/a[new_ch]->GetBinContent(scale_bin));
    pa2[new_ch]->Scale(1/pa2[new_ch]->GetBinContent(scale_bin));
    
    a1[new_ch] = (TH1D*)a[new_ch]->ProjectionX();
    ar[new_ch] = (TH1D*)pa2[new_ch]->ProjectionX();
   
    ar[new_ch]->Divide(a1[new_ch]);
   
    //a[new_ch]->Draw();
   
    TGraph *g = new TGraph(file_temp, "%lg %*lg %lg"," ");
    Double_t *time_min=g->GetX();
    //Double_t *room_temp=g->GetY();
    Double_t *table_temp=g->GetY();
    Int_t Nt=g->GetN();  
   //g->Draw("ap");
   //Amp vs temp plots to fit (says area but actually amp)
    
   //Scale for this run: 0.984 to 0.998
    TH2D* area_tempAll = new TH2D("area_tempAll","",(end_temp-start_temp)/temp_bin,start_temp,end_temp, 750, 0.98, 1.01);;// for 60 hr table - ratio
    TH2D* area1_tempAll = new TH2D("area1_tempAll","",(end_temp-start_temp)/temp_bin,start_temp,end_temp,750, 0.98, 1.01);// for 60 hr table - amp1
    TH2D* area2_tempAll = new TH2D("area2_tempAll","",(end_temp-start_temp)/temp_bin,start_temp,end_temp,750, 0.98, 1.01);// for 60 hr table - amp2
   
    for(int j = 0; j<Nt; j++)
      {
       //Double_t x = room_temp[new_ch]; //Note this is laser room or Hall of calo
	Double_t x = table_temp[j];
	
	//Double_t t = time_min[j]*60+init_time;//time converted to mins - if amp plots are in unix times
       
	Double_t t = time_min[j];//use this for 60 hr data set as time is in mins in both plots
	
	Double_t y = ar[new_ch]->GetBinContent(ar[new_ch]->FindBin(t));//area ratio for time t....
	//Double_t y_err = ar->GetBinError(ar->FindBin(t));
	
	Double_t y1 = a[new_ch]->GetBinContent(a[new_ch]->FindBin(t)); //amp1
	//Double_t y1_err = a->GetBinError(a->FindBin(t));
	
	Double_t y2 = pa2[new_ch]->GetBinContent(pa2[new_ch]->FindBin(t));//amp2
	//Double_t y2_err = pa2->GetBinError(pa2->FindBin(t));
	if(y1>0){
	  area_tempAll->Fill(x,y);
	  area1_tempAll->Fill(x,y1);
	  area2_tempAll->Fill(x,y2);
	}
      }
    //area_tempAll->Draw();
    TProfile *area_tempAll_p = area_tempAll->ProfileX();//ratio
    TProfile *area_temp_p1 = area1_tempAll->ProfileX();//a1
    TProfile *area_temp_p2 = area2_tempAll->ProfileX();//a2
    
    TF1 *f = new TF1("f", "pol1");
    //area_tempAll_p ->Fit("f","RQ","",32,33);
    area_tempAll_p ->Fit("f","Q");
    //cout<<"ok2!!\n";
    if(f->GetNDF()>0)//fill and fit only if there is data in the channel
      {
	ar_mean[new_ch] = -f->GetParameter(1);//slope
	//ar_err[new_ch]=f->GetParError(1)*sqrt(f->GetNDF());
	ar_err[new_ch]=f->GetParError(1);
      }
    //area_tempAll_p ->Draw();
    TF1 *f1 = new TF1("f1", "pol1");
    //area_temp_p1 ->Fit("f1","RQ","",32,33);
    area_temp_p1 ->Fit("f1","Q");
    //cout<<"ok2!!\n";
    if(f1->GetNDF()>0)//fill and fit only if there is data in the channel
      {
	a_mean1[new_ch] = -f1->GetParameter(1);//slope
	//a_err1[new_ch]=f1->GetParError(1)*sqrt(f1->GetNDF());
	a_err1[new_ch]=f1->GetParError(1);
      }
    
    TF1 *f2 = new TF1("f2", "pol1");
    //area_temp_p2 ->Fit("f2","QR","",32,33);
    area_temp_p2 ->Fit("f2","Q");
    //cout<<"ok2!!\n";
    if(f2->GetNDF()>0)//fill and fit only if there is data in the channel
      {
	a_mean2[new_ch] = -f2->GetParameter(1);//slope
	//a_err2[new_ch]=f2->GetParError(1)*sqrt(f2->GetNDF());
	a_err2[new_ch]=f2->GetParError(1);
      }
    
    if(new_ch>24) {
      a_new1[ch_comp]=ar_mean[new_ch];
      a_new_err1[ch_comp]=ar_err[new_ch];
      
      ch1[ch_comp]=ch_comp+1;
      ch_comp++;
      
    }
  }
  
  //printf("New ch:%f,%f,%f,%f,%f\n",ar_mean[5],ar_mean[0],ar_mean[6],ar_mean[8],ar_mean[4]);
  //printf("New ch err:%f,%f,%f,%f,%f\n",ar_err[5],ar_err[0],ar_err[6],ar_err[8],ar_err[4]);

  TGraphErrors *tg = new TGraphErrors(N,ch,ar_mean,ch_e,ar_err);
  TGraphErrors *tg1 = new TGraphErrors(N,ch,a_mean2,ch_e,a_err2);
  //TGraphErrors *tg1 = new TGraphErrors(N1,ch1,a_new1,ch_e1,a_new_err1);
  //TGraphErrors *tg = new TGraphErrors(N1,ch1,a_old1,ch_e1,a_old_err1);
  
  tg->GetXaxis()->SetTitle("Channel no.");
  tg->GetYaxis()->SetTitle("Gain drop /^{o} C");
 
  tg1->GetXaxis()->SetTitle("Channel no.");
  tg1->GetYaxis()->SetTitle("Gain drop /^{o} C");

  //TMultiGraph *mg = new TMultiGraph();
  //mg->SetTitle("Drop;Calorimeter no.;Gain drop /^{o}C");
  //mg->Add(tg);
  //mg->Add(tg1);
  //mg->Draw("ap");
  tg->Draw("ap");
}

