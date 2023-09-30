#pragma once

//#include <d3d11.h>
//#include <dxgi.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <dxgi1_4.h> // Include DXGI version 1.4 for IDXGIFactory4
#include "GraphicsAPI.h"

/**
 * requires windows SDK for DirectX12
 * DirectX11 requires dxgi.lib
 */
class API_DirectX
    : public GraphicsAPI {
public:
    ID3D12Device* d3dDevice;
    ID3D12DeviceChild* d3dContext;
        bool initialise() override;
        void queryCapabilities() override;
//        void shutdown() override;
//        VertexBuffer createVertexBuffer(...) override;
//        IndexBuffer createIndexBuffer(...) override;
//        Texture loadTexture(...) override;
//        Mesh loadMesh(...) override;
//        Shader createShader(...) override;
//        void setShader(Shader shader) override;
//        void setUniform(...) override;
//        void bindTextureToShader(Texture texture, int textureUnit, const std::string& uniformName) override;
//        void setShaderParameters(...) override;
//        void renderMesh(Mesh mesh, ...) override;
//        void setRenderTarget(RenderTarget target) override;
//        void clearRenderTarget(...) override;
//        void beginFrame() override;
//        void endFrame() override;
//        void resizeViewport(...) override;
//
//        std::string getError() override;
//

};


