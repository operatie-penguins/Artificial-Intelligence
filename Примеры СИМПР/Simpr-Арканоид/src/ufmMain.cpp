//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ufmMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#define  USERMESSAGE   "MyMessage"
//---------------------------------------------------------------------------
#define  YES   1
#define  NO   0
//---------------------------------------------------------------------------
#define   CONDITIONS   0
#define ACTIONS   1
//---------------------------------------------------------------------------
TufmArk *ufmArk;
//---------------------------------------------------------------------------


__fastcall TufmArk::TufmArk(TComponent* Owner)
	: TForm(Owner)
{
	mpGame = new Situation(PaintBox1);
}
//---------------------------------------------------------------------------


void __fastcall TufmArk::Button1Click(TObject *Sender)
{
	TDateTime D = TDateTime::CurrentDateTime();
	for(int i = 0; i < 1000; i++)
	{
		mpGame->turn();
	}
	ShowMessage((TDateTime::CurrentDateTime() - D).TimeString());
}
//---------------------------------------------------------------------------


void __fastcall TufmArk::FormCreate(TObject *Sender)
{
	OurMessage = RegisterWindowMessage("MyMessage");
}
//---------------------------------------------------------------------------


void __fastcall TufmArk::WndProc(Messages::TMessage &Message)
{
	if(Message.Msg == OurMessage)
	{

	 int nResult =
		 nResult = DoPhone(Message.WParamHi, Message.WParamLo, Message.LParam);

	 if(Loging->Checked)
		 Memo1->Lines->Add(AnsiString(Message.WParamHi) + " " +
										 AnsiString(Message.WParamLo) + " " +
										 AnsiString(Message.LParam) + " " +
										 AnsiString(nResult) );
	 Lifes->Caption = mpGame->mnLifes;
	 Score->Caption = mpGame->mnScore;

		Message.Result = nResult;
	}
	else
	{
		TCustomForm::WndProc(Message);
	}
}
//---------------------------------------------------------------------------


