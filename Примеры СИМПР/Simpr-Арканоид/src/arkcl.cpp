#include <math.h>

#include "arkcl.h"
//---------------------------------------------------------------------------


void Situation::loadLevel()
{
  mnSBA = 0;
	TStringList* pList = new TStringList();
	pList->LoadFromFile(Utils::getPath() + cstrLevelPath);
	for(int i = 0; i < cnBricksMax; i++)
	{
		int BT = pList->Strings[0].SubString(i * 2 + 1, 1).ToInt();
		int nX = (i % 10) * cnBW;
		int nY = (i / 10) * cnBH;

		if(BT != 0)
		{
			int BonusType = -1 - enBless;
			if(BT != 6)
			{
				BonusType = Utils::genBonus();
			}
			BrickStorage::getSingle()->add(new Brick(BT - 1, BonusType, nX, nY));
			mnSBA++;
		}
	}
	Board::getSingle()->setXPos(cnXCenter);
	Board::getSingle()->setYPos(cnBoardStart);
	Board::getSingle()->mnSize = cnInitialBoardSize;

	Ball::getSingle()->setXPos((cnWidth >> 1) - cnBallRadius);
	Ball::getSingle()->setYPos(cnBoardStart - cnBallRadius * 2);

	mnScore = 0;
}
//---------------------------------------------------------------------------


void Situation::baseSpeed()
{
  Ball::getSingle()->baseSpeed();
}
//---------------------------------------------------------------------------


void Situation::turn()
{
  mfFirstMove = false;

	Ball::getSingle()->move();
	Board::getSingle()->move();

	if( !mfFirstBoard && !Ball::getSingle()->BoardImpact())
    mfFirstBoard = true;

	Engine::getSingle()->draw();
}
//---------------------------------------------------------------------------


int Situation::floorBonus()
{
	for(int i = 0; i < BonusStorage::getSingle()->size(); i++)
	{
		Bonus* pBonus = BonusStorage::getSingle()->get(i);
		if(pBonus->getYPos() > cnHeight - cnBonusSize)
		{
      return i;
    }
	}
	return -1;
}
//---------------------------------------------------------------------------


int Situation::boardBonus()
{
	for(int i = 0; i < BonusStorage::getSingle()->size(); i++)
	{
		Bonus* pBonus = BonusStorage::getSingle()->get(i);
		if(pBonus->getYPos() > cnBoardStart - cnBonusSize)
		{
			if( (pBonus->getXPos() + cnBonusSize > Board::getSingle()->getXPos()) &&
					(pBonus->getXPos() < Board::getSingle()->getXPos() +
															 Board::getSingle()->mnSize) )
			{
				return i;
      }
    }
	}
	return -1;
}
//---------------------------------------------------------------------------


int Situation::getBottom()
{
	int nBottom = 0;
	for(int i = 0; i < BrickStorage::getSingle()->size(); i++)
	{
		Brick* pBrick = BrickStorage::getSingle()->get(i);
		if(pBrick->getYPos() + cnBH > nBottom)
		{
			nBottom = pBrick->getYPos() + cnBH;
    }
	}
	return nBottom;
}
//---------------------------------------------------------------------------


int Situation::getBonusTurns()
{
	int nBLP = Board::getSingle()->getXPos();
	int nBRP = nBLP + Board::getSingle()->mnSize;

	int nSize = BonusStorage::getSingle()->size();

	for(int i = 0; i < nSize; i++)
	{
		int nBoardDist = getArrival() * Board::getSingle()->mnMaxSpeed;

		Bonus* pBonus = BonusStorage::getSingle()->get(i);

		int nBonLP = pBonus->getXPos();
		int nBonRP = nBonLP + cnBonusSize;

		int nBonDist = 0;

		int nWhere = 0;

		if(nBonLP > nBRP)
		{
			nBonDist = nBonLP - nBRP;
			nWhere = 1;
			if(nBonLP > (cnWidth >> 1))
			{
				nBonDist += nBonLP;
			}
			else
			{
        nBonDist += (cnWidth - nBonLP);
      }
		}
		else
		{
			if(nBonRP < nBLP)
			{
        nWhere = -1;
				nBonDist = nBLP - nBonRP;
				if(nBonRP < (cnWidth >> 1))
				{
					nBonDist += (cnWidth - nBonRP);
				}
				else
				{
					nBonDist += nBonRP;
				}
			}
		}

		if(nBonDist <= nBoardDist)
		{
      return nWhere;
    }

	}
	return 2;
}
//---------------------------------------------------------------------------


PosCord* Situation::genStrikeSpeed(int anCenterShift)
{
	double dSpeed = Ball::getSingle()->getSpeed();
	double dHSpeed = abs(Ball::getSingle()->mnHSpeed);

	if(dSpeed < 0.01)
	{
		return new PosCord(0, 0);
  }

	double dFallAngel = asin(dHSpeed / dSpeed);

	double dAddAngel = asin(double(2 * anCenterShift) /
													double(3 * Board::getSingle()->mnSize));

	double dResultAngel = dFallAngel + dAddAngel;

	/*
	ShowMessage("fall angel " + AnsiString(dFallAngel));
	ShowMessage("add angel " + AnsiString(dAddAngel));
	*/

	if(dResultAngel > M_PI / 2.0)
	{
		dResultAngel = M_PI / 2.0;
	}
	if(dResultAngel < M_PI / 6)
	{
		dResultAngel = M_PI / 6;
	}

//	ShowMessage("result angel " + AnsiString(dResultAngel));

	double dZ = 1;
	if(Ball::getSingle()->mnHSpeed < 0)
	{
    dZ = -1;
	}

	if(sin(dResultAngel) < 0.01)
	{
		ShowMessage("Sin");
		return new PosCord( 0, -1.0 * dSpeed );
	}
	if(cos(dResultAngel) < 0.01)
	{
	  ShowMessage("Cos");
		return new PosCord( dSpeed, 0 );
	}

	return new PosCord(dZ * dSpeed * sin(dResultAngel),
																		 -1.0 * dSpeed * cos(dResultAngel) );

}
//---------------------------------------------------------------------------


int Situation::genUsefulStrike()
{
  return 0;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
