#pragma once
/// <summary>
/// コリジョン属性。
/// </summary>

namespace CollideUserIndex {
	enum EnCollisionAttr {
		enCollisionAttr_Ground,		//地形。
		enCollisionAttr_Character,	//キャラクター。
		enCollisionAttr_RayBlock,	//視線を遮る。
		enCollisionAttr_User,		//ユーザー定義。
	};
}