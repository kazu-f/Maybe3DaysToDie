#pragma once
class Stage : public IGameObject
{
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>true��Ԃ��܂Ń��[�v����</returns>
	bool Start();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// delete������ƌĂ΂��֐�
	/// </summary>
	void OnDestroy();

	/// <summary>
	/// �n�ʂ�\������
	/// </summary>
	void NewGround();
private:
	prefab::ModelRender* m_Model = nullptr;		//�n��
};

