### Arduino fun

### Initial setup, to get started
Speaker: Adafruit thin plastic speaker 8 ohm (P1891B)

![](./media/schematic.png)

https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody

### Arduino and C++
Sources: 
- https://forum.arduino.cc/t/how-do-i-use-c-to-code-the-arduino-boards/493409/8
- https://andybrown.me.uk/2011/01/15/the-standard-template-library-stl-for-avr-with-c-streams/
- https://github.com/arduino-libraries/Arduino_AVRSTL

Arduino uses its own GCC compiler version called `avr-gcc`. Arduino has very limited RAM, so there is no STD in avr-gcc. There are however libraries which add their own implementation of the STD for `arv-gcc`, but these are not official and provide varying results.

### Essentials
- `Serial.begin(rate)`
    initiating the serial output with a given rate, this rate should match in Arduino IDEs serial monitor
- `Serial.print()` and `Serial.println()`
    printing messages, `Serial.begin()` has to be invoked first
