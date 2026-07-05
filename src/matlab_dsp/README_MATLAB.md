# MATLAB Digital Signal Processing

This directory contains MATLAB source code for fundamental audio signal processing, filtering, and wave modulation.

## Folder Structure

- `audio_processing/`: Contains time-domain implementations for spatial acoustic effects (Echo, Reverb) and various Finite Impulse Response (FIR) filters. These filters use mathematical windows (e.g., Hamming) to ensure smooth frequency roll-off.
- `modulation/`: Contains an end-to-end Amplitude Modulation (AM) transmitter logic.
- `utils/`: Common mathematical and signal conditioning utilities used across modules.

All functions are implemented from foundational mathematics, intentionally avoiding high-level abstractions like `filter()` where instructive insight is required.
