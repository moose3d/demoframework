/*******************************************************************************
 * Copyright (c) 2009 Anssi Gröhn / eNtity entity at iki dot fi
 * 
 * 
 ******************************************************************************/
#ifndef __COBJModel_h__
#define __COBJModel_h__
////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <fstream>
#include <sstream>
#include "Types.h"
#include "CShader.h"
////////////////////////////////////////////////////////////////////////////////
#ifndef MESH_OPTIMIZATION
#define MESH_OPTIMIZATION 1
#endif
////////////////////////////////////////////////////////////////////////////////
using namespace std;
enum VBO_NAMES
  {
    VERTEX_VBO,
    NORMAL_VBO,
    TEXCOORD_VBO,
    NUM_VBO_NAMES
  };
////////////////////////////////////////////////////////////////////////////////
class COBJModel
{
protected:

  vector<Vertex>	m_Vertices;
  vector<Normal>	m_Normals;
  vector<TexCoord>      m_TexCoords;
  vector<Face>          m_Faces;

  Vector3D         *m_VertexArray;
  Vector3D         *m_NormalArray;
  Vector2D         *m_TexCoordArray;

  GLuint	m_DisplayList;
  
  GLuint        m_VBONames[NUM_VBO_NAMES];
  float         *m_CombinedArray;

  Vector4D       *m_VertexTangents;

  CShader         *m_pShader;

public:
  COBJModel()
  {
    m_VertexArray = NULL;
    m_NormalArray = NULL;
    m_TexCoordArray = NULL;
    m_VertexTangents = NULL;
    m_DisplayList = 0;

    m_pShader = NULL;

  }

  void SetShader( CShader *pShader ) { m_pShader = pShader; }

  virtual ~COBJModel()
  {

    if (m_DisplayList > 0 )
    {
      glDeleteLists( m_DisplayList, 1 );
      m_DisplayList = 0;
    }

#if MESH_OPTIMIZATION==3
    glDeleteBuffers(NUM_VBO_NAMES, m_VBONames);
#endif

    delete [] m_VertexArray;
    delete [] m_NormalArray;
    delete [] m_TexCoordArray;

  }
  
