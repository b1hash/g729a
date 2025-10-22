/**
 *  va_g729a wrapper implementation
 *  Simplified interface for G.729A codec
 */

#include "va_g729a_interface.h"
#include "g729a_interface.h"
#include <stdlib.h>
#include <string.h>

/* Global encoder and decoder states */
static void* g_encoder_state = NULL;
static void* g_decoder_state = NULL;

void va_g729a_init_encoder(void)
{
    if (g_encoder_state == NULL)
    {
        /* Allocate encoder state */
        unsigned int size = G729A_Encoder_Get_Size();
        g_encoder_state = malloc(size);
        if (g_encoder_state != NULL)
        {
            memset(g_encoder_state, 0, size);
        }
    }
    
    if (g_encoder_state != NULL)
    {
        G729A_Encoder_Init(g_encoder_state);
    }
}

void va_g729a_encoder(const short* speech, unsigned char* bitstream)
{
    if (g_encoder_state == NULL || speech == NULL || bitstream == NULL)
    {
        return;
    }
    
    G729A_Encoder_Process(g_encoder_state, (short*)speech, bitstream);
}

void va_g729a_init_decoder(void)
{
    if (g_decoder_state == NULL)
    {
        /* Allocate decoder state */
        unsigned int size = G729A_Decoder_Get_Size();
        g_decoder_state = malloc(size);
        if (g_decoder_state != NULL)
        {
            memset(g_decoder_state, 0, size);
        }
    }
    
    if (g_decoder_state != NULL)
    {
        G729A_Decoder_Init(g_decoder_state);
    }
}

void va_g729a_decoder(const unsigned char* bitstream, short* synth_short, int bfi, short* v1, short* v2)
{
    if (g_decoder_state == NULL || bitstream == NULL || synth_short == NULL)
    {
        return;
    }
    
    /* bfi parameter is currently ignored in this implementation */
    /* v1 and v2 parameters are reserved and not used */
    (void)bfi;
    (void)v1;
    (void)v2;
    
    G729A_Decoder_Process(g_decoder_state, (unsigned char*)bitstream, synth_short);
}
