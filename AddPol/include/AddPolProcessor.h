#ifndef AddPolProcessor_h
#define AddPolProcessor_h 1

#include <string>
#include <marlin/Processor.h>
#include <lcio.h>

using namespace lcio;
using namespace marlin;
using namespace std;

class AddPolProcessor : public Processor{
 public:
  virtual Processor* newProcessor() { return new AddPolProcessor; }
  AddPolProcessor();
  virtual void init();
  virtual void processRunHeader( LCRunHeader *run );
  virtual void processEvent( LCEvent *evt );
  virtual void check( LCEvent *evt );
  virtual void end();

 protected:
  int _nRun;
  int _nEvt;
  string _inputName;
};
#endif
