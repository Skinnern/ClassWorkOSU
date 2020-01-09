typedef float4 point;
typedef float4 vector;
typedef float4 color;
typedef float4 sphere;
typedef float4 rgba;
typedef float4 hsva;

vector
Bounce( vector in, vector n )
{
	vector out = in - n*(vector)( 2.*dot(in.xyz, n.xyz) );
	out.w = 0.;
	return out;
}

vector
BounceSphere( point p, vector v, sphere s )
{
	vector n;
	n.xyz = fast_normalize( p.xyz - s.xyz );
	n.w = 0.;
	return Bounce( v, n );
}

bool
IsInsideSphere( point p, sphere s )
{
	float r = fast_length( p.xyz - s.xyz );
	return  ( r < s.w );
}

rgba
HSVAtoRGBA(hsva in)
{
	float h, s, v, r, g, b;

	h = in.x;
	s = in.y;
	v = in.z;

	if (s == 0)
	{
		r = g = b = v;
	}
	else
	{
		float var_h, var_i, var_1, var_2, var_3;

		var_h = h * 6;
		if (var_h == 6)
		{
			var_h = 0;
		}
		var_i = floor(var_h);
		var_1 = v * (1 - s);
		var_2 = v * (1 - s * (var_h - var_i));
		var_3 = v * (1 - s * (1 - (var_h - var_i)));

		switch ((int) var_i)
		{
			case 0:
				r = v;
				g = var_3;
				b = var_1;
				break;
			case 1:
				r = var_2;
				g = v;
				b = var_1;
				break;
			case 2:
				r = var_1;
				g = v;
				b = var_3;
				break;
			case 3:
				r = var_1;
				g = var_2;
				b = v;
				break;
			case 4:
				r = var_3;
				g = var_1;
				b = v;
				break;
			default:
				r = v;
				g = var_1;
				b = var_2;
				break;
		}
	}

	return (rgba) (r, g, b, 1.f);
}


rgba
RGBAfromVelocity(vector v)
{
	// Determine the particle's relative speed.
	float max_speed = 150.f;                   // Matches VMAX in cpp file
	float relative_speed = fast_length(v) / max_speed;

	// Clamp the upper bound of speed.
	if (relative_speed > 1.f)
	{
		relative_speed = 1.f;
	}

	// Encode the fastest particles as red.
	float red_h = 0.f;

	// Encode the slowest particles as blue.
	float blue_h = 0.667f;

	// Interpolate hues based on the given velocity.
	float h = blue_h - relative_speed * (blue_h - red_h);

	// Desaturate slightly for aesthetic reasons.
	float s = 0.8;

	// Convert the interpolated color to rgba.
	return HSVAtoRGBA((hsva) (h, s, 1.f, 1.f));
}

kernel
void
Particle( global point *dPobj, global vector *dVel, global color *dCobj )
{
	const float4 G       = (float4) ( 0., -4.0, 0., 0. );
	const float  DT      = 0.1;
	const float4 VG		 = (float4) (1.0, 0.0, 0.00, 0.);

	const sphere Sphere1 = (sphere)( -100., -800., 0.,  600. );
	const sphere Sphere2 = (sphere)( -100., -800., 0.,  10000. );
	int gid = get_global_id( 0 );

	point  p = dPobj[gid];
	vector v = dVel[gid];
	color c = dCobj[gid];

	point  pp = p + v*DT + (float4)(.5*DT*DT)*G;
	vector vp = v + G*DT;
	color cp = c; //+ VG * c;
	pp.w = 1.;
	vp.w = 0.;
	cp.w = 1.;

	if( IsInsideSphere( pp, Sphere1 ) )
	{
		vp = BounceSphere( p, v, Sphere1 );
		pp = p + vp*DT + (float4)(.5*DT*DT)*G;
	}
	if( !IsInsideSphere( pp, Sphere2 ) )
	{
		vp = BounceSphere( p, v, Sphere1 );
		pp = p + vp*DT + (float4)(.5*DT*DT)*G;
	}

	dPobj[gid] = pp;
	dVel[gid] = vp;
	dCobj[gid] = RGBAfromVelocity(vp);

}
