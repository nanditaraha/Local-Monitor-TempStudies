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

void timeStudies()

{ 
  TString fileName("gm2rootTrees_ana__traces_15944.00400.root");
  gStyle->SetPalette(1);

  TH2D *hFirstTime = new TH2D("hFirstTime", " ",16,33313,5e4,300,1980,2010);//BIn: x-axis 1 us and y-axis 0.1 ns
  TH2D *hSecondTime = new TH2D("hSecondTime", " ",40,192e3,208e3,50,1998,2003);//BIn: x-axis 1 us and y-axis 0.1 ns
  //TH2D *hDiffTime = new TH2D("hDiffTime", " ",100,33313,5e4,100,0,180e3);
  TH2D *hDiffTime = new TH2D("hDiffTime", " ",50,33313,5e4,15,160000.5,160001.5);//BIn: x-axis 0.5 us and y-axis 20 ns

  TFile *file = TFile::Open(fileName,"READ");
  if (!file) { return; }

  TTree *tree  = (TTree*)file->Get("crystalHitTreeIF/crystalHits");//For file gm2rootTrees_LM_oof_all.root
  int nentries = tree->GetEntries();
  cout<<"ok tree...\n";
  cout << nentries << " entries" << endl;
  
  vector<double> Diff;
  vector<double> sync;
  vector<double> first;
  vector<double> second;
  vector <double> Time_first;
  vector <double> Time_second;
  vector <int> evt;
 
  Double_t time;
  Bool_t laserHit;
  UInt_t eventNum;
  UInt_t xtalNum;
  UInt_t subRunNum;
  UInt_t runStartUnixTimeSeconds;
  UInt_t caloNum;

  int sync_inx=0;
  int first_inx=0;
  //int evt=0;
  
  tree->SetBranchAddress("time",&time);
  tree->SetBranchAddress("laserHit",&laserHit);
  tree->SetBranchAddress("eventNum",&eventNum);
  tree->SetBranchAddress("xtalNum",&xtalNum);
  tree->SetBranchAddress("caloNum",&caloNum);
  tree->SetBranchAddress("subRunNum",&subRunNum);
  tree->SetBranchAddress("runStartUnixTimeSeconds",&runStartUnixTimeSeconds); 

  for (int i = 0; i < nentries; i++) {
  //for (int i = 0; i < 100; i++) {
    if(!tree->GetEntry(i)) continue;
    if(xtalNum==7 && laserHit==1){
      //cout<<"Event = "<<eventNum<<"  ##########################\n";
      //evt=evt+1;
      evt.push_back(eventNum);
      if(time<10000){
	//evt=eventNum;
	sync.push_back(time);
      }
      if(time>10000 && time<60000)
	first.push_back(time);

      if(time>70000 && time<300000)
	second.push_back(time);
      
      //cout<<evt<<endl;// to find total laser fills
    }
  }
  cout << evt.size() << " Event entries ################**************" << endl;
  cout << first.size() << " First pulse ################**************" << endl;
  cout << second.size() << " Second entries ################**************" << endl;
  cout << sync.size() << " Sync entries ################**************" << endl;
  for(int i=0;i<first.size();i++) {
    
    Time_second.push_back(second[i]-sync[i]);
    Diff.push_back(second[i]-first[i]);
    Time_first.push_back(first[i]-sync[i]); 
  }

  for(int i=0;i<first.size();i++) {
    //diff b/w two pulses of a consecutive fill will come after 24 pulses because of 24 calos. 
    //Seem to have 24 pulses in a fill - I checked with print statements...
    //So I add 24 to get the corresponding event of the next fill.
    if((i+24)<first.size()){
      //cout<<"Evt:"<<i<<" Time 1 is:"<<Time_first[i]<<"\n";
      //cout<<"Time 2 is:"<<Time_first[i+24]<<"\n";
      //cout<<"Diff is:"<<abs(Time_first[i+24]-Time_first[i])<<"\n";
      hFirstTime->Fill(first[i],abs(Time_first[i+24]-Time_first[i]));
      hSecondTime->Fill(second[i],abs(Time_second[i+24]-Time_second[i]));
    }
    hDiffTime->Fill(first[i],Diff[i]);    
    //cout<<"Time "<<i+1<<" is:"<<Time_first[i]<<"\n";
    
  }

  //TGraph *hFirstSyncTime = new TGraph(first.size(),&first[0],&Time_first[0]);
  //hFirstSyncTime->Draw("AP");   
  //TProfile *px = hDiffTime->ProfileX();
  //px->Draw();
  //hFirstTime->Draw("colz");   
  //hSecondTime->Draw("colz");   
  hDiffTime->Draw("colz");   
}

