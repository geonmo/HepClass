hw()
{
    Float_t data;
    TFile *f=new TFile("data.root");
    TTree* tree = f->Get("mytree");
    TBranch* branch = tree->GetBranch("data");
    branch->SetAddress(&data);

    TH1F* h1 = new TH1F("h1","h1",200,0.0,5.0);
    for(Int_t i= 0 ; i< tree->GetEntries() ; i++) {
	tree->GetEntry(i);
        h1->Fill( data) ;
    }
       
    TF1 *f2 = new TF1("f2", "[0]*x+[1]+gaus(2)", 0.0, 5.0);
    f2->SetParameter(3,3.7);

    TVirtualFitter *min = TVirtualFitter::Fitter(0,2);
    TVirtualFitter::SetDefaultFitter("Minuit");

    TFitResultPtr fitresult = h1->Fit("f2", "MES");
    cout<< "Parameter 0" << fitresult->Parameter(0) << "+-" << fitresult->ParError(0) << endl;
    cout<<  "Parameter 1" <<fitresult->Parameter(1) << "+-" << fitresult->ParError(1) << endl;
    cout << "Chi2 " << fitresult->Chi2() << endl;
    cout << "NDF " << fitresult->Ndf() << endl;
    cout << "Chi2 probability " << fitresult->Prob() << endl;
    TMatrixD covmat(fitresult->GetCovarianceMatrix());
    cout << "Covariance matrix" << endl;
    covmat.Print();
    TCanvas *c1 = new TCanvas("c1", "binned line fit", 600, 600);
    c1->Draw();
    h1->Draw();


}
