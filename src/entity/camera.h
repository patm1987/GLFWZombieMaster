#ifndef CAMERA_H
#define CAMERA_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils/utils.h"

namespace Entity
{
	/*!
	 * \brief Represents a camera in the world
	 */
	class Camera
	{
	public:
		/*!
		 * \brief Various kinds of supported camera configurations
		 */
		enum class ConfigType
		{
			None, //!< \brief the camera has not been configured
			Orthographic, //!< \brief the camera is an orthographic camera
			Perspective, //!< \brief the camera was configured via frustum points
			PerspectiveFov //!< \brief the camera was configured with vfov
		};

		struct OrthoConfig;
		struct PerspectiveConfig;
		struct PerspectiveFovConfig;

	public:
		Camera();

		template<typename T>
		void configure(const T& config);

		ConfigType getConfigType() const;

		template<typename T>
		const T* getConfiguration() const;

		void clearConfiguration();

	private:
		ConfigType m_configType;
		void* m_pConfiguration;
		glm::mat4x4 m_perspectiveProjectionMatrix;

	public:
		/*!
		 * \brief Describes an orthogrphic camera
		 */
		struct OrthoConfig
		{
			float top, bottom, left, right, nearPlane, farPlane;
			glm::mat4x4 generateMatrix() const;
			static const ConfigType configType = ConfigType::Orthographic;
		};

		/*!
		 * \brief Describes a perspective camera configured via six points
		 */
		struct PerspectiveConfig
		{
			float top, bottom, left, right, nearPlane, farPlane;
			glm::mat4x4 generateMatrix() const;
			static const ConfigType configType = ConfigType::Perspective;
		};

		struct PerspectiveFovConfig
		{
			float vfov, aspect, nearPlane, farPlane;
			glm::mat4x4 generateMatrix() const;
			static const ConfigType configType = ConfigType::PerspectiveFov;
		};
	};

	inline Camera::Camera() :
		m_configType(ConfigType::None),
		m_pConfiguration(nullptr),
		m_perspectiveProjectionMatrix()
	{}

	/*!
	 * \brief	Logic to configure a camera based on a configuration
	 * \param config	the configuration with which the camera will be
	 *		configured.
	 */
	template<typename T>
	void Camera::configure(const T& config)
	{
		Utils::safeDelete(m_pConfiguration);
		T* pConfig = new T(config);
		m_perspectiveProjectionMatrix = pConfig->generateMatrix();
		m_pConfiguration = pConfig;
		m_configType = pConfig->configType;
	}

	/*!
	 * \brief retrieves the configuration type used to configure the camera.
	 *	This can be used to operate on the configuration at run time
	 *
	 * \return the type of configuration used to configure the camera
	 */
	inline Camera::ConfigType Camera::getConfigType() const
	{
		return m_configType;
	}

	/*!
	 * \brief	retrieves the configuration for the camera. If you request a different
	 *	configuration type than the one used, you will get nullptr
	 */
	template<typename T>
	const T* Camera::getConfiguration() const
	{
		// you're a wizard harry!
		if (getConfigType() == T::configType)
		{
			return reinterpret_cast<T*>(m_pConfiguration);s
		}
		return nullptr;
	}

	/*!
	 * \brief clears the camera's configuration
	 */
	inline void Camera::clearConfiguration()
	{
		m_configType = ConfigType::None;
		Utils::safeDelete(m_pConfiguration);
		m_perspectiveProjectionMatrix = glm::mat4x4();
	}

	// matrix generation!
	inline glm::mat4x4 Camera::OrthoConfig::generateMatrix() const
	{
		return glm::ortho(left, right, bottom, top, nearPlane, farPlane);
	}

	inline glm::mat4x4 Camera::PerspectiveConfig::generateMatrix() const
	{
		return glm::frustum(left, right, bottom, top, nearPlane, farPlane);
	}

	inline glm::mat4x4 Camera::PerspectiveFovConfig::generateMatrix() const
	{
		return glm::perspective(vfov, aspect, nearPlane, farPlane);
	}
}

#endif // CAMERA_H
