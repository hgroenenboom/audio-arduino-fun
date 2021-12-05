#include "include/conversion.h"
#include "include/midinote.h"

#include <arduino-timer.h>

const MidiNote notes[]
{
  { 24, 0.0625f, false },
  { 0, 0.0625f, true },
  { 36, 0.125f, false },
  { 0, 0.25f, true },
  { 24, 0.0625f, false },
  { 0, 0.0625f, true },
  { 39, 0.125f, false },
  { 0, 1.125f, true }
};
const auto notesSize = sizeof(notes) / sizeof(MidiNote);

void loopNotes(int numTimes, float speedMultiplier)
{
  static const auto pin = 8;
  
  for(auto j = 0; j < numTimes; j++)
  {
    for (auto i = 0; i < notesSize; i++) 
    {
      const auto& note = notes[i];
      const auto noteDuration = speedMultiplier * note.duration;
        
      if(note.rest)
      {
        noTone(pin);  
      }
      else
      {    
        tone(pin, note.frequency, noteDuration);
      }

      delay(noteDuration);  
    }
  }
}

static const int sampleRate = 1000;
Timer<50, micros> audioTimer;

float phaseIncrement(float frequency)
{
  return static_cast<float>(sampleRate) / frequency;
}

float phase = 0.0f;
inline float processAudio(float dither)
{
  static const auto ditherAmount = 0.05f;

  phase += phaseIncrement(100.0f);
  
  return sin(phase) + ditherAmount * dither;
}

bool processTimer(void*)
{
  const float dither = -0.5f + 0.001f * static_cast<float>(random(1000));
  
  const float output = processAudio(dither);
  
  digitalWrite(8, (output > 0.0) ? HIGH : LOW);
    
  return true;
}

void setup() 
{
  Serial.begin(9600);
  Serial.println("start");

  constexpr float speedMultiplier =  multiplierFromBpm(120.0f);

  pinMode(8, OUTPUT);

  audioTimer.every(1000000 / sampleRate, processTimer);
}

void loop() 
{
  audioTimer.tick();
}
