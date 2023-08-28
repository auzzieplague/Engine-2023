
#include "API_OpenGL.h"
#include <glm/gtc/type_ptr.hpp>


void API_OpenGL::initialise() {
//    note: opengl initialise - for shader init see init render.shader
    GLsizeiptr size = transformBufferSize * sizeof(glm::mat4);
    glGenBuffers(1, &transformBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, transformBuffer);
//    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW); // Allocate 100 * 64 bytes of memory
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW ); // dynamic because constantly changing
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, transformBufferBindingPoint, transformBuffer);


//    glEnable(GL_MULTISAMPLE); // for antialiasing
}


RenderingConfig API_OpenGL::loadShader(std::string vertex, std::string fragment) {

    auto config = RenderingConfig();
    config.name = vertex +"_" + fragment;

    /// lookup paths in assetManager
    std::string vertexPath = AssetManager::getRelativePath("shaders_opengl", vertex);
    std::string vertexSource = AssetManager::stringFromFile(vertexPath);
    std::string fragmentPath = AssetManager::getRelativePath("shaders_opengl", fragment);
    std::string fragmentSource = AssetManager::stringFromFile(fragmentPath);

    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    GLint success;
    GLchar infoLog[512];

    // Check shader compilation
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, sizeof(infoLog), NULL, infoLog);
        Debug::show("frag Shader Compilation Error: "+ config.name);
        Debug::show(infoLog);
    }
    // Check shader compilation
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, sizeof(infoLog), NULL, infoLog);
        Debug::show("vertex Shader Compilation Error: "+ config.name);
        Debug::show(infoLog);
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    // Check program linking
    GLint logLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 1) {
        glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
        Debug::show("[X] - Program Linking Error: " + config.name);
        Debug::show(infoLog);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    config.shaderID = program;
    return config;
}

void API_OpenGL::initialiseShader(RenderingConfig &config) {
    currentRenderingConfig = &config;
    glUseProgram(config.shaderID);

    GLuint blockIndex = glGetUniformBlockIndex(config.shaderID, "TransformBlock");

    if (blockIndex != GL_INVALID_INDEX) {
        glUniformBlockBinding(config.shaderID, blockIndex, transformBufferBindingPoint);
        Debug::show("Transform Block Found");
    }
}

void API_OpenGL::shaderSetTransformList(const std::vector<glm::mat4> &mats) const {
    glBindBuffer(GL_UNIFORM_BUFFER, transformBuffer);
    GLsizeiptr size = mats.size() * sizeof(glm::mat4);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, size, mats.data());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void API_OpenGL::beginRender(RenderingConfig &config) {

    currentRenderingConfig = &config;
    glUseProgram(config.shaderID);

    for (auto enable: config.toEnable) {
        glEnable(enable);

        if (enable == GL_BLEND) {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
    }

    config.toEnableFlags = 0;

    for (auto disable: config.toDisable) {
        glDisable(disable);
    }

    config.toDisableFlags = 0;

    if (config.debugMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (config.clearFlags) {
        glClearColor(config.clearColour.x, config.clearColour.y, config.clearColour.z, config.clearColour.w);
        glClear(config.clearFlags);
    }
}

void API_OpenGL::endRender(RenderingConfig &config) {
//    glClear(config.clearFlags);
//    glfwSwapBuffers(scene->currentWindow->glRef());
}

// unsigned int GraphicsLayerOpenGL::testMeshVAO;
void API_OpenGL::renderMesh(Mesh *mesh) {
    // if the Mesh hasn't been setup yet, we'll need to initialise it (lazy loading)
    if (mesh->getID() == 0) {
        mesh->generateMeshID();
    }

    if (!mesh->isReady()) {
        return;
    }

    glBindVertexArray(mesh->getID());
    glDrawElements(GL_TRIANGLES, mesh->meshData->getIndices().size(), GL_UNSIGNED_INT, nullptr);
//    glDrawElements(GL_LINE_STRIP, mesh->meshData->getIndices().size(), GL_UNSIGNED_INT, nullptr);
}

void API_OpenGL::renderInstancedMesh(Mesh *mesh, std::vector<glm::mat4> transforms) {
//    if (mesh->getID() == 0) {
//        mesh->generateMeshID();
//    }

    if (!mesh->isReady()) {
        return;
    }

    glBindVertexArray(mesh->getID());
    shaderSetMaterial(mesh->getMaterial());
    // todo fix UBO
    shaderSetTransformList(transforms);
    glDrawElementsInstanced(GL_TRIANGLES, mesh->meshData->getIndices().size(), GL_UNSIGNED_INT, nullptr, transforms.size());
//    glDrawElementsInstanced(GL_LINE_STRIP, mesh->meshData->getIndices().size(), GL_UNSIGNED_INT, nullptr, transforms.size());

/**
 * currently looking at why objects are being rendered black, even after changing the renderer back
 * were just rendering single items to test the matrix being loaded correctly.
 */

    // todo strange that we have no materials flowing through even on single render
    // we havent pushed texture 1 into this shader
//    for (auto transform: transforms) {
//        shaderSetTransform(transforms[0]);
//        shaderSetMaterial(mesh->getMaterial());
//        glDrawElements(GL_LINE_STRIP, mesh->meshData->getIndices().size(), GL_UNSIGNED_INT, nullptr);
//    }
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

}

void API_OpenGL::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

unsigned int API_OpenGL::compileShader(std::string &source, unsigned int type) {
    if (source.length() == 0) return 0;

    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id,
                   1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id,
                  GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id,
                      GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) _malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message
        );
        std::cout << "modelShader fail: " << message <<
                  std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}


