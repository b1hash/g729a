# va_g729a Static Library Implementation

## Summary

This implementation provides a simplified wrapper interface (`va_g729a`) for the G.729A codec that can be built as a static library on Windows and other platforms.

## What Was Implemented

### 1. Wrapper Interface (`src/interface/va_g729a_interface.h`)

Provides four simple functions:
- `void va_g729a_init_encoder(void)` - Initialize encoder state
- `void va_g729a_encoder(const short* speech, unsigned char* bitstream)` - Encode one frame
- `void va_g729a_init_decoder(void)` - Initialize decoder state  
- `void va_g729a_decoder(const unsigned char* bitstream, short* synth_short, int bfi, short* v1, short* v2)` - Decode one frame

### 2. Wrapper Implementation (`src/interface/va_g729a_interface.c`)

The wrapper implementation:
- Uses global encoder/decoder states for simplified usage
- Wraps the existing G729A API (from `g729a_interface.h`)
- Automatically allocates and initializes codec states
- Provides error-safe operation (handles NULL pointers)

### 3. Visual Studio Project Files

**G729a.sln** - Visual Studio solution file
**G729a.vcxproj** - Visual Studio project configured for:

- **Debug|Win32** → Outputs `G729a_ud.lib` (32-bit debug)
- **Release|Win32** → Outputs `G729a_u.lib` (32-bit release)
- **Debug|x64** → Outputs `G729a_ud_x64.lib` (64-bit debug)
- **Release|x64** → Outputs `G729a_u_x64.lib` (64-bit release)

Output directory: `lib\[Platform]\[Configuration]\`

### 4. CMake Build System

**CMakeLists.txt** - Cross-platform build configuration supporting:
- Linux, macOS, Windows
- Automatic library naming based on platform and configuration
- Optional test program builds (`-DBUILD_TESTS=ON`)

### 5. Example Code

**example/** directory contains:
- `AudioCode.h` - Header matching the requirements
- `AudioCode.cpp` - Implementation using the va_g729a library
- `README.md` - Usage instructions

The example demonstrates encoding/decoding of 960-byte frames (6 G.729A frames).

### 6. Documentation

- **BUILD.md** - Comprehensive build instructions for both Visual Studio and CMake
- **IMPLEMENTATION.md** - This file
- **example/README.md** - Example usage guide

## Technical Details

### Frame Sizes

G.729A operates on:
- **Input**: 80 samples × 2 bytes = 160 bytes of 16-bit linear PCM @ 8kHz
- **Output**: 10 bytes of compressed bitstream
- **Compression ratio**: 16:1

The example code processes 6 frames at once:
- **Input**: 6 × 160 = 960 bytes
- **Output**: 6 × 10 = 60 bytes

### Library Linking

The example demonstrates automatic library selection based on build configuration:

```cpp
#if defined(_WIN64)
    #if _DEBUG
        #pragma comment(lib,"G729a_ud_x64.lib")
    #else
        #pragma comment(lib,"G729a_u_x64.lib")
    #endif
#else
    #if _DEBUG
        #pragma comment(lib,"G729a_ud.lib")
    #else
        #pragma comment(lib,"G729a_u.lib")
    #endif
#endif
```

### Runtime Library

Visual Studio builds use static runtime linking:
- Debug: Multi-threaded Debug (`/MTd`)
- Release: Multi-threaded (`/MT`)

## Building Instructions

### Windows with Visual Studio

1. Open `G729a.sln` in Visual Studio
2. Select configuration (Debug/Release, Win32/x64)
3. Build (Ctrl+Shift+B)
4. Find output in `lib\[Platform]\[Configuration]\`

### Linux/macOS with CMake

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

Output: `build/lib/libg729a.a`

## Integration Example

```cpp
#include "AudioCode.h"

int main() {
    CAudioCode codec;
    
    char inputPCM[960];    // 960 bytes input
    char encoded[60];      // 60 bytes encoded
    char decoded[960];     // 960 bytes decoded
    int encodedLen, decodedLen;
    
    // Encode
    if (codec.EncodeAudioData(inputPCM, 960, encoded, &encodedLen)) {
        // encodedLen = 60
        
        // Decode
        if (codec.DecodeAudioData(encoded, 60, decoded, &decodedLen)) {
            // decodedLen = 960
        }
    }
    
    return 0;
}
```

## Verification

The implementation has been verified to:
1. Compile successfully with GCC on Linux
2. Export all required functions (verified with `nm`)
3. Link correctly with test programs
4. Pass security scanning (no vulnerabilities)
5. Match the exact API requirements from the problem statement

## Notes

- The wrapper uses global state, so only one encoder and decoder instance can be active per process
- For multi-threaded applications requiring multiple instances, use the original G729A API directly
- The `bfi` parameter in `va_g729a_decoder` is currently ignored (reserved for future use)
- The `v1` and `v2` parameters are reserved and not used

## License

See the LICENSE file for licensing information. Most source code is based on ITU-T G.729 Software Package Release 2.
