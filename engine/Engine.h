#ifndef COMPONENTLAYOUT_ENGINE_H
#define COMPONENTLAYOUT_ENGINE_H

#include "../core/Window.h"
#include "Object.h"
#include "Scene.h"
#include "layers/Layer.h"

class Engine: Object {
  Scene *currentScene{};
  Scene *nextScene{};
  std::vector<Layer*> layers;

  Window* window{};

  static Engine *instance;

public:
    explicit Engine( uint32_t width = 1600, uint32_t height = 800,  const std::string& title = "Onion", Scene * scene = nullptr);

    static Engine* getInstance()
    {
        return instance;
    }

    void start();               // kick-start engine
    void loopLayers() const;          // main loop
    void stop() const;          // cleanup

};


#endif //COMPONENTLAYOUT_ENGINE_H
