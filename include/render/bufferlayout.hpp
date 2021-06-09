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
  /**Specify attributes defined in any buffer.*/
private:
  std::vector<Attribute> _attributes;
  int _stride;

public:
  /**Initalizes BufferLayout.*/
  BufferLayout();
  ~BufferLayout();

  /**Creates and enables Vertex attribute pointer for all attributes.
   *@see push_float.
   */
  void bind() const;
  /**Adds new attribute of type float to current layout.
   *@param count number of elements defining attribute valid value (1, 2, 3, 4).
   *@param normalized does parameter need to be normalized.
   */
  void push_float(int count, bool normalized = false);
};
