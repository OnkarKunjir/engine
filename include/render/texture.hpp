#pragma once

#include <stb_image.h>
#include <string>

// TODO: support 3d and 1d textures.

class Texture {
private:
  unsigned int _id;
  int _width, _height, _channels;

public:
  /**Constructor
   *@param path path of texture file.
   *@param texture_unit texture unit to bind image with.
   *@param format format of image eg. GL_RGBA, GL_RGB,..
   */
  Texture(const std::string &path, unsigned int texture_unit,
          unsigned int format);
  ~Texture();

  /**Binds current texture*/
  void bind() const;

  /**Set parameter for current texture.
   *uses glad_glTexParameteri to set parameter values.
   *@param pname parameter name.
   *@param param parameter value for pname.
   */
  void parameter(unsigned int pname, int param) const;

  /**Set parameter for current texture.
   *uses glad_glTexParameterf to set parameter values.
   *@param pname parameter name.
   *@param param parameter value for pname.
   */
  void parameter(unsigned int pname, float param) const;
};
