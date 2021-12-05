#include "include/conversion.h"
#include "include/midinote.h"

// Setup the timer by the TimerInterrupt library
#define USE_TIMER_2     true
#include <TimerInterrupt.h>

static const auto audioOutputPin = 8;

// SHARED STATE
bool noteOff = true;
float phaseIncrement;

// Optimal samplerate for single sample processing, with a little headroom
const int sampleRate = 5000;

// your processing function, only 1-bit
inline bool processAudio()
{
  static float phase = 0.0f;

  if(noteOff)
  {
    return false;
  }
    
  phase += phaseIncrement;
  phase -= floor(phase);
  
  return phase > 0.5f;
}

// called by the hardware timer, this is were lowlevel audioprocessing should happen
void TimerHandler(void)
{
  // Same as this, but using PortManipulation
  //digitalWrite(audioOutputPin, processAudio() ? HIGH : LOW);

  if(processAudio())
  {
    // Directly accesses the digital pins values
    PORTB |= B00000001;
  }
  else
  {
    PORTB &= B11111110;
  }
}

void setup() 
{
  // Setup serial stream
  Serial.begin(9600);
  Serial.println("start");

  // Correctly set up the audio pin
  pinMode(audioOutputPin, OUTPUT);

  // Start the hardware timer
  ITimer2.init();
  if (ITimer2.attachInterrupt(static_cast<float>(sampleRate), TimerHandler))
  {
    Serial.print(F("Starting  ITimer2 OK, millis() = ")); Serial.println(millis());
  }
}

void loop() 
{
  loopNotes();
}
