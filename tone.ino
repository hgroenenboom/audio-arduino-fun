#include "include/conversion.h"
#include "include/midinote.h"

#define USE_TIMER_2     true
#include <TimerInterrupt.h>

// Optimal samplerate for single sample processing, with a little headroom
static const long sampleRate = 5000;

const MidiNote notes[]
{
  { 24, 0.0625f, false },
  { 0, 0.0625f, true },
  { 36, 0.125f, false },
  { 0, 0.25f, true },
  { 24, 0.0625f, false },
  { 0, 0.0625f, true },
  { 39, 0.125f, false },
  { 0, 1.125f, true },
  { 60, 0.0625f, false },
  { 0, 0.0625f, true },
  { 36, 0.125f, false },
  { 0, 0.25f, true },
  { 24, 0.0625f, false },
  { 0, 0.0625f, true },
  { 36, 0.0625f, false },
  { 35, 0.0625f, false },
  { 0, 1, true }
};
const auto notesSize = sizeof(notes) / sizeof(MidiNote);

constexpr float incrementFromFrequency(float frequency)
{
  return 1.0f / (static_cast<float>(sampleRate) / frequency);
}

bool noteOff;
float phaseIncrement = incrementFromFrequency(200.0f);
float phase = 0.0f;
inline bool processAudio()
{
  if(noteOff)
  {
    return false;
  }
    
  phase += phaseIncrement;
  phase -= floor(phase);
  
  return phase > 0.5f;
}

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
        noteOff = true;
      }
      else
      {    
        phaseIncrement = incrementFromFrequency(note.frequency);
        noteOff = false;
      }

      delay(noteDuration);  
    }
  }
}

void TimerHandler(void)
{
  // Same as this, but using PortManipulation
  //digitalWrite(8, processAudio() ? HIGH : LOW);

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
  Serial.begin(9600);
  Serial.println("start");

  pinMode(8, OUTPUT);

  ITimer2.init();
  if (ITimer2.attachInterrupt(static_cast<float>(sampleRate), TimerHandler))
  {
    Serial.print(F("Starting  ITimer2 OK, millis() = ")); Serial.println(millis());
  }

  constexpr float speedMultiplier =  multiplierFromBpm(60.0f);
  loopNotes(100, speedMultiplier);
}

void loop() 
{
}