  // Rather blindly loads file into memory, does not perform 
  // error checking on data.
  bool Load( const char *szFilename )
  {
    ifstream file(szFilename, ios::in );
    if ( ! file ) 
    {
      cout << "Cannot open file " << szFilename << endl;
      return false;
    }
    
    string tmp;

    while( !file.eof())
    {
      getline(file, tmp );
      if (      IsVertex(tmp )  ) {  m_Vertices.push_back(ParseVector(tmp,1));   }
      else if ( IsNormal(tmp )  ) {  m_Normals.push_back(ParseVector(tmp,2));    }
      else if ( IsFace( tmp )   ) {  m_Faces.push_back(ParseFace(tmp));          }
      else if ( IsTexCoord(tmp) ) {  m_TexCoords.push_back(ParseTexCoord(tmp));  }
      // skip otherwise
    }
#if MESH_OPTIMIZATION>=2
    CreateArrays();

#if MESH_OPTIMIZATION==3
    glGenBuffers( NUM_VBO_NAMES,   m_VBONames);
    glBindBuffer( GL_ARRAY_BUFFER, m_VBONames[VERTEX_VBO]);
    glBufferData( GL_ARRAY_BUFFER, sizeof(float)*3*3*m_Faces.size(), m_VertexArray, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, m_VBONames[NORMAL_VBO]);
    glBufferData( GL_ARRAY_BUFFER, sizeof(float)*3*3*m_Faces.size(), m_NormalArray, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, m_VBONames[TEXCOORD_VBO]);
    glBufferData( GL_ARRAY_BUFFER, sizeof(float)*2*3*m_Faces.size(), m_TexCoordArray, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

#elif MESH_OPTIMIZATION==4
    glGenBuffers( 1, m_VBONames );
    CombineArrays();
    size_t                       nArraySize  = m_Faces.size()*3*3*sizeof(float);
    if ( ! m_Normals.empty() )   nArraySize += m_Faces.size()*3*3*sizeof(float);
    if ( ! m_TexCoords.empty() ) nArraySize += m_Faces.size()*3*2*sizeof(float);

    glBindBuffer( GL_ARRAY_BUFFER, m_VBONames[0] );
    glBufferData( GL_ARRAY_BUFFER, nArraySize, m_CombinedArray, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
#endif
#endif
    return true;
  }
  ////////////////////
  /// 
  void Render()
  {

#if MESH_OPTIMIZATION<1
    /* no optimization*/
    glBegin(GL_TRIANGLES);
    for( size_t i=0;i<m_Faces.size();i++)
    {

      for( int v=0;v<3;v++)
      {
	if ( !m_TexCoords.empty())
	  glTexCoord2f( m_TexCoords[m_Faces[i].texcoords[v]].s, 
			m_TexCoords[m_Faces[i].texcoords[v]].t );
	
	if ( !m_Normals.empty())
	  glNormal3f(   m_Normals[m_Faces[i].normals[v]].x,     
			m_Normals[m_Faces[i].normals[v]].y,    
			m_Normals[m_Faces[i].normals[v]].z   );
	
	glVertex3f(   m_Vertices[ m_Faces[i].vertices[v]].x,  
		      m_Vertices[ m_Faces[i].vertices[v]].y, 
		      m_Vertices[ m_Faces[i].vertices[v]].z);
      }
    }
    glEnd();
#elif MESH_OPTIMIZATION==1
    /* display list */ 
    if ( m_DisplayList == 0 ) 
    {
      m_DisplayList = glGenLists( 1 );
      glNewList( m_DisplayList, GL_COMPILE );
      glBegin(GL_TRIANGLES);
      for( size_t i=0;i<m_Faces.size();i++)
    {

      for( int v=0;v<3;v++)
      {
	if ( !m_TexCoords.empty())
	  glTexCoord2f( m_TexCoords[m_Faces[i].texcoords[v]].s, 
			m_TexCoords[m_Faces[i].texcoords[v]].t );
	
	if ( !m_Normals.empty())
	  glNormal3f(   m_Normals[m_Faces[i].normals[v]].x,     
			m_Normals[m_Faces[i].normals[v]].y,    
			m_Normals[m_Faces[i].normals[v]].z   );
	
	glVertex3f(   m_Vertices[ m_Faces[i].vertices[v]].x,  
		      m_Vertices[ m_Faces[i].vertices[v]].y, 
		      m_Vertices[ m_Faces[i].vertices[v]].z);
      }
    }
    glEnd();
    glEndList();
    glCallList( m_DisplayList );
    }
    else
    {
      glCallList( m_DisplayList );
    }
   
#elif MESH_OPTIMIZATION==2
    /* Regular vertex arrays */
    if ( !m_TexCoords.empty() )
    {
      glEnableClientState( GL_TEXTURE_COORD_ARRAY );
      glTexCoordPointer( 2, GL_FLOAT, 0, m_TexCoordArray );
    }

    if ( !m_Normals.empty() )
    {
      glEnableClientState( GL_NORMAL_ARRAY );
      glNormalPointer( GL_FLOAT, 0, m_NormalArray );
    }

    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, m_VertexArray );
#ifdef SHADER
    if ( m_pShader ) m_pShader->SetVertexAttribArray("vTangent", GetTangentArray());
#endif
    glDrawArrays( GL_TRIANGLES, 0, m_Faces.size()*3);

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );

#elif MESH_OPTIMIZATION==3
    /* Vertex buffer object optimization */
    if ( !m_TexCoords.empty() )
    {
      glEnableClientState( GL_TEXTURE_COORD_ARRAY );
      glBindBuffer( GL_ARRAY_BUFFER, m_VBONames[TEXCOORD_VBO]);
      glTexCoordPointer( 2, GL_FLOAT, 0, 0 );
    }

    if ( !m_Normals.empty() )
    {
      glEnableClientState( GL_NORMAL_ARRAY );
      glBindBuffer( GL_ARRAY_BUFFER, m_VBONames[NORMAL_VBO]);
      glNormalPointer( GL_FLOAT, 0, 0 );
    }

    glEnableClientState( GL_VERTEX_ARRAY );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBONames[VERTEX_VBO]);
    glVertexPointer( 3, GL_FLOAT, 0, 0 );


