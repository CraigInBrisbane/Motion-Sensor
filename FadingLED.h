class FadingLED
{
   
    private:
    unsigned long   _delayedStart;                  // Period to wait before starting.
    int             _ledPin;                        // The pin to control - Note, as we're fading, we must use an ANALOG pin.
    unsigned long   _fadePeriod;                    // The time to do a full light and dim cycle.
    unsigned long   _previousMillis;                // The previous millis value.
    float           _fadeChangeGap;                 // Calculated gap between brightness changes.
    unsigned long   _firstMillis;                   // The first time the class was initialised. Might not be 0.
        
    public:

    void Init(int LedPin, unsigned long FadePeriod, unsigned long DelayedStart)
    {
        _previousMillis = 0;
        _fadeChangeGap = 0;
        _firstMillis = -1;
    
        _ledPin = LedPin;
        _fadePeriod = FadePeriod;
        _delayedStart = DelayedStart;
        pinMode( _ledPin, OUTPUT );
    }//Init


    void Update(bool isOn)
    {
        int
            b,
            brightness;
        unsigned long
            diff,
            currentMillis;
    
        // Get the current millis since the board was started.
        currentMillis = millis();
    
        // Is this the first time this code is running?
        if(_firstMillis == -1)
            _firstMillis = currentMillis; // Set the first time this class was run.
    
        // Adjust the current time to be based on the current time since the object was created.
        currentMillis = currentMillis - _firstMillis;
    
        // Calculate the difference bwteen the last update and now.
        diff = currentMillis - _previousMillis;
    
        // Check if we have a delay set. If so, don't light up yet.
        if( _delayedStart > 0 && currentMillis < _delayedStart)
        {
            //Particle.publish("LED", "In Delay Start...", PUBLIC);
            _previousMillis = currentMillis;
            return;
    
        }//if
    
        // Map the difference which is betweem 0 and the cycle time, to a value between 0 and 512.
        // Map the difference, which is between 0 and the fade period, to a value between 0 at 512.
        b = map( diff, 0, _fadePeriod, 0, 512 ); // 512, as we'll brighten to 256, then then fade from 256 to 512.
    
        // Check if we should be bringtning, or fading...
        if( isOn )
        {
            if(b > 255)
                brightness = 255 - (b-255);
            else
                brightness = b;
    
        }
        else
            brightness = 0;
    
        // Set the brightness.
        analogWrite(_ledPin, brightness);
    
        // And then save the timestamp.
        if(currentMillis - _previousMillis >= _fadePeriod)
            _previousMillis = currentMillis;
    
    }
};