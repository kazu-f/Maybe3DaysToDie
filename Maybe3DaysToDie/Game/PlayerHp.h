#pragma once
class PlayerHp final : public IGameObject
{
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>true���Ԃ�܂Ń��[�v����</returns>
	bool Start()override final;
	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override final;
	/// <summary>
	/// 
	/// </summary>
	void OnDestroy()override final;


};

