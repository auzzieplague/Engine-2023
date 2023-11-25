

#cmake settings notes
* set CMake options to: -G Ninja
* set build options: -j 50 
* vcpkg integration
  - https://learn.microsoft.com/en-us/vcpkg/users/buildsystems/cmake-integration
  - -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
  

#agnostic graphics graphicsAPI
- i've started with API_OpenGL with the intention to allow for directX
- setupWindow will need moving to the APIs as window context is different
- no DirectX graphicsAPI methods have been implemented yet

#onion engine refactor
Previous iterations of this engine fall over when attempting collision detection,
we have demos of lighting, texture, animation, lua scripting, sound, and more
in this iteration the intention is to focus on collision and framework.

#collision
we might attempt to bolt in a third party collision framework, previous attempts failed 
however the component structure may have been to far gone to refactor. 

#Prerequisites
couple of things need building and/or including

#Direct X prerequisites
- can just remove API_DirectX.h and references to it if not using it otherwise
- directX https://github.com/microsoft/DirectXTK
- open the sln and build for debug/release 86/64 as required
- include DirectXTK.lib file in vendor libs folder - currently libs/debug/DirectXTK.lib
#requirements for physx
- python 3.11
- cmake 3.26
- vcpkg 
- After failing to link from compiled source due to all kinds of errors I used vcpkg to install physx then copied the dlls, libs from debug folder
  - pay attention to build byteSize and mechine byteSize e.g. debug/release 86/64 nit versions of libs
  - don't forget to include both dlls and the .lib file for dynamic libs (both are required)
  - don't forget to include dlls in the exe folder
---