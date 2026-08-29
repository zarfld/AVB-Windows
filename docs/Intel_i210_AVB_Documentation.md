# Intel i210 AVB Documentation

## Overview

This document provides detailed information on the AVB (Audio Video Bridging) functionality, configuration, and usage specific to Intel i210 Ethernet adapters.

## AVB Functionality

### Generalized Precision Time Protocol (gPTP)
gPTP ensures time synchronization between AVB devices. The Intel i210 supports gPTP, which is essential for maintaining precise timing across the network.

### Audio Video Transport Protocol (AVTP)
AVTP handles the streaming of audio and video data over AVB networks. The Intel i210 supports AVTP, enabling real-time transmission of multimedia content.

### AV Device Enumeration, Discovery, Connection Management (AVDECC)
AVDECC manages and controls devices on the AVB network. The Intel i210 supports AVDECC, allowing for the enumeration and management of AVB streams.

## Configuration

### Custom Driver Installation
To enable AVB functionality on the Intel i210, a custom driver must be installed. Follow these steps:

1. Download the custom driver package from the repository.
2. Extract the package to a desired location.
3. Open Device Manager and locate the Intel i210 NIC.
4. Right-click on the device and select "Update driver".
5. Choose "Browse my computer for drivers" and navigate to the extracted driver package.
6. Follow the on-screen instructions to complete the installation.
7. Restart your computer to apply the changes.

### Time Synchronization Configuration
To configure gPTP for time synchronization, follow these steps:

1. Ensure the custom driver is installed and the Intel i210 NIC is properly configured.
2. Download and run the gPTP daemon from the repository.
3. Monitor the synchronization status using the provided tools.

### Stream Configuration
To configure AVTP streams, follow these steps:

1. Ensure the custom driver is installed and the Intel i210 NIC is properly configured.
2. Use the provided AVBTool to create and manage AVTP streams.
3. Monitor the stream status and adjust settings as needed.

## Usage

### Best Practices
- Ensure all AVB devices on the network support gPTP for accurate time synchronization.
- Use high-quality network cables and switches to minimize latency and packet loss.
- Regularly monitor the network status and adjust configurations as needed.

### Examples
- Example 1: Configuring a gPTP daemon for time synchronization.
- Example 2: Creating and managing AVTP streams using AVBTool.
- Example 3: Enumerating and managing AVB devices using AVDECC.

## Relevant Resources

