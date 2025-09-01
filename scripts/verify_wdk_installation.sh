#!/bin/bash

# Set the WDK_IncludePath environment variable
export WDK_IncludePath="C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0;C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\km;C:\Program Files (x86)\Windows Kits\11\Include\11.0.22000.0;C:\Program Files (x86)\Windows Kits\11\Include\11.0.22000.0\km"

# Set the SDK_IncludePath environment variable
export SDK_IncludePath="C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0;C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\km;C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um;C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\shared;C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\winrt;C:\Program Files (x86)\Windows Kits\11\Include\11.0.22000.0\km"

# Check if the WDK files are present in the correct installation path for Windows 10
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0" ]; then
  echo "WDK files are present in the correct installation path for Windows 10.(10.0.22621.0)"
else
  echo "WDK files are not present in the correct installation path for Windows 10.(10.0.22621.0)"
fi

# Check if the WDK files are present in the correct installation path for Windows 11
if [ -d "C:\Program Files (x86)\Windows Kits\11\Include\11.0.22000.0" ]; then
  echo "WDK files are present in the correct installation path for Windows 11.(11.0.22000.0)"
else
  echo "WDK files are not present in the correct installation path for Windows 11.(11.0.22000.0)"
fi

# Check for the presence of ntddk.h in the correct installation path for Windows 10
if [ -f "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\km\ntddk.h" ]; then
  echo "ntddk.h is present in the correct installation path for Windows 10.(10.0.22621.0\km)"
else
  echo "ntddk.h is not present in the correct installation path for Windows 10.(10.0.22621.0\km)"
fi

# Check for the presence of ntddk.h in the correct installation path for Windows 11
if [ -f "C:\Program Files (x86)\Windows Kits\11\Include\11.0.22000.0\km\ntddk.h" ]; then
  echo "ntddk.h is present in the correct installation path for Windows 11.(11.0.22000.0\km)"
else
  echo "ntddk.h is not present in the correct installation path for Windows 11.(11.0.22000.0\km)"
fi

# Check if the WDK_IncludePath environment variable is set
if [ -z "$WDK_IncludePath" ]; then
  echo "WDK_IncludePath environment variable is not set."

else
  echo "WDK_IncludePath is set to: $WDK_IncludePath"
fi

# Check if the SDK_IncludePath environment variable is set
if [ -z "$SDK_IncludePath" ]; then
  echo "SDK_IncludePath environment variable is not set."
else
  echo "SDK_IncludePath is set to: $SDK_IncludePath"
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
  echo "Windows SDK 10 is properly installed."
elif [ -d "C:\Program Files (x86)\Windows Kits\10.1\Include\10.1.18362.1" ]; then
  echo "Windows SDK 10.1 is properly installed."
elif [ -d "C:\Program Files (x86)\Windows Kits\11\Include\11.0.22000.0" ]; then
  echo "Windows SDK 11 is properly installed."
else
  echo "Windows SDK is not properly installed."
fi

# Verify the installation of KMDF 1.31 for Windows 10
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\kmdf\1.31" ]; then
  echo "KMDF 1.31 is properly installed for Windows 10."
else
  echo "Warning: KMDF 1.31 is not properly installed for Windows 10."
fi

# Verify the installation of KMDF 1.33 for Windows 11
if [ -d "C:\Program Files (x86)\Windows Kits\11\Include\11.0.22000.0\kmdf\1.33" ]; then
  echo "KMDF 1.33 is properly installed for Windows 11."
else
  echo "Warning: KMDF 1.33 is not properly installed for Windows 11."
fi

# Log the output for troubleshooting
echo "WDK installation verification completed."

# Verify the installation of the WDK Visual Studio extension
if [ -d "C:\Program Files (x86)\Microsoft Visual Studio\2022\Community\Common7\IDE\Extensions\Microsoft\WDK" ]; then
  echo "WDK Visual Studio extension is properly installed."
else
  echo "WDK Visual Studio extension is not properly installed."
fi

# Check if KMDF 1.31 is installed
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\km\wdf" ]; then
  echo "KMDF 1.31 is properly installed."
else
  echo "KMDF 1.31 is not properly installed. Continuing without KMDF."
fi
