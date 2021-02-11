# OpenGLHouse
3D House model with Camera class and textures. This requires OpenGL to work and also OpenGL Mathematics - GLM available from here: https://glm.g-truc.net/0.9.5/api/index.html 

This is now updated to run without stb_image. I have reinvented the wheel! I wanted to practice loading images, and this is the result. So it illustrates how to load BMP files as well as creating an object in a world you can move around in. 

This is more complex 3D object with textures. It includes a Texture class and a Camera class. The Camera Class is heavily based on the work of Ben Cook who produced a udemy course on OpenGL. Do check it out. 

I did not use blender for this but ploted it on paper in order to fully understand the process. It was more difficult than you would imagine!

I used photos to make the textures and tried as much as possible to make them square and a resolution of a power of 2 which is best. I used colours to make the textures more interesting and add some shading. Obviously the way to add shading normally is with lighting but I chose to focus on textures for this project.

Everything should be illustrated in the comments

to compile on gcc use g++ house.cpp GLWindow.cpp Mesh.cpp Shader.cpp Camera.cpp Texture.cpp -o house  -lGL -lglfw -lGLEW


