#include <glad/glad.h>
#include "API_OpenGL.h"
#include <Window.h>
#include <graphics/VertexAttribute.h>
#include <chrono>
#include "graphics/buffers/VertexBuffer.h"
#include "graphics/buffers/IndexBuffer.h"
#include "graphics/buffers/FrameBuffer.h"
#include "graphics/buffers/BufferContainer.h"


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

bool API_OpenGL::isExtensionSupported(const char *extensionName) {
    if (glfwExtensionSupported(extensionName)) {
        return true;
    } else {
        return false;
    }
}

bool API_OpenGL::initialise(...) {
    if (this->initialised) {
        return true;
    }
//    this->fullScreenQuad = this->getFullScreenQuadMeshData();
//    this->allocateMeshData(fullScreenQuad);
    this->initialised = true;
    return true;
}



unsigned int API_OpenGL::createContainerObject(BufferContainer *bo) {
    glGenVertexArrays(1, &bo->bufferID); // Generate the Vertex Array Object
    glBindVertexArray(bo->bufferID); // Bind the VAO

    // todo need to order by index - setAsPositions etc needs to set a type
    for (auto &attributePair : bo->attributes) {
        VertexAttribute *attribute = attributePair.second;
        unsigned int vbo;

        glGenBuffers(1, &vbo); // Generate a new VBO
        glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind the VBOS
        glBufferData(GL_ARRAY_BUFFER, attribute->vertexType * attribute->byteSize, attribute->pointer, GL_STATIC_DRAW ); // Upload the data to the VBO

        glEnableVertexAttribArray(attribute->index); // Enable the vertex attribute array
        glVertexAttribPointer(
                attribute->index,           // Attribute index
                attribute->vertexType,        // Number of components per vertex attribute
                attribute->dataType,            // Data type of each component
                attribute->normalised,      // Normalization flag
                0,                       // Stride (0 for tightly packed data)
                reinterpret_cast<void*>(0) // Offset (0 for the start of the buffer)
        );

        glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO // todo - move outside loop ?
    }

    glBindVertexArray(0); // Unbind the VAO

    return bo->bufferID; // Return the ID of the created VAO
}


MeshData *API_OpenGL::allocateMeshData(MeshData *meshData) {
    auto VAO = (new BufferContainer());

    // todo apply layout options before creating VBO - VBO will need to contain all attribs
    // todo ^ GPU layout populated with data to use for VBO in vertex array creation

    auto layout0 = (new VertexAttribute(0))->setAsPositions3D(meshData->m_vertices.data())->applyTo(VAO);
    auto layout1 = (new VertexAttribute(1))->setAsTexture2D(meshData->m_UVs.data())->applyTo(VAO);

    VAO->generate();
    VAO->forMeshData(meshData);
    VAO->bind();

//    auto VBO = (new VertexBuffer(VAO,meshData,"static"))->generate()->bind();
// todo maybe the IndexBuffer should just be another vertex attribute, although we treat it different under the hood.

    auto EBO = (new IndexBuffer(VAO, meshData,"static"))->generate()->bind();

//    auto layout0 = (new GPULayout(0))->applyTo(VAO);
//    auto layout1 = (new GPULayout(1))->basicTexture()->applyTo(VAO);

    // todo - better store pointers for cleanup - some general internal mechanic
    this->containerObjects.push_back(VAO);
//    this->vertexBuffers.push_back(VBO);
    this->indexBuffers.push_back(EBO);
    this->gpuLayouts.push_back(layout0);
    this->gpuLayouts.push_back(layout1);

    return meshData;
}

unsigned int API_OpenGL::createVertexBuffer(VertexBuffer *vb) {
return 0;
}

void API_OpenGL::bindVertexBuffer(VertexBuffer *vb) {
    glBindBuffer(GL_ARRAY_BUFFER, vb->bufferID);
    glBufferData(GL_ARRAY_BUFFER, vb->byteCount, vb->data, vb->usage);
}


unsigned int API_OpenGL::createIndexBuffer(IndexBuffer *ib) {
    glGenBuffers(1, &ib->bufferID); // Generate the OpenGL buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->bufferID); // Bind the buffer to the GL_ELEMENT_ARRAY_BUFFER target
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib->byteCount, ib->data, ib->usage); // Upload the data to the buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the buffer

    return ib->bufferID; // Return the ID of the created buffer
}

void API_OpenGL::bindIndexBuffer(IndexBuffer *ib) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib->byteCount, ib->data, ib->usage);
}



void API_OpenGL::bindContainerObject(BufferContainer *bo) {
    glBindVertexArray(bo->bufferID);
}

