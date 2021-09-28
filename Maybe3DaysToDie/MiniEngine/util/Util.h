#pragma once

namespace Engine {
	/// <summary>
	/// Util�N���X�B
	/// </summary>

	class Util {
	public:
		/// <summary>
		/// �����񂩂�32bit�̃n�b�V���l���쐬�B
		/// </summary>
		static int MakeHash(const char* string)
		{
			if (string == nullptr)
			{
				return 0;
			}
			int hash = 0;									//�n�b�V���l�B
			int l = static_cast<int>(strlen(string));		//������̒����B
			//�n�b�V���l���쐬�B
			for (int i = 0; i < l; i++) {
				hash = hash * 37 + string[i];
			}
			return hash;
		}
		/// <summary>
		/// �����񂩂�32bit�̃n�b�V���l���쐬�B
		/// </summary>
		static int MakeHash(const wchar_t* string)
		{
			if (string == nullptr)
			{
				return 0;
			}
			int hash = 0;									//�n�b�V���l�B
			int l = static_cast<int>(wcslen(string));		//������̒����B
			//�n�b�V���l���쐬�B
			for (int i = 0; i < l; i++) {
				hash = hash * 37 + string[i];
			}
			return hash;
		}
	};

}