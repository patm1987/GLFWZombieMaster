#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <GLFW/glfw3.h>
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

	public:
		Renderable();
		~Renderable();

		void render();

		// Note to implementor: copy data in and take ownership
		// Note to user: clean up geometry data afterwards, it is copied
		void setGeometry(const GeometryData& geometryData);

	private:
		void clearGeometryData();
		void initBuffers();

		GLuint m_objectBuffer;

		/*!
		 * \brief the color of the object to render
		 */
		glm::vec4 m_color;
		GeometryData m_geometryData;
	};
}

#endif // RENDERABLE_H
