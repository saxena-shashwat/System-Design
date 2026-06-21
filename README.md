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

![Echo and Reverb Plot](<.\signals-and-systems\Reports\echo and reverb test.png>) 


### 2. Amplitude Modulation
*Displays the high-frequency carrier wave successfully modulated by the time-domain source message signal.*

![AM Modulated Wave](<.\signals-and-systems\Reports\amplitude modulation subplot.png>)


### 3. Frequency Spectrum Analysis (FFT)
*Transforms the discrete signals into the frequency domain to verify the efficacy of the implemented filtering operations.*

![Frequency Domain Plot](<.\signals-and-systems\Reports\frequency-domain-noise-filters.png>)

---

## Usage Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/saxena-shashwat/Communication-Systems.git