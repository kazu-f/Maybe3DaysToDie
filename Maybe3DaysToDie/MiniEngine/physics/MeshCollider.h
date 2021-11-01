#pragma once

#include "physics/ICollider.h"

namespace Engine {

	/// <summary>
	/// メッシュコライダー。
	/// </summary>
	class CMeshCollider:public ICollider
	{
	public:
		//コンストラクタ。
		CMeshCollider();
		//デストラクタ。
		~CMeshCollider();
		/// <summary>
		/// モデルクラスからメッシュコライダーを生成。
		/// </summary>
		/// <param name="model">スキンモデル</param>
		/// <param name="offsetMatrix">行列。</param>
		void CreateFromModel(const Model& model, const Matrix* offsetMatrix);
		/// <summary>
		/// tkmファイルからメッシュコライダーを生成。
		/// </summary>
		/// <param name="tkmFile">tkmファイル。</param>
		/// <param name="offsetMatrix">行列。</param>
		void CreateFromTkmFile(const TkmFile& tkmFile, const Matrix* offsetMatrix);
		/// <summary>
		/// 頂点バッファとインデックスバッファからコライダーを作成。
		/// </summary>
		/// <param name="vertices">頂点バッファ。</param>
		/// <param name="indices">インデックスバッファ。</param>
		/// <param name="offsetMatrix">行列。</param>
		void CreateFromBuffer(const std::vector<Vector3>& vertices, const std::vector<int>& indices, const Matrix* offsetMatrix);

		/// <summary>
		/// 頂点バッファァからコライダーを作成。
		/// </summary>
		/// <param name="vertices">頂点バッファ。</param>
		/// <param name="offsetMatrix">行列。</param>
		void CreateFromBuffer(const std::vector<Vector3>& vertices, const Matrix* offsetMatrix);

		/// <summary>
		/// シェイプを取得。
		/// </summary>
		btCollisionShape* GetBody() const override
		{
			return m_meshShape.get();
		}
	private:
		typedef std::vector<Vector3>		VertexBuffer;		//頂点バッファ。
		typedef std::vector<unsigned int>	IndexBuffer;		//インデックスバッファ。
		typedef std::unique_ptr<VertexBuffer>	VertexBufferPtr;	//頂点バッファのユニークポインタ。
		typedef std::unique_ptr<IndexBuffer>	IndexBufferPtr;		//インデックスバッファのユニークポインタ。
		std::vector<VertexBufferPtr>		m_vertexBufferArray;	//頂点バッファの配列。
		std::vector<IndexBufferPtr>			m_indexBufferArray;		//インデックスバッファの配列。
		std::unique_ptr<btBvhTriangleMeshShape>		m_meshShape;		//メッシュ形状。
		std::unique_ptr<btTriangleIndexVertexArray> m_stridingMeshInterface;

	};

}
