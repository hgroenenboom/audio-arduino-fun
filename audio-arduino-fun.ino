#if ARDUINO_ARCH_SAMD
#define HG_CALL_IN_SETUP callInSetup()
#define HG_CALL_IN_LOOP callInLoop()
#elif ARDUINO_ARCH_AVR
#define HG_CALL_IN_SETUP setupAudio()
#define HG_CALL_IN_LOOP loopNotes()
#endif

// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------

void setup() 
{
  Serial.begin(9600);
  while(!Serial) { delay(100); }
  
  Serial.println("started");

  HG_CALL_IN_SETUP;
}

void loop() 
{
  HG_CALL_IN_LOOP;
}
