#!/bin/bash

if [ -d "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0" ]; then
  echo "Windows SDK is properly installed."
else
  echo "Windows SDK is not properly installed."
  exit 1
fi
