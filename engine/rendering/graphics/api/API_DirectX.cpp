
#include "API_DirectX.h"
#include <locale>
#include <codecvt>

void API_DirectX::queryCapabilities() {
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
            std::wstring wideModel(adapterDesc.Description);
            std::string model(wideModel.begin(), wideModel.end());
            gpuInfo->model = model;
            gpuInfo->driverVersion = "N/A"; // DirectX 12 doesn't provide driver version directly

            // Get VRAM size in MB
            gpuInfo->VRAMSize = static_cast<int>(adapterDesc.DedicatedVideoMemory / (1024 * 1024));

            // Query DirectX version support
            gpuInfo->directXVersionSupport = "DirectX 12";

            // Other GPU capabilities
            // Add code to query and populate additional capabilities here...
        }

        adapter->Release();
    }

    dxgiFactory->Release();
    CoUninitialize();

}

bool API_DirectX::initialise() {
    HRESULT hr;

    // Create the DXGI Factory
    IDXGIFactory4* dxgiFactory;
    hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
    if (FAILED(hr)) {
        std::cerr << "Failed to create DXGI factory." << std::endl;
        return false;
    }

    // Create the DirectX 12 Device
    hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&d3dDevice));
    if (FAILED(hr)) {
        std::cerr << "Failed to create DirectX 12 device." << std::endl;
        dxgiFactory->Release();
        return false;
    }

    // Create a command queue (example)
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    hr = d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&d3dContext));
    if (FAILED(hr)) {
        std::cerr << "Failed to create DirectX 12 command queue." << std::endl;
        dxgiFactory->Release();
        d3dDevice->Release();
        return false;
    }

    // Initialization successful
    return true;
}
