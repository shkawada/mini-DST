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

## Introduction

The purpose of mini-DST project is to provide a "minumum" set of data from fully-simulated MC samples.
When we perform physics analysis, we should use full detector simulation samples to make your analysis as realistic as possible if you are allowed to use such MC samples and you are familiar with it.
However, for beginners and theorists who are typically not familiar with how to handle with it, the full information of simulation/reconstruction is too much and too complex.
The mini-DST project is trying to reduce such complexitity, but mini-DST file still have useful information for the analysis.