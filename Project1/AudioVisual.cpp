//
//  AudioVisual.cpp
//  Project
//
//  Created by Kevin Flint on 6/5/17.
//  Copyright © 2017 Kevin Flint. All rights reserved.
//

#include "AudioVisual.hpp"


AudioVisual::AudioVisual(float _xPosition, float _yPosition, int _shaderType, GLuint _shaderID) {
    
    windowWidth = 1000;
    windowHeight = 1000;
    
    channel = LEFT_CHANNEL;
    channels = 1;
    
    xPosition = _xPosition;
    yPosition = _yPosition;
    
    data = nullptr;

}


AudioVisual::~AudioVisual() {
    
    
    
}



void AudioVisual::WindowUpdate(int _width, int _height) {
    
    windowWidth = _width;
    windowHeight = _height;
    
}


void AudioVisual::SetData(std::vector<short>* _data) {
    
    data = _data;

    //std::cout << "Size: " << _data->size() << std::endl;
    
    if (VertexBufferSize() == 0 && channel == 0)
        AddVertexBuffer(data, 1, channels*sizeof(short));
    else if (VertexBufferSize() == 0)
        AddVertexBuffer(data, 1, 0);
    else
        GetVertexBuffer(0)->UpdateVertices(data);

}


std::vector<short>* AudioVisual::GetData() {
    
    return data;
    
}


void AudioVisual::SetChannel(unsigned int _channel) {
    
    if(channels > 1)
        channel = _channel;
    GetVertexBuffer(0)->SetOffset(channel*sizeof(short));
    
}

void AudioVisual::SetChannels(unsigned int _channels) {
    
    channels = _channels;
    
}

int AudioVisual::GetChannels() {
    
    return channels;
    
}


void AudioVisual::SetPositon(float _xPosition, float _yPosition) {
    
    xPosition = _xPosition;
    yPosition = _yPosition;
    
}


float* AudioVisual::GetPosition() {
    
    float pos[2];
    pos[0] = xPosition;
    pos[1] = yPosition;
    return pos;

}

float* AudioVisual::GetWindowInfo() {
    
    float win[2];
    win[0] = windowWidth;
    win[1] = windowHeight;
    return win;
    
}

