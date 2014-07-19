#include "shader.h"

#include "entity/entity.h"

namespace Renderer
{
	Shader::Shader()
	{
	}

	/*!
	 * \brief Will apply this shader to the gl state
	 */
	void Shader::loadShader()
	{
		assert(false);
	}

	/*!
	 * \brief will load the given camera into the shader
	 *
	 * Note that the shader should be currently active (call after loadShader)
	 * Note that the \a camera should be in the scenegraph and have a camera
	 *
	 * \param camera the camera to load
	 */
	void Shader::loadCameraParams(Entity::Entity &camera)
	{
		assert(camera.isInScenegraph());
		assert(camera.getCamera());

		assert(false);
	}

	/*!
	 * \brief will load the given object data into the shader
	 *
	 * Note that the shader must be currently active (call after loadShader)
	 * Note that the \a entity should be in the scenegraph and have a renderer
	 *
	 * \param entity to load the parameters of
	 */
	void Shader::loadObjectParams(Entity::Entity &entity)
	{
		assert(entity.isInScenegraph());
		assert(entity.getRenderable());

		assert(false);
	}
}
