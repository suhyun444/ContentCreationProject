// �ȼ� ���̴� �Է�.
struct ps_input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD0;
    float2 hitCoord : TEXCOORD1;
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
    if (input.hitCoord.x == 1)
    {
        return float4(0.8f, 0.0f, 0.0f, color.a);
    }
    return color;
}