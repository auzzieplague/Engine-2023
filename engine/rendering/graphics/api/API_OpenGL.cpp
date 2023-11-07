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

    const GLchar* sourceCStr = shader->source.c_str();
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

    glLinkProgram (program->programID);
    return program->programID;
}

// should be able to be promoted to parent class to render triangle agnostically
void API_OpenGL::demoTriangle(...) {
    // Define the vertices for a triangle

    auto meshData = this->getSampleMeshData();
    auto VAO = (new BufferObject())->generate()->bind();
    auto VBO = (new VertexBuffer(meshData->m_vertices.data(),meshData->m_vertices.size()*3, "static"))->generate()->bind();
    auto EBO = (new IndexBuffer (meshData->m_indices.data(),meshData->m_indices.size(),"static"))->generate()->bind();

    auto layout1 = new GPULayout(0);
    layout1->applyTo(VAO);

    auto * program = new ShaderProgram();

    // todo load from source, shader program might also load all source with the same name
    auto * vertexShader = new Shader(VERTEX_SHADER);
    vertexShader->loadFromSource("general");

    auto fragmentShader = new Shader(FRAGMENT_SHADER);
    fragmentShader->loadFromSource("general");
    program->addShader(fragmentShader)->addShader(vertexShader)->compileAndLink()->use();


    auto target = new RenderTarget(800,800);
    target->makeCurrent();
    target->setClearColour({0,0,0,0});
    // create render target
    // apply to window
    // add -> clear method
    // will have to initialise with GL_TEXTURE_2D for opengl
    // might be starting with rendering to texture :D

    //^ need to implement texture first
    // texture is used as render target.
    auto window = Window::getCurrentWindow();

    // Rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screens
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle using indices
        program->use();
        VAO->bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup (release resources) should be done when you're done with the OpenGL context
    glDeleteVertexArrays(1, &VAO->bufferID);
    glDeleteBuffers(1, &VBO->bufferID); // make cleanup method / destructor
    glDeleteBuffers(1, &EBO->bufferID);
    glDeleteShader(vertexShader->shaderID);
    glDeleteShader(fragmentShader->shaderID);
    glDeleteProgram(program->programID);

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
    glGenBuffers(1, &fbo->bufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->bufferID);

    // apply framebuffers width and hieght to a new texture
    fbo->texture = new Texture(fbo->width, fbo->height, GL_RGB);
    fbo->texture->generate();

    // Attach the texture to the FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo->texture->textureId, 0);

    // Unbind the FBO for now
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return GraphicsBehaviour::createFrameBuffer(fbo);
}

void API_OpenGL::createTexture(Texture *texture) {

     int format =  texture->format ? texture->format : GL_RGB;
     int width =  texture->width ? texture->width : 512;
     int height =  texture->height ? texture->height : 512;

    // Create the texture to render to
    glGenTextures(1, &texture->textureId);
    glBindTexture(GL_TEXTURE_2D, texture->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

    //todo get filter by type
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}



