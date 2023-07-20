#pragma once

#include "../core/Base.h"

class Object {
public:
    static unsigned int counter;
    unsigned int objectID;
    static std::map<int,Object *> objectMap;
    enum class ObjectType {
        OT_Unknown,
        OT_Object,
        OT_Component,
        OT_Model,
        OT_Terrain,
        OT_Mesh,
        OT_Texture,
        OT_Light,
        OT_Layer,
        OT_Layer_GUI
    };

    std::string objectName = "Un-named Object";
    glm::vec3 colourID;

    virtual ObjectType getType() {
        return ObjectType::OT_Object;
    };

    virtual std::string getName() {
        return objectName;
    };

    virtual void setName(std::string name) {
         objectName = name;
    };

    Object() {
        counter++;
        objectID = counter;
        setColourID();
        objectMap[objectID]= this;
        std::cout << "created object " << counter << "\n";
    }

    void setColourID(){
        this->colourID.r = (this->counter & 0x000000FF) / 255.0f;
        this->colourID.g = ((this->counter & 0x0000FF00) >>  8) / 255.0f;
        this->colourID.b = ((this->counter & 0x00FF0000) >> 16) / 255.0f;
    }

    Object* getByID(unsigned int ID) {
        return objectMap[ID];
    }
};

