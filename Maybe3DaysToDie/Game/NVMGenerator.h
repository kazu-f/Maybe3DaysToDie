#pragma once

/// <summary>
/// �i�r�Q�[�V�������b�V�������N���X�B
/// </summary>
/// <remarks>
/// ���̃N���X�́A�T���h�{�b�N�X�̃X�e�[�W����NVM�𓮓I��������N���X�B
/// �X�e�[�W�ɕύX���������ۂɂ�NVM�ύX���鏈��������i�\��j�B
/// �u���b�N�P�P�ʂ�2���b�V���Ƃ��Ĉ����ׁA�T���h�{�b�N�X�^�ł݂̂����@�\���Ȃ��B
/// �܂��A���̃N���X��static�N���X�����̂��߃C���X�^���X���͕K�v�Ƃ��Ȃ��B
/// </remarks>

class Terrain;

class NVMGenerator
{
private:
	NVMGenerator();
public:
	/// <summary>
	/// �n�`�f�[�^���NVM���쐬����B
	/// </summary>
	/// <param name="terrain">�n�`�B</param>
	static void CreateNVM(Terrain& terrain);
	/// <summary>
	/// �n�`�f�[�^���NVM���X�V����B
	/// </summary>
	/// <param name="terrain"></param>
	static void UpdateNVM(Terrain& terrain);
private:

};

