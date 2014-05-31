#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

namespace Scenegraph{
	class GraphNode;

	class Scenegraph
	{
	public:
		Scenegraph();

	private:
		GraphNode* pRoot;
	};
}

#endif // SCENEGRAPH_H
