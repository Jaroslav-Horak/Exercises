#include <iostream>
#include <cmath>
#include <ctime> 

double mez1(int nl, double b);
double mez2(int nl, double b);
double mez3(int nl, double b);
double poiss(double bp, short np);

using namespace std;
using namespace TMath;

void eff()
{		
	//deklarace 	
	int n = 500;
	clock_t start, end;
	double time_taken;
	double x[n], y1[n], y2[n], y3[n], a1[n], a2[n], a3[n];
	
	//x pole
	for (int i = 0; i < n; i++)
	{
		x[i] = 1.0*i;
	} 

	//metoda 1
	for (int i = 0; i < n; i++)
	{
		start = clock();
		a1[i] = mez1(x[i], 250);
		end = clock();
		time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		y1[i] = time_taken;
	}

	//metoda 2
	for (int i = 0; i < n; i++)
	{
		start = clock();
		a2[i] =  mez2(x[i], 250);
		end = clock();
		time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		y2[i] = time_taken;
	}

	
	//metoda 3
	for (int i = 0; i < n; i++)
	{
		start = clock();
		a3[i] = mez3(x[i], 250);
		end = clock();
		time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		y3[i] = time_taken;
	}
	
	//vykreslit
	TCanvas *c1 = new TCanvas("c1","Graph",200,10,700,500);
	/*
	TGraph *gr1 = new TGraph(n,x,y1);
	TGraph *gr2 = new TGraph(n,x,y2);
	TGraph *gr3 = new TGraph(n,x,y3);
	*/
	TGraph *gr1 = new TGraph(n,x,a1);
	TGraph *gr2 = new TGraph(n,x,a2);
	TGraph *gr3 = new TGraph(n,x,a3);
	
	TMultiGraph *mg = new TMultiGraph();
	TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
	leg->AddEntry(gr1, "eff");
	leg->AddEntry(gr2, "slow");
	leg->AddEntry(gr3, "root");
	gr1->SetLineColor(2);
	gr2->SetLineColor(3);
	gr3->SetLineColor(4);
	gr1->SetLineWidth(3);
	gr2->SetLineWidth(3);
	gr3->SetLineWidth(3);
	mg->Add(gr1);
	mg->Add(gr2);
	mg->Add(gr3);
	mg->GetXaxis()->SetTitle("n");
	mg->GetYaxis()->SetTitle("T[us]");
	mg->Draw("AL");
	leg->Draw();
	c1->GetFrame()->SetBorderSize(12);
	c1->Modified();

	//vykreslit
	TCanvas *c10 = new TCanvas("c10","Graph",200,10,700,500);
	
	TGraph *gr10 = new TGraph(n,x,y1);
	TGraph *gr20 = new TGraph(n,x,y2);
	TGraph *gr30 = new TGraph(n,x,y3);
	/*
	TGraph *gr1 = new TGraph(n,x,a1);
	TGraph *gr2 = new TGraph(n,x,a2);
	TGraph *gr3 = new TGraph(n,x,a3);
	*/
	TMultiGraph *mg0 = new TMultiGraph();
	TLegend *leg0 = new TLegend(0.1,0.7,0.48,0.9);
	leg0->AddEntry(gr1, "eff");
	leg0->AddEntry(gr2, "slow");
	leg0->AddEntry(gr3, "root");
	gr10->SetLineColor(2);
	gr20->SetLineColor(3);
	gr30->SetLineColor(4);
	gr10->SetLineWidth(3);
	gr20->SetLineWidth(3);
	gr30->SetLineWidth(3);
	mg0->Add(gr10);
	mg0->Add(gr20);
	mg0->Add(gr30);
	mg0->GetXaxis()->SetTitle("n");
	mg0->GetYaxis()->SetTitle("T[us]");
	mg0->Draw("AL");
	leg0->Draw();
	c10->GetFrame()->SetBorderSize(12);
	c10->Modified();
} 


//metoda 1
double mez1(int nl, double b)	
{		
	double poiss=exp(-b);
	//poiss = exp(-b);
	double sum = 0.0;
	for (int n = 1; n<nl+1; n++)
	{
		sum += poiss;
		poiss *= (b/n);
	}
	return sum;
}

//metoda 2
double mez2(int nl,double b)	
{
	double sum = 0.0;
	short n = 0;
	for (int n = 0; n<nl;n++)
	{
		sum+=poiss(b, n);
	}
	return sum;
}

//metoda 3
double mez3(int nl, double b)	
{
	long double sum = 0.0;
	short n = 0;
	for (int n = 0; n<nl;n++)
	{
		sum+=PoissonI(n, b);
	}
	return sum;
}

//poissonovo rozdeleni - pro metodu 2
double poiss(double bp, short np)
{
	if (np > 0) return (bp/np)*poiss(bp, np-1);
	else return exp(-bp);  
}
