#include <iostream>       // ci serve per stampare a video il testo
#include <TGraphErrors.h> // ci serve per istanziare grafici
#include <TAxis.h>        // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>      // ci serve per disegnare i grafici
#include <TH1D.h>          // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>        // ci serve per manipolare l'output a video
#include <TImage.h>       // ci serve per le immagini
#include <TPaveStats.h>   // ci serve per la tabella con i valori
#include <TFitResult.h>
#include <TMatrixD.h>
#include <fstream>
#include <TStyle.h>
#include <TF1.h>
#include <TMath.h>

using namespace std;
    void AmericioBall(){
    int nmisure = 2048;
    double conteggi[nmisure];
    double s=0;
    ifstream inFile;
    ofstream outFile;    
    inFile.open("Americio.txt");
    if(!inFile){                                 
        cout << "---ATTENZIONE!!! Non c'è nessun file!!!---"<< endl;
    }
    for(int i=0;i<nmisure;i++){//modificato i<inFile
        inFile >> conteggi[i];
        //cout<<"Controllo inserimento dati: "<<i<<" valore= "<< conteggi[i]<<endl;
        s=s+conteggi[i];
    }
    

    TCanvas *ciV = new TCanvas("ciV", "Americio", 200, 10, 1920, 1080);    
    ciV->SetFillColor(0);
    ciV->SetLogy();
    ciV->cd();
    
    
    TH1D *hist  = new TH1D("hist","Example",180,1300, 1480);
    hist->SetFillColor(0);
    hist->SetTitle("Conteggi Americio ");
    hist->SetTitle("Conteggi Americio ;CHN; N. conteggi");
    //hist->SetFillColor(2);
    for(int i=0; i<1480; i++){
        if(i>=1300){
            hist->SetBinContent(i-1299,conteggi[i]);
            hist->SetBinError(i-1299,sqrt(conteggi[i]));
        }
    }
    hist->Draw("hist E");



    // Fit with the sum of three Gaussians
    TF1* f = new TF1("func","crystalball(0) + crystalball(5) + crystalball(10)",1300,1430);
    f->SetParNames("Norm_{1}","#mu_{1}","#sigma_{1}","#alpha_{1}","N_{1}","Norm_{2}","#mu_{2}","#sigma_{2}","#alpha_{2}","N_{2}");
    f->SetParName(10,"Norm_{3}");
    f->SetParName(11,"#mu_{3}");
    f->SetParName(12,"#sigma_{3}");
    f->SetParName(13,"#alpha_{3}");
    f->SetParName(14,"N_{3}");
    // Set mameningful initial parameters
    f->SetParameter (0,400);
    f->SetParameter (1,1325);
    f->SetParameter (2,10);
    f->SetParameter (3,1);
    f->SetParameter (4,10);

    f->SetParameter (5,3150);
    f->SetParameter (6,1380);
    f->SetParameter (7,10);
    f->SetParameter (8,1);
    f->SetParameter (9,1);

    f->SetParameter (10,22000);
    f->SetParameter (11,1420);
    f->SetParameter (12,10);
    f->SetParameter (13,1);
    f->SetParameter (14,3000);

    f->SetParLimits(0,230,500);
    f->SetParLimits(1,1320,1340);
    f->SetParLimits(2,0,40);
    f->SetParLimits(3,0,5);
    f->SetParLimits(4,0,20);

    f->SetParLimits(5,3000,3500);
    f->SetParLimits(6,1375,1385);
    f->SetParLimits(7,6,30);
    f->SetParLimits(8,0,5);
    f->SetParLimits(9,0,20);

    f->SetParLimits(10,20000,25000);
    f->SetParLimits(11,1410,1430);
    f->SetParLimits(12,6,14);
    f->SetParLimits(13,0,10);   
    f->SetParLimits(14,2000,4000);
    
    gStyle->SetOptFit(1);
    gStyle->SetStatY(0.8);
    gStyle->SetStatX(0.8);
    hist->Fit(f,"","",1300,1430);

    TF1* g[3];
    g[0] = new TF1("g0", "crystalball", 1300,1480);
    g[0]->SetLineColor(kMagenta);
    g[1] = new TF1("g1", "crystalball", 1300,1480);
    g[1]->SetLineColor(kBlue);
    g[2] = new TF1("g2", "crystalball", 1300,1480);
    g[2]->SetLineColor(kGreen);
    double g_int[3];
    double int_total=0.;
    for (int k=0; k<3; ++k) {
        for (int j=0; j<5; ++j) {
            g[k]->SetParameter(j,f->GetParameter(5*k+j));
        }
        g_int[k] = g[k]->Integral(1300,1480);
        int_total += g_int[k];
        g[k]->SetLineWidth(2);
        g[k]->Draw("same");   
    }
    f->Draw("same");

    cout<<"Il numero totale di conteggi è: "<<s<<endl;
    cout<<"Il numero di conteggi valutati dalla funzione è: "<<int_total<<endl;
    cout<<"Il numero di conteggi con valutati è :"<<s-int_total<<endl;

    //Print the observed BRs 
    cout << endl << "BRs:" << endl;
    cout << "        Measured     " << endl;
    for (int i=0; i<3; ++i) {
    double fr = g_int[i]/int_total;
    cout << std::setprecision(3) << std::fixed;
    cout << "Picco " << i << ": ("  << fr*100 << "+-" << sqrt(fr*(1-fr)/int_total)*100 << ")% " <<endl;
    //cout << n[i]/(n[0]+n[1]+n[2]) << endl;
    }


    TImage *img = TImage::Create();
    img->FromPad(ciV);
    img->WriteImage("AmericioBall.png");
    }