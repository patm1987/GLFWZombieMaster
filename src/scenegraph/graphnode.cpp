#include "graphnode.h"

#include <glm/gtx/transform.hpp>

namespace Scenegraph
{
	/*!
	 * \brief default ctor
	 */
	GraphNode::GraphNode() :
		m_localToWorldDirty(true),
		m_worldToLocalDirty(true),
		m_scale(1.f, 1.f, 1.f),
		m_rotation(1.f, 0.f, 0.f, 0.f),
		m_position(0.f, 0.f, 0.f)
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
	 * \brief generates a transform that takes an object from local space to
	 *		world space
	 * \return the transform that takes any local object to world space
	 */
	const glm::mat4x4& GraphNode::getLocalToWorldTransform()
	{
		if (m_localToWorldDirty)
		{
			generateLocalToWorldMatrix();
		}
		return m_localToWorld;
	}

	/*!
	 * \brief gets the transform that takes any world object to local space
	 * \return the transform from world space to local space
	 */
	const glm::mat4x4& GraphNode::getWorldToLocalTransform()
	{
		if (m_worldToLocalDirty)
		{
			generateWorldToLocalMatrix();
		}
		return m_worldToLocal;
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
		if (pParent != m_pParent)
		{
			m_pParent = pParent;
			invalidateTransforms();
		}
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

	/*!
	 * \brief generates the local to world matrix
	 * \note This should typically be gated by the m_localToWorldDirty flag
	 */
	void GraphNode::generateLocalToWorldMatrix()
	{
		glm::mat4x4 scale = glm::scale(m_scale);
		glm::mat4x4 rot = glm::mat4_cast(m_rotation);
		glm::mat4x4 trans = glm::translate(m_position);

		glm::mat4x4 local = trans * rot * scale;

		if (m_pParent)
		{
			m_localToWorld = m_pParent->getLocalToWorldTransform() * local;
		}
		else
		{
			m_localToWorld = local;
		}

		m_localToWorldDirty = false;
	}

	/*!
	 * \brief generates the world to local matrix
	 * \note should typically be gated by the m_worldToLocalDirty flag
	 */
	void GraphNode::generateWorldToLocalMatrix()
	{
		glm::mat4x4 scale = glm::scale(1.f / m_scale);
		glm::mat4x4 rot = glm::mat4_cast(glm::conjugate(m_rotation));
		glm::mat4x4 trans = glm::translate(-m_position);

		glm::mat4x4 local = scale * rot * trans;
		if (m_pParent)
		{
			m_worldToLocal = local * m_pParent->getWorldToLocalTransform();
		}
		else
		{
			m_worldToLocal = local;
		}

		m_worldToLocalDirty = false;
	}

	/*!
	 * \brief invalidates all matrices
	 */
	void GraphNode::invalidateTransforms()
	{
		m_localToWorldDirty = true;
		m_worldToLocalDirty = true;
	}
}
