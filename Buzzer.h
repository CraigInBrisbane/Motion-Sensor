class Buzzer {
    private:
    int             _pin = 0;
    unsigned long   _startTime = 0;
    unsigned long   _toneTime = 0;
    int             _pitch = 2000;
    bool            _isBuzzing = false;
  
  public:

    void Init(int Pin) {
        _pin = Pin;
        pinMode(_pin, OUTPUT);
    }

    void Beep(int ToneTime, int Pitch) {
        _toneTime = ToneTime;
        _pitch = Pitch;

        _startTime = millis();
        _isBuzzing = true;
        tone(_pin, _pitch);
    }

    void Update() {
        unsigned long currentMillis = millis();
    
        if(_isBuzzing && currentMillis - _startTime > _toneTime) {
            noTone(_pin);
            _isBuzzing = false;
        }
    }
};