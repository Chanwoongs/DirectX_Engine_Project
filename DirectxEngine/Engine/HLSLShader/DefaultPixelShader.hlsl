struct PixelInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

// Texture.
Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
    // Sampling.
    float4 texColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
    
    float4 white = float4(1.0f, 1.0f, 1.0f, 1.0f);
    if (all(texColor == white))
    {
        return float4(input.texCoord, 0.0f, 1.0f);
    }
    
    return texColor;
} 