#include <iostream>       // ci serve per stampare a video il testo
#include <TGraphErrors.h> // ci serve per istanziare grafici
#include <TAxis.h>        // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>      // ci serve per disegnare i grafici
#include <TF1.h>          // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>        // ci serve per manipolare l'output a video
#include <TImage.h>       // ci serve per le immagini
#include <TPaveStats.h>   // ci serve per la tabella con i valori
#include <TFitResult.h>
#include <TMatrixD.h>
using namespace std;
//asse x energia asse y range
void Mylar()
{
  const int nmisure = 4;
  float E[] = {4, 4.5, 5, 5.5};
  float R[] = {2.9, 3.44, 4.04, 4.67};
  float sE[] = {0.01, 0.01, 0.01, 0.01};
  float sR[] = {0.02, 0.02, 0.02, 0.02};
  for (int j = 0; j < nmisure; ++j)
  {
    //sR[j]=1;
    cout << "\t Vout=(" << E[j] << " +- " << sE[j] << ")V       \tN=" << R[j] << endl;
  }
  // --------------------- Grafico i(v) ------------------------------ //

  TCanvas *ciV = new TCanvas("ciV", "I(v)", 200, 10, 1920, 1080);
  ciV->SetFillColor(0);
  ciV->cd();

  TGraphErrors *giV = new TGraphErrors(nmisure, E, R, sE, sR);
  giV->SetMarkerSize(1);
  giV->SetMarkerStyle(22);
  giV->SetTitle("Range");
  giV->GetXaxis()->SetTitle("E [MeV]");
  giV->GetYaxis()->SetTitle("Range [mg/cm^2] ");
  giV->Draw("AP");

  cout << "\n\n --- Ipotesi  [0]*x + [1] --- \n"
       << endl;
  TF1 *funz1 = new TF1("funz1", "[0]*(x-5)^2 + [1]*(x-5) + [2] ", 0, 10);
  //funz1->SetParameter(0,-1);
  //funz1->SetParameter(1,0);
  funz1->SetLineColor(2);
  gStyle->SetOptFit(1);
  gStyle->SetStatY(0.4);
  gStyle->SetStatX(0.85);
  giV->Fit(funz1, "R+");
  cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;

  TPaveStats *ps = (TPaveStats *)ciV->GetPrimitive("stats");
  //ps->SetName("mystats");

  TFitResultPtr r = giV->Fit("funz1", "S");
  //TMatrixD cov = r->GetCorrelationMatrix();
  TMatrixD cor = r->GetCovarianceMatrix();
  //cov.Print();
  cor.Print();



  //TF1 *funz2 = new TF1("funz2", "[0]*x^2+[1]*x",0,10);
  //funz2->SetLineColor(2);
  //giV->Fit(funz2,"R+");
  //cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;

  TImage *img = TImage::Create();
  img->FromPad(ciV);
  img->WriteImage("Rates.png");
}
