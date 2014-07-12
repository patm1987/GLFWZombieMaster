#ifndef UTILS_H
#define UTILS_H

namespace Utils
{
	/*!
	 * \brief safely delete an object (check if not null)
	 * \param pT a pointer to the object we want to delete
	 */
	template<typename T>
	static void safeDelete(T*& pT)
	{
		if (pT != nullptr)
		{
			delete pT;
			pT = nullptr;
		}
	}

	template<typename T>
	static void safeDeleteArray(T*& paT)
	{
		if (paT != nullptr)
		{
			delete[] paT;
			paT = nullptr;
		}
	}
}

#endif // UTILS_H
