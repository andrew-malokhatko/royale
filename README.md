# Royale
Royale is a real-time multiplayer strategy game (see [Clash Royale](https://supercell.com/en/games/clashroyale/) from [Supercell](https://supercell.com/)). This is my attempt to recreate the game for PC(specifically Windows). Here is the list of features I have managed to add in 15  days of development:

</br>

- Place cards by dragging them onto the field.
- MVC-like architecture that keep classes scalable and loosely coupled.
- Entity Component System to easily construct characters from json files and add new ones.
- Server and client. If the server is running, each event will be broadcasted to all users (see the demo below).
- Some very bad UI code using raylib (I promise I will fix it) :/

</br>

Here is the demo:

<img width="1907" height="997" alt="изображение" src="https://github.com/user-attachments/assets/75fe6d82-cbd7-47fc-b553-737270dc1bdb" />

</br>

# Build & run (untested)
Prerequisites:
- C++20 or later
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

Or if you want to run the server:
```
./server
```


