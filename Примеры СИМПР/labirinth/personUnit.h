//---------------------------------------------------------------------------
#ifndef personUnitH
#define personUnitH
//---------------------------------------------------------------------------
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

//��������������
const int up = 0,
          right = 1,
          down = 2,
          left = 3;
//---------------------------------------------------------------------------
typedef Graphics::TBitmap * bMaps[4];

class Person
{
    bMaps bitMaps;
    TImage * image; //������� �������� �������

    void changePicture(const int n); //������� ������� ��������

  protected:
    void dis(int& a, int &b, const bool key = false);
    int x,y, //���������� �������
        dir; //������� �����������
    int rotations; //���������� ����������� ��������� �� �����

  public:

    Person(bMaps,TImage*);
    ~Person();

    //-----------
    //���������
    //-----------

    int getX();
    int getY();

    //���������� �� �������, ����� p = 1 ����, p = 2 �����������
    //���������� 0 - � �������
    int alert(const int p);

    //���� �������
    int look();

    //����� ���� � �������, ������� �������
    bool canGo();

    //��������� �� ����
    bool onEdge();

    //---------------------
    //��������
    //---------------------

    //-----�����-----------

    //���������
    void turn(const int side);

    //����
    void go();

    //���������
    void show();

    //���������
    void hide();

    //������������� � ����� (���������)
    void gotoXY(const int x, const int y);

    //���������� ��������� �� �����
    int getRotations();

    //�������� �������
    void freeRotation();

    //-----�������������---

    //c�������� �������� (�������������/���������)
    virtual void randomAction() {}
    //������������� �������� (��������/�������)

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


