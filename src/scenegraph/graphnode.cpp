#include "graphnode.h"

#include <algorithm>

namespace Scenegraph
{
	/*!
	 * \brief default ctor
	 */
	GraphNode::GraphNode() :
		m_localToWorldDirty(true),
		m_worldToLocalDirty(true)
	{
	}

	/*!
	 * \brief default dtor
	 */
	GraphNode::~GraphNode()
	{
		if (getParent())
		{
			getParent()->removeChild(this);
		}

		for (auto child : m_childList)
		{
			child->setParent(nullptr);
		}
	}

	/*!
	 * \brief Adds a child node to this graph node
	 * \param pChild the child to add
	 * \return Errors::None if successfull
	 *		Errors::NullArgument if pChild was null
	 *		Errors::ChildExists if pChild is already in this node
	 */
	GraphNode::Errors GraphNode::addChild(GraphNode* pChild)
	{
		if (!pChild)
		{
			return Errors::NullArgument;
		}

		if (hasChild(pChild))
		{
			return Errors::ChildExists;
		}

		pChild->setParent(this);
		m_childList.push_back(pChild);

		return Errors::None;
	}

	/*!
	 * \brief removes a child from this graph node
	 * \param pChild the child to remove
	 * \return Errors::None on success
	 *		Errors::NullArgument if pChild was null
	 *		additional errors possible
	 */
	GraphNode::Errors GraphNode::removeChild(GraphNode* pChild)
	{
		if (!pChild)
		{
			return Errors::NullArgument;
		}

		std::vector<GraphNode*>::iterator elementToRemove;
		Errors error = findChild(pChild, &elementToRemove);
		if (error != Errors::None)
		{
			return error;
		}

		m_childList.erase(elementToRemove);
		pChild->setParent(nullptr);

		return Errors::None;
	}

	/*!
	 * \brief Determines if this node contains a child
	 * \param pChild the child that we're looking for
	 * \return true if pChild is contained herein
	 */
	bool GraphNode::hasChild(GraphNode* pChild)
	{
		return findChild(pChild, nullptr) == Errors::None;
	}

	/*!
	 * \brief Gets the parent of this graph node
	 * \return this node's parent
	 * \todo inline in the header!
	 */
	GraphNode* GraphNode::getParent() const
	{
		return m_pParent;
	}

	/*!
	 * \brief Sets the parent node of this object
	 * \param pParent the new parent
	 * \note this is called automatically when adding or removing children,
	 *		this will therefore fail to remove itself from the parent's
	 *		children if called outside of this context
	 */
	void GraphNode::setParent(GraphNode* pParent)
	{
		// WARNING: only call from add child or remove child
		m_pParent = pParent;
	}

	/*!
	 * \brief Finds a child in this graph node
	 * \param pChild the child to find
	 * \param pOutIterator an iterator representing this child
	 * \return Errors::None on success
	 *		Errors::NullArgument if there isn't any iterator in which to store
	 *			the result
	 *		Errors::NotFound if the child isn't found
	 */
	GraphNode::Errors GraphNode::findChild(
			GraphNode* pChild,
			std::vector<GraphNode*>::iterator* pOutIterator)
	{
		if (!pOutIterator)
		{
			return Errors::NullArgument;
		}

		auto result = std::find(m_childList.begin(), m_childList.end(), pChild);
		if (result == m_childList.end())
		{
			return Errors::NotFound;
		}

		if (pOutIterator)
		{
			*pOutIterator = result;
		}
		return Errors::None;
	}
}
