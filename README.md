# Communication Systems — Learning Lab

This repository is a structured archive of my hands-on learning in communication systems, networking, and signal processing. I use experiments, small projects, and notes to explore concepts such as networking (routers and wireless protocols), DSP, ADCs, modulation/demodulation, and related coding work. The goal is to keep a clear, reproducible log of experiments and resources I can revisit while studying and building projects.

## What you’ll find here

- Experimental writeups and results for hardware and software projects.
- Code used to generate or analyze signals, process data, or control devices.
- Lab notes, block diagrams, schematics, and photos that document setups.
- Short tutorials and references that summarize key concepts I learn.
- Scripts and configs for reproducible projects (firmware, router setups, simulation notebooks).

## Current areas of focus

- Networking basics and home router experiments (2.4 GHz hardware, firmware, SSID/MTU, packet captures).
- Digital Signal Processing (sampling, filters, FFTs, windowing, spectral analysis).
- ADCs and data acquisition (sampling rates, quantization, anti-aliasing).
- Modulation and demodulation (AM, FM, ASK/FSK/PSK), baseband and passband processing.
- MATLAB / Python / C code for simulating and processing signals.

## Example experiments

- Router experiments: flashing/reading firmware, changing channel/Tx power, capturing packets with Wireshark, testing throughput and latency under interference.
- ADC bench tests: characterizing noise floor, effective number of bits (ENOB), and SNR using known input signals.
- DSP notebooks: implementing FIR/IIR filters, window comparisons, and FFT visualizations in Python.
- Modulation demos: generate and demodulate ASK/FSK/PSK signals and visualize spectra and eye diagrams.

## How to use this repo

- Browse the `/experiments` folder for step-by-step writeups and instrumentation notes.
- Run notebooks in `/notebooks` to reproduce simulations and plots.

### Python Requirements

- Python 3.10+
- numpy
- scipy
- matplotlib
- pandas
- jupyter

- Check `/hardware` for PCB schematics, breadboard photos, and wiring diagrams.
- See `/code` for firmware, Python scripts, and small C programs used in experiments.

## Tools and dependencies

- Python: numpy, scipy, matplotlib, pandas, jupyter, librosa (optional for audio)
- Wireshark, tcpdump for packet capture and analysis
- GNU Radio (optional) or MATLAB/Octave for signal processing experiments
- Common microcontroller toolchains (PlatformIO, avr-gcc, stm32cube) if using MCU boards

## Contributing (Personal)

This is a personal learning log. I will maintain consistent structure and documented steps so each experiment is reproducible. Notes and scripts will include required hardware, software versions, and command examples.

## Author

**Shashwat**  
B.Tech, Electronics & Communication Engineering — First Year, Nirma University, Ahmedabad  
Project started: Summer 2026