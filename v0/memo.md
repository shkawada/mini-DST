# mini-DST files v0 (as of 2020/June/11)

Input DST files: all physics validation samples produced with iLCSoft v02-01. see sample.txt for full path.

Output mini-DST files: go to /afs/desy.de/user/s/skawada/public/mini-DST-v0

The next table shows that which original DST files are used to produce mini-DST files.
|File No|processID|physics process|
|:---:|:---:|:---:|
|1-4|I401005|e2e2h|
|5-9|I401006|e2e2h|
|10-11|I401007|qqh_zz|
|12|I499997|2f_z_l|
|13|I499998|4f_ww_sl|
|14|I499999|4f_sw_sl|

In these mini-DST file, the following collections are stored.
- PandoraPFOs, BCalRecoParticle (not merged yet, not simplified anything)
- MCParticle
- PrimaryVertex, PrimaryVertex_RP
- RecoMCThuthLink, MCTruthRecoLink (kept full relation)

The following collections are added to the mini-DST file. All parameters/weight files are not tuned at all.
- event shape variables (used ThrustReconstruction, Sphere, Fox): these are stored at the header of PandoraPFOs
- IsolatedMuons, IsolatedElectrons (used IsolatedLeptonTagging)
- IsolatedTaus (used TaJetClustering)
- RefinedNJets (N = 2, 3, 4, 5, 6) (used LCFIPlus: JetClustering, JetVertexRefiner, FlavorTag)
- The ErrorFlow processor is applied to RefinedNJets to calculate covariance matrix for jets.

File size details:

|File No|# events|DST (MB)|DST, (MB)/event|mini-DST (MB)|mini-DST, (MB)/event|
|:---:|:---:|:---:|:---:|:---:|:---:|
|1|12500|663|0.053|285|0.0228|
|2|12500|663|0.053|285|0.0228|
|3|12500|660|0.0528|284|0.0227|
|4|11000|584|0.0531|251|0.0228|
|5|10500|761|0.0725|319|0.0304|
|6|10500|762|0.0726|319|0.0304|
|7|10500|762|0.0726|319|0.0304|
|8|10500|764|0.0728|320|0.0305|
|9|8000|584|0.073|245|0.0306|
|10|5500|680|0.1236|275|0.05|
|11|4500|551|0.1224|223|0.0496|
|12|10000|91|0.009|56|0.006|
|13|10000|595|0.0595|264|0.0264|
|14|10000|603|0.0603|271|0.0271|
