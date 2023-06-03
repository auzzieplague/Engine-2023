#pragma once

#include "Material.h"
#include "../layers/graphics/api/GraphicsAPI.h"

GraphicsAPI *Material::m_api = nullptr;

const glm::vec3 &Material::getAmbientColor() const {
    return m_ambientColor;
}

void Material::setAmbientColor(const glm::vec3 &mAmbientColor) {
    m_ambientColor = mAmbientColor;
}

const glm::vec3 &Material::getDiffuseColor() const {
    return m_diffuseColor;
}

void Material::setDiffuseColor(const glm::vec3 &mDiffuseColor) {
    m_diffuseColor = mDiffuseColor;
}

const glm::vec3 &Material::getSpecularColor() const {
    return m_specularColor;
}

void Material::setSpecularColor(const glm::vec3 &mSpecularColor) {
    m_specularColor = mSpecularColor;
}

float Material::getShininess() const {
    return m_shininess;
}

void Material::setShininess(float mShininess) {
    m_shininess = mShininess;
}

void Material::setDiffuseTexture(unsigned int ID) {
    m_texture_diffuse = ID;
}


void Material::setNormalTexture(unsigned int ID) {
    m_texture_normal = ID;
}

void Material::setGraphicsAPI(GraphicsAPI *api) {
    Material::m_api = api;
}

void Material::loadFromAsset(std::string category, const std::string& materialName) {
    std::string path = AssetManager::getRelativePath(category,materialName);
    // todo: check if exists - upgrade the texture quality accordingly
    this->m_texture_diffuse = m_api->loadTexture(path+"_diffuse.png");
    this->m_texture_normal = m_api->loadTexture(path+"_normal.png");
}

unsigned int Material::getDiffuseTexture() {
    return m_texture_diffuse;
}

unsigned int Material::getNormalTexture() {
    return m_texture_normal;
}