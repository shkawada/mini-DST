#include "AddPolProcessor.h"
#include <string>

using namespace lcio;
using namespace marlin;
using namespace std;

AddPolProcessor aAddPolProcessor;

AddPolProcessor::AddPolProcessor() : Processor( "AddPolProcessor" ){
  registerProcessorParameter( "InputName",
			      "Name of input slcio file",
			      _inputName,
			      std::string( "input" )
			     );
}

void AddPolProcessor::init(){
  _nRun = 0;
  _nEvt = 0;
}

void AddPolProcessor::processRunHeader( LCRunHeader *run ){
  _nRun++;
}

void AddPolProcessor::processEvent( LCEvent *evt ){
  _nEvt++;

  std::string filename = _inputName.c_str();
  bool finish = false; //for speed boost

  int pol1 = filename.find( "eL.pL" );
  if( pol1 != std::string::npos ){
    evt->parameters().setValue( "beamPol1", float(-1) );
    evt->parameters().setValue( "beamPol2", float(-1) );
    finish = true;
  }
  if( finish == false ){
    int pol2 = filename.find( "eL.pR" );
    if( pol2 != std::string::npos ){
      evt->parameters().setValue( "beamPol1", float(-1) );
      evt->parameters().setValue( "beamPol2", float(1) );
      finish = true;
    }
  }
  if( finish == false ){
    int pol3 = filename.find( "eR.pL" );
    if( pol3 != std::string::npos ){
      evt->parameters().setValue( "beamPol1", float(1) );
      evt->parameters().setValue( "beamPol2", float(-1) );
      finish = true;
    }
  }
  if( finish == false ){
    int pol4 = filename.find( "eR.pR" );
    if( pol4 != std::string::npos ){
      evt->parameters().setValue( "beamPol1", float(1) );
      evt->parameters().setValue( "beamPol2", float(1) );
      finish = true;
    }
  }
}

void AddPolProcessor::check( LCEvent *evt ){
}

void AddPolProcessor::end(){
}
