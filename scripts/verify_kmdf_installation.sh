#!/bin/bash

# Check if KMDF 1.31 is properly installed for Windows 10
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\kmdf\1.31" ]; then
  echo "KMDF 1.31 is properly installed for Windows 10."
else
  echo "Warning: KMDF 1.31 is not properly installed for Windows 10."
fi

# Check if KMDF 1.33 is properly installed for Windows 11
if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\kmdf\1.33" ]; then
  echo "KMDF 1.33 is properly installed for Windows 11."
else
  echo "Warning: KMDF 1.33 is not properly installed for Windows 11."
fi

# Log the output for troubleshooting
echo "KMDF installation verification completed."
