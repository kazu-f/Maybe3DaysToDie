#pragma once
//�Q�[�����Ƀ��[�h���Ă���`�����N�͈̔�
enum class LoadingRange
{
	Short = 1 << 3,			//8
	Middle = 1 << 4,		//16
	Far = 1 << 5,			//32
};

class WorldConfig
{
public:
	WorldConfig() {}
	~WorldConfig() {}

public:
	void SetLoadingRange(LoadingRange range)
	{
		m_LoadingRange = range;
	}
	/// <summary>
	/// ���[�h����`�����N�͈̔͂��擾
	/// </summary>
	/// <returns></returns>
	int GetLoadingChunkRange()
	{
		int range = static_cast<int>(m_LoadingRange);
		range *= 2;
		range++;
		return range;
	}
private:
	LoadingRange m_LoadingRange = LoadingRange::Short;

};
