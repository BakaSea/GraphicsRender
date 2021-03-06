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

## Polygon Light

|     Quadrilateral      |         Pentagon         |         Hexagon         |
| :--------------------: | :----------------------: | :---------------------: |
| ![](imgsrc/square.png) | ![](imgsrc/pentagon.png) | ![](imgsrc/hexagon.png) |

## Microfacet Model & Multiple importance sampling

| $\alpha$ |       BRDF Sampling       |      Light Sampling       | Multiple importance sampling |
| :------: | :-----------------------: | :-----------------------: | :--------------------------: |
|   0.01   | ![](https://raw.githubusercontent.com/BakaSea/GraphicsRender/main/imgsrc/brdf-0.01.png) | ![](https://raw.githubusercontent.com/BakaSea/GraphicsRender/main/imgsrc/light-0.01.png) |  ![](https://raw.githubusercontent.com/BakaSea/GraphicsRender/main/imgsrc/mis-0.01.png)   |
|   0.1    | ![](https://raw.githubusercontent.com/BakaSea/GraphicsRender/main/imgsrc/brdf-0.1.png) | ![](https://raw.githubusercontent.com/BakaSea/GraphicsRender/main/imgsrc/light-0.1.png) |  ![](https://raw.githubusercontent.com/BakaSea/GraphicsRender/main/imgsrc/mis-0.1.png)   |
|   0.2    | ![](https://raw.githubusercontent.com/BakaSea/GraphicsRender/main/imgsrc/brdf-0.2.png) | ![](https://raw.githubusercontent.com/BakaSea/GraphicsRender/main/imgsrc/light-0.2.png) |  ![](https://raw.githubusercontent.com/BakaSea/GraphicsRender/main/imgsrc/mis-0.2.png)   |

