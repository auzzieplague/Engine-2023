#pragma once
#include <string>

enum ShaderType {
    VERTEX_SHADER,
    FRAGMENT_SHADER,
    GEOMETRY_SHADER,
    TESSELLATION_CONTROL_SHADER,
    TESSELLATION_EVALUATION_SHADER,
    COMPUTE_SHADER
    // potentially more types as graphics APIs evolve or based on specific needs
};


class GraphicsAPI; // forward declare

class Shader {
    static GraphicsAPI *graphicsApi;

public:
    unsigned int type; // should be an enum for ShaderType
    bool compiled = false;
    std::string source;
    unsigned int shaderID = 0;
    explicit Shader(unsigned int type);
    explicit Shader(unsigned int type, const std::string& fileName);

    Shader *loadFromSource (const std::string & sourceCode);
    Shader *setSource (const std::string & sourceCode);

    static void setGraphicsAPI(GraphicsAPI *api);

    Shader *compile ();
};