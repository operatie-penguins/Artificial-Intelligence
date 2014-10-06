//---------------------------------------------------------------------------

#ifndef CreatureH
#define CreatureH
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <math.h>
#include "HasXY.h"
#include "CreatureClassifier.h"

#define min(a,b) ((a)<(b)?(a):(b))

class Model;

class Creature : public HasXY {
  protected:
    float foodlevel;
    const static float hungerThreshold;
    const static float reproThreshold;
    float reproLevel;
    Creature* targetPair;
  public:

    Creature();
    bool maleGender;
    int deathIter;
    int pregnancy;
    float speed;

    virtual bool isHare() = 0;
    virtual bool isHungry();
    virtual bool isReadyForReproduction(); 
    virtual void onNextIter(Model* m);
    virtual void runTo(float aX, float aY);
    virtual void eat();
    virtual void copulate(Model* m);
    virtual void giveBirth(Model* m) = 0;
    virtual bool canDieOfHunger();

    void setTargetPair(Creature* p);
    Creature* getTargetPair();
};

#endif
