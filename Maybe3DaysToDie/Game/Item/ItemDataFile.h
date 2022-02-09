#pragma once
class GameItemBase;

/// <summary>
/// jsonファイルからツールデータを読み込むクラス。
/// </summary>
class ItemDataFile
{
	using json = nlohmann::json;

public:		//シングルトン。
	static void CreateInstance()
	{
		m_instance = new ItemDataFile();
	}

	static void Release()
	{
		if(m_instance != nullptr) delete m_instance;
	}

	static ItemDataFile* GetInstance()
	{
		return m_instance;
	}

private:
	static ItemDataFile* m_instance;

private:
	ItemDataFile();
	~ItemDataFile();

public:
	//アイテムのデータを読み込む処理。
	void InitItemData(const char* filePath);
	//アイテムデータを基底クラスで取得する。
	GameItemBase* GetItemDataBase(int id)
	{
		return m_itemArray[id];
	}

	/// <summary>
	/// アイテムのデータを取得する。
	/// </summary>
	/// <param name="id">アイテムのID</param>
	/// <returns>型変換が上手くいけば取得できる。</returns>
	template<class T>T* GetItemData(int id)
	{
		T* p = dynamic_cast<T*>(m_itemArray[id]);
		if (p == nullptr) {
			ENGINE_MESSAGE_BOX(
				"アイテムデータの型変換に失敗しました。",
				"\n型の情報を基底クラスの変数から確認してください。")
		}
		return p;
	}

private:
	typedef std::vector<GameItemBase*> ItemArray;
	ItemArray m_itemArray;
	int m_arraySize = 0;
};

