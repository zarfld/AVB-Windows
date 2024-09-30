# Software Requirements Specification (SRS)

## Table of Contents

1. **Introduction**
   - 1.1 Purpose
   - 1.2 Scope
   - 1.3 Definitions, Acronyms, and Abbreviations
   - 1.4 References
   - 1.5 Overview

2. **Overall Description**
   - 2.1 Product Perspective
   - 2.2 Product Functions
   - 2.3 User Characteristics
   - 2.4 Constraints
   - 2.5 Assumptions and Dependencies

3. **Specific Requirements**
   - 3.1 Functional Requirements
   - 3.2 Non-Functional Requirements
   - 3.3 External Interface Requirements
   - 3.4 System Features
   - 3.5 Performance Requirements
   - 3.6 Design Constraints
   - 3.7 Security Requirements

4. **Appendices**
   - A. Glossary
   - B. Analysis Models
   - C. Issues and TBDs

---

## 1. Introduction

### 1.1 Purpose

The purpose of this Software Requirements Specification (SRS) is to define the requirements for the **AVB (Audio Video Bridging) Stack Implementation for Windows** using the **Intel i210 Network Interface Card (NIC)**. This project aims to develop a Windows-based AVB solution prepared for Visual Studio, enabling the use of AVB protocols on Windows 10 platforms with Intel i210 hardware.

### 1.2 Scope

The project involves:

- Developing a Windows-compatible AVB stack, including gPTP (IEEE 802.1AS), AVTP (IEEE 1722), and AVDECC (IEEE 1722.1) protocols.
- Porting and adapting existing open-source AVB components (from OpenAvnu and avdecc-lib) to Windows.
- Implementing or extending the Intel i210 Windows driver to support AVB functionalities.
- Providing a Visual Studio solution for ease of development and collaboration.
- Ensuring compatibility with existing AVB networks and devices.

### 1.3 Definitions, Acronyms, and Abbreviations

- **AVB**: Audio Video Bridging
- **AVTP**: Audio Video Transport Protocol (IEEE 1722)
- **gPTP**: Generalized Precision Time Protocol (IEEE 802.1AS)
- **AVDECC**: AV Device Discovery, Enumeration, Connection management, and Control Protocol (IEEE 1722.1)
- **NIC**: Network Interface Card
- **Intel i210**: An Ethernet controller with AVB support
- **WDK**: Windows Driver Kit
- **SRS**: Software Requirements Specification

### 1.4 References

