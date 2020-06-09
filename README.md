# mini-DST project

These codes are used to create mini-DST files.

Author: Shin-ichi Kawada (DESY)

Contact: shin-ichi.kawada[atmk]desy.de

Originally triggered by Snowmass 2021 comminity planning study, but also useful for beginners who usually don't have plenty amount of knowledge of high energy physics and detector simulation.
__These codes are under development. You can use them but your own risk. Your comments/ideas are welcome because this project is under discussion.__

# Things need to be done / Things need to be discussed

- Include Yan's PandoraIsolatedPhotonFinder (not in master branch, but use develop branch)
  - Now suffering to include due to compile error
- MCParticle should be MCParticlesSkimmed
  - In next production? Validation samples produced with v02-01 only contain MCParticle
- Simplify PandoraPFOs
  - Only put single number on PID info. How to do it?
- Simplify RecoMCTruthLink/MCTruthRecoLink. How to do it?
- Which collections should be kept in mini-DST file?
- How to add number of tracks/clusters (probably at the event header)?
- Providing macro or library to read mini-DST file and produce ROOT file

# Introduction

The purpose of mini-DST project is to provide a "minumum" set of data from fully-simulated MC samples.
When we perform physics analysis, we should use full detector simulation samples to make your analysis as realistic as possible if you are allowed to use such MC samples and you are familiar with it.
However, for beginners and theorists who are typically not familiar with how to handle with it, the full information of simulation/reconstruction is too much and too complex.
The mini-DST project is reducing such complexitity, but mini-DST file still have useful information for the analysis.

# Detail Description (WIP)

We have fully-simulated MC samples named DST file which contain all information and result of simulation and reconstruction.
In mini-DST project, we will remove complex collections and add other useful information like number of isolated objects, jets, and other variables.
In mini-DST file, the following collections are stored.
- PandoraPFOs
- MCParticle (MCParticlesSkimmed)
- PrimaryVertex, PrimaryVertex_RP
- RecoMCThuthLink, MCTruthRecoLink

The following collections are added to the mini-DST file.
- IsolatedMuons, IsolatedElectrons
- IsolatedTaus
- (IsolatedPhotons)
- RefinedNJets (N = 2, 3, 4, 5, 6)

The ErrorFlow processor is added to calculate covariance matrix for jets.