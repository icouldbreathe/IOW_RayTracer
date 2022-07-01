# Raytracer

An attempt at making a ray tracer. Based on [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

## Final Render

<img width="600" alt="RTIOW Final Render" src="https://user-images.githubusercontent.com/9082440/176953805-aafc2261-1694-4cec-9c25-d788047cf1e6.png">

## Progress

- [x] Output an image (PPM)
- [x] Implement progress indicator
- [x] Implement basic vector class
- [x] Implement basic ray class
- [x] Implement basic camera, viewport and background
- [x] Implement a build solution (make)
- [x] Ray-Sphere intersection
- [x] Surface normals and multiple objects
- [x] Antialiasing
- [x] Diffuse materials
- [x] Metal
- [x] Dielectrics
- [x] Positionable Camera
- [x] Defocus Blur
- [x] Final Render

### Next:

- [ ] Ray Tracing the Next Week
- [ ] Ray Tracing the Rest of Your Life

## Prerequisites

- [make](https://www.gnu.org/software/make/)
- [clang++](https://releases.llvm.org/)
- [PPM viewer](https://fileinfo.com/extension/ppm#portable_pixmap_image_file_open)

## Usage

### Make

Use `make <debug|release>` to build debug or release builds. `make` or `make render` will also output the rendered image.

```shell
$ cd IOW_RayTracer
$ make <debug|release|render|remake|clean>
```
