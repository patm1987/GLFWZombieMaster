#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

// note: can't forward-declare camera and renderable because: unique_ptr
#include "camera.h"
#include "renderable.h"
#include "utils/autolist.h"

namespace Scenegraph
{
	class Scenegraph;
	class GraphNode;
}

namespace Entity
{
	/*!
	 * \brief Represents any Entity in the game
	 *
	 * \note is an auto list to get a list of all the entities
	 */
	class Entity : public Utils::AutoList<Entity>
	{
	public:
		/*!
		 * \brief The possible errors Entity will raise
		 */
		enum class Errors
		{
			None, //!< \brief no error
			GraphNodeError, //!< \brief there was an error in the graph node
			NullGraphNode //!< \brief there was no graph node
		};

	public:
		Entity();
		~Entity();

		Entity::Errors addToSceneGraph(Scenegraph::Scenegraph* pGraph);
		void removeFromSceneGraph();
		bool isInScenegraph() const;

		void setCamera(std::unique_ptr<Camera>& camera);
		void setRenderable(std::unique_ptr<Renderable>& renderable);

		Scenegraph::GraphNode* getGraphNode();
		Renderable* getRenderable();
		Camera* getCamera();

	private:
		// TODO: something smarter than just a pile of named pointers
		// TODO: pointers from components back to entity

		/*!
		 * \brief our position in the scene graph
		 * \todo move from normal pointers for more c++14 awesomeness
		 */
		Scenegraph::GraphNode* m_pNode;

		/*!
		 * \brief our renderable for rendering (if any)
		 *
		 * Since we're given it, use a unique_ptr so others don't try to free
		 * our precious precious memory
		 */
		std::unique_ptr<Renderable> m_upRenderable;

		/*!
		 * \brief the camera on this object (if any)
		 *
		 * Since we're given this, we'll use a unique_ptr so sothers don't try
		 * to free our memory!
		 */
		std::unique_ptr<Camera> m_upCamera;
	};

	/*!
	 * \brief determines if this entity is in the scene graph
	 * \return true if we're in the scenegraph
	 */
	inline bool Entity::isInScenegraph() const
	{
		return m_pNode != nullptr;
	}

	/*!
	 * \brief If we want a camera on this entity, set it here
	 * \param camera the camera we want to store on this entity
	 * \note we'll claim ownership of \a camera
	 */
	inline void Entity::setCamera(std::unique_ptr<Camera>& camera)
	{
		m_upCamera = std::move(camera);
	}

	/*!
	 * \brief If we want to render this entity, add a renderable here
	 * \param renderable used to render this object
	 * \note we'll claim ownership of this \a renderable
	 */
	inline void Entity::setRenderable(std::unique_ptr<Renderable>& renderable)
	{
		m_upRenderable = std::move(renderable);
	}

	/*!
	 * \brief if we're in the scenegraph, this will tell us where
	 * \return our location in the scenegraph
	 */
	inline Scenegraph::GraphNode* Entity::getGraphNode()
	{
		return m_pNode;
	}

	/*!
	 * \brief if we can be rendered, retrieve an instance of the renderer
	 * \return the renderer if we have one, or nullptr
	 */
	inline Renderable* Entity::getRenderable()
	{
		return m_upRenderable.get();
	}

	/*!
	 * \brief if we're a camera, retrieve it
	 * \return our camera or nullptr if none
	 */
	inline Camera* Entity::getCamera()
	{
		return m_upCamera.get();
	}
}

#endif // ENTITY_H
