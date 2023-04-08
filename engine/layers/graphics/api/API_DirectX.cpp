#pragma once
/**
* @author auzzi
*/

#include <d3d11.h>
#include "API_DirectX.h"

void API_DirectX::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    D3D11_VIEWPORT vp;
    vp.Width = static_cast<FLOAT>(width);
    vp.Height = static_cast<FLOAT>(height);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

// Set the viewport
//    pImmediateContext->RSSetViewports(1, &vp);
}
