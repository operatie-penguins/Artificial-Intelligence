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

CONDITION(Ended, "�����?", 0, 0)
{
  if(!m) {
    return true;
  }
  return m->paused || m->creatures.size() == 0;
}

//---------------------------------------------------------------------------

CONDITION(Female, "�����?", 1, 0)
{
  return !(m->getCurrentCreature()->maleGender);
}

CONDITION(Pregnant, "���������?", 1, 1)
{
  return m->getCurrentCreature()->pregnancy > -1;
}

CONDITION(TimeToBear, "���� ������?", 1, 2)
{
  return m->getCurrentCreature()->pregnancy <= m->iterNum
         && m->getCurrentCreature()->pregnancy > -1;
}

//---------------------------------------------------------------------------

CONDITION(DeathTime, "���� �������?", 2, 0)
{
  if(m->getCurrentCreature()) {
    return (m->iterNum >= m->getCurrentCreature()->deathIter)
           || m->getCurrentCreature()->canDieOfHunger();
  }
  return false;
}

CONDITION(IsHare, "����?", 2, 1)
{
  return m->isHare();
}

CONDITION(IsWolf, "����?", 2, 2)
{
  return !m->isHare();
}

//---------------------------------------------------------------------------

CONDITION(HareDanger, "���������!?", 3, 0)
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

CONDITION(HareIsHungry, "�������?", 3, 1)
{
  return m->getCurrentCreature()->isHungry();
}

CONDITION(HareFoodChosen, "��� �������?", 3, 2)
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

CONDITION(HareCanSeeFood, "����� ���; ��� �����?", 3, 3)
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

CONDITION(HareFoodReached, "��� ����������?", 3, 4)
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

CONDITION(ReadyForReproduction, "����� � �����������?", 4, 0)
{
  return m->getCurrentCreature()->isReadyForReproduction();
}

CONDITION(PairChosen, "���� �������?", 4, 1)
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

CONDITION(CanSeePair, "����� ����; ���� �����?", 4, 2)
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

CONDITION(PairOK, "���� ��?", 4, 3)
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

CONDITION(HarePairReached, "���� ����������?", 4, 4)
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

CONDITION(WolfIsHungry, "�������?", 5, 0)
{
  return m->getCurrentCreature()->isHungry();
}

CONDITION(WolfCanSeeFood, "��� �����?", 5, 1)
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

CONDITION(WolfFoodReached, "��� ����������?", 5, 2)
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

