#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <vector>

#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Scenegraph
{
	/*!
	 * \brief Represents a node in a scene graph
	 */
	class GraphNode
	{
	public:
		/*!
		 * \brief Represents possible errors raised by the scenegraph
		 */
		enum class Errors
		{
			None,        //!< No error raised
			ChildExists, //!< Attempted to double add a child
			NotFound,    //!< Unable to find something in a search
			NullArgument //!< Required argument was null
		};

	public:
		GraphNode();
		~GraphNode();

		Errors addChild(GraphNode* pChild);
		Errors removeChild(GraphNode* pChild);
		bool hasChild(GraphNode* pChild);

		GraphNode* getParent() const;

		const glm::mat4x4& getLocalToWorldTransform();
		const glm::mat4x4& getWorldToLocalTransform();



	private:
		void setParent(GraphNode* pParent);
		Errors findChild(
				GraphNode* pChild,
				std::vector<GraphNode*>::iterator* pOutIterator);

		GraphNode* m_pParent;
		std::vector<GraphNode*> m_childList;

		bool m_localToWorldDirty;
		bool m_worldToLocalDirty;

		glm::mat4x4 m_worldToLocal;
		glm::mat4x4 m_localToWorld;

		glm::vec3 m_scale;
		glm::quat m_quaternion;
		glm::vec3 m_position;
	};
}

#endif // GRAPHNODE_H
