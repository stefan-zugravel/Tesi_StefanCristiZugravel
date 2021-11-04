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
#include <fstream>
#include <TStyle.h>
#include <TF1.h>
#include <TMath.h>
#include <cmath>

using namespace std;
//Autore, onnipotente gruppo A-7
void Lambert(){
    //Parametri iniziali, serviranno per la parte iniziale del programma :) 
    int nColonne = 4;
    int nMisure = 28;
    int MisureTot = nMisure*4;
    int a = 0;
    int b = 0; 
    int c = 0; 
    int d = 0;  
    //inizializzo i nostri vettori con le misure.
    double D[nMisure];
    double eD[nMisure];
    double conteggi[nMisure];
    double econteggi[nMisure];

    ifstream inFile;
    ofstream outFile; 
    //Apro il mio file.txt
    inFile.open("Dati_Lambert_Beer.txt");
    if(!inFile){                                 
        cout << "---ATTENZIONE!!! Non trovo nessun file!!!---"<< endl;
    }
    //Metto i miei dati nei rispettivi vettori
    for(int j = 0; j < nMisure; j++)
    {
        inFile >> D[a];
        a++;
    }
    for(int j = nMisure; j < 2*nMisure; j++)
    {
        inFile >> eD[b];
        b++;
    }
    for(int j = 2*nMisure; j < 3*nMisure; j++)
    {
        inFile >> conteggi[c];
        c++;
    }
    for(int j = 3*nMisure; j < 4*nMisure; j++)
    {
        inFile >> econteggi[d];
        d++;
    }
    //Ciclo for per il debug, non è per forza necessario, ma è utile nel caso di qualche errore.
    for(int k = 0; k < nMisure; k++)
    {
        cout<<"Controllo dati: "<<k<<" valore= "<<D[k]<<"      \t"<<eD[k]<<"      \t"<<conteggi[k]<<"      \t"<<econteggi[k]<<endl;
    }
    //Creo il canvas
    TCanvas *ciV = new TCanvas("ciV", "Lamber Beer", 200, 10, 1920, 1080);    
    ciV->SetFillColor(0);
    ciV->SetLogy();
    ciV->cd();
    //Creo il grafico usando i nostri vettori
    TGraphErrors *giV = new TGraphErrors(nMisure, D, conteggi, eD, econteggi);
    giV->SetMarkerSize(1);
    giV->SetMarkerStyle(22);
    giV->SetTitle("Lambert Beer");
    giV->GetXaxis()->SetTitle("Spessore [mm]");
    giV->GetYaxis()->SetTitle("Conteggi/s [cps] ");
    giV->Draw("AP");
    //faccio il fit i due fit
    cout << "\n\n ----  FACCIO IL FIT  ---- \n" << endl;
    //fit1
    TF1 *funz1 = new TF1("funz1", "[0]*pow(e,[1]*(x)) ", 0, 0.61);
    funz1->SetParameter(0,1000);
    funz1->SetLineColor(2);
    giV->Fit(funz1, "R+");
    cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
    //fit2
    TF1 *funz2 = new TF1("funz2", "[0]*pow(e,[1]*(x)) ", 0.61, 3.6);
    funz2->SetParameter(0,1000);
    funz2->SetLineColor(8);
    giV->Fit(funz2, "R+");
    cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;
    //Calcolo e mostro su schermo i valori di mu
    double mu1 = funz1->GetParameter(1)*10/(-2.7);
    double mu2 = funz2->GetParameter(1)*10/(-2.7);
    double emu1 = funz1->GetParError(1)*10/(-2.7);
    double emu2 = funz2->GetParError(1)*10/(-2.7);
    cout<<"-------------------------------------------------"<<endl;
    cout<<"Ottemiamo questi valori di Mu: "<<endl;
    cout<<"mu1-rosso: "<<mu1<<"+-"<< emu1 <<endl;
    cout<<"mu2-verde: "<<mu2<<"+-"<< emu2 <<endl;
    //Creo l'immagine
    TImage *img = TImage::Create();
    img->FromPad(ciV);
    img->WriteImage("Lambert_Beer.png");
}
