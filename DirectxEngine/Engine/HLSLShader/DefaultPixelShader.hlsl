struct PixelInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
};

float4 main(PixelInput input) : SV_TARGET
{
	//return float4(input.color, 1);
	return float4(input.texCoord, 0.0f, 1.0f);
} 