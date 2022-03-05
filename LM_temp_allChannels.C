{
  //TFile *_file0 = TFile::Open("july_1_4.root");
  TFile *_file0 = TFile::Open("Laser_first_timeStab_60hr.root");
  //TFile *_file0 = TFile::Open("gm2rootTrees_LM_oof_all.root");//April 11
  //TFile *_file0 = TFile::Open("gm2rootTrees_ana_LM_1Apr.root");//april 1

  TGraphErrors *g_amp, *g_chi2;
  TString channel;
  
  localMonitorsTreeOoF->cd();
  //New TDirectory structure in new files

  gStyle->SetPalette(1);
  double mean1[29];
  double chi2_1[29];
  double m_err1[29];
  double c_err1[29];
  double ch[29];
  double ch_e[29]={0};

  for(int i=0;i<29;i++){
    channel.Form("channelNum==%d && amplitude_second_pulse>500",i);
    //monitors->Draw("pedestal>>h1(1000,1700,1800)",channel.Data(),"goff");//to not draw 
    monitors->Draw("area_second_pulse/area>>h1(300,-1,2)",channel.Data(),"goff");//to not draw 
    //monitors->Draw("amplitude>>h1",channel.Data(),"goff");//to not draw 
    //monitors->Draw("(time_second_pulse-time)*1.25>>h1",channel.Data(),"goff");//to not draw 
    TH1F *h1 = (TH1F*)gDirectory->Get("h1");

    //Above step is very important to retrieve the histogram or  the code would break in the next element of the loop;
    
    h1->Fit("gaus","RQ","", h1->GetMean()-3*h1->GetRMS(), h1->GetMean()+3*h1->GetRMS());
    //cout<<"ok2!!\n";
    if(gaus->GetNDF()>0)//fill and fit only if there is data in the channel
      {
	mean1[i] = gaus->GetParameter(1);//mean
	chi2_1[i] = gaus->GetParameter(2);//sigma
	//m_err1[i]=gaus->GetParameter(2)/sqrt(gaus->GetNDF());//sigma/sqrt(N)
	m_err1[i]=gaus->GetParError(1);
	c_err1[i]=gaus->GetParError(2);
      }
    //h1->Draw();
    //c_err1[i]=sqrt(gaus->GetParError(1)*gaus->GetParError(1) + gaus->GetParError(2)*gaus->GetParError(2))/sqrt(gaus->GetNDF());
    ch[i]=i+1;
    //cout<<i+1<<":Mean "<<mean1[i]<<" err "<<m_err1[i]<<"\n";
    /*
    if(i==10) {
    h1->Draw();
    break;
    }
    */
    
    }
  //Amplitudes
  
  g_amp = new TGraphErrors(29,ch,mean1,ch_e,m_err1);
  //g_amp->SetTitle("Ratio of Amplitude (second to first) pulse of all LM");
  //g_amp->SetTitle("Pedestals of all LM");
  //g_amp->SetTitle("Amplitude first pulse of all LM");
  g_amp->GetXaxis()->SetTitle("Channel #");
  g_amp->GetYaxis()->SetTitle("Average Area ratio (A2:A1)");
  //g_amp->GetYaxis()->SetTitle("Average Pedestal(ADC)");
  //g_amp->GetYaxis()->SetTitle("Time diff (ns)");
  g_amp->SetMarkerColor(kBlue);
  g_amp->SetMarkerStyle(kFullTriangleUp);
  g_amp->Draw("AP");
  //chi2
  
  //monitors->Draw("time_second_pulse-time>>h1","","colz");//to not draw 
  //monitors->Draw("amplitude:area>>h","amplitude>500&&channelNum==0","colz");
  //TProfile *p = h->ProfileX();
  //p->Draw();

  //Chi2 distribution is useful
  g_chi2 = new TGraphErrors(29,ch,chi2_1,ch_e,c_err1);
  g_chi2->SetTitle("Width #sigma/Mean");
  g_chi2->GetXaxis()->SetTitle("Channel #");
  g_chi2->GetYaxis()->SetTitle("Width #sigma/Mean");
  g_chi2->SetMarkerColor(kBlue);
  g_chi2->SetMarkerStyle(kFullTriangleUp);
  //g_chi2->Draw("AP");
  
  //h2[0]->Draw("sames");
}
