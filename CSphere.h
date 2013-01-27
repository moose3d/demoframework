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
#ifndef __CSphere_h__
#define __CSphere_h__
#include "Vector3D.h"
#include "Vector4D.h"
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
class CSphere
{
 protected:
  /// Vector where position is stored.
  Vector3D m_vPosition;
  /// Sphere radius.
  float m_fRadius;
  /// Squared radius.
  float m_fRadiusSqr;
 public:
  /////////////////////////////////////////////////////////////////
  /// The default constructor.
  CSphere()
  {
    m_fRadius    = 0.0f;
    m_fRadiusSqr = 0.0f;
  }
  /////////////////////////////////////////////////////////////////
  /// The parametrized constructor.
  CSphere( const Vector3D & vPosition, float fRadius )
  {
    SetPosition(vPosition);
    m_fRadius = fRadius;
    m_fRadiusSqr = m_fRadius * m_fRadius;
  }
  /////////////////////////////////////////////////////////////////
  /// Assingment operator.
  /// \param ref sphere to be assigned.
  inline CSphere & operator=(const CSphere & ref)
  {
    SetPosition(ref.GetPosition());
    SetRadius( ref.m_fRadius );
    return *this;
  }
  /////////////////////////////////////////////////////////////////
  /// Sets the radius.
  /// \param fRadius the radius value.
  inline void SetRadius(float fRadius)
  {
    m_fRadius = fRadius;
    m_fRadiusSqr = m_fRadius * m_fRadius;
  }
  /////////////////////////////////////////////////////////////////
  /// Return the radius.
  /// \return float radius.
  inline float GetRadius() const
  {
    return m_fRadius;
  }
  /////////////////////////////////////////////////////////////////
  /// Returns the squared radius. Useful in some situations.
  /// \returns squared radius.
  inline float GetRadiusSqr() const
  {
    return m_fRadiusSqr;
  }

  ////////////////////
  /// Assigns position.
  /// \param vPosition vector of which values are used.
  inline void SetPosition( const Vector3D &vPosition )
  {
    m_vPosition = vPosition;
  }
  ////////////////////
  /// Assigns the position.
  /// \param fX position on X-axis.
  /// \param fY position on Y-axis.
  /// \param fZ position on Z-axis.
  inline void SetPosition( float fX, float fY, float fZ )
  {
    m_vPosition.x = fX;
    m_vPosition.y = fY;
    m_vPosition.z = fZ;
  }

  ////////////////////
  /// Returns position.
  /// \param current position.
  inline const Vector3D & GetPosition() const
  {
    return m_vPosition;
  }

  ////////////////////
  /// Adds vector to current position.
  /// \param vPosition the movement applied to current position.
  inline void Move( const Vector3D & vPosition )
  {
    m_vPosition = m_vPosition + vPosition;
  }

  inline bool Intersects( const CSphere & sphere ) const
  {
    return (SquaredMag(GetPosition() - sphere.GetPosition()) < (sphere.GetRadiusSqr() + GetRadiusSqr()));
  }
  inline bool Intersects( const Vector4D & plane ) const
  {
	  const Vector3D & normal = plane.GetVector3D();
	  float fDistance = Dot(normal, GetPosition()) + plane.w;
      // Check does sphere intersect
	  return ( fabs(fDistance) <= GetRadius());
  }
  inline int OnWhichSideOfPlane( const Vector4D & plane ) const
    {
  	  const Vector3D & normal = plane.GetVector3D();
  	  float fDistance = Dot(normal, GetPosition()) + plane.w;
        // Check does sphere intersect
  	  if ( fabs(fDistance) <= GetRadius()) return 0;
  	  else if ( fDistance > GetRadius()) return 1;
  	  else return -1;

    }
  friend std::ostream & operator<<( std::ostream & stream, const CSphere & sphere )
  {
    stream << sphere.GetPosition().x << ","
	   << sphere.GetPosition().y << ","
	   << sphere.GetPosition().z << ","
    	   << sphere.GetRadius();
    return stream;
  }

}; // class CSphere
////////////////////////////////////////////////////////////////////////////////
#endif
