cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct VertexInputType
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD0;
    float3 worldPos : TEXCOORD1; // Add world position
};

PixelInputType CelShadingVertexShader(VertexInputType input)
{
    PixelInputType output;

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    // Pass the normal to the pixel shader
    output.normal = mul(input.normal, (float3x3)worldMatrix);

    // Pass the world position to the pixel shader
    output.worldPos = mul(input.position, worldMatrix).xyz;

    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;

    return output;
}