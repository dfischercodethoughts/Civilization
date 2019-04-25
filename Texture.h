//
// Created by JING LU on 2019-04-20.
//
#ifndef CIV_TEXTURE_H
#define CIV_TEXTURE_H

#include "Square.h"
#include <string>
#include <map>

//纹理
class Texture
{
protected:
    int width;//texture width
    int height;//texture height
    unsigned char *data;//texture data
    GLuint id;//texture id in opengl

    //prohibit texture copying
    Texture(const Texture &) = delete;
    Texture& operator=(const Texture &) = delete;

public:
    //initialized
    Texture();
    //read texture from file
    explicit Texture(const char *filePath);

    //constructor
    Texture(Texture &&rhs);
    Texture& operator=(Texture &&rhs);

    //return the size of texture
    int Width();
    int Height();

    //draw left bottom right top icon
    void Draw(int l,int b,int r,int t);

    //clean opengl data
    void DeleteOpenGLData();
    //automatically generate opengl data
    void CreateOpenGLData();

    virtual ~Texture();
};

//Class to manage the texture
class TextureManager
{
    static TextureManager instance;
    std::map<std::string, Texture> textures;
public:
    //the texture matching to the registration indicator
    static void Register(const char * identifier, Texture &&t);
    //get texture from identifier
    static Texture &GetTexture(const char *identifier);
};

#endif
