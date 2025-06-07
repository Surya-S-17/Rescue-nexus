
# 🚨 Rescue Nexus

**Rescue Nexus** is an intelligent emergency vehicle tracking and alert system designed to enhance road safety and reduce ambulance response times. It leverages real-time GPS tracking, ESP32-based proximity alerts, and a responsive user interface to notify nearby drivers, helping clear the path quickly and save lives.

---

## 📌 Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Architecture](#architecture)
- [Technology Stack](#technology-stack)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

---

## 🧠 Project Overview

**Rescue Nexus** addresses the critical delay in emergency response due to traffic congestion. By alerting nearby drivers of an approaching ambulance (within ~5 meters) and visualizing the ambulance's location, this system facilitates timely response and coordination.

---

## ✨ Features

- 🔴 **Real-Time Tracking** of ambulances via GPS
- 📳 **Proximity Alerts** through ESP32 signal detection
- 📱 **User-Controlled Alarms** with manual silencing option
- 🗺️ **Live Map View** using Google Maps or Mapbox
- 🔔 **Cross-Platform Notifications**
- ⚡ **Low Latency Communication** between devices

---

## 🏗 Architecture

![image](https://github.com/user-attachments/assets/1876cbfc-4ae1-44a9-b1f9-0194e156648f)


---

## 🛠 Technology Stack

| Component          | Technology                       |
| ------------------ | -------------------------------- |
| Frontend           | React / React Native / Streamlit |
| Real-Time Database | Firebase Realtime DB / Firestore |
| Microcontroller    | ESP32 (for signal transmission)  |
| Maps Integration   | Google Maps API / Mapbox         |
| Backend (optional) | Node.js / Express                |
| Notifications      | Push API / Local Alarm           |

---
# Product

![IMG_3905](https://github.com/user-attachments/assets/08678ea5-02d5-4155-8b81-d14d37f003cb)

![IMG_3909](https://github.com/user-attachments/assets/e0021c2f-c68b-4a23-83b3-2bb08317a131)

![IMG_3910](https://github.com/user-attachments/assets/58b6f401-d480-4a57-b94a-dd8ca3f876f7)

---

## 🚀 Installation

### 🔧 Prerequisites

* Node.js and npm installed
* Firebase project (Realtime DB or Firestore enabled)
* ESP32 board(s) with Arduino IDE or PlatformIO
* Google Maps API key (or equivalent)

### 🛠 Setup Steps

1. **Clone the repository:**

   ```bash
   git clone https://github.com/Surya-S-17/Rescue-nexus.git
   cd rescue-nexus
   ```

2. **Install frontend dependencies:**

   ```bash
   npm install
   ```

3. **Configure Firebase:**
   Create a file `src/firebaseConfig.js` with your Firebase credentials:

   ```js
   const firebaseConfig = {
     apiKey: "YOUR_API_KEY",
     authDomain: "your-app.firebaseapp.com",
     databaseURL: "https://your-app.firebaseio.com",
     projectId: "your-app-id",
     // ...
   };
   export default firebaseConfig;
   ```

4. **Add Google Maps API Key:**
   Set up `.env` file or update the map component config with:

   ```
   REACT_APP_GOOGLE_MAPS_API_KEY=your_key_here
   ```

5. **Flash ESP32 Modules:**
   Go to `/esp32` folder and follow instructions to upload firmware to ambulance and receiver devices.

6. **Run the app locally:**

   ```bash
   npm start
   ```

---

## 📲 Usage

1. Launch the **Rescue Nexus** app on your device.
2. Grant **location** and **notification** permissions.
3. The app:

   * Listens for nearby ambulance signals from ESP32
   * Displays ambulance's GPS position on map
   * Sounds an alarm when ambulance is within \~5 meters
4. Manually **acknowledge & silence** alarm from UI.

---

## ⚙️ How It Works

1. 🚑 **Ambulance ESP32** captures GPS coordinates and transmits via Wi-Fi/Bluetooth.
2. 🚗 **Nearby ESP32 devices** detect the ambulance signal and notify paired user apps.
3. 🌐 **Firebase** updates the ambulance's real-time location for map rendering.
4. 📱 **Users** receive a loud alarm and visual alert with ambulance position.

---

## 🔮 Future Enhancements

* 🧠 Predictive ambulance route using ML
* 🗣 Voice & vibration alerts for accessibility
* 🚨 Multi-ambulance support with prioritization
* 📡 Offline fallback support with peer-to-peer mode
* 🔐 Improved encryption and authentication for ESP32 comms

---

## 🤝 Contributing

Contributions are welcome!

1. Fork the repo
2. Create a branch: `git checkout -b feature/YourFeature`
3. Commit: `git commit -m 'Add YourFeature'`
4. Push: `git push origin feature/YourFeature`
5. Open a Pull Request

---

## 🙏 Acknowledgments

* Developed with support from **PSG iTech**
* Inspired by the need for faster and smarter emergency vehicle coordination
* Thanks to open-source contributors from Firebase, ESP32, React, and Google Maps communities

---
