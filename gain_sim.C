//This simulates the gain function for SiMPs, SM and LM etc. 1st version by Graziano. 

double G(double *x){
  double t=*x;
  return 0.992*(1 - 0.04*exp(-t-29/3.));
  //Gain function of the SiPM used by Graziano and Matthias
}
//double L(double t, double T){
double L(double T){
  double xL= 100*(1.+0.05*T/216000e6);
  return  gRandom ->Gaus(xL,0.01*xL);
}
double Source(double T){
  double c=1;
  return gRandom ->Gaus(c,0.001*c)*L(T);
}
double Sipm0(double T){
  double c=10.;
  //  return gRandom ->Gaus(c,0.001*c)*L(T);//
  return c*L(T);
}

double Sipmi(double T, double t){
  double c=10.;
  return c*G(&t)*L(T);
}


int Gain(){
  TF1 *f = new TF1("Gain","G",0,700); 
  double T0=0;
  double tc=5;
  double T=0;
  double T0C=0;
  double tf1=30;
  double tf2=200;
  double tf3=400;
  double TF1=0;
  double TF2=0;
  double TF3=0;
  double tFILL=700;
  double tof1=200;
  double tof2=200;
  double tof3=600;
  double tof4=800;
  double TOF1=0;
  double TOF2=0;
  double TOF3=0;
  double TOF4=0;
  double S0=999.;
  double Q0=999.;
  double cs=0.;
  double Si[42];
  double Qi[42];
  double T0s=0.;

  //  int ns=25; //100 cicli (1sub=4 cicli)
  int ns=43200; //100 cicli (1sub=4 cicli)
  for (int is=0;is<ns;is++){
    cs=0;
    T0s=5.2e6*is;
    //   for (int ic=0;ic<100;ic++){
    
    for (int ic=0;ic<4;ic++){ 
      double T0c=T0s+ic*1.3e6; //1.3 s e' il tempo del cycle
      int presc =0;
      if ( is*4+ic+1)%10==0 ) presc =1;
      //tree->Draw(“something”, “Entry$ % 5 != 0”); // skip every 5th entry
      //tree->Draw(“something”, “rndm() < 20.0/100.0”); // draw 
      
      for (int if=0;if<16;if++) {
	T0F=T0C+2.e3*if; //2ms e' il tempo di ciascun fill
	TC=T0F+tc; //tempo del sync assoluto
	//    xl = xL_sync= gRandom ->Gaus(L,1);
	
	S0=Source(TC);
	Q0=Sipm0(TC);
	cs=cs+S0/Q0;
	if(presc==1) {
	  tf1=30+2.5*if;
	  tf2=tf1+200;
	  tf3=tf2+200;
	  TF1=TC+tf1;
	  TF2=TC+tf2;
	  TF3=TC+tf3;
	  Si[if]=Source(TF1);
	  Si[if+1]=Source(TF2);
	  Si[if+2]=Source(TF3);
	  Qi[if]=Sipmi(TF1,tf1);
	  Qi[if+1]=Sipmi(TF2,tf2);
	  Qi[if+2]=Sipmi(TF3,tf3);
	  A[if]=Qi[if]/Si[if];
	  A[if+1]=Qi[if]/Si[if];
	  A[if+2]=Qi[if]/Si[if];			 	  
	    
	}
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
	cs=cs+S0/Q0;
	S0=Source(TOF2);
	Q0=Sipm0(TOF2);
	cs=cs+S0/Q0;	
	S0=Source(TOF3);
	Q0=Sipm0(TOF3);
	cs=cs+S0/Q0;
	S0=Source(TOF4);
	Q0=Sipm0(TOF4);
	cs=cs+S0/Q0;	
	
      }
      //16*5*4
      csav=cs/320.;
      //normalizzo i fill per ciascun subrun      
      if(presc==1){
	for (int if=0;if<42;if++) A[if]=A[if]/csav;	        
      }

      //plot
      
 /*   double xL_sync= gRandom ->Gaus(L,1); //1 impulso */
 /* double _sync= gRandom ->Gaus(L,1); //1 impulso */
 
 /* for (int i=0;i<3;i++) { */
 /*    //estraiamo gaussianamente la luce */
 /*    double t1= T0+; */
 /*    double L=100+i*i */
 /*    double x_sync= gRandom ->Gaus(L,1); //1 impulso */
 /*    //estraiamo */
}
