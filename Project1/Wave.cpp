#include "Wave.h"



Wave::Wave() {

	alGenSources(1, &source);
	alGenBuffers(STREAM_BUFFER_COUNT, bufferID);

	//current = high_resolution_clock::now();
	//last = high_resolution_clock::now();
    streamOffset = 0;
    //isStreaming = false;
    streamBufferSize = 0;

}


Wave::Wave(const char* _fileLoc) {
    
    info.format = 0; //required by libsndfile
    visualCount = 0;

	file = sf_open(_fileLoc, SFM_READ, &info);

	if (file == NULL)
	{
		
	}
	//else
    
    //std::cout << "Title: " << sf_get_string(file, SF_STR_TITLE) << std::endl;


	alGenSources(1, &source);
	alGenBuffers(STREAM_BUFFER_COUNT, bufferID);

	//current = high_resolution_clock::now();
	//last = high_resolution_clock::now();
    streamOffset = 0;
    //isStreaming = false;
    streamBufferSize = 0;
    
    //std::cout << "frames: " << info.frames << std::endl;
    

    /*
    AVIODirContext *ctx = NULL;
    
    if (avio_open_dir(&ctx, "/", NULL) < 0) {
        fprintf(stderr, "Cannot open directory.\n");
    }
    
    AVIODirEntry *entry = NULL;
    for (;;) {
        if (avio_read_dir(ctx, &entry) < 0) {
            fprintf(stderr, "Cannot list directory.\n");
            abort();
        }
        if (!entry)
            break;
        printf("%s\n", entry->name);
        avio_free_directory_entry(&entry);
    }
    */

}

/*
Wave::Wave(const char* _fileLoc, Waveform* _waveform) {
    
    info.format = 0; //required by libsndfile
    waveformCount = 1;
    
	file = sf_open(_fileLoc, SFM_READ, &info);

	if (file == NULL)
	{

	}
	//else

	//waveform = _waveform;
    
    waveforms.push_back(_waveform);

	waveforms[0]->SetData(&wave);

	alGenSources(1, &source);
	alGenBuffers(STREAM_BUFFER_COUNT, bufferID);

	current = high_resolution_clock::now();
	last = high_resolution_clock::now();

}
*/




Wave::~Wave() {

	alDeleteSources(1, &source);
	alDeleteBuffers(STREAM_BUFFER_COUNT, bufferID);

}




int Wave::OpenSoundFile(const char* _soundFileLoc) {



	file = sf_open(_soundFileLoc, SFM_READ, &info);

	if (file == NULL)
	{
		return false;
	}
	else
		return true;

}

//Doesnt work with streaming functions, fix
void Wave::AddVisual(AudioVisual* _visual) {

	//waveform = _waveform;
    visuals.push_back(_visual);
    visuals[visualCount]->SetChannels(info.channels);
	visuals[visualCount]->SetData(&wave);
    visualCount++;

}


void Wave::RemoveWaveform(unsigned int _index) {

    visuals.erase(visuals.begin()+_index);

}




inline int Wave::GetSampleSize() {

	if ((info.format % 16) == 1)
		return 8;
	else if ((info.format % 16) == 2)
		return 16;
	else
		return 16;

}


//Delete later, depricated
void Wave::Stream() {

	BeginStream(44100, 0, 0);

	int processedBuffers = 0;


	alGetSourcei(source, AL_BUFFERS_PROCESSED, &processedBuffers);




}

void Wave::SyncWaveform(unsigned int _index) {
    
    if (visuals.size() > 0) {

        visuals[_index]->SampleOffset(GetCurrentSample());

    }
}

void Wave::SyncAllWaveforms() {
        
    for (int i = 0; i < visuals.size(); i++) {
        
        visuals[i]->SampleOffset(GetCurrentSample());
        
    }
    //std::cout << "actual pos: " << CurrentSample()+streamOffset << std::endl;
}


//
void Wave::LoadChunkIntoBuffer(int _sampleCount) {
    
    int sampleCount = _sampleCount * info.channels;
    sf_read_short(file, wave.data(), sampleCount);
    
}


