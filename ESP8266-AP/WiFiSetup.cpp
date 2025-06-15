// File: WiFiSetup.cpp
#include "WiFiSetup.h"
#include <ESP8266WiFi.h>

WiFiSetup::WiFiSetup(const char* ssid, const char* password, IPAddress ip)
  : server(80), apSSID(ssid), apPassword(password), apIP(ip) {}

void WiFiSetup::begin() {
  WiFi.mode(WIFI_AP_STA);
  
  IPAddress gateway = apIP; 
  IPAddress subnet(255, 255, 255, 0);
  
  WiFi.softAPConfig(apIP, gateway, subnet);

  WiFi.softAP(apSSID, apPassword);

  server.on("/", std::bind(&WiFiSetup::handleRoot, this));
  server.on("/scan", std::bind(&WiFiSetup::handleScan, this));
  server.on("/connect", std::bind(&WiFiSetup::handleConnect, this));

  server.begin();
  Serial.println("HTTP server started");
}

void WiFiSetup::handle() {
  server.handleClient();
}

void WiFiSetup::handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void WiFiSetup::handleScan() {
  int n = WiFi.scanNetworks();
  String result = "[";
  for (int i = 0; i < n; i++) {
    if (i > 0) result += ",";
    result += "\"" + WiFi.SSID(i) + "\"";
  }
  result += "]";
  server.send(200, "application/json", result);
}

void WiFiSetup::handleConnect() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");

  Serial.println("Attempting to connect to: " + ssid);
  WiFi.begin(ssid.c_str(), password.c_str());

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 40) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to Wi-Fi!");
    server.send(200, "text/plain", "success");
    server.client().flush();
    server.client().stop();
    delay(5000);
    WiFi.softAPdisconnect(true);
    Serial.println("AP disconnected");
  } else {
    Serial.println("\nFailed to connect to Wi-Fi. Status: " + String(WiFi.status()));
    server.send(200, "text/plain", "failed");
    server.client().flush();
    server.client().stop();
  }
}

