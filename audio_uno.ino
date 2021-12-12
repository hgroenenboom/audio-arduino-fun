#if ARDUINO_ARCH_AVR

// Optimal samplerate for single sample processing, with a little headroom
const int sampleRate = 48000;

// Setup the timer by the TimerInterrupt (Generic) library
#define USE_TIMER_2     true
#include <TimerInterrupt.h>

// Configure the correct audio output variables
static const auto audioOutputPin = 15;
#define HG_AUDIO_OUTPUT_PORT PA02
#define HG_AUDIO_OUTPUT_ON 1
#define HG_AUDIO_OUTPUT_OFF 0

/** called by the hardware timer, this is were lowlevel audioprocessing should happen */
void TimerHandler(void)
{
  // Same as this, but using PortManipulation
  //digitalWrite(audioOutputPin, processAudio() ? HIGH : LOW);

  if(processAudio())
  {
    // Directly accesses the digital pins values
    HG_AUDIO_OUTPUT_PORT |= HG_AUDIO_OUTPUT_ON;
  }
  else
  {
    HG_AUDIO_OUTPUT_PORT &= HG_AUDIO_OUTPUT_OFF;
  }
}

void setupAudio()
{
  // Correctly set up the audio pin
  pinMode(audioOutputPin, OUTPUT);
  
  // Start the hardware timer
  ITimer2.init();
  if (ITimer2.attachInterrupt(static_cast<float>(sampleRate), TimerHandler))
  {
    Serial.print(F("Starting  ITimer2 OK, millis() = ")); Serial.println(millis());
  }
}

#endif //ARDUINO_ARCH_AVR

