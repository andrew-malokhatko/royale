# Royale
Royale is a real-time multiplayer strategy game (see Clash Royale from SUPERCELL). This is my attempt to recreate the game for PC with raylib. Currently it is only possible to place 
the units by draggin them onto the gaming area.

Here is the demo:

<img width="492" height="958" alt="изображение" src="https://github.com/user-attachments/assets/36a1b593-1810-4008-92c8-e555112eaccd" />

# Build & run
Prerequisites:
- C++17 or later
- raylib (either installed system-wide or built as part of the project)
- CMake (version 3.10 or newer)

First clone the repository:
```
git clone https://github.com/andrew-malokhatko/royale
```

Then build with CMake:
```
mkdir build
cd build
cmake ..
cmake --build .
```

Finally run with:
```
./game
```
