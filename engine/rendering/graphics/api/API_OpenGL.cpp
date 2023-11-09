#include <glad/glad.h>
#include "API_OpenGL.h"
#include <Window.h>
#include <graphics/GPULayout.h>
#include "graphics/buffers/VertexBuffer.h"
#include "graphics/buffers/IndexBuffer.h"
#include "graphics/buffers/FrameBuffer.h"
#include "graphics/buffers/BufferObject.h"


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
    this->initialised = true;
    return true;
}


unsigned int API_OpenGL::createVertexBuffer(VertexBuffer *vb) {
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

MeshData *API_OpenGL::allocateMeshData(MeshData *meshData) {
    auto VAO = (new BufferObject());
            VAO->generate();
            VAO->forMeshData(meshData);
            VAO->bind(); // forMeshData binds to mesh
    auto VBO = (new VertexBuffer(meshData->m_vertices.data(), meshData->m_vertices.size() * 3,
                                 "static"))->generate()->bind();
    auto EBO = (new IndexBuffer(meshData->m_indices.data(), meshData->m_indices.size(), "static"))->generate()->bind();

    auto layout1 = new GPULayout(0);
    layout1->applyTo(VAO);

    // todo - better store pointers for cleanup - some general internal mechanic
    this->bufferObjects.push_back(VAO);
    this->vertexBuffers.push_back(VBO);
    this->indexBuffers.push_back(EBO);
    this->gpuLayouts.push_back(layout1);

    return meshData;
}

// should be able to be promoted to parent class to render triangle agnostically
void API_OpenGL::demoTriangle(...) {
    // todo create an allocateMeshData function that does this and returns the setup mesh
    auto meshData = this->getSampleMeshData();
//    auto meshData = this->getFullScreenQuadMeshData();
    this->allocateMeshData(meshData);
    // todo load from source, shader program might also load all source with the same name
//    auto vertexShader = (new Shader(VERTEX_SHADER))->loadFromSource("general");
//    auto fragmentShader = (new Shader(FRAGMENT_SHADER))->loadFromSource("general");
//    auto lightingShader = (new ShaderProgram())->addShader(fragmentShader)->addShader(
//            vertexShader)->compileAndLink()->use();
//    auto quadShader = (new ShaderProgram())->addShader(fragmentShader)->addShader(
//            vertexShader)->compileAndLink()->use();

    auto lightingShader = (new ShaderProgram())
            ->addShader((new Shader(FRAGMENT_SHADER))->loadFromSource("general"))
            ->addShader( (new Shader(VERTEX_SHADER))->loadFromSource("general"))
            ->compileAndLink()
            ->use();

    this->quadShader = (new ShaderProgram())
            ->addShader((new Shader(FRAGMENT_SHADER))->loadFromSource("quad"))
            ->addShader( (new Shader(VERTEX_SHADER))->loadFromSource("quad"))
            ->compileAndLink()
            ->use();


    // ^ in reality quad shader is much simpler than rendering shader

    auto target = (new RenderTarget(800, 800))->setClearColour({0, 0, 0, 0});

    auto window = Window::getCurrentWindow();
    std::vector<MeshData *> meshDataList;
    meshDataList.push_back(meshData);

    // Rendering things to current target
    while (!glfwWindowShouldClose(window)) {
        lightingShader->use();
//        target->bind();
        target->clearColourBuffer();
        // would actually take a list of meshes not mesh data so it can pass transforms, materials etc to shader etc
        target->renderMeshes(meshDataList);

        target->finalRender();

        // render quad to screen, draw current render target texture on quad
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
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
    GLint screenTextureLocation = glGetUniformLocation(quadShader->programID, "screenTexture");
    GLint timeLocation = glGetUniformLocation(quadShader->programID, "time");

    // switch back to main buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Bind the texture to texture unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderTarget->frameBuffer->texture->textureId);


    this->fullScreenQuad->bufferObject->bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

}

void API_OpenGL::renderTargetDrawMeshData(RenderTarget *renderTarget, std::vector<MeshData *> meshDataList) {
    for (auto meshData: meshDataList) {
        // bind the buffer object containing the vertices / indices etcs and then transport to gfx memory
        meshData->bufferObject->bind();
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

void API_OpenGL::applyLayout(GPULayout *layout) {
    glEnableVertexAttribArray(layout->applyToBuffer->bufferID);

    glVertexAttribPointer(layout->index,
                          layout->size,
                          layout->type,
                          layout->normalised,
                          layout->stride,
                          layout->pointer);

    layout->applyToBuffer->addLayout(layout);
    glEnableVertexAttribArray(0);
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

    // Delete BufferObjects
    for (auto *bufferObject: bufferObjects) {
        glDeleteBuffers(1, &bufferObject->bufferID);
        delete bufferObject;
    }
    bufferObjects.clear();

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


