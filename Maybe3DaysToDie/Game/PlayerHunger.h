#pragma once
/// <summary>
/// �v���C���[�̋󕠓x��\���N���X
/// </summary>
class PlayerHunger : public IGameObject
{
private:
	/// <summary>
	/// New���ꂽ����GameObject����Ă΂�� 
	/// �������p�֐�
	/// </summary>
	/// <returns>true���Ԃ�܂Ń��[�v����</returns>
	bool Start() override final;

	/// <summary>
	/// ���t���[���Ă΂��X�V�֐�
	/// </summary>
	void Update()override final;

	/// <summary>
	/// delete������GameObject����Ă΂��֐�
	/// </summary>
	void OnDestroy()override final;

private:
	prefab::CSpriteRender* m_CrrentSprite = nullptr;
	prefab::CSpriteRender* m_FrameSprite = nullptr;

};

