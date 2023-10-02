
#include "API_DirectX.h"
#include <locale>
#include <codecvt>
#include <dxgiformat.h>
#include <iostream>
void API_DirectX::queryCapabilities(...) {
    if (this->gpuInfo == nullptr) {
        this->gpuInfo = new GPUInfo();
    }

    // Initialize COM
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    // Create the DXGI Factory
    IDXGIFactory4* dxgiFactory;
    HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
    if (FAILED(hr)) {
        std::cerr << "Failed to create DXGI factory." << std::endl;
        return;
    }

    // Enumerate adapters
    IDXGIAdapter1* adapter;
    hr = dxgiFactory->EnumAdapters1(0, &adapter);
    if (SUCCEEDED(hr)) {
        DXGI_ADAPTER_DESC1 adapterDesc;
        hr = adapter->GetDesc1(&adapterDesc);
        if (SUCCEEDED(hr)) {
            std::wstring wideDescription = adapterDesc.Description;
            std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
            std::string description = converter.to_bytes(wideDescription);
            gpuInfo->model = description;
            gpuInfo->VRAMSize = static_cast<int>(adapterDesc.DedicatedVideoMemory / (1024 * 1024));
            gpuInfo->shaderModelVersionSupport = this->getShaderFromFeature();
            gpuInfo->shaderLanguageSupport = "HLSL";
            gpuInfo->textureCompressionFormats = this->getTextureCompressionFormats();

//            D3D11_FEATURE_DATA_D3D11_OPTIONS options;
//            hr = d3dDevice->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS, &options, sizeof(options));
//            gpuInfo->maxTextureSize = options.;
        }
        adapter->Release();
    }

    dxgiFactory->Release();
    CoUninitialize();
}

bool API_DirectX::initialise(...) {
    HRESULT result;

    // Create a Direct3D device and device context
    result = D3D11CreateDevice(
            nullptr,                        // Use default adapter
            D3D_DRIVER_TYPE_HARDWARE,       // Use hardware acceleration
            nullptr,                        // No software rasterizer
            0,                              // No flags
            nullptr, 0,                     // Default feature levels
            D3D11_SDK_VERSION,              // SDK version
            &d3dDevice,                     // Output device
            &featureLevel,                  // Output feature level
            &d3dContext                     // Output device context
    );

    if (FAILED(result)) {
        std::cerr << "Failed to create Direct3D device and context." << std::endl;
        return false;
    }

    // Check the feature level to ensure it meets your requirements if necessary

    // Other initialization code (e.g., swap chain, render target, etc.) can go here...

    // Initialize DXGI
    result = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&dxgiFactory);
    if (FAILED(result)) {
        std::cerr << "Failed to create DXGI factory." << std::endl;
        return false;
    }

    return true;
}

void API_DirectX::shutdown(...) {
    // Release and clean up the DirectX resources

    // Release the device context
    if (d3dContext) {
        d3dContext->Release();
        d3dContext = nullptr;
    }

    // Release the device
    if (d3dDevice) {
        d3dDevice->Release();
        d3dDevice = nullptr;
    }

    // Release the DXGI factory
    if (dxgiFactory) {
        dxgiFactory->Release();
        dxgiFactory = nullptr;
    }
}

void API_DirectX::demoTriangle(...) {
//    // Check if necessary DirectX objects are valid
//    if (!d3dDevice || !d3dContext) {
//        std::cerr << "DirectX device or context is not valid." << std::endl;
//        return;
//    }
//
//    // Define vertices for a triangle (you can use your own vertices)
//    struct Vertex {
//        float x, y, z;
//    };
//    Vertex vertices[] = {
//            { 0.0f,  0.5f, 0.0f },  // Top
//            { 0.5f, -0.5f, 0.0f },  // Bottom right
//            { -0.5f, -0.5f, 0.0f }  // Bottom left
//    };
//
//    // Create a vertex buffer
//    D3D11_BUFFER_DESC bufferDesc = {};
//    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
//    bufferDesc.ByteWidth = sizeof(vertices);
//    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//
//    D3D11_SUBRESOURCE_DATA initData = {};
//    initData.pSysMem = vertices;
//
//    ID3D11Buffer* vertexBuffer = nullptr;
//    HRESULT hr = d3dDevice->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
//    if (FAILED(hr)) {
//        std::cerr << "Failed to create vertex buffer. HRESULT: " << hr << std::endl;
//        return;
//    }
//
//    // Set the vertex buffer
//    UINT stride = sizeof(Vertex);
//    UINT offset = 0;
//    d3dContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
//    D3D11_INPUT_ELEMENT_DESC layout[] =
//            {
//                    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//                    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//            };
//
//// Create the input layout
//    ID3D11InputLayout* inputLayout;
//    HRESULT hr = d3dDevice->CreateInputLayout(layout, 2, vertexShaderBytecode->GetBufferPointer(), vertexShaderBytecode->GetBufferSize(), &inputLayout);
//    if (FAILED(hr)) {
//        std::cerr << "Failed to create input layout. HRESULT: " << hr << std::endl;
//        return;
//    }
//
//// Set the input layout
//    d3dContext->IASetInputLayout(inputLayout);
//
//    // Set primitive topology (triangle list in this case)
//    d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//    // Set shaders (you need to create and set your own shaders)
//    // d3dContext->VSSetShader(...);
//    // d3dContext->PSSetShader(...);
//
//    // Render the triangle
//    d3dContext->Draw(3, 0); // 3 vertices starting from vertex 0
//
//    // Clean up resources (release the vertex buffer when done)
//    vertexBuffer->Release();
}

std::string API_DirectX::getShaderFromFeature() {
    // Convert the feature level to a string
    std::string shaderModel;
    switch (featureLevel) {
        case D3D_FEATURE_LEVEL_11_0:
            shaderModel = "Shader Model 5.0";
            break;
        case D3D_FEATURE_LEVEL_10_1:
            shaderModel = "Shader Model 4.1";
            break;
        case D3D_FEATURE_LEVEL_10_0:
            shaderModel = "Shader Model 4.0";
            break;
            // Handle other feature levels as needed
        default:
            shaderModel = "Unknown";
            break;
    }
    return shaderModel;
}

std::string API_DirectX::getTextureCompressionFormats() {

// List of common DXGI texture compression formats to check
    DXGI_FORMAT commonCompressionFormats[] = {
            DXGI_FORMAT_BC1_UNORM,
            DXGI_FORMAT_BC2_UNORM,
            DXGI_FORMAT_BC3_UNORM,
            // Add more formats as needed
    };

    std::string supportedFormats;

    int count = 0;
    for (DXGI_FORMAT format : commonCompressionFormats) {
        D3D11_TEXTURE2D_DESC texDesc = {};
        texDesc.Width = 1;
        texDesc.Height = 1;
        texDesc.MipLevels = 1;
        texDesc.ArraySize = 1;
        texDesc.Format = format;
        texDesc.SampleDesc.Count = 1;
        texDesc.SampleDesc.Quality = 0;
        texDesc.Usage = D3D11_USAGE_DEFAULT;
        texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        // Attempt to create a texture with the format
        if (SUCCEEDED(d3dDevice->CreateTexture2D(&texDesc, nullptr, nullptr))) {
            // Add the format to the string
            supportedFormats += std::to_string(format) + " ";
            count++;
        }
    }

    if (count==0) {
        supportedFormats = "No Texture Formats could be created";
    }
    return supportedFormats;
}
