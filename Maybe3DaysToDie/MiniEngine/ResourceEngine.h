#pragma once

namespace Engine {

	class CResourceEngine : Noncopyable
	{
	public:
		/// <summary>
		/// tkmファイルをバンクから取得。
		/// </summary>
		/// <param name="filePath">ファイルパス</param>
		/// <returns>tkmファイル。nullptrが返ってきたらバンクに登録されていない。</returns>
		TkmFile* GetTkmFileFromBank(const char* filePath)
		{
			return m_tkmBank.Get(filePath);
		}
		/// <summary>
		/// tksファイルをバンクから取得。
		/// </summary>
		/// <param name="filePath">ファイルパス</param>
		/// <returns>tksファイル。nullptrが返ってきたらバンクに登録されていない。</returns>
		TksFile* GetTksFileFromBank(const char* filePath)
		{
			return m_tksBank.Get(filePath);
		}
		/// <summary>
		/// tkmファイルをバンクに登録。
		/// </summary>
		/// <param name="filePath">tkmファイルパス</param>
		/// <param name="tkmFile"></param>
		void RegistTkmFileToBank(const char* filePath, TkmFile* tkmFile)
		{
			m_tkmBank.Regist(filePath, tkmFile);
		}
		/// <summary>
		/// tksファイルをバンクに登録。
		/// </summary>
		/// <param name="filePath">tksファイルパス</param>
		/// <param name="tkmFile"></param>
		void RegistTksFileToBank(const char* filePath, TksFile* tksFile)
		{
			m_tksBank.Regist(filePath, tksFile);
		}
		/// <summary>
		/// テクスチャをバンクに登録。
		/// </summary>
		/// <param name="filePath">ファイルパス。</param>
		/// <param name="texture">テクスチャ。</param>
		void RegistTextureToBank(const char* filePath, Texture* texture)
		{
			m_textureBank.Regist(filePath, texture);
		}
		/// <summary>
		/// バンクからテクスチャを取得。
		/// </summary>
		/// <param name="filePath">ファイルパス。</param>
		/// <returns>テクスチャ。</returns>
		Texture* GetTextureFromBank(const char* filePath)
		{
			return m_textureBank.Get(filePath);
		}
		/// <summary>
		/// シェーダーファイルバンクからシェーダーを取得。
		/// </summary>
		/// <param name="filePath"></param>
		/// <returns></returns>
		Shader* GetShaderFromBank(const char* filePath, const char* entryPointFuncName)
		{
			std::string programName = filePath;
			programName += entryPointFuncName;
			return m_shaderBank.Get(programName.c_str());
		}
		/// <summary>
		/// シェーダーファイルをバンクに登録。
		/// </summary>
		/// <param name="filePath"></param>
		/// <param name="shader"></param>
		void RegistShaderToBank(const char* filePath, const char* entryPointFuncName, Shader* shader)
		{
			std::string programName = filePath;
			programName += entryPointFuncName;
			m_shaderBank.Regist(programName.c_str(), shader);
		}
	private:
		TResourceBank<TkmFile> m_tkmBank;				//tkmファイルバンク。
		TResourceBank<TksFile> m_tksBank;				//tksファイルバンク。
		TResourceBank<Shader> m_shaderBank;				// シェーダーバンク
		TResourceBank<Texture>	m_textureBank;			// テクスチャバンク。
	};

}

