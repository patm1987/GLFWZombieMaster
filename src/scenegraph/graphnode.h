#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <vector>

#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Scenegraph
{
	class GraphNode
	{
	public:
		enum class Errors
		{
			None,
			ChildExists,
			NotFound,
			NullArgument
		};

	public:
		GraphNode();
		~GraphNode();

		Errors addChild(GraphNode* pChild);
		Errors removeChild(GraphNode* pChild);
		bool hasChild(GraphNode* pChild);

		GraphNode* getParent() const;

	private:
		void setParent(GraphNode* pParent);
		Errors findChild(GraphNode* pChild, std::vector<GraphNode*>::iterator* pOutIterator);

		GraphNode* m_pParent;
		std::vector<GraphNode*> m_childList;

		glm::vec3 m_scale;
		glm::quat m_quaternion;
		glm::vec3 m_position;
	};
}

#endif // GRAPHNODE_H
