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
#include <iostream>           // ci serve per stampare a video il testo
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TGraph.h>     // ci serve per istanziare grafici
#include <TMultiGraph.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video 
#include <TImage.h>           // ci serve per le immagini
#include <TPaveStats.h>       // ci serve per la tabella con i valori
#include <TString.h>
using namespace std;


void istoCPU(){
	//TString FilePath("data/CPU-time-rate-10kHz-200ms.txt");      // Path per il file con i dati
	//TString NamePhoto("img/CPU-time-rate-10kHz-200ms.png");
	//TString NamePlot("CPU rate 10kz 200ms");
	
	//TString FilePath("data/CPU-time-rate-10kHz-500ms.txt");      // Path per il file con i dati
	//TString NamePhoto("img/CPU-time-rate-10kHz-500ms.png");
	//TString NamePlot("CPU rate 10kHz 500ms");
	
	TString FilePath("data/CPU-time-rate-1MHz-200ms.txt");       // Path per il file con i dati
	TString NamePhoto("img/CPU-time-rate-1MHz-200ms.png");
	TString NamePlot("CPU rate 1MHz 200ms");
	
	//TString FilePath("data/CPU-time-rate-1MHz-500ms.txt");       // Path per il file con i dati
	//TString NamePhoto("img/CPU-time-rate-1MHz-500ms.png");
	//TString NamePlot("CPU rate 1MHz 500ms");
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//TString FilePath("data/FPGA-time-rate-10kHz-200ms.txt");     // Path per il file con i dati
	//TString NamePhoto("img/FPGA-time-rate-10kHz-200ms.png");
	//TString NamePlot("FPGA rate 10kHz 200ms");
	
	//TString FilePath("data/FPGA-time-rate-10kHz-500ms.txt");     // Path per il file con i dati
	//TString NamePhoto("img/FPGA-time-rate-10kHz-500ms.png");
	//TString NamePlot("FPGA rate 10kHz 500ms");
	
	//TString FilePath("data/FPGA-time-rate-1MHz-200ms.txt");      // Path per il file con i dati
	//TString NamePhoto("img/FPGA-time-rate-1MHz-200ms.png");
	//TString NamePlot("FPGA rate 1MHz 200ms");
	
	//TString FilePath("data/FPGA-time-rate-1MHz-500ms.txt");      // Path per il file con i dati
	//TString NamePhoto("img/FPGA-time-rate-1MHz-500ms.png");
	//TString NamePlot("FPGA rate 1MHz 500ms");
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//TH1F *Campione = new TH1F("Campione",NamePlot,24, 9999, 10005);     //CPU-time-rate-10kHz-200ms
	//TH1F *Campione = new TH1F("Campione",NamePlot,24, 9999, 10005);     //CPU-time-rate-10kHz-500ms
	TH1F *Campione = new TH1F("Campione",NamePlot,24, 999500, 1000500); //CPU-time-rate-1MHz-200ms
	//TH1F *Campione = new TH1F("Campione",NamePlot,24, 999500, 1000500); //CPU-time-rate-1MHz-500ms
	
	//TH1F *Campione = new TH1F("Campione",NamePlot,24, 9999, 10005);     //FPGA-time-rate-10kHz-200ms
	//TH1F *Campione = new TH1F("Campione",NamePlot,24, 9999, 10005);     //FPGA-time-rate-10kHz-500ms
	//TH1F *Campione = new TH1F("Campione",NamePlot,24, 999500, 1000500); //FPGA-time-rate-1MHz-200ms
	//TH1F *Campione = new TH1F("Campione",NamePlot,24, 999500, 1000500); //FPGA-time-rate-1MHz-500ms
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	int nmisure = 1000;
	double trasharray[nmisure/2];
	double time[nmisure/2];
	
	double ch0[nmisure/2];
	double ch1[nmisure/2];
	double ch2[nmisure/2];
	double ch3[nmisure/2];
	double ch4[nmisure/2];
	double ch5[nmisure/2];
	double ch6[nmisure/2];
	double ch7[nmisure/2];
	double ch8[nmisure/2];
	double ch9[nmisure/2];
	double ch10[nmisure/2];
	double ch11[nmisure/2];
	double ch12[nmisure/2];
	double ch13[nmisure/2];
	double ch14[nmisure/2];
	double ch15[nmisure/2];
	double ch16[nmisure/2];
	double ch17[nmisure/2];
	double ch18[nmisure/2];
	double ch19[nmisure/2];
	double ch20[nmisure/2];
	double ch21[nmisure/2];
	double ch22[nmisure/2];
	double ch23[nmisure/2];
	double ch24[nmisure/2];
	double ch25[nmisure/2];
	double ch26[nmisure/2];
	double ch27[nmisure/2];
	double ch28[nmisure/2];
	double ch29[nmisure/2];
	double ch30[nmisure/2];
	double ch31[nmisure/2];
	double ch32[nmisure/2];
	double ch33[nmisure/2];
	double ch34[nmisure/2];
	double ch35[nmisure/2];
	double ch36[nmisure/2];
	double ch37[nmisure/2];
	double ch38[nmisure/2];
	double ch39[nmisure/2];
	double ch40[nmisure/2];
	double ch41[nmisure/2];
	double ch42[nmisure/2];
	double ch43[nmisure/2];
	double ch44[nmisure/2];
	double ch45[nmisure/2];
	double ch46[nmisure/2];
	double ch47[nmisure/2];
	double ch48[nmisure/2];
	
	int ratenumber = nmisure/2 -1;
	double 	s=0;
	int 		k=0;
	int 		j=0;
	double rate[ratenumber];
	
	ifstream inFile;
	ofstream outFile;    
	inFile.open(FilePath);
	
	
	cout<<"**************************************************************************"<<endl;
	
	if(!inFile){                                 
		cout << "---ATTENZIONE!!! Non c'è nessun file!!!---"<< endl;
	}
	for(int i=0;i<nmisure;i++){
		if(i % 2 == 0){
			inFile >> trasharray[k] >> time[k] >> trasharray[k] ;
			//cout<<"n. ="<<k<<"\t time ="<<time[k]<<endl;
			k++;
		}
		else{
			inFile >> ch0[j] >> ch1[j] >> ch2[j] >> ch3[j] >> ch4[j] >> ch5[j] >> ch6[j] >> ch7[j] >> ch8[j] >> ch9[j] >> ch10[j] >> ch11[j] >> ch12[j] >> ch13[j] >> ch14[j] >> ch15[j] >> ch16[j] >> ch17[j] >> ch18[j] >> ch19[j] >> ch20[j] >> ch21[j] >> ch22[j] >> ch23[j] >> ch24[j] >> ch25[j] >> ch26[j] >> ch27[j] >> ch28[j] >> ch29[j] >> ch30[j] >> ch31[j] >> ch32[j] >> ch33[j] >> ch34[j] >> ch35[j] >> ch36[j] >> ch37[j] >> ch38[j] >> ch39[j] >> ch41[j] >> ch41[j] >> ch42[j] >> ch43[j] >> ch44[j] >> ch45[j] >> ch46[j] >> ch47[j];
			//cout<<"n. ="<<j<<"\t ch0 ="<<ch0[j]<<endl;
			j++;
		}
	}
	inFile.close();

	
	for(int a=1; a<=ratenumber; a++){
		rate[a] = (ch16[a] - ch16[a-1]) / (time[a] - time[a-1]);
		cout<<"rate a. ="<<a<<"\t rate ="<<rate[a]<<endl;
	}

	TCanvas *cX = new TCanvas("x","x",0,0,1280,720);
	cX->cd();
	
	
	
	Campione->SetStats(kFALSE);
	Campione->GetXaxis()->SetTitle("Rate [Hz]");
	Campione->GetYaxis()->SetTitle("Counts");
	
	for (int i=0; i<ratenumber; i++){
		Campione->Fill(rate[i]);
	}
	
	Campione->Draw();
	
	TF1 *fitB = new TF1("tutto","gaus", 998500, 1001500);
	Campione->SetLineColor(4);
	Campione->SetLineStyle(9);
	Campione->Fit(fitB,"ME0R"); 
	cout << "Chi^2:" << fitB->GetChisquare() << ", number of DoF: " << fitB->GetNDF() << " (Probability: " << fitB->GetProb() << ")." << endl;
	fitB->SetLineColor(6);
	fitB->Draw("same");
	
	
	
	TImage *img = TImage::Create();
   img->FromPad(cX);
   img->WriteImage(NamePhoto);

}
