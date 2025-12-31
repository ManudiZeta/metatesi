#include "TFile.h"
#include <Riostream.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TString.h"
#include "TLine.h"
#include "TPaveText.h"

void una_grand ()
{
    gStyle->SetOptStat(1);
    string in_1;
    TFile *myf_1 = nullptr;
    in_1 = "../../../vpho_std_isr_n_REC_merge100k_2.root";
    ifstream in_f1(in_1);
    
    
    if(!in_f1)
    {
        cout<<"Selected root file doesn't exist. Please, generate it. \n";
        return;
    }
    in_f1.close();
    
    myf_1 = new TFile("../../../vpho_std_isr_n_REC_merge100k_2.root");
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    TString var = "nbar_p/vpho_r_pRecoil";
    TString um = "";
    TString drawExpr1 = var + ">>histo1(100,0,1.5)";
    tree_1->Draw(drawExpr1,"nbar_mcPDG == -2112");
    
    
    delete c1;
    
    TH1D *histo1 = (TH1D*)gDirectory->Get("histo1");
        
    histo1->SetLineColor(kBlue);
    TString title_x = var + " [" + um + "]";
    histo1->GetXaxis()->SetTitle(title_x);
    histo1->GetYaxis()->SetTitle("counts []");
    TString title = "";
    histo1->SetTitle(title);
            
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    
    TString title_out = "../images/gen_" + var + ".pdf";
    tela->SaveAs("../images/feac_pREC_np.pdf");
    
}


void due_grand()
{
    gStyle->SetOptStat(1);
    string in_1, in_2;
    TFile *myf_1 = nullptr;
    
    
    in_1 = "../../../vpho_std_isr_n_REC_merge100k_2.root";
    
    ifstream in_f1(in_1);
    
    if(!in_f1)
    {
        cout<<"Selected root file doesn't exist. Please, generate it. \n";
        return;
    }
    in_f1.close();
    
    myf_1 = new TFile("../../../vpho_std_isr_n_REC_merge100k_2.root");
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    TTree *tree_2 = (TTree*)myf_1->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    TString var_1 = "vpho_r_pRecoil";
    TString var_2 = "nbar_mcP";
    TString drawExpr1 = var_1 + ">>histo1(128,0,7)";
    TString drawExpr2 = var_2 + ">>histo2(128,0,7)";
    tree_1->Draw(drawExpr1, "nbar_mcPDG == -2112", "goff");
    tree_2->Draw(drawExpr2, "nbar_mcPDG == -2112", "goff");
    
    
    delete c1;
    TH1 *histo1 = (TH1D*)gDirectory->Get("histo1");
    TH1 *histo2 = (TH1D*)gDirectory->Get("histo2");
    
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kRed);
    //TString title_x = var + "[rad]";
    TString title_x = "p [GeV]";
    histo1->GetXaxis()->SetTitle(title_x);
    histo1->GetYaxis()->SetTitle("counts []");
    
    TString title = "";
    histo1->SetTitle(title);
    
    
    cout<<"NEntries_1 = "<<histo1->GetEntries()<<endl;
    cout<<"NEntries_2 = "<<histo2->GetEntries()<<endl;
    
    TLegend *leg = new TLegend(0.6,0.6,0.78,0.78);
    leg->AddEntry(histo1,"pRecoil REC ","l");
    leg->AddEntry(histo2,"#bar{n} mc_P","l");
    
    TCanvas *tela = new TCanvas("tela", "tela");
    
    histo1->DrawCopy("HIST");
    histo2->DrawCopy("HIST SAMES");
    leg->Draw("SAME");
    
    TString title_out = "../images/pRecoil_nmcP_PDGsel.pdf";
    tela->SaveAs(title_out);
    
}



void corr ()
{
    gStyle->SetOptStat(1);
    string in_1;
    TFile *myf_1 = nullptr;
    in_1 = "../../../vpho_std_isr_n_REC_merge100k_2.root";
    ifstream in_f1(in_1);
    
    
    if(!in_f1)
    {
        cout<<"Selected root file doesn't exist. Please, generate it. \n";
        return;
    }
    in_f1.close();
    
    myf_1 = new TFile("../../../vpho_std_isr_n_REC_merge100k_2.root");
    
    TTree *tree_1 = (TTree*)myf_1->Get("tree");
    
    TCanvas *c1 = new TCanvas("c1", "c1",800,600);
    TString var = "vpho_r_pRecoil:nbar_mcP";
    TString um = "GeV";
    TString drawExpr1 = var + ">>histo1(100,0,7,100,0,7)";
    tree_1->Draw(drawExpr1,"nbar_mcPDG == -2112","colz");
    
    
    delete c1;
    
    TH2 *histo1 = (TH2D*)gDirectory->Get("histo1");
    double rho = histo1->GetCorrelationFactor();
    histo1->SetLineColor(kBlue);
    cout << "Correlation factor = " << rho << endl;
    
    TString title_x = var + " [" + um + "]";
    histo1->GetXaxis()->SetTitle("#bar{n} mc_p [GeV]");
    histo1->GetYaxis()->SetTitle("pRecoil [GeV]");
    histo1->SetTitle("From generator");
        
    TLine *tl = new TLine(0,0,7,7);
        
    TCanvas *tela = new TCanvas("tela", "tela");
    
    TPaveText *pt = new TPaveText(0.15, 0.80, 0.45, 0.90, "NDC");
    pt->SetFillColor(0);
    pt->SetBorderSize(1);
    pt->SetTextAlign(12);
    pt->SetTextSize(0.035);
    pt->AddText(Form("#rho = %.3f", rho));
    
    
    histo1->DrawCopy("HIST");
    tl->Draw("same");
    pt->Draw("same");
    //TString title_out = "../images/gen_" + var + ".pdf";
    TString title_out = "../images/gen_mc_p_corr.pdf";
    tela->SaveAs(title_out);
    
    
}


