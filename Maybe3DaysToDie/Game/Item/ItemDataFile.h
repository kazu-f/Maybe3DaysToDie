#pragma once
class GameItemBase;

/// <summary>
/// json�t�@�C������c�[���f�[�^��ǂݍ��ރN���X�B
/// </summary>
class ItemDataFile
{
	using json = nlohmann::json;

public:		//�V���O���g���B
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
	//�A�C�e���̃f�[�^��ǂݍ��ޏ����B
	void InitItemData(const char* filePath);
	//�A�C�e���f�[�^�����N���X�Ŏ擾����B
	GameItemBase* GetItemDataBase(int id)
	{
		return m_itemArray[id];
	}

	/// <summary>
	/// �A�C�e���̃f�[�^���擾����B
	/// </summary>
	/// <param name="id">�A�C�e����ID</param>
	/// <returns>�^�ϊ�����肭�����Ύ擾�ł���B</returns>
	template<class T>T* GetItemData(int id)
	{
		T* p = dynamic_cast<T*>(m_itemArray[id]);
		if (p == nullptr) {
			ENGINE_MESSAGE_BOX(
				"�A�C�e���f�[�^�̌^�ϊ��Ɏ��s���܂����B",
				"\n�^�̏������N���X�̕ϐ�����m�F���Ă��������B")
		}
		return p;
	}

private:
	typedef std::vector<GameItemBase*> ItemArray;
	ItemArray m_itemArray;
	int m_arraySize = 0;
};

