#ifndef HistDraw_hpp
#define HistDraw_hpp

#include <TH1.h>

#include <list>
#include <string>

struct HistEntry {
    std::string name;
    std::string name_tex;
    std::string draw_option;
    int         color;
    int         line_style;
    int         marker_style;
    TH1*        hist;
};

class HistDraw
{
public:
    HistDraw() = default;

public:
    void Append(const HistEntry&& entry) { m_hists.emplace_back(entry); }
    void Draw(const std::string& name, const std::string& x_title,
              const std::string& y_title) const;
    void SetTag(const std::string& tag) { m_tag = tag; }
    void SetResult(const std::string& result) { m_result = result; }

private:
    std::list<HistEntry> m_hists;
    std::string          m_tag;
    std::string          m_result;
};

#endif