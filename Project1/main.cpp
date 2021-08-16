//
//  main.cpp
//  NeuralNetworkApp
//
//  Created by Kevin Flint on 1/14/16.
//  Copyright © 2016 Kevin Flint. All rights reserved.
//

#include <iostream>
//#include <pthread.h>
#include "ProgramControl.hpp"

#include "Window.hpp"
#include "Shader.hpp"
#include <GLFW/glfw3.h>

#include <GL/glew.h>

/*
 void* Process1(void* threadID) {
 
 std::cout << "Process1 running - " << (long)threadID << std::endl;
 
 pthread_exit(NULL);
 
 }
 
 void* Process2(void* threadID) {
 
 std::cout << "Process2 running - " << (long)threadID << std::endl;
 
 pthread_exit(NULL);
 
 }
 
 */

int main(int argc, const char * argv[]) {
    
    /*  some multiprocessing stuff
     pthread_t thread1;
     pthread_t thread2;
     
     int creationError;
     
     void *joinReturn;
     
     creationError = pthread_create(&thread1, NULL, &Process1, (void*)1);
     if (creationError != 0){
     std::cout << "Error:unable to create thread," << creationError << std::endl;
     exit(-1);
     }
     
     pthread_join(thread1, &joinReturn);
     
     creationError = pthread_create(&thread2, NULL, &Process2, (void*)2);
     if (creationError != 0){
     std::cout << "Error:unable to create thread," << creationError << std::endl;
     exit(-1);
     }
     
     pthread_join(thread2, &joinReturn);
     */
    
    
    //SolidColorSO obj;
    
    
    //Window* win;
    
    //win = new Window(640, 480);
     
    
    ProgramControl* control = &ProgramControl::Instance();
    control -> MainControl();
    ProgramControl::Destroy();
    
    
    /*
    while(!glfwWindowShouldClose(win->GetWindow())){
        glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor(1, 0, 0, 1);
        glfwPollEvents();
    };
    */
    
    

    
    
    
    return 0;
    
}
