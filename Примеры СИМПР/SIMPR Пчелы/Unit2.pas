unit Unit2;

interface

uses
  ExtCtrls;

type

  Bee = Record
    State: Integer; //(0 - � ����; 1 - ����� � ������; 2 - ����� � ����; 3 - �������� ������)
    IsWithHoney: Boolean;
    Flower: Integer; //����� ������, 0 - �� ��������� �� ������
    Step: Integer;
    Speed: Integer;
    X: Integer;
    Y: Integer;
    image: TImage;
  end;

  Flower = Record
    IsWithPollen: Boolean;
    IsWithBee: Boolean;
    Bee: Integer;
    X: Integer;
    Y: Integer;
    image: TImage;
  end;



implementation

end.
