
#include "API_OpenGL.h"

void API_OpenGL::queryCapabilities() {;
    if (this->gpuInfo == nullptr) {
        this->gpuInfo = new GPUInfo();
    }

    // Get GPU model and vendor
    gpuInfo->model = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    gpuInfo->driverVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));

    // Get OpenGL version support
    gpuInfo->openGLVersionSupport = reinterpret_cast<const char *>(glGetString(GL_VERSION));

    // Get maximum texture size
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &gpuInfo->maxTextureSize);

    // Get maximum render target size
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &gpuInfo->maxRenderSize);

    // Get maximum anisotropic filtering level
    glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &gpuInfo->maxAnisotropicFiltering);

    // Get maximum MSAA level
    glGetIntegerv(GL_MAX_SAMPLES, &gpuInfo->maxMSAA);

    // Get maximum texture units
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &gpuInfo->maxTextureUnits);

    // Get maximum vertex attributes
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &gpuInfo->maxVertexAttributes);

    // Get maximum uniform buffer bindings
    glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &gpuInfo->maxUniformBindings);

    // Get maximum texture image units
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &gpuInfo->maxTextureImageUnits);

    // Get maximum geometry shader output vertices
    glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES, &gpuInfo->maxGeometryOutputVertices);

    // Get maximum geometry shader output components
    glGetIntegerv(GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS, &gpuInfo->maxGeometryOutputComponents);

    // Check for tessellation support
    gpuInfo->tessellationSupport = isExtensionSupported("GL_ARB_tessellation_shader") != 0;

    // Check for compute shader support
    gpuInfo->computeShaderSupport = isExtensionSupported("GL_ARB_compute_shader") != 0;
}


bool API_OpenGL::isExtensionSupported(const char *extensionName){
    if (glfwExtensionSupported(extensionName)) {
        std::cout << "Extension '" << extensionName << "' is supported." << std::endl;
        return true;
    } else {
        std::cout << "Extension '" << extensionName << "' is not supported." << std::endl;
        return false;
    }
}