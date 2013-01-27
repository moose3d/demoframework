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
/////////////////////////////////////////////////////////////////
#ifndef __CParticleSystem_h__
#define __CParticleSystem_h__
/////////////////////////////////////////////////////////////////
#include "Vector3D.h"
#include "IUpdateable.h"
#include <list>
#include <iostream>
/////////////////////////////////////////////////////////////////
/// The Particle base class, contains properties of a single particle.
struct  CParticle
{
  ///  Current position in the world.
  ///  \par previous position in the world is a special case,
  ///  \par must be implemented in inherited class.
Vector3D m_vPosition;
  ///  Direction and speed.
  Vector3D m_vVelocity;

  ///  The energy of this particle.
  float	      m_fEnergy;
  ///  The scaling factor for the particle shape defined in the
  ///  \par ParticleSystem.
  float	      m_fSize;
};
/////////////////////////////////////////////////////////////////
/// Particle System.
template <size_t SIZE, class InitializePolicy, class ActionPolicy, class PARTICLE_TYPE >
class  CParticleSystem : public IUpdateable
{
private:
  /// Particle array
  PARTICLE_TYPE m_aParticles[SIZE];
  /// The number of particles that are alive in the system.
  size_t	m_nNumParticlesAlive;
  /// Number of particles generated in one second. (not used).
  float		m_fThroughPut;


public:
  /// Initialization policy.
  InitializePolicy m_InitializePolicy;
  /// Action policy.
  ActionPolicy     m_ActionPolicy;
  ////////////////////
  /// Default constructor.
  CParticleSystem();
  ////////////////////
  /// Destructor.
  virtual ~CParticleSystem(){}
  ////////////////////
  /// Returns maximum number of particles in this system.
  size_t GetMaxParticles() const;
  ////////////////////
  /// Returns number of particles alive in this system.
  size_t GetAliveCount() const;
  ////////////////////
  /// Updates the particles with ActionPolicy.
  /// Particles are ordered so that the living particles are in the front
  /// of particle array.
  /// \param fSeconds Passed time in seconds.
  void Update( float fSecondsPassed );
  ////////////////////
  /// An accessor method for particle array
  /// \returns Pointer to particle array.
  const PARTICLE_TYPE * GetParticles() const;
  ////////////////////
  /// Intializes system.
  /// \param nNumParticles Number of particles to be created.
  void Init(const size_t nNumParticles );
  /////////////////////////////////////////////////////////////////
  /// Checks is system alive.
  /// \returns Non-zero if system has living particles ( energy > 0 )
  /// \returns Zero otherwise.
  int IsAlive() const;
  /////////////////////////////////////////////////////////////////
}; // CParticleSystem


/////////////////////////////////////////////////////////////////
// Policies for ParticleSystems - these babies make the systems
// tick.
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
/// CompletePolicy for handling size, color, velocity, energy, and position.
template < class PARTICLE_TYPE,class SizePolicy, class VelocityPolicy, class EnergyPolicy, class PositionPolicy>
class  CCompletePolicy
{
public:
  /// Size policy.
  SizePolicy     m_SizePolicy;
  /// Velocity policy.
  VelocityPolicy m_VelocityPolicy;
  /// Energy policy.
  EnergyPolicy     m_EnergyPolicy;
  /// Position policy.
  PositionPolicy m_PositionPolicy;
  ////////////////////
  /// Prepares this policy according to given time parameter.
  /// \param fSecondsPassed Passed time in seconds.
  inline void Prepare(  float fSecondsPassed )
  {
	m_SizePolicy.Prepare(fSecondsPassed);
	m_VelocityPolicy.Prepare( fSecondsPassed );
	m_EnergyPolicy.Prepare(fSecondsPassed);
	m_PositionPolicy.Prepare(fSecondsPassed);

  }
  ////////////////////
  /// Modifies given particle.
  /// \param particle a particle which values are to be modified.
  inline void operator()( PARTICLE_TYPE & particle )
  {
	m_SizePolicy(particle);
	m_VelocityPolicy(particle);
	m_EnergyPolicy(particle);
	m_PositionPolicy(particle);

  }
}; // end of CCompletePolicy

