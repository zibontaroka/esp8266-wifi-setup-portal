
# ESP8266 Web-Based Wi-Fi Setup Portal (v2.0.0)

A modular, cloud-free Wi-Fi provisioning system for ESP8266-based IoT devices. This portal enables users to scan Wi-Fi networks, select an SSID, enter a password, and connect the ESP8266 to a local network via a responsive web interface hosted on the device.

**Developed by Md Shaifulla Zibon** for privacy-conscious, real-time IoT applications.

## 🌟 What's New in v2.0.0
- **Custom SoftAP IP Support**: Set a custom Access Point IP (e.g., `192.168.10.10`) instead of the default `192.168.4.1`.
- **Improved Modularity**: `WiFiSetup` class now accepts an `IPAddress` parameter for easy setup from the main `.ino` file.
- **Backward Compatibility**: Supports older configurations without custom IP.

## 🚀 How It Works
1. ESP8266 boots in `WIFI_AP_STA` mode.
2. Creates a Wi-Fi network (e.g., `MyIoT_Device`) with a custom or default IP.
3. Hosts a web server for Wi-Fi configuration.
4. User connects via a browser to select and join a network.
5. ESP8266 switches to STA mode after successful connection.

## 🌐 Features
- Access Point (AP+STA) mode
- Responsive web interface (HTML/CSS/JS)
- Wi-Fi network scanning
- Secure password input with validation
- Auto-switch to STA mode
- Modular codebase (`.h`, `.cpp`, `.ino`)
- Offline, cloud-free operation
- Configurable AP IP address

## ⚙️ How to Use

### Prerequisites
- Arduino IDE with ESP8266 board support
  - Install the ESP8266 board package via Boards Manager: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
  - Required libraries: `ESP8266WiFi`, `ESPAsyncWebServer` (install via Library Manager)
- ESP8266 board (e.g., NodeMCU, Wemos D1 Mini)

### Setup Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/ESP8266-AP.git
   ```
2. Open `ESP8266-AP/ESP8266-AP.ino` in Arduino IDE.
3. Customize Access Point settings:
   ```cpp
   const char* apSSID = "MyIoT_Device";
   const char* apPassword = "12345678";
   IPAddress apIP(192, 168, 10, 10); // Custom SoftAP IP
   ```
4. Upload the web interface files:
   - Place the `data/` folder contents into the ESP8266 filesystem using the "ESP8266 Sketch Data Upload" tool (requires the `ESP8266FS` plugin).
5. Upload the sketch to your ESP8266.
6. Connect to the `MyIoT_Device` Wi-Fi network.
7. Open a browser and navigate to `http://192.168.10.10` (or your custom IP).

## 🧠 Why This Project?
Ideal for professional IoT systems requiring:
- 🔐 Data privacy and control
- 🌐 Offline operation
- ⚡ Real-time performance
- 💸 No cloud or licensing costs

Use cases:
- Local web dashboards
- SMPS-controlled automation
- Industrial IoT and factory equipment

## 📦 Project Structure
```bash
ESP8266-AP/
├── ESP8266-AP.ino        # Main firmware
├── WiFiSetup.h/.cpp      # Wi-Fi handler
├── data/                 # Web portal files (HTML/CSS/JS)
```

## 🛠 Troubleshooting
- **Cannot connect to AP**: Ensure the ESP8266 is powered and the `apSSID`/`apPassword` match your settings.
- **Web interface not loading**: Verify that the `data/` folder contents are uploaded to the ESP8266 filesystem.
- For more help, open an issue on GitHub.

## 📜 Version History
See [CHANGELOG.md](CHANGELOG.md) for detailed version updates.

---

## 🛡️ License
Licensed under the MIT License. See the `LICENSE` file for details.

- 
## 👨‍💻 Developer
**Md Shaifulla Zibon**  
IoT Systems Designer | SMPS Engineer | Web Dashboard Integrator  
🎓 B.Sc. in Electrical and Electronic Engineering, European University of Bangladesh  

💬 For questions, feature requests, or contributions, open an issue or pull request.
```
