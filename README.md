# ESP8266 Web-Based Wi-Fi Setup Portal

This repository contains a complete modular Wi-Fi setup portal system for ESP8266-based IoT devices. The portal allows users to scan available Wi-Fi networks, select a preferred SSID, input the password, and connect the ESP8266 module to their local Wi-Fi network — all through a user-friendly web interface hosted directly on the ESP device.

Developed by **Md Shaifulla Zibon**, this system is optimized for **real-time IoT systems** and **production-level embedded solutions**, especially where **third-party cloud services are avoided**.

---

## 🌟 Features

- ✅ **Access Point (AP) Mode Startup** – ESP8266 starts in AP+STA mode, creating its own Wi-Fi network.
- ✅ **Responsive Web Interface** – Modern HTML/CSS/JS served directly from ESP8266 memory.
- ✅ **Wi-Fi Network Scanning** – Lists available networks for easy selection.
- ✅ **Secure Password Entry** – Password toggle and form validation.
- ✅ **Auto Switch to STA Mode** – Shuts down AP after successful connection.
- ✅ **Modular Codebase** – Easy to integrate `.h`, `.cpp`, and `.ino` files.
- ✅ **No Cloud Dependency** – Works offline, local control only.

---

## 🏗️ Folder Structure

esp8266-wifi-setup/
├── ESP8266-AP/
│ ├── WiFiSetup.h # Function declarations
│ ├── WiFiSetup.cpp # Core logic: server, scanning, connection
│ └── WiFiSetupDemo.ino # Demo sketch with AP credentials
├── README.md # Project documentation
├── LICENSE # MIT License
├── .gitignore # Build and temp file exclusion
└── keywords.txt # Arduino IDE syntax highlighting


---

## 🚀 How It Works

1. ESP8266 boots in `WIFI_AP_STA` mode.
2. Creates a Wi-Fi network (e.g., `MyIoT_Device`).
3. Hosts a web server at `192.168.4.1`.
4. User connects and configures their Wi-Fi via browser.
5. ESP connects to the selected network and shuts down AP.

---

## ⚙️ How to Use

### 🔧 Prerequisites

- Arduino IDE with ESP8266 board support
- ESP8266 device (e.g., NodeMCU, Wemos D1 Mini)

### 📥 Steps

1. Clone or download this repository.
2. Open `src/WiFiSetupDemo.ino` in Arduino IDE.
3. Edit these lines to set your AP name and password:
   ```cpp
   const char* apSSID = "MyIoT_Device";
   const char* apPassword = "12345678";
Upload the sketch to your ESP8266.

Connect your phone or PC to MyIoT_Device Wi-Fi.

Open your browser and go to http://192.168.4.1.

Select your Wi-Fi, enter password, and connect.

🧠 Why This Project Exists
In professional IoT deployments, many developers avoid platforms like Blynk, Firebase, or Adafruit IO due to:

🔐 Privacy and data ownership

🌐 Localized, offline operation

📡 Real-time responsiveness

💸 Cost and licensing avoidance

This project provides an independent, offline Wi-Fi provisioning system perfect for:

Local Node.js dashboard integration via WebSocket

Industrial control without internet dependency

Custom SMPS or relay-based IoT systems

📦 Example Use Case
This system is actively used in Zibon’s commercial-grade embedded systems for:

✅ Real-time web dashboards (via WebSocket)

🛡️ License
This project is licensed under the MIT License.
You are free to use, modify, and redistribute — just keep the original license notice.

See LICENSE for full terms.

🧑‍💻 Developer Info
Md Shaifulla Zibon
IoT Systems Designer | SMPS Engineer | Web Dashboard Integrator
🎓 B.Sc. in Electrical and Electronic Engineering
🏫 European University of Bangladesh"# esp8266-wifi-setup-portal" 
