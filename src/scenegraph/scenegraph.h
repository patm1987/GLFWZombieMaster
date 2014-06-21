#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "graphnode.h"

namespace Scenegraph{
	class GraphNode;

	class Scenegraph
	{
	public:
		Scenegraph();

		GraphNode::Errors addNode(GraphNode* pNode);
		GraphNode::Errors removeNode(GraphNode* pNode);

	private:
		GraphNode m_root;
	};
}

#endif // SCENEGRAPH_H
