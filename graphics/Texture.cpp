#include "graphics.h"


Texture::Texture(unsigned int width, unsigned int height)
{
    glGenTextures(1, &this->ID);
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &this->ID);
}

void Texture::bind(unsigned int index) const
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
