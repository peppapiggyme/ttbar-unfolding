## To-do list

* ~~extract functions from `Loop`~~
* ~~add top-quark analysis~~
    * ~~find two original top-quark~~ (by status == 62)
    * ~~set them as true particle~~
* ~~add bbmumu anlaysis~~
    * ~~reconstructed particle~~
        * ~~find two b-jets~~ (efficiency is quite low..)
        * ~~find two muons~~ (leading two..)
* ~~reconstruct pt of t, tt, ...~~ (sum of transverse momentum, t not possible)
* ~~add a tree tool: can write member float to tree, cannot write float in map<index, float>~~ (worked with array<float>)

```bash
root [1] nominal->Show(1)
======> EVENT:1
 t0_truth_Pt     = 166.36
 t1_truth_Pt     = 207.932
 tt_truth_Pt     = 44.5957
 tt_truth_m      = 513.26
 ST_truth        = 374.292
 tt_Pt           = 155.199
 tt_m            = 284.667
 ST              = 464.953
 mu0_Pt          = 49.5792
 mu1_Pt          = 10.8683
 b0_Pt           = 150.474
 b1_Pt           = 72.6333
 MET             = 181.398
 n_jets          = 7
 event_number    = 2
 weight          = 0.00154058
```

* ~~generate more data~~ (pre-selection 100k ttbar_nlo_decayed)
    * ~~write scipts~~ (manually)
    * ~~do I have enough storage? (move outputs to disk)~~ (no need so far)


```bash
zhangbw@Artlas:~/Documents/playground$ du -shx *
2.0M    cpp
2.9G    MadGraph
4.1M    rust
```

* learn how to unfolding the traditional way
    * implement unfolding
* learn how to unfolding the normalising flow way
    * implement unfolding
* performance metric ?