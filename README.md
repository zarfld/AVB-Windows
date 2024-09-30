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

## Using Intel's Resources for AVB Implementation

To assist with your project of implementing AVB (Audio Video Bridging) on Windows using the Intel i210 network adapter, several resources provided by Intel can be highly beneficial. The link you provided leads to Intel's developer tools and documentation, which include various tools, SDKs, and manuals that can aid in your development process. Here's a breakdown of the most relevant resources:

### **1. Intel® Ethernet Controller I210 Datasheet and Technical Documents**

- **Description**: Detailed technical specifications, hardware registers, operational modes, and features of the Intel i210 Ethernet controller.
- **Usage**: Essential for understanding the hardware capabilities and programming interfaces required to implement AVB features such as time synchronization, traffic shaping, and priority queuing.
- **How it Helps**:
  - Provides in-depth knowledge of the i210's AVB support, including IEEE 802.1AS (gPTP), IEEE 802.1Qav (Credit-Based Shaper), and IEEE 802.1Qat (SRP).
  - Offers guidance on configuring the device for precise timing and stream reservation.
- **Access**: Available on Intel's documentation site under Ethernet Products.
- **Link**: [Intel® Ethernet Controller I210 Datasheet](https://www.intel.com/content/www/us/en/products/sku/58954/intel-ethernet-controller-i210at/specifications.html)

### **2. Intel® Network Adapter Driver Development Kit (DDK)**

- **Description**: A development kit that provides source code for Intel's network drivers and utilities.
- **Usage**: Serves as a reference or starting point for developing or modifying drivers to enable AVB support on Windows.
- **How it Helps**:
  - Allows you to study existing driver implementations to understand how to interact with the i210 hardware.
  - Facilitates the development of a custom driver that supports AVB functionalities not present in the standard Windows driver.
- **Access**: May require an Intel account or special access; consider contacting Intel support for availability.

### **3. Intel® Ethernet Drivers and Software**

- **Description**: Precompiled drivers, software, and utilities for Intel Ethernet adapters.
- **Usage**: While standard Windows drivers may not support AVB, these resources can provide insight into driver installation, configuration, and management.
- **How it Helps**:
  - Understand the limitations and capabilities of the existing drivers.
  - Identify which components may need to be extended or replaced to support AVB.
- **Access**: Available on Intel's download center.
- **Link**: [Intel® Ethernet Adapter Complete Driver Pack](https://downloadcenter.intel.com/product/36773/Intel-Ethernet-Adapters)

### **4. Intel® Ethernet Controller I210 Software Developer Manual**

- **Description**: A comprehensive guide for developers programming the i210 controller.
- **Usage**: Offers detailed information on programming interfaces, hardware features, and implementation notes specific to the i210.
- **How it Helps**:
  - Provides necessary details for low-level programming of the controller, crucial for driver development.
  - Explains hardware features related to AVB, such as timestamping and queue management.
- **Access**: Available through Intel's documentation resources.

### **5. Intel® System Studio**

- **Description**: An integrated development environment (IDE) for system and embedded software.
- **Usage**: Includes tools for low-level system programming, debugging, and performance optimization.
- **How it Helps**:
  - Assists in developing, debugging, and optimizing your AVB stack and driver code.
  - Offers advanced analysis tools to troubleshoot timing and performance issues.
- **Access**: Free to download and use; may require registration.
- **Link**: [Intel® System Studio](https://www.intel.com/content/www/us/en/developer/tools/system-studio/overview.html)

### **6. Intel® VTune™ Profiler**

- **Description**: A performance analysis tool for serial and multithreaded applications.
- **Usage**: Helps identify performance bottlenecks in your code.
- **How it Helps**:
  - Optimize the performance of your AVB stack, ensuring minimal latency and jitter.
  - Analyze CPU and threading performance, which is critical for real-time audio/video streaming.
- **Access**: Available as part of Intel oneAPI toolkits.
- **Link**: [Intel® VTune™ Profiler](https://www.intel.com/content/www/us/en/developer/tools/oneapi/vtune-profiler.html)

### **7. Intel® Network Builders University**

- **Description**: An educational resource offering courses on Intel networking technologies.
- **Usage**: Provides training materials and courses that cover networking concepts, including AVB and time-sensitive networking (TSN).
- **How it Helps**:
  - Enhances understanding of networking technologies relevant to your project.
  - Offers best practices and design considerations for implementing AVB solutions.
- **Access**: Requires registration.
- **Link**: [Intel® Network Builders University](https://networkbuilders.intel.com/university)

### **8. Intel® Developer Zone Forums and Support**

- **Description**: Community forums where developers discuss Intel products and technologies.
- **Usage**: Seek advice, share knowledge, and troubleshoot issues with other developers and Intel engineers.
- **How it Helps**:
  - Obtain answers to specific technical questions.
  - Learn from others who have worked on similar projects.
- **Access**: Open to all; posting may require registration.
- **Link**: [Intel® Developer Zone Forums](https://community.intel.com/)

### **9. Intel® Software Development Tools Documentation**

- **Description**: Comprehensive documentation for all Intel software development tools.
- **Usage**: Reference manuals, user guides, and API documentation.
- **How it Helps**:
  - Provides detailed information on using Intel tools effectively.
  - Offers guidance on integrating Intel tools into your development workflow.
- **Access**: Available online.
- **Link**: [Intel® Developer Tools Documentation](https://www.intel.com/content/www/us/en/developer/tools/documentation.html)

## Setting Up GitHub Actions for CI

### Benefits of Continuous Integration (CI)

- **Automated Builds**: Automatically build your project whenever code is pushed.
- **Automated Testing**: Run unit tests to ensure new code doesn't break existing functionality.
- **Code Quality Analysis**: Integrate tools like linters and static code analyzers to enforce coding standards.
- **Continuous Feedback**: Get immediate feedback on code changes, facilitating faster iteration.
- **Collaboration**: Ensure that all team members are aware of the build and test status.

### GitHub Actions Workflow

To set up a CI pipeline using GitHub Actions, create a workflow file in the `.github/workflows/` directory. Here is an example configuration for a Visual Studio C++ project:

```yaml
name: CI

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main, develop ]

jobs:
  build:

    runs-on: windows-latest

    steps:
    - name: Checkout code
      uses: actions/checkout@v3

    - name: Setup Visual Studio
      uses: microsoft/setup-msbuild@v1

    - name: Setup NuGet
      uses: NuGet/setup-nuget@v1

    - name: Restore NuGet packages
      run: nuget restore AVB_Windows.sln

    - name: Build solution
      run: msbuild AVB_Windows.sln /p:Configuration=Release

    - name: Run Unit Tests
      run: |
        vstest.console.exe Path\To\Your\TestProject.dll

    - name: Run PVS-Studio Analysis
      run: |
        # Install PVS-Studio
        choco install pvs-studio

        # Run analysis
        "C:\Program Files (x86)\PVS-Studio\PVS-Studio_Cmd.exe" \
          --target "AVB_Windows.sln" \
          --configuration "Release" \
          --output "PVS-Studio.log"

    - name: Check Code Formatting
      run: |
        choco install llvm

        clang-format -i -style=file **/*.cpp **/*.h

        git diff --exit-code
```

For more details, refer to the [ci.yml](.github/workflows/ci.yml) file in the repository.
