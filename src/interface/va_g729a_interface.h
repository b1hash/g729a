/**
 *  va_g729a wrapper interface
 *  Simplified interface for G.729A codec
 */

#ifndef __VA_G729A_INTERFACE_H__
#define __VA_G729A_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief  Initialize encoder state.
 */
void va_g729a_init_encoder(void);

/**
 *  @brief  Encode a frame of 16-bit linear PCM data with g729a.
 *
 *  @param speech,     Speech sample input vector (80 samples, 160 bytes).
 *  @param bitstream,  Encoded output vector (10 Bytes).
 */
void va_g729a_encoder(const short* speech, unsigned char* bitstream);

/**
 *  @brief  Initialize decoder state.
 */
void va_g729a_init_decoder(void);

/**
 *  @brief  Decode a frame of g729a encoded bitstream data.
 *
 *  @param bitstream,    Encoded input vector (10 Bytes).
 *  @param synth_short,  Decoded output speech vector (80 samples, 160 bytes).
 *  @param bfi,          Bad frame indicator (0 = good frame, 1 = bad frame).
 *  @param v1,           Reserved parameter (can be NULL).
 *  @param v2,           Reserved parameter (can be NULL).
 */
void va_g729a_decoder(const unsigned char* bitstream, short* synth_short, int bfi, short* v1, short* v2);

#ifdef __cplusplus
}
#endif

#endif  /* __VA_G729A_INTERFACE_H__ */
