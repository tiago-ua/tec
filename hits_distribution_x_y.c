void hits_distribution_x_y(){
    TFile * input = TFile::Open("AmberTarget_Run_1.root");          //Abrir data
    TFile * output = new TFile("OutputAnalysis1.root", "RECREATE");  //Cria um ficheiro output e recria-o caso já exista
    TTree * tree = (TTree*)input->Get("Hits");                      //ir buscar TTree do ficheiro de entrada
    double x, y;
    int decID, charge;
    const int nid = 4;                                              //número de detetores
    TH1F * htemp, *htempy;                                          //histogramas temporários
    tree->SetBranchAddress("detectorID", &decID);                   //Address a Branches às variáveis ​​para obter os valores quando os eventos são selecionados
    tree->SetBranchAddress("hitPosX_cm", &x);
    tree->SetBranchAddress("hitPosY_cm", &y);
    tree->SetBranchAddress("particleCharge", &charge);
    tree->Draw("hitPosX_cm>>htemp");                                //Draw às Branches e redirecionar cada uma para os histogramas htemp e htempy
    tree->Draw("hitPosY_cm>>htempy");
    htemp = (TH1F*)gDirectory->Get("htemp");                        //atribuição de histogramas temporários aos declarados para serem usados ​​na análise corretamente 
    htempy = (TH1F*)gDirectory->Get("htempy");
    Int_t xmax = htemp->GetXaxis()->GetXmax();                      //ir buscar o max/min de bins e o número de bins para posição em X e em Y
    Int_t xmin = htemp->GetXaxis()->GetXmin();
    Int_t xbins = htemp->GetXaxis()->GetNbins();
    Int_t ymax = htempy->GetXaxis()->GetXmax();
    Int_t ymin = htempy->GetXaxis()->GetXmin();
    Int_t ybins = htempy->GetXaxis()->GetNbins();
    TH1F * PosX[nid], *PosY[nid], *PosXcharge[nid], *PosXneutral[nid], *PosYcharge[nid], *PosYneutral[nid];  //declarar histogramas a usar
    for(int id = 0; id < nid; id++){
        PosX[id] = new TH1F(Form("PosXDec%d", id), Form("PosX DecID %d", id),xbins,xmin,xmax);                          //invocar construtores para cada histograma 
        PosXcharge[id] = new TH1F(Form("PosXChargeDec%d", id), Form("PosX Charged DecID %d", id),xbins,xmin,xmax);
        PosXneutral[id] = new TH1F(Form("PosXNeutralDec%d", id), Form("PosX Neutral DecID %d", id),xbins,xmin,xmax);
        PosY[id] = new TH1F(Form("PosYDec%d", id), Form("PosY DecID %d", id),ybins,ymin,ymax);
        PosYcharge[id] = new TH1F(Form("PosYChargeDec%d", id), Form("PosY Charged DecID %d", id),ybins,ymin,ymax);
        PosYneutral[id] = new TH1F(Form("PosYNeutralDec%d", id), Form("PosY Neutral DecID %d", id),ybins,ymin,ymax);
    }
    int nev = (Int_t)tree->GetEntries();                    //número de eventos no TTree para fazer o ciclo for
    printf("Number of entries are %d\n",nev);
    for(int i = 0; i<nev; i++){
        tree->GetEntry(i);                                  //obter o valor do i para que os valores x, y, decID e charge serem atribuídos aos valores do evento
        printf("Filling entry %d\r", i);
        switch(decID){                                      //mudar condição para preencher corretamente os histogramas para cada ID de detector
            case 0:
                PosX[0]->Fill(x);
                PosY[0]->Fill(y);
                if(charge==0){                              //verificar a carga de cada partículo e preencher o histograma correto
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
    for(int id = 0; id < nid; id++){                //Loop para salvar histogramas no ficheiro de saída
        PosX[id]->Write();
        PosXcharge[id]->Write();
        PosXneutral[id]->Write();
        PosY[id]->Write();
        PosYcharge[id]->Write();
        PosYneutral[id]->Write();
    }

    //Dar plot a parte da macro
    const int nvar = 6; //número de variáveis tiradas da Tree original
    TCanvas * c[nvar]; //Criar canvas para dar plot aos detetores inclusivos
    TString a[nvar] = {"PosX", "PosXcharge", "PosXneutral", "PosY", "PosYcharge", "PosYneutral"};
    const Int_t couls[nid] = {kBlue, kBlack, kGreen, kRed};  //cor dos diferentes detetores
    const Int_t styls[nid] = {20, 21, 22, 23};  //Estilos para cada detetor
    TLegend * leg = new TLegend(0.12,0.7, 0.23, 0.87);  //legenda
    leg->SetTextSize(0.03);
    for(int var = 0; var < nvar; var++){    //ciclo for nas variáveis ​​a dar plot
        c[var] = new TCanvas(a[var].Data(), a[var].Data(), 1280, 720);
        gStyle->SetOptStat(0); //remover o padrão TPaveStats 
        for(int id = 0; id < nid; id++){
            switch(var){                                    //mudar de case para dar plot às diferentes variáveis em diferentes plots
                case 0:
                    PosX[id]->SetMarkerStyle(styls[id]);
                    PosX[id]->SetMarkerColor(couls[id]);
                    PosX[id]->SetLineColor(couls[id]);
                    PosX[id]->GetYaxis()->SetRangeUser(0, 23000);
                    PosX[id]->SetTitle(Form("%s;[cm];N_{events}",a[var].Data()));
                    PosX[id]->Draw("PSAME");
                    break;
                case 1:
                    PosXcharge[id]->SetMarkerStyle(styls[id]);
                    PosXcharge[id]->SetMarkerColor(couls[id]);
                    PosXcharge[id]->SetLineColor(couls[id]);
                    PosXcharge[id]->GetYaxis()->SetRangeUser(0, 23000);
                    PosXcharge[id]->SetTitle(Form("%s;[cm];N_{events}",a[var].Data()));
                    PosXcharge[id]->Draw("PSAME");
                    break;
                case 2:
                    PosXneutral[id]->SetMarkerStyle(styls[id]);
                    PosXneutral[id]->SetMarkerColor(couls[id]);
                    PosXneutral[id]->SetLineColor(couls[id]);
                    PosXneutral[id]->GetYaxis()->SetRangeUser(0, 3500);
                    PosXneutral[id]->SetTitle(Form("%s;[cm];N_{events}",a[var].Data()));
                    PosXneutral[id]->Draw("PSAME");
                    break;
                case 3:
                    PosY[id]->SetMarkerStyle(styls[id]);
                    PosY[id]->SetMarkerColor(couls[id]);
                    PosY[id]->SetLineColor(couls[id]);
                    PosY[id]->GetYaxis()->SetRangeUser(0, 23000);
                    PosY[id]->SetTitle(Form("%s;[cm];N_{events}",a[var].Data()));
                    PosY[id]->Draw("PSAME");
                    break;
                case 4:
                    PosYcharge[id]->SetMarkerStyle(styls[id]);
                    PosYcharge[id]->SetMarkerColor(couls[id]);
                    PosYcharge[id]->SetLineColor(couls[id]);
                    PosYcharge[id]->GetYaxis()->SetRangeUser(0, 23000);
                    PosYcharge[id]->SetTitle(Form("%s;[cm];N_{events}",a[var].Data()));
                    PosYcharge[id]->Draw("PSAME");
                    break;
                case 5:
                    PosYneutral[id]->SetMarkerStyle(styls[id]);
                    PosYneutral[id]->SetMarkerColor(couls[id]);
                    PosYneutral[id]->SetLineColor(couls[id]);
                    PosYneutral[id]->GetYaxis()->SetRangeUser(0, 3500);
                    PosYneutral[id]->SetTitle(Form("%s;[cm];N_{events}",a[var].Data()));
                    PosYneutral[id]->Draw("PSAME");
                    break;
                default:
                    break;                 
            }
        }
        if(var==0){
            for(int id = 0; id < nid; id++){
                leg->SetHeader("Detector ID:", "C");
                leg->AddEntry(PosX[id], Form("%d",id), "p");
            }
        }
        leg->Draw("SAME");
        c[var]->Write();
        c[var]->Close();
    }    
    input->Close();                                 
    output->Close();
    gPad->Close();
}