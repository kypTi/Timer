#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C _lcd1(0x27, 16, 2);
int _dispTempLength1=0;
boolean _isNeedClearDisp1;
bool _gtv1 = 0;
bool _count1I = 0;
int _count1_Value = 0;
bool _count1MinLO = 0;
byte _mux2;
bool _count2I = 0;
int _count2_Value = 0;
bool _count2MaxLO = 0;
int _disp2oldLength = 0;
int _disp4oldLength = 0;
int _disp3oldLength = 0;
bool _bounseInputD5S = 0;
bool _bounseInputD5O = 0;
unsigned long _bounseInputD5P = 0UL;
bool _bounseInputD2S = 0;
bool _bounseInputD2O = 0;
unsigned long _bounseInputD2P = 0UL;
bool _gen5I = 0;
bool _gen5O = 0;
unsigned long _gen5P = 0UL;
bool _gen2I = 0;
bool _gen2O = 0;
unsigned long _gen2P = 0UL;
bool _bounseInputD4S = 0;
bool _bounseInputD4O = 0;
unsigned long _bounseInputD4P = 0UL;
int _disp6oldLength = 0;
bool _trgr1 = 0;
bool _bounseInputD3S = 0;
bool _bounseInputD3O = 0;
unsigned long _bounseInputD3P = 0UL;
bool _trgt2 = 0;
bool _trgt2I = 0;
int _disp1oldLength = 0;
bool _gen3I = 0;
bool _gen3O = 0;
unsigned long _gen3P = 0UL;
bool _bounseInputD6S = 0;
bool _bounseInputD6O = 0;
unsigned long _bounseInputD6P = 0UL;
bool _count4I = 0;
bool _count4_SCST = 0;
int _count4_Value = 0;
bool _gen1I = 0;
bool _gen1O = 0;
unsigned long _gen1P = 0UL;
void setup()
{
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(13, OUTPUT);
    digitalWrite(13, 0);
    pinMode(9, OUTPUT);
    digitalWrite(9, 0);
    Wire.begin();
    delay(10);
    _lcd1.init();
    _lcd1.backlight();
    _bounseInputD6O =  digitalRead(6);
    _bounseInputD4O =  digitalRead(4);
    _bounseInputD3O =  digitalRead(3);
    _bounseInputD2O =  digitalRead(2);
    _bounseInputD5O =  digitalRead(5);
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
    bool  _bounceInputTmpD6 =  (digitalRead (6));
    if (_bounseInputD6S)
    {
        if (millis() >= (_bounseInputD6P + 40))
        {
            _bounseInputD6O= _bounceInputTmpD6;
            _bounseInputD6S=0;
        }
    }
    else
    {
        if (_bounceInputTmpD6 != _bounseInputD6O)
        {
            _bounseInputD6S=1;
            _bounseInputD6P = millis();
        }
    }
    bool  _bounceInputTmpD3 =  (digitalRead (3));
    if (_bounseInputD3S)
    {
        if (millis() >= (_bounseInputD3P + 40))
        {
            _bounseInputD3O= _bounceInputTmpD3;
            _bounseInputD3S=0;
        }
    }
    else
    {
        if (_bounceInputTmpD3 != _bounseInputD3O)
        {
            _bounseInputD3S=1;
            _bounseInputD3P = millis();
        }
    }
    bool  _bounceInputTmpD4 =  (digitalRead (4));
    if (_bounseInputD4S)
    {
        if (millis() >= (_bounseInputD4P + 40))
        {
            _bounseInputD4O= _bounceInputTmpD4;
            _bounseInputD4S=0;
        }
    }
    else
    {
        if (_bounceInputTmpD4 != _bounseInputD4O)
        {
            _bounseInputD4S=1;
            _bounseInputD4P = millis();
        }
    }
    bool  _bounceInputTmpD5 =  (digitalRead (5));
    if (_bounseInputD5S)
    {
        if (millis() >= (_bounseInputD5P + 40))
        {
            _bounseInputD5O= _bounceInputTmpD5;
            _bounseInputD5S=0;
        }
    }
    else
    {
        if (_bounceInputTmpD5 != _bounseInputD5O)
        {
            _bounseInputD5S=1;
            _bounseInputD5P = millis();
        }
    }
    //Плата:1
    if(!(_bounseInputD2O)) _trgr1 = 0;
    if(!(_bounseInputD6O)) _trgr1 = 1;
    if (_trgr1) 
    {
         if (! _gen3I) 
        {
            _gen3I = 1;
            _gen3O = 1;
            _gen3P = millis();
        }
    }
     else 
    {
        _gen3I = 0 ;
        _gen3O= 0;
    }
    if (_gen3I) 
    {
          if (_isTimer (_gen3P , 500)) 
        {
             _gen3P = millis();
            _gen3O = ! _gen3O;
        }
    }
    bool  _tmp2 = !(_bounseInputD2O);
    if (_tmp2)  
    {
         if (! _trgt2I) _trgt2 = ! _trgt2;
    }
    _trgt2I = _tmp2;
    if (((_gtv1) || (_trgt2)))
    {
        _count2_Value = 0;
    }
     else 
    {
        if (((!(_bounseInputD3O)) && (!(_trgt2))))
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
        _mux2 = 0;
    }
    if((_count2_Value) == 1) 
    {
        _mux2 = 15;
    }
    if((_count2_Value) == 2) 
    {
        _mux2 = 30;
    }
    if((_count2_Value) == 3) 
    {
        _mux2 = 45;
    }
    if((_count2_Value) == 4) 
    {
        _mux2 = 59;
    }
    if (((!(_bounseInputD4O)) || (!(_bounseInputD5O)))) 
    {
        if (! _gen5I) 
        {
            _gen5I = 1;
            _gen5O = 1;
            _gen5P =  millis();
        }
    }
     else 
    {
        _gen5I = 0 ;
        _gen5O= 0;
    }
     if (_gen5I) 
    {
         if (_gen5O) 
        {
             if (_isTimer(_gen5P , 20)) 
            {
                 _gen5P = millis();
                _gen5O = 0;
            }
        }
         else  
        {
             if (_isTimer(_gen5P , 480)) 
            {
                  _gen5P = millis();
                _gen5O = 1;
            }
        }
    }
    if (_trgt2)
    {
        _count4_Value = 0;
    }
     else 
    {
        if (((!(_bounseInputD4O)) && (_gen5O) && (!(_trgt2))))
        {
            if (! _count4I) 
            {
                _count4I = 1;
                if(_count4_Value < 29) 
                {
                    _count4_Value = _count4_Value + 1;
                }
            }
        }
         else 
        {
            _count4I = 0;
        }
        if (((_gen5O) && (!(_bounseInputD5O)) && (!(_trgt2))))
        {
            if (! _count4_SCST) 
            {
                _count4_SCST = 1;
                if(_count4_Value > 0) 
                {
                    _count4_Value = _count4_Value - 1;
                }
            }
        }
         else 
        {
            _count4_SCST = 0;
        }
    }
    if (((!(_trgt2)) && (!(_trgr1)))) 
    {
        _dispTempLength1 = (((((_convertNumbeToTime((((_mux2)+((60)*(_count4_Value)))-((((_mux2)+((60)*(_count4_Value))) % (60))))/(60)))) + (String(":")) + ((_convertNumbeToTime((((_mux2)+((60)*(_count4_Value))) % (60)))))))).length();
        if (_disp2oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp2oldLength = _dispTempLength1;
        _lcd1.setCursor(int((16 - _dispTempLength1)/2), 1);
        _lcd1.print(((((_convertNumbeToTime((((_mux2)+((60)*(_count4_Value)))-((((_mux2)+((60)*(_count4_Value))) % (60))))/(60)))) + (String(":")) + ((_convertNumbeToTime((((_mux2)+((60)*(_count4_Value))) % (60))))))));
    }
     else 
    {
        if (_disp2oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp2oldLength = 0;
        }
    }
    if (!(_bounseInputD6O))
    {
        _count1_Value = (_mux2)+((60)*(_count4_Value));
    }
     else 
    {
        if (_gen3O)
        {
            if (! _count1I) 
            {
                _count1I = 1;
                if(_count1_Value > 0) 
                {
                    _count1_Value = _count1_Value - 1;
                }
            }
        }
         else 
        {
            _count1I = 0;
        }
    }
    _count1MinLO = _count1_Value <= 0;
    if (((_count1MinLO) && (_trgr1) && (!(_trgt2)))) 
    {
         if (! _gen1I) 
        {
            _gen1I = 1;
            _gen1O = 1;
            _gen1P = millis();
        }
    }
     else 
    {
        _gen1I = 0 ;
        _gen1O= 0;
    }
    if (_gen1I) 
    {
          if (_isTimer (_gen1P , 1000)) 
        {
             _gen1P = millis();
            _gen1O = ! _gen1O;
        }
    }
    digitalWrite(13, _gen1O);
    if (_gen1O) 
    {
        if (! _gen2I) 
        {
            _gen2I = 1;
            _gen2O = 1;
            _gen2P =  millis();
        }
    }
     else 
    {
        _gen2I = 0 ;
        _gen2O= 0;
    }
     if (_gen2I) 
    {
         if (_gen2O) 
        {
             if (_isTimer(_gen2P , 50)) 
            {
                 _gen2P = millis();
                _gen2O = 0;
            }
        }
         else  
        {
             if (_isTimer(_gen2P , 150)) 
            {
                  _gen2P = millis();
                _gen2O = 1;
            }
        }
    }
    digitalWrite(9, _gen2O);
    if (((!(_trgt2)) && (_trgr1))) 
    {
        _dispTempLength1 = (((((_convertNumbeToTime(((_count1_Value)-(((_count1_Value) % (60))))/(60)))) + (String(":")) + ((_convertNumbeToTime(((_count1_Value) % (60)))))))).length();
        if (_disp4oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp4oldLength = _dispTempLength1;
        _lcd1.setCursor(int((16 - _dispTempLength1)/2), 1);
        _lcd1.print(((((_convertNumbeToTime(((_count1_Value)-(((_count1_Value) % (60))))/(60)))) + (String(":")) + ((_convertNumbeToTime(((_count1_Value) % (60))))))));
    }
     else 
    {
        if (_disp4oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp4oldLength = 0;
        }
    }
    if (_trgt2) 
    {
        _dispTempLength1 = (((((_floatToStringWitRaz(((((analogRead (0)))-(20.00))*(0.48944))-(40.00),2))) + (String(" ^C"))))).length();
        if (_disp3oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp3oldLength = _dispTempLength1;
        _lcd1.setCursor(int((16 - _dispTempLength1)/2), 1);
        _lcd1.print(((((_floatToStringWitRaz(((((analogRead (0)))-(20.00))*(0.48944))-(40.00),2))) + (String(" ^C")))));
    }
     else 
    {
        if (_disp3oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp3oldLength = 0;
        }
    }
    if (!(_trgt2)) 
    {
        _dispTempLength1 = (String("Taimer")).length();
        if (_disp6oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp6oldLength = _dispTempLength1;
        _lcd1.setCursor(int((16 - _dispTempLength1)/2), 0);
        _lcd1.print(String("Taimer"));
    }
     else 
    {
        if (_disp6oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp6oldLength = 0;
        }
    }
    if (_trgt2) 
    {
        _dispTempLength1 = (String("Thermometer")).length();
        if (_disp1oldLength > _dispTempLength1) 
        {
            _isNeedClearDisp1 = 1;
        }
        _disp1oldLength = _dispTempLength1;
        _lcd1.setCursor(int((16 - _dispTempLength1)/2), 0);
        _lcd1.print(String("Thermometer"));
    }
     else 
    {
        if (_disp1oldLength > 0) 
        {
            _isNeedClearDisp1 = 1;
            _disp1oldLength = 0;
        }
    }
}
String  _floatToStringWitRaz(float value, int raz)
{
    return String(value,raz);
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
String _convertNumbeToTime(long value)
{
    if (value > 9) 
    {
        return String(value, DEC);
    }
    return (String("0") + String(value, DEC));
}
