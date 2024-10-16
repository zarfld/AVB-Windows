#!/bin/bash

# Check if the windowsdriverkit10 package is installed
if choco list --local-only | findstr /i "windowsdriverkit10"; then
  echo "WDK is installed."
else
  echo "WDK is not installed."
  exit 1
fi
