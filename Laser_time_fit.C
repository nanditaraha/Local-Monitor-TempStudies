#include "TFile.h"
#include "TTree.h"
#include <vector>
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include <TChain.h>
#include "TSystem.h"
#include "TBenchmark.h"
#include "TStyle.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include<TProfile.h>
#include<TDirectory.h>
#include<TGraph.h>

void Laser_time_fit()

{
  TFile *file = TFile::Open("Laser_time_60hr.root");

  TGraphErrors *g_amp;// *g_chi2;
  TString channel;
  const int N=24;//no.of calos
  const int X=54;//no of xtals

  gStyle->SetPalette(1);
  double mean1[N*X];
  //double chi2_1[N];
  double m_err1[N*X];
  //double c_err1[N];
  double ch[N*X];
  double ch_e[N*X]={0};
  TH1D *h1[N*X];
  TH3D *h[N];
  TString *hname[N];
  for(int i=0; i<N*X;i++) {
    ch[i]=i+1;
    h1[i] = new TH1D();
    //cout<<i<<" OK1\n";
  }
  
  int in=0;
  for(int i=0;i<24;i++){
    h[i]=new TH3D();
    hname[i]=new TString();
    //cout<<i<<" OK1\n";
  }
  for(int i=0;i<24;i++){
    hname[i]->Form("hFirstTime1_%d",i+1);
    //cout<<hname[i]->Data()<<" OK--2\n";
    h[i] = (TH3D*)file->Get(hname[i]->Data());
    
  }
  for(int i=0;i<24;i++){
    for(int j=0;j<54;j++){
      h[i]->GetZaxis()->SetRange(j,j+1);
      h1[in]=(TH1D*)h[i]->ProjectionY();
      TFitResultPtr g = h1[in]->Fit("gaus","QS");//option S is required
      mean1[in]=g->Parameter(1)*1.25;
      m_err1[in]=g->Parameter(2)*1.25/sqrt(g->Ndf());;
      in++;
      //cout<<"OK--3\n";
    }
    //in++;
  }
  cout<<in<<"\n";
  g_amp = new TGraphErrors(1296,ch,mean1,ch_e,m_err1);
  //g_amp->SetTitle("Ratio of Amplitude (second to first) pulse of all LM");
  //g_amp->SetTitle("Pedestals of all LM");
  //g_amp->SetTitle("Amplitude first pulse of all LM");
  g_amp->GetXaxis()->SetTitle("Crystal #");
  g_amp->GetYaxis()->SetTitle("#Delta Time (ns) ");
  //g_amp->GetYaxis()->SetTitle("Average Pedestal(ADC)");
  //g_amp->GetYaxis()->SetTitle("Time diff (ns)");
  g_amp->SetMarkerColor(kBlue);
  g_amp->SetMarkerStyle(kFullTriangleUp);
  g_amp->Draw("AP");
}


  
 
