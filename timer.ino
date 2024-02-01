#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C _lcd1(0x27, 20, 4);
int _dispTempLength1=0;
boolean _isNeedClearDisp1;
bool _gtv1;
bool _gtv2;
bool _gtv4;
String _swi3;
int _disp4oldLength = 0;
bool FTrig_2_Out = 0;
bool FTrig_2_OldStat = 0;
bool _trgrt3 = 0;
bool _trgrt3I = 0;
bool _count4I = 0;
int _count4_Value = 0;
bool _count4MinLO = 0;
int _disp5oldLength = 0;
bool _trgrt2 = 0;
bool _trgrt2I = 0;
bool _count2I = 0;
int _count2_Value = 0;
bool _count2MaxLO = 0;
bool _gen2I = 0;
bool _gen2O = 0;
unsigned long _gen2P = 0UL;
bool _gen1I = 0;
bool _gen1O = 0;
unsigned long _gen1P = 0UL;
String _swi2;
bool _tim1I = 0;
bool _tim1O = 0;
unsigned long _tim1P = 0UL;
bool _trgr2 = 0;
bool _count3I = 0;
int _count3_Value = 0;
bool _count3MinLO = 0;
int _disp3oldLength = 0;
bool _gen3I = 0;
bool _gen3O = 0;
unsigned long _gen3P = 0UL;
bool _bounseInputD11S = 0;
bool _bounseInputD11O = 0;
unsigned long _bounseInputD11P = 0UL;
int _disp6oldLength = 0;
bool _bounseInputD12S = 0;
bool _bounseInputD12O = 0;
unsigned long _bounseInputD12P = 0UL;
byte _mux1;
bool _trgr3 = 0;
int _disp7oldLength = 0;
bool _bounseInputD2S = 0;
bool _bounseInputD2O = 0;
unsigned long _bounseInputD2P = 0UL;
void setup()
{
    pinMode(11, INPUT_PULLUP);
    pinMode(2, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(3, OUTPUT);
    digitalWrite(3, 0);
    pinMode(5, OUTPUT);
    digitalWrite(5, 0);
    Wire.begin();
    delay(10);
    _lcd1.init();
    _lcd1.backlight();
    _bounseInputD12O =  digitalRead(12);
    _bounseInputD2O =  digitalRead(2);
    _bounseInputD11O =  digitalRead(11);
}
void loop()
{
    if (_isNeedClearDisp1) 
    {
        _lcd1.clear();
        _isNeedClearDisp1= 0;
    }
    bool  _bounceInputTmpD2 =  (digitalRead (2));
    if (_bounseInputD2S)
    {
        if (millis() >= (_bounseInputD2P + 40))
        {
            _bounseInputD2O= _bounceInputTmpD2;
            _bounseInputD2S=0;
        }
    }
    else
    {
        if (_bounceInputTmpD2 != _bounseInputD2O)
        {
            _bounseInputD2S=1;
            _bounseInputD2P = millis();
        }
    }
    bool  _bounceInputTmpD11 =  (digitalRead (11));
    if (_bounseInputD11S)
    {
        if (millis() >= (_bounseInputD11P + 40))
        {
            _bounseInputD11O= _bounceInputTmpD11;
            _bounseInputD11S=0;
        }
    }
    else
    {
        if (_bounceInputTmpD11 != _bounseInputD11O)
        {
            _bounseInputD11S=1;
            _bounseInputD11P = millis();
        }
    }
    bool  _bounceInputTmpD12 =  (digitalRead (12));
    if (_bounseInputD12S)
    {
        if (millis() >= (_bounseInputD12P + 40))
        {
            _bounseInputD12O= _bounceInputTmpD12;
            _bounseInputD12S=0;
        }
    }
    else
    {
        if (_bounceInputTmpD12 != _bounseInputD12O)
        {
            _bounseInputD12S=1;
            _bounseInputD12P = millis();
        }
    }
    //Плата:1
    if (!(_bounseInputD12O))
    {
         if (_tim1I) 
        {
             if (_isTimer(_tim1P, 2000)) 
            {
                _tim1O = 1;
            }
        }
         else 
        {
            _tim1I =1;
            _tim1P = millis();
        }
    }
     else 
    {
        _tim1O = 0;
        _tim1I = 0;
    }
    if (_tim1O) 
    {
         if (_trgrt3I) 
        {
             _trgrt3 = 0;
        }
         else 
        {
            _trgrt3 = 1;
            _trgrt3I = 1;
        }
    }
     else 
    {
        _trgrt3 = 0;
        _trgrt3I = 0;
    }
    ;
    if(!(_bounseInputD2O)) _trgr3 = 0;
    if(_trgrt3) _trgr3 = 1;
    if (((_trgr3) && (!(!(_bounseInputD12O))))) 
    {
         if (! _gen2I) 
        {
            _gen2I = 1;
            _gen2O = 1;
            _gen2P = millis();
        }
    }
     else 
    {
        _gen2I = 0 ;
        _gen2O= 0;
    }
    if (_gen2I) 
    {
          if (_isTimer (_gen2P , 500)) 
        {
             _gen2P = millis();
            _gen2O = ! _gen2O;
        }
    }
    FTrig_2_Out = 0;
    if ((!(_trgr3))&&(FTrig_2_OldStat))
    {
        FTrig_2_Out = 1;
    }
    FTrig_2_OldStat = _trgr3;
    if (((FTrig_2_Out) || (((_gtv2) && (!(_gtv4))))))
    {
        _count4_Value = 59;
    }
     else 
    {
        if (_gen2O)
        {
            if (! _count4I) 
            {
                _count4I = 1;
                if(_count4_Value > 0) 
                {
                    _count4_Value = _count4_Value - 1;
                }
            }
        }
         else 
        {
            _count4I = 0;
        }
    }
    _count4MinLO = _count4_Value <= 0;
    if (!(_bounseInputD12O)) 
    {
         if (_trgrt2I) 
        {
             _trgrt2 = 0;
        }
         else 
        {
            _trgrt2 = 1;
            _trgrt2I = 1;
        }
    }
     else 
    {
        _trgrt2 = 0;
        _trgrt2I = 0;
    }
    ;
    if(!(_bounseInputD2O)) _trgr2 = 0;
    if(_trgrt2) _trgr2 = 1;
    if (_gtv1)
    {
        _count2_Value = 0;
    }
     else 
    {
        if (((!(_trgr3)) && (_trgr2) && (!(_bounseInputD11O))))
        {
            if (! _count2I) 
            {
                _count2I = 1;
                if(_count2_Value < 5) 
                {
                    _count2_Value = _count2_Value + 1;
                }
            }
        }
         else 
        {
            _count2I = 0;
        }
    }
    _count2MaxLO = _count2_Value >= 5;
    _gtv1 = _count2MaxLO;
    if((_count2_Value) == 0) 
    {
        _mux1 = 1;
    }
    if((_count2_Value) == 1) 
    {
        _mux1 = 3;
    }
    if((_count2_Value) == 2) 
    {
        _mux1 = 5;
    }
    if((_count2_Value) == 3) 
    {
        _mux1 = 10;
    }
    if((_count2_Value) == 4) 
    {
        _mux1 = 15;
    }
    if (_trgr2) 
    {
        _dispTempLength1 = (((((String(_mux1, DEC))) + (String(" hv"))))).length();
        if (_disp4oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp4oldLength = _dispTempLength1;
        _lcd1.setCursor(12, 0);
        _lcd1.print(((((String(_mux1, DEC))) + (String(" hv")))));
    }
     else 
    {
        if (_disp4oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp4oldLength = 0;
        }
    }
    if (_trgrt3)
    {
        _count3_Value = (_mux1)-(1);
    }
     else 
    {
        if (_gtv2)
        {
            if (! _count3I) 
            {
                _count3I = 1;
                if(_count3_Value > 0) 
                {
                    _count3_Value = _count3_Value - 1;
                }
            }
        }
         else 
        {
            _count3I = 0;
        }
    }
    _count3MinLO = _count3_Value <= 0;
    _gtv4 = _count3MinLO;
    if((_count3_Value) > (9))
    {
        _swi2=(String(_count3_Value, DEC));
    }
    else
    {
        _swi2=((String(" ")) + ((String(_count3_Value, DEC))));
    }
    if (((_trgr3) && (_trgr2))) 
    {
        _dispTempLength1 = ((_swi2)).length();
        if (_disp5oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp5oldLength = _dispTempLength1;
        _lcd1.setCursor(6, 2);
        _lcd1.print((_swi2));
    }
     else 
    {
        if (_disp5oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp5oldLength = 0;
        }
    }
    if (((_count3MinLO) && (_count4MinLO) && (_trgr3))) 
    {
        if (! _gen1I) 
        {
            _gen1I = 1;
            _gen1O = 1;
            _gen1P =  millis();
        }
    }
     else 
    {
        _gen1I = 0 ;
        _gen1O= 0;
    }
     if (_gen1I) 
    {
         if (_gen1O) 
        {
             if (_isTimer(_gen1P , 600)) 
            {
                 _gen1P = millis();
                _gen1O = 0;
            }
        }
         else  
        {
             if (_isTimer(_gen1P , 1000)) 
            {
                  _gen1P = millis();
                _gen1O = 1;
            }
        }
    }
    digitalWrite(3, _gen1O);
    if (_gen1O) 
    {
        if (! _gen3I) 
        {
            _gen3I = 1;
            _gen3O = 1;
            _gen3P =  millis();
        }
    }
     else 
    {
        _gen3I = 0 ;
        _gen3O= 0;
    }
     if (_gen3I) 
    {
         if (_gen3O) 
        {
             if (_isTimer(_gen3P , 150)) 
            {
                 _gen3P = millis();
                _gen3O = 0;
            }
        }
         else  
        {
             if (_isTimer(_gen3P , 50)) 
            {
                  _gen3P = millis();
                _gen3O = 1;
            }
        }
    }
    digitalWrite(5, _gen3O);
    _gtv2 = _count4MinLO;
    if((_count4_Value) > (9))
    {
        _swi3=(String(_count4_Value, DEC));
    }
    else
    {
        _swi3=((String("0")) + ((String(_count4_Value, DEC))));
    }
    if (_trgr3) 
    {
        _dispTempLength1 = ((_swi3)).length();
        if (_disp7oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp7oldLength = _dispTempLength1;
        _lcd1.setCursor(9, 2);
        _lcd1.print((_swi3));
    }
     else 
    {
        if (_disp7oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp7oldLength = 0;
        }
    }
    if (_trgr2) 
    {
        _dispTempLength1 = (String("TAYMER")).length();
        if (_disp3oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp3oldLength = _dispTempLength1;
        _lcd1.setCursor(5, 0);
        _lcd1.print(String("TAYMER"));
    }
     else 
    {
        if (_disp3oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp3oldLength = 0;
        }
    }
    if (_trgr3) 
    {
        _dispTempLength1 = (String(":")).length();
        if (_disp6oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp6oldLength = _dispTempLength1;
        _lcd1.setCursor(8, 2);
        _lcd1.print(String(":"));
    }
     else 
    {
        if (_disp6oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp6oldLength = 0;
        }
    }
}
bool _isTimer(unsigned long startTime, unsigned long period)
{
    unsigned long currentTime;
    currentTime = millis();
    if (currentTime>= startTime) 
    {
        return (currentTime>=(startTime + period));
    }
     else 
    {
        return (currentTime >=(4294967295-startTime+period));
    }
}
