#include <iostream>           // ci serve per stampare a video il testo
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video 
#include <TImage.h>           // ci serve per le immagini
#include <TPaveStats.h>       // ci serve per la tabella con i valori
#include <TString.h>
using namespace std;
ifstream inFile;
ofstream outFile;
///////////Leggimi////////////
//Analisi dati per la velocità di pompaggio (Gruppo 7):
//Pellegrino Marco, Pugliese Vanna, Zugravel Stefan Cristi
//
//Per far partire l'analisi dati digitare: root Vuoto.cpp > logVuoto.txt


//int NdataFile      = 859;       // Numero totale di misure del file
//int StartData1     = 96;        // Dove cominciano le misure della prima presa dati
//int EndData1       = 444;       // Dove finiscono le misure della prima presa dati
//int StartData2     = 512;       // Dove cominciano le misure della seconda presa dati
//int EndData2       = 823;       // Dove finiscono le misure della seconda presa dati
//double plateau1    = 1.0;       // [mbar] Plateau della prima misura
//double plateau2    = 1.0;       // [mbar] Plateau della seconda perdita
//double h           = 0.400;     // [m] Lunghezza del condotto
double Pi            = 3.141592;  // PiGrego
double eh            = 0.01;      // [m] 1cm di errore Errore sulla lunghezza del condotto
double d             = 0.150;     // [m] Diametro del condotto
double ed            = 0.001;     // [m] 1 mm di errore Errore sul diametro del condotto
double StartFitValueX= 10000;     // [ms] Da vove parte il fit dandogli come estremi dei tempi
double EndFitValueX  = 60000;     // [ms] Dove finisce il fit dandogli come estremi dei tempi
double StartFitY     = 4.0;       // log(P-Po) Da vove parte il fit dando come estremi una pressione
double EndFitY       = 0.0;       // log(P-Po) Dove finiche il fit dando come estremi una pressione

double StartFitValueY; // 
double EndFitValueY;   //
int NdataFile;         // Numero totale di misure del file
int StartData1;        // Dove cominciano le misure della prima presa dati
int EndData1;          // Dove finiscono le misure della prima presa dati
int StartData2;        // Dove cominciano le misure della seconda presa dati
int EndData2;          // Dove finiscono le misure della seconda presa dati
double plateau1;       // [mbar] Plateau della prima misura
double plateau2;       // [mbar] Plateau della seconda perdita
double h;              // [m] Lunghezza del condotto
	////////////////////////////////////////////////////////////////////////
	//Questo serve per la creazione del grafico lineare
	//Tranne quanto tutti i valori dovrebero essere 13
	int                  value;
	int                Counter=0;
	int        CilindersNumber=13;
	double        PumpingSpeed[13];
	double       ePumpingSpeed[13];
	double              Volume[13];
	double             eVolume[13];
	double  CharacteristicTime[13];
	double eCharacteristicTime[13];


