# miniRT — Ray Tracer

A ray tracing engine built from scratch in **C**, rendering 3D scenes with realistic lighting, shadows, and reflections.

> 42 School project — implementing a ray tracer using only the miniLibX graphics library and the C standard library.

## Render Pipeline

```mermaid
graph LR
    Scene[".rt Scene File"] --> Parser
    Parser --> Objects["Object List<br/><sub>spheres, planes,<br/>cylinders, triangles</sub>"]
    Objects --> Raycast["Ray Casting<br/><sub>per pixel, multi-sample</sub>"]
    Raycast --> Intersect["Intersection Tests<br/><sub>quadratic solver</sub>"]
    Intersect --> Shading["Phong Shading<br/><sub>diffuse + specular + shadows</sub>"]
    Shading --> Display["miniLibX Window"]
```

## Features

- **Multi-object support** — spheres, planes, cylinders, triangles
- **Phong illumination model** — ambient, diffuse, and specular lighting with configurable shininess
- **Shadow casting** — ray-to-light occlusion testing
- **Anti-aliasing** — multi-sample per pixel with random jitter
- **Camera controls** — WASD movement, arrow key rotation
- **BRDF reflections** — bidirectional reflectance distribution
- **Light attenuation** — distance-based falloff
- **Scene description** — `.rt` file parser for configurable scenes

## Architecture

```
src/
├── parser/              # .rt file parsing (one parser per object type)
├── object/              # Ray-object intersection tests
├── render/              # Scene rendering, shadow computation
├── control/             # Camera movement and keyboard/mouse input
├── fsm/                 # Function dispatch tables (parser, intersect, render)
└── lib/
    ├── libvector3/      # 3D vector operations (dot, cross, normalize)
    ├── libcolor/        # Color math, illumination, attenuation
    ├── libprojection/   # Camera ray generation
    ├── libbrdf/         # Reflection model
    └── libmath/         # General math utilities
```

**Design pattern:** function pointer dispatch tables (FSM-style) for parser, intersection, and render stages — each object type registers its handler at initialization.

## Key Algorithms

| Algorithm | Purpose |
|---|---|
| Quadratic discriminant | Ray-sphere and ray-cylinder intersection |
| Phong reflection model | Ambient + diffuse + specular shading |
| Shadow rays | Point-to-light occlusion for hard shadows |
| Multi-sampling | Anti-aliasing via random sub-pixel jitter |
| 3D rotation matrices | Camera orientation (X/Y/Z axis) |
| Bresenham-style tracing | Pixel-level rendering |

## Tech Stack

| Component | Technology |
|---|---|
| Language | C (gcc, -O3 -flto -march=native) |
| Graphics | miniLibX (X11 / OpenGL) |
| Math | Custom vector3, matrix, and color libraries |
| Build | Makefile with automatic dependency tracking |

## Build & Run

```bash
make
./miniRT scene.rt
```

### Controls

| Key | Action |
|---|---|
| W / A / S / D | Move camera |
| Arrow keys | Rotate camera |
| ESC | Exit |

## Skills Demonstrated

- Linear algebra (vectors, matrices, 3D transformations)
- Ray tracing theory and implementation
- Phong illumination and BRDF
- Low-level C programming with manual memory management
- Performance optimization (-O3, -flto, -march=native)

## License

MIT
