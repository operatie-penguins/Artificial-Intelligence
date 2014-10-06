//---------------------------------------------------------------------------

#ifndef ModelH
#define ModelH
//---------------------------------------------------------------------------

#include <vector>
using namespace std;

#include "Creature.h"
#include "Painter.h"
#include "Food.h"

enum Conditions { COND_IS_HARE, COND_IS_HUNGRY };
enum Actions { ACT_NEXT };

class Model : public CreatureClassifier {

    unsigned int creatureIdx;
    Painter* listener;

  public:
    vector<Food*> food;
    vector<Creature*> creatures;
    int iterNum;
    bool paused;

    Creature* getCurrentCreature();
    Model();
    bool isHare();
    void nextCreature();
    void onBeginNextIter();
    void setModelListener(Painter* apListener);
    float distance(HasXY* a, HasXY* b);
    void killCurrent();
};

#endif
