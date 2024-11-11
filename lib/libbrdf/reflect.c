
Vector3 *reflect(Vector3 L, Vector3 N) {
	double dot_product = dot(N, L); // N dot L
	Vector3 *reflection = malloc(sizeof(Vector3));
	*reflection =  (Vector3) {
		2 * dot_product * N.x - L.x,
		2 * dot_product * N.y - L.y,
		2 * dot_product * N.z - L.z
	};
	 normalize(reflection); // Normalize the reflected vector
	return reflection;
}
