#ifndef SHADER_H
#define SHADER_H

namespace Entity
{
	class Entity;
}

namespace Renderer
{
	class Shader
	{
	public:
		Shader();

		void loadShader(); // apply shader to gl
		void loadCameraParams(Entity::Entity& camera); // load a camera transform
		void loadObjectParams(Entity::Entity& entity); // load an object transform
	};
}

#endif // SHADER_H
