#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooMinuit.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
using namespace RooFit ;

void lesson()
{
    TFile *f=new TFile("data.root");
    TTree *datatree = dynamic_cast<TTree *>f->Get("mytree");

    // Define observable x
    RooRealVar x("data","data points",0,5);
    RooDataSet data("dataraw", "dataset with x", datatree, x);

    // Define fit variables
    RooRealVar *c0 = new RooRealVar("c0", "slope", 1.0, -1.0, 1.0);
    RooPolynomial *model = new RooPolynomial("fit", "model p.d.f.", x, RooArgList(*c0));

    // do the fit
    RooFitResult *r = model->fitTo(data, Save());

    // plot result
    RooPlot* xframe = x.frame(Title("Unbinned data"));
    data.plotOn(xframe);
    model->plotOn(xframe, VisualizeError(*r,1), FillColor(kOrange)); // 1 sigma
    model->plotOn(xframe);

    //Show fit result
    TCanvas *c1=new TCanvas("c1", "fitted line", 600, 600);
    c1->Draw();
    xframe->Draw();


    // C o n s t r u c t   p l a i n   l i k e l i h o o d
    // ---------------------------------------------------

    // Construct unbinned likelihood
    RooAbsReal* nll = model->createNLL(data) ;

    // Minimize likelihood w.r.t all parameters before making plots
    RooMinuit(*nll).migrad() ;
    RooMinuit(*nll).minos() ;

    // Plot likelihood scan
    RooPlot* frame1 = c0->frame(Bins(10),Range(0.1,0.3),Title("LL in slope")) ;
    nll->plotOn(frame1,ShiftToZero()) ;
    TCanvas *c2=new TCanvas("c2", "Log likelihood curve", 600, 600);
    c2->Draw();
    frame1->Draw();


}

