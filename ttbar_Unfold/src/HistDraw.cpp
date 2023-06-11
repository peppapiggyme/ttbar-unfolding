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

    for (const auto& cfg : m_hists) {
        std::clog << "Drawing " << cfg.name << '\n';
        if (first) {
            cfg.hist->SetXTitle(x_title.data());
            cfg.hist->SetYTitle(y_title.data());
            cfg.hist->SetStats(0);
            first = false;
        }
        if (cfg.draw_option.find('e') != std::string::npos)
            cfg.hist->Draw("E HIST SAME");
        else
            cfg.hist->Draw("HIST SAME");
        cfg.hist->SetLineColor(cfg.color);
        cfg.hist->SetLineStyle(cfg.line_style);
        cfg.hist->SetMarkerColor(cfg.color);
        cfg.hist->SetMarkerStyle(cfg.marker_style);
        
        leg->AddEntry(cfg.hist, cfg.name_tex.data(), cfg.draw_option.data());
    }
    leg->Draw();
    c->SaveAs(name.data());

    delete c, leg;
}