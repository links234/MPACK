cmake_minimum_required(VERSION 3.3)
project(MPACK)

include_directories(
        ./jni/MPACK/Network
        ./jni/MPACK/Sound/ItfSound/ItfAudioController
        ./jni/MPACK/Sound/ItfSound/ItfAudioController/ItfGroupController
        ./jni/MPACK/Sound/ItfSound
        ./jni/MPACK/Sound/OpenSLES/OSLESAudioController
        ./jni/MPACK/Sound/OpenSLES/OSLESAudioController/OSLESGroupController
        ./jni/MPACK/Sound/OpenSLES
        ./jni/MPACK/Input
        ./jni/MPACK/Input/Android
        ./jni/MPACK/Input/Desktop
        ./jni/MPACK/Input/Desktop/OSX
        ./jni/MPACK/Input/Desktop/Windows
        ./jni/MPACK/Input/Desktop/Linux
        ./jni/MPACK/Algorithm/Geometry
        ./jni/MPACK/Resources/IniFile
        ./jni/MPACK/Resources/InputResources
        ./jni/MPACK/Resources/DOMParsers
        ./jni/MPACK/Resources
        ./jni/MPACK/Resources/MVFS/Binding
        ./jni/MPACK/Resources/MVFS
        ./jni/MPACK/Graphics/Font
        ./jni/MPACK/Graphics/Texture
        ./jni/MPACK/Graphics/Texture/Image
        ./jni/MPACK/Graphics/Geometry
        ./jni/MPACK/Graphics
        ./jni/MPACK/Graphics/Sprite
        ./jni/MPACK/Graphics/UI
        ./jni/MPACK/Graphics/Shader
        ./jni/MPACK/Graphics/Particles
        ./jni/MPACK/Graphics/Particles/Effector
        ./jni/MPACK/Graphics/Particles/Emitter
        ./jni/MPACK/Graphics/Camera
        ./jni/MPACK/Physics
        ./jni/MPACK/Physics/Shape
        ./jni/MPACK
        ./jni/MPACK/Core/Application
        ./jni/MPACK/Core/Logger
        ./jni/MPACK/Core/EventLoop
        ./jni/MPACK/Core/EventLoop/Android
        ./jni/MPACK/Core/EventLoop/Android/EGL
        ./jni/MPACK/Core/EventLoop/OSX
        ./jni/MPACK/Core/EventLoop/Windows
        ./jni/MPACK/Core/EventLoop/Linux
        ./jni/MPACK/Core/Console/Android
        ./jni/MPACK/Core/Console/OSX
        ./jni/MPACK/Core/Console/Windows
        ./jni/MPACK/Core/Console
        ./jni/MPACK/Core/Console/Linux
        ./jni/MPACK/Core/Console/Stub
        ./jni/MPACK/Debug/Profiler
        ./jni/MPACK/Debug
        ./jni/MPACK/Time/Android
        ./jni/MPACK/Time
        ./jni/MPACK/Time/OSX
        ./jni/MPACK/Time/Windows
        ./jni/MPACK/Time/Linux
        ./jni/MPACK/Math
        ./jni/MPACK/Modules/Android/GoogleAdMob
        ./jni/MPACK/Modules/Android/Keyboard
        ./jni/MPACK/Modules/Android/GoogleGameServices
        ./jni/MPACK/Modules/Android/RateMe
        ./jni/MPACK/Modules/Android/EasyShare
        ./jni/MPACK/Modules/Android/Encryptor
        ./jni/MPACK/Modules/Android/InternetConnection
        ./jni/MPACK/Modules/Android/GoogleInAppPurchases
        ./jni/MPACK/Modules/MVFS
        ./jni/MPACK/Modules/MVFS/V1
        ./jni/MPACK/Modules/MVFS/FileReader
        ./jni/MPACK/Modules/Experimental
        ./jni/MPACK/Misc
        ./jni/DemoAndroidApplication
        ./jni/DemoAndroidApplication/PlayGame/Input
        ./jni/DemoAndroidApplication/PlayGame/Input/Android
        ./jni/DemoAndroidApplication/PlayGame/Input/Desktop
        ./jni/DemoAndroidApplication/PlayGame/Object
        ./jni/DemoAndroidApplication/PlayGame
        ./jni/DemoAndroidApplication/WaterState/Input/WSDesktopInput
        ./jni/DemoAndroidApplication/WaterState/Input
        ./jni/DemoAndroidApplication/WaterState
        ./jni/DemoAndroidApplication/WaterState/WSObject
        ./jni/DemoAndroidApplication/MainMenu/GUI
        ./jni/DemoAndroidApplication/MainMenu/Input
        ./jni/DemoAndroidApplication/MainMenu
        ./jni/DemoConsoleApplication
        ./jni
        ./jni/DemoSeamCarvingApplication
        ./jni/DemoNetworkConsoleApplication
        ./jni/MPACK/Sound
        ./jni/MPACK/Glue
        ./jni/MPACK/Algorithm/DataStructures/AVL
        ./jni/MPACK/Algorithm/DataStructures/SearchList
        ./jni/MPACK/Algorithm/DataStructures/StaticStack
        ./jni/MPACK/Algorithm/DataStructures/StaticQueue
        ./jni/MPACK/Algorithm/DataStructures/IndexedSkipList
        ./jni/MPACK/Algorithm
        ./jni/MPACK/Core
        ./jni/MPACK/Math/Vector
        ./jni/MPACK/Math/Matrix
)

if (WIN32)
    add_custom_target(MPACK ALL COMMAND make -f "jni/Windows.mk" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif (WIN32)

if (UNIX)
    add_custom_target(MPACK ALL COMMAND make -f "jni/Linux.mk" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif (UNIX)

if (APPLE)
    add_custom_target(MPACK ALL COMMAND make -f "jni/OSX.mk" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif (APPLE)
