//proverò a creare il mio primo istogramma!! :)
#include <iostream>
#include <TCanvas.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TGaxis.h>
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
#include <TFile.h>
using namespace std;

double rate[999];  //to correct
double rate2[999]; //to correct

int nbin2;
double start2;
double end2;
int ratenumber2;


long double dohisto(const char FilePath[32], const char NamePhoto[32],const char NamePlot[32],int nmisure, int nbin, double start, double end, int SEL){
	
	double trasharray[nmisure/2];
	double time[nmisure/2];
	double time2[nmisure/2];
	int ratenumber = nmisure/2 -1;
	double 	s=0;
	int 		k=0;
	int 		j=0;
	///////////////////////
	nbin2       = nbin;
	start2      = start;
	end2        = end;
	ratenumber2 = ratenumber;
	///////////////////////
	double deltaT[ratenumber];
	long double AVGdeltaT=0;
	
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
	
	ifstream inFile;
	ofstream outFile;
	
	inFile.open(FilePath);
	if(!inFile){                                 
		cout << "---ATTENZIONE!!! Non c'è nessun file!!!---"<< endl;
	}
	for(int i=0;i<nmisure;i++){
		if(i % 2 == 0){
			inFile >> trasharray[k] >> time[k] >> time2[k] ;
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
	

	if( SEL == 0 ){
		for(int a=1; a<=ratenumber; a++){
		rate2[a] = 1000000000 * (ch16[a] - ch16[a-1]) / (time2[a] - time2[a-1]);
		//cout<<"rate a. ="<<a<<"\t rate ="<<rate[a]<<endl;
		AVGdeltaT = AVGdeltaT + ((time2[a] - time2[a-1]) / 1000000 );
		}
		AVGdeltaT = AVGdeltaT / ratenumber ;
	}
	else{
		for(int a=1; a<=ratenumber; a++){
		rate[a] = (ch16[a] - ch16[a-1]) / (time[a] - time[a-1]);
		//cout<<"a ="<<a<<"\t\t rate ="<<1000 *(time[a] - time[a-1])<<endl;
		AVGdeltaT = AVGdeltaT + ( 1000 *(time[a] - time[a-1]));
		}
		AVGdeltaT = AVGdeltaT / ratenumber ;
	}

	TCanvas *cX = new TCanvas("Rate","Rate",0,0,1280,720);
	cX->cd();
	
	TH1F *Rate = new TH1F("Rate",NamePlot, nbin, start, end);
	
	//Rate->SetStats(kFALSE);
	Rate->GetXaxis()->SetTitle("Rate [Hz]");
	Rate->GetYaxis()->SetTitle("Counts");
	//Rate->GetYaxis()->SetRangeUser(0., 170.);
	
	if( SEL == 0 ){
		for (int i=0; i<ratenumber; i++){
		Rate->Fill(rate2[i]);
		}
	}
	else{
		for (int i=0; i<ratenumber; i++){
		Rate->Fill(rate[i]);
		}
	}
	
	Rate->Draw("hist");
	
	TF1 *fitB = new TF1("tutto","gaus", start, end);
	
	fitB->SetParameters(1,1,1);
	
	Rate->SetLineColor(4);
	Rate->SetLineStyle(9);
	Rate->Fit(fitB,"ME0R");  
	cout << "Chi^2:" << fitB->GetChisquare() << ", number of DoF: " << fitB->GetNDF() << " (Probability: " << fitB->GetProb() << ")." << endl;
	fitB->SetLineColor(6);
	fitB->Draw("SAME");

	//Rate->SetRangeUser(0,160);
	
	TImage *img = TImage::Create();
   img->FromPad(cX);
   img->WriteImage(NamePhoto);
	
	return AVGdeltaT;
}


void istoFPGA(){
	
	//TFile fout("histograms.root", "RECREATE") ;
	
	long double AVGdeltaTmeasured[10];
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	AVGdeltaTmeasured[0] = dohisto("data/FPGA-time-rate-1MHz-1ms.txt", "img/FPGA-time-rate-1MHz-1ms.png","FPGA rate 1MHz 1ms",       2000, 24, 998500, 1001500, 0);
	AVGdeltaTmeasured[1] = dohisto("data/FPGA-time-rate-1MHz-50ms.txt", "img/FPGA-time-rate-1MHz-50ms.png","FPGA rate 1MHz 50ms",    2000, 24, 999950, 1000050, 0);
	AVGdeltaTmeasured[2] = dohisto("data/FPGA-time-rate-1MHz-100ms.txt", "img/FPGA-time-rate-1MHz-100ms.png","FPGA rate 1MHz 100ms", 2000, 24, 999980, 1000020, 0);
	AVGdeltaTmeasured[3] = dohisto("data/FPGA-time-rate-1MHz-200ms.txt", "img/FPGA-time-rate-1MHz-200ms.png","FPGA rate 1MHz 200ms", 2000, 24, 999990, 1000010, 0);
	AVGdeltaTmeasured[4] = dohisto("data/FPGA-time-rate-1MHz-300ms.txt", "img/FPGA-time-rate-1MHz-300ms.png","FPGA rate 1MHz 300ms", 2000, 24, 999993, 1000005, 0);
	AVGdeltaTmeasured[5] = dohisto("data/FPGA-time-rate-1MHz-500ms.txt", "img/FPGA-time-rate-1MHz-500ms.png","FPGA rate 1MHz 500ms", 2000, 24, 999995, 1000005, 0);
	
	AVGdeltaTmeasured[6] = dohisto("data/CPU-time-rate-1MHz-100ms.txt", "img/CPU-time-rate-1MHz-100ms.png","CPU rate 1MHz 100ms", 2000, 24, 999000, 1001000, 1);
	AVGdeltaTmeasured[7] = dohisto("data/CPU-time-rate-1MHz-200ms.txt", "img/CPU-time-rate-1MHz-200ms.png","CPU rate 1MHz 200ms", 2000, 24, 999000, 1001000, 1);
	AVGdeltaTmeasured[8] = dohisto("data/CPU-time-rate-1MHz-300ms.txt", "img/CPU-time-rate-1MHz-300ms.png","CPU rate 1MHz 300ms", 2000, 24, 999000, 1001000, 1);
	AVGdeltaTmeasured[9] = dohisto("data/CPU-time-rate-1MHz-500ms.txt", "img/CPU-time-rate-1MHz-500ms.png","CPU rate 1MHz 500ms", 2000, 24, 999600, 1000400, 1);
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout<<AVGdeltaTmeasured[0]<<" ms"<<endl;
	cout<<AVGdeltaTmeasured[1]<<" ms"<<endl;
	cout<<AVGdeltaTmeasured[2]<<" ms"<<endl;
	cout<<AVGdeltaTmeasured[3]<<" ms"<<endl;
	cout<<AVGdeltaTmeasured[4]<<" ms"<<endl;
	cout<<AVGdeltaTmeasured[5]<<" ms"<<endl;
	cout<<AVGdeltaTmeasured[6]<<" ms"<<endl;
	cout<<AVGdeltaTmeasured[7]<<" ms"<<endl;
	cout<<AVGdeltaTmeasured[8]<<" ms"<<endl;
	cout<<AVGdeltaTmeasured[9]<<" ms"<<endl;
	
	
	
	/* Double histogram graph 
	for (int i=0; i<ratenumber2; i++){
		rate[i] = rate[i]/1000000;
		rate2[i] = rate2[i]/1000000;
	}
	
	//TCanvas *Canvas = new TCanvas("Rate","Rate",0,0,1280,720);
	TCanvas *Canvas = new TCanvas("Rate","Rate",0,0,1920,1080);
	Canvas->cd();
	
	start2 = start2 / 1000000;
	end2 = end2 / 1000000;
	
	//TH1F *hFPGA = new TH1F("Rate","TEST1", nbin2, start2, end2);
	TH1F *hFPGA = new TH1F("Rate","FPGA and CPU rate 1MHz 100ms", 1024, start2, end2);
	hFPGA->SetStats(kFALSE);
	hFPGA->GetXaxis()->SetTitle("Rate [MHz]");
	hFPGA->GetXaxis()->CenterTitle();
	hFPGA->GetYaxis()->CenterTitle();
	hFPGA->GetYaxis()->SetTitle("Counts FPGA rate");
	//hFPGA->GetYaxis()->SetTitleColor(kBlue);
	//hFPGA->GetYaxis()->SetColor(kBlue);
	for (int i=0; i<ratenumber2; i++){
		hFPGA->Fill(rate2[i]);
	}
	
	hFPGA->Write() ;
	
	
	double scale = 1/hFPGA->Integral("width") * sqrt(6.28*hFPGA->GetRMS());
	//hFPGA->SetLineColor(kBlue);
	hFPGA->Scale(scale);
	hFPGA->Draw("HIST");
	Canvas->Update();
	
	//TH1F *hCPU = new TH1F("Rate","TEST2", nbin2, start2, end2);
	TH1F *hCPU = new TH1F("Rate","TEST2", 32, start2, end2);
	hCPU->SetStats(kFALSE);
	hCPU->GetXaxis()->SetTitle("Rate [MHz]");
	hCPU->GetYaxis()->SetTitle("Counts");
	for (int i=0; i<ratenumber2; i++){
		hCPU->Fill(rate[i]);
	}
	hCPU->Write() ;
   //double rightmax = 1.1*hCPU->GetMaximum();
   //double scale    = gPad->GetUymax()/rightmax;
	scale = 1/hCPU->Integral("width") * sqrt(6.28*hCPU->GetRMS());
   hCPU->SetLineColor(kRed);
   hCPU->Scale(scale);
	double rightmax = 1.1*hCPU->GetMaximum();
   hCPU->Draw("same HIST");
	
   //draw an axis on the right side
   TGaxis*axis = new TGaxis(gPad->GetUxmax(), gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(), 0, rightmax, 510, "+L");
   axis->SetLineColor(kRed);
   axis->SetLineWidth(1);
   axis->SetLabelColor(kRed);
   axis->SetLabelFont(40);
	axis->SetTitle("Counts CPU rate");
	axis->SetTitleFont(40);
	axis->CenterTitle();
	axis->SetTitleColor(kRed);
   axis->Draw();
	
	TImage *img2 = TImage::Create();
   img2->FromPad(Canvas);
   img2->WriteImage("img/FPGA_and_CPU_rate_1MHz_100ms.png");
	
	fout.Close();
	
	*/
}
