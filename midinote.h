#pragma once

#include "conversion.h"

class MidiNote
{
public:
  MidiNote(float pitch, float duration, bool rest)
  : pitch(pitch)
  , duration(duration)
  , rest(rest)
  {
    frequency = mtof(pitch);
  }

  float pitch;
  float frequency;
  
  float duration;
  
  bool rest;
};
