#pragma once

/*
extern "C" {

#include <libavformat/avformat.h>

    
}
*/

#include <iostream>

#include <vector>

#include "AL/al.h"
#include "AL/alc.h"

#include <sndfile.h>

#include "AudioVisual.hpp"

#include <chrono>




using namespace std::chrono;

#define NOT_STREAMING 0
#define STREAMING 1

#define STREAM_BUFFER_COUNT 4 //Number of buffers for streaming

class Wave {

private:

	SF_INFO info;
	SNDFILE* file;

	std::vector<short> wave;

	//Waveform* waveform;
    std::vector<AudioVisual*> visuals;


	ALuint source;

	//ALuint streamSource;

	high_resolution_clock::time_point current;
	high_resolution_clock::time_point last;

	ALuint bufferID[STREAM_BUFFER_COUNT];
    
    unsigned int visualCount;
    
    int streamOffset;
    int absoluteSampleOffset;
    
    int streamBufferSize;

	inline ALenum AlFormatType(int _channels, int _samples);

public:

	Wave();
	Wave(const char* _soundFileLoc);
	Wave(const char* _soundFileLoc, AudioVisual* _visual);
	~Wave();

	

	int OpenSoundFile(const char* _fileLoc);

	void LoadChunkIntoBuffer(int _sampleCount);

	//void LoadChunk();

	
	void LoadAllIntoBuffer();

	void Play(); //plays what is currently in the buffer
    void Pause();
    void Stop();
    
    void LoopAudio(bool _state);

	void BeginStream(int _bufferSize, int _offset, int _frontPadding);
	void UpdateStream();
    void ResetStream(int _bufferSize, int _offset, int _context, int _frontPadding);
    void StopStream();
    void UpdateStream(int _bufferSize, int _offset);
	
	void AddVisual(AudioVisual* _visual);

	void RemoveWaveform(unsigned int _index);

	void Stream();

	void SyncWaveform(unsigned int _index);
    void SyncAllWaveforms();

	int FillBuffer(ALuint _buffer, int _sampleCount, short* _ptr);

	inline int GetSampleSize();
    
    int GetCurrentSample();
    
    float GetCurrentTime();
    
    void SetPitch(float _pitch);
    
    ALint GetAudioState();
    
    void GoToSample(ALint _sample);
    
    //int GetActualPosition();

};
