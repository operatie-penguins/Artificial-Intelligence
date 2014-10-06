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
      t1_cond->push_back("���������?");
      tablesCond.push_back(*t1_cond);
      
      TableVector* t2_cond = new TableVector;
      t2_cond->push_back("");
      t2_cond->push_back("����?");
      tablesCond.push_back(*t2_cond);

      TableVector* t3_cond = new TableVector;
      t3_cond->push_back("");
      t3_cond->push_back("�������?");
      t3_cond->push_back("��� �����?");
      tablesCond.push_back(*t3_cond);

      TableVector* t1_act = new TableVector;
      tablesAct.push_back(*t1_act);

      TableVector* t2_act = new TableVector;
      tablesAct.push_back(*t2_act);

      TableVector* t3_act = new TableVector;
      t3_act->push_back("");
      t3_act->push_back("���� ����");
      t3_act->push_back("������� � ������");
      t3_act->push_back("���������");
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
          return "����������� ������� ��� ��������";
        }
        if(condOrActNum >= tablesAct[tableNum].size())
        {
          return "����������� ��������";
        }
        return tablesAct[tableNum][condOrActNum];
      }
      else
      {
        if(tableNum >= tablesCond.size())
        {
          return "����������� ������� ��� �������";
        }
        if(condOrActNum >= tablesCond[tableNum].size())
        {
          return "����������� �������";
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
