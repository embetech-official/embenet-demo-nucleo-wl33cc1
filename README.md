# embeNET Demo for NUCLEO-WL33CC1 board

## What's inside ?

This repository contains an exemplary project demonstrating the use of embeNET Suite on [NUCLEO-WL33CC1](https://www.st.com/en/evaluation-tools/nucleo-wl33cc1.html) evaluation boards. 
The project is designed for the [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html). 

## What's included ?

The demo includes the following components of the embeNET Suite:
- The embeNET Node library in demo mode, providing IPv6 wireless mesh networking connectivity
- A port of the embeNET Node for the STM32WL3 chip
- embeNET Node Management Service (ENMS) providing telemetry services
- MQTT-SN client

## What are the demo version limitations ?

The demo *can only be used for evaluation purposes* (see LICENSE.txt for details).
The demo is limited to 10 nodes only (including root node).

## What you'll need to run the demo

- PC with Windows
- One Nucleo-WL33CC1 board connected to the PC (via USB cable) that will act as the root of the network
- At least one more (up to 9) Nucleo-WL33CC1 boards that will act as the network nodes
- [embeNET demo package for Nucleo-WL33CC1](https://github.com/embetech-official/embenet-demo-nucleo-wl33cc1/releases)
- STM32CubeIDE, available for download from [the official ST site](https://www.st.com/en/development-tools/stm32cubeide.html) (for this demo version 1.17.0 was used)
- (optional)STM32CubeProgrammer available for download from [the official ST site](https://www.st.com/en/development-tools/stm32cubeprog.html)
- (optional)Any serial port terminal, for example [ExtraPutty](https://sourceforge.net/projects/extraputty), to view the logs. You can also use a [built-in terminal in CubeIDE](https://community.st.com/t5/stm32-mcus/how-to-use-the-stm32cubeide-terminal-to-send-and-receive-data/ta-p/49434).

Optionally, to play with the MQTT-SN demo service you'll need:
- Any MQTT-SN Gateway: we recommend the HiveMQ Edge, available for download from [the official HiveMQ page](https://www.hivemq.com/products/hivemq-edge)
- Any MQTT Client: we recommend the MQTT Client Toolbox from MQTTX, available for download from [the official MQTTX page](https://mqttx.app)

Optionally, to easily interact with the custom UDP service you'll need
- [UDP - Sender/Reciever app from Microsoft Store](https://www.microsoft.com/store/apps/9nblggh52bt0)

## How to start?

Read the ['Getting started with embeNET demo for NUCLEO-WL33CC1 board'](https://embe.net/docs/?q=doxyview/Getting%20started%20with%20Nucleo-WL33CC1/index.html) tutorial.

## What can I do to adapt this to my board?

The demo consists of closed-source core embeNET network components and open source port (driver) for STM32WL. The port is released using Apache License Version 2.0. You can modify and extend the port to your needs.