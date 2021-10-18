#pragma once

/// <summary>
/// ナビゲーションメッシュ生成クラス。
/// </summary>
/// <remarks>
/// このクラスは、サンドボックスのステージからNVMを動的生成するクラス。
/// ステージに変更があった際にもNVM変更する処理が走る（予定）。
/// ブロック１単位を2メッシュとして扱う為、サンドボックス型でのみしか機能しない。
/// また、このクラスはstaticクラス実装のためインスタンス化は必要としない。
/// </remarks>

class Terrain;

class NVMGenerator
{
private:
	NVMGenerator();
public:
	/// <summary>
	/// 地形データよりNVMを作成する。
	/// </summary>
	/// <param name="terrain">地形。</param>
	static void CreateNVM(Terrain& terrain);
	/// <summary>
	/// 地形データよりNVMを更新する。
	/// </summary>
	/// <param name="terrain"></param>
	static void UpdateNVM(Terrain& terrain);
private:

};

