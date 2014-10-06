//---------------------------------------------------------------------------

#include <stdlib.h>

#pragma hdrstop

#include "Model.h"
#include "Creature.h"

const float Creature::hungerThreshold = 0.5;
const float Creature::reproThreshold = 0.5;

//---------------------------------------------------------------------------

#pragma package(smart_init)

Creature::Creature() {
  speed = 0.005;
  foodlevel = 0.5;
  reproLevel = 0;
  pregnancy = -1;
  targetPair = NULL;
  maleGender = (random(100) > 50);
}

bool Creature::isHungry() {
  return foodlevel < hungerThreshold;
}

void Creature::onNextIter(Model* m) {
  foodlevel -= 0.0025;
  reproLevel += 0.01;
}

void Creature::runTo(float aX, float aY) {
  float dx = aX - x;
  float dy = aY - y;
  float l = sqrt(dx*dx + dy*dy);
  if(l > 0) {
    if(l > speed) {
      dx = dx/l * speed;
      dy = dy/l * speed;
    }
    x = x + dx;
    y = y + dy;
    if(x<0) x = 0;
    if(x>1) x = 1;
    if(y<0) y = 0;
    if(y>1) y = 1;
  }
}

void Creature::eat() {
  foodlevel = min(1.0, foodlevel + 0.3);
}

void Creature::copulate(Model* m) {
  reproLevel = 0;
  targetPair = NULL;
  if(!maleGender) {
    pregnancy = m->iterNum + 25;
  }
}

bool Creature::isReadyForReproduction() {
  return reproLevel > reproThreshold
         && pregnancy == -1
         && !isHungry();
}

void Creature::setTargetPair(Creature* p) {
  targetPair = p;
}

Creature* Creature::getTargetPair() {
  return targetPair;
}

bool Creature::canDieOfHunger() {
  return foodlevel < 0;
}



