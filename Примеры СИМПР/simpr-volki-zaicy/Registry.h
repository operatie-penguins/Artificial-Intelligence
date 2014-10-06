//---------------------------------------------------------------------------

#ifndef RegistryH
#define RegistryH
//---------------------------------------------------------------------------

#include <system.hpp>
#include <vector>

using namespace std;

class SysAction;
typedef vector<SysAction*> ActionVector;

class Condition;
typedef vector<Condition*> ConditionVector;

typedef vector<ActionVector> ActionTables;
typedef vector<ConditionVector> ConditionTables;

class Registry {
  private:
    ConditionTables tablesCond;
    ActionTables tablesAct;

  public:
    Registry() {
    }
/*
      TableVector* t1_cond = new TableVector;
      t1_cond->push_back("");
      t1_cond->push_back("Закончили?");
      tablesCond.push_back(*t1_cond);
      
      TableVector* t2_cond = new TableVector;
      t2_cond->push_back("");
      t2_cond->push_back("Заяц?");
      tablesCond.push_back(*t2_cond);

      TableVector* t3_cond = new TableVector;
      t3_cond->push_back("");
      t3_cond->push_back("Голоден?");
      t3_cond->push_back("Еда видна?");
      tablesCond.push_back(*t3_cond);

      TableVector* t1_act = new TableVector;
      tablesAct.push_back(*t1_act);

      TableVector* t2_act = new TableVector;
      tablesAct.push_back(*t2_act);

      TableVector* t3_act = new TableVector;
      t3_act->push_back("");
      t3_act->push_back("Идти есть");
      t3_act->push_back("Бродить в округе");
      t3_act->push_back("Следующий");
      tablesAct.push_back(*t3_act);
    }
    
    char* getString(unsigned int tableNum,
                    unsigned int condOrActNum,
                    unsigned int isAction)
    {
      if(isAction)
      {
        if(tableNum >= tablesAct.size())
        {
          return "Неизвестная таблица для действия";
        }
        if(condOrActNum >= tablesAct[tableNum].size())
        {
          return "Неизвестное действие";
        }
        return tablesAct[tableNum][condOrActNum];
      }
      else
      {
        if(tableNum >= tablesCond.size())
        {
          return "Неизвестная таблица для условия";
        }
        if(condOrActNum >= tablesCond[tableNum].size())
        {
          return "Неизвестное условие";
        }
        return tablesCond[tableNum][condOrActNum];
      }
    }
*/
    void registerAction(SysAction* act,
                        unsigned int tableNum,
                        unsigned int actionNum);
    void registerCondition(Condition* cond,
                           unsigned int tableNum,
                           unsigned int actionNum);

    Condition* getCondition(unsigned int tableNum, unsigned int condNum);
    SysAction* getAction(unsigned int tableNum, unsigned int actNum);

    static Registry* instance();
};

//---------------------------------------------------------------------------
#endif
