# Simulink Flight Controller Models

This module features real-time, robust control architectures for the **Vision-Based Helicopter System**.

## System Architecture

The flight controller is divided into two distinct feedback paradigms:
1. **PID Control (`servo_control.slx`)**: Acts as the outer loop. It evaluates high-level commands (e.g., target altitude, desired directional velocity) and maps these goals into explicit attitude reference angles.
2. **LQR State Feedback (`stateFeedback.slx`)**: Serves as the aggressive inner loop. Due to multi-variable coupling, it implements three distinct 2-state, 1-control LQR instances, calculating exact torque and thrust vectors for hardware implementation.

All models can be compiled for embedded execution via HDL/C-code generation.
