#include "scenegraph.h"

namespace Scenegraph
{
	Scenegraph::Scenegraph()
	{
	}

	/*!
	 * \brief Adds some node to the SceneGraph
	 * \param pNode the node to add
	 * \return an error if it occurs
	 */
	GraphNode::Errors Scenegraph::addNode(GraphNode *pNode)
	{
		return m_root.addChild(pNode);
	}

	/*!
	 * \brief Removes a node from the scenegraph if it exists
	 * \param pNode the node to try to remove
	 * \return any errors that occur
	 */
	GraphNode::Errors Scenegraph::removeNode(GraphNode *pNode)
	{
		return m_root.removeChild(pNode);
	}
}
