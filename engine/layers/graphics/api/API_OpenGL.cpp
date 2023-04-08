
#include "API_OpenGL.h"

//unsigned int API_OpenGL::shaderProgram;

void API_OpenGL::updateRendererConfig(RenderingConfig &config) {
    currentRenderingConfig = &config;
    glClearColor(config.clearColour.x, config.clearColour.y, config.clearColour.z, config.clearColour.w);
    glClear(config.clearFlags);

    if (config.toEnableFlags) {
        glEnable(config.toEnableFlags);
        config.toEnableFlags = 0;
    }

    if (config.toDisableFlags) {
        glDisable(config.toDisableFlags);
        config.toDisableFlags = 0;
    }

    if (config.debugMode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    glUseProgram(config.shaderID);
}

// unsigned int GraphicsLayerOpenGL::testMeshVAO;
void API_OpenGL::renderMesh(Mesh *mesh) {
    glBindVertexArray(mesh->gID);
//    glDrawArrays(GL_TRIANGLES, 0, 6);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
//    glDrawElements(GL_LINES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // no need to unbind it every time

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

unsigned int API_OpenGL::loadShader(std::string vertex, std::string fragment) {

    /// lookup paths in assetManager
    std::string vertexPath = AssetManager::getRelativePath("shaders_opengl", vertex);
    std::string vertexSource = AssetManager::stringFromFile(vertexPath);
    std::string fragmentPath = AssetManager::getRelativePath("shaders_opengl", fragment);
    std::string fragmentSource = AssetManager::stringFromFile(fragmentPath);

    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


unsigned int API_OpenGL::setupMesh(Mesh *mesh) {
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, mesh->positions.size() * sizeof(glm::vec3), &mesh->positions[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int), &mesh->indices[0],
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *) 0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

//    testMeshVAO=VAO;
    return VAO;
}


unsigned int API_OpenGL::getFlag(GraphicsFlag flag) {
    switch (flag) {
        case CULL_FACE:
            return GL_CULL_FACE;
        default:
            return 0;
    }
}

void API_OpenGL::shaderSetMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(currentRenderingConfig->shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}