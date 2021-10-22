#pragma once

#include "TerrainManager/TerrainRender/TerrainRender.h"

/// <summary>
/// �i�r�Q�[�V�������b�V�������N���X�B
/// </summary>
/// <remarks>
/// ���̃N���X�́A�T���h�{�b�N�X�̃X�e�[�W����NVM�𓮓I��������N���X�B
/// �X�e�[�W�ɕύX���������ۂɂ�NVM�ύX���鏈��������i�\��j�B
/// �u���b�N�P�P�ʂ�2���b�V���Ƃ��Ĉ����ׁA�T���h�{�b�N�X�^�ł݂̂����@�\���Ȃ��B
/// </remarks>
class NVMGenerator
{
public:
	NVMGenerator();
	~NVMGenerator();
public:
	/// <summary>
	/// �n�`�f�[�^���NVM���쐬����B
	/// </summary>
	/// <param name="terrain">�n�`�B</param>
	void CreateNVM(nsTerrain::TerrainRender* terrain);
	/// <summary>
	/// �n�`�f�[�^���NVM���X�V����B
	/// <para>�u���b�N���j�󂳂ꂽ��`�����N��NVM�̍X�V���s���B</para>
	/// </summary>
	/// <param name="terrain"></param>
	void UpdateNVM(nsTerrain::TerrainRender* terrain);
	/// <summary>
	/// �f�o�b�O�`��B
	/// </summary>
	/// <param name="isEnableDebug">�f�o�b�O�`�悷��H</param>
	void DebugDraw(bool& isEnableDebug);
private:
	static bool isInstantiate;		//�C���X�^���X���쐬����Ă��邩�B

};

