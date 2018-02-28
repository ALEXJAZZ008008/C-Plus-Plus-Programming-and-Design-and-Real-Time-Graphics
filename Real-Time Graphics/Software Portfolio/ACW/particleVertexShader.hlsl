cbuffer MatrixBuffer
{
	matrix WorldMatrix;
	matrix ViewMatrix;
	matrix ProjectionMatrix;
};

struct VertexInput
{
	float4 Position : POSITION;
	float2 TexCoord : TEXCOORD0;
};

struct PixelInput
{
	float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD0;
};

PixelInput ParticleVertexShader(VertexInput input)
{
	PixelInput output = (PixelInput)0;

	// Change the position vector to be 4 units for proper matrix calculations.
	output.Position = float4(input.Position.xyz, 1.0f);

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.Position = mul(output.Position, WorldMatrix);
	output.Position = mul(output.Position, ViewMatrix);
	output.Position = mul(output.Position, ProjectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.TexCoord = input.TexCoord;

	return output;
}