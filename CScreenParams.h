/*******************************************************************************
 * Copyright (c) 2009 Anssi Gr�hn / eNtity at iki dot fi.
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
#ifndef __CScreenParams_h__
#define __CScreenParams_h__
////////////////////////////////////////////////////////////////////////////////
struct CScreenParams
{
  int width;
  int height;
  int depth;
  ////////////////////
  /// Sets default values for screenparams.
  CScreenParams()
  {
    width  = 800;
    height = 600;
    depth  = 32;
  }

};
////////////////////////////////////////////////////////////////////////////////
#endif
