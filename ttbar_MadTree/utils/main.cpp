
#include "Config.hpp"
#include "RecoTree.hpp"

#include <iostream>
#include <memory>
#include <string>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::clog << "Usage:\n\tRecoAnalysis.Run <input.root>\n";
        exit(0);
    }
    // suppress warning/error outputs of ROOT
    gPrintViaErrorHandler = kTRUE;
    gErrorIgnoreLevel     = 6001;

    // config
    std::string in_path { argv[1] };
    IOConfig    c { in_path, std::string("reco_analysis__").append(in_path) };

    // run reco tree loop
    (new RecoTree(c))->Loop(); // leak but no segfault from ROOT

    return 0;
}
