
#include "RooUnfold.h"
#include "RooUnfoldErrors.h"
#include "RooUnfoldResponse.h"
#include "TH1.h"
#include "TH2.h"

#include <memory>
#include <optional>

class UnfoldFactory
{
public:
    /**
     * @brief Create a RooUnfold instance.
     *
     * Options are:
     * - kNone:     dummy unfolding
     * - kBayes:    Unfold via iterative application of Bayes theorem
     * - kSVD:      Unfold using singlar value decomposition (SVD)
     * - kBinByBin: Unfold bin by bin.
     * - kTUnfold:  Unfold with TUnfold
     * - kInvert:   Unfold using inversion of response matrix
     * - kIDS:      Unfold using iterative dynamically stabilized (IDS) method
     * - kGP:       Unfold using Gaussian Processes(GP)
     * - kPoisson:  Unfold using Poisson-based likelihood and Tikhinov
     * regularization
     *
     * @param alg Options enum as described above
     * @param res Pointer to RooUnfoldResponse instance
     * @param meas Histogram of measurement
     * @param reg  Regularisation parameter
     *
     * @return std::shared_ptr<RooUnfold>
     */
    static std::shared_ptr<RooUnfold> Create(RooUnfold::Algorithm alg,
                                             RooUnfoldResponse*   res,
                                             const TH1* meas, const std::optional<double>& reg);
};