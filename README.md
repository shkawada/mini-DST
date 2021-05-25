# mini-DST project

These codes are used to create mini-DST files. The details of mini-DST can be found at the [arXiv](https://arxiv.org/abs/2105.08622).

Author: Shin-ichi Kawada (DESY)

Contact: shin-ichi.kawada[atmk]desy.de

Originally triggered by Snowmass 2021 comminity planning study, but also useful for beginners who usually don't have plenty amount of knowledge of high energy physics and detector simulation.
__These codes are under development. You can use them but your own risk. Your comments/ideas are welcome because this project is under discussion.__

The full information of v0 mini-DST and v1 mini-DST are available under v0/ and v1/ directory.

# Things need to be done / Things need to be discussed

- MCParticle should be MCParticlesSkimmed
- Simplify PandoraPFOs
  - Only put single number on PID info? How to do it?
- Impact parameter?
- Simplify RecoMCTruthLink/MCTruthRecoLink. How to do it?
- How to add number of tracks/clusters (at the event header? at the header of PandoraPFOs?)?
- How to merge collections?

# Introduction

The purpose of mini-DST project is to provide a "minumum" set of data from fully-simulated (or SGV-based) MC samples.
When we perform physics analysis, we should use full detector simulation samples to make your analysis as realistic as possible, or, at least, fast simulation-based MC samples (like SGV-based and Delphes-based) are need to be used in the physics analysis.
Usually, these MC samples have tons amount of information.
However, for beginners, newcomers, and theorists who are typically not familiar with how to handle with it, the full information of simulation/reconstruction are too much and too complex.
The purpose of mini-DST project is try to reduce such complexity for beginners.
In mini-DST project, we will produce mini-DST files which have smaller file size but still contain useful information for physics analysis.

# Detail Description

We have fully-simulated MC samples named DST file which contain all information and result of simulation and reconstruction.
In mini-DST file, the complex collections are removed, and useful information are added as the high-level object, e.g.; number of isolated electrons, muons, jets,...

In mini-DST file, the following collections are kept from original DST file.
- PandoraPFOs, BCalRecoParticle (not merged yet)
- MCParticle (MCParticlesSkimmed in next production)
- PrimaryVertex, PrimaryVertex_RP
- RecoMCThuthLink, MCTruthRecoLink (kept full relation so far)

The following collections/variables are added as the high-level object to the mini-DST file.
- event shape variables (used ThrustReconstruction, Sphere, Fox): these are stored at the event header of PandoraPFOs
- IsolatedMuons, IsolatedElectrons (used IsolatedLeptonTagging)
- IsolatedTaus (used TaJetClustering)
- IsolatedPhotons (used IsolatedPhotonTaggingProcessor, not yet for MVA-based version)
- RefinedNJets (N = 2, 3, 4, 5, 6) (N can be increased to 10 for higher center-of-mass energy) (used LCFIPlus: JetClustering, JetVertexRefiner, FlavorTag)
- ErrorFlow is applied to RefinedNJets to calculate covariance matrix for jets.