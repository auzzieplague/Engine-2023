#pragma once
/**
* @author auzzi
*/

#include "Layer.h"
#include "../../core/Window.h"
class WindowLayer : public Layer {
private:
    Window * window = nullptr;
public:
     void onAttach(Scene*) override {
         Debug::show("Spawning Window");
         this->window = new Window(1280,720,"Window Layer");
     }
     void onDetach(Scene*) override {
         Debug::show("Killing Window");
     }

     void processInput (Scene * scene) override {
         //todo move to function pointer
             glfwPollEvents();

//         if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
//             glfwSetWindowShouldClose(window, true);
//         }
     };

     void afterRender(Scene * scene) override{
         glfwSwapBuffers(window->glRef);
     }
};
