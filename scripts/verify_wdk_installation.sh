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

# Check for the presence of C:\ProgramData\chocolatey\logs\chocolatey.log
if [ -f "C:\ProgramData\chocolatey\logs\chocolatey.log" ]; then
  echo "C:\ProgramData\chocolatey\logs\chocolatey.log is present."
else
  echo "C:\ProgramData\chocolatey\logs\chocolatey.log is not present."
  exit 1
fi
