#pragma once

//�`�����N���Ƃ̃u���b�N
class ChunkBlock
{
public:
	ChunkBlock();
	~ChunkBlock();

	/// <summary>
	/// �R���C�_�[��������
	/// </summary>
	void InitCol();

	/// <summary>
	/// �R���C�_�[�̈ʒu���`�����N�ɍ��킹�Ĉړ�����
	/// </summary>
	/// <param name="ChunkID">�`�����NID</param>
	void MoveChunk(int ChunkID[2]);
private:
	CPhysicsStaticObject m_StaticCol[ChunkWidth][ChunkHeight][ChunkWidth];		//�ÓI�����I�u�W�F�N�g
	const Vector3 BLOCK_SIZE = { OBJECT_UNIT ,OBJECT_UNIT ,OBJECT_UNIT };
};