# Example Usage of va_g729a Library

This directory contains example code demonstrating how to use the va_g729a static library as specified in the requirements.

## Files

- `AudioCode.h` - Header file defining the CAudioCode class
- `AudioCode.cpp` - Implementation of the CAudioCode class using va_g729a library

## Usage

This example shows the exact usage pattern from the requirements. The CAudioCode class:

1. Initializes the encoder and decoder in the constructor
2. Provides `EncodeAudioData` to encode 960 bytes (6 frames) of PCM data to 60 bytes
3. Provides `DecodeAudioData` to decode 60 bytes back to 960 bytes of PCM data

## Integration Steps

To use this in your Visual Studio project:

1. Build the G729a static library (see `../BUILD.md`)
2. Add the library output directory to your linker paths
3. Add `../src/interface` to your include paths
4. Include these files in your project
5. The library will be automatically linked based on your build configuration (Debug/Release, x86/x64)

## Library Linking

The code automatically selects the correct library based on your build configuration:

- **Debug Win32**: Links with `G729a_ud.lib`
- **Release Win32**: Links with `G729a_u.lib`
- **Debug x64**: Links with `G729a_ud_x64.lib`
- **Release x64**: Links with `G729a_u_x64.lib`

## Frame Information

- Input frame size: 960 bytes (6 × 160 bytes per frame)
- Encoded frame size: 60 bytes (6 × 10 bytes per frame)
- Each frame: 80 samples × 2 bytes/sample = 160 bytes
- Each encoded frame: 10 bytes
