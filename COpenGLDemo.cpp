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
#include "COpenGLDemo.h"
#include <algorithm>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
COpenGLDemo::COpenGLDemo() : m_bRunning(true), m_pScreen(NULL)
{

}
////////////////////////////////////////////////////////////////////////////////
bool
COpenGLDemo::Initialize()
{
	return true;
}
////////////////////////////////////////////////////////////////////////////////
COpenGLDemo::~COpenGLDemo()
{

}
////////////////////////////////////////////////////////////////////////////////
void
COpenGLDemo::HandleEvents()
{
  SDL_Event ev;
  while ( SDL_PollEvent( &ev ))
  {
    switch( ev.type )
    {
    case SDL_QUIT:
      OnQuit( ev.quit );
      break;
    case SDL_KEYDOWN:
      OnKeyDown( ev.key );
      break;
    case SDL_KEYUP:
      OnKeyUp( ev.key );
      break;
    case SDL_MOUSEMOTION:
      OnMouseMotion( ev.motion );
      break;
    case SDL_MOUSEBUTTONUP:
      OnMouseRelease( ev.button );
      break;
    case SDL_MOUSEBUTTONDOWN:
      OnMousePress( ev.button );
      break;
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
void
COpenGLDemo::OnQuit( SDL_QuitEvent & ev )
{
  SetRunning(false);
}
////////////////////////////////////////////////////////////////////////////////
bool
COpenGLDemo::IsRunning()
{
  return m_bRunning;
}
////////////////////////////////////////////////////////////////////////////////
void
COpenGLDemo::SetRunning( bool flag )
{
  m_bRunning = flag;
}
////////////////////////////////////////////////////////////////////////////////
struct UpdateOp
{
  float m_time;
  UpdateOp( float fSec ) : m_time(fSec){}

  inline void operator()( IUpdateable * pObj )
  {
    pObj->Update( m_time );
  }
};
////////////////////////////////////////////////////////////////////////////////
void
COpenGLDemo::Update()
{
  m_Timer.Update();
  UpdateableList & lst = GetUpdateables();
  //cout << "passed time: " << m_Timer.GetPassedTime() << endl; 
  for_each( lst.begin(), lst.end(), UpdateOp(m_Timer.GetPassedTime()));
  m_Timer.Reset();
}

////////////////////////////////////////////////////////////////////////////////
struct RenderOp
{
  inline void operator()( IRenderable *r )
  {
    r->Render();
  }
};
////////////////////////////////////////////////////////////////////////////////
void
COpenGLDemo::Render()
{
  for_each( GetRenderables().begin(), GetRenderables().end(), RenderOp());
}

////////////////////////////////////////////////////////////////////////////////
bool
COpenGLDemo::OpenScreen( CScreenParams params  )
{
  if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
  {
    std::cerr << "Error: " << SDL_GetError() << std::endl;
    return false;
  }
  SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 1 );
  // open OpenGL screen with double buffering
  m_pScreen = SDL_SetVideoMode( params.width,
				params.height,
				params.depth,
				SDL_OPENGL | SDL_DOUBLEBUF );


  if ( m_pScreen ) return true;
  else
  {
    std::cerr << "Error: " << SDL_GetError() << std::endl;
    return false;
  }
}
////////////////////////////////////////////////////////////////////////////////
void
COpenGLDemo::RenderScene()
{
  PreRender();
  Render();
  PostRender();
}
////////////////////////////////////////////////////////////////////////////////
void
COpenGLDemo::SetWindowCaption( const char *szCaption )
{
  SDL_WM_SetCaption( szCaption, szCaption );
}
////////////////////////////////////////////////////////////////////////////////
