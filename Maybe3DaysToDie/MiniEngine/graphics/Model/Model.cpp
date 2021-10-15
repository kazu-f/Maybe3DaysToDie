#include "MiniEngine.h"
#include "Model.h"

namespace Engine {
	void Model::Init(const ModelInitData& initData, int maxInstance)
	{
		//�C���X�^���V���O�`����s���H
		if (maxInstance > 1) {
			m_maxInstance = maxInstance;
			m_instancingData.reset(new Matrix[maxInstance]);
			m_instancingDataSB.Init(sizeof(Matrix), maxInstance, m_instancingData.get());
		}

		auto tkmFile = ResourceEngine().GetTkmFileFromBank(initData.m_tkmFilePath);
		if (tkmFile == nullptr)
		{
			tkmFile = new TkmFile();
			tkmFile->Load(initData.m_tkmFilePath);
			ResourceEngine().RegistTkmFileToBank(initData.m_tkmFilePath,tkmFile);
		}

		m_tkmFile = tkmFile;

		m_meshParts.InitFromTkmFile(
			*m_tkmFile,
			initData.m_shaderData,
			initData.m_expandConstantBuffer,
			initData.m_expandConstantBufferSize,
			initData.m_expandShaderResoruceView,
			m_instancingDataSB.IsInited() ? &m_instancingDataSB : nullptr,
			m_maxInstance
		);
		m_modelUpAxis = initData.m_modelUpAxis;
		UpdateWorldMatrix(g_vec3Zero, g_quatIdentity, g_vec3One);
	}

	void Model::UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale)
	{
		Matrix mBias;
		if (enModelUpAxis_Z == m_modelUpAxis) {
			//Z-up
			mBias.MakeRotationX(Math::PI * -0.5f);
		}
		Matrix mTrans, mRot, mScale;
		mTrans.MakeTranslation(pos);
		mRot.MakeRotationFromQuaternion(rot);
		mScale.MakeScaling(scale);
		m_world = mBias * mScale * mRot * mTrans;
	}
	void Model::UpdateInstancingData(const Vector3& pos, const Quaternion& rot, const Vector3& scale, bool isCulling)
	{
		if (m_numInstance < m_maxInstance) {
			if (isCulling) {
				Vector4 screenPos = pos;
				GraphicsEngine()->GetMainCamera().GetViewMatrix().Apply(screenPos);
				float viewPosZ = screenPos.z;
				GraphicsEngine()->GetMainCamera().GetProjectionMatrix().Apply(screenPos);
				screenPos.x /= screenPos.w;
				screenPos.y /= screenPos.w;
				screenPos.z /= screenPos.w;
				//TODO:���܂�D�܂����Ȃ��J�����O���Ă邩�璼�������B
				if (screenPos.x < -1.2f || screenPos.x > 1.2f ||
					screenPos.y < -1.2f || screenPos.y > 1.2f ||
					viewPosZ > m_cullingFar || viewPosZ < -100.0f)
				{
					return;
				}
			}
			UpdateWorldMatrix(pos, rot, scale);
			//�C���X�^���V���O�f�[�^���X�V����B
			m_instancingData[m_numInstance] = m_world;

			m_numInstance++;
		}
		else {
			ENGINE_LOG("Model::UpdateInstancingData	invalid UpdateInstancingData.");
		}
	}
	void Model::Draw(RenderContext& rc)
	{
		m_meshParts.Draw(
			rc,
			m_world,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			m_numInstance
		);
	}
	void Model::Draw(RenderContext& rc, Matrix mLVP)
	{
		m_meshParts.Draw(
			rc,
			m_world,
			mLVP,
			Matrix::Identity,
			m_numInstance
		);
	}
}