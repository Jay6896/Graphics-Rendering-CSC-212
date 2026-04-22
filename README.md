# Graphics-Rendering-CSC-212

Repository for trying out different Graphics Libraries and rendering images with them, each folder is named after their respective graphics library

Two small Windows/Visual Studio projects:

- **SDL3 rendering demo**: SDL Rendering/CSC 212/Template/Template.sln
- **OpenGL (GLFW) demo**: Open GL rendering/OpenGL CSC 212/OpenGL Project 1/OpenGL Project 1.sln

## Prerequisites (Windows)

- Visual Studio 2022 with **Desktop development with C++**
- Windows 10/11 SDK (installed by the workload)

External dependencies (not committed to the repo):

- SDL: `SDL3-devel-3.4.2-VC`
- GLFW: `glfw-3.4.bin.WIN64`

## One-time setup (recommended)

Set 2 environment variables so the `.vcxproj` files can find the libraries on _any_ machine.

1. Create an environment variable `SDL3_DIR` pointing at the folder that contains `include` and `lib`.

Example (your SDL folder layout may differ):

- `SDL3_DIR = C:\path\to\SDL3-3.4.2`

2. Create an environment variable `GLFW_DIR` pointing at the folder that contains `include` and `lib-vc2022`.

- `GLFW_DIR = C:\path\to\glfw-3.4.bin.WIN64`

Important: after setting environment variables, **restart Visual Studio** so it picks them up.

## Build & run: SDL3 project

1. Open `SDL Rendering/CSC 212/Template/Template.sln`
2. Select configuration: **Debug** and platform: **x64**
3. Build / Run

Notes:

- The project links `SDL3.lib` from `$(SDL3_DIR)\lib\x64`.
- A post-build step copies `SDL3.dll` into the output folder so the `.exe` runs without manually editing `PATH`.

## Build & run: OpenGL (GLFW) project

1. Open `Open GL rendering/OpenGL CSC 212/OpenGL Project 1/OpenGL Project 1.sln`
2. Select configuration: **Debug** and platform: **x64**
3. Build / Run

Notes:

- The project includes headers from `$(GLFW_DIR)\include` and links `glfw3.lib` from `$(GLFW_DIR)\lib-vc2022`.
- It also links `opengl32.lib` and required Windows system libs.
- A post-build step copies `glfw3.dll` into the output folder (if it exists in `lib-vc2022`).

## Git ignore / cloning notes

- Ignored files (build outputs, `.vs/`, `x64/`, `Debug/`, `*.pdb`, etc.) **do not affect** anyone cloning the repo; they’re generated locally on build.
- If you want to confirm Git is ignoring something, run:
  - `git check-ignore -v "SDL Rendering/CSC 212/Template/x64/Debug"`
  - `git check-ignore -v "Open GL rendering/OpenGL CSC 212/OpenGL Project 1/.vs"`

## Troubleshooting

- **Cannot open include file** (SDL/GLFW headers): double-check `SDL3_DIR` / `GLFW_DIR` and restart VS.
- **LNK1104 cannot open file 'SDL3.lib' / 'glfw3.lib'**: verify the `lib\x64` or `lib-vc2022` folder exists under the path you set.
- **Missing DLL at runtime**: ensure the post-build copy ran, or manually copy `SDL3.dll` / `glfw3.dll` next to the built `.exe`.
