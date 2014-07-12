#ifndef SINGLETON_H
#define SINGLETON_H

#include "utils.h"

namespace Utils
{
	template<typename T>
	class Singleton
	{
	public:
		enum class Errors
		{
			None,
			AlreadyInitialized,
			NotYetInitialized
		};

	public:
		static Errors initialize();
		static Errors destroy();
		static T& instance();

	private:
		static T* s_pInstance;
	};

	template <typename T>
	T Singleton<T>::s_pInstance = nullptr;

	template <typename T>
	typename Singleton<T>::Errors Singleton<T>::initialize()
	{
		if (s_pInstance != nullptr)
		{
			return Errors::AlreadyInitialized;
		}
		s_pInstance = new T();
		return Errors::None;
	}

	template <typename T>
	typename Singleton<T>::Errors Singleton<T>::destroy()
	{
		if (s_pInstance == nullptr)
		{
			return Errors::NotYetInitialized;
		}
		Utils::safeDelete(s_pInstance);
		return Errors::None;
	}

	template <typename T>
	T& Singleton<T>::instance()
	{
		return *s_pInstance;
	}
}

#endif // SINGLETON_H
