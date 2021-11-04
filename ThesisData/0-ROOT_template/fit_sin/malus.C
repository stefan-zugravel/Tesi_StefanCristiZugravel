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
void malus(){
  float pi=3.1415926535;
  int nmisure=37;
  float Angolo[nmisure];
  float sAngolo[nmisure];
  float I[]  = {200, 240, 270, 300, 315, 310, 280, 250, 220, 170, 125, 90, 57, 51, 50, 67, 87, 135, 183, 215, 250, 285, 299, 300, 290, 260, 220, 183, 131, 93, 65, 52, 55, 72, 115, 140, 195};
  float sI[nmisure];
  int a=0;

  for(int j=0;j<nmisure;j++){
    Angolo[j]=a;
    a=a+10;
    sAngolo[j]=2;
    I[j]=I[j]/100;
    sI[j]=0.05;
     
    cout<<"N."<< j << "\t angolo = (" <<Angolo[j] << " +- " << sAngolo[j] << ")°, \t intensità = (" << I[j] << " +- " << sI[j] << ")"<< endl;

  }

  TCanvas *Hg = new TCanvas("Hg","Malus",200,10,600,400);
  Hg->SetFillColor(0);
  Hg->cd();
  TGraphErrors *HG = new TGraphErrors(nmisure,Angolo,I,sAngolo,sI);
  HG->SetMarkerSize(0.6);
  HG->SetMarkerStyle(21);
  HG->SetTitle("Malus");
  HG->GetXaxis()->SetTitle("angolo [gradi]");
  HG->GetYaxis()->SetTitle("Intensita'");
  HG->Draw("AP");

  cout << "--- Vogliamo vedere se i nostri dati funzionano --- " <<endl;
  TF1 *funz1 = new TF1("funz1","[0]*pow(cos(x*(pi/180.0)+[2]),2)+[1]",-10,370);
  HG->Fit(funz1,"RM+");
  cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;

}
