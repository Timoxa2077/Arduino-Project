class emg_reader 
{
  public:
    byte _ready = 1;
    emg_reader(byte port){_port = port;}
    void step()
    {
      byte a = map(analogRead(_port), 0, 1023, 0, 255);
      max_v = max(a, max_v);
      min_v = min(a, min_v);
      cnt++;
      if(cnt == 30)
        _ready = 1;
    }

    double get_sData()
    {
      sData = sData*0.4 + (max_v - min_v)*0.6;
      cnt = 0;
      min_v = 255;
      max_v = 0;
      _ready = 0;
      return sData;
    }
  protected:
    double sData = 0;
    byte _port = 0;
    byte max_v = 0;
    byte min_v = 255;
    byte cnt = 0;
};