- [Intel i210 Ethernet Controller Datasheet](https://www.intel.com/content/www/us/en/ethernet-products/controllers/i210-ethernet-controller-datasheet.html)
- [Intel igb_avb Driver on SourceForge](https://sourceforge.net/projects/e1000/files/igb%20avb%20driver/)
- [Intel Ethernet Products Documentation](https://www.intel.com/content/www/us/en/ethernet-products/ethernet-products-documentation.html)
- [Intel Community Discussion on AVB](https://community.intel.com/t5/Ethernet-Products/AVB/td-p/)

These resources provide comprehensive information on how Intel Ethernet adapters, particularly the i210, can be configured and used for AVB. However, most of the detailed support is available for Linux, and as mentioned earlier, AVB support on Windows requires third-party software or modifications.

## Detailed Instructions for Installing and Configuring the Custom AVB Driver on Windows

### Installing the Custom AVB Driver

1. Download the custom AVB driver package from the repository.
2. Extract the package to a desired location.
3. Open Device Manager and locate the Intel i210 NIC.
4. Right-click on the device and select "Update driver".
5. Choose "Browse my computer for drivers" and navigate to the extracted driver package.
6. Follow the on-screen instructions to complete the installation.
7. Restart your computer to apply the changes.

### Configuring gPTP Synchronization

1. Ensure the custom driver is installed and the Intel i210 NIC is properly configured.
2. Download and run the gPTP daemon from the repository.
3. Monitor the synchronization status using the provided tools.

### Configuring Priority Queuing

1. Ensure the custom driver is installed and the Intel i210 NIC is properly configured.
2. Use the provided AVBTool to configure priority queuing for AVTP streams.
3. Monitor the stream status and adjust settings as needed.

### Configuring Traffic Shaping

1. Ensure the custom driver is installed and the Intel i210 NIC is properly configured.
2. Use the provided AVBTool to configure traffic shaping for AVTP streams.
3. Monitor the stream status and adjust settings as needed.

## Integrating Code Quality Tools in the CI Pipeline

To ensure code quality, integrate tools like static analyzers, linters, and code formatters into your CI pipeline.

### Static Code Analysis with PVS-Studio

PVS-Studio is a static code analyzer for C, C++, C#, and Java. It can be integrated into your CI pipeline to detect potential errors.

Example Step:

```yaml
    - name: Run PVS-Studio Analysis
      run: |
        # Install PVS-Studio
        choco install pvs-studio

        # Run analysis
        "C:\Program Files (x86)\PVS-Studio\PVS-Studio_Cmd.exe" \
          --target "AVB_Windows.sln" \
          --configuration "Release" \
          --output "PVS-Studio.log"
```

### Code Formatting with Clang-Format

Use Clang-Format to enforce consistent code style.

Example Step:

```yaml
    - name: Check Code Formatting
      run: |
        choco install llvm

        clang-format -i -style=file **/*.cpp **/*.h

        git diff --exit-code
```

If there are formatting differences, the git diff command will exit with a non-zero status, causing the build to fail.

### Updating the CI Pipeline for KMDF Versions

To ensure compatibility with the appropriate Windows versions, update the CI pipeline to use KMDF 1.31 for Windows 10 and KMDF 1.33 for Windows 11. Follow these steps:

1. **Update the `build-windows-7` Job**:
   - Modify the `build-windows-7` job in the `.github/workflows/ci.yml` file to target Windows 10 and Windows 11 instead of Windows 7.
   - Ensure that the `WDK_IncludePath` environment variable is set correctly for each Windows version.

2. **Modify the `build-windows-10` Job**:
   - Specify the correct KMDF version (KMDF 1.31) for Windows 10 in the `.github/workflows/ci.yml` file.

3. **Modify the `build-windows-11` Job**:
   - Specify the correct KMDF version (KMDF 1.33) for Windows 11 in the `.github/workflows/ci.yml` file.

4. **Verify KMDF Installation**:
   - Update the `scripts/verify_wdk_installation.sh` script to verify the installation of KMDF 1.31 for Windows 10 and KMDF 1.33 for Windows 11.

By following these steps, you can ensure that the CI pipeline is updated to use the correct KMDF versions for Windows 10 and Windows 11, ensuring compatibility and successful builds.

## Setting Up Branch Protection Rules and Pull Request Reviews

### Setting Up Branch Protection Rules

- Go to your GitHub repository settings.
- Under Branches, set up protection rules for main and develop branches.
- Require status checks to pass before merging.
  - Include checks like build success, unit tests passing, code analysis results.

### Pull Request Reviews

- Enforce code reviews for all pull requests.
- Use GitHub CODEOWNERS file to specify code reviewers.

CODEOWNERS Example (.github/CODEOWNERS):

```
# Define code owners
*       @yourusername
```

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

## Additional Notes

- **License and Usage Agreements**: Some tools and documentation may have licensing restrictions or require you to accept end-user license agreements (EULAs). Ensure you comply with all terms when using Intel's resources.

- **Contact Intel Support**: For specific inquiries or to gain access to certain development kits or confidential information, consider contacting Intel directly. They may provide additional resources or guidance tailored to your project.

- **Stay Updated**: Intel regularly updates their tools and documentation. Make sure to use the latest versions to benefit from recent improvements and fixes.

## How These Resources Aid Your Project

By leveraging Intel's documentation and tools, you can gain a deeper understanding of the Intel i210's capabilities and how to program it for AVB functionalities. The driver development kits and software manuals are particularly valuable for developing or modifying a Windows driver that supports AVB features, which is one of the critical components missing in the standard Windows environment.

Additionally, performance analysis tools like Intel® VTune™ Profiler can help optimize your implementation to meet the strict timing requirements of AVB protocols. Educational resources and community forums offer avenues to expand your knowledge and solve complex problems with the help of other experienced developers.

## Next Steps

1. **Download and Review Documentation**: Start by downloading the datasheets and developer manuals for the Intel i210 to familiarize yourself with the hardware.

2. **Set Up Development Tools**: Install Intel® System Studio and other relevant tools to prepare your development environment.

3. **Access Driver Development Kits**: If possible, obtain the Intel® Network Adapter Driver Development Kit to use as a reference for your driver development.

4. **Engage with the Community**: Join Intel's developer forums to seek advice and share progress with others working on similar projects.

5. **Plan Driver Development**: Use the insights gained from the documentation to plan the development or modification of a Windows driver that enables AVB support on the Intel i210.

6. **Implement and Test**: Begin coding, utilizing Intel's tools for debugging and performance analysis, and test your implementation in an AVB network environment.

By utilizing these Intel-provided resources, you can significantly accelerate your development process and overcome some of the challenges associated with implementing AVB support on Windows using the Intel i210 network adapter.

## Summary of Key Insights from References

### Understanding IEEE 1722 - AVTP Explained

- **URL**: [IEEE 1722 - AVTP Explained](https://www.ieee802.org/1/files/public/docs2009/avb-rboatright-p1722-explained-0903.pdf)
- **Description**: An in-depth explanation of the IEEE 1722 standard, providing insights into the AVTP.
- **Key Insights**:
  - Detailed explanation of AVTP packet formats.
  - Synchronization mechanisms for AVTP streams.
  - Media clock recovery techniques.

### AVnu Alliance - Audio Video Transport Protocol (AVTP) Overview by Dave Olsen

- **URL**: [AVTP Overview by Dave Olsen](https://avnu.org/wp-content/uploads/2014/05/AVnu-AAA2C_Audio-Video-Transport-Protocol-AVTP_Dave-Olsen.pdf)
- **Description**: A presentation detailing the AVTP, its applications, and implementation considerations.
- **Key Insights**:
  - Applications of AVTP in professional audio/video environments.
  - Implementation considerations for AVTP on different platforms.

### AVnu Alliance - IEEE 1722 Media on AVB Networks by Rob Silfvast

- **URL**: [IEEE 1722 Media on AVB Networks](https://avnu.org/wp-content/uploads/2014/05/AVnu-AABAC_IEEE-1722-Media-on-AVB-Networks_Rob-Silfvast.pdf)
- **Description**: Discusses the transport of media using IEEE 1722 over AVB networks, highlighting key aspects of implementation.
- **Key Insights**:
  - Transport of media using IEEE 1722 over AVB networks.
  - Key aspects of implementing AVTP for media transport.

### ResearchGate: IEEE 1722 AVTP Figure

- **URL**: [IEEE 1722 AVTP Diagram](https://www.researchgate.net/figure/IEEE-1722-Audio-Video-Transport-Protocol-AVTP_fig5_262323002)
- **Description**: Provides visual diagrams and explanations of AVTP structures and packet formats.
- **Key Insights**:
  - Visual diagrams of AVTP structures.
  - Explanations of AVTP packet formats.

## Critical Requirements and Challenges Identified

### Critical Requirements

- **AVTP Packet Formats**: The system must support specific AVTP packet formats as defined in IEEE 1722.
- **Synchronization Mechanisms**: The system must implement synchronization mechanisms for AVTP streams.
- **Media Clock Recovery**: The system must support media clock recovery techniques for AVTP streams.
- **Performance Metrics**: The system must meet performance metrics as defined in the project documentation.
- **Latency Considerations**: The system must consider latency requirements for AVTP streams.
- **Compliance**: The system must comply with relevant AVB standards and specifications.

### Challenges

- **Driver Development**: Developing a custom driver for the Intel i210 NIC to support AVB features on Windows.
- **Porting Open Source Code**: Adapting existing open-source AVB components to work on Windows.
- **Performance Optimization**: Ensuring the AVB stack and driver are optimized for performance on Windows.
- **Testing and Validation**: Building test environments to ensure compatibility and functionality with AVB networks and devices.

## New Driver Project and Abstraction Layer

### New Driver Project for Target NIC

To support AVB features for other NICs, a new driver project has been added. This project includes the necessary modifications to support AVB functionalities such as gPTP, AVTP, and AVDECC.

### Abstraction Layer for NIC-Specific Code

An abstraction layer has been created to separate NIC-specific code from the AVBStreamHandler core functionality. This makes it easier to support multiple NICs.

### Refactoring Existing Code

The existing code in `AVDECC/AVDECC.cpp`, `AVTP/AVTP.cpp`, and `gPTP/gPTP.cpp` has been refactored to use the abstraction layer. This ensures that the AVBStreamHandler components can work with different NICs by implementing the necessary functions defined in the abstraction layer.

### Implementing NIC-Specific Modules

Separate modules have been developed for each NIC, implementing the necessary functions defined in the abstraction layer. This allows the AVBStreamHandler to support multiple NICs seamlessly.

### Updating the Build Process

The build scripts and `AVB_Windows.sln` file have been updated to include the new abstraction layer and NIC-specific modules. This ensures that the new driver project and abstraction layer are part of the build process.

### Testing and Validation

Ensure that the integrated components work correctly by running tests and validating the functionality. Use the provided test scripts and tools, such as `scripts/verify_wdk_installation.sh` and `scripts/verify_kmdf_installation.sh`.

By following these steps, you can successfully integrate AVBStreamHandler with your current project and leverage its AVB functionalities for multiple NICs.
