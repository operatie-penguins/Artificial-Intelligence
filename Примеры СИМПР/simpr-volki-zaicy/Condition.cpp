//---------------------------------------------------------------------------

#include <math.h>

#pragma hdrstop

#include "Hare.h"
#include "Wolf.h"
#include "Model.h"
#include "StartConfig.h"
#include "Condition.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

CONDITION(Ended, "Пауза?", 0, 0)
{
  if(!m) {
    return true;
  }
  return m->paused || m->creatures.size() == 0;
}

//---------------------------------------------------------------------------

CONDITION(Female, "Самка?", 1, 0)
{
  return !(m->getCurrentCreature()->maleGender);
}

CONDITION(Pregnant, "Беременна?", 1, 1)
{
  return m->getCurrentCreature()->pregnancy > -1;
}

CONDITION(TimeToBear, "Пора рожать?", 1, 2)
{
  return m->getCurrentCreature()->pregnancy <= m->iterNum
         && m->getCurrentCreature()->pregnancy > -1;
}

//---------------------------------------------------------------------------

CONDITION(DeathTime, "Пора умирать?", 2, 0)
{
  if(m->getCurrentCreature()) {
    return (m->iterNum >= m->getCurrentCreature()->deathIter)
           || m->getCurrentCreature()->canDieOfHunger();
  }
  return false;
}

CONDITION(IsHare, "Заяц?", 2, 1)
{
  return m->isHare();
}

CONDITION(IsWolf, "Волк?", 2, 2)
{
  return !m->isHare();
}

//---------------------------------------------------------------------------

CONDITION(HareDanger, "Опасность!?", 3, 0)
{
  Hare* h = dynamic_cast<Hare*>(m->getCurrentCreature());
  Creature* c = NULL;
  float dist = 5;
  for(vector<Creature*>::iterator it = m->creatures.begin();
      it != m->creatures.end();
      it++)
  {
    if(!(*it)->isHare()) {
      float newDist = m->distance(h, *it);
      if(newDist < dist && newDist < 0.2) {
        c = *it;
        dist = newDist;
      }
    }
  }
  h->setDanger(c);
  if(c) {
    return true;
  }
  return false;
}

CONDITION(HareIsHungry, "Голоден?", 3, 1)
{
  return m->getCurrentCreature()->isHungry();
}

CONDITION(HareFoodChosen, "Еда выбрана?", 3, 2)
{
  Hare* h = dynamic_cast<Hare*>(m->getCurrentCreature());
  if(!h->getTargetFood()) {
    return false;
  }
  for(vector<Food*>::iterator it = m->food.begin();
      it != m->food.end();
      it++)
  {
    if(*it == h->getTargetFood()) {
      return true;
    }
  }
  h->setTargetFood(NULL);
  return false;
}

CONDITION(HareCanSeeFood, "Поиск еды; еду видно?", 3, 3)
{
  Hare* h = dynamic_cast<Hare*>(m->getCurrentCreature());
  Food* f = NULL;
  float dist = 5;
  for(vector<Food*>::iterator it = m->food.begin();
      it != m->food.end();
      it++)
  {
    float newDist = m->distance(h, *it);
    if(newDist < dist) {
      f = *it;
      dist = newDist;
    }
  }
  h->setTargetFood(f);
  if(f) {
    return true;
  }
  return false;
}

CONDITION(HareFoodReached, "Еда достигнута?", 3, 4)
{
  Hare* h = dynamic_cast<Hare*>(m->getCurrentCreature());
  if(!h->getTargetFood()) {
    return false;
  }
  if(m->distance(h->getTargetFood(), h) < 0.001) {
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------

CONDITION(ReadyForReproduction, "Готов к размножению?", 4, 0)
{
  return m->getCurrentCreature()->isReadyForReproduction();
}

CONDITION(PairChosen, "Пара выбрана?", 4, 1)
{
  Creature* c = m->getCurrentCreature();
  if(!c->getTargetPair()) {
    return false;
  }
  for(vector<Creature*>::iterator it = m->creatures.begin();
      it != m->creatures.end();
      it++)
  {
    if(*it == c->getTargetPair()) {
      return true;
    }
  }
  c->setTargetPair(NULL);
  return false;
}

CONDITION(CanSeePair, "Поиск пары; пару видно?", 4, 2)
{
  Creature* h = m->getCurrentCreature();
  Creature* p = NULL;
  float dist = 5;
  for(vector<Creature*>::iterator it = m->creatures.begin();
      it != m->creatures.end();
      it++)
  {
    float newDist = m->distance(h, *it);
    if(newDist < dist
        && (*it)->maleGender != h->maleGender
        && (*it)->isHare() == h->isHare()
        && (*it)->isReadyForReproduction()
        && (((*it)->getTargetPair() == NULL)
            || ((*it)->getTargetPair() == h))) {
      p = *it;
      dist = newDist;
    }
  }
  h->setTargetPair(p);
  if(p) {
    p->setTargetPair(h);
    return true;
  }
  return false;
}

CONDITION(PairOK, "Пара ОК?", 4, 3)
{
  Creature* h = m->getCurrentCreature();
  if(!h->getTargetPair()) {
    return false;
  }
  if(h->getTargetPair()->getTargetPair() != h) {
    return false;
  }
  if(!h->getTargetPair()->isReadyForReproduction()) {
    return false;
  }
  return true;
}

CONDITION(HarePairReached, "Пара достигнута?", 4, 4)
{
  Creature* h = m->getCurrentCreature();
  if(!h->getTargetPair()) {
    return false;
  }
  if(m->distance(h->getTargetPair(), h) < 0.001) {
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------

CONDITION(WolfIsHungry, "Голоден?", 5, 0)
{
  return m->getCurrentCreature()->isHungry();
}

CONDITION(WolfCanSeeFood, "Еду видно?", 5, 1)
{
  Wolf* w = dynamic_cast<Wolf*>(m->getCurrentCreature());
  Creature* c = NULL;
  float dist = 5;
  for(vector<Creature*>::iterator it = m->creatures.begin();
      it != m->creatures.end();
      it++)
  {
    if((*it)->isHare()) {
      float newDist = m->distance(w, *it);
      if(newDist < dist) {
        c = *it;
        dist = newDist;
      }
    }
  }
  w->setTargetFood(c);
  if(c) {
    return true;
  }
  return false;
}

CONDITION(WolfFoodReached, "Еда достигнута?", 5, 2)
{
  Wolf* w = dynamic_cast<Wolf*>(m->getCurrentCreature());
  if(!w->getTargetFood()) {
    return false;
  }
  if(m->distance(w->getTargetFood(), w) < StartConfig::instance()->hareSpeed) {
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------

