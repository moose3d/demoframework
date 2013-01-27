# ******************************************************************************
# *
# * Copyright (c) 2009 Anssi Gröhn / eNtity at iki dot fi.
# *
# * This file is part of eNtity's demo framework.
# *
# *  eNtity's demo framework is free software: you can redistribute it and/or modify
# *  it under the terms of the GNU General Public License as published by
# *  the Free Software Foundation, either version 3 of the License, or
# *  (at your option) any later version.
# *
# *  eNtity's demo framework is distributed in the hope that it will be useful,
# *  but WITHOUT ANY WARRANTY; without even the implied warranty of
# *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# *  GNU General Public License for more details.
# *
# *  You should have received a copy of the GNU General Public License
# *  along with eNtity's demo framework.  If not, see <http://www.gnu.org/licenses/>.
# ******************************************************************************
CFLAGS=-Wall -g `sdl-config --cflags` -I./Util -I.
CC=g++
LIBS=`sdl-config --libs` 
OBJ=COpenGLDemo.o CTimer.o CShader.o CTexture.o LoadTGA.o CFrustum.o CMutexProtected.o CSoundServer.o

all:  base

.PHONY: clean

clean:
	rm -f *.o a.out *.a

.cpp.o: 
	$(CC) -c $(CFLAGS) $< 

base:  $(OBJ)
	ar rcs libdemoframework.a $(OBJ)