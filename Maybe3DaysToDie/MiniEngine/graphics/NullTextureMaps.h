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

	public:	//アルベド。
		/// <summary> 
		/// アルベドマップを取得。
		/// </summary>
		const std::unique_ptr<char[]>& GetAlbedoMap() const
		{
			return m_albedoMap;
		}
		/// <summary>
		/// アルベドマップのサイズを取得。
		/// </summary>
		unsigned int GetAlbedoMapSize() const
		{
			return m_albedoMapSize;
		}
		/// <summary>
		/// アルベドマップのファイルパスを取得。
		/// </summary>
		const char* GetAlbedoMapFilePath() const
		{
			return m_albedoMapFileName.c_str();
		}

	public:	//法線マップ。
		/// <summary>
		/// 法線マップを取得。
		/// </summary>
		const std::unique_ptr<char[]>& GetNormalMap() const
		{
			return m_normalMap;
		}
		/// <summary>
		/// 法線マップのサイズを取得。
		/// </summary>
		unsigned int GetNormalMapSize() const
		{
			return m_normalMapSize;
		}
		/// <summary>
		/// 法線マップのファイルパスを取得。
		/// </summary>
		const char* GetNormalMapFilePath() const
		{
			return m_normalMapFileName.c_str();
		}

	public:	//スペキュラ。
		/// <summary>
		/// スペキュラマップを取得。
		/// </summary>
		const std::unique_ptr<char[]>& GetSpecularMap() const
		{
			return m_specularMap;
		}
		/// <summary>
		/// スペキュラマップのサイズを取得。
		/// </summary>
		unsigned int GetSpecularMapSize() const
		{
			return m_specularMapSize;
		}
		/// <summary>
		/// スペキュラマップのファイルパスを取得。
		/// </summary>
		const char* GetSpecularMapFilePath() const
		{
			return m_specularMapFileName.c_str();
		}

	public:	//リフレクションマップ。(0マップ)
		/// <summary>
		/// リフレクションマップを取得。
		/// </summary>
		const std::unique_ptr<char[]>& GetReflectionMap() const
		{
			return m_zeroValueMap;
		}
		/// <summary>
		/// リフレクションマップのサイズを取得。
		/// </summary>
		/// <returns></returns>
		unsigned int GetReflectionMapSize() const
		{
			return m_zeroValueMapSize;
		}
		/// <summary>
		/// 反射マップのファイルパスを取得。
		/// </summary>
		const char* GetReflectionMapFilePath() const
		{
			return m_zeroValueMapFileName.c_str();
		}

	public:	//屈折マップ。(0マップ)
		/// <summary>
		/// 屈折マップを取得。
		/// </summary>
		/// <returns></returns>
		const std::unique_ptr<char[]>& GetRefractionMap() const
		{
			return m_zeroValueMap;
		}
		/// <summary>
		/// 屈折マップのサイズを取得。
		/// </summary>
		/// <returns></returns>
		unsigned int GetRefractionMapSize() const
		{
			return m_zeroValueMapSize;
		}
		/// <summary>
		/// 屈折マップのファイルパス取得。
		/// </summary>
		const char* GetRefractionMapFilePath() const
		{
			return m_zeroValueMapFileName.c_str();
		}


	private:
		std::string m_albedoMapFileName;			//アルベドマップのファイル名。
		std::string m_normalMapFileName;			//法線マップのファイル名。
		std::string m_specularMapFileName;			//スペキュラマップのファイル名。
		std::string m_zeroValueMapFileName;		//リフレクションマップのファイル名。

		std::unique_ptr<char[]>	m_albedoMap;		//ロードされたアルベドマップ。(ddsファイル)
		unsigned int m_albedoMapSize;				//アルベドマップのサイズ。(ddsファイル)

		std::unique_ptr<char[]>	m_normalMap;		//ロードされた法線マップ。(ddsファイル)
		unsigned int m_normalMapSize;				//法線マップのサイズ。

		std::unique_ptr<char[]>	m_specularMap;		//ロードされたスペキュラマップ。(ddsファイル)
		unsigned int m_specularMapSize;				//スペキュラマップのサイズ。(ddsファイル)

		std::unique_ptr<char[]> m_zeroValueMap;		//0の値を格納しているマップ。
		unsigned int m_zeroValueMapSize = 0;		//0の値を格納しているマップのサイズ。
	};
}

