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
void Lambert2(){
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
    //Faccio anche il logaritmo di ogni valore di I
    double  I[nMisure];
    double  eI[nMisure];

    for(int k = 0; k < nMisure; k++)
    {
        I[k]=log(conteggi[k]);
        eI[k]=log(econteggi[k]);
        cout<<"Controllo dati: "<<k<<" valore= "<<D[k]<<"      \t"<<eD[k]<<"      \t"<<conteggi[k]<<"      \t"<<econteggi[k]<<endl;
    }
    //Creo il canvas
    TCanvas *ciV = new TCanvas("ciV", "Lamber Beer", 200, 10, 1920, 1080);    
    ciV->SetFillColor(0);
    ciV->cd();
    //Creo il grafico usando i nostri vettori
    TGraphErrors *giV = new TGraphErrors(nMisure, D, I, eD, eI);
    giV->SetMarkerSize(1);
    giV->SetMarkerStyle(22);
    giV->SetTitle("Lambert Beer ln(I)=-ux-ln(I0)");
    giV->GetXaxis()->SetTitle("Spessore [mm]");
    giV->GetYaxis()->SetTitle("log(Conteggi/s [cps]) ");
    giV->Draw("AP");

    //faccio un fit lineare per trovare -ln(I0)
    //fit1
    TF1 *funz1 = new TF1("funz1", "[0]*x + [1]", 0, 4);
    funz1->SetParameter(1,-1);
    funz1->SetParameter(0,-1);
    giV->Fit(funz1, "R+");

    //creo le variabili ln(I0-I)
    double lnI0 = -(funz1->GetParameter(1));
    double elnI0 = funz1->GetParError(1);
    double Ii[nMisure];
    double eIi[nMisure];

    //Calcolo e metto in un vettore ln(I0/I)
    for(int i = 0; i < nMisure; i++)
    {
        Ii[i]=-I[i]-lnI0;
        eIi[i]=sqrt(pow(eI[i],2)+pow(elnI0,2));
    }
    //Creo un nuovo Canvas
    TCanvas *ciV2 = new TCanvas("ciV2", "Lamber Beer 2", 200, 10, 1920, 1080);    
    ciV2->SetFillColor(0);
    ciV2->cd();

    //Creo il grafico usando i nostri vettori
    TGraphErrors *giV2 = new TGraphErrors(nMisure, D, Ii, eD, eIi);
    giV2->SetMarkerSize(1);
    giV2->SetMarkerStyle(22);
    giV2->SetTitle("Lambert Beer ln(I0/I)=ux");
    giV2->GetXaxis()->SetTitle("Spessore [mm]");
    giV2->GetYaxis()->SetTitle("log(I0/I [cps]) ");
    giV2->Draw("AP");

    //provo a fittare con una retta e controllo se passa per l'origine
    TF1 *funz2 = new TF1("funz2", "[0]*x + [1]", 0, 4);
    funz1->SetParameter(1,0);
    giV2->Fit(funz1, "R+");


  
    
    
    
}
