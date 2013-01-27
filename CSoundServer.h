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
#ifndef __CSoundServer_h__
#define __CSoundServer_h__
////////////////////////////////////////////////////////////////////////////////
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include <string>
using namespace std;
////////////////////////////////////////////////////////////////////////////////
typedef std::map<std::string, Mix_Chunk *> MapNameToSound;
typedef std::map<std::string, Mix_Music *> MapNameToMusic;
////////////////////////////////////////////////////////////////////////////////
class CSoundServer
{
private:

  MapNameToSound m_mapNameToSound;
  MapNameToMusic m_mapNameToMusic;

public:
	CSoundServer();
  virtual ~CSoundServer() { Destroy(); }
  bool Init( int freq = MIX_DEFAULT_FREQUENCY,
	     Uint16 format = MIX_DEFAULT_FORMAT,
	     int channels = 2,
	     int chunksize = 1024);

  void Destroy();


  bool Load( const std::string & name, const char *szSoundFile );
  bool LoadMusic( const std::string & name, const char *szMusicFile );
  void Remove( const std::string & name);
  void RemoveMusic( const std::string & name );

  int  Play( const std::string & name, int channel = -1 );
  int  PlayLooped( const std::string & name, int loops, int channel = -1 );
  int  PlayLoopedTimed( const std::string & name, int loops,
			int ms, int channel = -1 );


  int  FadeInLooped( const std::string & name, int loops, int ms, int channel=-1 );
  void FadeOutLooped( int ms, int channel = -1);

  void Halt( int channel = -1);
  void Pause( int channel = -1);
  void Resume( int channel = -1);


  void PlayMusic( const std::string & name );
  void HaltMusic();
  void PauseMusic();
  void ResumeMusic();

  bool IsPaused( int channel );
  bool IsPlaying( int channel );
  bool IsFading( int channel );
};
////////////////////////////////////////////////////////////////////////////////
#endif
