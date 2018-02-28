cbuffer MatrixBuffer
{
	matrix WorldMatrix;
	matrix ViewMatrix;
	matrix ProjectionMatrix;
};

cbuffer ObjectBuffer
{
	float ObjectType;
	float ObjectState;
	float RenderState;
	float TimeElapsed;
	float TimeOffset;
	float3 ObjectBufferPadding;
}

struct VertexInput
{
	float4 Position : POSITION;
	float2 TexCoord : TEXCOORD0;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
};

struct PixelInput
{
	float4 Position : SV_POSITION;
};

void BodyAnimation(inout VertexInput input)
{
	if (ObjectState > 0.0f)
	{
		float rotationAngle = 0.0f;
		float finalRotationAngle = 1.5708f;

		float translationMagnitude = 0.0f;
		float translationOffset = 0.0f;
		float finalTranslationOffset = 1.5f;
		
		if (ObjectState < 2.0f)
		{
			if (input.Position.y < 0.1f)
			{
				if (input.Position.x > 0.1f)
				{
					rotationAngle = finalRotationAngle * (TimeElapsed / 3.0f);
				}
				else
				{
					if (input.Position.x < -0.1f)
					{
						rotationAngle = -(finalRotationAngle * (TimeElapsed / 3.0f));
					}
				}

				translationOffset = finalTranslationOffset * (TimeElapsed / 3.0f);
			}
		}
		else
		{
			if (ObjectState > 1.0f && ObjectState < 3.0f)
			{
				if (input.Position.y < 0.1f)
				{
					if (input.Position.x > 0.1f)
					{
						rotationAngle = finalRotationAngle;
					}
					else
					{
						if (input.Position.x < -0.1f)
						{
							rotationAngle = -finalRotationAngle;
						}
					}

					translationOffset = finalTranslationOffset;
				}

				translationMagnitude = sin(TimeElapsed);
			}
			else
			{
				if (ObjectState > 2.0f && ObjectState < 4.0f)
				{
					if (input.Position.y < 0.1f)
					{
						if (input.Position.x > 0.1f)
						{
							rotationAngle = finalRotationAngle - (finalRotationAngle * ((TimeElapsed - TimeOffset) / 3.0f));
						}
						else
						{
							if (input.Position.x < -0.1f)
							{
								rotationAngle = -(finalRotationAngle - (finalRotationAngle * ((TimeElapsed - TimeOffset) / 3.0f)));
							}
						}

						translationOffset = finalTranslationOffset - (finalTranslationOffset * ((TimeElapsed - TimeOffset) / 3.0f));
					}
				}
			}
		}

		matrix<float, 4, 4> rotationMatrix =
		{
			cos(rotationAngle),
			-sin(rotationAngle),
			0.0f,
			1.0f,
			sin(rotationAngle),
			cos(rotationAngle),
			0.0f,
			1.0f,
			0.0f,
			0.0f,
			1.0f,
			0.0f,
			0.0f,
			0.0f,
			0.0f,
			1.0f
		};

		input.Position = mul(input.Position, rotationMatrix);

		float4 translation = float4(0.0f, translationMagnitude + translationOffset, 0.0f, 1.0f);
		input.Position += (translation / 10.0f);
	}
}

void WingAnimation(inout VertexInput input)
{
	if (ObjectState > 0.0f)
	{
		float rotationAngle = 0.0f;

		float translationMagnitude = 0.0f;

		if (ObjectState < 2.0f)
		{
			if (input.Position.y > 0.3f)
			{
				if (input.Position.x > 0.1f)
				{
					rotationAngle = sin(25.0f * TimeElapsed) / 4.0f;
				}
				else
				{
					if (input.Position.x < -0.1f)
					{
						rotationAngle = -sin(25.0f * TimeElapsed) / 4.0f;
					}
				}
			}
		}
		else
		{
			if (ObjectState > 1.0f && ObjectState < 3.0f)
			{
				if (input.Position.y > 0.3f)
				{
					if (input.Position.x > 0.1f)
					{
						rotationAngle = sin(25.0f * TimeElapsed) / 4.0f;
					}
					else
					{
						if (input.Position.x < -0.1f)
						{
							rotationAngle = -sin(25.0f * TimeElapsed) / 4.0f;
						}
					}
				}

				translationMagnitude = sin(TimeElapsed);
			}
			else
			{
				if (ObjectState > 2.0f && ObjectState < 4.0f)
				{
					if (input.Position.y > 0.3f)
					{
						if (input.Position.x > 0.1f)
						{
							rotationAngle = sin(25.0f * TimeElapsed) / 4.0f;
						}
						else
						{
							if (input.Position.x < -0.1f)
							{
								rotationAngle = -sin(25.0f * TimeElapsed) / 4.0f;
							}
						}
					}
				}
			}
		}

		matrix<float, 4, 4> rotationMatrix =
		{
			cos(rotationAngle),
			-sin(rotationAngle),
			0.0f,
			1.0f,
			sin(rotationAngle),
			cos(rotationAngle),
			0.0f,
			1.0f,
			0.0f,
			0.0f,
			1.0f,
			0.0f,
			0.0f,
			0.0f,
			0.0f,
			1.0f
		};

		input.Position = mul(input.Position, rotationMatrix);

		float4 translation = float4(0.0f, translationMagnitude, 0.0f, 1.0f);
		input.Position += (translation / 10.0f);
	}
}

void Animation(inout VertexInput input)
{
	if (ObjectType > 0.0f && ObjectType < 2.0f)
	{
		BodyAnimation(input);
	}
	else
	{
		if (ObjectType > 2.0f && ObjectType < 4.0f)
		{
			WingAnimation(input);
		}
	}
}

PixelInput ShadowVertexShader(VertexInput input)
{
	Animation(input);

	PixelInput output = (PixelInput)0;

	// Change the position vector to be 4 units for proper matrix calculations.
	output.Position = float4(input.Position.xyz, 1.0f);

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.Position = mul(output.Position, WorldMatrix);
	output.Position = mul(output.Position, ViewMatrix);
	output.Position = mul(output.Position, ProjectionMatrix);

	return output;
}