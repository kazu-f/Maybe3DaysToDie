#pragma once

namespace Engine {

	//���\�[�X�Ǘ��I�u�W�F�N�g�B
	template <class TResource>
	class TResourceBank : public Noncopyable
	{
	public:
		TResource* Get(const char* filePath)
		{
			int hash = Util::MakeHash(filePath);
			auto it = m_resourceMap.find(hash);
			if (it != m_resourceMap.end()) {
				//�o���N�ɓo�^����Ă���B
				return it->second.get();
			}
			return nullptr;
		}
		void Regist(const char* filePath, TResource* resource)
		{
			int hash = Util::MakeHash(filePath);
			auto it = m_resourceMap.find(hash);
			if (it == m_resourceMap.end()) {
				//���o�^�B
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
