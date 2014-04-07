#include "TFile.h"
#include "TTree.h"
#include "TF1.h"

void lesson()
{
    // Read in ROOT tree
    TFile *f=new TFile("data.root");
    TTree *datatree = dynamic_cast<TTree *>f->Get("mytree");

    // fit function
    TF1 *f3 = new TF1("f3", "[0]*x-[0]*2.5+0.2", 0.0, 5.0); // function's integral must be 1
    f3->SetParameter(0,0.01);

    // unbinned maximum likelihood fit
    // ROOT allows maximum likelihood fit on Root Trees
    datatree->UnbinnedFit("f3", "data");

    //TF1 *fitresult = h1->GetFunction("f2");
    //cout << "Chi2 " << fitresult->GetChisquare() << endl;
    //cout << "NDF " << fitresult->GetNDF() << endl;
    //cout << "Chi2 probability " << fitresult->GetProb() << endl;

    TVirtualFitter *fitrp = TVirtualFitter::GetFitter(); // assuming it's Minuit
    TMatrixD covmat(1,1, fitrp->GetCovarianceMatrix());
    cout << "Covariance matrix" << endl;
    covmat.Print();
    // how many sigma contour.. doesn't make sense for this fit
    //double sigma=1.0;
    //gMinuit->SetErrorDef(sigma*sigma); // s^2 
    //TGraph *gr1 = (TGraph*)gMinuit->Contour(80,0,1); // between variable 0 and 1
    //gr1->SetFillColor(38);
    //gr1->Draw("al");

}
