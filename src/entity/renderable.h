#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Entity
{
	/*!
	 * \brief Represents an object that can be rendered
	 */
	class Renderable
	{
	public:
		struct VertexData
		{
			glm::vec3 position;
			glm::vec3 normal;
		};

		struct GeometryData
		{
			VertexData* aVertexData;
			int32_t vertexDataCount;
			uint16_t* aIndexData;
			int32_t indexDataCount;
		};

		enum class VertexAttributes
		{
			Position,
			Normal
		};

	public:
		Renderable();
		~Renderable();

		void render();

		// Note to implementor: copy data in and take ownership
		// Note to user: clean up geometry data afterwards, it is copied
		void setGeometry(const GeometryData& geometryData);

	private:
		void clearGeometryData();

		GLuint m_vertexBuffer; //!< the vertex buffer to draw
		GLuint m_indexBuffer; //!< the index buffer to draw

		/*!
		 * \brief the color of the object to render
		 */
		glm::vec4 m_color;

		/*!
		 * \brief the geometry needed
		 * \note most of this is uneeded, I can get away with just storing
		 *	vertex and index counts...
		 */
		GeometryData m_geometryData;
	};
}

#endif // RENDERABLE_H
