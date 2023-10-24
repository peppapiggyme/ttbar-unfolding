#include "SimilarityTest.hpp"

#include <iomanip>

SimilarityTest::SimilarityTest(TH1* h1, TH1* h2) : m_h1(h1), m_h2(h2)
{
    ChiSquare();
}

std::string SimilarityTest::GetResults() const { return m_oss.str(); }

void SimilarityTest::Kolmogorov()
{
    auto pvalue = m_h1->KolmogorovTest(m_h2, "UO");
    m_oss << "KS p=" << std::setprecision(4) << pvalue << " ";
}

void SimilarityTest::ChiSquare()
{
    double chi2 { 0 };
    int    ndf { 0 };
    int    igood { 0 };
    auto   pvalue = m_h1->Chi2TestX(m_h2, chi2, ndf, igood, "WW");
    m_oss << "Chi2 p=" << std::setprecision(4) << pvalue
          << ", x2/ndf=" << chi2 / ndf << " ";
}
