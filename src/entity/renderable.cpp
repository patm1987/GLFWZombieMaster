#include "renderable.h"
#include "utils/utils.h"

#include "stdafx.h"

namespace Entity
{
	Renderable::Renderable() :
		m_color(0.f, 0.f, 0.f, 1.f),
		m_vertexBuffer(0)
	{
		glGenBuffers(1, &m_vertexBuffer);
		glGenBuffers(1, &m_indexBuffer);
	}

	Renderable::~Renderable()
	{
		clearGeometryData();
		glDeleteBuffers(1, &m_vertexBuffer);
		glDeleteBuffers(1, &m_indexBuffer);
	}

	/*!
	 * \brief Renders the object using fancy gl3 calls
	 * \note the transforms must already be set, will only submit geometry
	 */
	void Renderable::render()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glVertexAttribPointer(
			GLuint(VertexAttributes::Position),
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(VertexData),
			(void*)offsetof(VertexData, position));
		glEnableVertexAttribArray(GLuint(VertexAttributes::Position));
		glVertexAttribPointer(
			GLuint(VertexAttributes::Normal),
			3,
			GL_FLOAT,
			GL_TRUE,
			sizeof(VertexData),
			(void*)offsetof(VertexData, normal));
		glEnableVertexAttribArray(GLuint(VertexAttributes::Normal));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		glDrawElements(
			GL_TRIANGLES,
			m_geometryData.indexDataCount,
			GL_UNSIGNED_SHORT,
			nullptr);

		glDisableVertexAttribArray(GLuint(VertexAttributes::Position));
		glDisableVertexAttribArray(GLuint(VertexAttributes::Normal));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/*!
	 * \brief sets the stored geometry to the given geometry
	 * \param data to send to the GPU
	 */
	void Renderable::setGeometry(const GeometryData& geometryData)
	{
		clearGeometryData();
		m_geometryData.aIndexData = new uint16_t[geometryData.indexDataCount];
		memcpy(
			m_geometryData.aIndexData,
			geometryData.aIndexData,
			sizeof(uint16_t) * geometryData.indexDataCount);

		m_geometryData.aVertexData = new VertexData[geometryData.vertexDataCount];
		m_geometryData.indexDataCount = geometryData.indexDataCount;
		memcpy(
			m_geometryData.aVertexData,
			geometryData.aVertexData,
			sizeof(uint16_t) * geometryData.vertexDataCount);
		m_geometryData.vertexDataCount = geometryData.vertexDataCount;

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(GeometryData) * m_geometryData.vertexDataCount,
			m_geometryData.aVertexData,
			GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(uint16_t) * m_geometryData.indexDataCount,
			m_geometryData.aIndexData,
			GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	/*!
	 * \brief clears our cached geometry data
	 */
	void Renderable::clearGeometryData()
	{
		Utils::safeDeleteArray(m_geometryData.aIndexData);
		Utils::safeDeleteArray(m_geometryData.aVertexData);
		m_geometryData.indexDataCount = 0;
		m_geometryData.vertexDataCount = 0;
	}
}
