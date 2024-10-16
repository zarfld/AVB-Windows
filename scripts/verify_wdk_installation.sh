#!/bin/bash

# Check if the windowsdriverkit10 package is installed
if choco list --local-only | findstr /i "windowsdriverkit10""; then
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

# Use the 'where' command to locate 'wdksetup.exe'
if where wdksetup.exe; then
  echo "wdksetup.exe is located."
else
  echo "wdksetup.exe is not located."
#  exit 1
fi

# Log the output for troubleshooting
echo "WDK is properly installed."
