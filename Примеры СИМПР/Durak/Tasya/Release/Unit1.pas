unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ImgList, ExtCtrls, jpeg, Buttons, syncobjs;

type
  TForm1 = class(TForm)
    Player1Label: TLabel;
    Label5: TLabel;
    Player1List: TListBox;
    Player2List: TListBox;
    MyCard1: TImage;
    MyCard2: TImage;
    MyCard3: TImage;
    MyCard4: TImage;
    MyCard5: TImage;
    MyCard6: TImage;
    MyCard7: TImage;
    Player1Cards: TImage;
    Player2Cards: TImage;
    AttackCard1: TImage;
    AttackCard2: TImage;
    AttackCard3: TImage;
    AttackCard4: TImage;
    AttackCard5: TImage;
    AttackCard6: TImage;
    DefendCard1: TImage;
    DefendCard2: TImage;
    DefendCard3: TImage;
    DefendCard4: TImage;
    DefendCard5: TImage;
    DefendCard6: TImage;
    MyCard8: TImage;
    KosirImage: TImage;
    CurrentPlayerImage: TImage;
    ActivePlayerImage: TImage;
    MyCard10: TImage;
    MyCard12: TImage;
    MyCard16: TImage;
    MyCard9: TImage;
    MyCard11: TImage;
    MyCard14: TImage;
    Mycard13: TImage;
    MyCard15: TImage;
    MyCard19: TImage;
    MyCard18: TImage;
    MyCard23: TImage;
    MyCard21: TImage;
    MyCard17: TImage;
    MyCard20: TImage;
    MyCard22: TImage;
    MyCard24: TImage;
    MyCard28: TImage;
    MyCard27: TImage;
    MyCard25: TImage;
    MyCard26: TImage;
    MyCard29: TImage;
    MyCard30: TImage;
    procedure FormCreate(Sender: TObject);
    procedure WndProc(var Message:TMessage); override;
    procedure ShowCards;
    procedure RedrawPointer;
    procedure RedrawActivePlayer;
    procedure Button2Click(Sender: TObject);
    procedure MyCard1Click(Sender: TObject);
    procedure MyCard2Click(Sender: TObject);
    procedure MyCard3Click(Sender: TObject);
    procedure MyCard4Click(Sender: TObject);
    procedure MyCard5Click(Sender: TObject);
    procedure MyCard6Click(Sender: TObject);
    procedure MyCard7Click(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure CurrentPlayerImageClick(Sender: TObject);
    procedure MyCard8Click(Sender: TObject);
    procedure MyCard9Click(Sender: TObject);
    procedure MyCard10Click(Sender: TObject);
    procedure MyCard11Click(Sender: TObject);
    procedure MyCard12Click(Sender: TObject);
    procedure Mycard13Click(Sender: TObject);
    procedure MyCard16Click(Sender: TObject);
    procedure MyCard14Click(Sender: TObject);
    procedure MyCard15Click(Sender: TObject);
    procedure MyCard17Click(Sender: TObject);
    procedure MyCard18Click(Sender: TObject);
    procedure MyCard19Click(Sender: TObject);
    procedure MyCard20Click(Sender: TObject);
    procedure MyCard21Click(Sender: TObject);
    procedure MyCard22Click(Sender: TObject);
    procedure MyCard23Click(Sender: TObject);
    procedure MyCard24Click(Sender: TObject);
    procedure MyCard25Click(Sender: TObject);
    procedure MyCard27Click(Sender: TObject);
    procedure MyCard29Click(Sender: TObject);
    procedure MyCard26Click(Sender: TObject);
    procedure MyCard28Click(Sender: TObject);
    procedure MyCard30Click(Sender: TObject);


  private
        Event:TEvent;
    {ivate declarations }
  public




  end;
type

        CardsSet = set of byte;



var
  Form1: TForm1;
  Player1:set of byte;
  Player2:set of byte;
  Player3:set of byte;
  Bito:set of byte;
  Kosir : byte;
  AttackCard: byte;
  C1 : integer;
  C2 : integer;
  C3 : integer;
  C4 : integer;
  C5 : integer;
  C6 : integer;
  C7 : integer;
  C8 : integer;
  C9 : integer;
  C10 : integer;
  C11 : integer;
  C12 : integer;
  C13 : integer;
  C14 : integer;
  CardsOnTheTable : CardsSet;
  ActivePlayer : byte;
  UsedCards : byte;
  FirstIsGone : boolean;
  SecondIsGone : boolean;
  ThirdIsGone : boolean;
  Attack : boolean;
  Podkidon1:integer;
  Podkidon2:integer;
  Podkidon3:integer;
  Otbivon1:integer;
  Otbivon2:integer;
  Otbivon3:integer;
  EndFirstIsGone:boolean;
  EndSecondIsGone:boolean;
  Perehod : boolean;
  ChosenCard : byte;
  AttackCards: array [1..12] of byte;
  DefendCards: array [1..12] of byte;
  AttackNum : byte;
  DefendNum : byte;
  Chosen : boolean;
  CurrentPlayer : byte;


implementation

{$R *.dfm}

function card(S:CardsSet):byte;
var
        i:byte;
begin
        result := 0;
        for i:=0 to 35 do
                if i in S then
                        result:=result + 1;
end;

function OneHasLeft:boolean;
begin
        result := (FirstIsGone) or (SecondIsGone) or(ThirdIsGone);
end;


procedure TForm1.RedrawActivePlayer;
begin
        if OneHasLeft = false then
              case ActivePlayer of
                1:
                        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer1.bmp');
                2:
                        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer2.bmp');
                3:
                        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer3.bmp');
                end
        else
        begin
                if (ActivePlayer = 1) and (FirstIsGone) then
                        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer5.bmp');
                if (ActivePlayer = 1) and (SecondIsGone) then
                        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer6.bmp');
                if (ActivePlayer = 1) and (ThirdIsGone) then
                        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer1.bmp');
                if (ActivePlayer = 2) and (FirstIsGone) then
                        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer2.bmp');
                if (ActivePlayer = 2) and (SecondIsGone) then
                        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer6.bmp');
                if (ActivePlayer = 2) and (ThirdIsGone) then
                        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer4.bmp');
                if (ActivePlayer = 3) and (FirstIsGone) then
                        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer5.bmp');
                if (ActivePlayer = 3) and (SecondIsGone) then
                        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer3.bmp');
                if (ActivePlayer = 3) and (ThirdIsGone) then
                        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer4.bmp');
        end;

end;

procedure TForm1.RedrawPointer;
begin
 case CurrentPlayer of
        1:
                CurrentPlayerImage.Picture.LoadFromFile('CurrentPlayer1.bmp');
        2:
                CurrentPlayerImage.Picture.LoadFromFile('CurrentPlayer2.bmp');
        3:
                CurrentPlayerImage.Picture.LoadFromFile('CurrentPlayer3.bmp');
        end;

end;

procedure ClearTable ;
begin
        AttackNum :=1;
        DefendNum :=1;
end;

function NewCard:byte;
var
        NC:byte;
begin
        NC:=random(36);
        while (NC in Player1)or(NC in Player2)or(NC in Player3) or (NC in Bito) do
                NC := random(36);
        result:=NC;
        Bito := Bito + [NC];
        inc(UsedCards);
end;


{Эта процедура не нужна даже для тестирования}

function Transfigure(i : byte):string;
var
        Nominal : byte;
        Mast : byte;
begin
        Nominal := i mod 9;
        Mast := i div 9;

        result := IntToStr(i);
        result := result + ' - ';



        case Nominal of
        5:      result := result + 'В';
        6:      result := result + 'Д';
        7:      result := result + 'К';
        8:      result := result + 'Т';
        else
                result := result + IntToStr(Nominal + 6);
        end;

        result := result + ' ';

        case Mast of
        0:
        result := result + 'П';
        1:
        result := result + 'К';
        2:
        result := result + 'Ч';
        3:
        result := result + 'Б';
        end;


end;

procedure Rasdacha;
var
        i:byte;
begin
        for i:=0 to 5 do
        begin
                Player1:=Player1+[NewCard];
                Player2:=Player2+[NewCard];
                Player3:=Player3+[NewCard];
        end;
end;


function FindMinCard(Player:CardsSet):byte;
var
Mast : byte;
Nominal : byte;
MinMast :byte;
MinNominal : byte;
ExistsNotKosir : boolean;
i : byte;
begin
        ExistsNotKosir := false;
        MinMast := 0;
        MinNominal := 8;
        for i:=0 to 35 do
                if i in Player then
                begin
                        Nominal := i mod 9;
                        Mast := i div 9;
                        if (Nominal <= MinNominal) and (Mast <> Kosir) then
                        begin
                                ExistsNotKosir:=true;
                                MinNominal := Nominal;
                                MinMast := Mast;
                        end;
                end;
        if not ExistsNotKosir then
                for i:=0 to 35 do
                        if i in Player then
                        begin
                                Nominal := i mod 9;
                                Mast := i div 9;
                                if (Nominal <= MinNominal)then
                                begin
                                        MinNominal := Nominal;
                                        MinMast := Mast;
                                end;
                        end;
        result:=9*MinMast + MinNominal;
end;


function MinCard(PlayerNum : byte):byte;
begin
case PlayerNum of
1:
        result:=FindMinCard(Player1);
2:
        result:=FindMinCard(Player2);
3:
        result:=FindMinCard(Player3);
end;
end;


function FindPodkid(Player : CardsSet;C:byte):byte;
var
        InNominal : byte;
        i : byte;
begin
        InNominal :=C mod 9;

        result := 40;
        for i:=0 to 35 do
        begin
                if (i in Player) and (i mod 9 = InNominal) and (i div 9 <>Kosir) then
                begin
                        result:=i;
                        break;
                end;
                if (i in Player) and (i mod 9 = InNominal) and (i div 9 = Kosir) then
                        result := i;
        end;


end;



function Podkid(Player:CardsSet ; CS:CardsSet) : byte;
var
        ExistsNotKosir:boolean;
        ToBePodkided : CardsSet;
        MinMast : byte;
        Mast : byte;
        Nominal : byte;
        MinNominal : byte;
        i : byte;
        FP : byte;
begin
        ExistsNotKosir := false;
        ToBePodkided := [];

        for i:=0 to 35 do
                if i in CS then
                begin
                        FP := FindPodkid(Player,i);
                        if FP<>40 then
                                ToBePodkided := ToBePodkided + [FP];
                end;

        MinMast := 0;
        MinNominal := 8;
        for i:=0 to 35 do
                if i in ToBePodkided then
                begin
                        Nominal := i mod 9;
                        Mast := i div 9;
                        if (Nominal <= MinNominal) and (Mast <> Kosir) then
                        begin
                                ExistsNotKosir:=true;
                                MinNominal := Nominal;
                                MinMast := Mast;
                        end;
                end;

        if not ExistsNotKosir then
                for i:=0 to 35 do
                        if i in ToBePodkided then
                        begin
                                Nominal := i mod 9;
                                Mast := i div 9;
                                if (Nominal <= MinNominal)then
                                begin
                                        MinNominal := Nominal;
                                        MinMast := Mast;
                                end;
                        end;
        result:=9*MinMast + MinNominal;
        if card(ToBePodkided)=0 then
                result := 40;
        if card(CardsOnTheTable)=12 then
                result := 40;


end;

function Podkidon (PlayerNum : byte; C:CardsSet):byte;
begin
case PlayerNum of
1:
        result := Podkid(Player1,C);
2:
        result := Podkid(Player2,C);
3:
        result := Podkid(Player3,C);
end;
end;


procedure CasesOtbivon (C: byte);
begin

        if (C div 9 <>kosir) and (C mod 9 <=5) then
        begin
                Otbivon1 := 0;
                Otbivon2 := 0;
                Otbivon3 := 1;

        end;
        if (C div 9 <>kosir) and (C mod 9 >5) then
        begin
                Otbivon1 := 0;
                Otbivon2 := 1;
                Otbivon3 := 0;

        end;
        if (C div 9 =kosir) and (C mod 9 <=4) then
        begin
                Otbivon1 := 0;
                Otbivon2 := 1;
                Otbivon3 := 1;

        end;
        if (C div 9 =kosir) and (C mod 9 > 4) then
        begin
                Otbivon1 := 1;
                Otbivon2 := 0;
                Otbivon3 := 0;

        end;
        if (C > 35) then
        begin
                Otbivon1 := 0;
                Otbivon2 := 0;
                Otbivon3 := 0;

        end;

end;


procedure CasesPodkidon (C: byte);
begin

        if (C div 9 <>kosir) and (C mod 9 <=5) then
        begin
                Podkidon1 := 0;
                Podkidon2 := 0;
                Podkidon3 := 1;
        end;
        if (C div 9 <>kosir) and (C mod 9 >5) then
        begin
                Podkidon1 := 0;
                Podkidon2 := 1;
                Podkidon3 := 0;
        end;
        if (C div 9 =kosir) and (C mod 9 <=4) then
        begin
                Podkidon1 := 0;
                Podkidon2 := 1;
                Podkidon3 := 1;
        end;
        if (C div 9 =kosir) and (C mod 9 > 4) then
        begin
                Podkidon1 := 1;
                Podkidon2 := 0;
                Podkidon3 := 0;
        end;
        if (C > 35) then
        begin
                Podkidon1 := 0;
                Podkidon2 := 0;
                Podkidon3 := 0;
        end;
end;

{Можно переделать вместо ToBeOtbivoned result}
function FindOtbivon(Player : CardsSet;C:byte):byte;
var
        InNominal : byte;
        InMast : byte;
        ToBeOtbivoned : CardsSet;
        i : byte;
begin
        InNominal :=C mod 9;
        InMast := C div 9;
        ToBeOtbivoned := [];

        if (InMast <> Kosir) then
        begin
                for i:=0 to 35 do
                        if (i in Player) and (i mod 9 > InNominal) and (i div 9 = InMast)  then
                        begin
                                ToBeOtbivoned := ToBeOtbivoned + [i];
                                break;
                        end;
                if card(TobeOtbivoned)=0 then
                        for i:=0 to 35 do
                                if (i in Player) and (i div 9 = Kosir) then
                                begin
                                        ToBeOtbivoned := [i];
                                        break;
                                end;

        end
        else
                for i:=0 to 35 do
                        if (i in Player) and (i mod 9 > InNominal) and (i div 9 = InMast) then
                        begin
                                ToBeOtbivoned := [i];
                                break;
                        end;

        if card(ToBeOtbivoned) = 0 then
                result := 40
        else
                for i:=0 to 35 do
                if i in ToBeOtbivoned then
                begin
                        result:=i;
                        break;
                end;
end;

function Otbivon(PlayerNum : byte; C: byte):byte;
begin
case PlayerNum of
1:
        result:=FindOtbivon(Player1,C);
2:
        result:=FindOtbivon(Player2,C);
3:
        result:=FindOtbivon(Player3,C);
end;
end;

procedure ChangeForPlayer3(AC:byte);
begin
        AttackCard := AC;
        AttackNum := 1;
        DefendNum :=1;                
        AttackCards[Attacknum]:=AttackCard;
        inc(AttackNum);
        Bito := Bito + CardsOntheTable;
        CardsOnTheTable := [AttackCard];
        C1 := 1;
        C2 := 1;
        Player3 := Player3 - [AttackCard];
        ActivePlayer := 3;

end;


procedure ChangePlayer(PlayerNum:byte);
begin
        AttackCard := MinCard(PlayerNum);
        AttackNum := 1;
        DefendNum :=1;        
        AttackCards[AttackNum]:=AttackCard;
        inc(AttackNum);
        Bito := Bito + CardsOntheTable;
        CardsOnTheTable := [AttackCard];
        case PlayerNum of
        1:      begin
                        C1 :=0;
                        C2 := 1;
                        Player1 := Player1 - [AttackCard];

                end;
        2:      begin
                        C1 := 1;
                        C2 := 0;
                        Player2 := Player2 - [AttackCard];
                end;
        3:      begin
                        C1 := 1;
                        C2 := 1;
                        Player3 := Player3 - [AttackCard];
                end;
        end;

        ActivePlayer := PlayerNum;

end;

function TransfigureNum(Num : integer):integer;
begin
        result := Num - 3;
end;


procedure ChangePlayerEnd(PlayerNum: byte);
begin

        AttackCard := MinCard(TransfigureNum(PlayerNum));
        AttackNum := 1;
        DefendNum :=1;
        AttackCards[AttackNum]:=AttackCard;
        inc(AttackNum);
        Bito := Bito + CardsOntheTable;
        CardsOnTheTable := [AttackCard];

        case TransfigureNum(PlayerNum) of
        1:      begin
                        Player1 := Player1 - [AttackCard];

                end;
        2:      begin
                        Player2 := Player2 - [AttackCard];
                end;
        3:      begin
                        Player3 := Player3 - [AttackCard];
                end;
        end;

        ActivePlayer := TransfigureNum(PlayerNum);

end;

procedure ChangeForPlayer3End(AC: byte);
begin

        AttackCard := AC;
        AttackNum := 1;
        DefendNum :=1;        
        AttackCards[AttackNum]:=AttackCard;
        inc(AttackNum);
        Bito := Bito + CardsOntheTable;
        CardsOnTheTable := [AttackCard];

        Player3 := Player3 - [AttackCard];
        ActivePlayer := 3;

end;


procedure Prinyat (PlayerNum:byte);
begin
case PlayerNum of
1:
        Player1 := Player1 + CardsOnTheTable;
2:
        Player2 := Player2 + CardsonTheTable;
3:
        Player3 := Player3 + CardsonTheTable;
end;

        AttackNum := 1;
        DefendNum := 1;
end;

procedure Otbitsya(PlayerNum : byte;OC : byte);
begin
DefendCards[DefendNum] := OC;
inc(DefendNum);
CardsOnTheTable := CardsOnTheTable + [OC];
case PlayerNum of
1:
        Player1 := Player1 - [OC];
2:
        Player2 := Player2 - [OC];
3:
        Player3 := Player3 - [OC];
end;

end;

procedure Podkinut(PlayerNum : byte; PC:byte);
begin
AttackCards[AttackNum]:=PC;
inc(AttackNum);
        CardsOnTheTable := CardsOnTheTable + [PC];
        AttackCard := PC;
case PlayerNum of
1:
        Player1 := Player1 - [PC];
2:
        Player2 := Player2 - [PC];
3:
        Player3 := Player3 - [PC];
end;
end;

procedure TForm1.ShowCards;
var
        i:byte;
        T0 : TObject;
        Player3Shown:byte;
        B : TBitmap;
begin
        B := TBitmap.Create;
        Player3Shown := 1;
        Player1List.clear;
        Player2List.clear;


        MyCard1.Picture.LoadFromFile('Empty.bmp');
        MyCard2.Picture.LoadFromFile('Empty.bmp');
        MyCard3.Picture.LoadFromFile('Empty.bmp');
        MyCard4.Picture.LoadFromFile('Empty.bmp');
        MyCard5.Picture.LoadFromFile('Empty.bmp');
        MyCard6.Picture.LoadFromFile('Empty.bmp');
        MyCard7.Picture.LoadFromFile('Empty.bmp');
        MyCard8.Picture.LoadFromFile('Empty.bmp');
        MyCard9.Picture.LoadFromFile('Empty.bmp');
        MyCard10.Picture.LoadFromFile('Empty.bmp');
        MyCard11.Picture.LoadFromFile('Empty.bmp');
        MyCard12.Picture.LoadFromFile('Empty.bmp');
        MyCard13.Picture.LoadFromFile('Empty.bmp');
        MyCard14.Picture.LoadFromFile('Empty.bmp');
        MyCard15.Picture.LoadFromFile('Empty.bmp');
        MyCard16.Picture.LoadFromFile('Empty.bmp');
        MyCard17.Picture.LoadFromFile('Empty.bmp');
        MyCard18.Picture.LoadFromFile('Empty.bmp');
        MyCard19.Picture.LoadFromFile('Empty.bmp');
        MyCard20.Picture.LoadFromFile('Empty.bmp');
        MyCard21.Picture.LoadFromFile('Empty.bmp');
        MyCard22.Picture.LoadFromFile('Empty.bmp');
        MyCard23.Picture.LoadFromFile('Empty.bmp');
        MyCard24.Picture.LoadFromFile('Empty.bmp');
        MyCard25.Picture.LoadFromFile('Empty.bmp');
        MyCard26.Picture.LoadFromFile('Empty.bmp');
        MyCard27.Picture.LoadFromFile('Empty.bmp');
        MyCard28.Picture.LoadFromFile('Empty.bmp');
        MyCard29.Picture.LoadFromFile('Empty.bmp');
        MyCard30.Picture.LoadFromFile('Empty.bmp');

 {
        case ActivePlayer of
        1:
                ActivePlayerImage.Picture.LoadFromFile('ActivePlayer1.bmp');
        2:
                ActivePlayerImage.Picture.LoadFromFile('ActivePlayer2.bmp');
        3:
                ActivePlayerImage.Picture.LoadFromFile('ActivePlayer3.bmp');
        end;
{
        case CurrentPlayer of
        1:
                ActivePlayerImage.Picture.LoadFromFile('ActivePlayer1.bmp');
        2:
                ActivePlayerImage.Picture.LoadFromFile('ActivePlayer2.bmp');
        3:
                ActivePlayerImage.Picture.LoadFromFile('ActivePlayer3.bmp');
        end;
 }
        for i:=0 to 35 do
        begin
                if (i in Player1) then
                        Player1List.AddItem(Transfigure(i),T0);
                if (i in Player2) then
                        Player2List.AddItem(Transfigure(i),T0);
                if (i in Player3) then
                begin
                        case Player3Shown of
                        1:
                                begin
                                         MyCard1.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        2:
                                begin

                                         MyCard2.Picture.LoadFromFile(IntToStr(i) + '.bmp');

                                end;
                        3:
                                begin

                                         MyCard3.Picture.LoadFromFile(IntToStr(i) + '.bmp');

                                end;
                        4:
                                begin
                                         MyCard4.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        5:
                                begin
                                         MyCard5.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        6:
                                begin
                                         MyCard6.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        7:
                                begin
                                         MyCard7.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        8:
                                begin
                                         MyCard8.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        9:
                                begin
                                         MyCard9.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        10:
                                begin
                                         MyCard10.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        11:
                                begin
                                         MyCard11.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        12:
                                begin
                                         MyCard12.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        13:
                                begin
                                         MyCard13.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        14:
                                begin
                                         MyCard14.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        15:
                                begin
                                         MyCard15.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        16:
                                begin
                                         MyCard16.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        17:
                                begin
                                         MyCard17.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        18:
                                begin
                                         MyCard18.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        19:
                                begin
                                         MyCard19.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        20:
                                begin
                                         MyCard20.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        21:
                                begin
                                         MyCard21.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        22:
                                begin
                                         MyCard22.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        23:
                                begin
                                         MyCard23.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        24:
                                begin
                                         MyCard24.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        25:
                                begin
                                         MyCard25.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        26:
                                begin
                                         MyCard26.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        27:
                                begin
                                         MyCard27.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        28:
                                begin
                                         MyCard28.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        29:
                                begin
                                         MyCard29.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;
                        30:
                                begin
                                         MyCard30.Picture.LoadFromFile(IntToStr(i) + '.bmp');
                                end;

                        end;
                        inc (Player3Shown);
                end;

        end;






        AttackCard1.Picture.LoadFromFile('Empty.bmp');
        AttackCard2.Picture.LoadFromFile('Empty.bmp');
        AttackCard3.Picture.LoadFromFile('Empty.bmp');
        AttackCard4.Picture.LoadFromFile('Empty.bmp');
        AttackCard5.Picture.LoadFromFile('Empty.bmp');
        AttackCard6.Picture.LoadFromFile('Empty.bmp');

        DefendCard1.Picture.LoadFromFile('Empty.bmp');
        DefendCard2.Picture.LoadFromFile('Empty.bmp');
        DefendCard3.Picture.LoadFromFile('Empty.bmp');
        DefendCard4.Picture.LoadFromFile('Empty.bmp');
        DefendCard5.Picture.LoadFromFile('Empty.bmp');
        DefendCard6.Picture.LoadFromFile('Empty.bmp');


        for i:=1 to AttackNum-1 do
                case i of
                1:
                        AttackCard1.Picture.LoadFromFile(IntToStr(AttackCards[i])+'.bmp');
                2:
                        AttackCard2.Picture.LoadFromFile(IntToStr(AttackCards[i])+'.bmp');
                3:
                        AttackCard3.Picture.LoadFromFile(IntToStr(AttackCards[i])+'.bmp');
                4:
                        AttackCard4.Picture.LoadFromFile(IntToStr(AttackCards[i])+'.bmp');
                5:
                        AttackCard5.Picture.LoadFromFile(IntToStr(AttackCards[i])+'.bmp');
                6:
                        AttackCard6.Picture.LoadFromFile(IntToStr(AttackCards[i])+'.bmp');
                end;
        for i:=1 to DefendNum-1 do
                case i of
                1:
                        DefendCard1.Picture.LoadFromFile(IntToStr(DefendCards[i])+'.bmp');
                2:
                        DefendCard2.Picture.LoadFromFile(IntToStr(DefendCards[i])+'.bmp');
                3:
                        DefendCard3.Picture.LoadFromFile(IntToStr(DefendCards[i])+'.bmp');
                4:
                        DefendCard4.Picture.LoadFromFile(IntToStr(DefendCards[i])+'.bmp');
                5:
                        DefendCard5.Picture.LoadFromFile(IntToStr(DefendCards[i])+'.bmp');
                6:
                        DefendCard6.Picture.LoadFromFile(IntToStr(DefendCards[i])+'.bmp');
                end;

end;

function KolodaIsEmpty : boolean;
begin
        if (UsedCards = 36) then
                result := true
        else
                result := false;

end;


procedure SetWinners;
begin

        if (KolodaIsEmpty) then
        begin
                if (card(Player1) = 0) then
                begin
                        FirstIsGone := true;
                end;
                if (card(Player2) = 0) then
                begin
                        SecondIsGone := true;
                end;
                if (card(Player3) = 0) then
                begin
                        ThirdIsGone := true;
                end;
        end;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
lpClassName: PChar;
tmp: PChar;
x: integer;
begin
        Event := TEvent.Create(nil,true,false,'Chosen');
        AttackCard1.Picture.LoadFromFile('7.bmp');
        AttackCard1.Picture.LoadFromFile('Empty.bmp');

        AttackNum :=1;
        DefendNum :=1;
        Perehod:=true;
UsedCards:=0;

GetMem(lpClassName,20);
if GetClassName(Handle,lpClassName,20)<>0 then
        FreeMem(lpClassName,20);
        randomize;

        Rasdacha;
        ShowCards;

        Kosir := random(4);


        FirstIsGone := false;
        SecondIsGone := false;
        ThirdIsGone := false;

        Attack := true;


        if Kosir = 0 then
                KosirImage.Picture.LoadFromFile('Пики.bmp');
        if Kosir = 1 then
                KosirImage.Picture.LoadFromFile('Крести.bmp');
        if Kosir = 2 then
                KosirImage.Picture.LoadFromFile('Черви.bmp');
        if Kosir = 3 then
                KosirImage.Picture.LoadFromFile('Буби.bmp');

        Chosen := false;

end;

function FindC1(PlayerNum : byte):integer;
begin
        if Perehod then
        begin
                if (PlayerNum = 4) and (ActivePlayer = 1) then
                        result := 1;
                if (PlayerNum = 4) and (ActivePlayer = 2) then
                        result := 1;
                if (PlayerNum = 4) and (ActivePlayer = 3) then
                        result := 0;
                if (PlayerNum = 5) and (ActivePlayer = 1) then
                        result := 0;
                if (PlayerNum = 5) and (ActivePlayer = 2) then
                        result := 1;
                if (PlayerNum = 5) and (ActivePlayer = 3) then
                        result := 1;
                if (PlayerNum = 6) and (ActivePlayer = 1) then
                        result := 1;
                if (PlayerNum = 6) and (ActivePlayer = 2) then
                        result := 0;
                if (PlayerNum = 6) and (ActivePlayer = 3) then
                        result := 1;
                Perehod := false;
        end
        else
                If (PlayerNum = ActivePlayer) or (PlayerNum-3 = ActivePlayer) then
                        result := 1
                else
                        result := 0;



end;

procedure Rasdat;
begin
        while (card(Player1)<6)and(UsedCards<36) do
        begin
                Player1 := Player1 + [NewCard];
        end;


        while (card(Player2)<6)and (UsedCards < 36) do
        begin
                Player2 := Player2 + [NewCard];
        end;


        while (card(Player3)<6)and(UsedCards < 36) do
        begin
                Player3 := Player3 + [NewCard];
        end;

end;


procedure CallFool;
begin
        if (card(Player1) = 0)and (card(Player2)=0) and (card(Player3)=0) then
                MessageBox(0,'Ничья','Результаты',MB_OK or MB_ICONINFORMATION)
        else
        begin
                if (card(Player1)=0) and (card(Player2)=0) then
                        MessageBox(0,'Вы - дурак','Результаты',MB_OK or MB_ICONINFORMATION);
                if (card(Player1)=0) and (card(Player3)=0) then
                        MessageBox(0,'Игрок 2 остался дураком','Результаты',MB_OK or MB_ICONINFORMATION);
                if (card(Player3)=0) and (card(Player2)=0) then
                        MessageBox(0,'Игрок 1 остался дураком','Результаты',MB_OK or MB_ICONINFORMATION);
        end;
end;

procedure SetWinnersEnd;
begin
        EndFirstIsGone := false;
        EndSecondIsGone := false;
        if FirstIsGone then
        begin
                if card(Player2)=0 then
                        EndFirstIsGone := true;
                if card(Player3)=0 then
                        EndSecondIsGone := true;
        end;
        if SecondIsGone then
        begin
                if card(Player1)=0 then
                        EndFirstIsGone := true;
                if card(Player3)=0 then
                        EndSecondIsGone := true;
        end;

        if ThirdIsGone then
        begin
                if card(Player1)=0 then
                        EndFirstIsGone := true;
                if card(Player2)=0 then
                        EndSecondIsGone := true;
        end;
end;

procedure AnalyzeKoloda;
begin
        if UsedCards < 30 then
        begin
                C3 := 0;
                C4 := 0;
        end;
        if (UsedCards >=30) and (UsedCards < 36) then
        begin
                C3 := 0;
                C4 := 1;
        end;
        if (UsedCards = 36)then
        begin
                C3 := 1;
                C4 := 0; 
        end;

end;

function FindC11(PlayerNum:byte): integer;
begin
        if (PlayerNum = 4) and (SecondIsGone) then
                result := 0;
        if (PlayerNum = 4) and (ThirdIsGone) then
                result := 1;
        if (PlayerNum = 5) and (FirstIsGone) then
                result := 0;
        if (PlayerNum = 5) and (ThirdIsGone) then
                result := 1;
        if (PlayerNum = 6) and (FirstIsGone) then
                result := 0;
        if (PlayerNum = 6) and (SecondIsGone) then
                result := 1;
end;


procedure TForm1.WndProc(var Message:TMessage);
var
        Res:integer;
        tmp: PChar;
        RegMessage:integer;
        TmpCard : byte;
        OtbivonCard : byte;
        PodkidonCard : byte;
        S : String;
begin
        Res := 1;
        GetMem(tmp,255);
        tmp:= StrPCopy(tmp,'MyMessage');
        RegMessage:= RegisterWindowMessage('MyMessage');

        




        if (Message.Msg = RegMessage) then
        begin
                if (Message.WParamLo >3) then
                        CurrentPlayer :=Message.WParamLo -3
                else
                        CurrentPlayer :=Message.WParamLo;

                RedrawPointer;



                if (Message.WParamLo < 3) then
                begin

                        OtbivonCard := Otbivon(Message.WParamLo,AttackCard);
                        CasesOtbivon(OtbivonCard);
                        PodkidonCard := Podkidon(Message.WParamLo,CardsOnTheTable);
                        CasesPodkidon(PodkidonCard);
                        SetWinners;
                        AnalyzeKoloda;

                        if (Message.WParamHi=0) then
                        begin
                                case Message.LParam of
                                1:
                                        Message.Result := C1;
                                2:
                                        Message.Result := C2;
                                3:
                                        Message.Result := C3;
                                4:
                                        Message.Result := C4;
                                5:
                                        Message.Result := Otbivon1;
                                6:
                                        Message.Result := Otbivon2;
                                7:
                                        Message.Result := Otbivon3;
                                8:
                                        Message.Result := Podkidon1;
                                9:
                                        Message.Result := Podkidon2;
                                10:
                                        Message.Result := Podkidon3;
                                11:
                                        begin
                                                if Attack then
                                                        Message.Result := 1
                                                else
                                                        Message.Result := 0;
                                                Attack := false;
                                        end;
                                12:
                                        If FirstIsGone then
                                                Message.Result := 1
                                        else
                                                Message.Result := 0;
                                13:
                                        If SecondIsGone then
                                                Message.Result := 1
                                        else
                                                Message.Result := 0;

                                14:
                                        If ThirdIsGone then
                                                Message.Result := 1
                                        else
                                                Message.Result := 0;
                                end;
                        end
                        else
                        begin
                                case Message.LParam of
                                1:
                                       begin
                                               S:= 'Игрок' + IntToStr(Message.WParamLo) + ' принимает';
                                               sleep(2000);
                                               //MessageBox(0,PChar(S),'Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                               Prinyat(Message.WParamLo);

                                       end;
                                2:
                                       begin
                                                S:= 'Игрок' + IntToStr(Message.WParamLo) + ' отбивается';
                                                sleep(2000);
                                               //MessageBox(0,PChar(S),'Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                               Otbitsya(Message.WParamLo, OtbivonCard);
                                       end;
                                3:      Begin
                                                Podkinut(Message.WParamLo, PodkidonCard);
                                               S:= 'Игрок' + IntToStr(Message.WParamLo) + ' подкидывает';
                                               //MessageBox(0,PChar(S),'Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                               sleep(2000);
                                        end;
                                4:      begin
                                               S:= 'Игрок' + IntToStr(Message.WParamLo) + ' ничего не делает';
                                               //MessageBox(0,PChar(S),'Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                               sleep(2000);

                                        end;
                                5:
                                        begin
                                                Attack := true;
                                                ClearTable;
                                                Rasdat;
                                        end;
                                6:
                                        begin
                                                Attack := true;
                                                ClearTable;
                                                Rasdat;
                                        end;

                                7:
                                        begin
                                                Attack := true;
                                                ClearTable;
                                                Rasdat;
                                        end;

                                8:
                                        begin
                                                ChangePlayer(Message.WParamLo);
                                                RedrawActivePlayer;
                                        end;
                                end;

                                Message.Result := 1;
                                ShowCards;

                        end;
                end;

                if (Message.WParamLo = 3) then
                begin
                        if (Message.WParamHi=0) then
                        begin
                              SetWinners;
                              AnalyzeKoloda;
                              case Message.LParam of
                                1:
                                        Message.Result := C1;
                                2:
                                        Message.Result := C2;
                                3:
{                                        if MessageBox(0,'Ваши действия','Подкидной дурак',MB_OK or MB_ICONINFORMATION)= ID_YES then
                                        begin
                                                Message.Result := 1;
                                                OtbivonCard:=ChosenCard;//StrToInt(Edit5.Text);
                                                PodkidonCard:=ChosenCard;//StrToInt(Edit5.Text);
                                        end
                                        else
                                                Message.Result := 0;}
                                        begin
                                                while Event.WaitFor(20) <> wrSignaled do
                                                        Application.ProcessMessages;
                                                if Chosen then
                                                        Message.Result := 1
                                                else
                                                        Message.Result := 0;
                                                Event.ResetEvent;

                                        end;
                                4:
                                        begin
                                                if Attack then
                                                        Message.Result := 1
                                                else
                                                        Message.Result := 0;
                                                Attack := false;
                                        end;
                                5:
                                        If FirstIsGone then
                                                Message.Result := 1
                                        else
                                                Message.Result := 0;
                                6:
                                        If SecondIsGone then
                                                Message.Result := 1
                                        else
                                                Message.Result := 0;
                                7:
                                        If ThirdIsGone then
                                                Message.Result := 1
                                        else
                                                Message.Result := 0;



                               end;
                        end
                        else
                        begin

                              case Message.LParam of
                               1:
                                       begin
                                               //MessageBox(0,'Вы принимаете','Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                               Prinyat(Message.WParamLo);
                                       end;
                                2:
                                        begin
                                                OtbivonCard:=ChosenCard;//StrToInt(Edit5.Text);
                                                PodkidonCard:=ChosenCard;//StrToInt(Edit5.Text);
                                                //MessageBox(0,'Вы отбиваетесь','Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                               Otbitsya(Message.WParamLo, OtbivonCard);
                                        end;
                                3:
                                        Begin
                                                OtbivonCard:=ChosenCard;//StrToInt(Edit5.Text);
                                                PodkidonCard:=ChosenCard;//StrToInt(Edit5.Text);
                                                Podkinut(Message.WParamLo, PodkidonCard);
                                                //MessageBox(0,'Вы подкидываете','Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                        end;
                                4: ;
                                        //MessageBox(0,'Не подкидываете','Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                5:
                                        begin
                                                Attack := true;
                                                ClearTable;
                                                Rasdat;
                                        end;


                                6:
                                        begin
                                                Attack := true;
                                                ClearTable;
                                                Rasdat;
                                        end;
                                7:
                                        begin
                                                Attack := true;
                                                ClearTable;
                                                Rasdat;
                                        end;
                                8:
                                        begin
                                                ActivePlayer := 3;
                                                RedrawActivePlayer;

                                                //MessageBox(0,'Ваш ход','Подкидной дурак',MB_OK or MB_ICONINFORMATION);

                                                while Event.WaitFor(20) <> wrSignaled do
                                                        Application.ProcessMessages;
                                                while Chosen = false do
                                                        while Event.WaitFor(20) <> wrSignaled do
                                                                Application.ProcessMessages;

                                                Event.ResetEvent;
                                                ChangeForPlayer3(ChosenCard);


                                        end;
                                9:;
                                end;
                                ShowCards;
                                Message.Result :=1;
                        end;
                end;

                if (Message.WParamLo =4) or (Message.WParamLo =5)  then
                begin

                        OtbivonCard := Otbivon(TransfigureNum(Message.WParamLo),AttackCard);
                        CasesOtbivon(OtbivonCard);
                        PodkidonCard := Podkidon(TransfigureNum(Message.WParamLo),CardsOnTheTable);
                        CasesPodkidon(PodkidonCard);
                        SetWinnersEnd;
                        if (Message.WParamHi=0) then
                        begin
                                case Message.LParam of
                                1:
                                        Message.Result := FindC1(Message.WParamLo);
                                2:
                                        Message.Result := Otbivon1;
                                3:
                                        Message.Result := Otbivon2;
                                4:
                                        Message.Result := Otbivon3;
                                5:
                                        Message.Result := Podkidon1;
                                6:
                                        Message.Result := Podkidon2;
                                7:
                                        Message.Result := Podkidon3;
                                8:
                                        begin
                                                if Attack then
                                                        Message.Result := 1
                                                else
                                                        Message.Result:=0;
                                                Attack := false;
                                        end;
                                9:
                                        if EndFirstIsGone then
                                                Message.Result := 1
                                        else
                                                Message.Result := 0;
                                10:
                                        if EndSecondIsGone then
                                                Message.Result := 1
                                        else
                                                Message.Result := 0;

                                11:
                                        begin
                                                Message.Result := FindC11(Message.WParamLo);
                                        end;

                                end;
                        end
                        else
                        begin


                                case Message.LParam of
                                1:
                                       begin
                                                S:= 'Игрок' + IntToStr(Message.WParamLo-3) + ' принимает';
                                               //MessageBox(0,PChar(S),'Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                                sleep(2000);

                                               Prinyat(TransfigureNum(Message.WParamLo));
                                       end;
                                2:
                                        begin
                                               S:= 'Игрок' + IntToStr(Message.WParamLo-3) + ' отбивается';
                                               sleep(2000);
                                               //MessageBox(0,PChar(S),'Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                               Otbitsya(TransfigureNum(Message.WParamLo), OtbivonCard);
                                       end;
                                3:      Begin
                                               S:= 'Игрок' + IntToStr(Message.WParamLo-3) + ' подкидывает';
                                               //MessageBox(0,PChar(S),'Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                               sleep(2000);
                                               Podkinut(TransfigureNum(Message.WParamLo), PodkidonCard);
                                        end;
                                4:
                                        begin
                                                S:= 'Игрок' + IntToStr(Message.WParamLo-3) + ' ничего не делает';
                                               sleep(2000);
                                                //MessageBox(0,PChar(S),'Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                        end;


                                5:
                                        begin
                                                Attack := true;
                                                ClearTable;
                                        end;
                                6:
                                        begin

                                                ChangePlayerEnd(Message.WParamLo);
                                                RedrawActivePlayer;
                                        end;

                                7:
                                        CallFool;
                                end;
                                Message.Result := 1;
                                ShowCards;



                        end;




                end;

                if (Message.WParamLo = 6) then
                begin

                        SetWinnersEnd;
                        if (Message.WParamHi=0) then
                        begin
                                case Message.LParam of
                                1:
                                        Message.Result := FindC1(Message.WParamLo);
                                2:
                                        {if MessageBox(0,'Ваши действия','Подкидной дурак',MB_OK or MB_ICONINFORMATION)= ID_YES then
                                        begin
                                                Message.Result := 1;
                                                OtbivonCard:=ChosenCard;//StrToInt(Edit5.Text);
                                                PodkidonCard:=ChosenCard;//StrToInt(Edit5.Text);
                                        end
                                        else
                                                Message.Result := 0;
                                        }
                                        begin
                                                while Event.WaitFor(20) <> wrSignaled do
                                                        Application.ProcessMessages;
                                                if Chosen then
                                                        Message.Result := 1
                                                else
                                                        Message.Result := 0;
                                                Event.ResetEvent;

                                        end;


                                3:
                                        begin
                                                if Attack then
                                                        Message.Result := 1
                                                else
                                                        Message.Result := 0;
                                                Attack := false;
                                        end;
                                4:
                                        if EndFirstIsGone then
                                                Message.Result := 1
                                        else
                                                Message.Result := 0;
                                5:
                                        if EndSecondIsGone then
                                                Message.Result := 1
                                        else
                                                Message.Result := 0;
                                6:
                                        begin
                                                Message.Result := FindC11(Message.WParamLo);
                                        end;

                                end;
                        end
                        else
                        begin
                                case Message.LParam of
                                1:
                                       begin
                                               //MessageBox(0,'Принимаем','Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                               sleep(2000);
                                               Prinyat(TransfigureNum(Message.WParamLo));
                                       end;
                                2:
                                        begin
                                               //MessageBox(0,'Отбиваемся','Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                               sleep(2000);
                                               OtbivonCard:=ChosenCard;//StrToInt(Edit5.Text);
                                                PodkidonCard:=ChosenCard;//StrToInt(Edit5.Text);

                                               Otbitsya(TransfigureNum(Message.WParamLo), OtbivonCard);
                                       end;
                                3:      Begin
                                                OtbivonCard:=ChosenCard;//StrToInt(Edit5.Text);
                                                PodkidonCard:=ChosenCard;//StrToInt(Edit5.Text);
                                                Podkinut(TransfigureNum(Message.WParamLo), PodkidonCard);
                                                //MessageBox(0,'Подкидываем','Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                               sleep(2000);
                                         end;
                                4:      //MessageBox(0,'Не подкидываем','Подкидной дурак',MB_OK or MB_ICONINFORMATION);
                                               sleep(2000);
                                5:
                                        begin
                                                Attack := true;
                                                ClearTable;
                                        end;
                                6:
                                        begin
                                                ActivePlayer := 3;                                        
                                               RedrawActivePlayer;
//                                                MessageBox(0,'Ваш ход','Подкидной дурак',MB_OK or MB_ICONINFORMATION);

                                                while Event.WaitFor(20) <> wrSignaled do
                                                        Application.ProcessMessages;
                                                while Chosen=false do
                                                        while Event.WaitFor(20) <> wrSignaled do
                                                                Application.ProcessMessages;
                                                ChangeForPlayer3End(ChosenCard);
                                                Event.ResetEvent;

                                        end;
                                7:
                                        CallFool;
                                end;
                                Message.Result := 1;
                                ShowCards;
                        end;
                end;


{
                LWParamText.Text := IntToStr(Message.WParamLo);
                HWparamText.Text := IntToStr(Message.WParamHi);
                LParamText.Text := INtToStr(Message.LParam);
                ResultText.Text := IntToStr(Message.Result);

                if Edit2.Text = 'stop' then
                        MessageBox(0,'Продолжать','Подкидной дурак',MB_OK or MB_ICONINFORMATION);

}

        end       //Завершаем обработку сообщения \\\\
        else      //Вызываем стандартный обработчик родительского класса
        inherited WndProc(Message);

end;


procedure TForm1.Button2Click(Sender: TObject);
var
        B: TBitmap;
        T0 : TObject;
        i : byte;
        c : byte;
begin
{        Rasdacha;
        ShowCards;
 }
        c := random(36);

        while c<>35 do
                c := random(36);

end;



procedure TForm1.MyCard1Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 1;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard2Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 2;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;




end;

procedure TForm1.MyCard3Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 3;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;




end;

procedure TForm1.MyCard4Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 4;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;



end;

procedure TForm1.MyCard5Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 5;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;



end;

procedure TForm1.MyCard6Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 6;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;



end;

procedure TForm1.MyCard7Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 7;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;
end;

procedure TForm1.BitBtn1Click(Sender: TObject);
begin
//        AttackCard1.Picture.LoadFromFile('15I.bmp');
        ActivePlayerImage.Picture.LoadFromFile('ActivePlayer1.bmp');

//        AttackCard1.Picture.LoadFromFile('Empty.bmp');


end;

procedure TForm1.CurrentPlayerImageClick(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        Event.SetEvent;
        Chosen :=false;
end;

procedure TForm1.MyCard8Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 8;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;


end;

procedure TForm1.MyCard9Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 9;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard10Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 10;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard11Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 11;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard12Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 12;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.Mycard13Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 13;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard16Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 16;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard14Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 14;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard15Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 15;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard17Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 17;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard18Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 18;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard19Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 19;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard20Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 20;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard21Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 21;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard22Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 22;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard23Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 23;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard24Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 24;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;

end;

procedure TForm1.MyCard25Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 25;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;


end;

procedure TForm1.MyCard27Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 27;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;


end;

procedure TForm1.MyCard29Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 29;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;


end;

procedure TForm1.MyCard26Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 26;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;


end;

procedure TForm1.MyCard28Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 28;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;


end;

procedure TForm1.MyCard30Click(Sender: TObject);
var
        i : byte;
        Gone : byte;
        CardNum : byte;
begin
        CardNum := 30;
        Gone := 0;
        Event.SetEvent;
        Chosen := true;
        for i:=0 to 35 do
                if  i in Player3 then
                begin
                        Gone := Gone + 1;
                        if Gone = CardNum then
                                ChosenCard := i;

                end;


end;

end.

