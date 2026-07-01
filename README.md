# Communication Systems & Signal Processing

A MATLAB-based framework for the mathematical modeling of communication systems, focusing on end-to-end audio signal processing, digital filtering, and wave modulation.

**Note:** This project is being developed as part of an ongoing internship at the **Indian Institute of Information Technology (IIIT) Vadodara**, under the mentorship of **Dr. Jignesh Bhatt**.

---

## Features and Core Models

This repository contains MATLAB scripts developed to simulate real-world signal behavior fundamentally, minimizing the use of high-level abstract functions. The key implementations include:

### 1. Audio Effects and Space Simulation
Algorithms designed to simulate the physics of sound in physical environments:
* **`audioEcho.m`**: Generates distinct, delayed sound reflections (Echo).
* **`audioReverb.m`**: Simulates complex, overlapping reflections of sound within an acoustic space (Reverberation).
* **`unitDelay.m`**: Introduces precise time-domain unit delays to discrete signals.
* **`audioStableNoise.m`**: Generates and introduces stable background noise for system stress-testing and filter evaluation.

### 2. Signal Modulation
* **`AMEncoderSystem.m`**: A complete Amplitude Modulation (AM) system that maps an input baseband/message signal onto a high-frequency carrier wave for transmission.

### 3. Audio Filtering
Finite Impulse Response (FIR) filter implementations utilizing windowing techniques (e.g., Hamming windows):
* **`audioLowPass.m`**: Attenuates high-frequency noise, allowing baseband frequencies to pass.
* **`audioHighPass.m`**: Removes low-frequency interference, isolating higher frequency components.
* **`movingAverageLowPassFilter.m` & `audioLowPassMovingAvg.m`**: Applies a moving average algorithm to smooth signal fluctuations in the time domain.

---

## Visualizations and System Outputs

Below are examples of the system outputs demonstrating the mathematical manipulation and analysis of the audio samples:

### 1. Echo and Reverb (Time Domain Decay)
*Demonstrates the exponential decay tail in the reverb output, alongside the distinct secondary impulse in the echo output.*

![Echo and Reverb Plot](<img width="960" height="600" alt="Screenshot 2026-06-21 102340" src="https://github.com/user-attachments/assets/13df9ea0-5af2-4cf4-a242-0654792e1227" />
) 


### 2. Amplitude Modulation
*Displays the high-frequency carrier wave successfully modulated by the time-domain source message signal.*

![AM Modulated Wave](<img width="1051" height="690" alt="amplitude modulation subplot" src="https://github.com/user-attachments/assets/d5bb913f-a683-418f-8663-81840667950a" />
)


### 3. Frequency Spectrum Analysis (FFT)
*Transforms the discrete signals into the frequency domain to verify the efficacy of the implemented filtering operations.*

![Frequency Domain Plot](<img width="1059" height="699" alt="moving-avg-fft" src="https://github.com/user-attachments/assets/3f7b6740-7acd-487f-a207-69cf774f3ae9" />
)

---

# Vision Helicopter System
A robust low level system desigend to take inputs from either the user or primarily a vision based RL model. The flight controller system implements PID setpoint tracking and full state LQR loop.

The PID loop is responsible for the alitude control, and velocity to angle (pitch/roll/yaw) conversion. The single output outer loop is perfectly handled by the PID controller. 
The LQR on the other hand is responsible for the inner loop, converting angles (roll/pitch/yaw) and the angle rates (p, q, r) into meaningful attitude values (torque and thrust). Since the outer loop involves several variables, 3 different LQR loops are to be implemented, each one of these loops is a 2 state, 1 control LQR loop responsible for thrust in one axis of rotation. The key benefit of using LQR is that it allows us to optimise the feedback according to the plant model.

## Usage Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/saxena-shashwat/Communication-Systems.git
