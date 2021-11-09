#pragma once

class Block:public DestructibleObject
{
public:
	Block() {}
	~Block() override final;

	/// <summary>
	/// コライダーの初期化。
	/// </summary>
	void InitRayCollider();

	/// <summary>
	/// コライダーの登録、解除。
	/// </summary>
	void SetColliderEnable(bool flag);

	/// <summary>
	/// ダメージを与える。
	/// </summary>
	void Damage(const ToolInfo& tool)override final;

private:
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
	bool m_registColider = false;
};