int GraphAndFit(const char FilePath[32],const char ImageName1[32],const char ImageName2[32],const char CanvasName1[32],const char CanvasName2[32],int NdataFile,int StartData1,int EndData1,int StartData2,int EndData2,double plateau1,double plateau2,double h){
	
	//TString FilePath("vacuum_new/vol_2.txt");       // Path per il file con i dati
	//TString ImageName1("vol_2new_parte1.png");      // Nome immagine misura 1
	//TString ImageName2("vol_2new_parte2.png");      // Nome immagine misura 2
	//TString CanvasName1("volume 2 measuremet 1");   // Nome per il canvas 1
	//TString CanvasName2("volume 2 measuremet 2");   // Nome per il canvas 2
	//Inizializzazione di tutti i parametri.
	//int NdataFile     = 859;       // Numero totale di misure del file
	//int StartData1    = 96;        // Dove cominciano le misure della prima presa dati
	//int EndData1      = 444;       // Dove finiscono le misure della prima presa dati
	//int StartData2    = 512;       // Dove cominciano le misure della seconda presa dati
	//int EndData2      = 823;       // Dove finiscono le misure della seconda presa dati
	//double plateau1   = 1.0;       // [mbar] Plateau della prima misura
	//double plateau2   = 1.0;       // [mbar] Plateau della seconda perdita
	//double h          = 0.400;     // [m] Lunghezza del condotto
	
	double V          = ((d/2)*(d/2)*Pi*h);// [m^3] Volume del condotto
	double eV         =sqrt( (Pi*Pi/4)*(pow(eh*d*d/4,2) + pow(h*d*ed,2)) ); // [m^3] Errore sul volume
	double ErrorTime  = 10;        // [ms] Errore da assegnare al tempo
	double ErrorForLog= 0.05;      // [Log(mbar)]Errore da assegnare al logaritmo della pressione
	double PumpingSpeed1;          // Velocità di pompaggio nel caso 1
	double PumpingSpeed2;          // Velocità di pompaggio nel caso 2
	double ePumpingSpeed1;         // Errore della velocità di pompaggio nel caso 1
	double ePumpingSpeed2;         // Errore della velocità di pompaggio nel caso 2
	int Ndata1 = EndData1 - StartData1; // Questo è il numero di dati che si usa per il grafico 1
	int Ndata2 = EndData2 - StartData2; // Questo è il numero di dati che si usa per il grafico 2
   double P[NdataFile];           // Array con tutti i valori di pressione del file di dati
   double errP[NdataFile];        // Incertezza sulla pressione, questo valore ancora non viene usato
	double t[NdataFile];           // Array con tutti i valori di tempo del file di dati
	double Temp[NdataFile];        // E' un trash array con le ipotetiche temperature del file di dati
	double Pressure1[Ndata1];      // Array per le pressioni del fit 1
	double Time1[Ndata1];          // Array per i tempi del fit 1
	double Pressure2[Ndata2];      // Array per le pressioni del fit 2
	double Time2[Ndata2];          // Array per i tempi del fit 2
	double errt1[Ndata1];          // Array con le incertezze dei tempi per il fit 1
	double errt2[Ndata2];          // Array con le incertezze dei tempi per il fit 2
	double logP1[Ndata1];          // Array in cui vengono inseriti i dati da mettere su grafico per il fit 1
	double logP2[Ndata2];          // Array in cui vengono inseriti i dati da mettere su grafico per il fit 2
	double errlogP1[Ndata1];       // Array per l'errore dei dati precedenti
	double errlogP2[Ndata2];       // Array per l'errore dei dati precedenti
	double TimeStart1;             // Questo serve per far partire il tempo da zero per il fit1
	double TimeStart2;             // Questo serve per far partire il tempo da zero per il fit2
	double Z;                      // Valore per il test Z delle due misure
	double AvgPumpingSpeed;        // Valore per il valor medio del pompaggio
	double eAvgPumpingSpeed;       // Errore per il valor medio del pompaggio
	int index1;                    // Questo è un indice
	int index2;                    // Anche questo è un indice

	
	//Qua si apre il file, si mettono i dati in un array e poi lo si chiude.
	inFile.open(FilePath);
   if(!inFile){                                 
      cout << "---ATTENZIONE!!! Non c'è nessun file!!!---"<< endl;
   }
   for(int i=0;i<NdataFile;i++){
      inFile >> t[i] >> P[i] >> Temp[i];   
   }
	inFile.close();

	cout <<"Ora si lavora sul file: "<<FilePath<<endl;
	cout <<"-----------------------------------------------------"<<endl;
	
	//Scegliamo i punti da cui far partire il tempo per le due misure.
	TimeStart1 = t[StartData1];
	TimeStart2 = t[StartData2];
	
	for(int i=0;i<NdataFile;i++){
		index1 = i -StartData1;
		index2 = i -StartData2;
		
      //cout<<"Nfile: "<<i<<"\t Tempo= "<<t[i]<<"\t  Pressione= "<<P[i] <<endl;
		//Mettiamo ogni dato nei rispettivi array
		if(i>=StartData1 && i<EndData1){ 
			Pressure1[index1] = P[i];
			Time1[index1]     = t[i] - TimeStart1;
			logP1[index1]     = log(Pressure1[index1]-plateau1);
			errt1[index1]     = ErrorTime  ;
			errlogP1[index1]  = ErrorForLog;
		}else if(i>=StartData2 && i<EndData2){
			Pressure2[index2] = P[i];
			Time2[index2]     = t[i] - TimeStart2;
			logP2[index2]     = log(Pressure2[index2]-plateau2);
			errt2[index2]     = ErrorTime  ;
			errlogP2[index2]  = ErrorForLog;
		}
		
   }
	
	StartFitValueY = 0;
	EndFitValueY   = 0;
	//Controllo manuale del corretto inserimento dei dati nei loro rispettivi array.
	//Posizionamento dei limiti dei fit con il metodo delle ordinate.
	for(int i=0;i<Ndata1;i++){
		//cout<<"N1: "<<i<<"\t Time: "<<Time1[i]<<" +- "<<errt1[i]<<"\t LogP: "<<logP1[i]<<" +- "<<errlogP1[i]<<endl;	
		if( logP1[i] > EndFitY ){
			EndFitValueY = Time1[i];
		}	
		if( logP1[Ndata1 - i] < StartFitY ){
			StartFitValueY = Time1[Ndata1 - i];
		}
	}
	for(int i=0;i<Ndata2;i++){
		//cout<<"N2: "<<i<<"\t Time: "<<Time2[i]<<" +- "<<errt2[i]<<"\t LogP: "<<logP2[i]<<" +- "<<errlogP2[i]<<endl; 
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////
	//Da qua facciamo i fit ed è tutto come sempre.
	TCanvas *v1 = new TCanvas("v1", "misura 1", 5, 5, 1920, 1080);    
   v1->SetFillColor(0);
   v1->cd();
	
	TGraphErrors *gv1 = new TGraphErrors(Ndata1,Time1,logP1,errt1,errlogP1);
	gv1->SetMarkerSize(5);
	gv1->SetTitle(CanvasName1);
	gv1->GetXaxis()->SetTitle("Time [ms]");
	gv1->GetYaxis()->SetTitle("Log(P-P_0) ");
	gv1->Draw("AP");
	
   TF1 *funz1 = new TF1("funz1","[0]*x + [1]",StartFitValueY,EndFitValueY);
   funz1->SetParNames("slope","const");
   //gStyle->SetOptFit(1111);
   gv1->Fit(funz1,"RM+");
   cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;

	///////////////////////////////////////////////////////////////////////////////////////////
	TCanvas *v2 = new TCanvas("v2", "misura 2", 5, 5, 1920, 1080);    
   v2->SetFillColor(0);
   v2->cd();
	
	TGraphErrors *gv2 = new TGraphErrors(Ndata2,Time2,logP2,errt2,errlogP2);
	gv2->SetMarkerSize(5);
	gv2->SetTitle(CanvasName2);
	gv2->GetXaxis()->SetTitle("Time [ms]");
	gv2->GetYaxis()->SetTitle("Log(P-P_0) ");
	gv2->Draw("AP");
	
   TF1 *funz2 = new TF1("funz2","[0]*x + [1]",StartFitValueY,EndFitValueY);
   funz2->SetParNames("slope","const");
   //gStyle->SetOptFit(1111);
   gv2->Fit(funz2,"RM+");
   cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;
	///////////////////////////////////////////////////////////////////////////////////////////

	//Calcolo della velocità di pompaggio e del suo bravo errore.
	PumpingSpeed1 = -1*funz1->GetParameter(0) * 1000 * 3600 * V;    // m3/hours
	PumpingSpeed2 = -1*funz2->GetParameter(0) * 1000 * 3600 * V;    // m3/hours
	
	ePumpingSpeed1 = sqrt(pow(funz1->GetParameter(0)*1000*3600*eV,2) + pow(V*funz1->GetParError(0)*1000*3600,2));// m3/hours
	ePumpingSpeed2 = sqrt(pow(funz2->GetParameter(0)*1000*3600*eV,2) + pow(V*funz2->GetParError(0)*1000*3600,2));// m3/hours
	
	//Calcolo del test Z fra le due misure
	Z = (abs(PumpingSpeed1-PumpingSpeed2))/(sqrt(pow(ePumpingSpeed1,2) + pow(ePumpingSpeed2,2)));
	
	//Calcolo valor medio del pompaggio
	AvgPumpingSpeed = (PumpingSpeed1 + PumpingSpeed2)/2;
	eAvgPumpingSpeed = (sqrt(pow(ePumpingSpeed1,2) + pow(ePumpingSpeed2,2)))/2;

	cout <<"-----------------------------------------------------"<<endl;
	cout <<"Numero misure grafico1: "<<Ndata1<<endl;
	cout <<"Numero misure grafico2: "<<Ndata2<<endl;
	cout <<"-----------------------------------------------------"<<endl;
   cout <<"   Costante di tempo 1: "<<-1*funz1->GetParameter(0)<<" +- "<<funz1->GetParError(0)<<" ms^-1" <<endl;
	cout <<"   Costante di tempo 2: "<<-1*funz2->GetParameter(0)<<" +- "<<funz2->GetParError(0)<<" ms^-1" <<endl;
	cout <<"                Volume: "<< V <<" +- "<< eV << " m3" << endl;
	cout <<"velocità di pompaggio1: "<< PumpingSpeed1 <<" +- "<<ePumpingSpeed1<< " m3/hours" <<endl;
	cout <<"velocità di pompaggio2: "<< PumpingSpeed2 <<" +- "<<ePumpingSpeed2<< " m3/hours" <<endl;
	cout <<"-----------------------------------------------------"<<endl;
	cout <<"   Test Z fra i valori: "<<Z<<endl;
	cout <<" Valor medio pompaggio: "<<AvgPumpingSpeed<<" +- "<<eAvgPumpingSpeed<< " m3/hours\n \n \n \n" <<endl;

	//Creazione delle immagini, per i nomi usa le stringhe di inizio file.
	TImage *img1 = TImage::Create();
	img1->FromPad(v1);
	img1->WriteImage(ImageName1);
	
	TImage *img2 = TImage::Create();
	img2->FromPad(v2);
	img2->WriteImage(ImageName2);
	
	//cout <<"-----------------------------------------------------\n \n \n \n "<<endl;
			 PumpingSpeed[Counter] = AvgPumpingSpeed;
			ePumpingSpeed[Counter] = eAvgPumpingSpeed;
	  				 Volume[Counter] = V;
					eVolume[Counter] = eV;
	 CharacteristicTime[Counter] = 1/((((-1*funz1->GetParameter(0)) + (-1*funz2->GetParameter(0)))/2)*1000);
	eCharacteristicTime[Counter] = ((funz1->GetParError(0) + funz2->GetParError(0))/2)/(1000 * pow((((-1*funz1->GetParameter(0)) + (-1*funz2->GetParameter(0)))/2),2));
								Counter = Counter + 1 ;
	
	return 0;
}

int DoLinearFit(){
	
	//Creo il canvas
   TCanvas *ciV = new TCanvas("Pumping Speed", "Pumping Speed", 5, 5, 1920, 1080);    
   ciV->SetFillColor(0);
   ciV->cd();
   //Creo il grafico usando i nostri vettori
   TGraphErrors *giV = new TGraphErrors(CilindersNumber, Volume, CharacteristicTime, eVolume, eCharacteristicTime);
   giV->SetMarkerSize(1);
   giV->SetMarkerStyle(22);
   giV->SetTitle("Pumping Speed Linearity");
   giV->GetXaxis()->SetTitle("Volume [m^3]");
   giV->GetYaxis()->SetTitle("Characteristic Time [s] ");
   giV->Draw("AP");
   //cout << "\n\n ----  FACCIO IL FIT  ---- \n" << endl;
   TF1 *funz3 = new TF1("funz3", "[0]*x +[1] ", 0, 0.05);
	funz3->SetParNames("slope","const");
   gStyle->SetOptFit(1111);
	gStyle->SetStatY(0.4);
   funz3->SetLineColor(2);
   giV->Fit(funz3, "R+");
   cout << "Chi^2:" << funz3->GetChisquare() << ", number of DoF: " << funz3->GetNDF() << " (Probability: " << funz3->GetProb() << ")." << endl;

	TImage *img3 = TImage::Create();
	img3->FromPad(ciV);
	img3->WriteImage("Img/PumpingSpeedLinearity.png");
	
	cout <<"\n \n \n \n-----------------------------------------------------"<<endl;
	double PumpingSpeed3 = (1/funz3->GetParameter(0))*3600;
	double ePumpingSpeed3 = (funz3->GetParError(0)/pow(funz3->GetParameter(0),2)) * 3600;
	double ParasiticVolume = 1000*(funz3->GetParameter(1) * PumpingSpeed3)/3600 ; //(s/3600)*m3/hours [m3]
	double eParasiticVolume = 1000*sqrt(pow((funz3->GetParError(1)/3600)*PumpingSpeed3,2) + pow((funz3->GetParameter(1)/3600)*ePumpingSpeed3,2));
	//////////////////////////////////////////////////////////////////////////////////
	//Ora si procede alla misura della velocità di pompaggio con il secondo metodo.
	cout<<"Knowing that 1/S=B=Slope we can calculate S"<<endl;
	cout<<"Pumping Speed: "<< PumpingSpeed3 <<" +- "<< ePumpingSpeed3 <<" m^3/h \n"<<endl;
	cout<<"Now we cal calculate the parasitic Volume"<<endl;
	cout<<"V_Parasitic: "<<ParasiticVolume<<" +- "<<eParasiticVolume<<" liters"<<endl;
	cout<<"-----------------------------------------------------"<<endl;
	
	return 0;
}

//Volume 1     ->h=0.400m
//Volume 2     ->h=0.400m
//Volume 3     ->h=0.450m
//Volume 4     ->h=0.650m
//Volume 12    ->h=0.806m
//Volume 23    ->h=0.855m
//Volume 24    ->h=1.056m
//Volume 34    ->h=1.105m
//Volume 123   ->h=1.259m
//Volume 124   ->h=1.460m
//Volume 234   ->h=1.510m
//Volume 1234  ->h=1.915m
//Volume 12345 ->h=2.476m

void Vuoto(){
	
	
	//Volume 1   [ 1]-Path dei dati--Nome Immagine 1--Nome Immagine 2--Nome canvas 1--Nome canvas 2--NdataFile--StartData1--EndData1--StartData2--EndData2--plateau1--plateau2--h         
	value=GraphAndFit("Data/vol_1.txt","Img/vol_1_1.png","Img/vol_1_2.png","volume 1 measuremet 1","volume 1 measuremet 2",1413,408,696,835,1131,1.0,1.0,0.4);
	//Volume 2   [ 2]-
	value=GraphAndFit("Data/vol_2.txt","Img/vol_2_1.png","Img/vol_2_2.png","volume 2 measuremet 1","volume 2 measuremet 2",859,98,398,514,819,1.15,1.04,0.4);
	//Volume 3   [ 3]-
	value=GraphAndFit("Data/vol_3.txt","Img/vol_3_1.png","Img/vol_3_2.png","volume 3 measuremet 1","volume 3 measuremet 2",898,35,345,505,820,1.0,1.0,0.45);
	//Volume 4   [ 4]-
	value=GraphAndFit("Data/vol_4.txt","Img/vol_4_1.png","Img/vol_4_2.png","volume 4 measuremet 1","volume 4 measuremet 2",1496,159,586,763,1184,1.25,1.11,0.65);
	//Volume 12  [ 5]-
	value=GraphAndFit("Data/vol_12.txt","Img/vol_12_1.png","Img/vol_12_2.png","volume 1+2 measuremet 1","volume 1+2 measuremet 2",2163,689,1240,1410,1957,1.34,1.19,0.806);
	//Volume 23  [ 6]-
	value=GraphAndFit("Data/vol_23.txt","Img/vol_23_1.png","Img/vol_23_2.png","volume 2+3 measuremet 1","volume 2+3 measuremet 2",1821,358,949,1070,1646,1.32,1.16,0.855);
	//Volume 24  [ 7]-
	value=GraphAndFit("Data/vol_24.txt","Img/vol_24_1.png","Img/vol_24_2.png","volume 2+4 measuremet 1","volume 2+4 measuremet 2",2170,257,950,1108,1800,1.34,1.16,1.056);
	//Volume 34  [ 8]-
	value=GraphAndFit("Data/vol_34.txt","Img/vol_34_1.png","Img/vol_34_2.png","volume 3+4 measuremet 1","volume 3+4 measuremet 2",2175,291,1009,1213,1904,1.35,1.16,1.105);
	//Volume 123 [ 9]-
	value=GraphAndFit("Data/vol_123.txt","Img/vol_123_1.png","Img/vol_123_2.png","volume 1+2+3 measuremet 1","volume 1+2+3 measuremet 2",2652,266,1085,1617,2420,1.43,1.20,1.259);
	//Volume 124 [10]-
	value=GraphAndFit("Data/vol_124.txt","Img/vol_124_1.png","Img/vol_124_2.png","volume 1+2+4 measuremet 1","volume 1+2+4 measuremet 2",2577,147,1070,1248,2170,1.30,1.18,1.460);
	//Volume 234 [11]-
	value=GraphAndFit("Data/vol_234.txt","Img/vol_234_1.png","Img/vol_234_2.png","volume 2+3+4 measuremet 1","volume 2+3+4 measuremet 2",3509,962,1950,2140,3100,1.38,1.18,1.510);
	//Volume 1234[12]-
	value=GraphAndFit("Data/vol_1234.txt","Img/vol_1234_1.png","Img/vol_1234_2.png","volume 1+2+3+4 measuremet 1","volume 1+2+3+4 measuremet 2",5035,2149,3413,3694,4862,1.51,1.27,1.915);
	//Volume 12345[13]
	value=GraphAndFit("Data/vol_12345.txt","Img/vol_12345_1.png","Img/vol_12345_2.png","volume 12345 measuremet 1","volume 1+2+3+4+5 measuremet 2",4043,243,1766,2481,4008,1.47,1.38,2.476);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	cout <<"-----------------------------------------------------"<<endl;
	for(int i=0;i<CilindersNumber;i++){
		cout<<"N: "<<i<<"\t PumpingSpeed: "<<PumpingSpeed[i]<<" +- "<<ePumpingSpeed[i]<<" m^3/h "<<endl;
	}
	cout <<"-----------------------------------------------------\n \n \n \n "<<endl;
	cout <<"-----------------------------------------------------"<<endl;
	for(int i=0;i<CilindersNumber;i++){
		cout<<"N: "<<i<<"\t Volume: "<<Volume[i]<<" +- "<<eVolume[i]<<" m^3 "<<endl;
	}
	cout <<"-----------------------------------------------------\n \n \n \n "<<endl;
	cout <<"-----------------------------------------------------"<<endl;
	for(int i=0;i<CilindersNumber;i++){
		cout<<"N: "<<i<<"\t CharacteristicTime: "<<CharacteristicTime[i]<<" +- "<<eCharacteristicTime[i]<<" s "<<endl;
	}
	cout <<"-----------------------------------------------------\n \n \n \n "<<endl;

	DoLinearFit();
}