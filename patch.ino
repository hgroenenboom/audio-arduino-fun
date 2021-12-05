extern bool noteOff;
extern float phaseIncrement;

extern const int sampleRate;

constexpr float incrementFromFrequency(float frequency)
{
  return 1.0f / (static_cast<float>(sampleRate) / frequency);
}

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

void loopNotes()
{
  for (auto i = 0; i < notesSize; i++) 
  {
    const auto& note = notes[i];
    
    constexpr float speedMultiplier =  multiplierFromBpm(60.0f);
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