/////////////////////////////////////////////////////////////////
/// Class for measuring time difference within policies (using seconds).
class  CSecondPolicyBase
{
protected:
  /// Passed time in seconds
  float m_fPassedTimeInSec;
public:
  ////////////////////
  /// Constructor.
  CSecondPolicyBase() : m_fPassedTimeInSec(0.0f) {}
  ////////////////////
  /// Prepares this policy according to given time parameter.
  /// \param nPassedTimeInMS Passed milliseconds are stored as seconds.
  inline void Prepare( float fSecondsPassed )
  {
	  m_fPassedTimeInSec = fSecondsPassed;
  }
  ////////////////////
  /// Returns passed time.
  /// \returns Passed time in milliseconds.
  inline float GetPassedTime() const
  {
	  return m_fPassedTimeInSec;
  }
};

    /////////////////////////////////////////////////////////////////
    // Individual policies:
    /////////////////////////////////////////////////////////////////
    /// Template for GravityAction.
    template <class PARTICLE_TYPE>
    class  CGravityAction : public CSecondPolicyBase
    {
    private:
      /// Gravity values.
      Vector3D m_vGravity;
    public:
      ////////////////////
      /// Default constructor.
      CGravityAction() : m_vGravity(0,-9.81f,0) {};
      ////////////////////
      /// Modifies given particle.
      /// \param particle a particle which values are to be modified.
      inline void operator()(PARTICLE_TYPE &particle )
      {
	particle.m_vVelocity += m_vGravity * GetPassedTime();
      }
      /// Sets gravity vector.
      /// \param vDir a gravity vector.
      inline void SetGravity( const Vector3D &vDir )
      {
	m_vGravity = vDir;
      }

    }; // end of CGravityAction
    /////////////////////////////////////////////////////////////////
    // Template for MoveAction.
    template <class PARTICLE_TYPE>
    class  CMoveAction : public CSecondPolicyBase
    {
    public:
      ////////////////////
      /// Modifies given particle.
      /// \param p particle which values are to be modified.
      inline void operator()(PARTICLE_TYPE &p) const
      {
	p.m_vPosition += p.m_vVelocity * GetPassedTime();
      }
    }; // end of CMoveAction
    /////////////////////////////////////////////////////////////////
    /// Template for SizeInitializer.
    template <class PARTICLE_TYPE>
    class  CSizeInitializer
    {
    public:
      /// Size value.
      float m_fSize;
      ////////////////////
      /// Default constructor.
      CSizeInitializer() : m_fSize(1.0f){}
      ////////////////////
      /// Modifies given particle.
      /// \param p particle which values are to be modified.
      inline const void operator()(PARTICLE_TYPE &p) const
      {
	p.m_fSize = m_fSize;
      }
    }; // end of CSizeInitializer
    /////////////////////////////////////////////////////////////////
	/// Template for PositionInitializer.
	template <class PARTICLE_TYPE>
	class  CPositionInitializer
	{
	public:
	  Vector3D m_vPosition;
	  ////////////////////
	  /// Modifies given particle.
	  /// \param p particle which values are to be modified.
	  inline const void operator()(PARTICLE_TYPE &p) const
	  {
		  p.m_vPosition= m_vPosition;
	  }
	}; // end of CSizeInitializer

    /////////////////////////////////////////////////////////////////
    /// Template for policy which does not do a thing.
    /// Can be used when some policy will not matter.
    template <class PARTICLE_TYPE>
    class  CNullPolicy
    {
    public:
      ////////////////////
      /// Prepares this policy according to given time parameter.
      /// \param fSecondsPassed Passed time in seconds.
      inline void Prepare( float fSecondsPassed ){}
      ////////////////////
      /// Modifies given particle.
      /// \param p particle which values are to be modified.
      inline void operator()(PARTICLE_TYPE &p) const {}
    }; // end of CNullPolicy
    /////////////////////////////////////////////////////////////////
    template <class PARTICLE_TYPE>
    class  CEnergyInitializer
    {
    public:
      /// Initial energy.
      float m_fEnergy;
      ////////////////////
      /// Default constructor.
      CEnergyInitializer() : m_fEnergy(1.0f){}
      ////////////////////
      /// Modifies given particle.
      /// \param p particle which values are to be modified.
      inline void operator()(PARTICLE_TYPE &p) const
      {
    	  p.m_fEnergy = m_fEnergy;
      }
    };
    /////////////////////////////////////////////////////////////////

    template <class PARTICLE_TYPE>
    class  CEnergyAction : public CSecondPolicyBase
    {
	public:

		float m_fEnergyDrain;
		////////////////////
		/// Default constructor.
		CEnergyAction() : m_fEnergyDrain(1.0f){}
		////////////////////
		/// Modifies given particle.
		/// \param p particle which values are to be modified.
		inline void operator()(PARTICLE_TYPE &p) const
		{
			p.m_fEnergy -= m_fEnergyDrain * GetPassedTime();
		}
	};
    /////////////////////////////////////////////////////////////////
    // A velocity initializer for particle system
    template <class PARTICLE_TYPE>
    class  CVelocityInitializer
    {
    public:
      /// Velocity vector.
      Vector3D m_vVelocity ;
      ////////////////////
      /// Default constructor.
      CVelocityInitializer() :m_vVelocity(0,0,0) {}
      ////////////////////
      /// Modifies given particle.
      /// \param p particle which values are to be modified.
      inline void operator()(PARTICLE_TYPE &p) const
      {
	p.m_vVelocity = m_vVelocity;
      }
    };

    /////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
