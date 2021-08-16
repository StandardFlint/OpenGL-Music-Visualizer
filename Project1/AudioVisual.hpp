//
//  AudioVisual.hpp
//  Project
//
//  Created by Kevin Flint on 6/5/17.
//  Copyright © 2017 Kevin Flint. All rights reserved.
//

#ifndef AudioVisual_hpp
#define AudioVisual_hpp

#include <stdio.h>
#include <vector>
#include "ScreenObject.hpp"


#define LEFT_CHANNEL 0
#define RIGHT_CHANNEL 1


class AudioVisual : public ScreenObject{
    
private:
    
    std::vector<short>* data;
    
    unsigned int channel;
    unsigned int channels;
    
    int windowWidth;
    int windowHeight;
    
    float xPosition;
    float yPosition;
    
    
public:

    AudioVisual(float _xPosition, float _yPosition, int _shaderType, GLuint _shaderID);
    ~AudioVisual();
    
    void SetData(std::vector<short>* _data);
    std::vector<short>* GetData();

    void WindowUpdate(int _width, int _height);
    
    void SetChannel(unsigned int _channel);
    void SetChannels(unsigned int _channels);
    int GetChannels();
    
    void SetPositon(float _xPosition, float _yPosition);
    
    float* GetPosition();
    float* GetWindowInfo();
    
    virtual void SampleOffset(int _offset) = 0;
    
};


#endif /* AudioVisual_hpp */
