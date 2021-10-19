#include "MiniEngine.h"
#include "Model.h"

namespace Engine {
	void Model::Init(const ModelInitData& initData, int maxInstance)
	{
		auto tkmFile = ResourceEngine().GetTkmFileFromBank(initData.m_tkmFilePath);
		if (tkmFile == nullptr)
		{
			tkmFile = new TkmFile();
			tkmFile->Load(initData.m_tkmFilePath);
			ResourceEngine().RegistTkmFileToBank(initData.m_tkmFilePath,tkmFile);
		}

		m_tkmFile = tkmFile;

		if (initData.m_skeleton != nullptr) {
			//スケルトンが指定されている。
			m_meshParts.BindSkeleton(*initData.m_skeleton);
		}

		m_meshParts.InitFromTkmFile(
			*m_tkmFile,
			initData.m_shaderData,
			initData.m_expandConstantBuffer,
			initData.m_expandConstantBufferSize,
			initData.m_expandShaderResoruceView,
			initData.m_instancingDataSB,
			maxInstance
		);
		m_modelUpAxis = initData.m_modelUpAxis;
		UpdateWorldMatrix(g_vec3Zero, g_quatIdentity, g_vec3One);
	}

	Matrix Model::CalcWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale)
	{
		Matrix mBias, mWorld;
		if (m_modelUpAxis == enModelUpAxis_Z) {
			//Z-up
			mBias.MakeRotationX(Math::PI * -0.5f);
		}
		Matrix mTrans, mRot, mScale;
		mTrans.MakeTranslation(pos);
		mRot.MakeRotationFromQuaternion(rot);
		mScale.MakeScaling(scale);
		mWorld = mBias * mScale * mRot * mTrans;
		return mWorld;
	}
	void Model::Draw(RenderContext& rc, int numInstance)
	{
		m_meshParts.Draw(
			rc,
			m_world,
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix(),
			numInstance
		);
	}
	void Model::Draw(RenderContext& rc, Matrix mLVP, int numInstance)
	{
		m_meshParts.Draw(
			rc,
			m_world,
			mLVP,
			Matrix::Identity,
			numInstance
		);
	}
	void Model::Draw(RenderContext& rc, Matrix mView, Matrix mProj, int numInstance)
	{
		m_meshParts.Draw(
			rc,
			m_world,
			mView,
			mProj,
			numInstance
		);
	}
}