#pragma once

//#include <d3d11.h>
//#include <dxgi.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <dxgi1_4.h> // Include DXGI version 1.4 for IDXGIFactory4
#include <D3Dcompiler.h>
#include "GraphicsAPI.h"

/**
 * requires windows SDK for DirectX12
 * DirectX11 requires dxgi.lib
 */
class API_DirectX
    : public GraphicsBehaviour {
public:
    ID3D11Device* d3dDevice;
    ID3D11DeviceContext* d3dContext;
    IDXGIFactory1* dxgiFactory; // Added member for DXGI factory
    D3D_FEATURE_LEVEL featureLevel;


    bool initialise() override;
        void queryCapabilities() override;
        void shutdown(...) override;
        void demoTriangle();


    std::string getShaderFromFeature();

    std::string getTextureCompressionFormats();
};


