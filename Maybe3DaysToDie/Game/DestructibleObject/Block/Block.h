#pragma once

class Block:public DestructibleObject
{
public:
	Block() {}
	~Block() override final;
	/// <summary>
	/// �_���[�W��^����B
	/// </summary>
	void Damage(const ToolInfo& tool)override final
	{

	}

	/// <summary>
	/// �R���C�_�[�̏������B
	/// </summary>
	void InitRayCollider();

};

