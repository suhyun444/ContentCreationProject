// 픽셀 쉐이더 입력.
struct ps_input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD0;
    float2 hitCoord : TEXCOORD1;
};

// 텍스쳐 데이터.
Texture2D image;
SamplerState samplerState;

// 픽셀 쉐이더.
//float4 main(float4 position : POSITION) : SV_TARGET
float4 main(ps_input input) : SV_TARGET
{
    // 이미지의 색상 추출하기.
    float4 color = image.Sample(samplerState, input.texCoord);
    if (input.hitCoord.x == 1)
    {
        return float4(0.8f, 0.0f, 0.0f, color.a);
    }
    return color;
}