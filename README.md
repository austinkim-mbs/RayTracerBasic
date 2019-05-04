# RayTracerBasic

Basic Ray Tracer based on Peter Shirley's Ray Tracing in a weekend

Used as a method to familiarize myself with C++.

The basic methodology for this project relies on interactions with spheres on a 3-dimensional plot.
1. Spheres were used to simplify interactions, since reflections will create surface normals.
2. Materials used are matte and metal.
3. A camera will project the 3D space onto a 2D image. 

4. Rays are shot from origin (0,0,0) to every point. if rays intersect with an object, that pixel/spot is colored based on material and ray
and a new ray is created from that point. This process wil continue so all interaction points are colored appropriately.

5. Perspective Camera has been coded to be movable, to have a shifting 2D projected film space that is requires further reading to understand. 

