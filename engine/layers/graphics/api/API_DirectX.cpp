#pragma once

#include "API_DirectX.h"

void API_DirectX11::initialise() {
    HRESULT hr = D3D11CreateDevice(
            nullptr,                            // Use the default adapter
            D3D_DRIVER_TYPE_HARDWARE,            // Use hardware graphics driver
            nullptr,                            // No software rasterizer
            0,                                  // Flags for runtime layers (optional)
            nullptr,                            // Feature levels array (use default)
            0,                                  // Number of feature levels (use default)
            D3D11_SDK_VERSION,                  // SDK version
            &device,                            // Output device
            nullptr,                            // Output feature level (not needed here)
            &deviceContext                      // Output device context
    );

    if (FAILED(hr)) {
        // Handle device creation error
        // You may want to add error handling code here
        return;
    }
}

void API_DirectX11::setCapabilities() {
    // Get the device adapter description (which includes GPU name)
    IDXGIDevice* dxgiDevice = nullptr;
    device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
    if (dxgiDevice) {
        IDXGIAdapter* adapter = nullptr;
        dxgiDevice->GetAdapter(&adapter);
        if (adapter) {
            DXGI_ADAPTER_DESC adapterDesc;
            adapter->GetDesc(&adapterDesc);
            int len = lstrlenW(adapterDesc.Description);
            capabilities.gpuName.resize(len);

            // Convert wide character to string
            WideCharToMultiByte(CP_UTF8, 0, adapterDesc.Description, -1, &capabilities.gpuName[0], len, nullptr, nullptr);

            adapter->Release();
        }
        dxgiDevice->Release();
    }
    // Get other capabilities
    capabilities.maxTextureUnits = D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;
    capabilities.maxResolutionX = D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION;
    capabilities.maxResolutionY = D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION;
    capabilities.maxAnisotropy = D3D11_MAX_MAXANISOTROPY;
    capabilities.maxMultisampleSamples = D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;
    capabilities.maxConstantBufferSize = D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT * 16; // Assuming 16 bytes per constant
    capabilities.maxVertexBufferSize = D3D11_REQ_MULTI_ELEMENT_STRUCTURE_SIZE_IN_BYTES; // Maximum vertex buffer size
    capabilities.maxIndexBufferSize = D3D11_REQ_MULTI_ELEMENT_STRUCTURE_SIZE_IN_BYTES; // Maximum index buffer size
    capabilities.maxPrimitiveTopology = D3D11_REQ_DRAWINDEXED_INDEX_COUNT_2_TO_EXP;
    capabilities.maxRenderTargets = GetMaxRenderTargets();
    capabilities.maxUniformBufferBindings = D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT;


    // You'll need to set other capabilities based on DirectX properties

}

int API_DirectX11::GetMaxRenderTargets() {
    D3D_FEATURE_LEVEL featureLevel = device->GetFeatureLevel();

    switch (featureLevel) {
        case D3D_FEATURE_LEVEL_11_1:
        case D3D_FEATURE_LEVEL_11_0:
            return D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; // Typically 8 on feature level 11.
        case D3D_FEATURE_LEVEL_10_1:
        case D3D_FEATURE_LEVEL_10_0:
            return 4; // Maximum of 4 render targets on feature level 10.
            // Handle other feature levels as needed.
        default:
            return 1; // Minimum requirement is 1 render target.
    }
}
