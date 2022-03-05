//Plots the gain function with SiPM, SM and LM corrections - to check long term gain stability.
//LM not yet implemented in this code.
//#include <math.h>       /* remainder */

//Define some global variables here:

int no_cycles = 4;//The number of cycles in a subrun
int prescale_fac = 10;//Used a prescale factor of 10 (every 10th fill has laser pulses)
Double_t T0G=432.e3*5.2e6;
Double_t t24h=24*3600.e6;

//Define BV gain function in ROOT 
//BV sagging in fill gain function
Double_t G(Double_t *x, Double_t *par){
  Double_t t=*x;
  //  return 0.992*(1 - 0.04*exp(-t-29/3.));
  //  return 0.992*(1 - 0.04*exp(-t/3.));
  return 0.992*(1 - 0.04*exp(-t/30.));
}

//Define laser, SM, LM, SiPM functions (C++ func) here 
//Double_t L(Double_t t, Double_t T){
//laser function which drifts by 5% in 60 hrs
Double_t L(Double_t T){
  Double_t xL= 100*(1.+0.05*T/216000e6);
  return  gRandom->Gaus(xL,0.01*xL);
  //    Double_t xL= 100;
    //    return xL;
    //    return  gRandom ->Gaus(xL,0.02*xL);  
}
Double_t Source(Double_t T){
  Double_t c=1;
  //  return gRandom ->Gaus(c,0.01*c)*L(T);
  return c*L(T);
}
//SiPM out of fill
Double_t Sipm0(Double_t T){
  //Double_t c=10;
  Double_t c=(1603-0.018*T/60e6 + 1.775*cos(2*3.1415*(T-363.2)/(23.52*60*60e6)))/1603.;
  //return gRandom ->Gaus(c,0.01*c)*L(T);//
  return c*L(T);
}
//SiPM in fill
Double_t Sipmi(Double_t T, Double_t t){
  //Double_t c=10.;
  Double_t c=(1603-0.018*T/60e6 + 1.775*cos(2*3.1415*(T-363.2)/(23.52*60*60e6)))/1603.;
  
  //Parameter list - p[1];
  Double_t p[1];
  p[0]=0;
  //return gRandom->Gaus(c,0.01*c)*G(&t,p)*L(T);
  return c*G(&t,p)*L(T);
}
//Local monitor effect
Double_t LM0(Double_t T){
  //Double_t c=1;
  Double_t c=(1603-0.018*T/60e6 + 1.775*cos(2*3.1415*(T-363.2)/(23.52*60*60e6)))/1603.;
  //Double_t c=(1-T*8./3600e6 + cos(2*TMath::Pi()*T/t24h))/2.000001;//Trying to normalize
  //  return gRandom ->Gaus(c,0.001*c)*L(T);//
  //return c;
  return c*L(T);
}

