# VoltVault - Smart EV Charging Station Management System

**Charge up, for a greener future**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) <!-- Placeholder license badge -->
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](.) <!-- Placeholder build status badge -->

VoltVault is a comprehensive desktop application designed to manage and streamline operations for electric vehicle (EV) charging stations. It aims to provide a seamless experience for both customers and station operators, addressing common issues found in traditional fueling and existing EV charging solutions.

---

## Table of Contents

*   [About The Project](#about-the-project)
    *   [Problem Statement](#problem-statement)
    *   [Proposed Solution](#proposed-solution)
    *   [Goals & Impact](#goals--impact)
*   [Key Features](#key-features)
*   [Hardware Integration (Arduino)](#hardware-integration-arduino)
*   [Technology Stack (Inferred)](#technology-stack-inferred)
*   [Design](#design)
*   [Getting Started](#getting-started)
    *   [Prerequisites](#prerequisites)
    *   [Installation](#installation)
    *   [Running the Application](#running-the-application)
*   [Usage](#usage)
*   [Future Perspectives](#future-perspectives)
*   [Team](#team)
*   [Acknowledgments](#acknowledgments)

---

## About The Project

This project involves the creation of a desktop application featuring multiple modules and entities to manage smart EV charging stations efficiently.

### Problem Statement

Traditional gas stations and some current EV charging solutions suffer from several drawbacks:

1.  **Inconvenient User Experience:** Limited or non-user-friendly payment methods.
2.  **Lack of Automation:** Manual data entry leads to errors and inefficiency.
3.  **Pollution:** Gasoline combustion harms the environment.
4.  **Long Waits:** Inefficient processes can lead to customer frustration.
5.  **Security Concerns:** Vulnerability to cyber-attacks without proper security.
6.  **Competitor Limitations:** Existing apps may be pay-only, have clunky UIs, bugs, geographic restrictions, or privacy issues.

### Proposed Solution

VoltVault tackles these issues by offering:

*   **Easy Access:** Users can easily locate the nearest charging station (via Map integration).
*   **Simplified Payment & Billing:** Streamlined payment process and invoice generation.
*   **User-Friendly Interface:** Intuitive design for easy navigation and use.
*   **Improved Security:** Measures to prevent unauthorized access and secure data.
*   **Automation:** Reducing manual tasks through hardware integration and software logic.

### Goals & Impact

VoltVault aims to contribute positively by:

*   Aligning with UN Sustainable Development Goals:
    *   **SDG 7:** Affordable and Clean Energy
    *   **SDG 3:** Good Health and Well-being
    *   **SDG 11:** Sustainable Cities and Communities
    *   **SDG 13:** Climate Action
*   Providing a superior user experience for EV owners.
*   Increasing operational efficiency for charging station operators.
*   Promoting the adoption of electric vehicles by making charging easier and more reliable.
*   Reducing carbon footprint (CO2 reduction).

---

## Key Features

*   **User Management (Client & Employee):**
    *   Secure Login/Authentication.
    *   User-friendly Sign-up process (including camera capture for profile).
    *   Role-based access control.
    *   Employee/Client CRUD operations.
    *   Client credit management.
*   **Charging Station Management:**
    *   Station information display and management.
    *   Map integration to show station locations.
*   **Vehicle Management:**
    *   Tracking associated vehicles (Brand, Battery Capacity, HP).
*   **Billing & Payment:**
    *   Invoice generation for services.
    *   Integrated calculator for cost estimation/deduction.
    *   Payment processing via keypad input (linked to client credit).
*   **Real-time Information & Interaction:**
    *   QR Code generation for clients (containing user info).
    *   Real-time updates based on sensor data (e.g., car presence).
    *   Integrated Chat functionality (Employee communication).
*   **Reporting & Analytics:**
    *   Data visualization (e.g., pie charts for salary distribution, client credits, car brands).
    *   Data export options (PDF, XLS).
*   **Hardware Integration:**
    *   RFID reader for employee authentication.
    *   Motion sensor for vehicle detection.
    *   Keypad and LCD for client interaction and payment.

---

## Hardware Integration (Arduino)

The system integrates with Arduino microcontroller boards to interact with the physical environment:

1.  **Employee Authentication (Scenario 1):**
    *   **Components:** Arduino (e.g., Uno), RFID Reader (RC522), LEDs (Green/Red).
    *   **Functionality:** Employees scan their RFID card. The system verifies the ID; a green LED lights up for valid IDs, red for invalid ones.
2.  **Vehicle Detection (Scenario 2):**
    *   **Components:** Arduino (e.g., Mega), PIR Motion Sensor, LCD/7-Segment Display.
    *   **Functionality:** A motion sensor detects when a car enters the station. This triggers an update in the desktop application and potentially displays the count of cars on a local display.
3.  **Client Interaction & Payment (Scenario 3):**
    *   **Components:** Arduino (e.g., Uno), Keypad (4x4), LCD Display.
    *   **Functionality:** Clients enter their unique code/NIC via the keypad. Their available credit is shown on the LCD. They use the keypad again to input the charging amount, which is then deducted from their credit balance managed by the application.

**Non-Functional Hardware Requirements:**
*   Keypad must be durable for frequent use.
*   Motion sensor needs adequate sensitivity.

---

## Technology Stack (Inferred)

*   **Frontend/Desktop:** Qt Framework (Based on window titles like "Dialog", "Widget" in screenshots) - likely C++
*   **Hardware:**
    *   Arduino Uno / Arduino Mega 2560
    *   RFID-RC522 Reader
    *   PIR Motion Sensor
    *   Character LCD Display (e.g., 16x2 or 20x4)
    *   Membrane Keypad (4x4)
    *   LEDs
*   **Database:** (Specific DB not mentioned, but required for persistence)
*   **Serial Communication:** For Arduino-Desktop App interaction.

---

## Design

*   **Main Font:** Berlin Sans FB
*   **Color Palette:**
    *   Backgrounds: `#B6D7A8` (Light Green), `#7FA39A` (Teal Green)
    *   Accents: `#FAD8C3` (Light Peach), `#EBB7C0` (Light Pink)
    *   Other UI element colors visible in screenshots.
*   **Icons:** Various icons used for UI clarity (visible on slide 35).

---

## Getting Started

*(Provide instructions on how to set up and run the project. Below are placeholders.)*

### Prerequisites

*   Install Qt Framework ([Link to Qt](https://www.qt.io/))
*   Install Arduino IDE ([Link to Arduino IDE](https://www.arduino.cc/en/software))
*   Required Arduino libraries (e.g., MFRC522, LiquidCrystal)
*   Database system (Specify which one if applicable)
*   C++ Compiler (usually included with Qt)
*   ... (any other dependencies)

### Installation

1.  Clone the repo:
    ```sh
    git clone https://github.com/your-username/voltvault.git
    ```
2.  Navigate to the project directory:
    ```sh
    cd voltvault
    ```
3.  Configure the database connection (provide details).
4.  Open the project `.pro` file in Qt Creator.
5.  Upload the Arduino sketches (`.ino` files) from the `/arduino` directory to the respective Arduino boards. Ensure the correct ports are selected.

### Running the Application

1.  Build the project in Qt Creator (Build > Build Project "VoltVault").
2.  Run the application from Qt Creator (Build > Run).
3.  Ensure the Arduino devices are connected via USB and recognized by the system.

---

## Usage

1.  **Employees:** Log in using their credentials. Manage clients, cars, stations, view statistics, and potentially communicate via chat. Authenticate at physical terminals using RFID cards.
2.  **Clients:** Sign up (potentially using the camera feature). Use their unique code/NIC at the station keypad to view credit and authorize charging sessions. Receive invoices for services. Use the map feature (within the app if available, or implied via station finder) to locate stations.

---

## Future Perspectives

We are committed to continuously improving and expanding the VoltVault project. Future plans include:

*   Adding more advanced analytics features.
*   Integrating with real-time energy pricing.
*   Developing mobile companion apps.
*   Enhancing hardware integration capabilities.
*   Expanding features based on user feedback, aiming for a more sustainable and connected world.

---

## Team (N.A.N.S.Y)

*   **N**ada Latrach
*   **A**rij Mahouachi
*   **N**oura Jaziri
*   **S**kander Kechaou
*   **Y**oussef Ressaissi

---

## Acknowledgments

*   Inspired by the need for better EV charging infrastructure.
*   Guided by the UN Sustainable Development Goals.
*   Icons used from various sources (mention sources if known/required).
*   Qt Project ([https://www.qt.io/](https://www.qt.io/))
*   Arduino Project ([https://www.arduino.cc/](https://www.arduino.cc/))