void API_OpenGL::compileShader(Shader *shader) {
    //todo make a type map or method to lookup type
    switch (shader->type) {
        case VERTEX_SHADER:
            shader->shaderID = glCreateShader(GL_VERTEX_SHADER);
            break;
        case FRAGMENT_SHADER:
            shader->shaderID = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }

    const GLchar *sourceCStr = shader->source.c_str();
    glShaderSource(shader->shaderID, 1, &sourceCStr, NULL);
    glCompileShader(shader->shaderID);

}

void API_OpenGL::useShaderProgram(ShaderProgram *program) {
    glUseProgram(program->programID);
}

unsigned int API_OpenGL::linkShaderProgram(ShaderProgram *program) {

    program->programID = glCreateProgram();

    for (auto shader: program->shaders) {
        if (!shader->compiled) {
            shader->compile();
        }

        glAttachShader(program->programID, shader->shaderID);
    }

    glLinkProgram(program->programID);
    return program->programID;
}


void API_OpenGL::updateCurrentTime() {
    using namespace std::chrono;

    // Get the current time point
    auto now = high_resolution_clock::now();

    // Get the time since epoch in milliseconds
    auto timeSinceEpoch = duration_cast<milliseconds>(now.time_since_epoch());

    // Convert to seconds as a float
    this->currentTime = timeSinceEpoch.count() / 1000.0f;

}

 void checkGlErrors() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::string error;

        switch (err) {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default:                               error = "UNKNOWN_ERROR"; break;
        }

        std::cerr << "GL_" << error << std::endl;
    }
}

// should be able to be promoted to parent class to render triangle agnostically
void API_OpenGL::demoTriangle(...) {
    // Define the vertices for a triangle
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, // Bottom-left corner
            0.5f, -0.5f, 0.0f, // Bottom-right corner
            0.0f,  0.5f, 0.0f  // Top center
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and bind a vertex buffer object (VBO)
    GLuint VBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile vertex and fragment shaders
    const char* vertexShaderSource = "#version 330 core\n"
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

    const char* fragmentShaderSource = "#version 330 core\n"
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    auto window = Window::getCurrentWindow();

    // Rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup (release resources) should be done when you're done with the OpenGL context
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();
}

// should be able to be promoted to parent class to render triangle agnostically
void API_OpenGL::demoTriangle2(...) {
    auto lightingShader = (new ShaderProgram())
            ->addShader((new Shader(FRAGMENT_SHADER))->loadFromSource("general"))
            ->addShader( (new Shader(VERTEX_SHADER))->loadFromSource("general"))
            ->compileAndLink()
            ->use();

//    this->quadShader = (new ShaderProgram())
//            ->addShader((new Shader(FRAGMENT_SHADER))->loadFromSource("quad"))
//            ->addShader( (new Shader(VERTEX_SHADER))->loadFromSource("quad"))
//            ->compileAndLink()
//            ->use();

    auto target = (new RenderTarget(800, 800))->setClearColour({0, 0, 0, 0});
    auto window = Window::getCurrentWindow();

    // todo create an allocateMeshData function that does this and returns the setup mesh
    auto meshData = this->getSampleMeshData();

    this->allocateMeshData(meshData);
    std::vector<MeshData *> meshDataList;


    meshDataList.push_back(meshData);

    // Rendering things to current target
    while (!glfwWindowShouldClose(window)) {

        lightingShader->use();
//        target->bind(); // bind and use frame buffer 1 - should be rendering to texture
        target->clearColourBuffer();
        target->renderMeshes(meshDataList);

//        target->finalRender();
// switch back to main buffer

        // render quad to screen, draw current render target texture on quad
        glfwSwapBuffers(window);
        glfwPollEvents();
        checkGlErrors();
    }

    //cleanup
    {
        //todo add shaders to cleanup - will have to internally add something to manage the pointers
//        glDeleteShader(vertexShader->shaderID);
//        glDeleteShader(fragmentShader->shaderID);
//        glDeleteProgram(lightingShade->programID);
    }

    // Terminate GLFW
    glfwTerminate();
}

void API_OpenGL::finalRender(RenderTarget *renderTarget) {
    quadShader->use(); // switch to quad shader
    // Retrieve the location of the uniform variables
    glUniform1i(glGetUniformLocation(quadShader->programID, "screenTexture"), 0); // Set screenTexture uniform to texture unit 0
    glUniform3f(glGetUniformLocation(quadShader->programID, "colour"), 1,1,0); // Set screenTexture uniform to texture unit 0

    // switch back to main buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Bind the texture to texture unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderTarget->frameBuffer->texture->textureId);


    this->fullScreenQuad->bufferContainer->bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

}

