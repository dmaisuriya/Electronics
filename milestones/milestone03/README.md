# MILESTONE 02: The Voltmeter & Graph

<body>
<img width="400" height="600" alt="milestone3pic2" src="https://github.com/user-attachments/assets/66884a5f-2890-43f0-9866-86659f0f76db" /><br>
MENU PAGE <br><br><br>

<img width="400" height="600" alt="milestone3pic1" src="https://github.com/user-attachments/assets/314ab423-9098-4fec-a016-cc81cb0a36e9" /><br>
VOLTAGE GRAPHING MODE <br><br><br>


**Summary:** <br>
I added a preliminary menu system where you can choose between different modes but more modes will be added in the future, and these modes can be selected through 
a potentiometer and button. The voltage real time graph is a mode in this implementation. Adding on to the voltage grapher, I have added grids to the graph, so you can 
clearly see the divisions where I can later move into implementing zooming. On the voltage page, I have also added real-time stats which include: max, min, average,
RMS and instantaneous voltage. The biggest change I added less in hardware and more in my software, where I organised my functions and variables into accessible 
classes. This way the different overarching functions of my program is grouped into different sections, making the code way more organised and easier to read in 
the main.cpp file. Everything is abstracted into function calls, reducing the code in main.cpp from 200+ lines to just about 40.

**Challenges:** <br>
The biggest challenge was during when I was trying to implement time base scaling, where the time axis could be zoomed into, but the problem with that was I didn't 
know how to differentiate between the ADC sampling time rate, and rate of OLED refreshing the data, so I decided to leave it be and not pursue it until I have more 
knowledge or potentially just in another project, and decided to heard towards a different path, which explains the menu system which has different modes.

Another smaller challenge was getting the logic for the button and potentiometer working to change from the menu to the voltage mode as desired, and it was only 
a challenge because of the many test cases and boolean cases I had to consider. <br>

**Further Implementations/Improvements:**<br>
Now that I spent more time on this milestone, I was able to self reflect and have a more clearer next step than at any milestone before this
- Eventually, I would like to upgrade my OLED to a TFT 2.4in screen with higher resolution to fit more of the graph, and have more space to add things
- Look into rotary encoders as they may be a better alternative to potentiometers
- Add voltage scaling where the user can select discrete zooms to see the voltage graph in more detail
- Improve the aesthetics of the menu, and add more select options

</body>
