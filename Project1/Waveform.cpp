#include "Waveform.h"


Waveform::Waveform(float _xPosition, float _yPosition, float _width, float _amplitude, int _range, int _center, int _shaderType, GLuint _shaderID) : AudioVisual(_xPosition, _yPosition, _shaderType, _shaderID) {
    
    lineWidth = 1.0;
    

    
    amplitude = _amplitude;
    

    width = _width;
    
    SetRange(_range);

    sampleOffset = _center;
    centerOffset = sampleOffset * subdivision;
    xOffset = 0;
    
    //globalXPosition = _center * subdivision;
    //std::cout << "sub " << subdivision << std::endl;

	//std::cout << "sub " << subdivision << std::endl;
    
    


	SetObjectColor(1.0, 1.0, 1.0, 1.0);
    
    
    ///////////////////
    
    SetShaderType(_shaderType);
    SetShaderID(_shaderID);
    ChangeMode(GL_LINE_STRIP_ADJACENCY);
    


}


Waveform::~Waveform() {



}


void Waveform::SetRange(GLsizei _range) {

	range = _range;
    
    subdivision = (width / range);

	SetCount(_range+1);

}



void Waveform::SampleOffset(int _offset) {

    if ( centerOffset > 0){
        
        centerOffset = (sampleOffset - _offset) * subdivision;
        
    }
    else{
        
        centerOffset = 0;
        
        xOffset = _offset - sampleOffset;
        SetOffset(xOffset);
        
    }
    
    //std::cout << "Sample Off:"  << _offset  << std::endl;
    //if( GetData() != nullptr)
    //std::cout << "Data Size:"  << GetData()->size()  << std::endl;
    ////////////
    /*
    
    if( (GetData() != nullptr) && ( GetData()->size()/GetChannels() - (range - sampleOffset) < _offset) ){/////
        
        int countLim = _offset - ( GetData()->size()/GetChannels() - (range - sampleOffset) );
        
        
        //std::cout << "DONEEEEE"  << std::endl;
        SetCount( (range+1) - countLim );
        
        //GetData()->size() - sampleOffset < _offset
    }
     */

}



void Waveform::SetAmplitude(float _amplitude) {
    
    amplitude = _amplitude;
    
}

void Waveform::SetLineWidth(float _lineWidth) {
    
    lineWidth = _lineWidth;
    
}


void Waveform::Render() {

    
    GLint loc1 = glGetUniformLocation(GetShaderID(), "_sampleOffset");
    GLfloat loc2 = glGetUniformLocation(GetShaderID(), "_inc");
    
    GLfloat loc3 = glGetUniformLocation(GetShaderID(), "_xOffset");
    GLfloat loc4 = glGetUniformLocation(GetShaderID(), "_yOffset");
    
    GLfloat loc5 = glGetUniformLocation(GetShaderID(), "_amplitude");
    
    GLint loc6 = glGetUniformLocation(GetShaderID(), "_center");
    
    GLfloat loc7 = glGetUniformLocation(GetShaderID(), "_lineWidth");
    GLfloat loc8 = glGetUniformLocation(GetShaderID(), "_windowInfo");
    
    glUniform1i(loc1, xOffset);
    
    glUniform1f(loc2, subdivision);
    
    glUniform1f(loc3, GetPosition()[0] + centerOffset);
    glUniform1f(loc4, GetPosition()[1]);
    glUniform1f(loc5, amplitude);
    
    tempOffset = sampleOffset;
    if ( centerOffset > 0)
        tempOffset = sampleOffset - (centerOffset / subdivision);
    
    glUniform1i(loc6, tempOffset);
    
    glUniform1f(loc7, lineWidth);
    glUniform2f(loc8, GetWindowInfo()[0], GetWindowInfo()[1]);

	ScreenObject::Render();

}
