/*  PROGRAMMA LAMPADINA
Programma di base per l'analisi dati della caratteristica della lampadina.
In particolare, il seguente programma fa:
Grafico della curva i(V)
    --> si richiede di implementare la regressione con la curva teorica (vedi schede)
Grafico e una regressione della curva P(R)
    --> si richiede di implementare anche una regressione con una polinomiale di ordine 4

Le incertezze sulle misure sono indicative e vanno calcolate opportunamente in base al modello di tester adottato
La propagazione degli errori sulle quantità derivate va effettuata

Indicativamente, nel testo è presente dove [modifcare] il programma.

per eseguire il programma adottare uno dei due seguenti metodi alternativi:
1- da riga dei comandi (shell) digitare    root -l lampadina.C++
2- da riga dei comandi (shell) digitare    root -l    e una volta dentro a root digitare   .x lampadina.C++
*/


#include <iostream>           // ci serve per stampare a video il testo
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video 

using namespace std; 


// Corpo del programma. La funzione qui sotto deve avere lo stesso nome del file .C
void lampadina()
{

  // --------------------------- DATI ------------------------------- // 
  // Resistenza della lampadina, misurata in laboratorio con il multimetro
  const float R20 = 12.2; const float sR20 = 0.005*12.2 + 0.8; // ESEMPIO calcolo incertezza! Dipende dal modello!! Modificare 

  // numero misure prese
  const int nmisure = 24;

  
  // Dati presi in laboratorio: V = tensione, sV = incertezza tensione, i = intensità di corrente, si = incertezza intensità di corrente
  // consiglio di non mettere il valore per V = 0 V altrimenti si avranno problemi nella parte in cui si calcolano i logaritmi
  float V[]  = {320.0e-3, 820.0e-3, 1.370, 1.850, 2.300, 2.720, 3.270, 3.690, 4.340, 4.800, 5.280, 5.670, 6.240, 6.660, 7.160, 7.660, 8.200, 8.680, 9.240, 9.700, 10.20, 10.60, 11.18, 11.64}; // V
  float i[]  = {15.00, 21.00, 27.70, 32.80, 37.30, 40.80, 45.70, 49.20, 53.80, 56.80, 60.10, 62.50, 66.00, 68.50, 71.70, 74.50, 77.60, 80.20, 83.10, 85.60, 88.20, 90.20, 93.30, 95.60}; // mA
		


  // ---------------------------------------------------------------- //


  // ---------------------- Quantità derivate ----------------------- //

  // Array che conterà incertezze su i e V
  float sV[nmisure];
  float si[nmisure];
		
  // Array che conterrà i valori calcolati delle resistenze e loro incertezze
  float R[nmisure];
  float sR[nmisure];

  // Array che conterrà i valori calcolati delle potenze e loro incertezze
  float P[nmisure];
  float sP[nmisure];

  // ciclo for (loop) sulle misure
  for(int j=0; j<nmisure;++j){

    // calcolo incertezza! 
    if      (V[j] < 1)  sV[j] = V[j]*0.001 + 5e-4;
    else if (V[j] < 10) sV[j] = V[j]*0.001 + 5e-3;
    else                sV[j] = V[j]*0.001 + 5e-2;  

    // calcolo incertezza!
    if (i[j] < 1) si[j] = i[j]*0.015 + 3e-3;
    else          si[j] = i[j]*0.015 + 3e-2;
    
    R[j]  = V[j]/i[j]*1000;  // in ohm
    sR[j] =sqrt(pow(sV[j],2)/pow(i[j],2)+(pow(V[j],2)/pow(i[j],4))*pow(si[j],2)); // Effettuare la propagazione degli errori!!
    P[j]  = V[j] * i[j];
    sP[j] = sqrt(pow(i[j]*sV[j],2)+pow(V[j]*si[j],2)); // Effettuare la propagazione degli errori!!

    // Stampa a video dei valori. \t inserisce un tab nel print out. Mettendo \n si va a capo invece
    cout << "Measurement number " << j << ":\t V = (" << V[j] << " +- " << sV[j] << ") V, \t i = (" << i[j] << " +- " << si[j] << ") mA,\t R = (" 
	 << setprecision(4) << R[j] << " +- " << sR[j] << ") ohm, \t P = (" 
	 << P[j] << " +- " << sP[j] << ") mW." << endl;    
  }
  // ----------------------------------------------------------------- //



  
  // --------------------- Grafico i(V) ------------------------------ //
  // Creo il canvas (la tela) su cui disegnare il grafico. "ciV" è il il suo nome in memoria
  // è bene che sia unico dentro al programma. "i(v)" è semplicemente il titolo del canvas
  // le due coppie di numeri che seguono sono le coordinate dell'angolo superiore sinistro e le seconde
  // la dimensione in pixel lungo x e lungo y
  TCanvas *ciV = new TCanvas("ciV","i(v)",200,10,600,400);
  // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
  ciV->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  ciV->cd();
  // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
  // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
  // array delle  rispettive incertezze
  TGraphErrors *giV = new TGraphErrors(nmisure,V,i,sV,si);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV->SetMarkerSize(0.6);
  giV->SetMarkerStyle(21);
  // Facile, titolo del grafico
  giV->SetTitle("i(V)");
  // Titoli degli assi
  giV->GetXaxis()->SetTitle("V [V]");
  giV->GetYaxis()->SetTitle("i [mA]");
  // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
  // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
  // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
  giV->Draw("AP");
  // ----------------------------------------------------------------- //



  // --------------------- Grafico P(R) ------------------------------ //
  TCanvas *cPR = new TCanvas("cPR","P(R)",200,10,600,400);
  cPR->SetFillColor(0);
  cPR->cd();
  TGraphErrors *gPR = new TGraphErrors(nmisure,R,P,sR,sP);
  gPR->SetMarkerSize(0.6);
  gPR->SetMarkerStyle(21);
  gPR->SetTitle("P(R)");
  gPR->GetXaxis()->SetTitle("R [#Omega]");
  gPR->GetYaxis()->SetTitle("P [mW]");
  gPR->Draw("AP");
  // ----------------------------------------------------------------- //
  // --------------------- Grafico R(V) ------------------------------ /
  TCanvas *cRV = new TCanvas("cRV","R(V)",200,10,600,400);
  cRV->SetFillColor(0);
  cRV->cd();
  TGraphErrors *gRV = new TGraphErrors(nmisure,V,R,sV,sR);
  gRV->SetMarkerSize(0.6);
  gRV->SetMarkerStyle(21);
  gRV->SetTitle("R(V)");
  gRV->GetXaxis()->SetTitle("V [Volt]");
  gRV->GetYaxis()->SetTitle("R [#Omega]");
  gRV->Draw("AP");
  // ----------------------------------------------------------------- //

  cout << "\n\n --- Ipotesi  P=[0]*pow(x + [1],[2]) --- \n" <<endl;
  TF1 *funz1 = new TF1("funz1","[0]*pow(x + [1],[2])",35,125);
  funz1->SetParameter(0,pow(10,-7));
  funz1->SetParameter(1,0);
  funz1->SetParameter(2,4);
  funz1->SetParLimits(0,0,1);
  funz1->SetParLimits(1,-1e3,0);
  funz1->SetLineColor(4);
  gPR->Fit(funz1,"RM+");
  cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
  
  //cout << "\n\n --- Relazione tra i e V---" <<endl;
  //cout << "provo con una funzione del tipo [0]*pow(V,([1] - 1)/([1] + 1))" << endl;
  //TF1 *funz5 = new TF1("funz5","[0]*pow(x,([1] - 1)/([1] + 1))",0.5,12);
  //funz5->SetLineColor(3);
  //giV->Fit(funz5,"R+");
  //cout<< "Chi^2:" << funz5->GetChisquare() <<",number of Dof: "<< funz5->GetNDF() << " (Probability: " << funz5->GetProb() <<")." <<endl;
  //cout << "--------------------------------------------------------------------------------------------------------" << endl;

  //Provare a fare fit a P(R) con polinomiale di ordine 4.
  // cout << "\n\n --- Ipotesi P=[0]*R^4 + [1]*R^3 + [2]*R^2 + [3]*R +[4] --- \n" <<endl;
  //TF1 *funz2 = new TF1("funz2","[0]*pow(x,4) + [1]*pow(x,3) + [2]*pow(x,2) + [3]*x +[4]",0,130);
  //funz2->SetLineColor(6);
  //gPR->Fit(funz2,"RM+");
  //cout<< "Chi^2:" << funz2->GetChisquare() <<",number of Dof: "<< funz2->GetNDF() << " (Probability: " << funz2->GetProb() <<")." <<endl;
  //cout << "--------------------------------------------------------------------------------------------------------" << endl;

  // Provare a fare fit a P(R) con funzione quartica: funz3 = [0]*pow(x,4)
  //cout<< "\n\n --- Ipotesi funz3 = [0]*pow(x,4) --- \n" <<endl;
  //TF1 *funz3 = new TF1("funz3","[0]*pow(x,4)",35,130);
  //funz3->SetLineColor(3);
  //gPR->Fit(funz3,"RM+");
  //cout<< "Chi^2:" << funz3->GetChisquare() <<",number of Dof: "<< funz3->GetNDF() << " (Probability: " << funz3->GetProb() <<")." <<endl;
  //cout << "--------------------------------------------------------------------------------------------------------" << endl;
 
  //cout<< "provo ad aggiungere una b, quindi funz4=[0]*pow(x-[1],4) e vedo che valore di b ottengo" << endl;
  //TF1 *funz4 = new TF1("funz4","[0]*pow(x-[1],4)",35,130);
  //funz4->SetLineColor(41);
  //gPR->Fit(funz4,"RM+");
  //cout<< "Chi^2:" << funz4->GetChisquare() <<",number of Dof: "<< funz4->GetNDF() << " (Probability: " << funz4->GetProb() <<")." <<endl;
  //cout<< "--------------------------------------------------------------------------------------------------------" << endl;
  
  // cout<< "abbiamo ricavato un valore di q, ora procediamo a calcolarlo in maniera diversa per provare che i due valori ottenuti risultino compatibili" << endl;
  //cout << "provo con una funzione del tipo P=[0]*pow(R,[1])" << endl;
  //TF1 *funz6 = new TF1("funz6","[0]*pow(x,[1])",25,130);
  //funz6->SetLineColor(55);
  //gPR->Fit(funz6,"R+");
  //cout<< "Chi^2:" << funz6->GetChisquare() <<",number of Dof: "<< funz6->GetNDF() << " (Probability: " << funz6->GetProb() <<")." <<endl;
  //cout<< "--------------------------------------------------------------------------------------------------------" << endl;

  
}

