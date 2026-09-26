# 🚗 Smart Car Parking System

An Arduino-based Smart Car Parking System that monitors parking slot availability in real time and automates vehicle entry using sensor-based control logic.

Built using **Arduino Uno, IR sensors, an LCD display, and a servo motor**, this project demonstrates the integration of hardware and software to solve a real-world parking management problem.

<p align="center">
  <img src="Project%20Model/Project%20Model%20pic.png" alt="Smart Car Parking System Prototype" width="650">
</p>

<p align="center">
  <b>Real-Time Parking Monitoring | Automated Entry Control | Embedded Systems</b>
</p>

---

## 📌 Table of Contents

- [Project Overview](#-project-overview)
- [Features](#-features)
- [Hardware and Technologies](#-hardware-and-technologies)
- [How It Works](#-how-it-works)
- [System Architecture](#-system-architecture)
- [Project Demonstration](#-project-demonstration)
- [Project Files](#-project-files)
- [Getting Started](#-getting-started)
- [Learning Outcomes](#-learning-outcomes)
- [Future Enhancements](#-future-enhancements)
- [Author](#-author)

---

## 📖 Project Overview

The **Smart Car Parking System** is an automated parking management prototype designed to detect vehicles, monitor parking slot availability, and control vehicle entry based on available spaces.

The system uses IR sensors to detect vehicle presence and an Arduino Uno to process sensor inputs and manage parking logic. An LCD displays the parking status, while a servo motor controls the entry gate.

The project aims to reduce manual intervention in parking management and demonstrate how embedded systems can be used to develop practical automation solutions.

---

## ✨ Features

- 🚘 **Vehicle Detection:** Detects vehicle presence using IR sensors.
- 🅿️ **Real-Time Slot Monitoring:** Tracks parking slot availability.
- 🚦 **Automated Entry Control:** Controls the entry gate using a servo motor.
- 📟 **LCD Status Display:** Displays parking availability and system status.
- ⚙️ **Arduino-Based Control Logic:** Processes sensor inputs and manages system operations.
- 🔌 **Hardware-Software Integration:** Combines sensors, control logic, and output devices in a working prototype.

---

## 🛠️ Hardware and Technologies

### Hardware Components

| Component | Purpose |
|---|---|
| Arduino Uno | Main controller |
| IR Sensors | Vehicle detection |
| Servo Motor | Automated entry gate control |
| LCD Display | Parking status display |
| Jumper Wires | Electrical connections |
| Breadboard and Circuit Components | Circuit assembly |

### Software and Technologies

- Arduino IDE
- Arduino programming (C/C++)
- Embedded Systems
- Sensor-Based Control Logic
- Hardware-Software Integration

---

## ⚙️ How It Works

1. **Vehicle Detection:** IR sensors detect vehicles at the entrance and parking slots.
2. **Sensor Processing:** The Arduino Uno reads the sensor signals and processes the input.
3. **Parking Availability:** The system determines whether parking spaces are available.
4. **Status Display:** The LCD displays the current parking status.
5. **Entry Gate Control:** The servo motor controls the gate based on parking availability.

---

## 🏗️ System Architecture

The system follows an input-processing-output approach:

```text
      IR Sensors
           |
           v
      Arduino Uno
           |
           v
  Parking Availability
         Logic
       /       \
      v         v
 LCD Display  Servo Motor
              (Entry Gate)
```

**Input:** IR sensor signals

**Processing:** Arduino Uno and parking availability logic

**Output:** LCD status display and servo-controlled entry gate

---

## 🎥 Project Demonstration

Watch the working demonstration of the Smart Car Parking System.

<p align="center">
  <video src="Project%20Model/VID-20260511-WA0011.mp4" controls width="700">
    Your browser does not support embedded video.
    <a href="Project%20Model/VID-20260511-WA0011.mp4">Watch the project video</a>
  </video>
</p>

🔗 **[View or download the project demonstration video](Project%20Model/VID-20260511-WA0011.mp4)**

---

## 📂 Project Files

Explore the complete project resources below.

| Resource | Description |
|---|---|
| 💻 [Arduino Source Code](SmartCar_Code/SmartCar_Code.ino) | Main program for sensor processing, parking logic, and gate control |
| 🖼️ [Project Model Image](Project%20Model/Project%20Model%20pic.png) | Image of the working project prototype |
| 🎥 [Project Demonstration Video](Project%20Model/VID-20260511-WA0011.mp4) | Video demonstrating the project |
| 📄 [Project Report](Project%20Report/SMART%20CAR%20FINAL.1-1.docx) | Detailed project documentation |

---

## 🚀 Getting Started

Follow these steps to set up and run the project.

### Prerequisites

- Arduino IDE installed on your computer.
- Arduino Uno board.
- Required sensors and hardware components.
- USB cable for programming the Arduino.

### Installation and Setup

1. Clone the repository:

   ```bash
   git clone https://github.com/AkashGowda-R/Project-SmartCar.git
   ```

2. Navigate to the project directory:

   ```bash
   cd Project-SmartCar
   ```

3. Open the Arduino source file:

   `SmartCar_Code/SmartCar_Code.ino`

4. Connect the Arduino Uno and other hardware components according to the circuit connections.

5. Open the code in Arduino IDE and select the appropriate board and port.

6. Upload the code to the Arduino Uno.

7. Power the system and test vehicle detection, parking status, and entry gate operation.

---

## 📚 Learning Outcomes

Through this project, I gained practical experience in:

- Arduino programming and embedded systems.
- Working with IR sensors and servo motors.
- Implementing sensor-based control logic.
- Integrating hardware and software components.
- Testing and debugging a physical prototype.
- Applying programming concepts to a real-world automation problem.

---

## 🔮 Future Enhancements

Potential improvements to the system include:

- 📱 Mobile application for parking availability.
- 🌐 IoT-based remote monitoring.
- ☁️ Cloud-based parking data storage.
- 📊 Parking usage analytics and reporting.
- 🅿️ Online parking reservation functionality.

---

## 👨‍💻 Author

**Akash Gowda**

B.Sc. Computer Science

- **GitHub:** [AkashGowda-R](https://github.com/AkashGowda-R)
- **Project Repository:** [Smart Car Parking System](https://github.com/AkashGowda-R/Project-SmartCar)
- **LinkedIn:** https://www.linkedin.com/in/akashgowdaa
---

⭐ If you find this project interesting, consider giving the repository a star!
