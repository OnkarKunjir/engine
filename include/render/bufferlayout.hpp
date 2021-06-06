#pragma once
#include <glad/gl.h>
#include <vector>

struct Attribute {
  int index;
  int size;
  unsigned int type;
  bool normalized;
  int pointer;
};

class BufferLayout {
private:
  std::vector<Attribute> _attributes;
  int _stride;

public:
  BufferLayout();
  ~BufferLayout();

  void bind();
  void push_float(int count, bool normalized = false);
};
