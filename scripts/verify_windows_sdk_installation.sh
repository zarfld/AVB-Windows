#!/bin/bash

# Check if the Windows SDK files are present in the correct installation path
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0" ]; then
  echo "Windows SDK files are present in the correct installation path. (10.0.22621.0)"
elif [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.1.18362.1" ]; then
  echo "Windows SDK files are present in the correct installation path. (10.1.18362.1)"
elif [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.1.17763.1" ]; then
  echo "Windows SDK files are present in the correct installation path. (10.1.17763.1)"
elif [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.1.17134.12" ]; then
  echo "Windows SDK files are present in the correct installation path. (10.1.17134.12)"
elif [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.1.15063.468" ]; then
  echo "Windows SDK files are present in the correct installation path. (10.1.15063.468)"
elif [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.1.10586.15" ]; then
  echo "Windows SDK files are present in the correct installation path. (10.1.10586.15)"
else
  echo "Windows SDK files are not present in the correct installation path."
  exit 1
fi

# Check if the Windows SDK files are present in the correct installation path
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0" ]; then
  echo "Windows SDK files are present in the correct installation path."
else
  echo "Windows SDK files are not present in the correct installation path."
  exit 1
fi

# Check for specific versions of Windows SDK installed via Chocolatey
if choco list --local-only | grep -q "windows-sdk-10.1 10.1.18362.1"; then
  echo "Windows SDK version 10.1.18362.1 is installed via Chocolatey."
elif choco list --local-only | grep -q "windows-sdk-10.1 10.1.17763.1"; then
  echo "Windows SDK version 10.1.17763.1 is installed via Chocolatey."
elif choco list --local-only | grep -q "windows-sdk-10.1 10.1.17134.12"; then
  echo "Windows SDK version 10.1.17134.12 is installed via Chocolatey."
elif choco list --local-only | grep -q "windows-sdk-10.1 10.1.15063.468"; then
  echo "Windows SDK version 10.1.15063.468 is installed via Chocolatey."
elif choco list --local-only | grep -q "windows-sdk-10.1 10.1.10586.15"; then
  echo "Windows SDK version 10.1.10586.15 is installed via Chocolatey."
else
  echo "No matching Windows SDK version installed via Chocolatey."
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

# Log the output for troubleshooting
echo "Windows SDK is properly installed."
