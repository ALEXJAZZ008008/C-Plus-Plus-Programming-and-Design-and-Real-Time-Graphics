cbuffer LightBuffer
{
	float4 AmbientColour[3];
}

cbuffer BlendBuffer
{
	float BlendAmount;
	float3 BlendBufferPadding;
};

struct PixelInput
{
	float4 Position : SV_POSITION;
};

float4 ShadowPixelShader(PixelInput input) : SV_TARGET
{
	float4 output[3];

	for (int i = 0; i < 3; i++)
	{
		float4 lightColour = saturate(AmbientColour[i]);

		output[i] = saturate(lightColour);
	}

	return float4(saturate(output[0] + output[1] + output[2]).xyz, BlendAmount);
}