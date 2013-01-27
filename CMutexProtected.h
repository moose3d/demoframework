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

#ifndef CMUTEXPROTECTED_H_
#define CMUTEXPROTECTED_H_

#include <SDL.h>

class CMutexProtected {
protected:
	SDL_mutex *m_pMutex;
	CMutexProtected();
	virtual ~CMutexProtected();
public:
	// Used to lock access
  	bool Lock()                   { return (SDL_LockMutex( m_pMutex )==0); }
  	// Used to release access
  	bool Unlock()                 { return (SDL_UnlockMutex( m_pMutex)==0); }
};

#endif /* CMUTEXPROTECTED_H_ */
