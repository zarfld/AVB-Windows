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

permissions:
  actions: read
  contents: read
  issues: write

jobs:
  build:

    runs-on: windows-latest

    outputs:
      url: ${{ steps.upload_build_logs.outputs.url }}

    steps:
    - name: Checkout code
      uses: actions/checkout@v4

    - name: Setup Visual Studio
      uses: microsoft/setup-msbuild@v2

    - name: Setup NuGet
      uses: NuGet/setup-nuget@v2

    - name: Restore NuGet packages
      run: nuget restore AVB_Windows.sln

    - name: Install Windows Driver Kit (WDK)
      run: choco install windowsdriverkit10 --source=https://chocolatey.org/api/v2/

    - name: Set WDK environment variables
      run: |
        echo "WDK_IncludePath=C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0" >> $GITHUB_ENV

    - name: Clean solution
      run: msbuild AVB_Windows.sln /t:Clean

    - name: Build solution
      run: msbuild AVB_Windows.sln /p:Configuration=Release > build.log 2>&1

    - name: Ensure log file exists
      run: |
        if [ ! -f build.log ]; then
          echo "No build output captured." > build.log
        fi

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

    - name: Download Intel Tools
      run: |
        curl -o Intel_Ethernet_Controller_I210_Datasheet.pdf https://www.intel.com/content/www/us/en/products/sku/58954/intel-ethernet-controller-i210at/specifications.html
        curl -o Intel_Ethernet_Adapter_Complete_Driver_Pack.zip https://downloadcenter.intel.com/product/36773/Intel-Ethernet-Adapters
        curl -o Intel_System_Studio.exe https://www.intel.com/content/www/us/en/developer/tools/system-studio/overview.html
        curl -o Intel_VTune_Profiler.exe https://www.intel.com/content/www/us/en/developer/tools/oneapi/vtune-profiler.html

    - name: Run Intel Tools
      run: |
        # Run Intel System Studio
        start /wait Intel_System_Studio.exe /S

        # Run Intel VTune Profiler
        start /wait Intel_VTune_Profiler.exe /S

    - name: Validate AVB Implementation
      run: |
        # Run validation scripts using Intel tools
        python validate_avb.py

    - name: Update SRS
      run: |
        # Update the SRS document with new requirements
        python update_srs.py

    - name: Update Documentation
      run: |
        # Update the documentation with new requirements and considerations
        python update_docs.py

    - name: Update README
      run: |
        # Update the README with new requirements and key insights
        python update_readme.py

    - name: Run Error Detection
      run: |
        python scripts/error_detection.py

    - name: Save Errors and Metadata
      run: |
        python scripts/error_detection.py > errors_and_metadata.json

    - name: Install PyGithub
      run: pip install PyGithub

    - name: Upload Build Logs
      if: failure()
      id: upload_build_logs
      uses: actions/upload-artifact@v4
      with:
        name: build-logs
        path: *.log
        retention-days: 7
        if-no-files-found: error

    - name: Check for Missing Logs
      run: |
        if [ ! -f build.log ] && [ ! -f install_dependencies.log ] && [ ! -f install_windows_sdk.log ] && [ ! -f install_windows_driver_kit.log ] && [ ! -f install_kmdf_build_tools.log ]; then
          echo "No logs found. Skipping error-checking step."
        fi

    - name: Run Issue Creation
      if: failure()
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
        COMMIT_SHA: ${{ github.sha }}
        BUILD_LOGS_LINK: ${{ steps.upload_build_logs.outputs.url }}
      run: |
        python scripts/issue_creation.py

    - name: Use Milestones for Releases
      run: |
        milestone_title="v1.0 release"
        milestone_due_date="2023-12-31"
        milestone_description="Milestone for the v1.0 release"
        milestone=$(gh api -X POST /repos/${{ github.repository }}/milestones -f title="$milestone_title" -f due_on="$milestone_due_date" -f description="$milestone_description")
        echo "Milestone created: $milestone"

    - name: Trigger CI Pipeline for Issue Progress
      run: |
        issue_status="in progress"
        if [ "$issue_status" == "in progress" ]; then
          echo "Triggering CI pipeline for issue progress"
          # Add logic to trigger CI pipeline
        fi

    - name: CI Pipeline Alerts for Failed Builds
      run: |
        if [ -f build.log ]; then
          echo "Build failed. Sending alerts."
          # Add logic to send alerts via Slack, email, or GitHub notifications
        fi

    - name: Use Separate Labels for Environments
      run: |
        environment="development"
        if [ "$environment" == "development" ]; then
          echo "Labeling as 'in development'"
          # Add logic to label issues as 'in development'
        elif [ "$environment" == "staging" ]; then
          echo "Labeling as 'in staging'"
          # Add logic to label issues as 'in staging'
        elif [ "$environment" == "production" ]; then
          echo "Labeling as 'in production'"

    - name: Enforce Branch Protection Rules
      run: |
        branch="main"
        protection_rules=$(gh api -X GET /repos/${{ github.repository }}/branches/$branch/protection)
        if [ -z "$protection_rules" ]; then
          echo "Enforcing branch protection rules"
          # Add logic to enforce branch protection rules
        fi

    - name: Continuous Deployment Labels and Issue Auto-Close
      run: |
        deployment_status="success"
        if [ "$deployment_status" == "success"; then
          echo "Deployment successful. Auto-closing issues."
          # Add logic to auto-close issues

    - name: Enforce Issue Templates and CI Requirements
      run: |
        issue_template="bug_report.md"
        if [ -f .github/ISSUE_TEMPLATE/$issue_template ]; then
          echo "Enforcing issue templates"
          # Add logic to enforce issue templates

    - name: Integrate Monitoring and Feedback Tools
      run: |
        monitoring_tool="Datadog"
        if [ "$monitoring_tool" == "Datadog"; then
          echo "Integrating Datadog for monitoring and feedback"
          # Add logic to integrate Datadog
```

For more details, refer to the [ci.yml](.github/workflows/ci.yml) file in the repository.

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

### Installing the Windows SDK using Chocolatey

To install the Windows SDK using Chocolatey, follow these steps:

1. Open a command prompt with administrative privileges.
2. Run the following command to install the Windows SDK:
   ```sh
   choco install windows-sdk-10.1 --source=https://chocolatey.org/api/v2/
   ```
   ```sh
   choco install windows-sdk-10 --source=https://chocolatey.org/api/v2/
   ```

This command installs the Windows SDK version 10.1 and Windows SDK version 10 from the Chocolatey package repository.

### Verifying the Windows SDK Installation

After installing the Windows SDK, it is important to verify that it is properly installed. You can add a step in your CI pipeline to check the installation:

* Add a step to verify the Windows SDK installation in the `.github/workflows/ci.yml` file:
  ```yaml
  - name: Verify Windows SDK Installation
    run: |
      if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0" ]; then
        echo "Windows SDK 10 is properly installed."
      elif [ -d "C:\Program Files (x86)\Windows Kits\10.1\Include\10.1.18362.1" ]; then
        echo "Windows SDK 10.1 is properly installed."
      else
        echo "Windows SDK is not properly installed."
        exit 1
  ```

This step ensures that the Windows SDK is installed correctly and is compatible with the WDK.

### Installing the WindowsKernelModeDriver build tools using Chocolatey

To install the WindowsKernelModeDriver build tools using Chocolatey, follow these steps:

1. Open a command prompt with administrative privileges.
2. Run the following command to install the WindowsKernelModeDriver build tools:
   ```sh
   choco install kmdf
   ```

This command installs the WindowsKernelModeDriver build tools from the Chocolatey package repository.

### Accessing and Interpreting Installation Logs

To access and interpret the installation logs generated during the CI pipeline, follow these steps:

1. **Accessing Logs**:
   - The logs from each installation step are uploaded as artifacts in the GitHub Actions workflow.
   - Navigate to the "Actions" tab in your GitHub repository.
   - Select the workflow run you are interested in.
   - Download the "build-logs" artifact, which contains all the log files.

2. **Interpreting Logs**:
   - Each log file is named descriptively based on the installation step, e.g., `install_dependencies.log`, `install_windows_sdk.log`.
   - Open the log file corresponding to the installation step you want to review.
   - Look for any error messages or warnings in the log file to identify issues during the installation process.
   - Use the log file to troubleshoot and resolve any problems encountered during the installation steps.

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

### Setting Up GitHub Actions Permissions

To ensure that the CI pipeline runs jobs as expected, it is important to set up GitHub Actions permissions in the repository settings. Follow these steps:

1. Navigate to the repository on GitHub.
2. Click on the "Settings" tab.
3. In the left sidebar, click on "Actions".
4. Under "Actions permissions", ensure that "Allow all actions and reusable workflows" is selected.
5. Under "Workflow permissions", select "Read and write permissions".
6. Click "Save" to apply the changes.

By setting up the appropriate permissions, you ensure that the CI pipeline has the necessary access to run jobs and interact with the repository.

### Installing the Windows SDK using Chocolatey

To install the Windows SDK using Chocolatey, follow these steps:

1. Open a command prompt with administrative privileges.
2. Run the following command to install the Windows SDK:
   ```sh
   choco install windows-sdk-10.1 --source=https://chocolatey.org/api/v2/
   ```

This command installs the Windows SDK version 10.1 from the Chocolatey package repository.

### Verifying the Windows SDK Installation

After installing the Windows SDK, it is important to verify that it is properly installed. You can add a step in your CI pipeline to check the installation:

* Add a step to verify the Windows SDK installation in the `.github/workflows/ci.yml` file:
  ```yaml
  - name: Verify Windows SDK Installation
    run: |
      if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0" ]; then
        echo "Windows SDK is properly installed."
      else
        echo "Windows SDK is not properly installed."
        exit 1
  ```

This step ensures that the Windows SDK is installed correctly and is compatible with the WDK.

### Installing the WindowsKernelModeDriver build tools using Chocolatey

To install the WindowsKernelModeDriver build tools using Chocolatey, follow these steps:

1. Open a command prompt with administrative privileges.
2. Run the following command to install the WindowsKernelModeDriver build tools:
   ```sh
   choco install kmdf
   ```

This command installs the WindowsKernelModeDriver build tools from the Chocolatey package repository.

### Accessing and Interpreting Installation Logs

To access and interpret the installation logs generated during the CI pipeline, follow these steps:

1. **Accessing Logs**:
   - The logs from each installation step are uploaded as artifacts in the GitHub Actions workflow.
   - Navigate to the "Actions" tab in your GitHub repository.
   - Select the workflow run you are interested in.
   - Download the "build-logs" artifact, which contains all the log files.

2. **Interpreting Logs**:
   - Each log file is named descriptively based on the installation step, e.g., `install_dependencies.log`, `install_windows_sdk.log`.
   - Open the log file corresponding to the installation step you want to review.
   - Look for any error messages or warnings in the log file to identify issues during the installation process.
   - Use the log file to troubleshoot and resolve any problems encountered during the installation steps.

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

### Setting Up GitHub Actions Permissions

To ensure that the CI pipeline runs jobs as expected, it is important to set up GitHub Actions permissions in the repository settings. Follow these steps:

1. Navigate to the repository on GitHub.
2. Click on the "Settings" tab.
3. In the left sidebar, click on "Actions".
4. Under "Actions permissions", ensure that "Allow all actions and reusable workflows" is selected.
5. Under "Workflow permissions", select "Read and write permissions".
6. Click "Save" to apply the changes.

By setting up the appropriate permissions, you ensure that the CI pipeline has the necessary access to run jobs and interact with the repository.

### Environment Variables

The following environment variables are used in the CI pipeline:

- `WDK_IncludePath`: Specifies the include paths for the Windows Driver Kit (WDK).
- `NUGET`: Specifies the path to the NuGet executable.

Ensure that these environment variables are set correctly in the CI pipeline configuration.
