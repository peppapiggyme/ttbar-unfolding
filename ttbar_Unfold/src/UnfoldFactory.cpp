#include "UnfoldFactory.hpp"

#include "RooMultiVarGaussian.h"

#include "RooUnfoldBayes.h"
#include "RooUnfoldBinByBin.h"
#include "RooUnfoldErrors.h"
#include "RooUnfoldGP.h"
#include "RooUnfoldHelpers.h"
#include "RooUnfoldIds.h"
#include "RooUnfoldInvert.h"
#include "RooUnfoldPoisson.h"
#include "RooUnfoldResponse.h"
#include "RooUnfoldSvd.h"
#include "RooUnfoldTH1Helpers.h"
#include "RooUnfoldTUnfold.h"

std::shared_ptr<RooUnfold> UnfoldFactory::Create(RooUnfold::Algorithm  alg,
                                                 RooUnfoldResponse*    res,
                                                 const TH1*            meas,
                                                 const std::optional<double>& reg)
{
    std::shared_ptr<RooUnfold> unfold;

    switch (alg) {
        case RooUnfolding::kNone:
            unfold = std::make_shared<RooUnfold>(res, meas);
            break;
        case RooUnfolding::kBayes:
            unfold = std::make_shared<RooUnfoldBayes>(res, meas);
            break;
        case RooUnfolding::kSVD:
            unfold = std::make_shared<RooUnfoldSvd>(res, meas);
            break;
        case RooUnfolding::kBinByBin:
            unfold = std::make_shared<RooUnfoldBinByBin>(res, meas);
            break;
        case RooUnfolding::kTUnfold:
            unfold = std::make_shared<RooUnfoldTUnfold>(res, meas);
            break;
        case RooUnfolding::kInvert:
            unfold = std::make_shared<RooUnfoldInvert>(res, meas);
            break;
        case RooUnfolding::kGP:
            unfold = std::make_shared<RooUnfoldGP>(res, meas);
            break;
        case RooUnfolding::kPoisson:
            unfold = std::make_shared<RooUnfoldPoisson>(res, meas);
            break;
        case RooUnfolding::kIDS:
            unfold = std::make_shared<RooUnfoldIds>(res, meas);
            break;
        default:
            std::clog << "Unfolding algorithm not specified. Using SVD..\n";
            unfold = std::make_shared<RooUnfoldSvd>(res, meas);
    }

    unfold->SetName("ttbar_unfold");
    unfold->SetTitle("t#bar{t} unfolding");
    if (reg.has_value()) { unfold->SetRegParm(reg.value()); }

    return unfold;
}