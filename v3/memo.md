# mini-DST files v3 (as of 2020/August/4)

Input DST files: physics validation samples produced with iLCSoft v02-01-02. see sample.txt for full path.

Output mini-DST files: uploaded on [DESY cloud](https://desycloud.desy.de/index.php/s/YR5HB9DTBiLzSHi)

The next table shows that which original DST files are used to produce mini-DST files.
|File No|processID|physics process|
|:---:|:---:|:---:|
|1-5|401010|e2e2h|
|6-7|401011|qqh_zz|
|8-10|401012|6f_llxyyx|
|11|499989|2f_z_l|
|12|499990|2f_z_h|
|13|499991|4f_ww_sl|
|14|499992|4f_sw_sl|

## Difference between v2 and v3
- Now using iLCSoft v02-01-02. Test samples as well.

In these mini-DST file, the following collections are stored.
- PandoraPFOs, BCalRecoParticle (not merged yet, not simplified anything)
- MCParticle
- PrimaryVertex, PrimaryVertex_RP
- RecoMCThuthLink, MCTruthRecoLink (kept full relation)

The following collections are added to the mini-DST file. All parameters/weight files are not tuned at all.
- event shape variables (used ThrustReconstruction, Sphere, Fox): these are stored at the header of PandoraPFOs
- IsolatedMuons, IsolatedElectrons (used IsolatedLeptonTagging)
- IsolatedTaus (used TauFinder)
- IsolatedPhotons (used IsolatedPhotonTaggingProcessor)
- RefinedNJets (N = 2, 3, 4, 5, 6) (used LCFIPlus: JetClustering, JetVertexRefiner, FlavorTag)
- The ErrorFlow processor is applied to RefinedNJets to calculate covariance matrix for jets.

File size details:

|File No|# events|DST (MB)|DST, (MB)/event|mini-DST (MB)|mini-DST, (MB)/event|
|:---:|:---:|:---:|:---:|:---:|:---:|
|1|10500|704|0.0670|252|0.0240|
|2|10500|699|0.0666|250|0.0238|
|3|10500|699|0.0666|250|0.0238|
|4|10500|702|0.0669|251|0.0239|
|5|8000|535|0.0669|191|0.0239|
|6|5100|578|0.113|198|0.0390|
|7|4900|555|0.113|190|0.0390|
|8|6800|734|0.108|253|0.0370|
|9|6800|736|0.108|254|0.0370|
|10|6400|692|0.108|239|0.0370|
|11|10000|79|0.00790|44|0.00440|
|12|10000|620|0.0620|232|0.0232|
|13|10000|542|0.0542|205|0.0205|
|13|10000|541|0.0541|205|0.0205|
