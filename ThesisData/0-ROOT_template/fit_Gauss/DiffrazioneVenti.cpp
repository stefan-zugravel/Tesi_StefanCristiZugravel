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
//Lavoro del favoloso gruppo A-7

void DiffrazioneVenti(){
    //Inizializzo i parametri iniziali.
    int nColonne = 4;
    int nMisure = 43;
    int MisureTot = nMisure*3;
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int test = 0;
    int testb = 0;
    //inizializzo i nostri vettori con le misure.
    double dueteta[nMisure];
    double edueteta[nMisure];
    double conteggi[nMisure];
    double econteggi[nMisure];
    //Valori dopo l'analisi dati
    double angolo[nMisure];
    double eangolo[nMisure];
    double dato[nMisure];
    double edato[nMisure];

    ifstream inFile;
    ofstream outFile; 
    //Apro il mio file.txt
    inFile.open("VentiKV_nuovo.txt");
    if(!inFile){                                 
        cout << "---ATTENZIONE!!! Non trovo nessun file!!!---"<< endl;
    }
    //Metto i miei dati nei rispettivi vettori
    for(int j = 0; j < nMisure; j++)
    {
        inFile >> dueteta[a];
        a++;
    }
    for(int j = nMisure; j < 2*nMisure; j++)
    {
        inFile >> edueteta[c];
        c++;
    }
    for(int j = 2*nMisure; j < 3*nMisure; j++)
    {
        inFile >> conteggi[d];
        d++;
    }
    for(int j = 3*nMisure; j < 4*nMisure; j++)
    {
        inFile >> econteggi[b];
        b++;
    }
    //Ciclo for per il debug, non è per forza necessario, ma è utile nel caso di qualche errore.
    //for(int k = 0; k < nMisure; k++)
    //{
    //    cout<<"Dati: "<<k<<" valore= "<<dueteta[k]<<"       \t"<<edueteta[k]<<"       \t"<<conteggi[k]<<"       \t"<<econteggi[k]<<endl;
    //}

    //Questa parte è molto importante, cercheremo di mediare i dati uguali, per ottenere un grafico migliore.
    int l=0;
    int pippo=0;
    for(int i = 0; i < nMisure; i++)
    {
        if (conteggi[i]>0) {
            pippo = 0;
            for( int k = i+1; k < nMisure; k++)
            {                
                if (dueteta[i]==dueteta[k]) {
                    dato[l]=(conteggi[i]+conteggi[k])/2;
                    edato[l]=(econteggi[i]+econteggi[k])/2;
                    angolo[l]=dueteta[i];
                    eangolo[l]=edueteta[i];
                    conteggi[k]=-2;
                    l++;
                    pippo = 1;
                }
                else
                {
                    test++;
                }
               testb++;
            }
            if (pippo == 0) {
                dato[l]=conteggi[i];
                edato[l]=econteggi[i];
                angolo[l]=dueteta[i];
                eangolo[l]=edueteta[i];
                l++; 
            }
            
            
        }
        else
        {
           // cout<<"elimino valore"<< k <<": "<<dueteta[i]<<endl;
        }
            
    }
    //fine analisi dati doppi

    //inizio conversione angoli da sessagesimali a radianti.
    int ParteInt[l];
    double ParteSessagesimale[l];
    double ParteDec[l];
    double GradoDec[l];
    double GradoRad[l];
    for(int i = 0; i < l; i++)
    {
        ParteInt[i]=angolo[i];
        ParteSessagesimale[i]=angolo[i]-ParteInt[i];
        ParteDec[i]=ParteSessagesimale[i]*5/3;
        GradoDec[i]=ParteDec[i]+ParteInt[i];
        GradoRad[i]=(M_PI*GradoDec[i])/180;
    }
    //Faccio la stessa cosa per gli errori
    int eParteInt[l];
    double eParteSessagesimale[l];
    double eParteDec[l];
    double eGradoDec[l];
    double eGradoRad[l];
    for(int i = 0; i < l; i++)
    {
        eParteInt[i]=eangolo[i];
        eParteSessagesimale[i]=eangolo[i]-eParteInt[i];
        eParteDec[i]=eParteSessagesimale[i]*5/3;
        eGradoDec[i]=eParteDec[i]+eParteInt[i];
        eGradoRad[i]=(M_PI*eGradoDec[i])/180;
    }
    
    for(int m = 0; m < l; m++)
    {
        cout<<"Dati: "<<m<<" valore= "<<angolo[m]<<"       \t"<<eangolo[m]<<"       \t"<<dato[m]<<"       \t"<<edato[m]<<endl;
    }
    cout<<"Il Numero totale di dati è: "<<l<<endl;
    cout<<"Il valore di test è: "<<test<<endl;
    cout<<"Il valore di testb è: "<<testb<<endl;
    //for(int k = 0; k < nMisure; k++)
    //{
    //    cout<<"Dati: "<<k<<" valore= "<<dueteta[k]<<"       \t"<<edueteta[k]<<"       \t"<<conteggi[k]<<"       \t"<<econteggi[k]<<endl;
    //}

    //Creo il canvas
    TCanvas *ciV = new TCanvas("ciV", "Diffrazione NaCl", 200, 10, 1920, 1080);    
    ciV->SetFillColor(0);
    //ciV->SetLogy();
    ciV->cd();
    //Creo il grafico usando i nostri vettori
    TGraphErrors *giV = new TGraphErrors(l, GradoRad, dato, eGradoRad, edato);
    giV->SetMarkerSize(1);
    giV->SetMarkerStyle(22);
    giV->SetTitle("Diffrazione NaCl 20KV");
    giV->GetXaxis()->SetTitle("2#theta [Rad]");
    giV->GetYaxis()->SetTitle("Conteggi/s [1/s]");
    giV->Draw("AP");
    //Procedo con i due fit, per i due picchi
    TF1* f = new TF1("func","gaus(0)",0.455,0.515);
    f->SetParNames("Norm","#mu","#sigma");
    //Impongo dei limiti ai parametri
    cout<<endl<<endl<<endl;
    cout<<"Questo è il fit in rosso"<<endl;
    f->SetParLimits(0,9,19);
    f->SetParLimits(1,0,1);
    f->SetParLimits(2,0,1);
    f->SetLineColor(2);  
    //configuro la schermata dei parametri
    //gStyle->SetOptFit(1111);
    giV->Fit(f,"RM+","",0.455,0.515);
    cout<<"Chi^2:"<<f->GetChisquare()<<", number of DoF: " <<f->GetNDF()<<" (Probability: "<<f->GetProb()<< ")."<<endl;

    //ora si vola con il secondo Fit
    TF1* f2 = new TF1("func2","gaus(0)",0.515,0.57);
    f2->SetParNames("Norm2","#mu2","#sigma2");
    //Impongo dei limiti ai parametri
    cout<<endl<<endl<<endl;
    cout<<"Questo è il fit in verde"<<endl;
    f2->SetParLimits(0,45,55);
    f2->SetParLimits(1,0,1);
    f2->SetParLimits(2,0,1);
    f2->SetLineColor(8);
    //configuro la schermata dei parametri
    //gStyle->SetOptFit(1111);
    giV->Fit(f2,"RM+","",0.515,0.57);
    cout<<"Chi^2:"<<f2->GetChisquare()<<", number of DoF: " <<f2->GetNDF()<<" (Probability: "<<f2->GetProb()<< ")."<<endl;


    //Creo l'immagine
    TImage *img = TImage::Create();
    img->FromPad(ciV);
    img->WriteImage("Diffrazione_20KV.png");

}