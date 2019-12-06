#ifndef __WAVEFILE_H_
#define __WAVEFILE_H_

/******************************************************************************
* File Name: wavefile.h
*
* Created for CMPR-271 on: Nov. 1, 2019
*
* Author: Carlos Barrios
*
* Modified by: <student's name here> on <date>
*
* Purpose: Contains the structure prototype for the wavefile to be created
* by the module dtmf.c
*  
******************************************************************************/

#include <stdint.h>

#define BYTES_PER_SAMPLE 2
#define SAMPLE_RATE 44100
//#define SAMPLE_RATE 11025
//#define SAMPLE_RATE 8000
#define NUM_CHANNELS 1
#define AMPLITUDE 16382

#define PCM_FORMAT 1

#pragma pack (1)    // pack the data one byte at a time, disregarding word boundaries

typedef struct 
{
   uint8_t ChunkID[4];  
   uint32_t ChunkSize;      // 4 + (8+SubChunk1Size) + (8+SubChunk2Size)
   uint8_t Format[4];

   uint8_t SubChunk1ID[4];
   uint32_t SubChunk1Size;
   
   uint16_t AudioFormat;
   uint16_t NumChannels;
   
   uint32_t SampleRate;
   uint32_t ByteRate;       //SampleRate * NumChannels * BitsPerSample/8
   uint16_t BlockAlign;     //NumChannles * BitsPerSample/8
   uint16_t BitsPerSample;

   uint8_t SubChunk2ID[4];
   uint32_t SubChunk2Size;  //NumSamples * NumChannels * BitsPerSample/8
   
   
}WAVEFILE;

#pragma pack ()     // no more data packing, use word boundaries again

#endif
