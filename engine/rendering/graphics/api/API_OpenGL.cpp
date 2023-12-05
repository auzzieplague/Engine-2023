#include <glad/glad.h>
#include "API_OpenGL.h"
#include <Window.h>
#include <chrono>
#include "graphics/buffers/FrameBuffer.h"
#include "OpenGLReferenceObject.h"


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
    this->fullScreenQuad = this->getFullScreenQuadMeshData();
    this->allocateMeshData(fullScreenQuad);

    /// set initial size to current window size
    auto window = Window::getCurrentWindow();
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    mainRenderTarget = new RenderTarget(width, height);

    this->quadShader = (new ShaderProgram())
            ->addShader((new Shader(FRAGMENT_SHADER))->loadFromSource("quad"))
            ->addShader((new Shader(VERTEX_SHADER))->loadFromSource("quad"))
            ->compileAndLink()
            ->use();

    this->initialised = true;
    return true;
}


MeshData *API_OpenGL::allocateMeshData(MeshData *meshData) {
    auto giro = new OpenGLReferenceObject();

    meshData->giro = giro;
    glGenVertexArrays(1, &giro->VAO); // Generate the Vertex Array Object
    glBindVertexArray(giro->VAO); // Bind the VAO

    unsigned int vbo;
    glGenBuffers(1, &vbo); // Generate a new VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind the VBOS

    // positions
    auto size = meshData->m_vertices.size() *
                sizeof(meshData->m_vertices[0]); // itemcount x 3 for vector x sizeof (float) for total bytes
    glBufferData(GL_ARRAY_BUFFER, size, meshData->m_vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

    // uvs
    if (meshData->m_UVs.size() > 0) {
        unsigned int vbo2;
        glGenBuffers(1, &vbo2); // Generate a new VBO
        glBindBuffer(GL_ARRAY_BUFFER, vbo2); // Bind the VBOS
        auto sizeUV = meshData->m_UVs.size() *
                      sizeof(meshData->m_UVs[0]); // itemcount x 2 for vector x sizeof (float) for total bytes
        glBufferData(GL_ARRAY_BUFFER, sizeUV, meshData->m_UVs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
    }

    // if we have an indices generate an index buffer - set the flags accordingly
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    size = meshData->m_indices.size() * sizeof(meshData->m_indices[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, meshData->m_indices.data(), GL_STATIC_DRAW);


    //todo set flags based on presence of items, then we can use the bitmask to select the correct shader (or subroutines)

    // Enable vertex attribute arrays
    glEnableVertexAttribArray(0); // position
    glEnableVertexAttribArray(1); // UVs

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return meshData;
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

    GLint success;
    GLchar infoLog[512];
    program->programID = glCreateProgram();

    for (auto shader: program->shaders) {
        if (!shader->compiled) {
            shader->compile();
            // Check shader compilation
            glGetShaderiv(shader->shaderID, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader->shaderID, 512, NULL, infoLog);
                std::cerr << "Shader compilation failed: " << infoLog << std::endl;
                return 0;
            }

        }

        glAttachShader(program->programID, shader->shaderID);
    }

    glLinkProgram(program->programID);

    glGetProgramiv(program->programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program->programID, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        return 0;
    }

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
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                error = "STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                error = "STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
            default:
                error = "UNKNOWN_ERROR";
                break;
        }

        std::cerr << "GL_" << error << std::endl;
    }
}

