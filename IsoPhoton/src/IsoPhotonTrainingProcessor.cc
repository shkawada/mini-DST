// *****************************************************
// Processor for training isolated photons selection
//                        ----Junping & Shin-ichi
// *****************************************************
#include "IsoPhotonTrainingProcessor.h"
#include <iostream>
#include <sstream>
#include <iomanip>

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <IMPL/LCCollectionVec.h>
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/ReconstructedParticleImpl.h>
#include <EVENT/Cluster.h>
#include <UTIL/LCTypedVector.h>
#include <EVENT/Track.h>
#include <UTIL/LCRelationNavigator.h>
#include <EVENT/ParticleID.h>
#include <marlin/Exceptions.h>
#include <EVENT/Vertex.h>

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"

#include "TROOT.h"
#include "TFile.h"
#include "TH1D.h"
#include "TNtupleD.h"
#include "TVector3.h"
#include "TMath.h"
#include "TLorentzVector.h"

#include "Utilities.h"

//#define __SINGLEP__

using namespace lcio ;
using namespace marlin ;
using namespace std;

using namespace isolep;

IsoPhotonTrainingProcessor aIsoPhotonTrainingProcessor ;


IsoPhotonTrainingProcessor::IsoPhotonTrainingProcessor() : Processor("IsoPhotonTrainingProcessor") {
  
  // modify processor description
  _description = "IsoPhotonTrainingProcessor does whatever it does ..." ;
  

  // register steering parameters: name, description, class-variable, default value

  registerInputCollection( LCIO::MCPARTICLE,
			   "InputMCParticlesCollection" , 
			   "Name of the MCParticle collection"  ,
			   _colMCP ,
			   std::string("MCParticlesSkimmed") ) ;

  registerInputCollection( LCIO::LCRELATION,
			   "InputMCTruthLinkCollection" , 
			   "Name of the MCTruthLink collection"  ,
			   _colMCTL ,
			   std::string("RecoMCTruthLink") ) ;

  registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			   "InputPandoraPFOsCollection" , 
			   "Name of the PandoraPFOs collection"  ,
			   _colPFOs ,
			   std::string("PandoraPFOs") ) ;

  registerProcessorParameter("MCDebugging" ,
			     "set true if you want to check generator information",
			     _mcdebug,
			     bool(false)
			     );

}

void IsoPhotonTrainingProcessor::init() { 

  streamlog_out(DEBUG) << "   init called  " 
		       << std::endl ;
  
  
  // usually a good idea to
  printParameters() ;

  _nRun = 0 ;
  _nEvt = 0 ;
  
}

void IsoPhotonTrainingProcessor::processRunHeader( LCRunHeader* run) { 

  _nRun++ ;
} 

