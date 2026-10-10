# MILESTONE 01: PWM Generator

<body>
<img width="300" height="300" alt="on" src="https://github.com/user-attachments/assets/de89c0e2-f65b-4c2d-b9d3-a243afd2a19e" /> <br> Voltage reading when LED is ON <br><br>
<img width="300" height="300" alt="off" src="https://github.com/user-attachments/assets/12028afd-cd9e-4ed0-97ec-951b6c4c6002" /> <br> Voltage reading when LED is OFF <br><br>

**Part List:**
- 1x ESP32 WROOM-32 DevKit-C
- 1x TLC555 Timer
- 1x MCP3201 ADC
- 1x SPI 128x64 OLED display
- 1x LED
- 3x Resistors
- 2x Capacitors <br>

**Summary:** <br>
I made a PWM square waveform using the 555 timer and displayed the real-time voltage across the blinking LED on the OLED display. 

The 555 timer is in astable form, and produces a square waveform, and by carefully choosing resistor and capacitor values, I am able to tweak the frequency at which this wave oscillates. In my case, I wanted my LED to blink approximately every second, so I chose resistor and capacitor values that set the frequency to 1Hz. Now that the LED was blinking, I wanted to measure the voltage across this LED, and then display this value on the OLED display. I fed the voltage on both sides of the LED into the IN+ and IN- pins of the ADC so it gets the potential difference across the LED (when LED was on it was ~1.77V), which then outputted a number between 0 and 4095 and sent this to the ESP32, which then was directly fed into the OLED display with a simple mathematical operation done in the code to finally display the live voltage across the LED. <br>

**Motivation Behind Component Selection:** <br>
- I had an arduino nano and an esp32 devkit-c to choose from, but I chose the latter as it will be more useful as the projects get more an more complex. My esp32 also had 30 pinouts, and more capability overall than the arduino nano, as it has a much higher processing speed.<br>

- The standard 555 timer many people use is the NE555 timer, but I wanted to keep everything powered by the esp32's logic level voltage which was 3.3V, and the NE555 was rated for more than that to be powered. So instead a used a TLC555 timer which had a lower voltage rating, so 3.3V could easily supply this. This also has many more advantages over the classic NE555 such as lower power consumption and reduced electrical noise. <br>

- I used the MCP3201 ADC due to its high sampling rate (50-100 kilo samples per second) and 12-bit resolution. I chose the 12-bit resolution especially because the esp32's built in ADC is also 12-bit, so I wanted to keep that level of resolution while using the ADC chip separately. This ADC also had SPI communication so it was very compatible with my esp32 to transfer the bit data effectively to the OLED display peripheral. 

**Challenges:** <br>
While I found wiring the components quite easy, the hardest part would have been to learn and implement the SPI communication from the ADC to the esp32. For learning purposes, I decided that I wanted to implement the SPI manually by referring to the data sheet to see each state of the SPI pins. To be specific, I had to generate a clock manually and shift the RELEVANT bits only, which took a very long time to wrap my head around. <br><br>

It involved reading the graphs below from the datasheet: <br>
<img width="600" height="250" alt="SPI" src="https://github.com/user-attachments/assets/2da45f45-e90c-4200-9ae3-3c059204751c" /> <br>

**Future Improvements And/Or Implementations:** <br>
The next step would be to actually display the waveform of the changing voltage across the LED as a function of time on the OLED display, as well as allowing for a variable frequency for the 555 timer to generate different duty cycle PWM.

Once I have finalised a design, I may attempt to make a PCB for this circuit, and would want to keep a permanent micro-controller on the PCB, rather than having to use headers to attach and detach the esp32 devkit-c every time. For this purpose I may instead order an ESP32-C3 Supermini, which has 20 GPIO pins and take up less space on the PCB.  

</body>


