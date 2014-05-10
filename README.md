Final-Project-383
=================

Final project in 383

PURPOSE:  
The purpose of my final project was to interface a GPS chip with a magnetometer. The data from both would then be logged in software 
to provide a map of relative magnetic field strengths that could be used in finding large metal object (in theory). For this the GPS would be a standard sr-92 chip, the magnetometer would be a generic UBlox and they would both ideally be interfaced through a spartan 6 fpga. The only part that I was able to get working however, was the GPS. That process and procedure is outlined below. 

Implementation: 
For the GPS, I first found a GPS unit called the sr-92. After some research online, I was able to download the data sheet online. Using the data, i changed the pins used to read in the switches in Lab 4 to the GPIO pins on the FPGA. I then routed the output from the GPS to one of these pins and read them all into the FPGA as bytes where the GPS was the lsb. I then stored each byte as a char in an array in c (using microblaze) and then wrote taht same byte out to the leds. I was able to use two logic probes, one on the GPS output and one on the LED output to find out the time delay of the FPGA. From that, i created a delay loop in microblaze just after i read each byte into the array in order to synce the input times. Ultimately there was no visible delay after 1000 bits, so the synchronization was close to perfect. It is worth noting that the array and the entire waiting sequence started once every second so that every second the two devices were re-synched. For knowing when to start data aquisition, the first zero recieved was the start bit so that began the process while any sequence of 11 or more zeros stopped the aquisition until the next zero.

Software manipulation: 
After reading all samples into an array, they were processed by disgarding the first bit, or'ing the next 8 together while doing corrosponding shift lefts (first was shifted left 0 times, the second was shifted once, etc). This effectively built a byte of all of all 8 lsb's which was then passed out to a UART port and written to terra term. The process worked fairly well but there was always a bit of giberish included. 

Debugging 
The biggest issue i had was in using the datasheet. It said that the output was 4800 baud, with one start bit and one stop bit. In reality, there was one start bit, two stop bits, a baud of 9600, and all of the bits were backwards from what i was expecting. Figuring this out took me about 6 hours and a lot of help from a teacher (Dr. York). Several times the wires that were soddered onto the gps came off and made me think my software was broken but it became force of habit to visually inspect the wires every time. Overall however, the hardest part was also the simplest. Knowing for sure that the bit i was interested in was the lsb and that or'ing all of the bytes in c with one byte of 0's took some trial and error to figure out. In hindsite, I should have written entire bytes out to the LEDs for this analysis. I could have then used 8 logic probes to assess each byte.

Conclusion:
I am a lot more comfortable with logic probes and thye helped a significant amount for this project. The datasheets, even when from the manufacturer, are not always right. This one had some serious issues that cost me a lot of time because i thought it was right. With more time, I am confident that completing the entire project would not be an issue, especially after the lessons i learned from the GPS module. 

Documenation: I worked closely with Ryan Good on most of this project to include coding. Please let me know if there are any more unanswered questions. 
