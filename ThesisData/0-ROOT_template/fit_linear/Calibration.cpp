#include <iostream>           // ci serve per stampare a video il testo
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video 
#include <TPaveStats.h>
#include <TImage.h>

using namespace std;

void Calibration()
{
  const int nmisure = 3;
  float chn[]  = {941, 1080, 1143 };
  float E[]  = {4.788, 5.486, 5.805};
  float schn[] ={2.35482, 1.17741, 1.17741};
  float sE[]  = {0.001, 0.001, 0.001};
  float chn2[nmisure];
  for(int j=0; j<nmisure;++j){  
    //chn2[j]=chn[j]-1080;
    cout << "\t chn=(" << chn[j] << " +- " << schn[j] << ")   \t E=(" << E[j]<<" +- "<<0.001<<")MeV" << endl;    
  }

  //cout<<"Ora trasliamo i valori"<<endl<<endl;

  //for(int i=0; i<nmisure;i++){
  //  cout << "\t chn=(" << chn2[i] << " +- " << schn[i] << ")   \t E=" << E[i]<<"MeV" << endl;   
  //}

  //------------------------------------------------------------------------------------------------//

  //TCanvas *ciV = new TCanvas("ciV","I(v)",200,10,600,400);
  //ciV->SetFillColor(0);
  //ciV->cd();
  
  //TGraphErrors *giV = new TGraphErrors(nmisure,chn,E,schn,sE);
  //TGraphErrors *giV = new TGraphErrors(nmisure,E,chn,sE,schn);
  //giV->SetMarkerSize(1);
  //giV->SetMarkerStyle(6);
  //giV->SetTitle("Calibrazione");
  //giV->GetXaxis()->SetTitle("chn [#]");
  //giV->GetYaxis()->SetTitle("E [MeV] ");
  //giV->Draw("AP");

  //cout <<  "\n\n --- Ipotesi  [0]*x + [1] --- \n" <<endl; // prametri liberi quelli tra par quadre
  //TF1 *funz1 = new TF1("funz1","[0]*x + [1]",-10,1200);
  //funz1->SetParameter(0,-1);
  //funz1->SetParameter(1,0);
  //funz1->SetLineColor(8);
  //giV->Fit(funz1,"RM+");
  //cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: ";
  //cout << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;

  //------------------------------------------------------------------------------------------------//
 
  TCanvas *ciV2 = new TCanvas("ciV2","I(v)",200,10,1920,1080);
  ciV2->SetFillColor(0);
  ciV2->cd();
  
  TGraphErrors *giV2 = new TGraphErrors(nmisure,chn,E,schn,sE);
  giV2->SetMarkerSize(1);
  giV2->SetMarkerStyle(22);
  giV2->SetTitle("Calibrazione E=P0*(X-1080)+P1");
  giV2->GetXaxis()->SetTitle("chn [#]");
  giV2->GetYaxis()->SetTitle("E [MeV] ");
  giV2->Draw("AP");


  cout <<  "\n\n --- Ipotesi  [0]*x + [1] --- \n" <<endl;
  TF1 *funz2 = new TF1("funz2","[0]*(x-1080) + [1]",-10,1200);
  //funz1->SetParameter(0,0.005);
  funz2->SetParameter(1,1.17);
  funz2->SetLineColor(2);
  gStyle->SetOptFit(1);
  gStyle->SetStatY(0.4);
  gStyle->SetStatX(0.85);
  giV2->Fit(funz2,"RM+");
  cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: "; 
  cout << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;

  TPaveStats *ps = (TPaveStats*)ciV2->GetPrimitive("stats");

  TImage *img = TImage::Create();
  img->FromPad(ciV2);
  img->WriteImage("Calibration.png");
}
