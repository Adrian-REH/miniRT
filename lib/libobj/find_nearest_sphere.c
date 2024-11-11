
int find_nearest_sphere(Scene scene, Ray *ray, double *t){
	int i;
	int j;
	double min_dist = INT32_MAX;

	i = -1;
	j = -1;
	while (++i < scene.n_spheres)
	{
		if (intersect_sphere(ray, &scene.spheres[i], t) && (*t < min_dist))
		{
			min_dist = *t;
			j = i;
		}
	}
	*t = min_dist;
	return j;
}
