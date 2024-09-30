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

### Availability of Custom Driver for AVB Features on Windows
A custom driver is now available to support AVB features on Windows, including gPTP synchronization, priority queuing, and traffic shaping. This driver integrates with the existing AVTP and gPTP implementations in `AVTP/AVTP.cpp` and `gPTP/gPTP.cpp`.

### Installation Instructions for the Custom Driver
To install the custom driver, follow these steps:

1. Download the custom driver package from the repository.
2. Extract the package to a desired location.
3. Open Device Manager and locate the Intel i210 NIC.
4. Right-click on the device and select "Update driver".
5. Choose "Browse my computer for drivers" and navigate to the extracted driver package.
6. Follow the on-screen instructions to complete the installation.
7. Restart your computer to apply the changes.

### Integration of AVTP and gPTP Implementations with the Windows Driver for Intel i210
The current codebase includes AVTP and gPTP implementations in `AVTP/AVTP.cpp` and `gPTP/gPTP.cpp`, which are now integrated with the Windows driver for Intel i210. This integration ensures that AVTP frames are handled efficiently and gPTP synchronization is maintained accurately.

## Setting Up the Development Environment with Visual Studio and WDK

To set up the development environment for AVB on Windows, follow these steps:

1. **Install Visual Studio**: Ensure you have Visual Studio 2019 or 2022 installed with the necessary components like C++ development tools and networking libraries.
2. **Install Windows Driver Kit (WDK)**: Download and install the WDK for Visual Studio from [here](https://developer.microsoft.com/en-us/windows/hardware/windows-driver-kit). This is essential for working with network interface cards at the driver level.
3. **Create a new project**:
   - For user-space development, create a new Windows Desktop Application (C++) project.
   - For kernel-mode drivers, create a Kernel Mode Driver (KMDF) project.

## Porting and Integrating OpenAvnu Libraries

To port and integrate the OpenAvnu libraries for gPTP and AVTP, follow these steps:

1. **Port gPTP and AVTP libraries**:
   - Download the gPTP and AVTP libraries from the OpenAvnu project.
   - Refactor the code to work on Windows, using Windows-specific APIs like `QueryPerformanceCounter()` for timing and `Winsock` for low-level networking.
   - Integrate the ported libraries into your Visual Studio project.
2. **Modify the code**:
   - Update the `gPTP/gPTP.cpp` and `AVTP/AVTP.cpp` files to ensure compatibility with Windows.
   - Ensure the code uses appropriate Windows APIs and handles socket communication correctly.

## Developing and Testing the Custom Intel i210 Driver

To develop and test the custom Intel i210 driver for AVB, follow these steps:

1. **Develop the driver**:
   - Reference the Linux-based `igb_avb` driver for Intel i210 from SourceForge and port the necessary parts to Windows using WDK.
   - Extend or build a custom Intel i210 driver to enable AVB functionality on Windows.
   - Use the `Driver/i210AVBDriver.cpp` file as a starting point for your driver development.
2. **Test the driver**:
   - Set up a virtual AVB environment using AVB switches and endpoints to validate the driver and stack behavior.
   - Use Visual Studio’s debugging tools and WDK integrated tools for kernel-level debugging.

By following these steps, you can successfully prepare an AVB project for Visual Studio on Windows, targeting the Intel i210 NIC with AVB support.
