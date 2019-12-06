#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"wavefile (1).h"


int checkphonenumber(const char* number)
{
    while (*number)
    {
        char pokemon = *number;
        switch (pokemon)
        {
        case '#':
            break;
        case '*':
            break;
        case '-':
            break;
        default:
            if (pokemon > '9' || pokemon < '0' ) 
               return -1; 
        }
        number++; 
    }
    return 1; 
}

//get 
int dtfmgenerator (FILE* wave, float tonelength, char* phonenumber, int numberLength)
{
int samplecount = 0;
uint16_t sampleValue = 0;
uint16_t* audiosamples = (uint16_t *) malloc(numberLength * SAMPLE_RATE* tonelength*sizeof(uint16_t));
for(; *phonenumber != '\0' ; phonenumber++)
{ 
    int tone1 = 0;
	int tone2 = 0;

	switch(*phonenumber)
	{	
		case'1':
		    tone1 = 1209;
			break;
		case'4':
			tone1 = 1209;
			break;
		case'7':
			tone1 = 1209;
			break;
		case'*':
			tone1 = 1209;
			break;
		case'2':
			tone1 = 1336;
			break;
		case'5':
			tone1 = 1336;
			break;
		case'8':
			tone1 = 1336;
			break;
		case'0':
			tone1 = 1336;
			break;
		case'3':
			tone1 = 1477;
			break;
		case'6':
			tone1 = 1477;
			break;
		case'9':
			tone1 = 1477;
			break;
		case'#':
			tone1 = 1477;
			break;
	}	



	switch( *phonenumber)
	{	
		case'1':
		    tone2 = 697;
			break;
		case'4':
			tone2 = 770;
			break;
		case'7':
			tone2 = 852;
			break;
		case'*':
			tone2 = 941;
			break;
		case'2':
			tone2 = 697;
			break;
		case'5':
			tone2 = 770;
			break;
		case'8':
			tone2 = 852;
			break;
		case'0':
			tone2 = 941;
			break;
		case'3':
			tone2 = 697;
			break;
		case'6':
			tone2 = 770;
			break;
		case'9':
			tone2 = 852;
			break;
		case'#':
			tone2 = 941;
			break;
	}
	
		int tonesound = SAMPLE_RATE*tonelength;
		for(int sampleNum=0; sampleNum <= tonesound ; sampleNum++,samplecount++) 
		{
		sampleValue = AMPLITUDE *(
			sin(sampleNum * tone1 * 2 * 3.14159 / SAMPLE_RATE) +
			sin(sampleNum * tone2 * 2 * 3.14159 / SAMPLE_RATE));
			*(audiosamples+ samplecount) =  sampleValue;
		}
}
fwrite(audiosamples, sizeof(uint16_t), numberLength * tonelength * SAMPLE_RATE, wave );
fclose(wave);
}



 
//writing to wave file
void waveheader(FILE* wave, float tonelength, int numberLength)
{
	
	WAVEFILE* headerPtr = (WAVEFILE*)malloc(sizeof(WAVEFILE));
	int subChunk2Size = numberLength * tonelength * SAMPLE_RATE * NUM_CHANNELS * BYTES_PER_SAMPLE;
	
	headerPtr->ChunkID[0] = 'R';
	headerPtr->ChunkID[1] = 'I';
	headerPtr->ChunkID[2] = 'F';
	headerPtr->ChunkID[3] = 'F';
	headerPtr->ChunkSize = 36 + subChunk2Size;
	headerPtr->Format[0] = 'W';
	headerPtr->Format[1] = 'A';
	headerPtr->Format[2] = 'V';
	headerPtr->Format[3] = 'E';
	headerPtr->SubChunk1ID[0] = 'f';
	headerPtr->SubChunk1ID[1] = 'm';
	headerPtr->SubChunk1ID[2] = 't';
	headerPtr->SubChunk1ID[3] = ' ';
	headerPtr->SubChunk1Size = 16;
	headerPtr->AudioFormat = 1;
	headerPtr->NumChannels = NUM_CHANNELS;
	headerPtr->SampleRate = SAMPLE_RATE;
	headerPtr->ByteRate = SAMPLE_RATE*NUM_CHANNELS*BYTES_PER_SAMPLE;
	headerPtr->BlockAlign = NUM_CHANNELS*BYTES_PER_SAMPLE;
	headerPtr->BitsPerSample = 16;
	headerPtr->SubChunk2ID[0]= 'd';
	headerPtr->SubChunk2ID[1]= 'a';
	headerPtr->SubChunk2ID[2]= 't';
	headerPtr->SubChunk2ID[3]= 'a';
	headerPtr->SubChunk2Size = subChunk2Size;
	
	fwrite(headerPtr,sizeof(WAVEFILE),1,wave);
}

int main ( int argc, char* argv[])
{		 
	printf("argc = %d\n", argc);
	float tonelength = atof(argv[2]);

	if (checkphonenumber(argv[3]) == -1)
	{	
		printf("%s", "Error\n");
		exit(-1);
	}
	if (tonelength < 0.0 || tonelength > 1.0 )
	{
		return -1;
	}

	FILE *fp = NULL;
	fp = fopen(argv[1], "wb");

	waveheader(fp, tonelength, strlen(argv[3]));
	dtfmgenerator(fp, tonelength, argv[3] ,strlen(argv[3])); 
}
