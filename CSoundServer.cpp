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
#include "CSoundServer.h"
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////////////////////
CSoundServer::CSoundServer()
{

}
////////////////////////////////////////////////////////////////////////////////
bool
CSoundServer::Init( int freq, Uint16 format, int channels, int chunksize)
{
  if ( ! SDL_WasInit( SDL_INIT_AUDIO))
  {
    if ( SDL_InitSubSystem( SDL_INIT_AUDIO ) == -1)
    {
      std::cerr << "Init error :" << SDL_GetError() << std::endl;
      return false;
    }
  }
  if ( Mix_OpenAudio(freq, format, channels, chunksize ) == -1 )
  {
    std::cerr << "OpenAudio error: " << Mix_GetError() << std::endl;
    return false;
  }
  return true;
}
////////////////////////////////////////////////////////////////////////////////
void CSoundServer::Destroy()
{
  // Destroy all sound samples and music
  while( !m_mapNameToSound.empty())
    m_mapNameToSound.erase(m_mapNameToSound.begin());

  SDL_QuitSubSystem( SDL_INIT_AUDIO );
}
////////////////////////////////////////////////////////////////////////////////
bool CSoundServer::Load( const std::string & name, const char *szSoundFile )
{
  Mix_Chunk *pChunk = Mix_LoadWAV( szSoundFile );
  if ( ! pChunk )
  {
    std::cerr << "Cannot load sample: " << szSoundFile << std::endl;
    return false;
  }

  if( m_mapNameToSound.find(name) == m_mapNameToSound.end())
  {
    m_mapNameToSound.insert( make_pair( name, pChunk ));
  }
  else
  {
    Mix_FreeChunk( pChunk );
    std::cerr << "Name '" << name << "' already exists!" << endl;
    return false;
  }
  return true;
}
////////////////////////////////////////////////////////////////////////////////
bool
CSoundServer::LoadMusic( const std::string & name, const char *szMusicFile )
{
  Mix_Music *pMusic = Mix_LoadMUS( szMusicFile );
  if ( !pMusic )
  {
    std::cerr << "Cannot load music: " << szMusicFile << std::endl;
    return false;
  }
  MapNameToMusic::iterator it;
  if ( (it=m_mapNameToMusic.find(name)) == m_mapNameToMusic.end() )
  {
    m_mapNameToMusic.insert( make_pair( name, pMusic ));
  }
  else
  {
    Mix_FreeMusic( pMusic );
    std::cerr << "Name '" << name << "' already exists!" << endl;
    return false;
  }
  return true;
}
////////////////////////////////////////////////////////////////////////////////
void
CSoundServer::Remove( const std::string & name)
{
  MapNameToSound::iterator it = m_mapNameToSound.find(name);
  if ( it != m_mapNameToSound.end())
  {
    Mix_FreeChunk(it->second);
    m_mapNameToSound.erase(it);
  }
}
////////////////////////////////////////////////////////////////////////////////
void
CSoundServer::RemoveMusic( const std::string & name )
{
  MapNameToMusic::iterator it = m_mapNameToMusic.find(name);
  if ( it != m_mapNameToMusic.end())
  {
    Mix_FreeMusic(it->second);
    m_mapNameToMusic.erase(it);
  }
}
////////////////////////////////////////////////////////////////////////////////
int
CSoundServer::Play( const std::string & name, int channel  )
{
  return PlayLooped( name, 0, channel );
}
/////////////////////////////////////////////////////////////////
int
CSoundServer::PlayLooped( const std::string & name, int loops, int channel )
{
  return PlayLoopedTimed( name, loops, 0, channel );
}
////////////////////////////////////////////////////////////////////////////////
int
CSoundServer::PlayLoopedTimed( const std::string & name, int loops,
			      int ms, int channel )
{

  MapNameToSound::iterator it= m_mapNameToSound.find(name);
  if ( it != m_mapNameToSound.end())
  {
    return Mix_PlayChannelTimed(channel, it->second, loops, ms);
  }
  return -1;
}
////////////////////////////////////////////////////////////////////////////////
void
CSoundServer::Halt( int channel )
{
  Mix_HaltChannel(channel);
}
////////////////////////////////////////////////////////////////////////////////
void
CSoundServer::Pause( int channel )
{
  Mix_Pause(channel);
}
////////////////////////////////////////////////////////////////////////////////
void
CSoundServer::Resume( int channel )
{
  Mix_Resume(channel);
}
////////////////////////////////////////////////////////////////////////////////
void
CSoundServer::PlayMusic( const std::string & name )
{
  MapNameToMusic::iterator it = m_mapNameToMusic.find(name);
  if ( it != m_mapNameToMusic.end())
  {
    Mix_PlayMusic( it->second, 0 );
  }
}
////////////////////////////////////////////////////////////////////////////////
void
CSoundServer::HaltMusic()
{
  Mix_HaltMusic();
}
////////////////////////////////////////////////////////////////////////////////
void
CSoundServer::PauseMusic()
{
  Mix_PauseMusic();
}
////////////////////////////////////////////////////////////////////////////////
void
CSoundServer::ResumeMusic()
{
  Mix_ResumeMusic();
}
////////////////////////////////////////////////////////////////////////////////
bool
CSoundServer::IsPaused( int channel )
{
  return Mix_Paused(channel);
}
////////////////////////////////////////////////////////////////////////////////
bool
CSoundServer::IsPlaying( int channel )
{
  return Mix_Playing(channel);
}
////////////////////////////////////////////////////////////////////////////////
bool
CSoundServer::IsFading( int channel )
{
  return ( Mix_FadingChannel(channel) != MIX_NO_FADING );
}
////////////////////////////////////////////////////////////////////////////////
int
CSoundServer::FadeInLooped( const std::string & name, int loops, int ms,
			   int channel )
{
  MapNameToSound::iterator it= m_mapNameToSound.find(name);
  if ( it != m_mapNameToSound.end())
  {
    return Mix_FadeInChannel( channel, it->second, loops, ms );
  }
  return -1;
}
////////////////////////////////////////////////////////////////////////////////
void
CSoundServer::FadeOutLooped( int channel, int ms  )
{
  Mix_FadeOutChannel( channel, ms );
}
////////////////////////////////////////////////////////////////////////////////