int Gain_LM_SM(){  
  //TH2D *h = new TH2D("h","Hist",500,0,500,100, 0.95, 1.02);
  TF1 *f = new TF1("Gain",G,0.,500,0); 
  //new TCanvas;
  f->SetNpx(1000);
  //f->Draw();
  Double_t T0=0;
  Double_t tc=5;//sync pulse time
  Double_t TC=0;
  Double_t T=0;
  Double_t T0C=0;

  //time of the three infill pulses
  Double_t tf1=30;
  Double_t tf2=200;
  Double_t tf3=400;

  //abs time of the three infill pulses
  Double_t TF1=0;
  Double_t TF2=0;
  Double_t TF3=0;
  Double_t tfill=2000;//width of the fill in us 
  
  //Out of fill times in micro-sec(us) - four OOF at, 200, 400, 600 800 us
  Double_t tof1=200;
  Double_t tof2=400;//Should this be 200 or 400???
  Double_t tof3=600;
  Double_t tof4=800;

  //Absoulte times of OOF
  Double_t TOF1=0;
  Double_t TOF2=0;
  Double_t TOF3=0;
  Double_t TOF4=0;

  Double_t S0=999.;
  Double_t Q0=999.;
  //Double_t Q0=.;
  Double_t L0=999.;
  Double_t cs=0.;
  Double_t Si[48];
  Double_t Qi[48];
  Double_t Li[48];//LM infills
  Double_t A[48];
  Double_t A0[48];
  Double_t A02[48];
  Double_t EA[48];
  Double_t EX[48];
  Double_t T0s=0.;
  Double_t T0F=0;
  Double_t csav=0;
  int presc =0;
  int lpresc=0;
  //int ns=100; //100 cicli (1sub=4 cicli) - # of subruns that make a list 'ns'
  //int ns=432; //100 cicli (1sub=4 cicli)
  int ns=432.e4; //100 cicli (1sub=4 cicli)
  //int ns=432.e5; // //100 cicli (1subrun=4 cycles and 1000 cycles make a list - in this case)
  //int ns=432.e3; // //100 cicli (1subrun=5 cycles and 1000 cycles make a list - in this case)
  int icount =0;
  int ic;//ith cycle
  int ics=0;//ith subrun in a cycle
  //loop over 16*3 in fill pulses only for initializing arrays
  for (int iff=0;iff<48;iff++) {
    A0[iff]=0.;
    A02[iff]=0.;
    EA[iff]=0;
    EX[iff]=0;
  }
  //loop over all time points (total subruns): ith subrun # 'is'
  for (int is=0;is<ns;is++){
    //gRandom->SetSeed(0);
    cs=0;//gain - initialize it
    lpresc=0;//Prescale factor for entire subrun
    T0s=5.2e6*is;//Each cycle is 1.3 s and 1 subrun = 4 cycles = 5.2s (abs time of subrun)
    //T0s=6.5e6*is;//Each cycle is 1.3 s and 1 subrun = 5 cycles = 6.5s
    ics=0;
    for (int iff=0;iff<48;iff++)  A[iff]=0.;
    //No. of cycles in a subrun = 4; cycle # with a subrun 'ic'
    for (int ic=0;ic<no_cycles;ic++){ 
      Double_t T0c=T0s+ic*1.3e6; //1.3 s e' il tempo del cycle (abs time of cycle in a subrun)
      presc =0;//Prescale factor for entire cycle
      if ((is*no_cycles+ic)%prescale_fac==0 ) {
	presc =1;
	lpresc=1;
      }
      
      //loop for 16 fill points 
      for (int iff=0;iff<16;iff++) {
      	T0F=T0C+12.e3*iff; //2ms e' il tempo di each fill - (INfill+OOfill = 2+10 ms)
      	TC=T0F+tc; //tempo del sync assoluto
      	//    xl = xL_sync= gRandom ->Gaus(L,1);
	
      	S0=Source(TC);
      	Q0=Sipm0(TC);
	L0=LM0(TC); 
	//cs=cs+Q0/S0;
      	cs=cs+Q0/(S0*L0);//Gains of all cycles (prescale and not) - Sync pulse
		
      	if(presc==1) {	 
      	  tf1=30+2.5*iff;//we start from 30 us in a fill
      	  tf2=tf1+200;
      	  tf3=tf2+200;
      	  TF1=T0F+tf1;
      	  TF2=T0F+tf2;
      	  TF3=T0F+tf3;
      	  Si[iff*3]=Source(TF1);
      	  Si[iff*3+1]=Source(TF2);
      	  Si[iff*3+2]=Source(TF3);
      	  Qi[iff*3]=Sipmi(TF1,tf1);
      	  Qi[iff*3+1]=Sipmi(TF2,tf2);
      	  Qi[iff*3+2]=Sipmi(TF3,tf3);
	  
	  //Same for LMs too
	  
	  Li[iff*3]=LM0(TF1);
      	  Li[iff*3+1]=LM0(TF2);
      	  Li[iff*3+2]=LM0(TF3);
	  
      	  A[iff*3]=Qi[iff*3]/(Si[iff*3]*Li[iff*3]);
      	  A[iff*3+1]=Qi[iff*3+1]/(Si[iff*3+1]*Li[iff*3+1]);
      	  A[iff*3+2]=Qi[iff*3+2]/(Si[iff*3+2]*Li[iff*3+2]);
	  
	  
	  //Case with SM only:
	  /*
	  A[iff*3]=Qi[iff*3]/Si[iff*3];
      	  A[iff*3+1]=Qi[iff*3+1]/Si[iff*3+1];
      	  A[iff*3+2]=Qi[iff*3+2]/Si[iff*3+2];
	  */
	  
      	}//end of prescale cycle for infill 

	//OOF of the first fill - done for all fills and not just prescale
	
	tof1=tfill+200;
	tof2=tfill+400;
	tof3=tfill+600;
	tof4=tfill+800;		
	
	TOF1=T0F+tof1;
	TOF2=T0F+tof2;
	TOF3=T0F+tof3;
	TOF4=T0F+tof4;
	S0=Source(TOF1);
	Q0=Sipm0(TOF1);
	cs=cs+Q0/(S0*LM0(TOF1));
	//cs=cs+Q0/S0;
	//cout<<"is= "<<is<<" ic= "<<ic<<" CS = "<<cs<<" ics= "<<ics++<<endl;
	S0=Source(TOF2);
	Q0=Sipm0(TOF2);
	cs=cs+Q0/(S0*LM0(TOF2));
	//cs=cs+Q0/S0;
	//cout<<"is= "<<is<<" ic= "<<ic<<" CS = "<<cs<<" ics= "<<ics++<<endl;
	S0=Source(TOF3);
	Q0=Sipm0(TOF3);
	cs=cs+Q0/(S0*LM0(TOF3));
	//cs=cs+Q0/S0;
	//	cout<<"is= "<<is<<" ic= "<<ic<<" CS = "<<cs<<" ics= "<<ics++<<endl;
	S0=Source(TOF4);
	Q0=Sipm0(TOF4);
	cs=cs+Q0/(S0*LM0(TOF4));
	//cs=cs+Q0/S0;
	//cout<<"is= "<<is<<" ic= "<<ic<<" CS = "<<cs<<" ics= "<<ics++<<endl;
	//}
      }//end of  fill
    }//end of all 4 cycles of a subrun

    //We have 16 cycles with 1(sync) + 4 OOF pulses = 5 pulses and 4 cycles(no_cycles)
    csav=cs/(16.*5*no_cycles);//Average value of cs (gain) in a subrun
    //cout<<"is= "<<is<<" ic= "<<ic<<" CSAVG = "<<csav<<" prescale = "<<lpresc<<endl;
    
    if(lpresc==1){
      //for(int j=0;j<3;j++){
      for (int iff=0;iff<16;iff++) {
	//cout<<"Histogram: is= "<<is;
	for (int j=0;j<3;j++) {
	  A[3*iff+j]=A[3*iff+j]/csav;	        
	  //cout<<" A["<<iff<<"]= "<<A[3*iff+j];
	  //h->Fill(30+2.5*iff+j*200,A[3*iff+j]);
	}
	//cout<<"\n";
      }
    }


    if(lpresc==1){
      //pre_no++;
      ++icount;
      //cout<<"incount= "<<icount<<endl;
      for (int iff=0;iff<48;iff++){
	//A[iff]=A[iff]/csav;
	A0[iff]=A0[iff]+A[iff];
	A02[iff]=A02[iff]+A[iff]*A[iff];
	
      }
      //h->Fill(30.+2.5*iff+j*200,A0[iff+j]*10/(ns*4));
    }
  }//conclude il loop sugli ns - End of Subruns (loop ns)
  
  
  Double_t x[48];
  for (int iff=0;iff<16;iff++) {
    x[3*iff]=30.+2.5*iff;
    x[3*iff+1]=30.+2.5*iff+200;
    x[3*iff+2]=30.+2.5*iff+400;
    A0[3*iff]=A0[3*iff]/icount;
    A0[3*iff+1]=A0[3*iff+1]/icount;
    A0[3*iff+2]=A0[3*iff+2]/icount;

    //cout<<"A - graph:"<<A0[3*iff]<<","<<A0[3*iff+1]<<","<<A0[3*iff+2]<<"\n";
    A02[3*iff]=A02[3*iff]/icount;
    A02[3*iff+1]=A02[3*iff+1]/icount;
    A02[3*iff+2]=A02[3*iff+2]/icount;
    EA[3*iff]=sqrt(A02[3*iff]-A0[3*iff]*A0[3*iff])/sqrt(icount);
    EA[3*iff+1]=sqrt(A02[3*iff+1]-A0[3*iff+1]*A0[3*iff+1])/sqrt(icount);
    EA[3*iff+2]=sqrt(A02[3*iff+2]-A0[3*iff+2]*A0[3*iff+2])/sqrt(icount);	  
    
  }

  TGraphErrors *gr1 = new TGraphErrors(48, x, A0,EX,EA);
  gr1->Draw("A*");
  //gr1->Fit("f");
  f->Draw("same");
  TFile *f1 = new TFile("gainSim_LM_max_e4.root", "RECREATE");
  gr1->Write("Gain_LM");
  //h->ProfileX()->Draw();
  return 0;
}
