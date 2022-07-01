void Tempo() {
	
	TFile *ficheiro=new TFile("AmberTarget_Run_3.root","READ");	
	TFile *ficheiroGravar=new TFile("output.root","RECREATE");
	TTree *dados=(TTree*)ficheiro->Get("Hits");
	
	Int_t nBins=50;
	Double_t minBin=0.0;
	Double_t maxBin=30;

	Int_t nHistos=4;
	TH1D* histoDetetor[nHistos];
	TCanvas *canvas[nHistos];
	TString branchName;
	TString canvasName;
	
	auto c4 = new TCanvas("distribuicao temporal de hits por detetor", "distribuicao temporal de hits por detetor", 600,500);
	
	THStack *hs = new THStack("hs","distribuicao temporal de hits por detetor");
	TLegend *leg = new TLegend(0.5752508,0.6680672,0.8762542,0.8781513);
	 
	
for (Int_t i=0;i<nHistos; i++){

	TString histoName = "histoDetetor"+ TString::Itoa(i,10);
	histoDetetor[i] = new TH1D(histoName, histoName, nBins, minBin, maxBin);
	branchName = "particleHitTime_ns";
	//canvasName="canvas"+TString::Itoa(i,10);
	histoDetetor[i]->SetLineColor(i+1);
	histoDetetor[i]->SetFillStyle(4050);
	//canvas[i]=new TCanvas(canvasName, canvasName);
	dados->Draw(branchName + ">>" + histoName,"(detectorID == " + TString::Itoa(i,10) + ")");
	histoDetetor[i]->SetTitle(histoName);
	histoDetetor[i]->Write();
	hs->Add(histoDetetor[i]);
	leg->AddEntry("histoDetetor" + TString::Itoa(i,10));
	

	
	}
	
hs->Draw("Nostack");
leg->Draw();
}
