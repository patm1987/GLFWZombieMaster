#include "renderable.h"
#include "utils/utils.h"

namespace Entity
{
	Renderable::Renderable() :
		m_color(0.f, 0.f, 0.f, 1.f),
		m_objectBuffer(0)
	{
		initBuffers();
	}

	Renderable::~Renderable()
	{
		clearGeometryData();
	}

	void Renderable::render()
	{

	}

	void Renderable::setGeometry(const GeometryData& geometryData)
	{
//		clearGeometryData();
//		memcpy(
//			m_geometryData.aIndexData,
//			geometryData.aIndexData,
//			sizeof(uint16_t) * geometryData.indexDataCount);
//		m_geometryData.indexDataCount = geometryData.indexDataCount;
//		memcpy(
//			m_geometryData.aVertexData,
//			geometryData.aVertexData,
//			sizeof(uint16_t) * geometryData.vertexDataCount);
//		m_geometryData.vertexDataCount = geometryData.vertexDataCount;
	}

	void Renderable::clearGeometryData()
	{
		Utils::safeDeleteArray(m_geometryData.aIndexData);
		Utils::safeDeleteArray(m_geometryData.aVertexData);
		m_geometryData.indexDataCount = 0;
		m_geometryData.vertexDataCount = 0;
	}

	void Renderable::initBuffers()
	{
//		m_objectBuffer = glGen
	}
}
