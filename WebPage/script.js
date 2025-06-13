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
    fetch(url, { cache: "no-store" })
        .then(res => res.text())
        .then(res => {
            const confirmation = document.getElementById("confirmationMessage");
            if (res === "success") {
                confirmation.textContent = "Wi-Fi Connected Successfully!";
                confirmation.style.display = "block";
                setTimeout(() => {
                    document.getElementById("wifiSetup").classList.add("hidden");
                    document.getElementById("connected").classList.remove("hidden");
                }, 1000);
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
    if (passwordInput.type === "password") {
        passwordInput.type = "text";
        toggleButton.textContent = "👁️‍🗨️";
    } else {
        passwordInput.type = "password";
        toggleButton.textContent = "👁️";
    }
}

window.onload = loadNetworks;