const char* WiFiSetup::htmlPage = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>IoT Wi-Fi Setup</title>
    <style>
        body { font-family: Arial, sans-serif; background: #e6e6fa; display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; }
        .container { background: #fff; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); text-align: center; width: 350px; }
        h2, h3 { color: #6a5acd; margin-bottom: 10px; }
        .input-group { position: relative; width: 100%; }
        input { width: 100%; padding: 10px 40px 10px 10px; margin: 5px 0; border: 1px solid #ccc; border-radius: 5px; box-sizing: border-box; }
        .toggle-password {
            display: flex;
            position: absolute;
            padding-top: 0px;
            height: 20px;
            width: 20px;
            right: 10px;
            top: 50%;
            transform: translateY(-50%);
            background: none;
            border: none;
            cursor: pointer;
            font-size: 16px;
            color: #6a5acd;
            align-items: center;
            justify-content: center;
        }
        .input-group button:hover { background: none; }
        button { width: 100%; padding: 10px; background: #6a5acd; color: white; border: none; border-radius: 5px; cursor: pointer; margin: 5px 0; }
        button:hover { background: #483d8b; }
        .hidden { display: none; }
        .network-list ul { list-style: none; padding: 0; text-align: left; }
        .network-list ul li { padding: 10px; background: #ebeaf9; margin: 5px 0; border-radius: 5px; cursor: pointer; }
        .network-list ul li:hover { background: #d9d7f1; }
        .connected { color: green; font-weight: bold; }
        #selectedSSID { color: #6a5acd; margin: 10px 0; font-style: italic; }
        #confirmationMessage { color: green; margin-top: 10px; display: none; }
    </style>

</head>

<body>
    <div class="container">
        <div id="login" class="page">
            <h2>Welcome to IoT Device</h2>
            <h3>Login to Access Point</h3>
            <input type="text" id="apUsername" placeholder="AP Username" value="admin">
            <div class="input-group">
                <input type="password" id="apPassword" placeholder="AP Password">
                <button class="toggle-password" onclick="togglePassword('apPassword')">👁️</button>
            </div>
            <button onclick="login()">Login</button>
        </div>
        <div id="wifiSetup" class="page hidden">
            <h2>Wi-Fi Setup</h2>
            <div class="network-list">
                <ul id="networkList"></ul>
            </div>
            <div id="selectedSSID"></div>
            <div class="input-group">
                <input type="password" id="wifiPassword" placeholder="Enter Wi-Fi Password">
                <button class="toggle-password" onclick="togglePassword('wifiPassword')">👁️</button>
            </div>
            <button onclick="connect()">Connect</button>
            <button onclick="showSettings()">Settings</button>
            <div id="confirmationMessage"></div>
        </div>
        <div id="settings" class="page hidden">
            <h2>Settings</h2>
            <h3>Change Username and Password</h3>
            <input type="text" id="newUsername" placeholder="Change Username">
            <div class="input-group">
                <input type="password" id="newPassword" placeholder="Change Password">
                <button class="toggle-password" onclick="togglePassword('newPassword')">👁️</button>
            </div>
            <button onclick="saveSettings()">Save</button>
            <button onclick="showWifiSetup()">Back</button>
        </div>
        <div id="connected" class="page hidden">
            <h2>Device Connected to Wi-Fi</h2>
            <p>You may now close this window.</p>
        </div>
    </div>

    <script>
        let selectedSSID = "";

        function login() {
            let username = document.getElementById("apUsername").value;
            let password = document.getElementById("apPassword").value;
            if (username === "admin" && password === "admin") {
                document.getElementById("login").classList.add("hidden");
                document.getElementById("wifiSetup").classList.remove("hidden");
                loadNetworks();
            } else {
                alert("Invalid credentials!");
            }
        }

        function loadNetworks() {
            fetch('/scan')
                .then(res => res.json())
                .then(ssids => {
                    let list = document.getElementById("networkList");
                    list.innerHTML = "";
                    ssids.forEach(ssid => {
                        let li = document.createElement("li");
                        li.textContent = ssid;
                        li.onclick = () => {
                            selectedSSID = ssid;
                            document.querySelectorAll("#networkList li").forEach(el => el.style.background = "#ebeaf9");
                            li.style.background = "#d9d7f1";
                            document.getElementById("selectedSSID").textContent = "Selected SSID: " + selectedSSID;
                        };
                        list.appendChild(li);
                    });
                })
                .catch(error => console.error("Error loading networks:", error));
        }
function connect() {
    let password = document.getElementById("wifiPassword").value;
    if (!selectedSSID) {
        alert("Please select a Wi-Fi network!");
        return;
    }
    let url = `/connect?ssid=${encodeURIComponent(selectedSSID)}&password=${encodeURIComponent(password)}`;
    console.log("Connecting to:", url);
    fetch(url, { cache: "no-store" }) // ক্যাশে এড়িয়ে ফ্রেশ রিকোয়েস্ট
        .then(res => res.text())
        .then(res => {
            console.log("Response received:", res); // ডিবাগিং
            const confirmation = document.getElementById("confirmationMessage");
            if (res === "success") {
                confirmation.textContent = "Wi-Fi Connected Successfully!";
                confirmation.style.display = "block";
                setTimeout(() => {
                    document.getElementById("wifiSetup").classList.add("hidden");
                    document.getElementById("connected").classList.remove("hidden");
                }, 1000); // 1 সেকেন্ড অপেক্ষা
            } else {
                confirmation.textContent = "Connection failed! Please try again.";
                confirmation.style.display = "block";
                setTimeout(() => confirmation.style.display = "none", 3000);
            }
        })
        .catch(error => console.error("Error connecting:", error));
}



        function showSettings() {
            document.getElementById("wifiSetup").classList.add("hidden");
            document.getElementById("settings").classList.remove("hidden");
        }

        function saveSettings() {
            let newUsername = document.getElementById("newUsername").value;
            let newPassword = document.getElementById("newPassword").value;
            if (newUsername && newPassword) {
                document.getElementById("apUsername").value = newUsername;
                document.getElementById("apPassword").value = newPassword;
                alert("Settings saved! Username and Password updated.");
                showWifiSetup();
            } else {
                alert("Please fill all fields!");
            }
        }

        function showWifiSetup() {
            document.getElementById("settings").classList.add("hidden");
            document.getElementById("wifiSetup").classList.remove("hidden");
            loadNetworks();
        }

        function togglePassword(inputId) {
            let passwordInput = document.getElementById(inputId);
            let toggleButton = passwordInput.nextElementSibling;
            if (passwordInput.getAttribute("type") === "password") {
                passwordInput.setAttribute("type", "text");
                toggleButton.textContent = "👁️‍🗨️";
            } else {
                passwordInput.setAttribute("type", "password");
                toggleButton.textContent = "👁️";
            }
        }

        window.onload = loadNetworks;
    </script>
</body>
</html>
)=====";