    glDrawArrays( GL_TRIANGLES, 0, m_Faces.size()*3);

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );

#elif MESH_OPTIMIZATION==4

    glBindBuffer( GL_ARRAY_BUFFER, m_VBONames[0]);
    size_t stride = 0;
    if ( !m_TexCoords.empty() && !m_Normals.empty() ) stride = sizeof(float)*8;
    if ( m_TexCoords.empty() && !m_Normals.empty() ) stride = sizeof(float)*6;
    if ( !m_TexCoords.empty() && m_Normals.empty() ) stride = sizeof(float)*5;
    if ( m_TexCoords.empty() && m_Normals.empty() ) stride = sizeof(float)*3;

    if ( !m_TexCoords.empty() && !m_Normals.empty() )
    {
      glEnableClientState( GL_TEXTURE_COORD_ARRAY );
      glTexCoordPointer( 2, GL_FLOAT, stride, BUFFER_OFFSET(sizeof(float)*6));
    }
    else if ( !m_TexCoords.empty())
    {
      glEnableClientState( GL_TEXTURE_COORD_ARRAY );
      glTexCoordPointer( 2, GL_FLOAT, stride, BUFFER_OFFSET(sizeof(float)*3));
    }
    
    if ( !m_Normals.empty() )
    {
      glEnableClientState( GL_NORMAL_ARRAY );
      glNormalPointer( GL_FLOAT, stride, BUFFER_OFFSET(sizeof(float)*3) );
    }
      
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, stride, 0 );


    glDrawArrays( GL_TRIANGLES, 0, m_Faces.size()*3);

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif


  }

  void CreateArrays()
  {
    // rather straightforward approach, using triangle list.
    
    // #faces, each has 3 vertices, each of which has 3 floats.
    m_VertexArray = new Vector3D[m_Faces.size()*3];
    m_NormalArray = new Vector3D[m_Faces.size()*3];
    // #faces, each has 3 vertices, each of which has 2 floats.!!!
    m_TexCoordArray = new Vector2D[m_Faces.size()*3];
    vector<Face>::iterator f = m_Faces.begin();
    int vIndex = 0;
    int tIndex = 0;
    for( ; f != m_Faces.end(); f++)
    {
      for( size_t v=0;v<3;v++)
      {
	m_VertexArray[vIndex].x = m_Vertices[(*f).vertices[v]].x;
	m_NormalArray[vIndex].x = m_Normals[(*f).normals[v]].x;
	//++vIndex;

	m_VertexArray[vIndex].y = m_Vertices[(*f).vertices[v]].y;
	m_NormalArray[vIndex].y = m_Normals[(*f).normals[v]].y;
	//++vIndex;

	m_VertexArray[vIndex].z = m_Vertices[(*f).vertices[v]].z;
	m_NormalArray[vIndex].z = m_Normals[(*f).normals[v]].z;
	//++vIndex;	
	++vIndex;

	m_TexCoordArray[tIndex].x = m_TexCoords[(*f).texcoords[v]].s;
	m_TexCoordArray[tIndex].y = m_TexCoords[(*f).texcoords[v]].t;
	++tIndex;
      }
    }
    
  }


  void CombineArrays()
  {
    size_t                       nArraySize  = m_Faces.size()*3*3*sizeof(float);
    if ( ! m_Normals.empty() )   nArraySize += m_Faces.size()*3*3*sizeof(float);
    if ( ! m_TexCoords.empty() ) nArraySize += m_Faces.size()*3*2*sizeof(float);

    m_CombinedArray = new float[ nArraySize ];
    vector<Face>::iterator f = m_Faces.begin();
    int idx = 0;


    for( ; f != m_Faces.end(); f++)
    {

      for( size_t v=0;v<3;v++)
      {
	m_CombinedArray[idx++] = m_Vertices[(*f).vertices[v]].x;
	m_CombinedArray[idx++] = m_Vertices[(*f).vertices[v]].y;
	m_CombinedArray[idx++] = m_Vertices[(*f).vertices[v]].z;

	if ( !m_Normals.empty() )
	{
	  m_CombinedArray[idx++] = m_Normals[(*f).normals[v]].x;
	  m_CombinedArray[idx++] = m_Normals[(*f).normals[v]].y;
	  m_CombinedArray[idx++] = m_Normals[(*f).normals[v]].z;
	}

	if ( !m_TexCoords.empty() )
	{
	  m_CombinedArray[idx++] = m_TexCoords[(*f).texcoords[v]].s;
	  m_CombinedArray[idx++] = m_TexCoords[(*f).texcoords[v]].t;
	}
      }
    }
  }
  Vector4D * GetTangentArray() { return m_VertexTangents;}
  
