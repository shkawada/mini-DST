#ifndef __CINT__ 
#include "lcio.h"
#include "IO/LCReader.h"
#include "IOIMPL/LCFactory.h"
#include "EVENT/LCCollection.h"
#include "EVENT/ReconstructedParticle.h"
#include "EVENT/LCEvent.h"
#include "UTIL/LCTOOLS.h"
#include "UTIL/LCIterator.h"
#endif

#include "TH1F.h"
#include "TLorentzVector.h"

/*
put this into your .rootlogon.C file
{
 gInterpreter->AddIncludePath("$LCIO");
 gSystem->Load("${LCIO}/lib/liblcio.so");
 gSystem->Load("${LCIO}/lib/liblcioDict.so");
}
for the LCIO API documentation see:
http://lcio.desy.de/v02-09/doc/doxygen_api/html/index.html
*/

using namespace lcio;

//Example script for couting number of isolated objects

void count( const char* FILEN, TString outname = "count" ){
  int nEvents = 0;
  int maxEvt = 100000; // change as needed

  //create histogram
  int nbin = 6;
  float xmin = 0;
  float xmax = 6;
  const int nhistos = 4;

  TH1F* hn[nhistos]; //0 = mu, 1 = e, 2 = tau, 3 = photon
  hn[0] = new TH1F(" hnmu"    , ";N; ; ", nbin, xmin, xmax );
  hn[1] = new TH1F(" hne"     , ";N; ; ", nbin, xmin, xmax );
  hn[2] = new TH1F(" hntau"   , ";N; ; ", nbin, xmin, xmax );
  hn[3] = new TH1F(" hnphoton", ";N; ; ", nbin, xmin, xmax );
  TString legtext[nhistos];
  legtext[0] = "N_{#mu}";
  legtext[1] = "N_{e}";
  legtext[2] = "N_{#tau}";
  legtext[3] = "N_{#gamma}";

  //collection to use:
  // ALWAYS read also PandoraPFOs / PFOs when reading IsolatedX collections!
  const char* muonColName = "IsolatedMuons";
  const char* electronColName = "IsolatedElectrons";
  const char* tauColName = "IsolatedTaus";
  const char* photonColName = "IsolatedPhotons";
  //full & SGV
  const char* pfoColName = "PandoraPFOs";
  //bool isDelphes = false;
  //delphes2lcio
  //const char* pfoColName = "PFOs";
  //bool isDelphes = true;

  IO::LCReader* lcReader = IOIMPL::LCFactory::getInstance()->createLCReader();
  lcReader->setReadCollectionNames( { pfoColName, muonColName, electronColName, tauColName, photonColName } );
  lcReader->open( FILEN );

  EVENT::LCEvent* evt;

  //the event loop
  while( ( evt = lcReader->readNextEvent() ) != 0 && nEvents++ < maxEvt ){
    LCIterator<ReconstructedParticle> muons( evt, muonColName );
    int n0 = muons.size();
    hn[0]->Fill( n0 );
    LCIterator<ReconstructedParticle> electrons( evt, electronColName );
    int n1 = electrons.size();
    hn[1]->Fill( n1 );
    LCIterator<ReconstructedParticle> taus( evt, tauColName );
    int n2 = taus.size();
    hn[2]->Fill( n2 );
    LCIterator<ReconstructedParticle> photons( evt, photonColName );
    int n3 = photons.size();
    hn[3]->Fill( n3 );

  }

  gStyle->SetOptStat(10);

  TCanvas* c1 = new TCanvas("count plots","count plot",800,600);
  TLegend *leg = new TLegend(0.7,0.6,0.9,0.9);
  hn[0]->SetLineColor(kBlack);
  hn[1]->SetLineColor(kRed);
  hn[2]->SetLineColor(kBlue);
  hn[3]->SetLineColor(kGreen);

  for( int ihist = 0; ihist < nhistos; ihist++ ){
    hn[ihist]->Draw("same");
    leg->AddEntry(hn[ihist], legtext[ihist], "F");
  }
  leg->Draw();

  TString outnamepdf = outname + ".pdf";
  c1->SaveAs(outnamepdf);
  TString outnameRoot  = outname + ".root";
  TFile outputFile (outnameRoot,"RECREATE");

  for( int ihist = 0; ihist < nhistos; ihist++ ){
    hn[ihist]->Write();
  }
  outputFile.Close();

  std::cout << std::endl;
  std::cout << "read file: " << FILEN << std::endl;
  std::cout << nEvents << " events read from the file." << std::endl;

  lcReader->close();
  delete lcReader;
}
