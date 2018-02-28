#include "face.h"

Face::Face() : m_VectorIndex(), m_TextureIndex(), m_NormalIndex()
{
	
}

Face::Face(const Face &face) : m_VectorIndex(face.GetVectorIndex()), m_TextureIndex(face.GetTextureIndex()), m_NormalIndex(face.GetNormalIndex())
{
	
}

Face & Face::operator = (const Face &face)
{
	if (this != &face)
	{
		m_VectorIndex = face.GetVectorIndex();
		m_TextureIndex = face.GetTextureIndex();
		m_NormalIndex = face.GetNormalIndex();
	}

	return *this;
}

Face::Face(const Face &&face) : m_VectorIndex(face.GetVectorIndex()), m_TextureIndex(face.GetTextureIndex()), m_NormalIndex(face.GetNormalIndex())
{

}

Face & Face::operator = (const Face &&face)
{
	if (this != &face)
	{
		m_VectorIndex = face.GetVectorIndex();
		m_TextureIndex = face.GetTextureIndex();
		m_NormalIndex = face.GetNormalIndex();
	}

	return *this;
}

Face::~Face()
{
	try
	{

	}
	catch (const exception &e)
	{
#ifdef _DEBUG

		cout << e.what();

#endif
	}
}