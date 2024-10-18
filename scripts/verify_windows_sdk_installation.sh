#!/bin/bash

# Check if the Windows SDK files are present in the correct installation path
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0" ]; then
  echo "Windows SDK files are present in the correct installation path."
else
  echo "Windows SDK files are not present in the correct installation path."
  exit 1
fi

# Log the output for troubleshooting
echo "Windows SDK is properly installed."
