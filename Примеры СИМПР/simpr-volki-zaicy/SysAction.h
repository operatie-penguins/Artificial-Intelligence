//---------------------------------------------------------------------------

#ifndef SysActionH
#define SysActionH
//---------------------------------------------------------------------------

class Model;
#include "Registry.h" 

class SysAction {
  protected:
    char* ruText;
  public:
    SysAction(char* ruText) {
      this->ruText = ruText;
    }

    SysAction(char* ruText, int tableNum, int actNum) {
      this->ruText = ruText;
      Registry::instance()->registerAction(this, tableNum, actNum);
    }

    char* getRuText() {
      return ruText;
    }

    virtual void doAction(Model* m) = 0;
};

class DumbAction : public SysAction {
  public:
    DumbAction() : SysAction("***Dumb Action***") {
    }
    virtual void doAction(Model* m) {
    }
};

#define SYSACTION(className,argRuText,argTableNum,argActNum)     \
class className##Action : public SysAction {                     \
  public:                                                        \
    className##Action();                             \
    virtual void doAction(Model* m);                             \
} className##Action##Instance;                                   \
className##Action::className##Action()                           \
                  : SysAction(argRuText, argTableNum, argActNum) \
{ }                                                              \
void className##Action::doAction(Model* m)                       \

//---------------------------------------------------------------------------
#endif