void API_OpenGL::renderTargetDrawMeshData(RenderTarget *renderTarget, std::vector<MeshData *> meshDataList) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    for (auto meshData: meshDataList) {
        // bind the buffer object containing the vertices / indices etcs and then transport to gfx memory
        meshData->bufferContainer->bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); // draw object
    }
}

void API_OpenGL::renderTargetClearDepthBuffer(RenderTarget *renderTarget) {
    glClear(GL_DEPTH_BUFFER_BIT);
}

void API_OpenGL::renderTargetBind(RenderTarget *renderTarget) {
    glBindFramebuffer(GL_FRAMEBUFFER, renderTarget->frameBuffer->bufferID);
}

void API_OpenGL::renderTargetClearColourBuffer(RenderTarget *renderTarget) {
    glClearColor(
            renderTarget->clearColour.x,
            renderTarget->clearColour.y,
            renderTarget->clearColour.z,
            renderTarget->clearColour.a
    );
    glClear(GL_COLOR_BUFFER_BIT);
}

unsigned int API_OpenGL::getFlagCode(const char *string) {
    static std::map<std::string, unsigned int> flagMap = {
            {"static",  GL_STATIC_DRAW},
            {"dynamic", GL_DYNAMIC_DRAW},
            {"stream",  GL_STREAM_DRAW},
            // Add more mappings here
    };

    // todo return flagmap[string] ?? null - trap exception or something.
    auto it = flagMap.find(string);
    if (it != flagMap.end()) {
        return it->second;
    } else {
        return 0;
    }
}

void API_OpenGL::applyAttribute(VertexAttribute *layout) {
    layout->applyToBuffer->addLayout(layout);
}

unsigned int API_OpenGL::createFrameBuffer(FrameBuffer *fbo) {
    glGenFramebuffers(1, &fbo->bufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->bufferID);

    fbo->texture = new Texture(fbo->width, fbo->height, GL_RGB);
    fbo->texture->generate();

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo->texture->textureId, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        return 0;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return fbo->bufferID;
}

void API_OpenGL::createTexture(Texture *texture) {
    int format = texture->format ? texture->format : GL_RGB;
    int width = texture->width ? texture->width : 512;
    int height = texture->height ? texture->height : 512;

    glGenTextures(1, &texture->textureId);
    glBindTexture(GL_TEXTURE_2D, texture->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
}

void API_OpenGL::cleanupResources() {

    // todo actually can put all the pointers into a single list - at least most of them

    for (auto *containerObject: containerObjects) {
        glDeleteBuffers(1, &containerObject->bufferID);
        delete containerObject;
    }
    containerObjects.clear();

    // Delete IndexBuffers
    for (auto *indexBuffer: indexBuffers) {
        glDeleteBuffers(1, &indexBuffer->bufferID);
        delete indexBuffer;
    }
    indexBuffers.clear();

    // Delete VertexBuffers
    for (auto *vertexBuffer: vertexBuffers) {
        glDeleteBuffers(1, &vertexBuffer->bufferID);
        delete vertexBuffer;
    }
    vertexBuffers.clear();

    // Delete FrameBuffers
    for (auto *frameBuffer: frameBuffers) {
        glDeleteFramebuffers(1, &frameBuffer->bufferID);
        // If there's a texture attached to the framebuffer, delete it
        if (frameBuffer->texture && frameBuffer->texture->textureId != 0) {
            glDeleteTextures(1, &frameBuffer->texture->textureId);
            delete frameBuffer->texture;
        }
        delete frameBuffer;
    }
    frameBuffers.clear();

    // Delete GPULayouts
    // Assuming GPULayouts do not have a direct OpenGL deletion equivalent
    // and just need to be deleted normally.
    for (auto *gpuLayout: gpuLayouts) {
        delete gpuLayout;
    }
    gpuLayouts.clear();
}

std::string getGLErrorString(GLenum err) {
    switch (err) {
        case GL_NO_ERROR: return "No error";
        case GL_INVALID_ENUM: return "Invalid enum";
        case GL_INVALID_VALUE: return "Invalid value";
        case GL_INVALID_OPERATION: return "Invalid operation";
        case GL_STACK_OVERFLOW: return "Stack overflow";
        case GL_STACK_UNDERFLOW: return "Stack underflow";
        case GL_OUT_OF_MEMORY: return "Out of memory";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid framebuffer operation";
        default: return "Unknown error";
    }
}

void API_OpenGL::reportErrors() {
    GLenum errCode;
    std::string errString;

    // Loop until `glGetError` returns `GL_NO_ERROR`
    while ((errCode = glGetError()) != GL_NO_ERROR) {
        errString = getGLErrorString(errCode);
        std::cerr << "OpenGL Error: " << errString << " (0x" << std::hex << errCode << ")" << std::endl;
    }
}


