#if ARDUINO_ARCH_AVR && ARDUINO_AVR_UNO

// Optimal samplerate for single sample processing, with a little headroom
const int sampleRate = 5000;

// Setup the timer by the TimerInterrupt (Generic) library
#define USE_TIMER_2     true
#include <TimerInterrupt.h>

// Configure the correct audio output variables
static const auto audioOutputPin = 8;
#define HG_AUDIO_OUTPUT_PORT PORTB
#define HG_AUDIO_OUTPUT_ON B00000001
#define HG_AUDIO_OUTPUT_OFF B11111110

/** called by the hardware timer, this is were lowlevel audioprocessing should happen */
void TimerHandler(void)
{
  // Same as this, but using PortManipulation
  //digitalWrite(audioOutputPin, processAudio() ? HIGH : LOW);

  if(process1bit())
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
  Serial.println("Arduino UNO!");
  
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

