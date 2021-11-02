#pragma once
/// <summary>
/// コリジョン属性。
/// </summary>

namespace ColliderUserIndex {

	enum EnCollisionAttr {
		enCollisionAttr_None = 0,		//属性無し。
		enCollisionAttr_Ground = 1 << 0,		//地形。
		enCollisionAttr_Character = 1 << 1,	//キャラクター。
		enCollisionAttr_RayBlock = 1 << 2,	//視線を遮る。
		enCollisionAttr_Ground_RayBlock = enCollisionAttr_Ground | enCollisionAttr_RayBlock,		//地形で且つレイを遮る。
		enCollisionAttr_ALL = 0xffffffff,		//最大値。
	};
}