void analysis(){
    TFile * input = TFile::Open("AmberTarget_Run_0.root");          //Opening input data
    TFile * output = new TFile("OutputAnalysis.root", "RECREATE");  //Creates output file and recreates it in case the file already exists
    TTree * tree = (TTree*)input->Get("Hits");                      //Getting TTree "Hits" from input file
    double x, y;
    int decID, charge;
    const int nid = 4;                                              //defining number of detectors for cycling
    TH1F * htemp, *htempy;                                          //declaration of temporary histograms
    tree->SetBranchAddress("detectorID", &decID);                   //Addressing Branches to variables in order to get the values when events are selected
    tree->SetBranchAddress("hitPosX_cm", &x);
    tree->SetBranchAddress("hitPosY_cm", &y);
    tree->SetBranchAddress("particleCharge", &charge);
    tree->Draw("hitPosX_cm>>htemp");                                //Drawing Branches hitPosX_cm and hitPosY_cm redirecting them to histograms htemp and htempy
    tree->Draw("hitPosY_cm>>htempy");
    htemp = (TH1F*)gDirectory->Get("htemp");                        //assigning temporary histograms to declared ones in order to be used in the analysis properly
    htempy = (TH1F*)gDirectory->Get("htempy");
    Int_t xmax = htemp->GetXaxis()->GetXmax();                      //Getting bins max/min values and number of bins for PosY and PosX
    Int_t xmin = htemp->GetXaxis()->GetXmin();
    Int_t xbins = htemp->GetXaxis()->GetNbins();
    Int_t ymax = htempy->GetXaxis()->GetXmax();
    Int_t ymin = htempy->GetXaxis()->GetXmin();
    Int_t ybins = htempy->GetXaxis()->GetNbins();
    TH1F * PosX[nid], *PosY[nid], *PosXcharge[nid], *PosXneutral[nid], *PosYcharge[nid], *PosYneutral[nid];  //declaring histograms to be used for the analysis
    for(int id = 0; id < nid; id++){
        PosX[id] = new TH1F(Form("PosXDec%d", id), Form("PosX DecID %d", id),xbins,xmin,xmax);                          //invoking costructors via the new operator for each histogram
        PosXcharge[id] = new TH1F(Form("PosXChargeDec%d", id), Form("PosX Charged DecID %d", id),xbins,xmin,xmax);
        PosXneutral[id] = new TH1F(Form("PosXNeutralDec%d", id), Form("PosX Neutral DecID %d", id),xbins,xmin,xmax);
        PosY[id] = new TH1F(Form("PosYDec%d", id), Form("PosY DecID %d", id),ybins,ymin,ymax);
        PosYcharge[id] = new TH1F(Form("PosYChargeDec%d", id), Form("PosY Charged DecID %d", id),ybins,ymin,ymax);
        PosYneutral[id] = new TH1F(Form("PosYNeutralDec%d", id), Form("PosY Neutral DecID %d", id),ybins,ymin,ymax);
    }
    int nev = (Int_t)tree->GetEntries();                    //Getting number of events in the TTree for cycling
    printf("Number of entries are %d\n",nev);
    for(int i = 0; i<nev; i++){
        tree->GetEntry(i);                                  //Getting the event i, hence values x, y, decID and charge are assigned to the event values
        printf("Filling entry %d\r", i);
        switch(decID){                                      //switch condition to fill properly the histograms for each detector ID
            case 0:
                PosX[0]->Fill(x);
                PosY[0]->Fill(y);
                if(charge==0){                              //checking the charge and filling the appropriate histograms
                    PosXneutral[0]->Fill(x);
                    PosYneutral[0]->Fill(y);    
                }
                else{
                    PosXcharge[0]->Fill(x);
                    PosYcharge[0]->Fill(y);    
                }
                break;
            case 1:
                PosX[1]->Fill(x);
                PosY[1]->Fill(y);
                if(charge==0){
                    PosXneutral[1]->Fill(x);
                    PosYneutral[1]->Fill(y);    
                }
                else{
                    PosXcharge[1]->Fill(x);
                    PosYcharge[1]->Fill(y);    
                }
                break;
            case 2:
                PosX[2]->Fill(x);
                PosY[2]->Fill(y);
                if(charge==0){
                    PosXneutral[2]->Fill(x);
                    PosYneutral[2]->Fill(y);    
                }
                else{
                    PosXcharge[2]->Fill(x);
                    PosYcharge[2]->Fill(y);    
                }
                break;        
            case 3:
                PosX[3]->Fill(x);
                PosY[3]->Fill(y);
                if(charge==0){
                    PosXneutral[3]->Fill(x);
                    PosYneutral[3]->Fill(y);    
                }
                else{
                    PosXcharge[3]->Fill(x);
                    PosYcharge[3]->Fill(y);    
                }
                break;    
        }
    }
    cout << std::endl;
    for(int id = 0; id < nid; id++){                //Loop for histograms saving into the output file
        PosX[id]->Write();
        PosXcharge[id]->Write();
        PosXneutral[id]->Write();
        PosY[id]->Write();
        PosYcharge[id]->Write();
        PosYneutral[id]->Write();
    }
    input->Close();                                 //Closing opened .root files
    output->Close();
}