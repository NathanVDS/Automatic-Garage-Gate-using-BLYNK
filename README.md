# Automatic-Garage-Gate-using-BLYNK-
Gate Opener IoT Project: A self-built application for opening and monitoring gates, utilizing ESP32, sensors, and Blynk app | Poortopener IoT Project: Een zelfgebouwde applicatie voor het openen en monitoren van poorten, met gebruik van ESP32, sensoren en Blynk app
Project Description
In the scope of this project, I have chosen to develop an application that acts as a gate opener, with the additional functionality of monitoring and reporting the status of the gates. This was achieved by utilizing field-effect transistors (FETs) and bipolar transistors readily available. The concept involves providing three gates, each equipped with two physical buttons and a virtual button. Additionally, the closed status of the gates is detected using contact sensors. This functionality is executed through an ESP32 development module. Furthermore, the ESP is also utilized for measuring temperature and humidity using a DHT11 sensor.

1. Description of Used Hardware
   
ESP32: A programmable microcontroller with built-in Wi-Fi and Bluetooth functionality, chosen for its versatility and connectivity options.
IRL530: An N-channel MOSFET transistor used for driving external loads such as motors or lamps. The IRL530 is chosen for its high power capacity and efficient switching.
BC547: An NPN bipolar transistor acting as a signal amplifier or switch. The BC547 is used for signal amplification in the gate switching circuit.
MC-38 Magnetic Contact Switch Sensor: A magnetic contact sensor used for detecting the open or closed status of the gates. The sensor consists of a magnetic reed contact activated by the proximity of a magnet.
DHT11: A digital temperature and humidity sensor used for measuring environmental conditions. The DHT11 communicates via a single data line and is easy to integrate into the ESP32 platform.
Jumperwires: Flexible electrical wires with connectors at both ends, used for establishing electrical connections between components.
Terminal Blocks: Electrical connectors used to securely and firmly connect wires. Terminal blocks are used for connecting wires to the ESP32 and other components, providing a reliable connection.
3. Methodology and Process Description

2 Hardware Configuration
The initial phase of the hardware assembly process involved hanging all wires and sensors. The existing physical switches were equipped with jumper wires directly connected to the gate opener. Additionally, two extra jumper wires were connected in parallel to these wires to provide additional functionality (see attachment 1).

The placement of the contact sensors was strategically determined to activate a signal when the gate is closed. The importance of this position was that it should not hinder the functionality of the gate. A unique position was determined for each gate (see attachments 2.1 | 2.2 | 2.3). To achieve the correct positioning, the contact sensors were extended using jumper wires.

All wiring was directed to a breadboard on which the ESP32 microcontroller was mounted. This centralization point facilitated the management and connection of all components (see attachment 3).


2.1 Calculation of the Resistance Value for the BC547 Transistor

For the resistance value between the ESP32 and the base of the BC547 transistor, you can calculate it using the following formula:
•	R=(VGPIO−VBE)/IB
Where:
o VGPIO is the output voltage from the ESP32 GPIO pin (in this case, 3.3V).
o VBE is the base-emitter voltage of the transistor (approximately 0.7V for a silicon transistor like the BC547).
o IB is the desired base current (0.30mA in this case).
Assuming VGPIO=3.3V, VBE=0.7V, and IB=0.30mA, we have:
• R=(3.3V−0.7V)/0.30mA
• R≈0.30mA/2.6V
• ≈8666.67Ω
You can use a standard resistance value close to this calculated value, such as 8.2kΩ or 10kΩ.

2.2 Calculation of the Resistance Value for the IRL530 MOSFET
To determine the correct resistance value for the IRL530 MOSFET, we utilize the following formula:
•	R= VGPIO/ IGATE
Where:
o VGPIO is the output voltage from the ESP32 GPIO pin (3.3V).
o IGATE is the current required to activate the MOSFET gate (a small value typically in the range of microamperes to milliamperes).
The gate current (IGATE) for MOSFETs like the IRL530 is usually very small and can often be neglected for digital switching applications. However, for a safe margin, let's set IGATE to approximately 10 times the leakage current, which typically falls in the nanampere range.
Let's assume IGATE = 10 × 100nA = 1μA = 0.000001A.
By substituting the values, we get:
• R = 3.3V / 0.000001A
•	R=3,3V/0,000001A
•	R=3,3×10^6Ω
•	R=3,3MΩ
However, such a high resistance value can slow down the switching process. It is more practical to use a resistor with a lower value, typically in the kilo-ohm range.
For example, a 10kΩ resistor would work well:
• R = 10kΩ
This will provide sufficient current limiting while ensuring fast switching times.


4. Electrical Schema: Design and Explanation
(see attachment 4)

Here is a description of the electrical schema for the system:
Three transistors, namely Transistor1, Transistor2, and Transistor3, are configured as switches to control the operation of different gates, named Gate1, Gate2, and Gate3. Transistor1 is connected to GPIO pin 2 of the microcontroller, along with the ground and Gate1 connections. Transistor2 is connected to GPIO pin 4, along with the ground and Gate2 connections. Transistor3 is connected to GPIO pin 5, along with the ground and Gate3 connections.

Additionally, there are three contact sensors, namely Switch1, Switch2, and Switch3, serving as external controls for the system. Switch1 is connected to GPIO pin 18 and ground, Switch2 to GPIO pin 19 and ground, and Switch3 to GPIO pin 21 and ground.

Finally, a DHT sensor is integrated into the system to measure environmental data. The sensor is connected to the 3.3V power source of the microcontroller, GPIO pin 22 for data exchange, and ground for reference grounding.

4. Description and Usage of the Blynk Application
To control the gate, the BLYNK app is used. This app utilizes a legacy version hosted on a self-managed server. However, this option may be limited for some users. Therefore, I recommend checking out my home-assistant repository (currently in development) for a self-hosted alternative.

A screenshot of the app layout can be found in attachment 5. A LED in the app lights up when the gate is open, allowing remote verification of the gate status. Two meters are used to visually display temperature and humidity. Additionally, three buttons are available as gate switches. It is important to note that these buttons must be pressed for at least 500 milliseconds to ensure a complete contact.

5. Troubleshooting, Lessons Learned, and Future Improvements
One of the main challenges encountered was extending the wires. Ultimately, terminal blocks were chosen for use. However, this solution proved suboptimal due to the thinness of the jumper wire. Especially in environments where water or wind is present, this option may be problematic.

The use of a breadboard was found to be cluttered. For future projects, transitioning to a printed circuit board (PCB) would be considered. However, the downside of a PCB is that it may offer less flexibility for expansion. Moreover, replacing gates may disrupt the functionality of the transistors.

When placing the contact sensors, it is important to ensure that they do not hinder the operation of the gate. If the gate does not fully close, the sensor position needs to be adjusted. Additionally, maintaining a suitable distance between the sensors is essential to prevent false negative values.

Furthermore, the reliance on the Blynk app from a third party posed a limitation. Therefore, a transition was made to a home-assistant application, utilizing YAML configuration files. This alternative approach enables self-hosting of the project, thereby increasing autonomy and reducing dependency on external platforms. Details of this project adjustment are described in a separate GitHub repository.
