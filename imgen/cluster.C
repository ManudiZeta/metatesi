#include "TFile.h"
#include <Riostream.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TString.h"

void super (TString var, TString assex,TString title, TString um, TString x1, TString x2)
{
    gStyle->SetOptStat(0);
    TString in_1;
    TFile *myf_1 = new TFile("../../../vpho_isr_n_REC_merge100k_09012026.root");
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    TTree *tree_2 = (TTree*)myf_1->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    TString drawExpr1 = var + ">>histo1(512," + x1 + "," + x2 + ")";
    TString drawExpr2 = var + ">>histo2(512," + x1 + "," + x2 + ")";
    tree_1->Draw(drawExpr1, "", "goff");
    tree_2->Draw(drawExpr2, "nbar_mcPDG == -2112", "goff");
    
    
    delete c1;
    
    TH1 *histo1 = (TH1D*)gDirectory->Get("histo1");
    TH1 *histo2 = (TH1D*)gDirectory->Get("histo2");
    
    double mean_1 = histo1->GetMean();
    double devstd_1 = histo1->GetStdDev();
    double entries_1 = histo1->GetEntries();
    
    
    double mean_2 = histo2->GetMean();
    double devstd_2 = histo2->GetStdDev();
    double entries_2 = histo2->GetEntries();
    
    
    cout<<"entries_1 = "<<entries_1<<"|mean_1 = "<<mean_1<<"|devstd_1 = "<<devstd_1<<endl;
    cout<<"entries_2 = "<<entries_2<<"|mean_2 = "<<mean_2<<"|devstd_2 = "<<devstd_2<<endl;
    
    //histo1->Scale(1.0 / histo1->Integral());
    //histo2->Scale(1.0 / histo2->Integral());
    
    
    double max1 = histo1->GetBinContent(histo1->GetMaximumBin());
    cout<<"max1 = "<<max1<<endl;
    double max2 = histo2->GetBinContent(histo2->GetMaximumBin());
    cout<<"max2 = "<<max2<<endl;
    double max = (max1 > max2) ? max1 : max2;
    //double max = max1;
    cout<<"max = "<<max<<endl;
    
    histo1->SetMaximum(max + 0.1*max);
    histo2->SetMaximum(max + 0.1*max);
    
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);
    histo1->SetFillColor(kBlue);
    histo2->SetFillColor(kRed);
    //TString title_x = var + "[rad]";
    TString title_x = assex + um;
    histo1->GetXaxis()->SetTitle(title_x);
    histo1->GetYaxis()->SetTitle("counts");
    
    histo1->SetTitle(title);
    
    
    cout<<"NEntries_1 = "<<histo1->GetEntries()<<endl;
    cout<<"NEntries_2 = "<<histo2->GetEntries()<<endl;
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(histo1,"all #bar{n} candidates","l");
    leg->AddEntry(histo2,"MC truth ID","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    histo2->DrawCopy("HIST SAMES");
    leg->Draw("SAME");
    
    TString title_out = "../images/cluster/" + var + ".pdf";
    tela->SaveAs(title_out);
    
    
}


void super_real (TString var, TString assex,TString title, TString um, TString x1, TString x2)
{
    gStyle->SetOptStat(0);
    TString in_1;
    TFile *myf_1 = new TFile("../../../RealSel_nog_cocktail_parz.root");
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    TString drawExpr1 = var + ">>histo1(512," + x1 + "," + x2 + ")";
    tree_1->Draw(drawExpr1, "alpha<0.35 &&  nROE_Charged__bo__bc == 0 && vpho_r_mRecoil >0.8 && vpho_r_mRecoil <1.1", "goff");
    
    
    delete c1;
    
    TH1 *histo1 = (TH1D*)gDirectory->Get("histo1");
    
    
    histo1->SetLineColor(kBlue);
    histo1->SetFillColor(kBlue);
    
    TString title_x = assex + um;
    histo1->GetXaxis()->SetTitle(title_x);
    histo1->GetYaxis()->SetTitle("counts");
    
    histo1->SetTitle(title);
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    
    TString title_out = "../images/cluster/" + var + "_real.pdf";
    tela->SaveAs(title_out);
    
    
}




void due_grand(TString var, TString cut, TString um, TString x1, TString x2)
{
    gStyle->SetOptStat(1);
    string in_1, in_2;
    TFile *myf_1 = nullptr;
    
    
    in_1 = "../../../tot_nog_06012026.root";
    
    ifstream in_f1(in_1);
    
    if(!in_f1)
    {
        cout<<"Selected root file doesn't exist. Please, generate it. \n";
        return;
    }
    in_f1.close();
    
    myf_1 = new TFile("../../../tot_nog_06012026.root");
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    TTree *tree_2 = (TTree*)myf_1->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    TString var_1 = "nbar_" + var;
    TString var_2 = "nbar_" + var;
    cout<<"var_1 = "<<var_1<<endl;
    cout<<"var_2 = "<<var_2<<endl;
    
    TString drawExpr1 = var_1 + ">>histo1(256," + x1 + "," + x2 + ")";
    TString drawExpr2 = var_2 + ">>histo2(256," + x1 + "," + x2 + ")";
    TString cut_2 = "nbar_" + cut;
    cout<<"cut_2 = "<<cut_2<<endl;
    tree_1->Draw(drawExpr1, "", "goff");
    tree_2->Draw(drawExpr2, cut_2, "goff");
    
    
    delete c1;
    TH1 *histo1 = (TH1D*)gDirectory->Get("histo1");
    TH1 *histo2 = (TH1D*)gDirectory->Get("histo2");
    
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);
    histo1->SetFillColor(kBlue);
    histo2->SetFillColor(kRed);
    
    TString title_x = var + " [" + um + "]";
    //TString title_x = "clusterSecondMoment []";
    histo1->GetXaxis()->SetTitle(title_x);
    histo1->GetYaxis()->SetTitle("counts []");
    
    
    TString title = "";
    histo1->SetTitle(title);
    
    
    cout<<"NEntries_1 = "<<histo1->GetEntries()<<endl;
    cout<<"NEntries_2 = "<<histo2->GetEntries()<<endl;
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(histo1,"all #bar{n} candidates ","l");
    leg->AddEntry(histo2,cut_2,"l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    histo2->DrawCopy("HIST SAMES");
    leg->Draw("SAME");
    
    TString title_out = "../images/continuum/" + var +"_-2112.pdf";
    tela->SaveAs(title_out);
    
}
