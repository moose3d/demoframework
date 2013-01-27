/******************************************************************************
 *  Copyright (c) Anssi Gröhn / eNtity at iki dot fi
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *****************************************************************************/
#include <string>
#include <fstream>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
using std::string;
using std::ifstream;
using std::ios;
////////////////////////////////////////////////////////////////////////////////
/// Loads file content into string.
/// \param szFilename path to file.
/// \param sContents Reference to string where contents will be stored.
int
LoadShaderFile( const char * szFilename, std::string &sContents )
{

  // Temporary container for line 
  string sLine;
  // The file stream 
  ifstream fsFile;

  fsFile.open( szFilename, ios::in );

  if ( fsFile.is_open() )    // test for failure 
  {
    // read line by line 
    while( ! fsFile.eof() )
    {
      getline( fsFile, sLine );
      sContents.append( sLine );
      sContents.append( "\n" );
    }
    fsFile.close();
  } 
  else 
  {
    std::cerr << "The file " << szFilename
	      << " couldn't be opened."  << std::endl;
    return 1;
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
#define INFO_LOG_BUF_SIZE 1024
////////////////////////////////////////////////////////////////////////////////
/// Parses shader/program info log into given string.
/// \param nObject From which shader/program log is retrieved.
/// \param strInfoLog String where log is stored.
/// \param bProgram True for retrieving program info log, 
/// False for shader info log
void 
GetInfoLog( GLuint nObject, std::string &strInfoLog, bool bProgram )
{
  int iInfologLength   = 0;      // total length of log
  int iCharsRetrievedBatch  = 0; // how many chars were retrived 
				 // from log in current pass
  int iCharsRetrievedTotal = 0;  // how many chars in total is retrieved.
  char sInfoLog[INFO_LOG_BUF_SIZE];

  // Get length of the info log
  if ( bProgram ) glGetProgramiv(nObject, GL_INFO_LOG_LENGTH, &iInfologLength);
  else		  glGetShaderiv( nObject, GL_INFO_LOG_LENGTH, &iInfologLength);
  //std::cerr << "info log length is : " << iInfologLength << std::endl;
  // if info log exists, we parse it
  if (iInfologLength > 0)
  {
    strInfoLog.clear(); // clear existing string
    strInfoLog.reserve(iInfologLength); // allocate sufficient memory

    // read chars up to info log length
    while ( iCharsRetrievedTotal < iInfologLength )
    {
      if ( bProgram ) 
      {
	//std::cerr << "getting program info log" << std::endl;
	glGetProgramInfoLog(nObject, INFO_LOG_BUF_SIZE, 
			    &iCharsRetrievedBatch, sInfoLog);
      }
      else
      {
	glGetShaderInfoLog(nObject, INFO_LOG_BUF_SIZE, 
			   &iCharsRetrievedBatch, sInfoLog);
      }

      if ( iCharsRetrievedBatch > 0 )
      {
	iCharsRetrievedTotal += iCharsRetrievedBatch; 
	strInfoLog.append(sInfoLog, iCharsRetrievedBatch); 
      }
      else break;
      
    } // end while
    // ok, done
  }
}
////////////////////////////////////////////////////////////////////////////////
