
void vertex()
{
    TFile * input = TFile::Open("AmberTarget_Run_0.root");
    TFile * output = new TFile("OutputAnalysisVertex.root", "RECREATE");
    TTree * tree = (TTree*)input->Get("hadronicVertex");
    double zPos;
    int eventID, primary;
    tree->SetBranchAddress("eventID", &eventID);
    tree->SetBranchAddress("vertexPosZ_cm", &zPos);
    tree->SetBranchAddress("IsPrimary", &primary);
    int p=0;
    int s=0;
    
    


    Int_t nBins=220;
    Double_t minBin=-550;
    Double_t maxBin=550;

    TH1D * histo[2];

    histo[0] = new TH1D("Histograma Vertex", "Primario",nBins,minBin,maxBin);
    histo[1] = new TH1D("Histograma Vertex", "Secundario",nBins,minBin,maxBin);
    
    int nev = (Int_t)tree->GetEntries();
    for(int i = 0; i<nev; i++)
    {
        tree->GetEntry(i);
        if (primary==1)
        {
            histo[0]->Fill(zPos);
            
        }
        else
        {
            histo[1]->Fill(zPos);
        }    
    }
    histo[0]->Write();
    histo[1]->Write();
    input->Close();
    output->Close();


}

