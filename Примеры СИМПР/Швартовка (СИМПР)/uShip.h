//---------------------------------------------------------------------------

#ifndef uShipH
#define uShipH

//---------------------------------------------------------------------------

#include <ExtCtrls.hpp>
#endif

//---------------------------------------------------------------------------

//����� ������� (��������� �� TImage)
class Ship : TImage
{
  private:
    //��������� �������� ������� (0 - ��������, 1 - ���������, 2 - ���������,)
    int int_Status;
    //��������� ����� ������� (0 - ��� �����, 1 - ���� ����)
    int int_Load;
    //���������� ������� (0 - ������������, 1 - ��������)
    int int_Mission;
    //����������� �������� (0 ���� - , 1 - �����, 2 - ������, 3 - �����,)
    int int_Direction;
    //���������� X
    int int_X;
    //���������� Y
    int int_Y;
    //���������� ������� ������
    void __fastcall tmr_TimeTimer(TObject *Sender);
    //����
    bool flgTmr;
    //���� ����
    bool flgStep;
    //���� ����
    bool flgDock;
  public:
    //Timer
    TTimer* tmr_Time;
    //�����������
    Ship(int int_NewStatus, int int_NewLoad, int int_NewMission, int int_NewDirection, int int_NewCordX, int int_NewCordY, TWinControl* AOwner);
    //������� "���"
    int __ShpStep(int int_StepX, int int_StepY);
    //������� "�������� �� �����"
    int __ShpMove(int int_StepX, int int_StepY);
    //������� "���������"
    int __ShpDock(int int_StepX, int int_StepY, int int_DestinationX, int int_DestinationY, int int_DestinationW, int int_DestinationH);
    //������� "���������"
    int __ShpUnload(int int_Time);
    //������� ���������� ��������� �������� �������
    int GetStatus();
    //�������������� ��������� ��������� �������� �������
    int SetStatus(int int_NewStatus);
    //������� ���������� ��������� ����� �������
    int GetLoad();
    //�������������� ��������� ��������� ����� �������
    int SetLoad(int int_NewLoad);
    //������� ���������� ���������� �������
    int GetMission();
    //������� ���������� ����������� �������� �������
    int GetDirection();
    //�������������� ��������� ����������� �������� �������
    int SetDirection(int int_NewDirection);
    //�������������� ��������� ������������� �������
    int SetOwner(TWinControl* AOwner);
    //������� ���������� ���������� X
    int GetX();
    //������� ���������� ���������� Y
    int GetY();
    //������� �������������� ���������� X
    int SetX(int int_NewX);
    //������� �������������� ���������� Y
    int SetY(int int_NewY);
    //������� ���������� ���� ����
    bool GetFlgStep();
    //�������������� ��������� ����� ����
    bool SetFlgStep(bool NewFlgStep);
    //������� ���������� ���� ����
    bool GetFlgDock();
    //�������������� ��������� ����� ����
    bool SetFlgDock(bool NewFlgDock);
    //������� ���������� ���� �������
    bool GetFlgTmr();
    //�������������� ��������� ����� �������
    bool SetFlgTmr(bool NewFlgTmr);
};
