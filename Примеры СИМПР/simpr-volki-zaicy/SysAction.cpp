//---------------------------------------------------------------------------


#pragma hdrstop

#include "Hare.h"
#include "Wolf.h"
#include "Model.h"
#include "TMainForm.h"
#include "SysAction.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

SYSACTION(DoNothing, "��������", 0, 0)
{
}

//---------------------------------------------------------------------------

SYSACTION(GiveBirth, "������", 1, 0)
{
  m->getCurrentCreature()->giveBirth(m);
  m->getCurrentCreature()->pregnancy = -1;
}

//---------------------------------------------------------------------------

SYSACTION(HareDie, "�������", 2, 0)
{
  m->killCurrent();
}

//---------------------------------------------------------------------------

SYSACTION(HareGoToFood, "���� � ���", 3, 0)
{
  Hare* h = dynamic_cast<Hare*>(m->getCurrentCreature());
  if(h->getTargetFood()) {
    h->runTo(h->getTargetFood()->x, h->getTargetFood()->y);
  }
}

SYSACTION(HareEat, "����", 3, 1) {
  Hare* h = dynamic_cast<Hare*>(m->getCurrentCreature());
  for(vector<Food*>::iterator it = m->food.begin();
      it != m->food.end();
      it++) {
    if(*it == h->getTargetFood()) {
      m->food.erase(it);
      h->eat();
      h->setTargetFood(NULL);
      break;
    }
  }
}

SYSACTION(HareWanderByTable2, "������� ������", 3, 2)
{

}

SYSACTION(NextCreatureTable2, "���������", 3, 3)
{
  m->nextCreature();
}

SYSACTION(HareRunAway, "�������!", 3, 4)
{
  Hare* h = dynamic_cast<Hare*>(m->getCurrentCreature());
  if(h->getDanger()) {
    float toX = h->x - h->getDanger()->x;
    float toY = h->y - h->getDanger()->y;
    float l = sqrt(toX*toX + toY*toY);
    if(l > 0) {
      toX = toX/l * h->speed;
      toY = toY/l * h->speed;
      toX += h->x;
      toY += h->y;
    }

    if(toX >= 1) toX = 0.9;
    if(toY >= 1) toY = 0.9;
    if(toX <= 0) toX = 0.1;
    if(toY <= 0) toY = 0.1;
    h->runTo(toX, toY);
    h->setTargetFood(NULL);
    h->setTargetPair(NULL);
  }
}

//---------------------------------------------------------------------------

SYSACTION(GoToPair, "���� � ����", 4, 0)
{
  Creature* h = m->getCurrentCreature();
  if(h->getTargetPair()) {
    h->runTo(h->getTargetPair()->x, h->getTargetPair()->y);
  }

}

SYSACTION(Reproduce, "������������", 4, 1)
{
  Creature* h = m->getCurrentCreature();
  if(h->getTargetPair()) {
    Creature* p = h->getTargetPair();
    h->copulate(m);
    p->copulate(m);
  }
  else {
    h->setTargetPair(NULL);
  }
}

SYSACTION(WanderByTable3, "������� ������", 4, 2)
{

}

SYSACTION(DropPair, "�������� ����", 4, 3)
{
  Creature* h = m->getCurrentCreature();
  h->setTargetPair(NULL);
}

SYSACTION(CreatureTable3, "���������", 4, 4)
{
  m->nextCreature();
}

//---------------------------------------------------------------------------


SYSACTION(WolfGoToFood, "���� � ���", 5, 0)
{
  Wolf* w = dynamic_cast<Wolf*>(m->getCurrentCreature());
  if(w->getTargetFood()) {
    w->runTo(w->getTargetFood()->x, w->getTargetFood()->y);
  }
}

SYSACTION(WolfEat, "����", 5, 1) {
  Wolf* w = dynamic_cast<Wolf*>(m->getCurrentCreature());
  for(vector<Creature*>::iterator it = m->creatures.begin();
      it != m->creatures.end();
      it++) {
    if(*it == w->getTargetFood()) {
      m->creatures.erase(it);
      w->eat();
      break;
    }
  }
  w->setTargetFood(NULL);
}

SYSACTION(WolfWanderByTable5, "������� ������", 5, 2)
{

}

SYSACTION(NextCreatureTable5, "���������", 5, 3)
{
  m->nextCreature();
}
