//---------------------------------------------------------------------------


#pragma hdrstop

#include <math.h>
#include "StartConfig.h"
#include "Wolf.h"
#include "Hare.h"
#include "Model.h"
#include "TChartForm.h"
#include "TMainForm.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool Model::isHare() {
  if(getCurrentCreature()) {
    return getCurrentCreature()->isHare();
  }
  return false;
}

//---------------------------------------------------------------------------

Creature* Model::getCurrentCreature() {
  if(creatureIdx < creatures.size()) {
    return creatures[creatureIdx];
  } else {
    return NULL;
  }
}

//---------------------------------------------------------------------------

Model::Model() {
  listener = NULL;
  for(int i=0; i<StartConfig::instance()->hareCount; i++) {
    Hare* h = new Hare();
    h->maleGender = (i % 2 == 1);
    creatures.push_back(h);
  }
  for(int i=0; i<StartConfig::instance()->wolfCount; i++) {
    Wolf* w = new Wolf();
    w->maleGender = (i % 2 == 1);
    creatures.push_back(w);
  }
  for(int i=0; i<StartConfig::instance()->foodCount; i++) {
    food.push_back(new Food());
  }
  creatureIdx = 0;
  iterNum = 0;
  paused = true;  
}

//---------------------------------------------------------------------------

void Model::nextCreature() {
  if(listener) {
    listener->onBeforeNextCreature();
  }
  if(creatureIdx < creatures.size()) {
    creatureIdx++;
  }
  if(creatureIdx == creatures.size()) {
    onBeginNextIter();
    creatureIdx = 0;
  }
}

//---------------------------------------------------------------------------

void Model::onBeginNextIter() {
  iterNum++;
  unsigned int creaturesCount = creatures.size();
  unsigned int hareCount = 0;
  unsigned int wolfCount = 0;
  for(unsigned int creatIdx = 0;
      creatIdx < creaturesCount;
      creatIdx++) {
    if(creatures[creatIdx]->isHare()) {
      hareCount++;
    } else {
      wolfCount++;
    }
    creatures[creatIdx]->onNextIter(this);
  }
  ChartForm->Series1->AddXY(iterNum, hareCount);
  ChartForm->Series3->AddXY(iterNum, wolfCount);

  int foodCount = food.size();
  if(random(1000) < StartConfig::instance()->foodGenProbabilityX1000
     && foodCount < StartConfig::instance()->foodLimit) {
    food.push_back(new Food());
  }
  ChartForm->Series2->AddXY(iterNum, foodCount);
  for(int i=0;
      i < foodCount;
      i++) {
    if(random(1000) < StartConfig::instance()->foodRespawnProbabilityX1000
       && foodCount < StartConfig::instance()->foodLimit) {
      Food* f = new Food();
      f->x = fabs(food[i]->x + random(1000000000)/1000000000.0*0.1 - 0.05);
      f->y = fabs(food[i]->y + random(1000000000)/1000000000.0*0.1 - 0.05);
      if(f->x < 1 && f->y < 1) {
        food.push_back(f);
      }
    }
  }
//  Sleep(1000);
  if(listener) {
    listener->onBeginNextIter();
  }
}

//---------------------------------------------------------------------------

void Model::setModelListener(Painter* apListener) {
  listener = apListener;
}

//---------------------------------------------------------------------------

float Model::distance(HasXY* a, HasXY* b) {
  return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}
//---------------------------------------------------------------------------

void Model::killCurrent() {
  unsigned int i = 0;
  i = creatureIdx;
  creatures.erase(creatures.begin() + creatureIdx);
  if(creatures.size() <= i) {
    creatureIdx = 0;
  } else {
    creatureIdx = i;
  }
}

