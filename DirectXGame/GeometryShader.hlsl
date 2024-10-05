struct GS_INPUT
{
    float4 pos : POSITION;
    float4 pos1 : POSITION1;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

struct GS_OUTPUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    float angle;
};

[maxvertexcount(16)]
void main(triangle GS_INPUT input[3], inout TriangleStream<GS_OUTPUT> outputStream)
{
    GS_OUTPUT output;

    for (int i = 0; i < 3; ++i)
    {
        output.pos = input[i].pos;
        output.color = input[i].color;
        output.color1 = input[i].color1;

        outputStream.Append(output);
    }

    outputStream.RestartStrip();

    const float4 positions[4] =
    {
        float4(-0.10f, 0.10f, 0.0f, 0.0f),
        float4(0.10f, 0.10f, 0.0f, 0.0f),
        float4(-0.10f, -0.10f, 0.0f, 0.0f),
        float4(0.10f, -0.10f, 0.0f, 0.0f),
    };

    for (int i = 0; i < 3; i++)
    {
        // int next = (i + 1) % 3;
        for (int j = 0; j < 4; j++)
        {
            output.pos = input[i].pos + positions[j];
            output.color = input[i].color;
            output.color1 = input[i].color1;
    
            outputStream.Append(output);
        }

        outputStream.RestartStrip();
    }

}