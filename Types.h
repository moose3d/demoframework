/*******************************************************************************
 * Copyright (c) 2009 Anssi Gröhn / eNtity at iki dot fi.
 *
 * This file is part of eNtity's demo framework.
 *
 *  eNtity's demo framework is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  eNtity's demo framework is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with eNtity's demo framework.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/
#ifndef __Types_h__
#define __Types_h__
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
////////////////////////////////////////////////////////////////////////////////
struct Color
{
  float r,g,b,a;
  void ToArray( float * pArray ) { pArray[0] = r; pArray[1] = g; pArray[2] = b; pArray[3] = a; }
  void operator=(const Color & col ) { r=col.r; g=col.g; b =col.b; a = col.a; }
};
////////////////////////////////////////////////////////////////////////////////
typedef Vector3D Vertex;
typedef Vector3D Normal;
////////////////////////////////////////////////////////////////////////////////
struct Face 
{
  int vertices[3];
  int normals[3];
  int texcoords[3];
  friend std::ostream & operator<<( std::ostream & stream, const Face & f )
  {
    stream << "tri ("<< f.vertices[0] << ", " << f.vertices[1] << ", " << f.vertices[2] << ")";
    stream << " n ("<< f.normals[0] << ", " << f.normals[1] << ", " << f.normals[2] << ")";
    return stream;
  }
};
////////////////////////////////////////////////////////////////////////////////
struct TexCoord
{
  float s,t;
};
////////////////////////////////////////////////////////////////////////////////
#define COLOR_INIT(C, r1,g1,b1,a1 )  C.r = r1;   C.g = g1;   C.b = b1;   C.a = a1;
#define SET_VECTOR4(A, B)        A.x = B.x; A.y = B.y; A.z = B.z; A.w = B.w;
#define SET_VECTOR3(A, B)        A.x = B.x; A.y = B.y; A.z = B.z; 
////////////////////////////////////////////////////////////////////////////////
#define BUFFER_OFFSET(i) ((char*)NULL + (i))
////////////////////////////////////////////////////////////////////////////////
#endif


