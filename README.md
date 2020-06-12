# Kyle's (Arguably) Amazing Final Graphics Engine
## Kyle Edwards, Period 5

### Excuse the lateness... Sorry :C

## Things I plan to add

- Multiple Lights
- Mesh importing
  - OBJ and STL files
- Set (Assign values to knobs)
- Saveknobs (Save values of knobs)
- Tween (Move between two knob lists)
- Shading revamp
  - Use uthash instead of a KD tree
- Save_Coordinate_System (Save a copy of the stack to the symbol table)
- Cylinders!

## Things I may not get to (but I hope I can!)
- Changing the behavior of vary (Add exponential, logarithmic, sinusodial)
- Texture mapping
- Anti-Aliasing
- Using vary to move lights

## Things I added in the end
- Multiple lights
	- Simple enough, you just declare a new light in the mdl program, and the 
- Mesh importation
	- The importation of obj and stl (both ascii and binary) is available. Some of the .mtl properties of a .obj file have not been added
	- If given ka or kd maps in an mtl file, textures will also be added!
		- This however only works if the textures are .ppm files and are labelled as such in the .mtl file
		- The texturing also only works when phong shading is enabled
- Set
	- Values can be assigned to knobs using ```set [KNOB] [VALUE]```
- Saveknobs
	- You can save the values of the current knobs using ```save_knobs [NAME]```
- Tween
	- Using two knob lists from saveknobs, you can tween to create animation. 
	- Sadly, there isn't any way to change the nature of the tweening, and it's all linear :C
	- ```tween [START FRAME] [END FRAME] [KNOB_LIST_START] [KNOB_LIST_END]```
- Shading
	- You can switch between flat, gouraud, phong, and wireframe shading using ```shading [SHADER_NAME]```
- Save_Coordinate_System
	- Using ```save_coord_system [NAME]```, you can save the current coord system, and use that system for later
- Cylinders
	- ```cylinder [POSSIBLE CONSTANTS] [CX] [CY] [CZ] [RADIUS] [HEIGHT] [POSSIBLE COORD SYSTEM]```
	- Draw a cylinder at point (cx, cy, cz) with radius r and height h.
		- Note that the center of the cylinder is in the actual middle of the cylinder, not on one of the faces
- Super sampling
	- The images are rendered at 500x500, but are drawn as 250x250 pictures with averaging
	- I tried to make them drawn as 500x500, but the program kept crashing for inexplicable reasons >:C