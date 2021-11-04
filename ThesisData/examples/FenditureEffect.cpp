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
void FenditureEffect()
{
	ifstream inFile;
	ofstream outFile;
	double s=0;
//////////////////////////////////////////////////////////////////////////////////FASE 1, fit 1_2ff2
	int nmisure1 = 201;
   double conteggi1[nmisure1];
	double numeroonda1[nmisure1];
	double erroreconteggi1[nmisure1];
	double errorenumeroonda1[nmisure1];
	double trasharray1[nmisure1];
	 
	for(int i=0;i<nmisure1;i++){
      errorenumeroonda1[i] = 0.5;      
   }
	 
   inFile.open("Data/Calibration_1_2ff2.txt");
   if(!inFile){                                 
      cout << "---ATTENZIONE!!! Non c'è nessun file!!!---"<< endl;
   }
   for(int i=0;i<nmisure1;i++){//modificato i<inFile
      inFile >> numeroonda1[i] >> trasharray1[i] >> conteggi1[i];
      erroreconteggi1[i] = sqrt(conteggi1[i]);
   }
	inFile.close();

    
	for(int i=0 ; i<nmisure1 ; i++){
	cout<<"Numero d'onda "<<i<<"= "<<numeroonda1[i]<<"\t  conteggi "<<i<<"= "<<conteggi1[i] <<endl;
	}

   TCanvas *srV1 = new TCanvas("srV1", "Spectral line Hg-Ar 546.074nm 2ff2", 200, 10, 1920, 1080);    
   srV1->SetFillColor(0);
   srV1->cd();
	
	TGraphErrors *giV1 = new TGraphErrors(nmisure1,numeroonda1,conteggi1,errorenumeroonda1,erroreconteggi1);
	//giV->SetMarkerSize(1);
	//giV->SetMarkerStyle(22);
	giV1->SetTitle("Spectral line Hg-Ar 546.074nm 2ff2");
	giV1->GetXaxis()->SetTitle("Wave number [cm^{-1}]");
	giV1->GetYaxis()->SetTitle("Counts");
	giV1->Draw("AP");

	
	TF1* f1 = new TF1("func","gaus(0) + [3]",18270,18310);
   f1->SetParNames("Norm_{1}","#mu_{1}","#sigma_{1}", "const");
   // Set mameningful initial parameters
   f1->SetParameter (0,29500);
   f1->SetParameter (1,18293);
   f1->SetParameter (2,10);
	f1->SetParameter (3,60);
	
   f1->SetParLimits(0,28000,30500);
   f1->SetParLimits(1,18290,18305);
   f1->SetParLimits(2,2,20);
	f1->SetParLimits(3,15,100);
	
	giV1->Fit(f1);


   gStyle->SetOptFit(1);
   gStyle->SetStatY(0.8);
   gStyle->SetStatX(0.8);

   f1->Draw("same");

   TImage *img1= TImage::Create();
   img1->FromPad(srV1);
   img1->WriteImage("HgAr_2ff2__1.png");
//////////////////////////////////////////////////////////////////////////////////FASE 2, fit 1_4ff4
	int nmisure2 = 191;
   double conteggi2[nmisure2];
	double numeroonda2[nmisure2];
	double erroreconteggi2[nmisure2];
	double errorenumeroonda2[nmisure2];
	double trasharray2[nmisure2];
	 
	for(int i=0;i<nmisure2;i++){
      errorenumeroonda2[i] = 0.5;      
   }
	 
   //double s=0;
   //ifstream inFile;
   //ofstream outFile;    
   inFile.open("Data/Calibration_1_4ff4.txt");
   if(!inFile){                                 
      cout << "---ATTENZIONE!!! Non c'è nessun file!!!---"<< endl;
   }
   for(int i=0;i<nmisure2;i++){//modificato i<inFile
      inFile >> numeroonda2[i] >> trasharray2[i] >> conteggi2[i];
      erroreconteggi2[i] = sqrt(conteggi2[i]);
   }
	inFile.close();
    
   cout<<"Il numero totale di conteggi è: "<<s<<endl;

    
	for(int i=0 ; i<nmisure2 ; i++){
	cout<<"Numero d'onda "<<i<<"= "<<numeroonda2[i]<<"\t  conteggi "<<i<<"= "<<conteggi2[i] <<endl;
	}

   TCanvas *srV2 = new TCanvas("srV2", "Spectral line Hg-Ar 546.074nm 4ff4", 200, 10, 1920, 1080);    
   srV2->SetFillColor(0);
   srV2->cd();
	
	TGraphErrors *giV2 = new TGraphErrors(nmisure2,numeroonda2,conteggi2,errorenumeroonda2,erroreconteggi2);
	//giV->SetMarkerSize(1);
	//giV->SetMarkerStyle(22);
	giV2->SetTitle("Spectral line Hg-Ar 546.074nm 4ff4");
	giV2->GetXaxis()->SetTitle("Wave number [cm^{-1}]");
	giV2->GetYaxis()->SetTitle("Counts");
	giV2->Draw("AP");

	
	TF1* f2 = new TF1("func2","gaus(0) + [3]",18265,18340);  //18270, 18310
   f2->SetParNames("Norm_{1}","#mu_{1}","#sigma_{1}", "const");
   // Set mameningful initial parameters
   f2->SetParameter (0,14000);
   f2->SetParameter (1,18293);
   f2->SetParameter (2,10);
	f2->SetParameter (3,60);
	
   f2->SetParLimits(0,10000,17000);
   f2->SetParLimits(1,18290,18305);
   f2->SetParLimits(2,2,20);
	f2->SetParLimits(3,15,100);
	 
	giV2->Fit(f2);


   gStyle->SetOptFit(1);
   gStyle->SetStatY(0.8);
   gStyle->SetStatX(0.8);

   f2->Draw("same");

   TImage *img2 = TImage::Create();
   img2->FromPad(srV2);
   img2->WriteImage("HgAr_4ff4__1.png");
//////////////////////////////////////////////////////////////////////////////////FASE 3, fit 1_6ff6
	int nmisure3 = 186;
   double conteggi3[nmisure3];
	double numeroonda3[nmisure3];
	double erroreconteggi3[nmisure3];
	double errorenumeroonda3[nmisure3];
	double trasharray3[nmisure3];
	 
	for(int i=0;i<nmisure3;i++){
      errorenumeroonda3[i] = 0.5;      
   }
	 
   //double s=0;
   //ifstream inFile;
   //ofstream outFile;    
   inFile.open("Data/Calibration_1_6ff6.txt");
   if(!inFile){                                 
      cout << "---ATTENZIONE!!! Non c'è nessun file!!!---"<< endl;
   }
   for(int i=0;i<nmisure3;i++){//modificato i<inFile
      inFile >> numeroonda3[i] >> trasharray3[i] >> conteggi3[i];
      erroreconteggi3[i] = sqrt(conteggi3[i]);
   }
	inFile.close();
   
    
	for(int i=0 ; i<nmisure3 ; i++){
	cout<<"Numero d'onda "<<i<<"= "<<numeroonda3[i]<<"\t  conteggi "<<i<<"= "<<conteggi3[i] <<endl;
	}

   TCanvas *srV3 = new TCanvas("srV3", "Spectral line Hg-Ar 546.074nm 6ff6", 200, 10, 1920, 1080);    
   srV3->SetFillColor(0);
   srV3->cd();
	
	TGraphErrors *giV3 = new TGraphErrors(nmisure3,numeroonda3,conteggi3,errorenumeroonda3,erroreconteggi3);
	//giV->SetMarkerSize(1);
	//giV->SetMarkerStyle(22);
	giV3->SetTitle("Spectral line Hg-Ar 546.074nm 6ff6");
	giV3->GetXaxis()->SetTitle("Wave number [cm^{-1}]");
	giV3->GetYaxis()->SetTitle("Counts");
	giV3->Draw("AP");

	/*
	TF1* f3 = new TF1("func3","gaus(0)",18270,18310);
   f3->SetParNames("Norm_{1}","#mu_{1}","#sigma_{1}");
   // Set mameningful initial parameters
   f3->SetParameter (0,29500);
   f3->SetParameter (1,18293);
   f3->SetParameter (2,10);
	
   f3->SetParLimits(0,28000,30500);
   f3->SetParLimits(1,18290,18305);
   f3->SetParLimits(2,2,20);
	
	giV3->Fit(f3);


   gStyle->SetOptFit(1);
   gStyle->SetStatY(0.8);
   gStyle->SetStatX(0.8);

   f3->Draw("same");
	
	*/

   TImage *img3 = TImage::Create();
   img3->FromPad(srV3);
   img3->WriteImage("HgAr_6ff6__1.png");

//////////////////////////////////////////////////////////////////////////////////FASE 4, fit 1_5ff5
	int nmisure4 = 183;
   double conteggi4[nmisure4];
	double numeroonda4[nmisure4];
	double erroreconteggi4[nmisure4];
	double errorenumeroonda4[nmisure4];
	double trasharray4[nmisure4];
	 
	for(int i=0;i<nmisure4;i++){
      errorenumeroonda4[i] = 0.5;      
   }
	   
   inFile.open("Data/Calibration_1_5ff5.txt");
   if(!inFile){                                 
      cout << "---ATTENZIONE!!! Non c'è nessun file!!!---"<< endl;
   }
   for(int i=0;i<nmisure4;i++){//modificato i<inFile
      inFile >> numeroonda4[i] >> trasharray4[i] >> conteggi4[i];
      erroreconteggi4[i] = sqrt(conteggi4[i]);
   }
	inFile.close();
   
    
	for(int i=0 ; i<nmisure4 ; i++){
	cout<<"Numero d'onda "<<i<<"= "<<numeroonda4[i]<<"\t  conteggi "<<i<<"= "<<conteggi4[i] <<endl;
	}

   TCanvas *srV4 = new TCanvas("srV4", "Spectral line Hg-Ar 546.074nm 5ff5", 200, 10, 1920, 1080);    
   srV4->SetFillColor(0);
   srV4->cd();
	
	TGraphErrors *giV4 = new TGraphErrors(nmisure4,numeroonda4,conteggi4,errorenumeroonda4,erroreconteggi4);
	//giV->SetMarkerSize(1);
	//giV->SetMarkerStyle(22);
	giV4->SetTitle("Spectral line Hg-Ar 546.074nm 5ff5");
	giV4->GetXaxis()->SetTitle("Wave number [cm^{-1}]");
	giV4->GetYaxis()->SetTitle("Counts");
	giV4->Draw("AP");

	
	TF1* f4 = new TF1("func4","gaus(0) + [3]",18265,18340);  //test here
   f4->SetParNames("Norm_{1}","#mu_{1}","#sigma_{1}", "const");
   // Set mameningful initial parameters
   f4->SetParameter (0,6000);
   f4->SetParameter (1,18293);
   f4->SetParameter (2,10);
	f4->SetParameter (3,60);
	
   f4->SetParLimits(0,5000,7000);
   f4->SetParLimits(1,18290,18305);
   f4->SetParLimits(2,2,20);
	f4->SetParLimits(3,15,100);
	
	giV4->Fit(f4);


   gStyle->SetOptFit(1);
   gStyle->SetStatY(0.8);
   gStyle->SetStatX(0.8);

   f4->Draw("same");

   TImage *img4 = TImage::Create();
   img4->FromPad(srV4);
   img4->WriteImage("HgAr_5ff5__1.png");
//////////////////////////////////////////////////////////////////////////////////FASE 5, grafico finale FWHM Fenditures

	int nmisure5 = 3 ;
	
	double fwhm[nmisure5];
	double errorefwhm[nmisure5];
	double fenditure[] = {2 , 4 , 5};
	double errorefenditure[] = {0.015,0.015,0.015};
	
	fwhm[0] = f1->GetParameter(2) * 2.35 ;
	fwhm[1] = f2->GetParameter(2) * 2.35 ;
	fwhm[2] = f4->GetParameter(2) * 2.35 ;
	
	errorefwhm[0] = f1->GetParError(2) * 2.35 ;
	errorefwhm[1] = f2->GetParError(2) * 2.35 ;
	errorefwhm[2] = f4->GetParError(2) * 2.35 ;

	TCanvas *srV5 = new TCanvas("srV5", "Fenditure effect", 200, 10, 1920, 1080);    
   srV5->SetFillColor(0);
   srV5->cd();
	
	TGraphErrors *giV5 = new TGraphErrors(nmisure5,fenditure,fwhm,errorefenditure,errorefwhm);
	//giV->SetMarkerSize(1);
	//giV->SetMarkerStyle(22);
	giV5->SetTitle("Fenditure effect");
	giV5->GetXaxis()->SetTitle("Fenditure aperture]");
	giV5->GetYaxis()->SetTitle("FWHM [cm^{-1}");
	giV5->Draw("AP");

	
	TF1* f5 = new TF1("func4","x*[0] + [1]",0,25);  //test here
   f5->SetParNames("slope", "const");
   // Set mameningful initial parameters
	
	giV5->Fit(f5);


   gStyle->SetOptFit(1);
   gStyle->SetStatY(0.8);
   gStyle->SetStatX(0.8);

   f5->Draw("same");

   TImage *img5 = TImage::Create();
   img5->FromPad(srV5);
   img5->WriteImage("FenditureEffect.png");
}