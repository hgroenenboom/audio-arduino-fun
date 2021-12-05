#include "include/conversion.h"
#include "include/midinote.h"

#define USE_TIMER_2     true
#include <TimerInterrupt.h>

// Optimal samplerate for single sample processing, with a little headroom
static const long sampleRate = 5000;

constexpr float incrementFromFrequency(float frequency)
{
  return 1.0f / (static_cast<float>(sampleRate) / frequency);
}

float phaseIncrement = incrementFromFrequency(200.0f);
float phase = 0.0f;
inline bool processAudio()
{
  phase += phaseIncrement;
  phase -= floor(phase);
  
  return phase > 0.5f;
}

void TimerHandler(void)
{
  digitalWrite(8, processAudio() ? HIGH : LOW);
}

void setup() 
{
  Serial.begin(9600);
  Serial.println("start");

  constexpr float speedMultiplier =  multiplierFromBpm(120.0f);

  pinMode(8, OUTPUT);

  ITimer2.init();
  if (ITimer2.attachInterrupt(static_cast<float>(sampleRate), TimerHandler))
  {
    Serial.print(F("Starting  ITimer2 OK, millis() = ")); Serial.println(millis());
  }
}

void loop() 
{
}
