# VTOL UAV Motor Controller (Simulink to SIL)

This repository contains the auto-generated C source code for a PID-controlled Brushless DC (BLDC) motor, designed for Vertical Take-Off and Landing (VTOL) UAV applications. 

The project demonstrates a rigorous **Model-Based Design (MBD)** workflow, transitioning from mathematical block diagrams in MATLAB/Simulink to deployable embedded C code, verified via Software-in-the-Loop (SIL) simulation.

## 🚀 Live Simulation (Wokwi)
You can view and run the compiled logic interactively in the browser here: 
https://wokwi.com/projects/461914427293991937

## 📂 Repository Structure
The generated code has been modularized for clean embedded implementation:
* `/src` : Contains the core PID controller logic (`PID0.c`, `PID0.h`), optimized as an atomic subsystem with fixed-step solvers.
* `/vtol` : Contains the main plant model and motor control generation files.

## ⚙️ Engineering Workflow
1. **Mathematical Modeling:** Designed the VTOL plant and PID feedback loop using MATLAB/Simulink.
2. **Hardware Constraints:** Configured the model for embedded deployment by enforcing fixed-step integration and disabling MAT-file logging.
3. **Code Generation:** Utilized Simulink Coder to translate the atomic subsystems into hardware-agnostic, portable C/C++ code.
4. **Verification:** Tested the generated logic using the Wokwi simulator alongside the Arduino framework.

## 🔮 Future Hardware Implementation
This project is currently in the SIL (Software-in-the-Loop) phase. The next planned phase involves deploying this control logic onto physical hardware, specifically interfacing a microcontroller (e.g., TI C2000 or Arduino architecture) with physical ESCs and BLDC motors to validate the closed-loop response in the physical world.

## 📄 License
This project is licensed under the MIT License - see the LICENSE file for details.
