#pragma once

namespace Engine {

	//リソース管理オブジェクト。
	template <class TResource>
	class TResourceBank : public Noncopyable
	{
	public:
		TResource* Get(const char* filePath)
		{
			int hash = Util::MakeHash(filePath);
			auto it = m_resourceMap.find(hash);
			if (it != m_resourceMap.end()) {
				//バンクに登録されている。
				return it->second.get();
			}
			return nullptr;
		}
		void Regist(const char* filePath, TResource* resource)
		{
			int hash = Util::MakeHash(filePath);
			auto it = m_resourceMap.find(hash);
			if (it == m_resourceMap.end()) {
				//未登録。
				m_resourceMap.insert(
					std::pair< int, TResourcePtr>(hash, resource)
				);
			}
		}

	private:
		using TResourcePtr = std::unique_ptr<TResource>;
		std::map<int, TResourcePtr> m_resourceMap;

	};	///class TResource Bank;

}///namespace Engine;
