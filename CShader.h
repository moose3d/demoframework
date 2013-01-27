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
#ifndef __CShader_h__
#define __CShader_h__
////////////////////////////////////////////////////////////////////////////////
#include <list>
#include <GL/GLee.h>
////////////////////////////////////////////////////////////////////////////////
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
////////////////////////////////////////////////////////////////////////////////
class CShader
{
protected:
  GLuint	    program;
  std::list<GLuint> m_lstShaders;
public:

  CShader();
  virtual ~CShader();

  bool LoadVertexShader( const char *szVertexFile );
  bool LoadFragmentShader( const char *szFragmentFile );
  bool Link();
  void Apply();
  void SetUniformParameter( const char *szName, float fValue );
  void SetUniformParameter( const char *szName, int iValue );
  void SetVertexAttribArray( const char *szName, const Vector4D * attrib );

protected:
  void Destroy();
};
////////////////////////////////////////////////////////////////////////////////
#endif
