void ZMomentum(TString nome){
	
	TFile * ficheiro= new TFile(nome,"READ");
	TString novoNome=nome;
	novoNome.ReplaceAll("AmberTarget_Run","Analise");
	TFile * ficheiroGravar= new TFile(novoNome,"RECREATE");
	TTree * dados= (TTree*)  ficheiro -> Get("tracksData");
	
	Int_t nBins=200;
	Double_t minBin=0.0;
	Double_t maxBin=210;
	Int_t nHistos=3;
	//Double_t pz;
	
	TH1D* Momentum[nHistos];
	TCanvas *canvas[nHistos];
	TString branchName ="pZ_GeV";
	TString canvasName;
	TString histoName;
	
	//Muões -13 13
	//Piões -211 21
	THStack *hs = new THStack("hs","Stacked 1D histograms");
	
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
			canvasName="canvas"+TString::Itoa(i,10);
			canvas[i]= new TCanvas(canvasName,canvasName);	
			dados->Draw(branchName+">>"+histoName,cut);
			//dados->Draw(branchName+">>"+histoName,branchName+">0"); //Funciona
			Momentum[i] -> SetTitle(histoName);
			Momentum[i] -> Write();
			hs->Add(Momentum[i]);
			}

}
