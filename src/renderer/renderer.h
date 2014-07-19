#ifndef RENDERER_H
#define RENDERER_H

#include "utils/singleton.h"

namespace Entity
{
	class Entity;
}

namespace Scenegraph
{
	class GraphNode;
}

namespace Renderer
{
	class Shader;

	class Renderer : public Utils::Singleton<Renderer>
	{
	public:
		Renderer();

		void setCamera(Entity::Entity* pCamera);
		void setShader(Shader* pShader);
		void renderObject(Entity::Entity& entity);

	private:
		Entity::Entity* m_pCamera; //!< the camera we want to render with
		Shader* m_pShader; //!< the shader we want to render with
	};

	inline Renderer::Renderer() :
		m_pCamera(nullptr),
		m_pShader(nullptr)
	{
	}
}

#endif // RENDERER_H
