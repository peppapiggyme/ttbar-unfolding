#ifndef SimilarityTest_hpp
#define SimilarityTest_hpp

#include "TH1.h"

#include <sstream>
#include <string>

/**
 * @brief Common tests of the similarity of two histograms,
 * described in [TH1](https://root.cern.ch/doc/master/classTH1.html).
 */
class SimilarityTest
{
public:
    SimilarityTest(TH1* h1, TH1* h2);
    std::string GetResults() const;

private:
    void Kolmogorov();
    void ChiSquare();

    TH1* m_h1;
    TH1* m_h2;

    std::ostringstream m_oss;
};

#endif