# Router Experiments Log

These are notes and results from my experiments with two consumer‑grade 2.4 GHz routers (an iBall and a TP‑Link). The goal is to characterize basic networking behavior, test throughput and latency, and understand how IP allocation and routing behave when connecting two routers together.

***

## Day 1

### iBall Router (Router Red)

- **SSID**: `Router Red`  
- **WLAN Password**: `16512214`  
- **Admin Credentials**:  
  - User: `admin`  
  - Password: `admin`  

Basic functions:
- WLAN: Working  
- Traffic statistics: Working (interface is slow to respond)  
- IP allocation (DHCP): Working  

Python server:
- Set up a simple Python HTTP / TCP server on the laptop for testing: Working  

**Performance measurements (laptop connected to WLAN of Router Red)**  
- **File Transfer (Throughput)**: ~10 MB/s  
- **Ping statistics (to router at 192.168.2.1)**:  
  - Loss: 0%  
  - Minimum: 0 ms  
  - Maximum: 320 ms  
  - Average: 23 ms  

Wi‑Fi bands:
- 2.4 GHz: Working  
- 5 GHz: N/A  

**Laptop IP assignment**: `192.168.2.201`  

***

### TP‑Link Router (Router White)

- **SSID**: `Router White`  
- **WLAN Password**: `16512214`  
- **Admin Credentials**:  
  - User: `admin`  
  - Password: `admin`  

Basic functions:
- WLAN: Working  
- Traffic statistics: Working  
- IP allocation (DHCP): Working  

Python server:
- Same setup on laptop: Working  

**Performance measurements (laptop connected to WLAN of Router White)**  
- **File Transfer (Throughput)**: ~3 MB/s  
- **Ping statistics (to router at 192.168.3.1)**:  
  - Loss: 0%  
  - Minimum: 18 ms  
  - Maximum: 434 ms  
  - Average: 289 ms  

Wi‑Fi bands:
- 2.4 GHz: Working  
- 5 GHz: N/A  

**Laptop IP assignment**: `192.168.3.100`  

**Notes on Router White**  
- The admin interface is much messier and slower to navigate than the iBall web UI.  
- This router appears older and contributes to lower speeds and higher latency.  
- It offers more advanced configuration options (e.g., port forwarding, QoS, wireless modes), but the UI is less intuitive.  

***

### Connecting the Two Routers

#### Setup Overview

**Router White (TP‑Link)**
- IP: `192.168.3.1`  
- DHCP: **ON**  
- Type: **Main gateway** (serving as the primary router)  

**Router Red (iBall)**
- IP: `192.168.2.1`  
- DHCP: **?** (not yet confirmed; likely ON by default)  
- Type: **Secondary node**  

#### Physical Connection

- Connected `Router Red (LAN2)` ↔ `Router White (LAN3)` via Ethernet cable.  
- Laptop connected to the WLAN of **Router White**.  
- IP configuration observed on laptop confirmed assignment via Router White’s DHCP pool (`192.168.3.100`).  

**Test results after connecting both routers**

- **IP assigned to device connected to Router White (WLAN)**: `192.168.3.100`  
- **Ping to Router White (192.168.3.1)**:  
  - Packets: Sent = 4, Received = 4, Lost = 0 (0% loss)  
  - Approximate round trip times (ms):  
    - Minimum = 6 ms  
    - Maximum = 19 ms  
    - Average = 9 ms  

- **Ping to Router Red (192.168.2.1)**:  
  - Packets: Sent = 4, Received = 2, Lost = 2 (50% loss)  
  - Response: `Destination Host Unreachable`  

**Observations**

- The laptop can reach Router White (`192.168.3.1`) consistently, but cannot reliably reach Router Red (`192.168.2.1`).  
- This indicates that there is **no active route between the two subnets**, even though a physical Ethernet link exists between the routers.  
- The most likely cause is **DHCP being enabled on both routers**, so each thinks it is a standalone gateway and does not advertise routes to the other.  
- In this case, the routers effectively operate as **two separate subnets (`192.168.2.x` and `192.168.3.x`)**, with no routing bridge between them.  

***

## Day 2

### Turning Off DHCP on One Router

**Goal**: Make one router act as a pure access‑point / switch and allow proper routing between subnets.

**Setup**
- **Router Red (iBall)**:  
  - DHCP: **ON**  
- **Router White (TP‑Link)**:  
  - DHCP: **OFF**  
- Physical connection:  
  - `Router Red (LAN2)` ↔ `Router White (LAN3)` (same Ethernet link)  

All other settings (SSID, passwords, etc.) were left unchanged.

**Results**

- When connecting to **either WLAN**, the device only sees **Router Red’s gateway** (`192.168.2.1`).  
- **Router White** effectively behaves as an **extension** of Router Red, i.e., a simple access point and switch.  
- The Router White admin page at `192.168.3.1` becomes **inaccessible** from any WLAN client.  
- Direct attempts to access `192.168.3.1` fail, confirming that Router White is no longer acting as a gateway; its own subnet is unreachable via the connected WLAN.  

**Method to Restore DHCP on Router White**

Because the admin page of Router White was unreachable, the following steps were taken:

1. **Disconnected the Ethernet link** between Router Red and Router White.  
2. **Connected laptop directly to the WLAN of Router White**.  
3. **Manually assigned a static IP** on the laptop (via Control Panel / network settings) within the `192.168.3.x/24` subnet.  
4. **Accessed Router White’s admin page at `192.168.3.1`** using the static IP configuration.  
5. **Re‑enabled DHCP** on Router White and saved the configuration.  

***

### Router White Firmware Flashing Attempts

Several attempts were made to flash alternative firmware on the TP‑Link router (Router White) to explore more advanced features and debugging capabilities.

**Observations**
- **TP‑Link firmware restrictions**:  
  - TP‑Link appears to block firmware downgrades and unofficial firmware through its official web updater.  
  - The online firmware selection UI is cluttered and hard to navigate, making it difficult to locate the exact model and version.  
- **OpenWRT compatibility**:  
  - OpenWRT does not list a supported firmware version for this specific TP‑Link model (or the site’s layout is too confusing to confirm).  
- **DD‑WRT compatibility**:  
  - Reported DD‑WRT firmware for this model is being blocked or disallowed by TP‑Link’s mechanism.  

**Conclusion**
- At this stage, **firmware flashing is not feasible** without risking brick or violating device restrictions.  
- Any further experimentation will rely on the **stock firmware** and configuration within the constraints of the built‑in admin interface.