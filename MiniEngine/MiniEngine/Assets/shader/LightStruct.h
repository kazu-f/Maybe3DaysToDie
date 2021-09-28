/*
* ���C�g�̍\���́A�萔�B
*/

static const int MAX_POINT_LIGHT = 1024;				//�|�C���g���C�g�̍ő吔�B

//�f�B���N�V�������C�g�B
struct SDirectionalLight {
	float4 color;		//���C�g�̐F�B
	float3 direction;	//���C�g�̕����B
	unsigned int lightingMaterialIDGroup;		//���C�g�̉e����^����}�e���A�������߂�ID�B
};

//�|�C���g���C�g�B
struct SPointLight
{
	float3		position;		//�|�C���g���C�g�̈ʒu�B
	float3		positionInView;	//�r���[��Ԃł̃|�C���g���C�g�̍��W�B
	float4		color;			//�|�C���g���C�g�̃J���[�B
	float4		attn;			//�����萔�Bx:�|�C���g���C�g�̉e�����͂��͈́By:�|�C���g���C�g�̌������B
								//y���傫���Ȃ�ƁA�����������Ȃ�B1.0�Ő��`�̌������ɂȂ�Bz,w:���g�p�B
	float4		directionAndAngle;	//�w�������C�g�̕����ƏƎˊp�x�B
									//xyz�ɕ����Aw�Ɋp�x(���W�A���P��)������B
									//hasDirection��1�̎��ɗL���ƂȂ�B
	unsigned int hasDirection;		//���̃|�C���g���C�g���w�������C�g���ǂ����̃t���O�B(�X�|�b�g���C�g���ǂ����B)
	unsigned int lightingMaterialIDGroup;	//���C�g�̉e����^����}�e���A��ID�̃O���[�v�B
};
