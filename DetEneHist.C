void DetEneHist(TString nome) {

	TFile * ficheiro= new TFile(nome,"READ");

	TString novoNome=nome;
	novoNome.ReplaceAll("AmberTarget_Run","Analise");
	TFile * ficheiroGravar= new TFile(novoNome,"RECREATE");



	TTree * dados= (TTree*)  ficheiro -> Get("edep_Per_Event");
	
	
	
	
	
	
	Double_t detector0;
	Double_t detector1;
	Double_t detector2;
	Double_t detector3;
	Double_t Soma;
	
	dados->SetBranchAddress("detector0",&detector0);
	dados->SetBranchAddress("detector1",&detector1);
	dados->SetBranchAddress("detector2",&detector2);
	dados->SetBranchAddress("detector3",&detector3);
	
	Long64_t  N = dados-> GetEntries();
	TTree* newTree = new TTree("newTree","newTree");
	newTree -> Branch("Soma", &Soma, "Soma /D");
	
	for (Int_t i=0; i< N; i++){
		dados->GetEntry(i);
		Soma=detector0+detector1+detector2+detector3;
		newTree -> Fill();
		
	} 

	newTree -> Write();
	
}
