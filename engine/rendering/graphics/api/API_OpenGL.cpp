#include <glad/glad.h>
#include "API_OpenGL.h"
#include <Window.h>
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../BufferObject.h"


void API_OpenGL::queryCapabilities(...) {
    if (this->gpuInfo == nullptr) {
        this->gpuInfo = new GPUInfo();
    }
    gpuInfo->model = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    gpuInfo->driverVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    gpuInfo->openGLVersionSupport = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &gpuInfo->maxTextureSize);
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &gpuInfo->maxRenderSize);
    glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &gpuInfo->maxAnisotropicFiltering);
    glGetIntegerv(GL_MAX_SAMPLES, &gpuInfo->maxMSAA);
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &gpuInfo->maxTextureUnits);
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &gpuInfo->maxVertexAttributes);
    glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &gpuInfo->maxUniformBindings);
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &gpuInfo->maxTextureImageUnits);
    glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES, &gpuInfo->maxGeometryOutputVertices);
    glGetIntegerv(GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS, &gpuInfo->maxGeometryOutputComponents);
    gpuInfo->tessellationSupport = isExtensionSupported("GL_ARB_tessellation_shader") != 0;
    gpuInfo->computeShaderSupport = isExtensionSupported("GL_ARB_compute_shader") != 0;
}

bool API_OpenGL::isExtensionSupported(const char *extensionName){
    if (glfwExtensionSupported(extensionName)) {
        return true;
    } else {
        return false;
    }
}

bool API_OpenGL::initialise(...) {
    // initialise opengl context
    return true;
}


unsigned int API_OpenGL::createVertexBuffer( VertexBuffer* vb) {
    glGenBuffers(1, &vb->bufferID); // Generate the OpenGL buffer
    glBindBuffer(GL_ARRAY_BUFFER, vb->bufferID); // Bind the buffer to the GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, vb->dataSize, vb->data, vb->usage); // Upload the data to the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the buffer

    return vb->bufferID; // Return the ID of the created buffer
}

void API_OpenGL::bindVertexBuffer(VertexBuffer *vb) {
    glBindBuffer(GL_ARRAY_BUFFER, vb->bufferID);
    glBufferData(GL_ARRAY_BUFFER, vb->dataSize, vb->data, vb->usage);
}


unsigned int API_OpenGL::createIndexBuffer(IndexBuffer *ib) {
    glGenBuffers(1, &ib->bufferID); // Generate the OpenGL buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->bufferID); // Bind the buffer to the GL_ELEMENT_ARRAY_BUFFER target
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib->dataSize, ib->data, ib->usage); // Upload the data to the buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the buffer

    return ib->bufferID; // Return the ID of the created buffer
}

void API_OpenGL::bindIndexBuffer(IndexBuffer *ib) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib->dataSize, ib->data, ib->usage);
}


unsigned int API_OpenGL::createBufferObject(BufferObject *bo) {
    glGenVertexArrays(1, &bo->bufferID); // Generate the OpenGL buffer
    return bo->bufferID; // Return the ID of the created buffer
}

void API_OpenGL::bindBufferObject(BufferObject *bo) {
    glBindVertexArray(bo->bufferID);
}

// should be able to be promoted to parent class to render triangle agnostically
void API_OpenGL::demoTriangle(...) {
    // Define the vertices for a triangle
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, // Bottom-left corner
            0.5f, -0.5f, 0.0f, // Bottom-right corner
            0.0f, 0.5f, 0.0f, // Top center
    };

    // Define the indices to create triangles
    unsigned int indices[] = {
            0, 1, 2 // Indices for the vertices that make up the triangle
    };

//    GLuint VAO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//    glBindVertexArray(VAO);

    BufferObject VAO;
    VAO.generate()->bind();

    VertexBuffer VBO(vertices, sizeof(vertices), "static");
    VBO.generate()->bind();

    IndexBuffer EBO(indices, sizeof(indices),"static");
    EBO.generate()->bind();



    // Bind and initialize the element buffer (indices)
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//    reate and compile vertex and fragment shaders
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for shader compilation errors (you should add error checking here)

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for shader compilation errors (you should add error checking here)

    // Create and link a shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for shader program linking errors (you should add error checking here)

    // Use the shader program
    glUseProgram(shaderProgram);


    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    auto window = Window::getCurrentWindow();

    // Rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle using indices
        glUseProgram(shaderProgram);
        VAO.bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup (release resources) should be done when you're done with the OpenGL context
    glDeleteVertexArrays(1, &VAO.bufferID);
    glDeleteBuffers(1, &VBO.bufferID); // make cleanup method / destructor
    glDeleteBuffers(1, &EBO.bufferID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();
}

/**
 * We will replace each piece of this demo triangle with the new methodology
 */
void API_OpenGL::demoTriangleRaw() {
    // Define the vertices for a triangle
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, // Bottom-left corner
            0.5f, -0.5f, 0.0f, // Bottom-right corner
            0.0f, 0.5f, 0.0f, // Top center
    };

    // Define the indices to create triangles
    unsigned int indices[] = {
            0, 1, 2 // Indices for the vertices that make up the triangle
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Bind and initialize the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and initialize the element buffer (indices)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//    reate and compile vertex and fragment shaders
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for shader compilation errors (you should add error checking here)

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for shader compilation errors (you should add error checking here)

    // Create and link a shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for shader program linking errors (you should add error checking here)

    // Use the shader program
    glUseProgram(shaderProgram);


    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    auto window = Window::getCurrentWindow();

    // Rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle using indices
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup (release resources) should be done when you're done with the OpenGL context
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();
}

unsigned int API_OpenGL::getFlagCode(const char *string) {
    static std::map<std::string, unsigned int> flagMap = {
            {"static",  GL_STATIC_DRAW},
            {"dynamic", GL_DYNAMIC_DRAW},
            {"stream",  GL_STREAM_DRAW},
            // Add more mappings here
    };

    auto it = flagMap.find(string);
    if (it != flagMap.end()) {
        return it->second;
    } else {
        return 0;
    }
}


