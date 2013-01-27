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
#include "CTimer.h"
////////////////////////////////////////////////////////////////////////////////
void
CTimer::Update()
{
  m_CurrentTime = SDL_GetTicks();
}
////////////////////////////////////////////////////////////////////////////////
CTimer::CTimer() 
{
  Reset();
}
////////////////////////////////////////////////////////////////////////////////
void 
CTimer::Reset()
{
  m_PreviousTime = m_CurrentTime = SDL_GetTicks();
}
////////////////////////////////////////////////////////////////////////////////
float 
CTimer::GetPassedTime()
{
  return (m_CurrentTime - m_PreviousTime) * 0.001f;
}
////////////////////////////////////////////////////////////////////////////////
Uint32 
CTimer::GetPassedTimeMS()
{
  return (m_CurrentTime - m_PreviousTime);
}
////////////////////////////////////////////////////////////////////////////////
