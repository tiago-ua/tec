void ZMomentum(TString nome){
	
	TFile * ficheiro= new TFile(nome,"READ");
	TString novoNome=nome;
	novoNome.ReplaceAll("AmberTarget_Run","Analise");
	TFile * ficheiroGravar= new TFile(novoNome,"RECREATE");
	TTree * dados= (TTree*)  ficheiro -> Get("tracksData");
	
	Int_t nBins=1000;
	Double_t minBin=-4;
	Double_t maxBin=4;
	Int_t nHistos=3;
	
	TH1D* Momentum[nHistos];
	TCanvas *canvas[nHistos];
	TString branchName ="pZ_GeV";
	TString canvasName;
	TString histoName;
	
	//Muões -13 13
	//Piões -211 21
	
	auto c4 = new TCanvas("Distribuicao do momento na componente Z para muoes e pioes", "Distribuicao do momento na componente Z para muoes e pioes", 600,500);
	THStack *hs = new THStack("hs","Distribuicao do momento na componente Z para muoes e pioes");
	TLegend *leg = new TLegend(0.5752508,0.6680672,0.8762542,0.8781513);
	
	for (Int_t i=0; i<nHistos; i++){
			TString cut;
			if (i==0){
				histoName="Muoes";
				cut=branchName+">0 && (particlePDG == 13 || particlePDG == -13) ";
			}
			else if (i==1) {
				histoName="Pioes";
				cut=branchName+">0 && (particlePDG == 211 || particlePDG == -211) ";
			} 
			else if (i==2) {
				histoName="Outras";
				cut=branchName+">0 && (particlePDG != 13 && particlePDG != -13 && particlePDG != -211 && particlePDG != 211)";
			}
					
			Momentum[i] = new TH1D(histoName,histoName,nBins,minBin,maxBin);
			Momentum[i]->SetLineColor(i+1);
			Momentum[i]->SetFillStyle(4050);
			dados->Draw(branchName+">>"+histoName,cut);
			Momentum[i] -> SetTitle(histoName);
			Momentum[i] -> Write();
			hs->Add(Momentum[i]);
			leg->AddEntry(histoName);
			}
			
	hs->Draw("Nostack");
	leg->Draw();

}
