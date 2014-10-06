//---------------------------------------------------------------------------


#pragma hdrstop

#include "StartConfig.h"
#include "Model.h"
#include "Wolf.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Wolf::Wolf() : Creature() {
  speed = StartConfig::instance()->wolfSpeed;
  deathIter = StartConfig::instance()->wolfLifeLength;
  targetFood = NULL;
}

void Wolf::setTargetFood(Creature* c) {
  targetFood = c;
}

Creature* Wolf::getTargetFood() {
  return targetFood;
}

void Wolf::giveBirth(Model* m) {
  int children = random(StartConfig::instance()->wolfSpawnFactor)+1;
  for(int i=0; i<children; i++) {
    Wolf* child = new Wolf();
    child->x = x;
    child->y = y;
    child->deathIter = m->iterNum + StartConfig::instance()->wolfLifeLength;
    m->creatures.push_back((Creature*)child);
  }
}

void Wolf::eat() {
  foodlevel = min(1.0, foodlevel + 1.0);
}

void Wolf::copulate(Model* m) {
  reproLevel = 0;
  targetPair = NULL;
  if(!maleGender) {
    pregnancy = m->iterNum + StartConfig::instance()->wolfPregnancyLength;
  }
}



