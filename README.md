# mini-DST project

These codes are used to create mini-DST files.

Author: Shin-ichi Kawada (DESY)

Contact: shin-ichi.kawada[atmk]desy.de

Originally triggered by Snowmass 2021 comminity planning study, but also useful for beginners who usually don't have plenty amount of knowledge of high energy physics and detector simulation.
__These codes are under development. You can use them but your own risk. Your comments/ideas are welcome because this project is under discussion.__

# Things need to be done / Things need to be discussed

- Include isolated photon finder
  - will discuss with Junping for the development
- MCParticle should be MCParticlesSkimmed
  - In next production? Validation samples produced with v02-01 only contain MCParticle
- Simplify PandoraPFOs
  - Only put single number on PID info? How to do it?
- Simplify RecoMCTruthLink/MCTruthRecoLink. How to do it?
- How to add number of tracks/clusters (at the event header? at the header of PandoraPFOs?)?
- How to merge collections?

# Introduction

The purpose of mini-DST project is to provide a "minumum" set of data from fully-simulated (or SGV-based) MC samples.
When we perform physics analysis, we should use full detector simulation samples to make your analysis as realistic as possible.
Or, at least fast simulation-based MC samples are used in the physics analysis.
Usually, these MC samples have tons amount of information.
However, for beginners and theorists who are typically not familiar with how to handle with it, the full information of simulation/reconstruction is too much and too complex.
The mini-DST project is reducing such complexitity, and will provide smaller file size mini-DST which still have useful information for the analysis.

# Detail Description (WIP)

We have fully-simulated MC samples named DST file which contain all information and result of simulation and reconstruction.
In mini-DST project, we will remove complex collections and add other useful information like number of isolated objects, jets, and other variables.
In mini-DST file, the following collections are stored.
- PandoraPFOs, BCalRecoParticle (not merged yet)
- MCParticle (MCParticlesSkimmed in next production)
- PrimaryVertex, PrimaryVertex_RP
- RecoMCThuthLink, MCTruthRecoLink (kept full relation at this time being)

The following collections are added to the mini-DST file.
- event shape variables (used ThrustReconstruction, Sphere, Fox): these are stored at the header of PandoraPFOs
- IsolatedMuons, IsolatedElectrons (used IsolatedLeptonTagging, not tuned)
- IsolatedTaus (used TaJetClustering, not tuned)
- (IsolatedPhotons) (future)
- RefinedNJets (N = 2, 3, 4, 5, 6) (used LCFIPlus: JetClustering, JetVertexRefiner, FlavorTag, not tuned)

The ErrorFlow processor is applied to calculate covariance matrix for jets.