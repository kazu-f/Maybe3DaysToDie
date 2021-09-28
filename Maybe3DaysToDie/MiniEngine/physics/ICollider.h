#pragma once

class btCollisionShape;

namespace Engine {

	/// <summary>
	/// �R���C�_�[�̃C���^�[�t�F�[�X�N���X�B
	/// </summary>
	class ICollider : Noncopyable
	{
	public:
		virtual ~ICollider() {};
		virtual btCollisionShape* GetBody()const = 0;
	};
}

