This will contain the docs explaining the code in this repo
-----------------------------------------------------------
## sampling and aliasing:
- sampling: process of figuring out the colour of a pixel by shooting one or more rays
- currently, we have done point sampling -> shooting one ray per pixel leading **aliasing**
- This is because in real life, points on screen, high quality, dimensionless, essentially, u have inifinite number of samples
- pixels, however, have width and height, u cant treat them as single point, meaning they will get a color leading to sharp jaddges edges which is called **aliasing**
- To solve this, shoot multiple rays around the pixel center, but within the bounds of the pixel, average the color from each ray

### Anti-aliasing tecnhiques:
### 1. Stratified/Pattern Sampling
- divide each pixel into n by n square
- shoot a random ray through a random point in each smaller sub pixel
- average the color

### 2. Pure Random Sampling
- you just pick n random point within that 2d pixel
- average n colours returned

**Note:** 
- in both cases, we sample points around the 2d area, evenly with an even dist, especially in stratified sampling
- we could hit in centre in bith cases - extreemely rare, but we dont care because it is about traeating the 2d areas as a continuous region rather than a single point which it is not because it has dimensions
