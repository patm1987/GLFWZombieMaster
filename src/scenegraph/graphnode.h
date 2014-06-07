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

		const glm::vec3 &getPosition() const;
		const glm::quat &getRotation() const;
		const glm::vec3 &getScale() const;

		void setPosition(const glm::vec3 &position);
		void setRotation(const glm::quat &rotation);
		void setScale(const glm::vec3 &scale);

	private:
		void setParent(GraphNode* pParent);
		Errors findChild(
				GraphNode* pChild,
				std::vector<GraphNode*>::iterator* pOutIterator);

		void generateLocalToWorldMatrix();
		void generateWorldToLocalMatrix();

		void invalidateTransforms();

		GraphNode* m_pParent;
		std::vector<GraphNode*> m_childList;

		bool m_localToWorldDirty;
		bool m_worldToLocalDirty;

		glm::mat4x4 m_worldToLocal;
		glm::mat4x4 m_localToWorld;

		glm::vec3 m_scale;
		glm::quat m_rotation;
		glm::vec3 m_position;
	};

	/*!
	 * \brief GraphNode::getPosition
	 * \return the position of this graph node
	 */
	inline const glm::vec3 &GraphNode::getPosition() const
	{
		return m_position;
	}

	/*!
	 * \brief GraphNode::getRotation
	 * \return the rotation of this graph node
	 */
	inline const glm::quat &GraphNode::getRotation() const
	{
		return m_rotation;
	}

	/*!
	 * \brief GraphNode::getScale
	 * \return the scale of this graph node
	 */
	inline const glm::vec3 &GraphNode::getScale() const
	{
		return m_scale;
	}

	/*!
	 * \brief GraphNode::setPosition
	 * \param position the new position of this graph node
	 */
	inline void GraphNode::setPosition(const glm::vec3 &position)
	{
		m_position = position;
		invalidateTransforms();
	}

	/*!
	 * \brief GraphNode::setRotation
	 * \param rotation the new rotation of this graph node
	 */
	inline void GraphNode::setRotation(const glm::quat &rotation)
	{
		m_rotation = rotation;
		invalidateTransforms();
	}

	/*!
	 * \brief GraphNode::setScale
	 * \param scale the new scale of this graph node
	 */
	inline void GraphNode::setScale(const glm::vec3 &scale)
	{
		m_scale = scale;
		invalidateTransforms();
	}
}

#endif // GRAPHNODE_H
