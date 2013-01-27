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
#ifndef __CCamera_h__
#define __CCamera_h__
////////////////////////////////////////////////////////////////////////////////
#include "CFrustum.h"
////////////////////////////////////////////////////////////////////////////////
enum Projection_t { ORTHO, PERSPECTIVE };
#define g_fDegToRad 0.01745329252
////////////////////////////////////////////////////////////////////////////////
class CCamera
{
  Vector3D m_aPosition;
  float m_fRotationAngle;
  float m_fRotationAngleVert;
  Vector3D m_aHeading;
  Projection_t  m_Projection;
  CFrustum      m_Frustum;
  int         m_aViewport[4];
  float   m_fNear; ///< Near clipping plane
  float   m_fFar;  ///< Far clipping plane
public:

  CCamera()
  {
    m_aPosition.x = 0.0f;
    m_aPosition.y = 0.0f;
    m_aPosition.z = 0.0f;
    m_fNear = 0.1;
    m_fFar  = 1000.0f;
    m_fRotationAngle = 0.0f;
    m_fRotationAngleVert = 0.0f;
    m_aHeading.x = 0.0;
    m_aHeading.y = 0.0;
    m_aHeading.z = -1.0;
    m_Projection = PERSPECTIVE;
    ComputeHeading();
    SetViewport(0,0,640,480);
  }
  void SetNear( float fVal ) { m_fNear = fVal; }
  void SetFar( float fVal ) { m_fFar = fVal; }
  void SetPosition(float x, float y, float z)
  {
    m_aPosition.x = x;
    m_aPosition.y = y;
    m_aPosition.z = z;
  }

  Vector3D & GetPosition()
  {
    return m_aPosition;
  }

  void RotateY( float fVal ) { m_fRotationAngle += fVal;  ComputeHeading(); }
  void RotateX( float fVal ) { m_fRotationAngleVert += fVal; ComputeHeading(); }

  void MoveX( float fVal )    { m_aPosition.x += fVal; }
  void MoveY( float fVal )    { m_aPosition.y += fVal; }
  void MoveZ( float fVal )    { m_aPosition.z += fVal; }

  void MoveFwd( float fVal )
  {
    m_aPosition.x += fVal*m_aHeading.x;
    m_aPosition.y += fVal*m_aHeading.y;
    m_aPosition.z += fVal*m_aHeading.z;
  }

  void SetViewport( int x, int y, int w, int h)
  {
	  m_aViewport[0] = x;
	  m_aViewport[1] = y;
	  m_aViewport[2] = w;
	  m_aViewport[3] = h;
  }

  void ComputeHeading()
  {
		m_aHeading.x =  -sinf(m_fRotationAngle*g_fDegToRad);
		m_aHeading.y = -(-sinf(m_fRotationAngleVert*g_fDegToRad)*cosf(m_fRotationAngle*g_fDegToRad));
		m_aHeading.z = -(cosf(m_fRotationAngleVert*g_fDegToRad)*cosf(m_fRotationAngle*g_fDegToRad));
		//cout << "new heading computed: " << m_aHeading << endl;
  }

  void Apply()
  {
	glViewport( m_aViewport[0], m_aViewport[1], m_aViewport[2], m_aViewport[3]);
    ApplyPerspective();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef( -m_fRotationAngleVert, 1,0,0);
    glRotatef( -m_fRotationAngle, 0,1,0 );
    glTranslatef( -m_aPosition.x, -m_aPosition.y, -m_aPosition.z );
    // Update frustum planes
    m_Frustum.ExtractFromOpenGL();

  }
  void ApplyPerspective()
  {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    switch ( m_Projection )
    {
    case PERSPECTIVE:
      gluPerspective(43.0f,(float)m_aViewport[2]/(float)m_aViewport[3], m_fNear, m_fFar);
      break;
    case ORTHO:
      glOrtho( -10, 10, -10, 10, m_fNear, m_fFar);
      break;
    }
  }

  void SetProjection( Projection_t type )
  {
    m_Projection = type;
  }

  Projection_t GetProjection() const
  {
    return m_Projection;
  }

  Vector3D & GetHeading()
  {
    return m_aHeading;
  }

  const CFrustum & GetFrustum() const
  {
    return m_Frustum;
  }
};
////////////////////////////////////////////////////////////////////////////////
#endif
