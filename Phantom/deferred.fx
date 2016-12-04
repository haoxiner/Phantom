cbuffer CBImmutable
{
  float4x4 projection;
};
cbuffer CBPerFrame
{
  float4x4 worldToView;
};
cbuffer CBPerObject
{
  float4x4 modelToWorld;
};
struct VertexInput
{
  float4 position:POSITION0;
  float3 normal:NORMAL0;
  float2 texCoord:TEXCOORD0;
};
struct PixelInput
{
  float4 pixelPosition:SV_POSITION;
  float3 position:POSITION0;
  float3 normal:NORMAL0;
  float2 texCoord:TEXCOORD0;
};
PixelInput VS(VertexInput input)
{
  PixelInput output;
  output.svPosition.w = 1.0f;
  output.position = mul(modelToWorld, input.position);
  output.position = mul(worldToView, output.position);
  output.pixelPosition = mul(projection, output.position);
  output.normal = mul((float3x3)modelToWorld, input.normal);
  output.normal = normalize(output.normal);
  output.texCoord = input.texCoord;
  return output;
}
struct PixelOutput
{
  float4 diffuse : SV_Target0;
  float4 normal : SV_Target1;
};
PixelOutput PS(PixelInput input)
{
  PixelOutput output;
  output.diffuse = float4(0.2f,0.4f,0.6f,1.0f);
  output.normal = float4(input.normal, 1.0f);
  //output.normal = normalize(output.normal);
  return output;
};