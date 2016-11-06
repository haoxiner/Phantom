float4 VS(float3 position:POSITION):SV_POSITION
{
  return float4(position, 1.0);
}

float4 PS(float4 position:SV_POSITION):SV_Target
{
  return float4(0.2, 0.4, 0.6, 1.0);
}