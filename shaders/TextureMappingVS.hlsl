// ��� ������.
// Constant Buffer. (��� ����.)
cbuffer transform : register(b0)
{
	// 4x4 ���. 
	matrix world; // ���� ���.
};
cbuffer camera : register(b1)
{
	matrix viewProjection;
};
// ���� �Է�.
struct vs_input
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD;
};

// ���� ���.
struct vs_output
{
	float4 position : SV_POSITION; // �ý����� ���ϱ�, SV ����.
	float2 texCoord : TEXCOORD;
};

// float4 main(float4 position : POSITION) : SV_POSITION
// float4 main(vs_input input) : SV_POSITION
vs_output main(vs_input input)
{
	vs_output output;
	output.position = mul(input.position, world);
	output.position = mul(output.position, viewProjection);
	output.texCoord = input.texCoord;

	return output;
}