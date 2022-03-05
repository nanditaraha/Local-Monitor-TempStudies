{

  //List of good CSV files:
  //temp_1april.csv
  //temp_11april.csv
  //temp_60h_1.csv - laser hut and optical table
  //temp_hall_60h.csv - All hall
  //temp_run_log18050.csv - most recent
  //temp_9days.csv


  //TString f= "temp_run_log18050.csv";//For temp filename
  //TString f= "temp_60h_1.csv";//For temp filename
  TString f= "temp_Sept_all.csv";//For temp filename
  
  auto c4 = new TCanvas("c", "c", 600,500);
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("Temperature;Time (min);Temperature (^{0}C)");
  TLegend *legend = new TLegend(0.75, 0.75, 0.95, 0.95);
  TGraph *gr2 = new TGraph(f, "%lg %lg %*lg"," ");
  TGraph *gr1 = new TGraph(f, "%lg %*lg %lg"," ");
  gr1->SetMarkerColor(kRed);
  gr1->SetLineColor(kRed);
  gr2->SetMarkerColor(kBlue);
  gr2->SetLineColor(kBlue);

  legend->AddEntry(gr1,"Optical Table Temperature","lp");
  //legend->SetTextColor(kRed);
  legend->AddEntry(gr2,"Laser Hut temperature","lp");
  //legend->SetTextColor(kBlue);
  //mg->GetYaxis()->SetTitle("Temperature");
  //mg->GetXaxis()->SetTitle("Time (min)");
  mg->Add(gr1);
  mg->Add(gr2);
  mg->Draw("alp");
  legend->Draw();
  //c4->BuildLegend();
}
