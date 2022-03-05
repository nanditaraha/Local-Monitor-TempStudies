/*This code plots the area ratio, time difference b/w the two LM pulses for a particular channel in a time ordered manner. 
It also plots the for pedestals and times.
Reads initial time from the unix time stamps histogram... 
Important cuts for bad data
ask that amplitude and amplitude_second_pulse are both > 100
and that time > 100 and time_second_pulse < 700
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

void LM_temp()

{ 
  //TString fileName("gm2rootTrees_ana_13966.root");//New run with timestamp for temperature studies ..
  //TString fileName("gm2rootTrees_LM_oof_all.root");//11th april run with timestamp for temperature studies ..
  TString fileName("gm2rootTrees_ana_LM_1Apr_00_12.root");//Latest run 1st april - we use this...

  gStyle->SetPalette(1);

  //This is the histogram bin and sizes for gm2rootTrees_LM_1Apr.root and all 24 hrs run sets
  TH2D *hPedestal = new TH2D("hPedestal", " ",100*24,0,50*24,200, 1780, 1800);//out fill
  TH2D *hArea = new TH2D("hArea", " ",100*24,0,50*24,200, 18000, 38000);//out fill  
  TH2D *hArea2 = new TH2D("hArea2", " ",100*24,0,50*24,200, 0, 38000);//out fill  
  TH2D *hArea_ratio = new TH2D("hArea_ratio", " ",100*24,0,50*24, 200,0.42, 1.2);//in fill  
  TH2D *hTime_diff = new TH2D("hTime_diff", "",100*24,0,50*24, 10,230, 240);//in of fill 
  //TH2D *hIsland = new TH2D("hIsland", " ",202,0,101,50, 0, 50);//in fill
  TFile *file = TFile::Open(fileName,"READ");
  if (!file) { return; }
  
  TTree *tree;
  //file->GetObject("localMonitorsTreeIF/monitors",tree);//For file gm2rootTrees_ana_13966.root
  file->GetObject("monitors",tree);//For file gm2rootTrees_LM_oof_all.root
  
  Int_t nentries = (Int_t)tree->GetEntries();
  Double_t pedestal;
  UInt_t channelNum;
  Double_t area;
  Double_t amplitude;
  Double_t amplitude_second_pulse;
  Double_t area_second_pulse;
  Double_t time_second_pulse;
  Double_t time;
  int eventNum;
  int runNum;
  int islandNum;
  int runStartUnixTimeSeconds;
  int subRunNum;
  
  //int time_init=1521.678e6;//read it from the histogram - not a good way. For file gm2rootTrees_ana_13966.root
  //int time_init=1523.46575e6;//read it from the histogram - not a good way. For file gm2rootTrees_LM_oof_all.root - 11th April
  int time_init=1522.5779e6;//read it from the histogram - not a good way. For file gm2rootTrees_LM_oof_all.root - 1st April  
  
  TBranch *bEvt = tree->GetBranch("runStartUnixTimeSeconds");
  bEvt->SetAddress(&runStartUnixTimeSeconds); 
  
  TBranch *bSubRun = tree->GetBranch("subRunNum");
  bSubRun->SetAddress(&subRunNum); 
  
  TBranch *bRun = tree->GetBranch("runNum");
  bRun->SetAddress(&runNum); 
  TBranch *bPed = tree->GetBranch("pedestal");
  bPed->SetAddress(&pedestal);  
  TBranch *bChannel = tree->GetBranch("channelNum");
  bChannel->SetAddress(&channelNum);
  TBranch *bAmp = tree->GetBranch("amplitude");
  bAmp->SetAddress(&amplitude);
  TBranch *bAmp2 = tree->GetBranch("amplitude_second_pulse");
  bAmp2->SetAddress(&amplitude_second_pulse);

  TBranch *bArea = tree->GetBranch("area");
  bArea->SetAddress(&area);
  TBranch *bArea2 = tree->GetBranch("area_second_pulse");
  bArea2->SetAddress(&area_second_pulse);
  TBranch *bTime2 = tree->GetBranch("time_second_pulse");
  bTime2->SetAddress(&time_second_pulse);
  
  TBranch *bTime = tree->GetBranch("time");
  bTime->SetAddress(&time);

  for (Int_t i = 0; i < nentries; i++) {
    //for (Int_t i = 300000; i < nentries; i++) {
    tree->GetEntry(i);
    if(channelNum==0 && area_second_pulse/amplitude_second_pulse<25) {
    //if(channelNum==1 && amplitude_second_pulse>500) {
      hPedestal->Fill((runStartUnixTimeSeconds - time_init)/60.,pedestal);//to convert the time from sec to min - this run is 50 min long
      hArea->Fill((runStartUnixTimeSeconds - time_init)/60.,area);
      hArea2->Fill((runStartUnixTimeSeconds - time_init)/60.,area_second_pulse);
      //hIsland->Fill(,islandNum);
      hArea_ratio->Fill((runStartUnixTimeSeconds - time_init)/60.,area_second_pulse/area);
      //if(i<100)
      //cout<<"time"<<(time_second_pulse)*1.25<<"\n";
      hTime_diff->Fill((runStartUnixTimeSeconds - time_init)/60.,(time_second_pulse-time)*1.25);
      
      }
    //if(i<100) cout<<i+1<<": Run Number:"<<runNum<<" Event:"<<Event[i]<<" Event #:"<<eventNum<<"\n";
  }
  
  //for(int i=0;i<10;i++) cout<<i+1<<": Run Number:"<<runNum<<" Event:"<<Event[i]<<"Event size:"<<Event.size()<<"\n";
  //hEvt->Draw("colz");
  
  hPedestal->GetXaxis()->SetTitle("Time (min)");
  hPedestal->GetYaxis()->SetTitle("Pedestal (ADC)");
  hPedestal->SetStats(0);
  
  hArea->GetXaxis()->SetTitle("Time (min)");
  hArea->GetYaxis()->SetTitle("Area (ADC)");
  hArea->SetStats(0);
  
  hArea_ratio->GetXaxis()->SetTitle("Time (min)");
  hArea_ratio->GetYaxis()->SetTitle("Ratio of Areas");
  hArea_ratio->SetStats(0);
  
  hTime_diff->GetXaxis()->SetTitle("Time (min)");
  hTime_diff->GetYaxis()->SetTitle("Time diff (t_{2}-t_{1}) ns");
  hTime_diff->SetStats(0);
  
  TProfile *p = hPedestal->ProfileX();
  p->GetXaxis()->SetTitle("Time (min)");
  p->GetYaxis()->SetTitle("Pedestal (ADC)");
  p->GetYaxis()->SetRangeUser(1786,1793);//for ped
  //p->SetStats(0);
  
  TProfile *a = hArea->ProfileX();
  a->GetXaxis()->SetTitle("Time (min)");
  a->GetYaxis()->SetTitle("Area (ADC)");
  a->GetYaxis()->SetRangeUser(2260,2350);//for ped
  a->SetStats(0);
  
  TProfile *ar = hArea_ratio->ProfileX();
  ar->GetXaxis()->SetTitle("Time (min)");
  ar->GetYaxis()->SetTitle("Ratio of Area");
  ar->GetYaxis()->SetRangeUser(0.95,1.05);//for ped
  //ar->SetStats(0);
  //hAmp_ratio->Scale(1/ar->GetMean(2));   
  
  TProfile *ar_y = hArea_ratio->ProfileY();
  //ar_y->Draw();
  
  TProfile *t = hTime_diff->ProfileX();
  t->GetXaxis()->SetTitle("Time (hr)");
  t->GetYaxis()->SetTitle("Time diff (t_{2}-t_{1}) ns");
  t->GetYaxis()->SetRangeUser(235.8,236.4);//for ped
  //t->SetStats(0);
  
  TProfile *pa2 = hArea2->ProfileX();
  //Scaling ar
  //ar->Scale(1/ar->GetMean(2));
  //ar->Draw();
  //t->Draw();
  
  //for 11th april
  /*
  TGraphErrors* g= new TGraphErrors("room_temp_11April.csv", "%lg %lg", ",");
  TGraph* g1= new TGraph("table_temp_11april.csv", "%lg %lg", ",");
  */
  //for 1st April
  TGraphErrors* g= new TGraphErrors("room_temp_1april_min.csv", "%lg %lg", " ");
  TGraph* g1= new TGraph("table_temp_1april_min.csv", "%lg %lg", " ");
  //g->Draw(""); 
  //g1->SetLineColor(kRed);
  //g1->Draw("same");
  
  Double_t *time_min=g1->GetX();
  Double_t *room_temp=g->GetY();
  Double_t *table_temp=g1->GetY();
  Int_t N=g->GetN();  
  
  //TGraphErrors* area_temp = new TGraphErrors(N);
  //TH3D* area_temp = new TH3D("area_temp","",100*24,0,50*24, 200,0.5, 1.5,N,28,28.6);// for 11th april
  //TH3D* area_temp = new TH3D("area_temp","",100*24,0,50*24, 200,0.5, 1.5,N,27.5,27.9);// for 1st april room
  /*
  TH3D* area_temp = new TH3D("area_temp","",100*24,0,50*24, 200,0.5, 1.5,N,29.6,30);// for 1st april table
  TH3D* area1_temp = new TH3D("area1_temp","",100*24,0,50*24, 200, 18000, 38000,N,29.6,30);// for 1st april
  TH3D* area2_temp = new TH3D("area2_temp","",100*24,0,50*24, 200, 0, 38000,N, 29.6,30);// for 1st april
  */
  TH3D* area_temp = new TH3D("area_temp","",300,0,50*24, 200,0.5, 1.5,N,27.5,27.9);// for 1st april room - ratio
  TH3D* area1_temp = new TH3D("area1_temp","",300,0,50*24, 200, 18000, 38000,N,27.5,27.9);// for 1st april-area1
  TH3D* area2_temp = new TH3D("area2_temp","",300,0,50*24, 200, 0, 38000,N, 27.5,27.9);// for 1st april-area2
  //cout<<
  
  for(int i = 0; i<N; i++)
    {
      Double_t x = room_temp[i];
      //Double_t x = table_temp[i];
      Double_t t = time_min[i];
      
      Double_t y = ar->GetBinContent(ar->FindBin(t));
      Double_t y_err = ar->GetBinError(ar->FindBin(t));
      
      Double_t y1 = a->GetBinContent(a->FindBin(t));
      Double_t y1_err = a->GetBinError(a->FindBin(t));
      
      Double_t y2 = pa2->GetBinContent(pa2->FindBin(t));
      Double_t y2_err = pa2->GetBinError(pa2->FindBin(t));

      //area_temp->SetPoint(i,x,y); //Good for graph
      //area_temp->SetPointError(i,0,y_err); 
     
      if(y>0)
	area_temp->Fill(t, y, x);

      if(y1>0)
	area1_temp->Fill(t, y1, x);

      if(y2>0)
	area2_temp->Fill(t, y2, x);
      //cout<<"Time:"<<t<<" Temp:"<<x<<" ar:"<<y<<"\n";
    }
    
  //hist->Draw();
  TH2D *area_t = (TH2D*)area_temp->Project3D("yz");
  TProfile *area_temp_p = area_t->ProfileX();
  //area_temp_p->Draw();

  TH2D *area1_t = (TH2D*)area1_temp->Project3D("yz");
  TProfile *area1_temp_p = area1_t->ProfileX();
  area1_temp_p->Draw();

  TH2D *area2_t = (TH2D*)area2_temp->Project3D("yz");
  TProfile *area2_temp_p = area2_t->ProfileX();
  //area2_temp_p->Draw();

  TFile *f1 = new TFile("test.root","RECREATE");
  //TFile *f1 = new TFile("OoF_roomTemp_1april_ch0_cut.root","RECREATE");
  ar->Write("prof_ar");
  t->Write("prof_t");
  p->Write("prof_p");
  hArea->Write("area");
  hArea_ratio->Write("hist_area_ratio");
  hPedestal->Write("hist_ped");
  hTime_diff->Write("hist_time"); 
  area_temp_p->Write("temperature_area");
  area1_temp_p->Write("temperature_area1");
  area2_temp_p->Write("temperature_area2");
}
