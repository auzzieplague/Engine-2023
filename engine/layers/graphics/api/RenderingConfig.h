#pragma once

struct RenderingConfig {
public:

    /*
     * some flags will only need to be enabled / disabled intermittently
     * these can be added to the enable/ disable queue this should keep things
     * a little more generalised. For openGl we can
     */
    std::vector<unsigned int> toEnable;
    unsigned int toEnableFlags = 0;
    std::vector<unsigned int> toDisable;
    unsigned int toDisableFlags = 0;

    unsigned int clearFlags = GL_COLOR_BUFFER_BIT;
    glm::vec4 clearColour{0.2f, 0.3f, 0.3f, 1.0};
    unsigned int shaderID;
    bool debugMode = true;

    /**
     * amalgamates all flag changes into next render cycle to minimise m_api calls
     * - if you need changes applied immediately use @see GraphicsAPI::updateRendererConfig()
     * @param flag
     */
    void enable(unsigned int flag) {
        toEnableFlags = toEnableFlags | flag;
        toEnable.push_back(flag);
    }

    void disable(unsigned int flag) {
        toDisableFlags = toDisableFlags | flag;
        toDisable.push_back(flag);
    }

    void setClearFlag(unsigned int flag) {
        clearFlags = clearFlags | flag;
    }

    void unsetClearFlag(unsigned int flag) {
        clearFlags = clearFlags & ~flag;
    }

    void setClearColour(const glm::vec4 &clearColour) {
        RenderingConfig::clearColour = clearColour;
    }
};
