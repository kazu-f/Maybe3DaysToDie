
//GBuffer�ɏ������ނ��߂̍\���́B
struct PSOut_GBuffer {
	float4 albedo : SV_Target0;		//�A���x�h�J���[�B
	float4 normal : SV_Target1;		//�@���B
	float4 worldPos : SV_Target2;	//���[���h���W�B
	float4 specMap : SV_Target3;		//�X�y�L�����B
	float shadow : SV_Target4;		//�V���h�E�B
	float2 reflection : SV_Target5;	//���˗��B
};