- **IEEE Standards**:
  - IEEE 802.1AS (gPTP): [IEEE 802.1AS-2020](https://standards.ieee.org/standard/802_1AS-2020.html)
  - IEEE 1722 (AVTP): [IEEE 1722-2016](https://standards.ieee.org/standard/1722-2016.html)
  - IEEE 1722.1 (AVDECC): [IEEE 1722.1-2013](https://standards.ieee.org/standard/1722_1-2013.html)
- **Intel i210 Datasheet**: [Intel i210 Datasheet](https://www.intel.com/content/www/us/en/embedded/products/networking/ethernet-controller-i210-family-datasheet.html)
- **OpenAvnu Project**: [OpenAvnu on GitHub](https://github.com/AVnu/OpenAvnu)
- **avdecc-lib Project**: [avdecc-lib on GitHub](https://github.com/audioscience/avdecc-lib)
- **Windows Driver Kit (WDK)**: [WDK Documentation](https://docs.microsoft.com/en-us/windows-hardware/drivers/)

### 1.5 Overview

This SRS provides a detailed description of the software requirements. Section 2 gives an overall description of the product, while Section 3 specifies the detailed requirements.

---

## 2. Overall Description

### 2.1 Product Perspective

The AVB Stack Implementation for Windows is an open-source project aimed at enabling AVB functionalities on Windows platforms using Intel i210 NICs. It builds upon existing open-source projects (OpenAvnu, avdecc-lib) by porting and adapting them to work on Windows. The product will provide developers and users with the tools necessary to participate in AVB networks using Windows machines.

### 2.2 Product Functions

- **AVB Protocol Stack Implementation**:
  - **gPTP (IEEE 802.1AS)**: Time synchronization between devices.
  - **AVTP (IEEE 1722)**: Streaming of audio/video data over Ethernet.
  - **AVDECC (IEEE 1722.1)**: Device discovery, enumeration, and control.

- **Driver Support**:
  - Development of a Windows driver for the Intel i210 that supports AVB features.
  - Integration with the Windows networking stack.

- **Development Environment**:
  - A Visual Studio solution with projects for each component.
  - Scripts and tools for building and testing.

- **User Tools**:
  - Command-line or GUI-based tools for configuring and monitoring AVB functionalities.

### 2.3 User Characteristics

- **Developers**:
  - Familiar with C/C++ programming.
  - Experience with Windows development and Visual Studio.
  - Understanding of networking protocols and driver development is beneficial.

- **End Users**:
  - Users who require AVB functionalities on Windows platforms.
  - May include audio/video professionals, system integrators, and network engineers.

### 2.4 Constraints

- **Operating System**: Windows 10 (64-bit)
- **Hardware**: Intel i210 NIC
- **Development Tools**: Visual Studio 2019/2022, Windows Driver Kit (WDK)
- **Licensing**: Compliance with open-source licenses from OpenAvnu and avdecc-lib.
- **Compliance**: Must adhere to relevant IEEE standards for AVB.

### 2.5 Assumptions and Dependencies

- The Intel i210 NIC is properly installed and functioning on the Windows system.
- Users have administrative privileges required for driver installation and network configuration.
- The project will leverage existing open-source code where possible, requiring adaptation to Windows.
- The AVB network environment (switches, endpoints) is compliant with IEEE standards.

---

## 3. Specific Requirements

### 3.1 Functional Requirements

#### 3.1.1 gPTP (IEEE 802.1AS) Implementation

- **FR-1**: The system shall provide a gPTP daemon that synchronizes the local clock with the AVB network clock.
- **FR-2**: The gPTP implementation shall interface with the Intel i210 hardware timestamping capabilities.
- **FR-3**: The system shall allow configuration of gPTP parameters (e.g., priority, clock class).

#### 3.1.2 AVTP (IEEE 1722) Support

- **FR-4**: The system shall implement the AVTP stack for transmitting and receiving audio/video streams.
- **FR-5**: The AVTP implementation shall support encapsulation and de-encapsulation of AVB streams according to IEEE 1722.
- **FR-6**: The system shall handle stream identification, sequence numbers, and timestamps.

#### 3.1.3 AVDECC (IEEE 1722.1) Controller

- **FR-7**: The system shall include an AVDECC controller for device discovery and management.
- **FR-8**: The controller shall allow users to enumerate devices on the AVB network.
- **FR-9**: The system shall support connection management and control of AVB devices.

#### 3.1.4 Intel i210 Driver Support

- **FR-10**: The system shall provide a Windows driver for the Intel i210 that enables AVB functionalities.
- **FR-11**: The driver shall support priority-based queuing and traffic shaping for AVB streams.
- **FR-12**: The driver shall interface with the Windows networking stack and provide necessary hooks for the AVB protocols.

#### 3.1.5 User Interface

- **FR-13**: The system shall provide command-line tools for configuration and monitoring.
- **FR-14**: Optionally, the system may provide a GUI for ease of use.

#### 3.1.6 Configuration and Logging

- **FR-15**: The system shall allow configuration of AVB parameters via configuration files or command-line options.
- **FR-16**: The system shall log events and errors for troubleshooting purposes.

### 3.2 Non-Functional Requirements

#### 3.2.1 Performance

- **NFR-1**: The system shall achieve time synchronization accuracy within the limits specified by IEEE 802.1AS.
- **NFR-2**: The system shall handle AVTP streams with minimal latency and jitter appropriate for professional audio/video applications.
- **NFR-3**: The driver and protocol stack shall be optimized for performance on Windows.

#### 3.2.2 Reliability

- **NFR-4**: The system shall operate continuously without crashes or memory leaks.
- **NFR-5**: The system shall handle network disruptions gracefully and recover automatically.

#### 3.2.3 Usability

- **NFR-6**: The system shall be easy to set up and configure for developers and end-users.
- **NFR-7**: Documentation shall be provided for installation, configuration, and usage.

#### 3.2.4 Portability

- **NFR-8**: The code shall be portable across Windows 10 versions and compatible with future Windows releases where possible.

### 3.3 External Interface Requirements

#### 3.3.1 User Interfaces

- **Command-Line Interface**: Tools for configuring gPTP, AVTP, and AVDECC functionalities.
- **Graphical User Interface** (optional): A GUI application for monitoring and managing AVB devices and streams.

#### 3.3.2 Hardware Interfaces

- **Intel i210 NIC**: Direct interaction with the NIC for timestamping, traffic shaping, and priority queuing.

#### 3.3.3 Software Interfaces

- **Windows Networking Stack**: Integration with Winsock APIs for network communication.
- **Windows Driver Framework (WDF)**: For driver development and interaction with hardware.

#### 3.3.4 Communications Interfaces

- **Ethernet**: Support for standard Ethernet communication with AVB extensions.
- **AVB Protocols**: Compliance with IEEE 802.1AS, IEEE 1722, and IEEE 1722.1.

### 3.4 System Features

#### 3.4.1 Time Synchronization (gPTP)

- **Feature Description**: Synchronizes system clock with the network clock to enable time-sensitive communication.
- **Requirements Addressed**: FR-1, FR-2, FR-3

#### 3.4.2 Audio/Video Streaming (AVTP)

- **Feature Description**: Supports streaming of audio and video data over the network with minimal latency.
- **Requirements Addressed**: FR-4, FR-5, FR-6

#### 3.4.3 Device Management (AVDECC)

- **Feature Description**: Discovers and manages AVB devices on the network.
- **Requirements Addressed**: FR-7, FR-8, FR-9

#### 3.4.4 Driver Support

- **Feature Description**: Provides necessary driver support for the Intel i210 NIC to enable AVB features.
- **Requirements Addressed**: FR-10, FR-11, FR-12

### 3.5 Performance Requirements

- **PR-1**: Time synchronization accuracy shall be within ±500 nanoseconds as per IEEE 802.1AS.
- **PR-2**: The system shall support audio streaming at standard professional audio sample rates (e.g., 48 kHz, 96 kHz) with minimal latency.
- **PR-3**: The system shall support multiple simultaneous AVTP streams without degradation of performance.

### 3.6 Design Constraints

- **DC-1**: The system must comply with relevant IEEE AVB standards.
- **DC-2**: The driver must be developed using the Windows Driver Kit and adhere to Microsoft's driver development guidelines.
- **DC-3**: The project must use Visual Studio for development to facilitate collaboration.

### 3.7 Security Requirements

- **SR-1**: The system shall prevent unauthorized access to AVB device controls.
- **SR-2**: The driver and applications shall run with the minimum required privileges.
- **SR-3**: The system shall validate all network inputs to prevent buffer overflows and other common vulnerabilities.

---

## 4. Appendices

### A. Glossary

- **AVB**: A set of technical standards that ensure audio and video streams are delivered over Ethernet networks with high quality of service.
- **gPTP**: A protocol for synchronizing clocks throughout a computer network.
- **AVTP**: Protocol that defines the encapsulation of audio and video data for transmission over AVB networks.
- **AVDECC**: Protocol for device discovery, enumeration, connection management, and control on AVB networks.
- **Intel i210**: An Ethernet controller by Intel that supports AVB features at the hardware level.

### B. Analysis Models

- **Use Case Diagrams**: Depicting interactions between users and the system.
- **Sequence Diagrams**: Illustrating the sequence of operations for key functionalities like streaming and synchronization.
- **Class Diagrams**: Showing the structure of the software components.

### C. Issues and TBDs

- **C-1**: Determination of licensing compatibility with OpenAvnu and avdecc-lib when ported to Windows.
- **C-2**: Evaluation of the need for a GUI application based on user feedback.
- **C-3**: Testing on various hardware configurations to ensure broad compatibility.

---

**End of Software Requirements Specification**