void IsoPhotonTrainingProcessor::processEvent( LCEvent * evt ) { 

    
  // this gets called for every event 
  // usually the working horse ...
  _nEvt++;

  Double_t fCosConeCut = 0.98;   // the angle of cone around the direction of pfo
  Double_t fCosLargeConeCut = 0.95; // angel of large cone around the pfo

  TDirectory *last = gDirectory;
  gFile->cd("/");

  cerr << endl << "Hello, MVA Photon Training! Event No. " << _nEvt << endl;

  // -- Get the MCTruth Linker --
  LCCollection *colMCTL = evt->getCollection(_colMCTL);
  LCRelationNavigator *navMCTL = new LCRelationNavigator(colMCTL);

  // -- Read out MC information --  
  LCCollection *colMC = evt->getCollection(_colMCP);
  if (!colMC) {
    std::cerr << "No MC Collection Found!" << std::endl;
    throw marlin::SkipEventException(this);
  }
  if (_mcdebug) {
    mcDebug(colMC);
  }

  // -- Read out PFO information --
  LCCollection *colPFO = evt->getCollection(_colPFOs);
  if (!colPFO) {
    std::cerr << "No PFO Collection Found!" << std::endl;
    throw marlin::SkipEventException(this);
  }

  static TNtupleD *hPfo = 0;
  if (!hPfo) {
    stringstream tupstr_pfo;
    tupstr_pfo << "energy:costheta:mcpdg:motherpdg:deltae:mmotherpdg" << ":"
	       << "mcoriginal:coneec:coneen:coslarcon:energyratio"    << ":"
	       << "iov:isim"
	       << ends;
    hPfo = new TNtupleD("hPfo","",tupstr_pfo.str().data());
  }

  // loop all the PFOs
  Int_t nPFOs = colPFO->getNumberOfElements();
  for (Int_t i=0;i<nPFOs;i++) {
    ReconstructedParticle *recPart = dynamic_cast<ReconstructedParticle*>(colPFO->getElementAt(i));
    Int_t itype = recPart->getType();
    if (itype != 22) continue;  // Pandora Photon ID == 22
    LCObjectVec vecMCTL = navMCTL->getRelatedToObjects(recPart);
    FloatVec vecWgtMCTL = navMCTL->getRelatedToWeights(recPart);
    Int_t mcpdg,motherpdg,mmotherpdg;
    Double_t mcwgt=0.;
    mcpdg = 0;
    motherpdg = -99999;
    mmotherpdg = -99999;
    Double_t deltaE = -99999.;
    Int_t mcoriginal = 0;
    Int_t iOverlay = 0;
    Int_t iCreatedInSim = 0;
    if (vecMCTL.size() > 0) {
      //      MCParticle *mcPart = dynamic_cast<MCParticle *>(vecMCTL[0]);
      MCParticle *mcPart = getMCParticle(recPart,colMCTL,mcwgt);      
      if (!mcPart) continue;
      if (mcPart->isOverlay()) iOverlay = 1;
      if (mcPart->isCreatedInSimulation()) iCreatedInSim = 1;
      mcpdg = mcPart->getPDG();
      //      mcwgt = vecWgtMCTL[0];
      deltaE = mcPart->getEnergy()-recPart->getEnergy();
      mcoriginal = getOriginalPDG(mcPart);
      motherpdg = 0;
      if (mcPart->getParents().size() != 0) {
	MCParticle *motherPart = mcPart->getParents()[0];
	motherpdg = motherPart->getPDG();
	mmotherpdg = 0;
	if (motherPart->getParents().size() != 0) {
	  MCParticle *mmotherPart = motherPart->getParents()[0];
	  mmotherpdg = mmotherPart->getPDG();
	}
      }
    }
    Double_t energy = recPart->getEnergy();
    Double_t charge = recPart->getCharge();
    TVector3 momentum = TVector3(recPart->getMomentum());
    Double_t momentumMagnitude = momentum.Mag();
    Double_t cosTheta = momentum.CosTheta();
    //get cone information
    Double_t coneEnergy0[3] = {0.,0.,0.};
    Double_t pLargeCone[4]  = {0.,0.,0.,0.};
    Double_t _cosConeSmall = fCosConeCut;
    Double_t _cosConeLarge = fCosLargeConeCut;
    getConeEnergy(recPart,colPFO,_cosConeSmall,coneEnergy0,_cosConeLarge,pLargeCone);
    Double_t coneEnergy = coneEnergy0[0];
    Double_t coneEN     = coneEnergy0[1];
    Double_t coneEC     = coneEnergy0[2];
    TLorentzVector lortzLargeCone = TLorentzVector(pLargeCone[0],pLargeCone[1],pLargeCone[2],pLargeCone[3]);
    TVector3 momentumLargeCone = lortzLargeCone.Vect();
    Double_t cosThetaWithLargeCone = 1.;
    if (momentumLargeCone.Mag() > 0.0000001) {
      cosThetaWithLargeCone = momentum.Dot(momentumLargeCone)/momentumMagnitude/momentumLargeCone.Mag();
    }
    Double_t energyRatioWithLargeCone = energy/(energy+lortzLargeCone.E());

    Double_t data[20];
    data[0] = energy;
    data[1] = cosTheta;
    data[2] = mcpdg;
    data[3] = motherpdg;
    data[4] = deltaE;
    data[5] = mmotherpdg;
    data[6] = mcoriginal;
    data[7] = coneEC;
    data[8] = coneEN;
    data[9] = cosThetaWithLargeCone;
    data[10]= energyRatioWithLargeCone;
    data[11]= iOverlay;
    data[12]= iCreatedInSim;
    hPfo->Fill(data);
  }

  //-- note: this will not be printed if compiled w/o MARLINDEBUG=1 !

  streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
  		       << "   in run:  " << evt->getRunNumber() 
  		       << std::endl ;

  //  _nEvt ++ ;

  last->cd();
}



void IsoPhotonTrainingProcessor::check( LCEvent * evt ) { 
  // nothing to check here - could be used to fill checkplots in reconstruction processor
}


void IsoPhotonTrainingProcessor::end(){ 

  cerr << "IsoPhotonTrainingProcessor::end()  " << name() 
       << " processed " << _nEvt << " events in " << _nRun << " runs "
       << endl ;
  
}
