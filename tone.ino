struct Note
{
  float midi;
  float duration;
  bool rest;
};

const Note notes[]
{
  { 50, 0.125f, false },
  { 0, 0.125f, true },
  { 200, 0.125f, false },
  { 0, 0.125f, true }
};
const auto numNotes = sizeof(notes) / sizeof(Note);

constexpr float multiplierFromBpm(float bpm)
{
  return 1000.0f * (60.0f / bpm);
};

void loopNotes(int numTimes, float speedMultiplier)
{
  constexpr auto pin = 8;
  
  for(auto j = 0; j < numTimes; j++)
  {
    for (auto i = 0; i < numNotes; i++) 
    {
      const auto& note = notes[i];
      const auto noteDuration = speedMultiplier * note.duration;
        
      if(note.rest)
      {
        noTone(pin);  
      }
      else
      {    
        tone(pin, note.midi, noteDuration);
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
