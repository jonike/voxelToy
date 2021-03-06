float rayAABBIntersection(in vec3 o, in vec3 d, 
						  in vec3 boundsMin, in vec3 boundsMax)
{
	vec3 invDir = vec3(1.0f) / d; 

	vec3 tMin3 = (boundsMin - o) * invDir;
	vec3 tMax3 = (boundsMax - o) * invDir;

	vec3 tmin   = min(tMin3, tMax3);
	float tminf = max(tmin.x, max(tmin.y, tmin.z));
	vec3 tmax   = max(tMin3, tMax3);
	float tmaxf = min(tmax.x, min(tmax.y, tmax.z));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behind us
	if (tmaxf < 0)
	{
		return -1; 
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tminf > tmaxf)
	{
		return -1; 
	}

	// this is a bit of a specific behaviour to raymarching: if we're inside of 
	// the volume we're not interested in the outgoing (tmax) intersection, but
	// simply clamp tmin to 0 to start marching from the current ray origin.
	return max(0, tminf); 
	// this would be the usual ray/aabb intersection code
	//return tminf >= 0 ? tminf : tmaxf;
}

