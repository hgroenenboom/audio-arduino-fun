#include "include/conversion.h"
#include "include/midinote.h"

// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------

// SHARED STATE
extern const int sampleRate;

// LOCAL STATE
static float phase = 0.0f;
static bool noteOff = true;
static float phaseIncrement;

// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------

static float incrementFromFrequency(float frequency)
{
  return 1.0f / (static_cast<float>(sampleRate) / frequency);
}

static const MidiNote notes[]
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
static const auto notesSize = sizeof(notes) / sizeof(MidiNote);


// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------

constexpr 
float speedMultiplier = multiplierFromBpm(60.0f);

void loopNotes()
{ 
  for (const auto& note : notes)
  {
    if (note.rest)
    {
      noteOff = true;
    }
    else
    {
      phaseIncrement = incrementFromFrequency(note.frequency);
      noteOff = false;
    }

    delay(speedMultiplier * note.duration);
  }
}

void processNotes()
{
  static unsigned int sampleCounter = 0;
  static size_t noteCounter = 0;
  static unsigned int noteDurationInSamples = 0;

  if(sampleCounter++ != noteDurationInSamples)
  {   
    return;
  }
  
  noteCounter = (noteCounter + 1) % notesSize;
  sampleCounter = 0;
  auto& note = notes[noteCounter];

  noteOff = note.rest;
  noteDurationInSamples = speedMultiplier * note.duration * sampleRate;
  
  if(!noteOff)
  {
    phaseIncrement = incrementFromFrequency(note.frequency);
  }
}

// your processing function
inline bool process1bit()
{
  if(noteOff)
  {
    return false;
  }

  phase += phaseIncrement;
  phase -= floor(phase);
  
  return phase > 0.5f;
}

// https://stackoverflow.com/questions/18662261/fastest-implementation-of-sine-cosine-and-square-root-in-c-doesnt-need-to-b
inline float fastCosine(float x) noexcept
{
    x -= 0.25f + floor(x + 0.25f);
    x *= 16.0f * (abs(x) - 0.5f);
    return x;
}

// your processing function
inline float processFloat()
{ 
  if (noteOff)
  {
    return 0.0f;
  }
    
  phase += phaseIncrement;
  if (phase > 1.0f)
  {
    phase -= floor(phase);
  }

  return fastCosine(phase);
}



