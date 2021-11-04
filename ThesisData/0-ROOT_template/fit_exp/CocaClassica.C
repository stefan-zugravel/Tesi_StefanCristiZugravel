#include <iostream>
#include <TGraphErrors.h>     
#include <TAxis.h>            
#include <TCanvas.h>         
#include <TF1.h>              
#include <iomanip>
#include <TFitResultPtr.h>
#include <TFitResult.h>
#include <cmath>
using namespace std;
void CocaClassica(){
  int nmisure=16;
  float x[]  = {1.565, 2.56, 3.27, 4.02, 4.83, 5.665, 6.815, 7.595, 8.735, 9.625, 10.68, 11.72, 12.8, 13.525, 14.445, 16.685};
  float sx[nmisure];
  float ua[]  = {1592, 1034, 772, 589, 455, 336, 235, 176, 119, 91, 63, 48, 34, 27, 23, 13};
  float sua[nmisure];

  for(int j=0;j<nmisure;j++){
    sx[j]=0.005;
    sua[j]=5;
     
    cout<<"N."<< j << "\t spessore = (" <<x[j] << " +- " << sx[j] << ")cm, \t corrente = (" << ua[j] << " +- " << sua[j] << ")ua"<< endl;

  }

  TCanvas *Hg = new TCanvas("Hg","CocaClassica",200,10,600,400);
  Hg->SetFillColor(0);
  Hg->cd();
  Hg->SetLogy();
  TGraphErrors *HG = new TGraphErrors(nmisure,x,ua,sx,sua);
  HG->SetMarkerSize(0.6);
  HG->SetMarkerStyle(21);
  HG->SetTitle("CocaClassica");
  HG->GetXaxis()->SetTitle("Spessore [cm]");
  HG->GetYaxis()->SetTitle("Corrente [ua]");
  HG->Draw("AP");

  cout << "--- Vogliamo vedere se i nostri dati funzionano --- " <<endl;
  TF1 *funz1 = new TF1("funz1","[0]*pow(e,-[1]*x)",1,17);
  funz1->SetParameter(0,3000);
  HG->Fit(funz1,"RM+");
  cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;

}
