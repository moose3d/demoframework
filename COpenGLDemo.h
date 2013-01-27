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
////////////////////////////////////////////////////////////////////////////////
#ifndef __SDLAPP_H__
#define __SDLAPP_H__
////////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
#pragma warning( disable : 4244 4305 4996 )
#endif
////////////////////////////////////////////////////////////////////////////////
#include <SDL.h>
#include <GL/GLee.h>
#include <GL/glu.h>
#include "IRenderable.h"
#include "IUpdateable.h"
#include "CScreenParams.h"
#include "CTimer.h"
#include "CShader.h"
#include "CObject3D.h"
#include "COBJModel.h"
#include "CCamera.h"
#include "CParticleSystem.h"
#include "CMutexProtected.h"
#include "CSoundServer.h"
#include <list>
////////////////////////////////////////////////////////////////////////////////
typedef std::list<IRenderable *> RenderableList;
typedef std::list<IUpdateable *> UpdateableList;
////////////////////////////////////////////////////////////////////////////////
class COpenGLDemo
{
protected:

  RenderableList	m_lstRenderables;
  UpdateableList	m_lstUpdateables;
  bool			m_bRunning;
  CTimer		m_Timer;
  SDL_Surface *		m_pScreen;
  CCamera           m_Camera;
public:

  COpenGLDemo();
  virtual ~COpenGLDemo();


  RenderableList & GetRenderables() { return m_lstRenderables; }
  UpdateableList & GetUpdateables() { return m_lstUpdateables; }

  virtual bool Initialize();
  virtual bool OpenScreen( CScreenParams params = CScreenParams() );

  virtual void OnKeyUp( SDL_KeyboardEvent & ev ) {}
  virtual void OnKeyDown( SDL_KeyboardEvent & ev ) {}
  virtual void OnMouseMotion( SDL_MouseMotionEvent & ev ) {}
  virtual void OnMousePress( SDL_MouseButtonEvent & ev ) {}
  virtual void OnMouseRelease( SDL_MouseButtonEvent & ev ) {}
  virtual void OnQuit( SDL_QuitEvent & ev );

  virtual void HandleEvents();
  virtual void Update();

  virtual void PreRender() = 0;
  virtual void Render();
  virtual void PostRender() = 0;

  virtual void RenderScene();
  void SetWindowCaption( const char *szCaption );
  bool IsRunning();
  void SetRunning( bool flag );

  CTimer & GetTimer() { return m_Timer;}
};
////////////////////////////////////////////////////////////////////////////////
#endif
