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
cbuffer unit : register(b2)
{
	matrix isLeft;
};
// ���� �Է�.
struct vs_input
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD0;
};

// ���� ���.
struct vs_output
{
	float4 position : SV_POSITION; // �ý����� ���ϱ�, SV ����.
	float2 texCoord : TEXCOORD0;
	float2 hitCoord : TEXCOORD1;
};

// float4 main(float4 position : POSITION) : SV_POSITION
// float4 main(vs_input input) : SV_POSITION
vs_output main(vs_input input)
{
	vs_output output;
	output.position = mul(input.position, world);
	output.position = mul(output.position, viewProjection);
	output.texCoord = lerp(float2(input.texCoord.x, input.texCoord.y), float2(-input.texCoord.x, input.texCoord.y), isLeft._11);
	output.hitCoord = lerp(0, 1, isLeft._22);

	return output;
}