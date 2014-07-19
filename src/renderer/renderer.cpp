#include "renderer.h"

#include "entity/entity.h"
#include "shader.h"

namespace Renderer
{
	/*!
	 * \brief Will load the camera for rendering
	 *
	 * The camera will be loaded into the shader if one exists. You will need to
	 * call this again if you want to move this camera
	 *
	 * \param pCamera the camera to render from or nullptr
	 */
	void Renderer::setCamera(Entity::Entity* pCamera)
	{
		m_pCamera = pCamera;
		if (m_pShader && m_pCamera)
		{
			m_pShader->loadCameraParams(*m_pCamera);
		}
	}

	/*!
	 * \brief Will load a shader for rendering
	 *
	 * Currently will also reload camera data
	 *
	 * \param pShader the shader we'll use for any following renderObject
	 *	commands or nullptr
	 */
	void Renderer::setShader(Shader* pShader)
	{
		m_pShader = pShader;
		if (m_pShader)
		{
			pShader->loadShader();
			if(m_pCamera)
			{
				m_pShader->loadCameraParams(*m_pCamera);
			}
		}
	}

	/*!
	 * \brief will render the given object with the previously set camera and
	 *	shader.
	 *
	 * Note that your entity must be in a scenegraph and have a renderable
	 * component on it. Also: a camera and a shader must have been set
	 *
	 * \param entity the entity we want to render
	 */
	void Renderer::renderObject(Entity::Entity& entity)
	{
		assert(entity.isInScenegraph());
		assert(entity.getRenderable());
		assert(m_pCamera);
		assert(m_pCamera->getCamera());
		assert(m_pCamera->isInScenegraph());
		assert(m_pShader);

		if (m_pShader)
		{
			m_pShader->loadObjectParams(entity);
		}
		Entity::Renderable* pRenderable = entity.getRenderable();
		pRenderable->render();
	}
}
