Приложение
Обработка сообщений:


void __fastcall TmainForm::WndProc(Messages::TMessage &Message)
{
    if(Message.Msg == msgSimpr)
    {
        Message.Result=work(Message.WParamHi, Message.WParamLo, Message.LParam);
        if((Message.WParamHi==Actions)&&N10->Checked) Sleep(delayTime);
    }
    else TCustomForm::WndProc(Message);
}
//-----------------------------------------------------------------------

bool TmainForm::work(Word WParamHi, Word WParamLo, int LParam)
{
    static int position = 0,
               criminals = numberCrime,
               catched = 0,
               disappeard = 0;

    switch(WParamHi)
    {
            case Conditions :
            {
                switch(WParamLo)
                {
                    case 1 :
                    {
                        switch(LParam)
                        {
                            case 1: return (position < numberCop);
                            case 2: return (position >= numberCop);
                            case 3: return (criminals == 0);
                            case 4: return (catched > disappeard);
                            case 5: return (catched==numberCrime);
                            case 6: return (disappeard==numberCrime);
                        }
                    }
                    case 2 :
                    {
                        switch(LParam)
                        {
                            case 1: return (queue[position]->alert(1)!=-1);
                            case 2: return (queue[position]->look()==up);
                            case 3: return (queue[position]->look()==right);
                            case 4: return (queue[position]->look()==down);
                            case 5: return (queue[position]->look()==left);
                            case 6: return queue[position]->canGo();
                            case 7: return queue[position]->onEdge();
                            case 8: return ifCop(queue[position]->getX(),queue[position]->getY());
                        }
                    }
                    case 3 :
                    {
                        switch(LParam)
                        {
                            case 1: return (queue[position]->alert(2)!=-1);
                            case 2: return (queue[position]->look()==up);
                            case 3: return (queue[position]->look()==right);
                            case 4: return (queue[position]->look()==down);
                            case 5: return (queue[position]->look()==left);
                            case 6: return queue[position]->canGo();
                            case 7: return (queue[position]->getRotations()>=4);
                        }
                    }
                }
            }
            case Actions :
            {
                switch(WParamLo)
                {
                    case 1 :
                    {
                        switch(LParam)
                        {
                            case 1:
                            {
                                say("Все преступники переловлены!");
                                return true;
                            }
                            case 2:
                            {
                                say("Все преступники ушли!");
                                return true;
                            }
                            case 3:
                            {
                                say("Больше половины преступников поймано, копы - молодцы.");
                                return true;
                            }
                            case 4:
                            {
                                say("Больше половины преступников сбежало, копы плохо работают.");
                                return true;
                            }
                        }
                    }
                    case 2 :
                    {
                        switch(LParam)
                        {
                            case 1:
                            {
                                queue[position]->go();
                                return true;
                            }
                            case 2:
                            {
                                queue[position]->turn(up);
                                return true;
                            }
                            case 3:
                            {
                                queue[position]->turn(right);
                                return true;
                            }
                            case 4:
                            {
                                queue[position]->turn(down);
                                return true;
                            }
                            case 5:
                            {
                                queue[position]->turn(left);
                                return true;
                            }
                            case 6:
                            {
                                queue[position]->hide();
                                return true;
                            }
                            case 7:
                            {
                                catched++;
                                criminals--;
                                qAvaible[position-numberCop]=false;
                                return true;
                            }
                            case 8:
                            {
                                disappeard++;
                                criminals--;
                                qAvaible[position-numberCop]=false;
                                return true;
                            }
                            case 9: return true;
                            case 10:
                            {
                                queue[position]->turn(random(4));
                                return true;
                            }
                            case 11:
                            {
                                if(!qFree())
                                {
                                    do
                                    {
                                        if(position<numberCop+numberCrime-1) position++;
                                        else position=0;
                                    }
                                    while((position>=numberCop)&&!qAvaible[position-numberCop]);
                                }

                                return true;
                            }
                        }
                    }
                    case 3 :
                    {
                        switch(LParam)
                        {
                            case 1:
                            {
                                queue[position]->go();
                                return true;
                            }
                            case 2:
                            {
                                queue[position]->turn(up);
                                return true;
                            }
                            case 3:
                            {
                                queue[position]->turn(right);
                                return true;
                            }
                            case 4:
                            {
                                queue[position]->turn(down);
                                return true;
                            }
                            case 5:
                            {
                                queue[position]->turn(left);
                                return true;
                            }
                            case 6:
                            {
                                queue[position]->turn(random(4));
                                return true;
                            }
                            case 7: return true;
                            case 8:
                            {
                                if(!qFree())
                                {
                                    do
                                    {
                                        if(position<numberCop+numberCrime-1) position++;
                                        else position=0;
                                    }
                                    while((position>=numberCop)&&!qAvaible[position-numberCop]);
                                }
                                return true;
                            }
                        }
                    }
                }
            }
    }

    return false;
}
//---------------------------------------------------------------------------