private:
  ////////////////////////////////////////////////////////////////////////////////
  bool IsVertex( string & tmp )    {    return ( tmp.find("v ") == 0);   }
  bool IsNormal( string & tmp )    {    return ( tmp.find("vn ") == 0);  }
  bool IsFace( string & tmp )      {    return ( tmp.find("f ") == 0);   }
  bool IsTexCoord( string & tmp )  {    return ( tmp.find("vt ") == 0);  }
  ////////////////////////////////////////////////////////////////////////////////
  /// Parses vector (vertex, normal)
  Vector3D ParseVector( string & tmp, int start_pos  )
  {
    Vector3D res;
    

    size_t start = tmp.find(" ", start_pos)+1;
    size_t end   = tmp.find(" ", start);
    
    istringstream(tmp.substr( start, end-start )) >> res.x;

    start = end+1;
    end = tmp.find(" ", start);
    istringstream(tmp.substr( start, end-start )) >> res.y;
    
    start = end+1;
    end = tmp.length();
    istringstream(tmp.substr( start, end-start )) >> res.z;

    return res;
  }
  ////////////////////////////////////////////////////////////////////////////////
  /// Parses texture coordinate
  TexCoord ParseTexCoord( string & tmp )
  {
    TexCoord res;

    size_t start = tmp.find(" ", 2)+1;
    size_t end   = tmp.find(" ", start);
    
    istringstream(tmp.substr( start, end-start)) >> res.s;
    start = end+1;
    end = tmp.length();
    istringstream(tmp.substr( start, end-start)) >> res.t;
    return res;
  }
  ////////////////////////////////////////////////////////////////////////////////
  /// Parses face
  Face ParseFace( string & tmp )
  {
    Face f;
    int  index = 0;
    size_t start = tmp.find(" ", 1)+1;

    for( int v = 0;v<3;v++)
    {
      size_t end   = tmp.find(" ", start);

      // in case line has been processed
      if ( end == string::npos ) end = tmp.length();

      string face_set = tmp.substr( start, end-start);
      // parse first set of indices

      // parse vertex index
      size_t tmp_start_pos = 0;
      size_t tmp_end_pos = face_set.find("/", tmp_start_pos);
      
      istringstream(face_set.substr(tmp_start_pos, tmp_end_pos-tmp_start_pos)) >> index;
      f.vertices[v] = index-1;

      // parse texcoord index
      tmp_start_pos = tmp_end_pos+1;
      tmp_end_pos = face_set.find("/", tmp_start_pos);
      if ( tmp_start_pos != tmp_end_pos ) 
      {
	istringstream(face_set.substr(tmp_start_pos, tmp_end_pos-tmp_start_pos)) >> index;
	f.texcoords[v] = index-1;
      }
      // parse normal index
      tmp_start_pos = tmp_end_pos+1;
      tmp_end_pos =  face_set.length();
      if ( tmp_start_pos != tmp_end_pos )
      {
	istringstream(face_set.substr(tmp_start_pos, tmp_end_pos-tmp_start_pos)) >> index;
	f.normals[v] = index -1;
      }
      // start next search right after next char
      start = end+1;
    }

    return f;
  }


};
////////////////////////////////////////////////////////////////////////////////
#endif
