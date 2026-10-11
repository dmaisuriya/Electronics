# MILESTONE 02: The Voltmeter & Graph

<body>
<img width="300" height="400" alt="fa940a7d-130d-4460-8bff-65e1278100a3" src="https://github.com/user-attachments/assets/d9ac244a-5e9e-4da2-a5c8-5bdf4326fffe" /> <br> Voltage reading when LED is ON <br><br>
<img width="300" height="400" alt="922f6138-f543-4481-8ea7-bda50bbad565" src="https://github.com/user-attachments/assets/2ded113d-9ed6-40da-a179-657b27232933" /> <br> Voltage reading when LED is OFF <br><br>

**Part List:**
- 1x ESP32 WROOM-32 DevKit-C
- 1x TLC555 Timer
- 1x MCP3201 ADC
- 1x SPI 128x64 OLED display
- 1x LED
- 3x Resistors
- 2x Capacitors <br>

**Summary:** <br>
Improving on my last milestone, as shown in the photo, the hardware functions the same, but this time I plotted the voltage on a graph on the OLED display.
After a lot of trialling and debugging, I was finally able to get the graph to display the voltage properly, and I even increased the maximum voltage it can
read from 3.3V to 5V. Most of this milestone involved firmware and I managed to learn a few things along the way like arduino's built-in map() function which 
made my life easier when I had to accurately map my voltage readings to be proportional to the graph. Structs were also another very useful thing I got to learn 
as it proved useful to keep many of my variables in one section so I can always access values inside of the struct and alter them inside of any function, which
proved to be useful.

**Challenges:** <br>
The biggest challenge here would have been trying to figure out how to create a scrolling graph so that the graph could constantly update within the x and y axis 
boundaries. Once I had an idea it took several iterations of debugging until I got it to work.

**Future Improvements And/Or Implementations:** <br>  

</body>
