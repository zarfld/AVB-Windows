#!/bin/bash

# Set the WDK_IncludePath environment variable
export WDK_IncludePath="C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0"

# Check if the WDK files are present in the correct installation path
if (Test-Path "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0") {
  echo "WDK files are present in the correct installation path."
} else {
  echo "WDK files are not present in the correct installation path."
  exit 1
}

# Check for the presence of ntddk.h in the correct installation path
if (Test-Path "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\km\ntddk.h") {
  echo "ntddk.h is present in the correct installation path."
} else {
  echo "ntddk.h is not present in the correct installation path."
  exit 1
}

# Check if the WDK_IncludePath environment variable is set
if ($env:WDK_IncludePath -eq $null) {
  echo "WDK_IncludePath environment variable is not set."
  exit 1
} else {
  echo "WDK_IncludePath is set to: $env:WDK_IncludePath"
}

# Log the output for troubleshooting
echo "WDK is properly installed."

# Provide debugging information on the path and files for Driver/i210AVBDriver.cpp
echo "Debugging information for Driver/i210AVBDriver.cpp:"
echo "Path: $(Get-Item -Path Driver/i210AVBDriver.cpp).FullName"
echo "Files in directory:"
Get-ChildItem -Path Driver/

# Check if the Windows SDK is installed and compatible with the WDK
if (Test-Path "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0") {
  echo "Windows SDK is properly installed."
} else {
  echo "Windows SDK is not properly installed."
  exit 1
}

# Verify the installation of KMDF 1.31 for Windows 10
if (Test-Path "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\kmdf\1.31") {
  echo "KMDF 1.31 is properly installed for Windows 10."
} else {
  echo "Warning: KMDF 1.31 is not properly installed for Windows 10."
}

# Verify the installation of KMDF 1.33 for Windows 11
if (Test-Path "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\kmdf\1.33") {
  echo "KMDF 1.33 is properly installed for Windows 11."
} else {
  echo "Warning: KMDF 1.33 is not properly installed for Windows 11."
}