// should be able to be promoted to parent class to render triangle agnostically
void API_OpenGL::demoTriangle(...) {

    auto lightingShader = (new ShaderProgram())
            ->addShader((new Shader(FRAGMENT_SHADER))->loadFromSource("general"))
            ->addShader((new Shader(VERTEX_SHADER))->loadFromSource("general"))
            ->compileAndLink()
            ->use();

    auto meshData = this->getSampleMeshData();
    this->allocateMeshData(meshData);

    auto window = Window::getCurrentWindow();
    int width, height;
    glfwGetWindowSize(window, &width, &height);

//    auto target = new RenderTarget(512, 512);
//    target->setClearColour({0, 0, 0, 0});


    // Rendering loop
    while (!glfwWindowShouldClose(window)) {

        lightingShader->use(); // shader is good!
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // clear colour order doesn't matter
        glClear(GL_COLOR_BUFFER_BIT);
        //target->clear();

        glBindFramebuffer(GL_FRAMEBUFFER, mainRenderTarget->frameBuffer->bufferID); // bind target
        glBindVertexArray(dynamic_cast<OpenGLReferenceObject *>(meshData->giro)->VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glUseProgram(0);


        quadShader->use(); ///testing - output full screen quad using demo quad with uvs
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // clear colour order doesn't matter
//        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mainRenderTarget->frameBuffer->texture->textureId);
        glUniform1i(glGetUniformLocation(quadShader->programID, "screenTexture"), 0);


        glBindVertexArray(
                dynamic_cast<OpenGLReferenceObject *>(this->fullScreenQuad->giro)->VAO); // todo remove quad data
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup (release resources) should be done when you're done with the OpenGL context
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);

    // Terminate GLFW
    glfwTerminate();
    exit(0);
}


void API_OpenGL::finalRender(RenderTarget *renderTarget) {
    quadShader->use(); // switch to quad shader
    // Retrieve the location of the uniform variables
    glUniform1i(glGetUniformLocation(quadShader->programID, "screenTexture"),
                0); // Set screenTexture uniform to texture unit 0
    glUniform3f(glGetUniformLocation(quadShader->programID, "colour"), 1, 1,
                0); // Set screenTexture uniform to texture unit 0

    // switch back to main buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Bind the texture to texture unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderTarget->frameBuffer->texture->textureId);


//    this->fullScreenQuad->bufferContainer->bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

}

void API_OpenGL::renderTargetDrawMeshData(RenderTarget *renderTarget, std::vector<MeshData *> meshDataList) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    for (auto meshData: meshDataList) {
        // bind the buffer object containing the vertices / indices etcs and then transport to gfx memory
//        meshData->bufferContainer->bind();
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

void API_OpenGL::resetFrameBuffer(FrameBuffer *fbo, int width, int height) {
    // Delete existing texture and framebuffer
    glDeleteTextures(1, &fbo->texture->textureId); // need to get framebuffer
    glDeleteFramebuffers(1, &fbo->bufferID);
    fbo->width = width;
    fbo->height = height;
    createFrameBuffer(fbo);
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

}

std::string getGLErrorString(GLenum err) {
    switch (err) {
        case GL_NO_ERROR:
            return "No error";
        case GL_INVALID_ENUM:
            return "Invalid enum";
        case GL_INVALID_VALUE:
            return "Invalid value";
        case GL_INVALID_OPERATION:
            return "Invalid operation";
        case GL_STACK_OVERFLOW:
            return "Stack overflow";
        case GL_STACK_UNDERFLOW:
            return "Stack underflow";
        case GL_OUT_OF_MEMORY:
            return "Out of memory";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "Invalid framebuffer operation";
        default:
            return "Unknown error";
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

void API_OpenGL::resizeViewport(int width, int height, ...) {
    va_list args;
    va_start(args, height);
    GLFWwindow* window = va_arg(args,GLFWwindow *);
    va_end(args);


    glViewport(0, 0, width, height);

    // resize framebuffer

    mainRenderTarget->resetFrameBuffer(width,height);
    // todo make a resetFrameBufferMethod on renderTarget
    // Delete existing texture and framebuffer
//    glDeleteTextures(1, &mainRenderTarget->frameBuffer->texture->textureId); // need to get framebuffer
//    glDeleteFramebuffers(1, &mainRenderTarget->frameBuffer->bufferID);
//    mainRenderTarget->frameBuffer->width = width;
//    mainRenderTarget->frameBuffer->height = height;
//    createFrameBuffer(mainRenderTarget->frameBuffer);

}


