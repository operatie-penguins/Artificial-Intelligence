//---------------------------------------------------------------------------


#pragma hdrstop

#include "Condition.h"
#include "SysAction.h"
#include "Registry.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Registry* Registry::instance() {
  static Registry inst;
  return &inst;
}
//---------------------------------------------------------------------------


void Registry::registerAction(SysAction* act,
                              unsigned int tableNum,
                              unsigned int actionNum) {
  while(tablesAct.size() < tableNum + 1) {
    tablesAct.push_back(*(new ActionVector()));
  }
  while(tablesAct[tableNum].size() < actionNum + 1) {
    SysAction* dumb = new DumbAction();
    tablesAct[tableNum].push_back(dumb);
  }
  tablesAct[tableNum][actionNum] = act;
}
//---------------------------------------------------------------------------


void Registry::registerCondition(Condition* cond,
                                 unsigned int tableNum,
                                 unsigned int condNum) {
  while(tablesCond.size() < tableNum + 1) {
    tablesCond.push_back(*(new ConditionVector()));
  }
  while(tablesCond[tableNum].size() < condNum + 1) {
    Condition* dumb = new DumbCondition();
    tablesCond[tableNum].push_back(dumb);
  }
  tablesCond[tableNum][condNum] = cond;
}
//---------------------------------------------------------------------------


Condition* Registry::getCondition(unsigned int tableNum, unsigned int condNum) {
  if(tableNum >= tablesCond.size()) {
    return NULL;
  }
  if(condNum >= tablesCond[tableNum].size()) {
    return NULL;
  }
  return tablesCond[tableNum][condNum];
}
//---------------------------------------------------------------------------


SysAction* Registry::getAction(unsigned int tableNum, unsigned int actNum) {
  if(tableNum >= tablesAct.size()) {
    return NULL;
  }
  if(actNum >= tablesAct[tableNum].size()) {
    return NULL;
  }
  return tablesAct[tableNum][actNum];
}
//---------------------------------------------------------------------------


