#include "TLorentzVector.h"
#include "TVector3.h"
#include "TMath.h"
#include "lester_mt2_bisect.h"

//______________________________________________________________________________________________
float MT2()
{
    TLorentzVector lepton1;
    TLorentzVector lepton2;
    TLorentzVector misspart;
    TLorentzVector rest_WW;

    float lep_pt1 = 20;
    float lep_pt2 = 30;
    float lep_eta1 = 0.1;
    float lep_eta2 = 0.5;
    float lep_phi1 = 1.0;
    float lep_phi2 = 2.0;
    float lep_energy1 = 23;
    float lep_energy2 = 33;
    float met = 50;
    float metphi = -2.0;

    lepton1.SetPtEtaPhiE(lep_pt1, lep_eta1, lep_phi1, lep_energy1);
    lepton2.SetPtEtaPhiE(lep_pt2, lep_eta2, lep_phi2, lep_energy2);
    misspart.SetPtEtaPhiM(met, /*???*/TMath::Pi() / 2, metphi, 0);
    rest_WW = lepton1 + lepton2 + misspart;
    TVector3 beta_from_miss_reverse(rest_WW.BoostVector());
    TVector3 beta_from_miss(-beta_from_miss_reverse.X(),-beta_from_miss_reverse.Y(),-beta_from_miss_reverse.Z());

    lepton1.Boost(beta_from_miss);
    lepton2.Boost(beta_from_miss);
    misspart.Boost(beta_from_miss);
    asymm_mt2_lester_bisect::disableCopyrightMessage();
    double MT2_0mass = asymm_mt2_lester_bisect::get_mT2(0,lepton1.Px(),lepton1.Py(),0,lepton2.Px(),lepton2.Py(),misspart.Px(), misspart.Py(),0,0,0);

    return MT2_0mass;
}

//______________________________________________________________________________________________
int main()
{
    float result = MT2();
    printf("result = %f\n", result);
}
