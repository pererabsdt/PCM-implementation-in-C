# Pulse Code Modulation (PCM) Implementation

This project implements a Pulse Code Modulator in C, along with an analog signal generator for testing purposes. The implementation is modular, with each component responsible for a specific PCM function.

## Components

### 1. Analog Signal Generator
- Function: `float analog_signal_generator(asignal signal, int t)`
- Generates a sinusoidal analog signal based on input parameters.

### 2. Sampler
- Function: `void sampler(float *samples, int interval, asignal signal)`
- Takes samples from the analog signal at specified intervals.

### 3. Quantizer
- Function: `void quantizer(float *samples, int *pcmpulses, int levels, float A)`
- Quantizes the sampled values into discrete levels.

### 4. Encoder
- Function: `void encoder(int *pcmpulses, int *dsignal, int encoderbits)`
- Encodes the quantized values into a binary stream.

### 5. Run Function
- Function: `void run()`
- Orchestrates the PCM process by reading input parameters and executing the components in sequence.

## Input Parameters

The program takes the following space-separated input parameters:
```
A omega sigma duration interval encoderbits
```

Where:
- `A`: Peak amplitude
- `omega`: Angular frequency in radians
- `sigma`: Phase in radians
- `duration`: Number of time units the signal exists
- `interval`: Sampling interval
- `encoderbits`: Number of bits used for a single PCM code

## Output

The program outputs the final PCM encoded binary stream to stdout.

---

This project was completed as a lab exercise for the Data Communication and Networking module in Semester 3 of the Computer Science and Engineering at University of Moratuwa. 
