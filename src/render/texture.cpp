#define __FILENAME__ "Texture"

#include "render/texture.hpp"
#include "utils/log.hpp"

#include <glad/gl.h>
#include <stb_image.h>
#include <string>

Texture::Texture(const std::string &path, unsigned int texture_unit,
                 unsigned int format) {
  // load image bytes as unsigned char
  unsigned char *data =
      stbi_load(path.c_str(), &_width, &_height, &_channels, 0);

  // check if image was read successfully or not.
  if (data == nullptr) {
    Log::error(__FILENAME__, "Failed to open texture file: " + path);
  }

  // actiavte perticular texture uint
  glad_glActiveTexture(texture_unit);

  glad_glGenTextures(1, &_id);

  bind();

  // set default parameters for texture.
  parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, format,
                    GL_UNSIGNED_BYTE, data);

  // generate mimaps for texture.
  glad_glGenerateMipmap(GL_TEXTURE_2D);

  // delete image data form the cpu.
  stbi_image_free(data);
}

Texture::~Texture() { glad_glDeleteTextures(1, &_id); }

// public functions
void Texture::bind() const { glad_glBindTexture(GL_TEXTURE_2D, _id); }

void Texture::parameter(unsigned int pname, int param) const {
  glad_glTexParameteri(GL_TEXTURE_2D, pname, param);
}

void Texture::parameter(unsigned int pname, float param) const {
  glad_glTexParameterf(GL_TEXTURE_2D, pname, param);
}
