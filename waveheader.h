void waveheader()
{
	long size = tonelength * SAMPLE_RATE * ( phone num length);
	WAVEFILE *wavePtr = malloc(sizeof(WAVEFILE));
	
	wavePtr->ChunkID[0] = 'R';
	wavePtr->ChunkID[1] = 'I';
	wavePtr->ChunkID[2] = 'F';
	wavePtr->ChunkID[3] = 'F';
	wavePtr->ChunkSize = 36 + (size*NUM_CHANNELS*BYTES_PER_SAMPLE);
	wavePtr->Format[0] = 'W';
	wavePtr->Format[1] = 'A';
	wavePtr->Format[2] = 'V';
	wavePtr->Format[3] = 'E';
	wavePtr->SubChunk1ID[0] = 'f';
	wavePtr->SubChunk1ID[1] = 'm';
	wavePtr->SubChunk1ID[2] = 't';
	wavePtr->SubChunk1ID[3] = ' ';
	wavePtr->SubChunk1Size = 16;
	wavePtr->AudioFormat = 1;
	wavePtr->NumChannels = NUM_CHANNELS;
	wavePtr->SampleRate = SAMPLE_RATE;
	wavePtr->ByteRate = SAMPLE_RATE*NUM_CHANNELS*BYTES_PER_SAMPLE;
	wavePtr->BlockAlign = NUM_CHANNELS*BYTES_PER_SAMPLE;
	wavePtr->BitsPerSample = 16;
	wavePtr->SubChunk2ID[0]= 'd';
	wavePtr->SubChunk2ID[1]= 'a';
	wavePtr->SubChunk2ID[2]= 't';
	wavePtr->SubChunk2ID[3]= 'a';
	wavePtr->SubChunk2Size = size*NUM_CHANNELS*BYTES_PER_SAMPLE;
	FILE *wave;
	wave = fopen(filename ,"wb");
	fwrite(wavePtr,sizeof(WAVEFILE),1,wave);
	fwrite((name of variable for samples),size*BYTES_PER_SAMPLE,1,wave);
	fclose(wave);
}