void Wave::LoadAllIntoBuffer() {
    
    int sampleCount = info.frames * info.channels;
    wave.assign(sampleCount, 0);
    
    FillBuffer(bufferID[0], sampleCount, wave.data());
    
    alSourcei(source, AL_BUFFER, bufferID[0]);
    
}


int Wave::FillBuffer(ALuint _buffer, int _sampleCount, short* _ptr) {
    
    //set offset with sndfile library here
    //sf_seek(file, _offset, SEEK_CUR); //
    //Note: not needed, remove offset later
    
    int samplesRead = sf_read_short(file, _ptr, _sampleCount);
    
    if (samplesRead > 0)
    
        alBufferData(
                     _buffer,
                     AlFormatType(info.channels, GetSampleSize()),
                     _ptr,
                     samplesRead * sizeof(short),
                     info.samplerate
                     );

    return samplesRead;
    
}


void Wave::GoToSample(ALint _sample) {
    
    int type = 0;
    alGetSourcei(source, AL_SOURCE_TYPE, &type);
    
    if (type == AL_STATIC){
        alSourcei(source, AL_SAMPLE_OFFSET, _sample);
    }
    else if (type == AL_STREAMING){
        ResetStream(streamBufferSize, _sample, SEEK_SET, streamOffset/streamBufferSize);
    }
    
    
    
}



//Note: change to accept number of stream buffers as an argument (int)
void Wave::BeginStream(int _bufferSize, int _offset, int _frontPadding) {
    
    streamBufferSize = _bufferSize;


	int sampleCount = streamBufferSize * info.channels;

	short* chunk = new short[sampleCount];
    
    sf_seek(file, _offset, SEEK_SET);
    

	for (int i = 0; i < STREAM_BUFFER_COUNT; i++) {
        //std::cout << "Chunk size: " << sampleCount << std::endl;
		//FillBuffer(bufferID[i], sampleCount, chunk);
        
        if(FillBuffer(bufferID[i], sampleCount, chunk))
            alSourceQueueBuffers(source, 1, &bufferID[i]);

        wave.insert(wave.end(), chunk, chunk + sampleCount);
        
        //std::cout << "bsize: " << wave.size() << std::endl;
	}
    
    for (int i = 0; i < _frontPadding; i++)
        wave.insert(wave.begin(), sampleCount, 0);
    streamOffset = streamBufferSize * _frontPadding;

	//alSourceQueueBuffers(source, STREAM_BUFFER_COUNT, bufferID);
	//std::cout << "SR " << info.samplerate << std::endl;
    
    delete[] chunk;

}



void Wave::ResetStream(int _bufferSize, int _offset, int _context, int _frontPadding) {
    
    int type = 0;
    alGetSourcei(source, AL_SOURCE_TYPE, &type);
    
    if (type == AL_STREAMING){
        
        alSourceStop(source);
        
        alSourceUnqueueBuffers(source, STREAM_BUFFER_COUNT, bufferID);
        wave.clear();
        
        streamBufferSize = _bufferSize;

        int sampleCount = streamBufferSize * info.channels;
        short* chunk = new short[sampleCount];
        
        sf_seek(file, _offset, _context);
        
        for (int i = 0; i < STREAM_BUFFER_COUNT; i++) {
            FillBuffer(bufferID[i], sampleCount, chunk);
            wave.insert(wave.end(), chunk, chunk + sampleCount);
        }
        
        alSourceQueueBuffers(source, STREAM_BUFFER_COUNT, bufferID);
        
        for (int i = 0; i < _frontPadding; i++)
            wave.insert(wave.begin(), sampleCount, 0);
        streamOffset = streamBufferSize * _frontPadding;
        
        delete[] chunk;
        
        alSourcePlay(source);
        
    }
    
}


void Wave::StopStream() {
    
    int type = 0;
    alGetSourcei(source, AL_SOURCE_TYPE, &type);
    
    if (type == AL_STREAMING){
        
        alSourceStop(source);
        alSourceUnqueueBuffers(source, STREAM_BUFFER_COUNT, bufferID);
        wave.clear();
        streamBufferSize = 0;
        streamOffset = 0;
        
    }
    
}


