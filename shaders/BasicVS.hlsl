
cbuffer transform : register(b0)
{
	matrix world;
};

cbuffer camera : register(b1)
{
	matrix viewProjection;
};
struct vs_input
{
	float4 position : POSITION;
};

struct vs_output
{
	float4 position : SV_POSITION;
};

vs_output main(vs_input input)
{
	vs_output output;
	output.position = mul(input.position, world);
	output.position = mul(output.position, viewProjection);

	return output;
}