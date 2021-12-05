struct Note
{
  float midi;
  float duration;
  bool rest;
};

const Note notes[]
{
  { 24, 0.125f, false },
  { 0, 0.125f, true },
  { 36, 0.125f, false },
  { 0, 0.125f, true }
};
const auto notesSize = sizeof(notes) / sizeof(Note);

constexpr float multiplierFromBpm(float bpm)
{
  return 1000.0f * (60.0f / bpm);
};

constexpr float mtof(float midi)
{
  return 440.0f * pow(2.0f, 0.08333333333f * (midi - 69.0f));
}

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
        tone(pin, mtof(note.midi), noteDuration);
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
