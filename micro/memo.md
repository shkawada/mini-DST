# mini-DST files v1 (as of 2020/July/1)

Input DST files: physics validation samples produced with iLCSoft v02-01. see sample.txt for full path.

Output mini-DST files: go to /afs/desy.de/user/s/skawada/public/mini-DST-v1

The next table shows that which original DST files are used to produce mini-DST files.
|File No|processID|physics process|
|:---:|:---:|:---:|
|1-5|I401006|e2e2h|
|6-7|I401007|qqh_zz|
|8-10|I401009|6f_llxyyx|
|11|I499997|2f_z_l|
|12|I499998|4f_ww_sl|
|13|I499999|4f_sw_sl|

## Difference between v0 and v1
- The e2e2h files with processID I401005 are removed from sample.txt because these samples are created wrongly.
- The 6f_llyxxy files (ID = I401009) are added in sample.txt.
- The processor for isolated taus are changed from TaJetClustering to TauFinder. One reason of this change is that TaJetClustering gave us terrible performance with DBD 4f_WW_hadronic events. Another reason is that TauFinder is used most recently under ILC physics analysis.

In these mini-DST file, the following collections are stored.
- PandoraPFOs, BCalRecoParticle (not merged yet, not simplified anything)
- MCParticle
- PrimaryVertex, PrimaryVertex_RP
- RecoMCThuthLink, MCTruthRecoLink (kept full relation)

The following collections are added to the mini-DST file. All parameters/weight files are not tuned at all.
- event shape variables (used ThrustReconstruction, Sphere, Fox): these are stored at the header of PandoraPFOs
- IsolatedMuons, IsolatedElectrons (used IsolatedLeptonTagging)
- IsolatedTaus (used TauFinder)
- RefinedNJets (N = 2, 3, 4, 5, 6) (used LCFIPlus: JetClustering, JetVertexRefiner, FlavorTag)
- The ErrorFlow processor is applied to RefinedNJets to calculate covariance matrix for jets.

File size details:

|File No|# events|DST (MB)|DST, (MB)/event|mini-DST (MB)|mini-DST, (MB)/event|
|:---:|:---:|:---:|:---:|:---:|:---:|
|1|10500|761|0.0725|319|0.0304|
|2|10500|762|0.0726|319|0.0304|
|3|10500|762|0.0726|320|0.0305|
|4|10500|764|0.0728|320|0.0305|
|5|8000|584|0.073|245|0.0306|
|6|5500|680|0.1236|275|0.05|
|7|4500|551|0.1224|223|0.0496|
|8|6800|807|0.1187|329|0.0484|
|9|6800|802|0.1179|327|0.0481|
|10|6400|753|0.1177|308|0.0481|
|11|10000|91|0.009|56|0.006|
|12|10000|595|0.0595|264|0.0264|
|13|10000|603|0.0603|272|0.0272|