unsigned int API_OpenGL::loadTexture(std::string fileName) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, numChannels;
    stbi_set_flip_vertically_on_load(false);
    unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &numChannels, 0);
    if (data) {
        GLenum format;
        if (numChannels == 1)
            format = GL_RED;
        else if (numChannels == 3)
            format = GL_RGB;
        else if (numChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        // Failed to load texture
        stbi_image_free(data);
        return 0;
    }

    return textureID;
}

unsigned int API_OpenGL::setupMesh(Mesh *mesh) {
    if (mesh->meshData->getIndices().empty()) {
        Debug::show("mRootMesh object has no indices");
        return 0;
    }
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->meshData->getVertices().size() * sizeof(glm::vec3),
                 &mesh->meshData->getVertices()[0], GL_STATIC_DRAW);
    auto stride = sizeof(glm::vec3);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

// Bind and set UVs
    unsigned int uvVBO;
    glGenBuffers(1, &uvVBO);
    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->meshData->getUVs().size() * sizeof(glm::vec2), &mesh->meshData->getUVs()[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *) 0);
    glEnableVertexAttribArray(1);

    // Bind and set Normals
    unsigned int normalVBO;
    glGenBuffers(1, &normalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->meshData->getNormals().size() * sizeof(glm::vec3),
                 &mesh->meshData->getNormals()[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *) 0);
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->meshData->getIndices().size() * sizeof(unsigned int),
                 &mesh->meshData->getIndices()[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    return VAO;
}

GLuint API_OpenGL::setupTerrain(HeightMap *heightmap) {
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, heightmap->vertices.size() * sizeof(float), &heightmap->vertices[0],
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, heightmap->indices.size() * sizeof(unsigned int), &heightmap->indices[0],
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    return VAO;
}

unsigned int API_OpenGL::getFlag(GraphicsFlag flag) {
    switch (flag) {
        case CULL_FACE:
            return GL_CULL_FACE;
        case DEPTH_TEST:
            return GL_DEPTH_TEST;
        case CLEAR_DEPTH_BUFFER:
            return GL_DEPTH_BUFFER_BIT;
        case CLEAR_COLOUR_BUFFER:
            return GL_COLOR_BUFFER_BIT;
        case ALPHA_BLENDING:
            return GL_BLEND;
        default:
            return 0;
    }
}

void API_OpenGL::shaderSetMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(currentRenderingConfig->shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void API_OpenGL::shaderSetVec3(const std::string &name, const glm::vec3 &vector) const {
    glUniform3f(glGetUniformLocation(currentRenderingConfig->shaderID, name.c_str()), vector.x, vector.y, vector.z);
}

void API_OpenGL::shaderSetFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(currentRenderingConfig->shaderID, name.c_str()), value);
}

void API_OpenGL::shaderSetVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4f(glGetUniformLocation(currentRenderingConfig->shaderID, name.c_str()), value.x, value.y, value.z,
                value.w);
}

void API_OpenGL::shaderSetBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(currentRenderingConfig->shaderID, name.c_str()), (int) value);
}

void API_OpenGL::shaderSetInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(currentRenderingConfig->shaderID, name.c_str()), value);
}

void API_OpenGL::shaderSetVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2f(glGetUniformLocation(currentRenderingConfig->shaderID, name.c_str()), value.x, value.y);
}

void API_OpenGL::shaderSetMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(currentRenderingConfig->shaderID, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(mat));
}

void API_OpenGL::shaderSetMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(currentRenderingConfig->shaderID, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(mat));
}

void API_OpenGL::shaderSetMaterial(Material material) const {
    shaderSetVec3("material.ambientColor", material.getAmbientColor());
//    shaderSetVec3("material.diffuseColor", material.getDiffuseColor());
    shaderSetVec3("material.specularColor", material.getSpecularColor());
    shaderSetFloat("material.shininess", material.getShininess());

    // here we need to activate the textures
    unsigned int textureID = material.getDiffuseTexture();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    shaderSetInt("material.diffuseTexture", 0);

    textureID = material.getNormalTexture();
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureID);
    shaderSetInt("material.normalTexture", 1);
}

void API_OpenGL::shaderSetTransform(const glm::mat4 &mat) const {
    shaderSetMat4("transform", mat);
}

void API_OpenGL::shaderSetView(const glm::mat4 &mat) const {
    shaderSetMat4("view", mat);
}

void API_OpenGL::shaderSetProjection(const glm::mat4 &mat) const {
    shaderSetMat4("projection", mat);
}

void API_OpenGL::shaderSetCamera(Camera *camera) {
    shaderSetVec3("camera", camera->getLocalPosition());
}

void API_OpenGL::readColourBufferRBGA(unsigned char *data, float x, float y, float width, float height) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void API_OpenGL::readDepthBuffer(float *data, float x, float y, float width, float height) {
    glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, data);
}

void API_OpenGL::flushBuffers() {
    glFlush();
    glFinish();
}

void API_OpenGL::setCapabilities() {
    capabilities.gpuName = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &capabilities.maxTextureUnits);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &capabilities.maxResolutionX);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &capabilities.maxResolutionY);
//    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &capabilities.maxAnisotropy);
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &capabilities.maxRenderTargets);
    glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &capabilities.maxUniformBufferBindings);
}



