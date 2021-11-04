//proverò a creare il mio primo istogramma!! :)
#include <iostream>
#include <TCanvas.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom3.h>             // per la stampa e lettura a video (ed altre cose MR ibe)
#include <TGraphErrors.h>       // ci serve per istanziare grafici           // ci serve per manipolare gli assi dei grafici         // ci serve per disegnare i grafic                // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>              // ci serve per manipolare l'output a video
#include <tgmath.h>             // lo uso per la funzione esponenziale ed altre funzioni matematiche (tipo le goniometriche)
#include <cmath>                // lo uso per la funzione logaritmo
#include <TMultiGraph.h>
#include <TStyle.h>		// lo uso per i dati sul grafico
using namespace std;
void isto(){

  float m[]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.2, 0.2, 0.2, 0.2, 0.25};

  for(int a=0; a<40; a++){
    cout<<"misura numero "<<a+1<<" = "<<m[a]<<endl;
  }

  TCanvas *cX = new TCanvas("x","x",200,10,600,400);
  cX->cd();

  TH1F *Campione = new TH1F("Campione","Misure dello Zero",6, -0.05, 0.30);
  Campione->SetStats(kFALSE);
  Campione->GetXaxis()->SetTitle("rotazione");
  Campione->GetYaxis()->SetTitle("Conteggi");

  for (int i=0; i<40; i++){
    Campione->Fill(m[i]);
  }
  Campione->Draw();

  TF1 *fitB = new TF1("tutto","gaus",-0.05,0.30);
  Campione->SetLineColor(4);
  Campione->SetLineStyle(9);
  Campione->Fit(fitB,"ME0"); 
  cout << "Chi^2:" << fitB->GetChisquare() << ", number of DoF: " << fitB->GetNDF() << " (Probability: " << fitB->GetProb() << ")." << endl;
  fitB->SetLineColor(6);
  fitB->Draw("same");
 

}
