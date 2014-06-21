#ifndef ENTITY_H
#define ENTITY_H

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

	private:
		// TODO: something smarter than just a pile of named pointers
		// TODO: pointers from components back to entity
		Scenegraph::GraphNode* m_pNode;
	};

	/*!
	 * \brief determines if this entity is in the scene graph
	 * \return true if we're in the scenegraph
	 */
	inline bool Entity::isInScenegraph() const
	{
		return m_pNode != nullptr;
	}
}

#endif // ENTITY_H
