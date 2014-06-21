#ifndef UTILS_H
#define UTILS_H

namespace Utils
{
	/*!
	 * \brief safely delete an object (check if not null)
	 * \param pT a pointer to the object we want to delete
	 */
	template<typename T>
	static void safeFree(T* pT)
	{
		if (pT != nullptr) { delete pT; }
	}
}

#endif // UTILS_H
