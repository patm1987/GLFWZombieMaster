#ifndef AUTOLIST_H
#define AUTOLIST_H

namespace Utils
{
	/*!
	 * \brief A list that automatically tracks all elements of a given type
	 *
	 * Usage:
	 *  * create a class (lets call it cls) that inherits from AutoList<cls>
	 *  * in the ctor, add itself to the auto list
	 *
	 * you can now get all the objects of type cls by calling cls::getList
	 * you can iterate over all the objects by doing:
	 * for(auto node : cls::getList())
	 * {
	 *  cls c = node.value;
	 * }
	 */
	template<typename T>
	class AutoList
	{
	public:
		AutoList(T& t);
		~AutoList();

		AutoList<T>* begin();
		AutoList<T>* end();

		T& value();
		const T& value() const;

		static AutoList<T>& getList();

	private:
		T& m_t; //!< a reference to the type we're tracking to avoid dynamic_cast

		AutoList<T>* m_pPrev; //!< the previous T
		AutoList<T>* m_pNext; //!< the next T

		static AutoList<T>* s_pFirst; //!< the first T or nullptr if none exist
	};

	/*!
	 * \brief Default ctor: must provide a base class to resolve to
	 * \param t the object that will be returned with the value() call
	 */
	template <typename T>
	AutoList<T>::AutoList(T& t) : m_t(t)
	{
		m_pNext = s_pFirst;
		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = this;
		}
		m_pPrev = nullptr;
	}

	template <typename T>
	AutoList<T>::~AutoList()
	{
		if (s_pFirst == this)
		{
			s_pFirst = m_pNext;
		}
		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = m_pPrev;
		}
		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = m_pNext;
		}
	}

	/*!
	 * \brief the first item in the list
	 * \note for use with the ranged for expression in C++11
	 * \return the first item in the list
	 */
	template<typename T>
	AutoList<T>* AutoList<T>::begin()
	{
		return s_pFirst;
	}

	/*!
	 * \brief gets the item after the end of the list
	 * \note for use with the ranged for expression in C++11
	 * \return nullptr
	 */
	template<typename T>
	AutoList<T>* AutoList<T>::end()
	{
		return nullptr;
	}

	/*!
	 * \return the item this is an AutoList of, to avoid dynamic_cast
	 */
	template<typename T>
	T& AutoList<T>::value()
	{
		return m_t;
	}

	/*!
	 * \return the item this is an AutoList of, to avoid dynamic_cast
	 */
	template<typename T>
	const T& AutoList<T>::value() const
	{
		return m_t;
	}

	/*!
	 * \return the beginning of the list, intended for use with the ranged for
	 */
	template<typename T>
	AutoList<T>& AutoList<T>::getList()
	{
		return *s_pFirst;
	}

	template <typename T>
	AutoList<T>* AutoList<T>::s_pFirst = nullptr;
}

#endif // AUTOLIST_H
