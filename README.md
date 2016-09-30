# Instrumentation Oscilloscope

**A portable, low-cost oscilloscope for laboratory and educational usage**

## Abstract

Oscilloscopes are the devices used to observe varying signal voltages. Originally, the oscilloscopes are considered as costly, bulky and standalone devices. The project aims at building a low cost, low power, hand-held and portable oscilloscope with the basic utilities for efficient laboratory use. The device consists primarily of three parts, viz. signal conditioning, power management and micro-controller unit. The project has sampling as the basic technical basis, and the other circuits are employed to ensure minimal errors and maximal efficiency. The micro-controller unit is integrated with an LCD display which displays the signal along with its frequency and amplitude values.

**Please read the Technical Report included with each implementation for detailed information.**

## Motivation

The project was a top submission in multiple national design contests.
- Top 100 out of 1800 national proposals in [Texas Instruments Analog Design Contest 2014](http://youtu.be/NTonO6jmq0U). Implementation on TI MSP430 micro-controller.
- Top 50 out of 1000 national proposals in [Freescale Design Contest 2014](http://youtu.be/67Osx63GCeo). Implementation on FRDM-KL25Z micro-controller.

## Usage

The following files are included with each implementation:
- Schematic and PCB Layout
- Technical Report
- Source Code in in Embedded C/Arduino

#### Notes:
- For TI MSP430 implementation, the code was compiled and burned into micro-controller using Energia IDE.
- For FRDM-KL25Z implementation, the code was compiled and burned into micro-controller using mbed online platform.

## Contribute

Want to work on the project? Any kind of contribution is welcome!

Follow these steps:
- Fork the project.
- Create a new branch.
- Make your changes and write tests when practical.
- Commit your changes to the new branch.
- Send a pull request.

## License

[MIT License](https://github.com/ankitaggarwal011/InstrumentationOscilloscope/blob/master/LICENSE)