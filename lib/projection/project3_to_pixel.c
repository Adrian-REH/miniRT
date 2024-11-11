
void point3D_to_pixel(Vector3 point, Camera camera, int screen_width, int screen_height, Vector2 *pxl) {
    // Vector desde la cámara al punto
    Vector3 to_point = {
        point.x - camera.pos.x,
        point.y - camera.pos.y,
        point.z - camera.pos.z
    };

    // Calculamos el factor de escala para la proyección
    double t = camera.dir.z / to_point.z;

    // Proyectamos el punto en el plano de la cámara
    Vector3 projected_point = {
        to_point.x * t,
        to_point.y * t,
        camera.plane_distance
    };

    // Calculamos las coordenadas en el plano de proyección
    double px = projected_point.x / camera.plane_half_width;
    double py = projected_point.y / camera.plane_half_height;

    // Convertimos las coordenadas del plano a coordenadas de píxel
    pxl->x = (int)((px + 1.0) * 0.5 * screen_width );
    pxl->y = (int)(((py + 1.0) * 0.5) * screen_height);
	//*x = ((int)((1 - point.x) * WINX) + WINX / 2) % WINX;
	//*y = (int)((1 - point.y) * WINY);

    // Ajustamos para el centro del píxel
     pxl->x  = ( pxl->x < screen_width && pxl->x > 0) ? pxl->x : screen_width - 1;
     pxl->y = ( pxl->y < screen_height && pxl->y > 0) ? pxl->y : screen_height - 1;
}
