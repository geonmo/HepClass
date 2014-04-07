#include "TRandom3.h"
#include "TH1F.h"

void gaussianrandomsample(int nsamples)
{
    TRandom3 rn;
    TH1F *h1 = new TH1F("h1", "gaussian random sample",50, -5.0, 5.0);
    TH1F *hsamplemean = new TH1F("hsamplemean", "Sample mean", 50, -5.0, 5.0);
    TH1F *hsamplerms = new TH1F("hsamplerms", "sample rms", 50, 0.0, 2.0);
    TH1F *htruerms = new TH1F("htruerms", "sample rms", 50, 0.0, 2.0);
    TH1F *htdistribution = new TH1F("htdistribution", "Student's t", 50, -5.0, 5.0);
    TH1F *hpull = new TH1F("hpull", "Pull Distribution", 50, -5.0, 5.0);

    double xsum;
    double xsquaredsum;
    double xi[1000];

    if (nsamples>1000) {
        cout << "try nsamples less than 1000" << endl; 
        return;
    }

    for (int trials=0; trials<10000; trials++)
    {
        xsum = 0.0;
        xsquaredsum = 0.0;
        for (int i=0; i<nsamples; i++)
        {
            xi[i] = rn.Gaus(1.0, 1.0); // sample from mean=1, sigma=1
            // Calculate sample mean
            // xbar = 1/N * (sum of x_i)
            //
            xsum  += xi[i];

            // Calculate sample variance
            // sigma^2 = 1/N * (sum of x_i squared) - (xbar squared)  
            xsquaredsum += xi[i]*xi[i];

        }
        double muhat = xsum / nsamples;
        double samplevariance = (xsquaredsum/nsamples - muhat*muhat);
            //*nsamples/(nsamples-1);

        hsamplemean->Fill(muhat);
        hsamplerms->Fill(sqrt(samplevariance));
        for (int i=0; i<nsamples; i++)
        {
            htdistribution->Fill((xi[i]-1.0)/sqrt(samplevariance));
            hpull->Fill((xi[i]-1.0)/1.0);
        }
    }

}
