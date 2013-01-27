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
#include "CShader.h"
#include <fstream>
#include "load_shader.cpp"
using namespace std;
////////////////////////////////////////////////////////////////////////////////
CShader::CShader()
{
}
////////////////////////////////////////////////////////////////////////////////
CShader::~CShader()
{
  Destroy();
}
////////////////////////////////////////////////////////////////////////////////
bool
CShader::LoadVertexShader( const char *szVertexFile )
{

  GLuint shader;
  string log;
  string tmp;  
  int status;

  shader = glCreateShader(GL_VERTEX_SHADER);

  if ( LoadShaderFile( szVertexFile, tmp) ) return false;

  // to make compiler happy
  const char *ptr = tmp.c_str();
  glShaderSource(shader, 1, &ptr, NULL); 
  
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &status); 
  if ( status == GL_FALSE )
  {
    GetInfoLog( shader, log, false );
    cerr << "Errors for vertex shader " << szVertexFile << ":\n" << log << endl;
    glDeleteShader(shader);
    return false;
  }
  
  m_lstShaders.push_back(shader);
  return true;
}
////////////////////////////////////////////////////////////////////////////////
bool
CShader::LoadFragmentShader( const char *szFragmentFile )
{

  GLuint shader;
  string log;
  string tmp;  
  int status;

  shader = glCreateShader(GL_FRAGMENT_SHADER);
  if ( LoadShaderFile( szFragmentFile, tmp) ) return false;

  const char *ptr = tmp.c_str();
  glShaderSource(shader, 1, &ptr, NULL); 
  
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &status); 
  if ( status == GL_FALSE )
  {
    GetInfoLog( shader, log, false );
    cerr << "Errors for fragment shader " << szFragmentFile << ":\n" << log << endl;
    glDeleteShader(shader);
    return false;
  }

  m_lstShaders.push_back(shader);
  return true;
}
////////////////////////////////////////////////////////////////////////////////
bool
CShader::Link()
{
  int status = 0;
  string log;
  program = glCreateProgram();

  std::list<GLuint>::iterator it = m_lstShaders.begin();
  
  for (  ; it != m_lstShaders.end(); it++)
  {
    glAttachShader( program, *it );
  }
  
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &status); 

  if ( status == GL_FALSE )
  {

    GetInfoLog( program, log, true );
    cerr << log << endl;
    Destroy();
    return false;
  }
  return true;
}
////////////////////////////////////////////////////////////////////////////////
void CShader::Destroy()
{
  std::list<GLuint>::iterator it = m_lstShaders.begin();
  for (  ; it != m_lstShaders.end(); it++)
  {
    glDetachShader( program, *it );
    glDeleteShader( *it );
  }
  glDeleteProgram(program);
}
////////////////////////////////////////////////////////////////////////////////
void
CShader::Apply()
{
  glUseProgram(program);
}
////////////////////////////////////////////////////////////////////////////////
void
CShader::SetUniformParameter( const char *szName, float fValue )
{
  GLint loc = glGetUniformLocation( program, szName);
  if ( loc == -1 ) 
  {
    cerr << "No such parameter " << szName << " in this shader." << endl;
    return;
  }
  glUniform1f( loc, fValue);
}
////////////////////////////////////////////////////////////////////////////////
void
CShader::SetUniformParameter( const char *szName, int iValue )
{
  GLint loc = glGetUniformLocation( program, szName);
  if ( loc == -1 ) 
  {
    cerr << "No such parameter " << szName << " in this shader." << endl;
    return;
  }
  glUniform1i( loc, iValue);
}
////////////////////////////////////////////////////////////////////////////////
void
CShader::SetVertexAttribArray( const char *szName, const Vector4D * attrib )
{
  GLint loc = glGetAttribLocation(program,szName);
  if ( loc == -1 )
  {
    cerr << "No such vertex attribute parameter " << szName << " in this shader." << endl;
    return;
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 4, GL_FLOAT, 0,0, reinterpret_cast<const float *>(attrib));
}
////////////////////////////////////////////////////////////////////////////////
