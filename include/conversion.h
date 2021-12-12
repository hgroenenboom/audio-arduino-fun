#pragma once

constexpr float multiplierFromBpm(float bpm)
{
  return (60.0f / bpm);
};

constexpr float mtof(float midi)
{
  return 440.0f * pow(2.0f, 0.08333333333f * (midi - 69.0f));
}
