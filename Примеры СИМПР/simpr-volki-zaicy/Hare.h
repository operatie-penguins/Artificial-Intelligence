//---------------------------------------------------------------------------

#ifndef HareH
#define HareH
//---------------------------------------------------------------------------

#include "Creature.h"

class Food;
class Model;

class Hare : public Creature {

  protected:
    Food* targetFood;
    Creature* danger;

  public:
    virtual bool isHare();
    Hare();
    void setTargetFood(Food* f);
    Food* getTargetFood();
    void setDanger(Creature* d);
    Creature* getDanger();
    virtual void giveBirth(Model* m);
    virtual void copulate(Model* m);
    

};

#endif