template <size_t SIZE, class InitializePolicy, class ActionPolicy, class PARTICLE_TYPE >
CParticleSystem<SIZE,InitializePolicy, ActionPolicy, PARTICLE_TYPE >::CParticleSystem()
{
  m_nNumParticlesAlive = 0;

}
/////////////////////////////////////////////////////////////////
template <size_t SIZE, class InitializePolicy, class ActionPolicy, class PARTICLE_TYPE >
inline size_t
CParticleSystem<SIZE,InitializePolicy, ActionPolicy, PARTICLE_TYPE >::GetMaxParticles() const
{
  return SIZE;
}
/////////////////////////////////////////////////////////////////
template <size_t SIZE, class InitializePolicy, class ActionPolicy, class PARTICLE_TYPE >
inline size_t
CParticleSystem<SIZE,InitializePolicy, ActionPolicy, PARTICLE_TYPE >::GetAliveCount() const
{
  return m_nNumParticlesAlive;
}
/////////////////////////////////////////////////////////////////
template <size_t SIZE, class InitializePolicy, class ActionPolicy, class PARTICLE_TYPE >
void
CParticleSystem<SIZE,InitializePolicy, ActionPolicy, PARTICLE_TYPE >::Update( float fSecondsPassed )
{
  m_ActionPolicy.Prepare( fSecondsPassed );
  for(unsigned int i = 0;i<GetAliveCount();)
  {
    PARTICLE_TYPE &p = m_aParticles[i];
    m_ActionPolicy(p);
    // Is particle is dead
    if ( p.m_fEnergy <= 0.0f && m_nNumParticlesAlive > 0)
    {
      // Replace dead particle with last known live one
      m_aParticles[i] = m_aParticles[m_nNumParticlesAlive - 1];
      m_nNumParticlesAlive--;
    }
    else
    {
      i++;
    }
  }

}
/////////////////////////////////////////////////////////////////
template <size_t SIZE, class InitializePolicy, class ActionPolicy, class PARTICLE_TYPE >
inline const PARTICLE_TYPE *
CParticleSystem<SIZE,InitializePolicy, ActionPolicy, PARTICLE_TYPE >::GetParticles() const
{
  return m_aParticles;
}
/////////////////////////////////////////////////////////////////
template <size_t SIZE, class InitializePolicy, class ActionPolicy, class PARTICLE_TYPE >
void
CParticleSystem<SIZE,InitializePolicy, ActionPolicy, PARTICLE_TYPE >::Init(const size_t nNumParticles )
{
  size_t nAmount = nNumParticles;
  float  fParticleMaxSize = 0.0f;
  if ( GetAliveCount() + nAmount > GetMaxParticles() )
  {
    nAmount = GetMaxParticles() - GetAliveCount();
  }
  ////////////////////
  /// Create the particles.
  if ( nAmount > 0 )
  {
    size_t nCount = GetAliveCount();
    m_nNumParticlesAlive += nAmount ;

    for(; nCount < GetAliveCount(); nCount++)
    {
      // init policy must take care of all positioning, we might have different types of
      // particles that require additional structures to be set (Such as tails of energy weapons)
      // m_aParticles[nCount].m_vPosition = vPosition;
      // Init policy takes care of positioning, if necessary.
      m_InitializePolicy(m_aParticles[nCount]);

      if ( m_aParticles[nCount].m_fSize > fParticleMaxSize)
      {
	fParticleMaxSize = m_aParticles[nCount].m_fSize;
      }
    }
  }
}
/////////////////////////////////////////////////////////////////
template <size_t SIZE, class InitializePolicy, class ActionPolicy, class PARTICLE_TYPE >
inline int
CParticleSystem<SIZE,InitializePolicy, ActionPolicy, PARTICLE_TYPE >::IsAlive() const
{
  return ( GetAliveCount() > 0 );
}
/////////////////////////////////////////////////////////////////
#endif
