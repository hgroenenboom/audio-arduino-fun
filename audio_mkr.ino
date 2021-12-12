#if ARDUINO_ARCH_SAMD

// Expected samplerate that the processor will execute the loop with 
// TODO: more accurate would be using timers
const int sampleRate = 32000;

extern inline void processNotes();
extern inline float processFloat();

constexpr auto range = 1 << 9;

constexpr auto targetPort = PORT_PA02;

void callInSetup()
{
  pinMode(A0, OUTPUT);
  analogWriteResolution(10);
  analogWrite(A0, range);
}

inline void callInLoop()
{
  processNotes();

  const auto value = range + int(static_cast<float>(range) * processFloat());
  
  // SAMD21 - DAC write register - obtained from
  // AppData\Local\Arduino15\packages\arduino\tools\CMSIS-Atmel\1.2.0\CMSIS\Device\ATMEL\samd21\include\instance\dac.h
  REG_DAC_DATABUF = value;
}

#endif //ARDUINO_ARCH_SAMD

