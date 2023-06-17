#include "HistDraw.hpp"

#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"

#include <iostream>

void HistDraw::Draw(const std::string_view& name,
                    const std::string_view& x_title,
                    const std::string_view& y_title) const
{
    TCanvas* c   = new TCanvas("c", "c", 800, 600);
    TLegend* leg = new TLegend(0.75, 0.75, 0.9, 0.9);

    bool first = true;
    float max_value = 0;

    for (const auto& cfg : m_hists) {
        max_value = std::max(max_value, (float)cfg.hist->GetMaximum());
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
        max_value = std::max(max_value, (float)cfg.hist->GetMaximum());

        leg->AddEntry(cfg.hist, cfg.name_tex.data(), cfg.draw_option.data());
    }
    leg->Draw();
    c->SaveAs(name.data());

    delete c, leg;
}