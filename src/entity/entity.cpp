#include "entity.h"

#include "utils/utils.h"
#include "scenegraph/scenegraph.h"
#include "scenegraph/graphnode.h"

namespace Entity
{
	/*!
	 * \brief ctor for the entity
	 *
	 * TODO: inline in the header
	 */
	Entity::Entity() :
		AutoList<Entity>(*this),
		m_pNode(nullptr),
		m_upRenderable(nullptr),
		m_upCamera(nullptr)
	{
	}

	/*!
	 * \brief destroys this entity, cleaning up its components if necessary
	 */
	Entity::~Entity()
	{
		if (isInScenegraph())
		{
			removeFromSceneGraph();
		}
	}

	/*!
	 * \brief Adds this entity to a scenegraph
	 * \param pGraph the scenegraph to add this entity to
	 * \return any errors that occur
	 */
	Entity::Errors Entity::addToSceneGraph(Scenegraph::Scenegraph* pGraph)
	{
		if (isInScenegraph())
		{
			removeFromSceneGraph();
		}
		if (pGraph)
		{
			m_pNode = new Scenegraph::GraphNode();
			auto error = pGraph->addNode(m_pNode);
			return (error == Scenegraph::GraphNode::Errors::None)
				? Errors::None : Errors::GraphNodeError;
		}
		return Errors::NullGraphNode;
	}

	/*!
	 * \brief removes this entity from the scenegraph
	 */
	void Entity::removeFromSceneGraph()
	{
		if (!isInScenegraph())
		{
			return;
		}

		Utils::safeDelete(m_pNode);
	}
}
