//---------------------------------------------------------------------------

#ifndef ConditionH
#define ConditionH
//---------------------------------------------------------------------------

class Model;
#include "Registry.h"

class Condition {
    char* ruText;
  public:
    Condition(char* ruText) {
      this->ruText = ruText;
    }

    Condition(char* ruText, int tableNum, int condNum) {
      this->ruText = ruText;
      Registry::instance()->registerCondition(this, tableNum, condNum);
    }

    char* getRuText() {
      return ruText;
    }

    virtual bool check(Model* m) = 0;
};

class DumbCondition : public Condition {
  public:
    DumbCondition() : Condition("***Dumb Condition***") {
    }
    virtual bool check(Model* m) {
      return true;
    }
};

#define CONDITION(className,argRuText,argTableNum,argCondNum)    \
class className##Condition : public Condition {                  \
  public:                                                        \
    className##Condition();                                      \
    virtual bool check(Model* m);                                \
} className##Condition##Instance;                                \
className##Condition::className##Condition()                     \
                  : Condition(argRuText, argTableNum, argCondNum)\
{ }                                                              \
bool className##Condition::check(Model* m)                       \

//---------------------------------------------------------------------------
#endif
