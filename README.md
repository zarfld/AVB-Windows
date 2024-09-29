# AVB Functionality on Windows 10 using Intel i210

This document provides detailed instructions on how to set up and use the AVB (Audio Video Bridging) functionality on Windows 10 using an Intel i210 NIC.

## Components

### gPTP (Generalized Precision Time Protocol)
gPTP ensures time synchronization between AVB devices. The gPTP daemon has been ported from the OpenAvnu repository to Windows and refactored for compatibility with Windows timing APIs and network interfaces.

### AVTP (Audio Video Transport Protocol)
AVTP handles streaming of audio and video data over AVB networks. It has been integrated into the Windows networking stack, and a user-space or kernel-space driver has been developed to capture and process AVB-specific Ethernet frames.

### AVDECC (AV Device Enumeration, Discovery, Connection Management)
AVDECC manages and controls devices on the AVB network. An AVDECC controller has been developed for Windows, enabling enumeration and management of AVB streams.

## Installation and Configuration

### Custom Driver for Intel i210 NIC
A custom driver has been developed to support AVB-specific features such as gPTP clock synchronization and real-time streaming capabilities. Follow these steps to install and configure the driver:

1. Download the custom driver package from the repository.
2. Extract the package to a desired location.
3. Open Device Manager and locate the Intel i210 NIC.
4. Right-click on the device and select "Update driver".
5. Choose "Browse my computer for drivers" and navigate to the extracted driver package.
6. Follow the on-screen instructions to complete the installation.
7. Restart your computer to apply the changes.

For detailed AVB-specific documentation, please refer to the [Intel i210 AVB Documentation](docs/Intel_i210_AVB_Documentation.md).

### GUI-based Tool for AVB Configuration and Monitoring
A GUI-based tool has been developed to configure and monitor AVB streams, devices, and time synchronization. Follow these steps to use the tool:

1. Download the AVBTool package from the repository.
2. Extract the package to a desired location.
3. Run the `AVBTool.exe` executable.
4. Use the user-friendly interface to manage your AVB network, configure streams, and monitor time synchronization.

## AVTP and gPTP Stack Porting from OpenAvnu to Windows
The AVTP and gPTP stacks have been ported from the OpenAvnu project to Windows. This porting process involved adapting the code to work with Windows-specific APIs and network interfaces. The AVTP stack is responsible for handling the transport of audio and video data over AVB networks, while the gPTP stack ensures precise time synchronization between AVB devices.

## Suggested Steps for Development

1. Research Existing AVB Projects: Start by reviewing OpenAvnu for reference implementations of gPTP and AVTP on Linux.
2. Port Core Components: Adapt gPTP and AVTP components to work on Windows. Focus on using Windows real-time network APIs and time synchronization features.
3. Develop Driver Extensions: Work with Windows Driver Framework (WDF) to modify or extend the i210 driver to support AVB.
4. Testing & Validation: Build test environments with AVB switches and endpoints to ensure compatibility and functionality with the newly developed stack.

This project bridges the current gap in Windows AVB support, enabling the use of Intel i210 NICs for professional audio/video streaming over an AVB network.
