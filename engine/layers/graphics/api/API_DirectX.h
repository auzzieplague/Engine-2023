#pragma once

#include "GraphicsAPI.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h> // For shader compilation functions

class API_DirectX11 : public GraphicsAPI {
public:
//    void framebufferSizeCallback(GLFWwindow *window, int width, int height) override;

    ID3D11Device *device = nullptr;
    ID3D11DeviceContext *deviceContext = nullptr;

    void initialise() override;
    void setCapabilities() override;
    int GetMaxRenderTargets();

    // load shader function should allow a list


//    api->beginRender(instanceRenderConfig);
//    api->shaderSetView(scene->currentCamera->getViewMatrix());
//    api->shaderSetTransform(mesh->getWorldMatrix());
//    api->shaderSetVec3("highlight", highlight);
//    api->shaderSetMaterial(mesh->getMaterial());
//    api->renderMesh(mesh);
//    api->renderInstancedMesh(mesh, transforms);
//    api->shaderSetMat4
//            api->setCapabilities();
//    api->displayCapabilities();
//    api->loadShader("general.vert", "general.frag");
//    api->shaderSetProjection(scene->currentCamera->getProjectionMatrix());
//    api->shaderSetView(scene->currentCamera->getViewMatrix());
};