void Wave::UpdateStream() {
    
	int trashHeap = 0;
	
	alGetSourcei(source, AL_BUFFERS_PROCESSED, &trashHeap);

	if (trashHeap >= 1 && GetAudioState() == AL_PLAYING) {

		ALuint updateBuffer;

		int sampleCount = streamBufferSize * info.channels;

		short* chunk = new short[sampleCount];

		for (int i = 0; i < trashHeap; i++) {

			updateBuffer = 0;
			alSourceUnqueueBuffers(source, 1, &updateBuffer);

            if(FillBuffer(updateBuffer, sampleCount, chunk))
                alSourceQueueBuffers(source, 1, &updateBuffer);
            
            wave.insert(wave.end(), chunk, chunk+sampleCount);
            wave.erase(wave.begin(), wave.begin()+sampleCount);
            
            for (int j = 0; j < visuals.size(); j++)
                visuals[j]->SetData(&wave);
            
		}

        delete[] chunk;

	}
    else if (trashHeap == STREAM_BUFFER_COUNT) //if stream is interrupted, continue
        ResetStream(streamBufferSize, 0, SEEK_CUR, streamOffset/streamBufferSize);
    else if (GetAudioState() == AL_STOPPED){
        
        wave.assign(1, 0);
        for (int j = 0; j < visuals.size(); j++)
            visuals[j]->SetData(&wave);
        
    }

}



void Wave::UpdateStream(int _bufferSize, int _offset) {
    
    int trashHeap = 0;
    
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &trashHeap);
    
    /*
     std::cout << std::endl;
     std::cout << "Audio State: " << GetAudioState() << std::endl;
     std::cout << "Trash: " << trashHeap << std::endl;
     std::cout << std::endl;
     */
    
    if (trashHeap > 0) {
        
        ALuint updateBuffer;
        
        int sampleCount = _bufferSize * info.channels;
        
        short* chunk = new short[sampleCount];
        
        sf_seek(file, _offset, SEEK_CUR);
        
        for (int i = 0; i < trashHeap; i++) {
            
            updateBuffer = 0;
            alSourceUnqueueBuffers(source, 1, &updateBuffer);
            //int id = updateBuffer - bufferID[0];
            
            FillBuffer(updateBuffer, sampleCount, chunk);
            
            alSourceQueueBuffers(source, 1, &updateBuffer);
            
        }
        
        delete[] chunk;
        
    }
    
}






 inline ALenum Wave::AlFormatType(int _channels, int _samples) {

	if (_samples == 8) {

		if (_channels > 1)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_MONO8;

	}
	else if (_samples == 16) {

		if (_channels > 1)
			return AL_FORMAT_STEREO16;
		else
			return AL_FORMAT_MONO16;

	}
	else
		return -1;

}


void Wave::Play() {


	 alSourcePlay(source);

}

void Wave::Pause() {
    
    
    alSourcePause(source);
    
}

void Wave::Stop() {
    
    alSourceStop(source);
    
    int type = 0;
    alGetSourcei(source, AL_SOURCE_TYPE, &type);
    
    if (type == AL_STREAMING){
        
        alSourceUnqueueBuffers(source, STREAM_BUFFER_COUNT, bufferID);
        
    }
    
    /*
    wave.assign(1, 0);
    for (int j = 0; j < visuals.size(); j++)
        visuals[j]->SetData(&wave);
    */
    
}

void Wave::SetPitch(float _pitch) {
    
    
    alSourcef(source, AL_PITCH, _pitch);
    
}


void Wave::LoopAudio(bool _state) {
    
    alSourcei(source, AL_LOOPING, _state);
    
}

int Wave::GetCurrentSample() {
    
    int offset = 0;
    alGetSourcei(source, AL_SAMPLE_OFFSET, &offset);

    return offset+streamOffset;
    
}

float Wave::GetCurrentTime() {
    
    float time = 0;
    alGetSourcef(source, AL_SEC_OFFSET, &time);
    return time;
    
}


ALint Wave::GetAudioState() {
    
    int state = 0;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state;
    
}
