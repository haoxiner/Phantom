struct VSIN
{
  float3 position:POSITION;
  float3 normal:NORMAL;
  float2 texCoord:TEXCOORD;
};
struct VSOUT
{
  float4 position:SV_POSITION;
  float3 normal:NORMAL;
  float2 texCoord:TEXCOORD;
};

VSOUT VS(
  VSIN vin)
{
  VSOUT vout;
  vout.position = float4(vin.position, 1.0);
  vout.normal = vin.normal;
  vout.texCoord = vin.texCoord;
  return vout;
}

float4 PS(VSOUT pin):SV_Target
{
  return float4(pin.normal * 0.5 + float3(0.5,0.5,0.5), 1.0);
}