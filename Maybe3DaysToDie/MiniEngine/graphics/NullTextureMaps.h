#pragma once

namespace Engine {
	/// <summary>
	/// Nullテクスチャマップを保持するクラス。
	/// </summary>
	/// <remarks>
	/// テクスチャが設定されてなければNullテクスチャを適用させる。
	/// Specマップなら0,Normalマップなら凹凸無し、反射マップなら0のマップとなる。
	/// </remarks>
	class NullTextureMaps
	{
	public:
		/// <summary>
		/// Nullテクスチャマップを読み込み。
		/// </summary>
		void Init();


	private:
		std::string m_albedoMapFileName;			//アルベドマップのファイル名。
		std::string m_normalMapFileName;			//法線マップのファイル名。
		std::string m_specularMapFileName;		//スペキュラマップのファイル名。
		std::string m_reflectionMapFileName;		//リフレクションマップのファイル名。
		std::string m_refractionMapFileName;		//屈折率マップのファイル名。

		std::unique_ptr<char[]>	m_albedoMap;		//ロードされたアルベドマップ。(ddsファイル)
		unsigned int m_albedoMapSize;				//アルベドマップのサイズ。(ddsファイル)

		std::unique_ptr<char[]>	m_normalMap;		//ロードされた法線マップ。(ddsファイル)
		unsigned int m_normalMapSize;				//法線マップのサイズ。

		std::unique_ptr<char[]>	m_specularMap;	//ロードされたスペキュラマップ。(ddsファイル)
		unsigned int m_specularMapSize;			//スペキュラマップのサイズ。(ddsファイル)

		std::unique_ptr<char[]>	m_reflectionMap;	//ロードされたリフレクションマップ。(ddsファイル)
		unsigned int m_reflectionMapSize;			//リフレクションマップのサイズ。

		std::unique_ptr<char[]>	m_refractionMap;	//ロードされた屈折率マップ。(ddsファイル)
		unsigned int m_refractionMapSize;			//屈折率マップのサイズ。(ddsファイル)
	};
}

