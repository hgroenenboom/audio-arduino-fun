#include "conversion.h"
#include "midinote.h"

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
  constexpr auto pin = 8;
  
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

void setup() 
{
  Serial.begin(9600);
  Serial.println("start");

  constexpr float speedMultiplier =  multiplierFromBpm(120.0f);

  loopNotes(10, speedMultiplier);
}

void loop() 
{
}
