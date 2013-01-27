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
#ifndef __CObject3D_h__
#define __CObject3D_h__
////////////////////////////////////////////////////////////////////////////////
#include "COBJModel.h"
#include "CShader.h"
#include "CSphere.h"
#include "CTexture.h"
#include "IRenderable.h"
#include "IUpdateable.h"
#include "CCamera.h"
////////////////////////////////////////////////////////////////////////////////
class CObject3D : public IRenderable,
		  public IUpdateable
{
protected:

  CTexture  * m_pTexture;
  COBJModel * m_pMesh;
  Vector3D    m_Position;
  Vector3D    m_Rotation;
  Vector3D    m_vHeading;
  float       m_fScale;

  CShader    *m_pShader;
  CSphere     m_Sphere;

  void ComputeHeading()
  {
	  Vector3D negZ(0,0,-1);
	  negZ.RotateAboutY( m_Rotation.y*g_fDegToRad);
	  m_vHeading = negZ;

  }
public:

  void SetPosition( const Vector3D & v )  { m_Position = v; }
  void SetRotation( const Vector3D & r )  { m_Rotation = r; ComputeHeading();}

  Vector3D & GetRotation() { return m_Rotation; }
  Vector3D & GetPosition() { return m_Position; }
  Vector3D & GetHeading() { return m_vHeading; }

  void SetMesh( COBJModel *pMesh )        { m_pMesh = pMesh; }
  void SetTexture( CTexture *pTexture )   { m_pTexture = pTexture; }
  void SetScale( float fScale )		  { m_fScale = fScale; }

  void SetShader( CShader *pShader ) { m_pShader = pShader; }

  CObject3D() : m_pTexture(NULL), m_pMesh(NULL), m_pShader(NULL)
  {
    m_Position.x = 0;
    m_Position.y = 0;
    m_Position.z = 0,

    m_Rotation.x = 0;
    m_Rotation.y = 0;
    m_Rotation.z = 0;

    m_vHeading.x = 0;
    m_vHeading.y = 0;
    m_vHeading.z = -1;
    m_fScale = 1.0f;
    m_Sphere.SetRadius(0.0);
    m_Sphere.SetPosition(0,0,0);
  }

  void Render()
  {
    if ( m_pTexture ) m_pTexture->Apply();
    if ( m_pShader ) m_pShader->Apply();

    glPushMatrix();
      glTranslatef( m_Position.x, m_Position.y, m_Position.z);
      glRotatef( m_Rotation.z, 0, 0, 1 );
      glRotatef( m_Rotation.y, 0, 1, 0 );
      glRotatef( m_Rotation.x, 1, 0, 0);
      glScalef( m_fScale, m_fScale, m_fScale );
      if ( m_pMesh ) m_pMesh->Render();
    glPopMatrix();
    glUseProgram(0);
  }

  void Update(float fSeconds )
  {

  }

  CSphere & GetBoundingSphere()
  {
    return m_Sphere;
  }

  virtual void UpdateBoundingSphere()
  {
    GetBoundingSphere().SetPosition(m_Position);
    GetBoundingSphere().SetRadius(1.0);
  }

};
////////////////////////////////////////////////////////////////////////////////
#endif
