
#include <TH1.h>

#include <list>
#include <string>

struct HistEntry {
    std::string_view name;
    std::string_view name_tex;
    std::string_view draw_option;
    int              color;
    int              line_style;
    int              marker_style;
    TH1*             hist;
};

class HistDraw
{
public:
    HistDraw() = default;

public:
    void Append(const HistEntry&& entry) { m_hists.emplace_back(entry); }
    void Draw(const std::string_view& name, 
              const std::string_view& x_title,
              const std::string_view& y_title) const;

private:
    std::list<HistEntry> m_hists;
};