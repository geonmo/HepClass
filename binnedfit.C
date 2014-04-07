#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TVirtualFitter.h"
#include "TMatrixD.h"

void lesson()
{
    TFile *f=new TFile("data.root");

    TH1F *h1 = dynamic_cast<TH1F *> f->Get("h1");
    TF1 *f2 = new TF1("f2", "[0]*x+[1]", 0.0, 5.0);

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

    // alternative way of getting fit result if the function is saved to a file
    //In this method, however, you cannot extract covariance matrix.
    //
    //TF1 *fitresult = h1->GetFunction("f2");
    //cout<< "Parameter 0" << fitresult->GetParameter(0) << "+-" << fitresult->GetParError(0) << endl;
    //cout<<  "Parameter 1" <<fitresult->GetParameter(1) << "+-" << fitresult->GetParError(1) << endl;
    //cout << "Chi2 " << fitresult->GetChisquare() << endl;
    //cout << "NDF " << fitresult->GetNDF() << endl;
    //cout << "Chi2 probability " << fitresult->GetProb() << endl;
    //

    // Yet another way
    TVirtualFitter *fitresult2 = TVirtualFitter::GetFitter(); 
    //cout<< "Parameter 0" << fitesult2->GetParameter(0) << "+-" << fitesult2->GetParError(0) << endl;
    //out<<  "Parameter 1" <<fitesult2->GetParameter(1) << "+-" << fitesult2->GetParError(1) << endl;
    //TMatrixD covmat(2,2, fitesult2->GetCovarianceMatrix());
    TH1F *hconf = new TH1F(*h1);
    hconf->SetFillColor(4);
    hconf->SetFillStyle(3003);
    fitresult2->GetConfidenceIntervals(hconf, 0.68); // 1 sigma band
    hconf->Draw("sameE3");



    TCanvas *c2 = new TCanvas("c2", "error ellipse", 600, 600);
    // how many sigma contour
    double sigma=1.0;
    gMinuit->SetErrorDef(sigma*sigma); // s^2 
    TGraph *gr1 = (TGraph*)gMinuit->Contour(80,0,1); // between variable 0 and 1
    gr1->SetFillColor(38);
    gr1->Draw("alw");

}
    

