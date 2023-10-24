#include "HistDraw.hpp"

#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TStyle.h"

#include <iostream>

void HistDraw::Draw(const std::string& name, const std::string& x_title,
                    const std::string& y_title) const
{
    TCanvas* c   = new TCanvas("c", "c", 800, 600);
    TLegend* leg = new TLegend(0.75, 0.75, 0.9, 0.9);

    bool  first     = true;
    float max_value = 0;

    for (const auto& cfg : m_hists) {
        max_value = std::max(max_value, (float) cfg.hist->GetMaximum());
    }

    for (const auto& cfg : m_hists) {
        std::clog << "Drawing " << cfg.name << '\n';
        if (first) {
            cfg.hist->SetXTitle(x_title.data());
            cfg.hist->SetYTitle(y_title.data());
            cfg.hist->SetStats(0);
            cfg.hist->GetYaxis()->SetRangeUser(0, max_value * 2.f);
            first = false;
        }
        if (cfg.draw_option.find('e') != std::string::npos)
            cfg.hist->Draw("E SAME");
        else
            cfg.hist->Draw("HIST SAME");
        cfg.hist->SetLineColor(cfg.color);
        cfg.hist->SetLineStyle(cfg.line_style);
        cfg.hist->SetMarkerColor(cfg.color);
        cfg.hist->SetMarkerStyle(cfg.marker_style);
        max_value = std::max(max_value, (float) cfg.hist->GetMaximum());

        leg->AddEntry(cfg.hist, cfg.name_tex.data(), cfg.draw_option.data());
    }

    TLatex* tag = new TLatex(0.2f, 0.8f, m_tag.data());
    tag->SetNDC(true);
    tag->SetTextFont(42);
    tag->SetTextSize(0.036f);

    TLatex* res = new TLatex(0.2f, 0.7f, m_result.data());
    res->SetNDC(true);
    res->SetTextFont(42);
    res->SetTextSize(0.036f);

    leg->Draw();
    tag->Draw();
    res->Draw();
    c->SaveAs(name.data());

    delete c, leg;
}