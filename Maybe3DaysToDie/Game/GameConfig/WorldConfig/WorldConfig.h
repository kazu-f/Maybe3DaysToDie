#pragma once
//ゲーム中にロードしているチャンクの範囲
enum class LoadingRange
{
	Short = 1 << 3,			//8
	Middle = 1 << 4,		//16
	Far = 1 << 5,			//32
};
static const int LoadingChunkCols = 3;
static const int LoadingChunks = 9;
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
	/// ロードするチャンクの範囲を取得
	/// </summary>
	/// <returns></returns>
	int GetLoadingChunkRange()
	{
		int range = static_cast<int>(m_LoadingRange);
		return range;
	}
private:
	LoadingRange m_LoadingRange = LoadingRange::Short;

};