int TufmArk::DoPhone(Word WParamHi, Word WParamLo, int LParam)
{
	int Type = WParamHi;
	int Table = WParamLo;
	int Num = LParam;

	switch(Type)
	{
		case 0:
		{
			switch(Table)
			{
				case 1:
				{
					switch(Num)
					{
						case 1:
						{
							return Start->Tag;
						}
						case 2:
						{
              return mpGame->mfFirstMove;
						}
						case 3:
						{
							return (mpGame->mnLifes == 0);
						}
						case 4:
						{
              return (BrickStorage::getSingle()->size() == 0);
            }
          }
				}
				case 2:
				{
					switch(Num)
					{
						case 1:
						{
							return mpGame->isBrickImpact();
						}
						case 2:
						{
							return Ball::getSingle()->BoardImpact();
						}
						case 3:
						{
							return Ball::getSingle()->FloorImpact();
						}
						case 4:
						{
              return (mpGame->mnFreeTurns >= 3);
						}
					}
				}
				case 3:
				{
					switch(Num)
					{
						case 1:
						{
              return mpGame->isSimpleBrick();
						}
						case 2:
						{
              return mpGame->hitTopBottom();
						}
						case 3:
						{
							return mpGame->isInstantBrick();
            }
          }
				}
				case 4:
				{
					switch(Num)
					{
						case 1:
						{
              return (Ball::getSingle()->getXPos() < 1);
						}
						case 2:
						{
              return (Ball::getSingle()->getXPos() + cnBallRadius * 2 > cnWidth - 1 );
						}
						case 3:
						{
							return (Ball::getSingle()->getYPos() < 1);
            }
					}
				}
				case 5:
				{
					switch(Num)
					{
						case 1:
						{
							return mpGame->canCountFinalPos();
						}
						case 2:
						{
							return ( (Board::getSingle()->getXPos() < 
											 (cnWidth - Board::getSingle()->mnSize) / 2) );
						}
						case 3:
						{
							return ( (Board::getSingle()->getXPos() > 
											 (cnWidth + Board::getSingle()->mnSize)/ 2) );
						}
						case 4:
						{
							return ( Board::getSingle()->getXPos() > (mpGame->mnFinalPos -
											 cnBallRadius * 2) );
						}
						case 5:
						{
							return ( Board::getSingle()->getXPos() + 
											 Board::getSingle()->mnSize < (mpGame->mnFinalPos +
											 cnBallRadius * 2) );
						}
						case 6:
						{
							return ( ( Board::getSingle()->getXPos() <= (mpGame->mnFinalPos  -
											 cnBallRadius * 2)) &&
											 ( Board::getSingle()->getXPos() + 
												 Board::getSingle()->mnSize >= (mpGame->mnFinalPos +
											 cnBallRadius * 2) )     );
						}
          }
				}
			}
		}
		case 1:
		{
			switch(Table)
			{
				case 1:
				{
					switch(Num)
					{
						case 1:
						{
              return 1;
						}
						case 2:
						{
							mpGame->baseSpeed();
							return 1;
						}
						case 3:
						{
							ShowMessage("Win!!!!!");
							return 1;
						}
						case 4:
						{
							ShowMessage("Attempt to win ended in failure");
							return 1;
						}
						case 5:
						{
							mpGame->turn();
							Label1->Caption =
							  AnsiString(Ball::getSingle()->getSpeed()).SubString(1, 6);
							return 1;
						}
						case 6:
						{
							mpGame->mfFirstMove = false;
							return 1;
						}
          }
				}
				case 2:
				{
					switch(Num)
					{
						case 1:
						{
              mpGame->mnLifes--;
              return 1;
						}
						case 2:
						{
							if( Ball::getSingle()->BoardImpact() && !mpGame->mfFirstBoard )
							{
								return 1;
              }
							Ball::getSingle()->mnVSpeed = -1 * Ball::getSingle()->mnVSpeed;  
							return 1;
						}
						case 3:
						{
              mpGame->randomSpeedViolation();
							mpGame->mnFreeTurns++;
							mpGame->mfFirstBoard = false;
							Engine::getSingle()->addEffect(Ball::getSingle()->getXPos() + cnBallRadius,
																						 Ball::getSingle()->getYPos() + cnBallRadius,
																						 0,
																						 clYellow);
							return 1;
						}
						case 4:
						{
							BrickStorage::getSingle()->del(Random(BrickStorage::getSingle()->size()));
							mpGame->mnFreeTurns--;
							return 1;
            }
          }
				}
				case 3:
				{
					switch(Num)
					{
						case 1:
						{
							BrickStorage::getSingle()->del(Ball::getSingle()->BrickImpact());
							return 1;
						}
						case 2:
						{
							Ball::getSingle()->mnVSpeed = -1 * Ball::getSingle()->mnVSpeed; 
							return 1;
						}
						case 3:
						{
							Ball::getSingle()->mnHSpeed = -1 * Ball::getSingle()->mnHSpeed;
							return 1;
						}
						case 4:
						{
							BrickStorage::getSingle()->get(Ball::getSingle()
																			 ->BrickImpact())->mnType--;
							BrickStorage::getSingle()->get(Ball::getSingle()
																			 ->BrickImpact())->mnBitmapNum--;
							return 1;
						}
						case 5:
						{
							mpGame->mnScore++;
							mpGame->mnFreeTurns = 0;
							Engine::getSingle()->addEffect(Ball::getSingle()->getXPos() + 5,
																						 Ball::getSingle()->getYPos() + 5,
																             0, clYellow);
            }
					}
				}
				case 4:
				{
					switch(Num)
					{
						case 1:
						{
							Ball::getSingle()->mnVSpeed = -1 * Ball::getSingle()->mnVSpeed;
							return 1;
						}
						case 2:
						{
							Ball::getSingle()->mnHSpeed = -1 * Ball::getSingle()->mnHSpeed;
							return 1;
            }
          }
				}
				case 5:
				{
					switch(Num)
					{
						case 1:
						{
              Board::getSingle()->mnSpeed = 0;
							return 1;
						}
						case 2:
						{
							Board::getSingle()->mnSpeed = -1 * cnBoardSpeed;
							return 1;
						}
						case 3:
						{
						  Board::getSingle()->mnSpeed = cnBoardSpeed;
							return 1;
            }
					}
				}
			}
		}
	}

	return YES;
}
//---------------------------------------------------------------------------
void __fastcall TufmArk::Button2Click(TObject *Sender)
{
	fLog = false;
}
//---------------------------------------------------------------------------

