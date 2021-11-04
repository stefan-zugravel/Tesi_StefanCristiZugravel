#include <iostream>           // ci serve per stampare a video il testo
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video 
#include <TImage.h>           // ci serve per le immagini
#include <TPaveStats.h>       // ci serve per la tabella con i valori
using namespace std;

void Linearity()
{
  const int nmisure = 13;
  float V[]  = {0.976, 2.02, 2.94, 3.86, 4.92, 5.88, 6.84, 7.84, 8.80, 9.60, 8.32, 5.52, 3.42  };
  float chn[]  = {195, 392, 589.23, 787.38, 984.77, 1183.51, 1381.25, 1577.30, 1772.58, 1966.13, 1673.91, 1083.58, 688.84  };
  float schn[nmisure];
  float sV[]  = {0.04, 0.1, 0.1, 0.1, 0.2, 0.2, 0.2, 0.2, 0.4, 0.4, 0.4, 0.2, 0.1};
  for(int j=0; j<nmisure;++j){  
    schn[j]=1;
    cout << "\t Vout=(" << V[j] << " +- " << sV[j] << ")V       \tN=" << chn[j] << endl;    
  }
   // --------------------- Grafico i(v) ------------------------------ //

  TCanvas *ciV = new TCanvas("ciV","I(v)",200,10,1920,1080);
  ciV->SetFillColor(0);
  ciV->cd();
  
  TGraphErrors *giV = new TGraphErrors(nmisure,V,chn,sV,schn);
  giV->SetMarkerSize(1);
  giV->SetMarkerStyle(22);
  giV->SetTitle("Linearita'");
  giV->GetXaxis()->SetTitle("V [V]");
  giV->GetYaxis()->SetTitle("chn [#] ");
  giV->Draw("AP");

  cout <<  "\n\n --- Ipotesi  [0]*x + [1] --- \n" <<endl;
  TF1 *funz1 = new TF1("funz1","[0]*x + [1]",0,10);
  //funz1->SetParameter(0,-1);
  //funz1->SetParameter(1,0);
  funz1->SetLineColor(8);
  gStyle->SetOptFit(1);
  gStyle->SetStatY(0.4);
  gStyle->SetStatX(0.85);
  giV->Fit(funz1,"RM+");
  cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;

  TPaveStats *ps = (TPaveStats*)ciV->GetPrimitive("stats");
  //ps->SetName("mystats");
  
  TImage *img = TImage::Create();
  img->FromPad(ciV);
  img->WriteImage("Linearity.png");

}
