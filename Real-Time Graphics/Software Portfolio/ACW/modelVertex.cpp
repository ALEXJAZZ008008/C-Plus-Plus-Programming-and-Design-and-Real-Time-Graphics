#include "modelVertex.h"

ModelVertex::ModelVertex() : m_ImageVertex(), m_Normal(), m_Tangent(), m_Binormal()
{

}

ModelVertex::ModelVertex(const float pX, const float pY, const float pZ, const float tU, const float tV, const float nX, const float nY, const float nZ) : m_ImageVertex(ImageVertex(pX, pY, pZ, tU, tV)), m_Normal(XMFLOAT3(nX, nY, nZ)), m_Tangent(), m_Binormal()
{

}

ModelVertex::ModelVertex(const float pX, const float pY, const float pZ, const float tU, const float tV, const float nX, const float nY, const float nZ, const float tX, const float tY, const float tZ, const float bX, const float bY, const float bZ) : m_ImageVertex(ImageVertex(pX, pY, pZ, tU, tV)), m_Normal(XMFLOAT3(nX, nY, nZ)), m_Tangent(XMFLOAT3(tX, tY, tZ)), m_Binormal(XMFLOAT3(bX, bY, bZ))
{

}

ModelVertex::ModelVertex(const ModelVertex &modelVertex) : m_ImageVertex(modelVertex.GetImageVertex()), m_Normal(modelVertex.GetNormal()), m_Tangent(modelVertex.GetTangent()), m_Binormal(modelVertex.GetBinormal())
{

}

ModelVertex & ModelVertex::operator = (const ModelVertex &modelVertex)
{
	if (this != &modelVertex)
	{
		m_ImageVertex = modelVertex.GetImageVertex();

		m_Normal = modelVertex.GetNormal();
		m_Tangent = modelVertex.GetTangent();
		m_Binormal = modelVertex.GetBinormal();
	}

	return *this;
}

ModelVertex::ModelVertex(const ModelVertex &&modelVertex) : m_ImageVertex(modelVertex.GetImageVertex()), m_Normal(modelVertex.GetNormal()), m_Tangent(modelVertex.GetTangent()), m_Binormal(modelVertex.GetBinormal())
{

}

ModelVertex & ModelVertex::operator = (const ModelVertex &&modelVertex)
{
	if (this != &modelVertex)
	{
		m_ImageVertex = modelVertex.GetImageVertex();

		m_Normal = modelVertex.GetNormal();
		m_Tangent = modelVertex.GetTangent();
		m_Binormal = modelVertex.GetBinormal();
	}

	return *this;
}

ModelVertex::~ModelVertex()
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