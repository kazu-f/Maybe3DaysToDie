#pragma once

class Block:public DestructibleObject
{
public:
	Block() {}
	~Block() override final;
	/// <summary>
	/// ダメージを与える。
	/// </summary>
	void Damage(const ToolInfo& tool)override final
	{

	}

	/// <summary>
	/// コライダーの初期化。
	/// </summary>
	void InitRayCollider();

};

