##AC Waveform Analyzer
An automated engineering tool developed in C to process and analyze 3-phase power quality data from industrial log files. This program calculates electrical parameters and identifies potential grid faults or anomalies.

## Features
3-Phase Analysis: Processes Phase A, Phase B, and Phase C data simultaneously.

RMS Calculation: Computes the Root Mean Square voltage for every 100-sample cycle.

Peak-to-Peak Amplitude: Tracks the voltage to find the total difference between high and low peaks.

DC Offset Detection: Calculates means to identify unwanted DC shifts.


Fault Logging:

Tolerance Warnings: Flags any RMS values that fall outside the ±10% threshold (207V - 253V).

Clipping Detection: Identifies and logs precise timestamps for any voltage spikes exceeding 324.9V.

Automated Reporting: Generates a clean, formatted text report (outcome/report.txt) for engineering review.

## Project Structure
main.c: The entry point of the application; manages the primary data array and high-level logic.

waveform.c / waveform.h: Contains the mathematical algorithms for RMS, DC Offset, and Clipping.

io.c / io.h: Handles file input/output, including CSV reading and report creation

power_quality_log.csv: The raw data source containing time-stamped voltage samples.

## Requirements
Compiler: GCC (MinGW for Windows users).

Build System: CMake 3.0 or higher (Optimized for CLion).

Data: A valid power_quality_log.csv must be present in the project root.

## How to Build and Run
Using CLion:
Open the project folder in CLion.

Ensure the power_quality_log.csv is in the same directory as your source files.

Click the Run button (green arrow) in the top right corner.

Check the outcome/ folder for the generated report.txt.

Using Terminal (GCC):
Compile the program ->
gcc main.c waveform.c io.c -o WaveformAnalyzer -lm

Run the program -> ./WaveformAnalyzer

## Development & Testing

Github Repository: https://github.com/atorresda/AC-Waveforms

Unit Testing: Verified individual math functions against manual calculations.

Integration Testing: Ensured effective data transfer across pointers and function layers.

Scenario Testing: Validated fault-detection logic using a high-voltage surge scenario (310V RMS).

## Author
Anika Torres Davalos Engineering Development Project - May 2026