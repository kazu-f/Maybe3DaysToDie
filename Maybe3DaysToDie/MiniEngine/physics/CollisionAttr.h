#pragma once
/// <summary>
/// �R���W���������B
/// </summary>

namespace ColliderUserIndex {

	enum EnCollisionAttr {
		enCollisionAttr_None = 0,		//���������B
		enCollisionAttr_Ground = 1 << 0,		//�n�`�B
		enCollisionAttr_Character = 1 << 1,	//�L�����N�^�[�B
		enCollisionAttr_RayBlock = 1 << 2,	//�������Ղ�B
		enCollisionAttr_Ground_RayBlock = enCollisionAttr_Ground | enCollisionAttr_RayBlock,		//�n�`�Ŋ����C���Ղ�B
		enCollisionAttr_ALL = 0xffffffff,		//�ő�l�B
	};
}