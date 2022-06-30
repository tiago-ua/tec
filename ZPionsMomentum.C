void ZPionsMomentum(TString nome){
	
	TFile * ficheiro= new TFile(nome,"READ");
	TString novoNome=nome;
	novoNome.ReplaceAll("AmberTarget_Run","Analise");
	TFile * ficheiroGravar= new TFile(novoNome,"RECREATE");
	TTree * dados= (TTree*)  ficheiro -> Get("tracksData");
	
	Int_t nBins=1000;
	Double_t minBin=-50;
	Double_t maxBin=250;
	Int_t nHistos=2;
	
	TH1D* PionsMomentum[nHistos];
	//TCanvas *canvas[nHistos];
	TString branchName ="pZ_GeV";
	//TString canvasName;
	TString histoName;
	

	auto c4 = new TCanvas("Distribuicao do momento na componente Z para pioes primarios e secundarios", "Distribuicao do momento na componente Z para pioes primarios e secundarios", 600,500);
	THStack *hs = new THStack("hs","Distribuicao do momento na componente Z para pioes primarios e secundarios");
	TLegend *leg = new TLegend(0.5752508,0.6680672,0.8762542,0.8781513);
	
	for (Int_t i=0; i<nHistos; i++){
		TString cut;
		if (i==0){
			histoName="Pioes Primarios";
			cut=branchName+">0 && (IsPrimary == 1) ";
		}
		else if (i==1) {
			histoName="Pioes Secundarios";
			cut=branchName+">0 && (IsPrimary != 1) ";
		} 
		PionsMomentum[i] = new TH1D(histoName,histoName,nBins,minBin,maxBin);
		PionsMomentum[i]->SetLineColor(i+1);
		PionsMomentum[i]->SetFillStyle(4050);		
		dados->Draw(branchName+">>"+histoName,cut);
		PionsMomentum[i] -> SetTitle(histoName);
		PionsMomentum[i] -> Write();
		hs->Add(PionsMomentum[i]);
		hs->Add(PionsMomentum[i]);
		leg->AddEntry(histoName);
	}
			
	hs->Draw("Nostack");
	leg->Draw();

}
