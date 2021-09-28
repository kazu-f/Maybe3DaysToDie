#pragma once
/// <summary>
/// ���C�g�̊��N���X�B
/// </summary>

namespace Engine {
	namespace prefab {
		/// <summary>
		/// ���C�g�̊��N���X�B
		/// </summary>
		class CLightBase :public IGameObject
		{
		public:
			virtual ~CLightBase() {};
			bool Start()override final;
			void OnDestroy()override final;
			/// <summary>
			/// 
			/// </summary>
			void SetLightingMaterialIDGroup(unsigned int group)
			{
				m_lightingMaterialIDGroup = group;
			}
			/// <summary>
			/// ���C�g�̉e����^����}�e���A��ID�O���[�v���擾�B
			/// </summary>
			unsigned int GetLightingMaterialIDGroup()const
			{
				return m_lightingMaterialIDGroup;
			}
	
		private:
			virtual bool StartSub() = 0;
			virtual void OnDestroySub() {};
		private:
			unsigned int m_lightingMaterialIDGroup = 0xFFFFFFFF;		//!<���C�g�̉e����^���鑊������ʂ���}�e���A��ID�O���[�v�B0xFFFFFFFF�ł��ׂĂɉe����^����B

		};//// class LightBase

	}//// namespace prefab

}//// namespace Engine


