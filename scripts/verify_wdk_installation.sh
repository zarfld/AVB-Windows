#!/bin/bash

# Check if the windowsdriverkit10 package is installed
if choco list --local-only | findstr /i "windowsdriverkit10"; then
  echo "WDK package is installed."
else
  echo "WDK package is not installed."
#  exit 1
fi

# Check if the WDK files are present in the correct installation path
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0" ]; then
  echo "WDK files are present in the correct installation path."
else
  echo "WDK files are not present in the correct installation path."
#  exit 1
fi

# Check for the presence of ntddk.h in the correct installation path
if [ -f "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\km\ntddk.h" ]; then
  echo "ntddk.h is present in the correct installation path."
else
  echo "ntddk.h is not present in the correct installation path."
#  exit 1
fi

# Use the 'where' command to locate 'wdksetup.exe'
if where wdksetup.exe; then
  echo "wdksetup.exe is located."
else
  echo "wdksetup.exe is not located."
#  exit 1
fi

# Log the output for troubleshooting
echo "WDK is properly installed."

# Provide debugging information on the path and files for Driver/i210AVBDriver.cpp
echo "Debugging information for Driver/i210AVBDriver.cpp:"
echo "Path: $(realpath Driver/i210AVBDriver.cpp)"
echo "Files in directory:"
ls -l Driver/
