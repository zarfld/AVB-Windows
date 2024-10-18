#!/bin/bash

# Set the WDK_IncludePath environment variable
export WDK_IncludePath="C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0"

# Check if the WDK files are present in the correct installation path
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0" ]; then
  echo "WDK files are present in the correct installation path."
else
  echo "WDK files are not present in the correct installation path."
  exit 1
fi

# Check for the presence of ntddk.h in the correct installation path
if [ -f "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\km\ntddk.h" ]; then
  echo "ntddk.h is present in the correct installation path."
else
  echo "ntddk.h is not present in the correct installation path."
  exit 1
fi

# Check if the WDK_IncludePath environment variable is set
if [ -z "$WDK_IncludePath" ]; then
  echo "WDK_IncludePath environment variable is not set."
  exit 1
else
  echo "WDK_IncludePath is set to: $WDK_IncludePath"
fi

# Log the output for troubleshooting
echo "WDK is properly installed."

# Provide debugging information on the path and files for Driver/i210AVBDriver.cpp
echo "Debugging information for Driver/i210AVBDriver.cpp:"
echo "Path: $(realpath Driver/i210AVBDriver.cpp)"
echo "Files in directory:"
ls -l Driver/

# Check if the Windows SDK is installed and compatible with the WDK
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0" ]; then
  echo "Windows SDK is properly installed."
else
  echo "Windows SDK is not properly installed."
  exit 1
fi

# Verify the installation of KMDF 1.31 for Windows 10
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\kmdf\1.31" ]; then
  echo "KMDF 1.31 is properly installed for Windows 10."
else
  echo "Warning: KMDF 1.31 is not properly installed for Windows 10."
fi

# Verify the installation of KMDF 1.33 for Windows 11
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\kmdf\1.33" ]; then
  echo "KMDF 1.33 is properly installed for Windows 11."
else
  echo "Warning: KMDF 1.33 is not properly installed for Windows 11."
fi

# Check for specific versions of WDK installed via Chocolatey
if choco list --local-only | grep -q "windowsdriverkit10 10.0.19041.685"; then
  echo "WDK version 10.0.19041.685 is installed via Chocolatey."
elif choco list --local-only | grep -q "windowsdriverkit10 10.0.17763"; then
  echo "WDK version 10.0.17763 is installed via Chocolatey."
elif choco list --local-only | grep -q "windowsdriverkit10 10.0.17134"; then
  echo "WDK version 10.0.17134 is installed via Chocolatey."
elif choco list --local-only | grep -q "windowsdriverkit10 10.0.10586"; then
  echo "WDK version 10.0.10586 is installed via Chocolatey."
else
  echo "No matching WDK version installed via Chocolatey."
  exit 1
fi

# Ensure matching versions of WDK and SDK
if choco list --local-only | grep -q "windows-sdk-10.1 10.1.18362.1" && choco list --local-only | grep -q "windowsdriverkit10 10.0.19041.685"; then
  echo "Matching versions of WDK and SDK are installed via Chocolatey."
elif choco list --local-only | grep -q "windows-sdk-10.1 10.1.17763.1" && choco list --local-only | grep -q "windowsdriverkit10 10.0.17763"; then
  echo "Matching versions of WDK and SDK are installed via Chocolatey."
elif choco list --local-only | grep -q "windows-sdk-10.1 10.1.17134.12" && choco list --local-only | grep -q "windowsdriverkit10 10.0.17134"; then
  echo "Matching versions of WDK and SDK are installed via Chocolatey."
elif choco list --local-only | grep -q "windows-sdk-10.1 10.1.10586.15" && choco list --local-only | grep -q "windowsdriverkit10 10.0.10586"; then
  echo "Matching versions of WDK and SDK are installed via Chocolatey."
else
  echo "No matching versions of WDK and SDK installed via Chocolatey."
  exit 1
fi

# Check for the dependency KB2999226
if choco list --local-only | grep -q "kb2999226"; then
  echo "Dependency KB2999226 is installed via Chocolatey."
else
  echo "Dependency KB2999226 is not installed via Chocolatey."
  exit 1
fi

# Check for the dependencies of KB2999226
if choco list --local-only | grep -q "kb2919355"; then
  echo "Dependency kb2919355 is installed via Chocolatey."
else
  echo "Dependency kb2919355 is not installed via Chocolatey."
  exit 1
fi

if choco list --local-only | grep -q "chocolatey-windowsupdate.extension"; then
  echo "Dependency chocolatey-windowsupdate.extension is installed via Chocolatey."
else
  echo "Dependency chocolatey-windowsupdate.extension is not installed via Chocolatey."
  exit 1
fi
