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
#include "CTexture.h"
#include "LoadTGA.h"
#include <GL/glu.h>
////////////////////////////////////////////////////////////////////////////////
CTexture::CTexture()
{
  texture = 0; 
}
////////////////////////////////////////////////////////////////////////////////
CTexture::~CTexture()
{
  glDeleteTextures(1, &texture);
}
////////////////////////////////////////////////////////////////////////////////
bool
CTexture::Load( const char *szFilename )
{
  TGAImg img;
  switch ( img.Load( (char *)szFilename ) )
  {
  case IMG_OK:
    
    break;
  default:
    return false;
    break;
  }
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &texture);
  glBindTexture( GL_TEXTURE_2D, texture );  
  GLenum format = img.GetBPP() == 32 ? GL_RGBA : GL_RGB;
   
  glTexImage2D( GL_TEXTURE_2D, 0, format, img.GetWidth(), img.GetHeight(), 0, format, GL_UNSIGNED_BYTE, img.GetImg());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  gluBuild2DMipmaps( GL_TEXTURE_2D, format, img.GetWidth(), img.GetHeight(),  format, GL_UNSIGNED_BYTE, img.GetImg());
  glDisable(GL_TEXTURE_2D);
  return true;
}
////////////////////////////////////////////////////////////////////////////////
void
CTexture::Apply(size_t unit )
{
  glActiveTexture(GL_TEXTURE0+unit);
  glEnable(GL_TEXTURE_2D);
  glBindTexture( GL_TEXTURE_2D, texture );
}
////////////////////////////////////////////////////////////////////////////////
