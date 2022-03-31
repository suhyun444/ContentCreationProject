// �ȼ� ���̴� �Է�.
struct ps_input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD;
};

// �ؽ��� ������.
Texture2D image;
SamplerState samplerState;

// �ȼ� ���̴�.
//float4 main(float4 position : POSITION) : SV_TARGET
float4 main(ps_input input) : SV_TARGET
{
    // �̹����� ���� �����ϱ�.
    float4 color = image.Sample(samplerState, input.texCoord);
    //return float4(0.0f, 0.0f, 0.0f, 0.5f);
    return color;
}