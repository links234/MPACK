This Framework is intended to be a cross-platform starting point for 2D games running on Windows, Linux and Android. Everything is written in C++ and some Bash for building scripts.

Cross-platform features:

	- Custom bash scripts transparent to source tree (folders are only used for better) - moved to makefiles, script are now obsolete
	- Math library
		- 2D, 3D and 4D vectors
		- 3x3 matrices
			- multiplication
			- normal matrix calculation
		- 4x4 matrices
			- multiplication
			- rotation (over X,Y,Z or random axis), translation and scaling
			- frustrum, orthographic and perspective
			- inverse and transpose
			- object and camera look-at
		- Axis aligned bound boxes (AABB for both 1D and 2D)
		- Plane
		- Frustrum
			- reconstruction from view-projection matrix
			- intersection with point
			- intersection with sphere
		- Sphere-sphere intersection
		- 2D triangle determinant
		- Line-line intersection
		- Tangent/bitangent calculation (for normal/bump/parallax mapping)
	- Time service
	- OpenGL 2.0 graphics service
		- Shader loading and management
		- Generic buffer object (VBO/IBO possibly PBO for OpenGL 3.0)
		- 2D Texture loading
			- support multiple filtering types (Point,Bilinear and Trilinear)
			- load from RAW data, file or build-blank
			- wraping mode
		- Sprite rendering system
			- Multi-layer sprite batcher (batch merging for each layer)
			- Basic sprites
			- Animated sprites
				- Rectangular grip for frames
				- Inherits AnimationPlayer
			- Tiled background with parallax effect
			- Multiple shading options implemented in fragment shader:
				- alpha blending, alpha testing and none (does not take care of alpha)
				- per vertex color
			- Debug polygon and circle rendering
		- Texture mapped font rendering
			- load from raw font texture (16x16 cells, one per character)
			- monospaced font option
			- proportional font construction from monospaced font
			- font size and color
			- multiple centering options
		- Particle system
			- emitters (spawner)
				- circle emitter
			- effectors 
				- acceleration (gravity)
				- linear interpolation between 2 colors
			- very flexbile and relatively easy to use
		- Camera system
			- 2D camera
				- position
				- direction
				- zoom
				- object following (fixed camera or spring system option)
			- 3D generic camera
				- look at
			- 3D free camera
		- Simple caching for textures, shaders and buffer object to reduce OGL calls
	- Image loading from file (automatic switch to right format)
		- PNG (pnglib)
		- Targa
	- Physics service
		- AABB fast test
		- Convex polygon collision using Separating Axis Theorem (SAT)
		- Circle collision
		- Circle-Convex polygon collision (SAT)
		- Basic physics (linear velocity, linear acceleration, angular velocity and friction system)
	- General purpose animation player (AnimationPlayer)
		- Forward, backward, loop
		- Interpolation between frames (usefull for MD2 model animation)
	- Random number generation (int and double)
	- Debug 
		- Console/logcat printing
		- Screen printing
		- Assert on OpenGL fault

Android specific features:

	- Transparent resource system (automatic switch from assets to SD files)
	- Multi-touch input (event-based with simple mutex)
		- Pinch to zoom and rotate
		- Virtual joystick
	- Back key overwriting
	- OpenSLES sound service
		- Playlists
		- WAV loading and playback
		- Basic SFX

Windows and Linux features:

	- Window creation
	- Debug
		- File logger in html format
	- Keyboard input
	- Mouse input

