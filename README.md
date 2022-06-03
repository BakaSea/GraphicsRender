# GraphicsRender
## Path Tracing

Model:

* Sangonomiya Kokomi/miHoYo/观海子
* Bunny/Standford University

1000x1000 spp3000:

![](imgsrc/1000x1000spp3000.png)

2000x2000 spp3000:

![](imgsrc/2000x2000spp3000.png)

## Sampler

All 1000x1000 spp16.

Use different sampler in light sampling.

### Uniform

![](imgsrc/uniform.png)

### Random

![](imgsrc/random.png)

### Blue Noise

![](imgsrc/bluenoise.png)

## Microfacet Model & Multiple importance sampling

| $\alpha$ |       BRDF Sampling       |      Light Sampling       | Multiple importance sampling |
| :------: | :-----------------------: | :-----------------------: | :--------------------------: |
|   0.01   | ![](imgsrc/brdf-0.01.png) | ![](imgsrc/light-0.01.png) |  ![](imgsrc/mis-0.01.png)   |
|   0.1    | ![](imgsrc/brdf-0.1.png) | ![](imgsrc/light-0.1.png) |  ![](imgsrc/mis-0.1.png)   |
|   0.2    | ![](imgsrc/brdf-0.2.png) | ![](imgsrc/light-0.2.png) |  ![](imgsrc/mis-0.2.png)   |