void __fastcall TufmArk::StartClick(TObject *Sender)
{
	Start->Tag = 1;
}
//---------------------------------------------------------------------------


































/*switch(Type)
	{
	
		case CONDITIONS:	// �������
		{
			
			switch(Table)
			{

				case 1:
				{

					switch(Num)
					{

						case 1:
						{
							return mpGame->isBrickImpact();
						}
						case 2:
						{
              return Ball::getSingle()->FloorImpact();
						}
						case 3:
						{
              return Ball::getSingle()->BoardImpact();
						}
						case 4:
						{
							return (Ball::getSingle()->mnVSpeed == 0);
						}
						case 5:
						{
							return (BrickStorage::getSingle()->size() == 0);
						}
						case 6:
						{
							return mpGame->zeroLifes(); 
						}
						case 7:
						{
							return mpGame->isFloorBonus();
						}
						case 8:
						{
							return mpGame->isBoardBonus();
            }

					}
				
				}
				case 2:
				{

					switch(Num)
					{
					
						case 1:
						{
              return mpGame->isBrickBonus();
						}
						case 2:
						{
              return mpGame->isSimpleBrick();
						}
						case 3:
						{
              return mpGame->isAcidBall();
						}
						case 4:
						{
              return mpGame->isInstantBrick();
            }
					
					}
				
				}
				case 3:
				{

					switch(Num)
					{
					
						case 1:
						{
              return mpGame->isLess25();
						}
						case 2:
						{
							return mpGame->is4NoImpact();
						}
						case 3:
						{
              return (Board::getSingle()->mnSpeed != 0);
						}
						case 4:
						{
							return (Board::getSingle()->getAcceleration() > 0);
						}
						case 5:
						{
						  return (Board::getSingle()->getAcceleration() < 0);
            }
					
					}
				
				}
				case 4:
				{

					switch(Num)
					{

						case 1:
						{
							return (mpGame->getBonusTurns() == 0);
						}
						case 2:
						{
							return (mpGame->getBonusTurns() == -1);
						}
						case 3:
						{
							return (mpGame->getBonusTurns() == 1);
						}
						case 4:
						{
							return (mpGame->getBallPosCord() == -1);
						}
						case 5:
						{
							return (mpGame->getBallPosCord() == 1);
						}
						case 6:
						{
							return (mpGame->genUsefulStrike() < 0);
						}
						case 7:
						{
							return (mpGame->genUsefulStrike() > 0);
						}
						case 8:
						{
							return 0;
						}
						case 9:
						{
              return 0;
            }
					
					}
				
				}
				case 5:
				{
				  return mpGame->mfPlay;
				}
				
			}
			
		}

		case ACTIONS:	// ��������
		{

			switch(Table)
			{

				case 1:
				{

					switch(Num)
					{

						case 1:
						{
							Board::getSingle()->setXPos(cnXCenter);
							Board::getSingle()->setYPos(cnBoardStart);
							Board::getSingle()->mnSize = cnInitialBoardSize;

							Ball::getSingle()->setXPos((cnWidth >> 1) - cnBallRadius);
							Ball::getSingle()->setYPos(cnBoardStart - cnBallRadius * 2);
							Ball::getSingle()->mnVSpeed = 0;
							Ball::getSingle()->mnHSpeed = 0;

							return YES;
						}
						case 2:
						{
							ShowMessage("Win");
							return YES;
						}
						case 3:
						{
							ShowMessage("Lose");
							return YES;
						}
						case 4:
						{
              mpGame->mnLifes--;
							return YES;
						}
						case 5:
						{
							// TODO: ��������� �����
							return YES;
						}
						case 6:
						{
							BonusStorage::getSingle()->del(mpGame->floorBonus());
							return YES;
						}
						case 7:
						{
							Ball::getSingle()->baseSpeed();
							return YES;
            }

					}
				
				}
				case 2:
				{

					switch(Num)
					{

						case 1:
						{
							BrickStorage::getSingle()->del(Ball::getSingle()->BrickImpact());
							return YES;
            }
						case 2:
						{
							BrickStorage::getSingle()->get(
											Ball::getSingle()->BrickImpact())->mnType--;
							BrickStorage::getSingle()->get(
											Ball::getSingle()->BrickImpact())->mnBitmapNum--;
							return YES;
						}
						case 3:
						{
							BonusStorage::getSingle()->add(new Bonus(0,
							BrickStorage::getSingle()->get(
											Ball::getSingle()->BrickImpact())->getXPos(),
							BrickStorage::getSingle()->get(
											Ball::getSingle()->BrickImpact())->getYPos()));
							return YES;
						}
						case 4:
						{
              BrickStorage::getSingle()->get(
											Ball::getSingle()->BrickImpact())->mfBonus = false;
							BrickStorage::getSingle()->get(
											Ball::getSingle()->BrickImpact())->mnBonusType = -1;
							return YES;
						}
						case 5:
						{
							PosCord* pPos = mpGame->genStrikeSpeed(0);
							Ball::getSingle()->mnVSpeed = pPos->getYPos() * -1;
							Ball::getSingle()->mnHSpeed = pPos->getXPos();
							return YES;
						}
						case 6:
						{
							mpGame->mnScore++;
							return YES;
						}
						case 7:
						{
							mpGame->mnScore += BrickStorage::getSingle()->get(
											Ball::getSingle()->BrickImpact())->mnType;
							return YES;
						}
						case 8:
						{
							mpGame->mnTWOI = 0;
							return YES;
            }

					}
				
				}
				case 3:
				{

					switch(Num)
					{

						case 1:
						{
							mpGame->randomDemolution();
							return YES;
						}
						case 2:
						{
							int nAdd = 1;
							if(Board::getSingle()->mnSpeed < 0)
							{
                nAdd = -1;
              }
							Ball::getSingle()->mnHSpeed += nAdd;
							return YES;
						}
						case 3:
						{
							Ball::getSingle()->mnHSpeed += Board::getSingle()->getAcceleration();
							return YES;
						}
						case 4:
						{
							Ball::getSingle()->mnHSpeed -= Board::getSingle()->getAcceleration();
							return YES;
						}
						case 5:
						{
							PosCord* pPos = mpGame->genStrikeSpeed(mpGame->getCenterShift());
							Ball::getSingle()->mnVSpeed = pPos->getYPos();
							Ball::getSingle()->mnHSpeed = pPos->getXPos();
							return YES;
						}
						case 6:
						{
							Board::getSingle()->mnSpeed = 0;
							return YES;
            }
					
					}
				
				}
				case 4:
				{

					switch(Num)
					{

						case 1:
						{
							Board::getSingle()->mnSpeed = Board::getSingle()->mnMaxSpeed;
							return YES;
						}
						case 2:
						{
							Board::getSingle()->mnSpeed = Board::getSingle()->mnMaxSpeed * -1;
							return YES;
						}
						case 3:
						{
							Board::getSingle()->mnSpeed = Board::getSingle()->mnMaxSpeed;
							return YES;
						}
						case 4:
						{
							Board::getSingle()->mnSpeed = Board::getSingle()->mnMaxSpeed * -1;
							return YES;
						}
						case 5:
						{
              return YES;
						}
						case 6:
						{
              return YES;
            }

					}
				
				}
				case 5:
				{
					 mpGame->moveBonus();
           mpGame->turn();
					 return YES;
				}
				
			}


		}
		
	}  
			*/
