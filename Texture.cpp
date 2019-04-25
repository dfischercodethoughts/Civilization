//
// Created by JING LU on 2019-04-24.
//

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"

Texture::Texture(const char *filePath):
        id(0),
        width(0),
        height(0),
        data(0)
{
    data=stbi_load(filePath, &width, &height, 0, 4);
}

Texture::Texture(Texture &&rhs)
{
    this->id = rhs.id;
    this->data = rhs.data;
    this->width = rhs.width;
    this->height = rhs.height;
    rhs.id = 0;
    rhs.data = 0;
    rhs.width = 0;
    rhs.height = 0;
}

Texture::Texture():
        id(0),
        width(0),
        height(0),
        data(0)
{

}

Texture& Texture::operator=(Texture &&rhs)
{
    DeleteOpenGLData();
    this->~Texture();
    this->id = rhs.id;
    this->data = rhs.data;
    this->width = rhs.width;
    this->height = rhs.height;
    rhs.id = 0;
    rhs.data = 0;
    rhs.width = 0;
    rhs.height = 0;
    return *this;
}

int Texture::Width()
{
    return width;
}

int Texture::Height()
{
    return height;
}

void Texture::Draw(int l, int b, int r, int t)
{
    //save current attributes
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    //close culling，open texture and blend
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //auomaically generate the texture
    if (!id)
    {
        CreateOpenGLData();
    }
    //blinding texture
    glBindTexture(GL_TEXTURE_2D, id);
    //set color to white
    glColor3f(1,1,1);
    //draw a square
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2i(l,t);
    glTexCoord2f(1, 1);
    glVertex2i(r,t);
    glTexCoord2f(1, 0);
    glVertex2i(r, b);
    glTexCoord2f(0, 0);
    glVertex2i(l, b);
    glEnd();

    //restore attributes
    glPopAttrib();
}

void Texture::DeleteOpenGLData()
{
    if (id)
    {
        glDeleteTextures(1, &id);
        id = 0;
    }
}

//generate the texture
void Texture::CreateOpenGLData()
{
    if (!id)
    {
        if (data)
        {
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}

Texture::~Texture()
{
    if (data)
    {
        free(data);
        data = 0;
    }
}

TextureManager TextureManager::instance;

void TextureManager::Register(const char * identifier, Texture &&t)
{
    instance.textures[identifier] = std::move(t);
}

Texture & TextureManager::GetTexture(const char * identifier)
{
    return instance.textures[identifier];
}
