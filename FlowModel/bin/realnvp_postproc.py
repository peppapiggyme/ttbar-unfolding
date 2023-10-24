#!/usr/bin/python

import ROOT as R
import os.path as path

def Hist(df, var_name, hist_title, nbins, start, end, weight_name="weight"):
    print(f"Filling histogram of {var_name} ..")
    h = df.Histo1D(
        R.RDF.TH1DModel(var_name, hist_title, nbins, start, end), var_name, weight_name
    )
    h.SetDirectory(0)
    return h

def main():
    run_path = "/home/zhangbw/Documents/projects/ttbar-unfolding/run"
    file_name = path.join(run_path, "realnvp_output.root")
    out_file_name = path.join(run_path, "realnvp_output_hist.root")

    reco = R.RDataFrame("reco", file_name)
    unfold = R.RDataFrame("unfold", file_name)
    truth = R.RDataFrame("truth", file_name)

    h_reco = Hist(reco, "ST", "", 40, 0, 800)
    h_unfold = Hist(unfold, "ST_NF", "", 40, 0, 800)
    h_truth = Hist(truth, "ST_truth", "", 40, 0, 800)
    
    # post-proc output file
    f = R.TFile(out_file_name, "recreate")
    print(f"Writing to {out_file_name} ..")
    h_reco.Write()
    h_unfold.Write()
    h_truth.Write()
    f.Close()

if __name__ == "__main__":
    main()
