# Building va_g729a Static Library

## Overview

This project provides a simplified wrapper interface for the G.729A codec that can be built as a static library for Windows platforms.

## Building with Visual Studio

### Prerequisites
- Visual Studio 2019 or later (with C/C++ tools)
- Windows SDK 10.0

### Build Instructions

1. Open `G729a.sln` in Visual Studio
2. Select the desired configuration:
   - **Debug|Win32** - Builds `G729a_ud.lib` (32-bit debug)
   - **Release|Win32** - Builds `G729a_u.lib` (32-bit release)
   - **Debug|x64** - Builds `G729a_ud_x64.lib` (64-bit debug)
   - **Release|x64** - Builds `G729a_u_x64.lib` (64-bit release)
3. Build the solution (Ctrl+Shift+B)

### Output Location

Library files will be generated in:
- `lib\Win32\Debug\G729a_ud.lib`
- `lib\Win32\Release\G729a_u.lib`
- `lib\x64\Debug\G729a_ud_x64.lib`
- `lib\x64\Release\G729a_u_x64.lib`

## Using the Library

### Include Headers

```cpp
extern "C" {
    #include "va_g729a_interface.h"
}
```

### Link the Library

Add one of the following to your project settings or code:

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

### API Functions

The library provides the following functions:

- `void va_g729a_init_encoder(void)` - Initialize encoder
- `void va_g729a_encoder(const short* speech, unsigned char* bitstream)` - Encode 80 samples (160 bytes) to 10 bytes
- `void va_g729a_init_decoder(void)` - Initialize decoder
- `void va_g729a_decoder(const unsigned char* bitstream, short* synth_short, int bfi, short* v1, short* v2)` - Decode 10 bytes to 80 samples (160 bytes)

### Frame Size Information

- Input PCM: 80 samples (160 bytes) of 16-bit linear PCM @ 8kHz
- Output bitstream: 10 bytes (compressed)
- Encoding ratio: 16:1 (160 bytes -> 10 bytes)

### Example Usage

```cpp
#define SIZE_AUDIO_FRAME 960  // 6 frames * 160 bytes
#define SIZE_AUDIO_PACKED 60  // 6 frames * 10 bytes

class CAudioCode
{
public:
    CAudioCode();
    virtual ~CAudioCode();

    BOOL EncodeAudioData(char *pin, int len, char* pout, int* lenr);
    BOOL DecodeAudioData(char *pin, int len, char* pout, int* lenr);
};

CAudioCode::CAudioCode()
{
    va_g729a_init_encoder();
    va_g729a_init_decoder();
}

CAudioCode::~CAudioCode()
{
}

BOOL CAudioCode::EncodeAudioData(char* pin, int len, char* pout, int* lenr)
{
    if (!pin || len != SIZE_AUDIO_FRAME || !pout)
        return FALSE;

    // Encode 6 frames (960 bytes / 160 bytes per frame)
    va_g729a_encoder((short*)pin, (BYTE*)pout);
    va_g729a_encoder((short*)(pin + 160), (BYTE*)pout + 10);
    va_g729a_encoder((short*)(pin + 320), (BYTE*)pout + 20);
    va_g729a_encoder((short*)(pin + 480), (BYTE*)pout + 30);
    va_g729a_encoder((short*)(pin + 640), (BYTE*)pout + 40);
    va_g729a_encoder((short*)(pin + 800), (BYTE*)pout + 50);

    if (lenr)
        *lenr = SIZE_AUDIO_PACKED;

    return TRUE;
}

BOOL CAudioCode::DecodeAudioData(char* pin, int len, char* pout, int* lenr)
{
    if (!pin || len != SIZE_AUDIO_PACKED || !pout)
        return FALSE;

    // Decode 6 frames (60 bytes / 10 bytes per frame)
    va_g729a_decoder((BYTE*)pin, (short*)(pout), 0);
    va_g729a_decoder((BYTE*)pin + 10, (short*)(pout + 160), 0);
    va_g729a_decoder((BYTE*)pin + 20, (short*)(pout + 320), 0);
    va_g729a_decoder((BYTE*)pin + 30, (short*)(pout + 480), 0);
    va_g729a_decoder((BYTE*)pin + 40, (short*)(pout + 640), 0);
    va_g729a_decoder((BYTE*)pin + 50, (short*)(pout + 800), 0);

    if (lenr)
        *lenr = SIZE_AUDIO_FRAME;

    return TRUE;
}
```

## Notes

- The library uses static runtime linking (Multi-threaded or Multi-threaded Debug)
- Each encoder/decoder instance uses global state, so only one encoder and one decoder can be active at a time
- For thread-safe multi-instance support, consider using the original G729A API directly
