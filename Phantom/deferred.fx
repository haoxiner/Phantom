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
  float3 position:POSITION;
  float3 normal:NORMAL;
  float2 texCoord:TEXCOORD;
};
struct VertexOutput
{
  float4 position:SV_POSITION;
  float4 posInCameraSpace:POSITION;
  float4 normal:NORMAL;
  float2 texCoord:TEXCOORD;
};
