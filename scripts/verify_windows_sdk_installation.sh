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

# Log the output for troubleshooting
echo "Windows SDK is properly installed."
