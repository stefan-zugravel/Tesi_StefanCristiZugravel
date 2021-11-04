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

using namespace std;
    void Americio(){
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
    
    cout<<"Il numero totale di conteggi è: "<<s<<endl;

    TCanvas *ciV = new TCanvas("ciV", "Americio", 200, 10, 1920, 1080);    
    ciV->SetFillColor(0);
    ciV->cd();
    
    TH1D *hist  = new TH1D("hist","Example",140,1300, 1440);
    hist->SetFillColor(0);
    hist->SetTitle("Conteggi Americio ");
    hist->SetTitle("Conteggi Americio ;CHN; N. conteggi");
    //hist->SetFillColor(2);
    for(int i=0; i<1440; i++){
        if(i>=1300){
            hist->SetBinContent(i-1300,conteggi[i]);
            hist->SetBinError(i-1300,sqrt(conteggi[i]));
        }
    }
    hist->Draw("histo E");



    // Fit with the sum of three Gaussians
    TF1* f = new TF1("func","gaus(0) + gaus(3) + gaus(6)",1300,1440);
    f->SetParNames("Norm_{1}","#mu_{1}","#sigma_{1}","Norm_{2}","#mu_{2}","#sigma_{2}","Norm_{3}","#mu_{3}","#sigma_{3}");
    // Set mameningful initial parameters
    f->SetParameter (0,400);
    f->SetParameter (1,1325);
    f->SetParameter (2,25);

    f->SetParameter (3,3000);
    f->SetParameter (4,1380);
    f->SetParameter (5,25);

    f->SetParameter (6,22000);
    f->SetParameter (7,1420);
    f->SetParameter (8,25);

    f->SetParLimits(0,300,500);
    f->SetParLimits(1,1320,1330);
    f->SetParLimits(2,2,20);

    f->SetParLimits(3,2500,3500);
    f->SetParLimits(4,1375,1385);
    f->SetParLimits(5,3,20);

    f->SetParLimits(6,20000,23000);
    f->SetParLimits(7,1415,1425);
    f->SetParLimits(8,3,20);


    gStyle->SetOptFit(1);
    gStyle->SetStatY(0.8);
    gStyle->SetStatX(0.8);
    hist->Fit(f);

    TF1* g[3];
  g[0] = new TF1("g0", "gaus", 1300,1440);
  g[0]->SetLineColor(kMagenta);
  g[1] = new TF1("g1", "gaus", 1300,1440);
  g[1]->SetLineColor(kBlue);
  g[2] = new TF1("g2", "gaus", 1300,1440);
  g[2]->SetLineColor(kGreen);
  double g_int[3];
  double int_total=0.;
  for (int i=0; i<3; ++i) {
    for (int j=0; j<3; ++j) {
      g[i]->SetParameter(j,f->GetParameter(3*i+j));
      //g_int[i] = g[i]->Integral(0,100);
      //int_total += g_int[i];
    }
    g[i]->SetLineWidth(2);
    g[i]->Draw("same");   
  }
  f->Draw("same");

    //               Print the observed BRs 
    //cout << endl << "BRs:" << endl;
    //cout << "        Measured     | True" << endl;
    //for (int i=0; i<3; ++i) {
    //double fr = g_int[i]/int_total;
    //cout << std::setprecision(3) << std::fixed;
    //cout << "Peak " << i << ": "  << fr << "+-" << sqrt(fr*(1-fr)/int_total) << " | "  << n[i]/(n[0]+n[1]+n[2]) << endl;
    //}



    //cout<<"------------------------------------------------------------------------"<<endl;
    //cout<<"--- Fit con palla di cristallo -----------------------------------------"<<endl; 
    //TF1 *ball= new TF1("ball","crystalball",1250,1550);//root conosce già la funzione di gauss
    //ball->SetParNames("Constant", "Mean", "Sigma", "Alpha", "N");
    //ball->SetLineColor(2);
    //hist->Fit(ball,"R");//fai il fit
    //ball->draw();
    //cout << "Chi^2: " << ball->GetChisquare() << ", number of DoF: " <<ball->GetNDF();
    //cout << " (Probability: " <<ball->GetProb() << ")." << endl;
    TImage *img = TImage::Create();
    img->FromPad(ciV);
    img->WriteImage("Americio.png");
    }