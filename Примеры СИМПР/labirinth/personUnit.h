//---------------------------------------------------------------------------
#ifndef personUnitH
#define personUnitH
//---------------------------------------------------------------------------
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

//Идентификаторы
const int up = 0,
          right = 1,
          down = 2,
          left = 3;
//---------------------------------------------------------------------------
typedef Graphics::TBitmap * bMaps[4];

class Person
{
    bMaps bitMaps;
    TImage * image; //текущая картинка объекта

    void changePicture(const int n); //сменить текущую картинку

  protected:
    void dis(int& a, int &b, const bool key = false);
    int x,y, //координаты объекта
        dir; //текущее направление
    int rotations; //количество совершённых поворотов на месте

  public:

    Person(bMaps,TImage*);
    ~Person();

    //-----------
    //состояния
    //-----------

    int getX();
    int getY();

    //расстояние до тревоги, видит p = 1 копа, p = 2 преступника
    //расстояние 0 - в плотную
    int alert(const int p);

    //куда смотрит
    int look();

    //может идти в сторону, которую смотрит
    bool canGo();

    //находится на краю
    bool onEdge();

    //---------------------
    //действия
    //---------------------

    //-----Общие-----------

    //повернуть
    void turn(const int side);

    //идти
    void go();

    //появиться
    void show();

    //изчезнуть
    void hide();

    //переместиться в точку (мгновенно)
    void gotoXY(const int x, const int y);

    //количество поворотов на месте
    int getRotations();

    //обнулить ротации
    void freeRotation();

    //-----Перегружаемые---

    //cлучайное действие (патрулировать/озираться)
    virtual void randomAction() {}
    //специфическое действие (догонять/убегать)

};
//---------------------------------------------------------------------------

class Cop : public Person
{
  public:
    Cop(bMaps,TImage*);
    void randomAction();
};
//---------------------------------------------------------------------------

class Crime : public Person
{
  public:
    Crime(bMaps,TImage*);
    void randomAction();
};
//---------------------------------------------------------------------------
#endif


