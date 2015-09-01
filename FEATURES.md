# Full features list:

### Cross-platform features:

1. Custom bash scripts transparent to source tree (folders are only used for better structure) - moved to makefiles, script (~~apr.sh~~) is now obsolete
2. Math library
   + 2D, 3D and 4D vectors
   + 3x3 matrices
      - multiplication
      - normal matrix calculation
   + 4x4 matrices
      - multiplication
      - rotation (over X,Y,Z or random axis), translation and scaling
      - frustrum, orthographic and perspective
      - inverse and transpose
      - object and camera look-at
   + Axis aligned bounding boxes (AABB for both 1D and 2D)
   + Plane
   + Frustrum
      - reconstruction from view-projection matrix
      - intersection with point
      - intersection with sphere
   + Sphere-sphere intersection
   + 2D triangle determinant
   + Line-line intersection
   + Tangent/bitangent calculation (for normal/bump/parallax mapping)
3. Time service
4. Transparent resource system (automatic switch from assets to SD files or MVFS files)
5. OpenGL 2.0 graphics service
   + Shader loading and management
   + Generic buffer object (VBO/IBO possibly PBO for OpenGL 3.0)
   + 2D Texture loading
      - support multiple filtering types (Point,Bilinear and Trilinear)
      - load from RAW data, file or build-blank
      - wraping mode
   + Sprite rendering system
      - Multi-layer sprite batcher (batch merging for each layer)
      - Basic sprites
      - Animated sprites
      - Tiled background with parallax effect
      - Multiple shading options built in fragment shader:
         - alpha blending, alpha testing and none (does not take care of alpha)
         - per vertex color
      - Debug polygon and circle rendering
   + Custom render calls
   + Texture mapped font rendering
      - load from raw font texture (16x16 grid, one per character)
	  - render as monospaced font
	  - automatic construction 
	  - font size and color
	  - centering/alignment
   + Particle system
      - full flexibility
      - emitters (spawner)
         - circle emitter
      - effectors (modifier)
         - acceleration (gravity)
         - linear interpolation between 2 colors
   + Post effect rendering (pipelined) with built in:
      - FXAAI
      - FXAAII
   + Camera system
      - 2D camera (follow an object and spring system)
      - 3D generic camera
      - 3D free camera
   + Basic UI scaling helper functions
   + Basic caching for textures, shaders and buffer objects to reduce OGL calls
6. Image loading from file (automatic switch to right format)
   + PNG (pnglib)
   + Targa
7. Physics service
   + AABB fast test
   + Convex-convex polygon collision using SAT
   + Circle-circle collision
   + Circle-Convex polygon collision (SAT)
   + Basic physics (linear velocity, linear acceleration, angular velocity and friction system)
7. Misc
   + General purpose animation player (AnimationPlayer)
      - Forward, backward, loop
      - Interpolation between frames (usefull for MD2 model animation)
   + Random number generation (int, double, flip coin)
   + Various string functions (StringEx):
      - get extension (from path)
      - upper, lower, to upper, to lower
      - is printable, visible, control char, lower/upper case, alpha, digit, etc.
      - to int, bool, double
      - strip left, right, substr, slice
      - memswap
   + Uncopyable class
9. Debug 
   + Console/logcat printing
   + Screen printing
   + Assert on OpenGL or EGL error

### Android specific features:

1. Multi-touch input (event-based)
   + Pinch to zoom and rotate
   + Virtual joystick
2. Back key overwriting
3. OpenSLES sound service
   + WAV/MP3/OGG loading and playback
   + Basic SFX
   + Controller wrappers (please note that not all are supported on all devices) for:
      - Play (Start/Pause/Resume)
      - Volume
      - Bass booster
      - Pitch
      - Stereo
      - Seek
      - Playback rate
   + Group controllers (issue a regular controller action to multiple objects)
4. Google Ads

### Windows and Linux features:

1. Window creation
2. Debug
   + File logger in html format
3. Input
   + Keyboard input
   + Mouse input

