# Wolfenstein-Style 3D Game Engine

This is a basic 3D game engine built from the ground up, inpired by the original 'Wolfenstein 3D' game. It uses rasterization with raycasting to produce a 3D-looking scene on a two-dimensional screen. It is CPU-based and does not leverage any external graphics APIs (viz. OpenGL, Vulcan, etc), rather manually calculates and assigns values to the pixel buffer with math.

## Features
- Raycasting: Rendering a 3D environment using 2D grid-based maps.
- Basic Lighting: Walls that are further away get darker to get a better feel for the 3D perspective.
- Simple Collision Detection
- Scene and Player Customization: Ability to change colours of the various elements in the scene along with customizing player speed.
- Mini-map: A mini-map to better help with navigation.

## Usage
To try the game for yourself
- Navigate to the 'Releases' section.
- Download the `WolfensteinCloneV2.zip` folder.
- Unzip the entire folder into a preferred directory.
- Run the `WolfensteinClone.exe` executable.
- If Windows tries to block the application, press 'More Info' and then 'Run Anyway'.
- Press 'START' on the top right of the window to start the game.

## Screenshots
![game_showcase](https://github.com/user-attachments/assets/67910898-2c38-4fec-8f29-53f6858d17df)

![color_customization](https://github.com/user-attachments/assets/4a0ab78d-b763-4287-8e55-0d2f1818460e)

### Note:
- The actual project scripts are stored in `WolfensteinClone/src`, not `scripts`.
