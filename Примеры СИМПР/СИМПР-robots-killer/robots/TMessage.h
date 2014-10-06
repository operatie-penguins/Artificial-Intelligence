struct TMessage
{
    unsigned long Msg;
    union
    {
       struct
       {

           WORD WParamLo;
           WORD WParamHi;
           WORD LParamLo;
           WORD LParamHi;
           WORD ResultLo;
           WORD ResultHi;               
       };
       struct
       {
           long WParam;
           long LParam;
           long Result;    
       };
    };
};