#pragma once

#include "TerrainManager/TerrainRender/TerrainRender.h"

/// <summary>
/// ナビゲーションメッシュ生成クラス。
/// </summary>
/// <remarks>
/// このクラスは、サンドボックスのステージからNVMを動的生成するクラス。
/// ステージに変更があった際にもNVM変更する処理が走る（予定）。
/// ブロック１単位を2メッシュとして扱う為、サンドボックス型でのみしか機能しない。
/// </remarks>
class NVMGenerator
{
public:
	NVMGenerator();
	~NVMGenerator();
public:
	/// <summary>
	/// 地形データよりNVMを作成する。
	/// </summary>
	/// <param name="terrain">地形。</param>
	void CreateNVM(nsTerrain::TerrainRender* terrain);
	/// <summary>
	/// 地形データよりNVMを更新する。
	/// <para>ブロックが破壊されたらチャンク分NVMの更新を行う。</para>
	/// </summary>
	/// <param name="terrain"></param>
	void UpdateNVM(nsTerrain::TerrainRender* terrain);
	/// <summary>
	/// デバッグ描画。
	/// </summary>
	/// <param name="isEnableDebug">デバッグ描画する？</param>
	void DebugDraw(bool& isEnableDebug);
private:
	static bool isInstantiate;		//インスタンスが作成されているか。

};

