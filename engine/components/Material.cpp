#pragma once

#include "Material.h"

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
