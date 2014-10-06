//---------------------------------------------------------------------------

#ifndef WolfH
#define WolfH
//---------------------------------------------------------------------------

#include "Creature.h"

class Wolf : public Creature {
    Creature* targetFood;

  public:
    virtual bool isHare() {
      return false;
    }

    Wolf();

    void setTargetFood(Creature* c);
    virtual void eat();
    Creature* getTargetFood();

    virtual void giveBirth(Model* m);
    virtual void copulate(Model* m);

};

#endif
