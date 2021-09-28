#pragma once

#include "Util.h"

namespace Engine {

	template<class T>
	class TNameKey {
		using MyString = std::basic_string < T, std::char_traits<T>, std::allocator<T>>;
		MyString m_name;			//���O�B
		unsigned int m_hashCode = 0;
	public:
		TNameKey() {}
		TNameKey( const T* name) 
		{
			Init(name);
		}
		/// <summary>
		/// �������B
		/// </summary>
		/// <param name="name">������</param>
		void Init(const T* name)
		{
			if (name != nullptr) {
				m_name = name;
				//���O���n�b�V�����B
				m_hashCode = Util::MakeHash(name);
			}
		}
		//�n�b�V���R�[�h���擾�B
		unsigned int GetHashCode()const
		{
			return m_hashCode;
		}
		//���O���擾�B
		const T* GetName()const
		{
			return m_name.c_str();
		}
	};//class TNameKey

	using NameKey = TNameKey<char>;
	using WNameKey = TNameKey<wchar_t>;
}//namespace Engine