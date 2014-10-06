//---------------------------------------------------------------------------

#include <stdlib.h>

#pragma hdrstop

#include "StartConfig.h"
#include "Model.h"
#include "Food.h"
#include "Hare.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool Hare::isHare() {
  return true;
}

Hare::Hare() : Creature() {
  speed = StartConfig::instance()->hareSpeed;
  deathIter = StartConfig::instance()->hareLifeLength;
  targetFood = NULL;
  danger = NULL;
}

void Hare::setTargetFood(Food* f) {
  targetFood = f;
}

Food* Hare::getTargetFood() {
  return targetFood;
}

void Hare::setDanger(Creature* d) {
  danger = d;
}

Creature* Hare::getDanger() {
  return danger;
}

void Hare::giveBirth(Model* m) {
  int children = random(StartConfig::instance()->hareSpawnFactor)+1;
  for(int i=0; i<children; i++) {
    Hare* child = new Hare();
    child->x = x;
    child->y = y;
    child->deathIter = m->iterNum + StartConfig::instance()->hareLifeLength;
    m->creatures.push_back((Creature*)child);
  }
}

void Hare::copulate(Model* m) {
  reproLevel = 0;
  targetPair = NULL;
  if(!maleGender) {
    pregnancy = m->iterNum + StartConfig::instance()->harePregnancyLength;
  }
}


