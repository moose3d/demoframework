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
#include "CFrustum.h"
#include <GL/GLee.h>
////////////////////////////////////////////////////////////////////////////////
void
CFrustum::ExtractFromOpenGL()
{
  float   proj[16];
  float   modl[16];
  float   clip[16];
  float   t;
 
  /* Get the current PROJECTION matrix from OpenGL */
  glGetFloatv( GL_PROJECTION_MATRIX, proj );
 
  /* Get the current MODELVIEW matrix from OpenGL */
  glGetFloatv( GL_MODELVIEW_MATRIX, modl );
 
  /* Combine the two matrices (multiply projection by modelview) */
  clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
  clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
  clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
  clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];
 
  clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
  clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
  clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
  clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];
 
  clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
  clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
  clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
  clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];
 
  clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
  clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
  clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
  clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];
 
  /* Extract the numbers for the RIGHT plane */
  planes[0][0] = clip[ 3] - clip[ 0];
  planes[0][1] = clip[ 7] - clip[ 4];
  planes[0][2] = clip[11] - clip[ 8];
  planes[0][3] = clip[15] - clip[12];
 
  /* Normalize the result */
  t = sqrt( planes[0][0] * planes[0][0] + planes[0][1] * planes[0][1] + planes[0][2] * planes[0][2] );
  planes[0][0] /= t;
  planes[0][1] /= t;
  planes[0][2] /= t;
  planes[0][3] /= t;
 
  /* Extract the numbers for the LEFT plane */
  planes[1][0] = clip[ 3] + clip[ 0];
  planes[1][1] = clip[ 7] + clip[ 4];
  planes[1][2] = clip[11] + clip[ 8];
  planes[1][3] = clip[15] + clip[12];
 
  /* Normalize the result */
  t = sqrt( planes[1][0] * planes[1][0] + planes[1][1] * planes[1][1] + planes[1][2] * planes[1][2] );
  planes[1][0] /= t;
  planes[1][1] /= t;
  planes[1][2] /= t;
  planes[1][3] /= t;
 
  /* Extract the BOTTOM plane */
  planes[2][0] = clip[ 3] + clip[ 1];
  planes[2][1] = clip[ 7] + clip[ 5];
  planes[2][2] = clip[11] + clip[ 9];
  planes[2][3] = clip[15] + clip[13];
 
  /* Normalize the result */
  t = sqrt( planes[2][0] * planes[2][0] + planes[2][1] * planes[2][1] + planes[2][2] * planes[2][2] );
  planes[2][0] /= t;
  planes[2][1] /= t;
  planes[2][2] /= t;
  planes[2][3] /= t;
 
  /* Extract the TOP plane */
  planes[3][0] = clip[ 3] - clip[ 1];
  planes[3][1] = clip[ 7] - clip[ 5];
  planes[3][2] = clip[11] - clip[ 9];
  planes[3][3] = clip[15] - clip[13];
 
  /* Normalize the result */
  t = sqrt( planes[3][0] * planes[3][0] + planes[3][1] * planes[3][1] + planes[3][2] * planes[3][2] );
  planes[3][0] /= t;
  planes[3][1] /= t;
  planes[3][2] /= t;
  planes[3][3] /= t;
 
  /* Extract the FAR plane */
  planes[4][0] = clip[ 3] - clip[ 2];
  planes[4][1] = clip[ 7] - clip[ 6];
  planes[4][2] = clip[11] - clip[10];
  planes[4][3] = clip[15] - clip[14];
 
  /* Normalize the result */
  t = sqrt( planes[4][0] * planes[4][0] + planes[4][1] * planes[4][1] + planes[4][2] * planes[4][2] );
  planes[4][0] /= t;
  planes[4][1] /= t;
  planes[4][2] /= t;
  planes[4][3] /= t;
 
  /* Extract the NEAR plane */
  planes[5][0] = clip[ 3] + clip[ 2];
  planes[5][1] = clip[ 7] + clip[ 6];
  planes[5][2] = clip[11] + clip[10];
  planes[5][3] = clip[15] + clip[14];
 
  /* Normalize the result */
  t = sqrt( planes[5][0] * planes[5][0] + planes[5][1] * planes[5][1] + planes[5][2] * planes[5][2] );
  planes[5][0] /= t;
  planes[5][1] /= t;
  planes[5][2] /= t;
  planes[5][3] /= t;

}
////////////////////////////////////////////////////////////////////////////////
bool
CFrustum::PointInFrustum( float x, float y, float z ) const
{
  int p;
 
  for( p = 0; p < 6; p++ )
    if( planes[p][0] * x + planes[p][1] * y + planes[p][2] * z + planes[p][3] <= 0 )
      return false;
  return true;

}
////////////////////////////////////////////////////////////////////////////////
bool
CFrustum::PointInFrustum( const Vector3D & point ) const
{
  return PointInFrustum(point.x, point.y, point.z );
}
////////////////////////////////////////////////////////////////////////////////
bool
CFrustum::SphereInFrustum( float x, float y, float z, float radius  ) const
{
  int p;
 
  for( p = 0; p < 6; p++ )
    if( planes[p][0] * x + planes[p][1] * y + planes[p][2] * z + planes[p][3] <= -radius )
      return false;
  return true;

}
////////////////////////////////////////////////////////////////////////////////
bool
CFrustum::SphereInFrustum( const CSphere & sphere  ) const
{
  return SphereInFrustum(sphere.GetPosition().x, sphere.GetPosition().y, sphere.GetPosition().z, sphere.GetRadius());
}
////////////////////////////////////////////////////////////////////////////////
