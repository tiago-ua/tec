#include <stdlib.h>

void soma_de_energia_4_particulas(){
	TFile * ficheiro= new TFile("AmberTarget_Run_0.root","READ");
	TFile * ficheiroGravar= new TFile("Analise.root","RECREATE");
	TTree * dados= (TTree*)  ficheiro -> Get("tracksData");

	Double_t detetor[4];
	Int_t PDG;

	for (Int_t i = 0; i < 4; i++){
		dados->SetBranchAddress("EdepDet" + TString::Itoa(i,10) + "_keV", &detetor[i]);
	}
	dados->SetBranchAddress("particlePDG",&PDG);


	TTree* newTree = new TTree("newTree","newTree");
	Double_t Soma;
	newTree -> Branch("Soma", &Soma, "Soma/D");
	newTree->Branch("PDG",&PDG,"PGD/I");

	Long64_t  N = dados -> GetEntries();
	for (Int_t i=0; i< N; i++){
		dados -> GetEntry(i);
		Soma = detetor[0] + detetor[1] + detetor[2] + detetor[3];
		newTree -> Fill();
	} 
	
	//newTree -> Scan();

	Int_t nBins=500;
    Double_t minBin=1000;
    Double_t maxBin=100000;

    TH1D* histoDetetor[3];
	TString branchName = "Soma";
    THStack *hs = new THStack("hs","Stacked 1D histograms");


	TString histoName = "pioes";
	histoDetetor[0]=new TH1D(histoName, histoName, nBins, minBin, maxBin);
	histoDetetor[0]->SetLineColor(kRed);
	newTree->Draw(branchName+">>"+histoName, "abs(PDG) == 13");
	histoDetetor[0]->Write();
	hs->Add(histoDetetor[0]);

	histoName = "muoes";
	histoDetetor[1]=new TH1D(histoName, histoName, nBins, minBin, maxBin);
	histoDetetor[1]->SetLineColor(kBlue);
	newTree->Draw(branchName+">>"+histoName, "abs(PDG) == 211");
	histoDetetor[1]->Write();
	hs->Add(histoDetetor[1]);

	histoName = "outros";
	histoDetetor[2]=new TH1D(histoName, histoName, nBins, minBin, maxBin);
	histoDetetor[2]->SetLineColor(kGreen);
	newTree->Draw(branchName+">>"+histoName, "abs(PDG) != 211 && abs(PDG)!=13");
	histoDetetor[2]->Write();
	hs->Add(histoDetetor[2]);

	gPad->SetLogy(1);
	hs->SetTitle("Energy deposition for muons, pions and other particles");
	hs->Draw("NoStack");

	auto legend = new TLegend(0.7,0.7,0.9,0.9);
	legend->SetHeader("Particles","C"); // option "C" allows to center the header
	legend->AddEntry(histoDetetor[0],"Muons","l");
	legend->AddEntry(histoDetetor[1],"Pions","l");
	legend->AddEntry(histoDetetor[2],"Other particles","l");
	legend->Draw();

	//newTree -> Write();
}

