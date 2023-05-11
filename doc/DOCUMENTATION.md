# DOCUMENTATION ARCADE

The arcade is a C++ project that is designed to be able to have different
graphical libraries, with different games that can all be played by all the
graphical libraries.

## Implement new libraries

The libraries are used to make games or graphical libraries, you can implement
for example the SFML, SDL2 with a nibbler game or a snake game.

### What attributes do we need to use ?

First we will need a `arcade::Size` that has a **width** and a **height**. This
attribute can be found in the
link : [<FrameBuffer.hpp>](https://github.com/Ackfire/Arcade/blob/main/interfaces/FrameBuffer.hpp) <br>

Then, we will need a `arcade::Pixel`, that has a **bool up**, it will show if
the pixel was updated or not to be able to not draw it again if it was not
updated, a **fg**, to print a color to the character (between 0 and 127), a **bg**,
to print a color to the background (between 0 and 127) and a `char c` that
is an enum of `arcade::Character` (you can find it in
the [<Enum.hpp>](https://github.com/Ackfire/Arcade/blob/main/interfaces/Enum.hpp) <br>

Also, you will need a `arcade::FrameBuffer`. You can find it in
the [<FrameBuffer.hpp>](https://github.com/Ackfire/Arcade/blob/main/interfaces/FrameBuffer.hpp)
Be careful, the size of the vector **has** to be equal to `width * height` <br>

You will also need a `arcade::STATUS`, that is an enum of four things:

* **exit**, exit the project <br>
* **failure**, exit the project without clearing anything <br>
* **running**, continue to run <br>
* **option**, call the `option` function in the current game. <br>

You can find it in the [<Enum.hpp>](https://github.com/Ackfire/Arcade/blob/main/interfaces/Enum.hpp)

You will then need a `arcade::EVENT` that is an enum of all the possible events,
you can find it in
the [<Enum.hpp>](https://github.com/Ackfire/Arcade/blob/main/interfaces/Enum.hpp) <br>
&emsp; In those events, you will have **3** possibilities: <br>
&emsp;&emsp; - The `ARCADE_KEY_SMT`, it's a key bind and is used by the game to
know what key is pressed (it can be found in
the [<Enum.hpp>](https://github.com/Ackfire/Arcade/blob/main/interfaces/Enum.hpp) <br>
&emsp;&emsp; - The `ARCADE_SYS_SMT`, it's a system event that is intercepted by
the core to know what to do (it can be found in
the [<Enum.hpp>](https://github.com/Ackfire/Arcade/blob/main/interfaces/Enum.hpp) <br>
&emsp;&emsp; - The `ARCADE_WIN_SMT`, it's a window event that is intercepted by
the core to know what to do (it can be found in
the [<Enum.hpp>](https://github.com/Ackfire/Arcade/blob/main/interfaces/Enum.hpp) <br>

You will need a `arcade::Character` that will have all the possible forms of
character, it is include in
the [<Enum.hpp>](https://github.com/Ackfire/Arcade/blob/main/interfaces/Enum.hpp) <br>

You will also need `arcade::Option`, it is only used by a `std::pair` containing
the enum option and a string as arguments <br>
It is an enum with those options: <br>
&emsp;&emsp; - `LOAD_GRAPH`, loads a new graphical library from the path given
in the pair <br>
&emsp;&emsp; - `LOAD_GAME`, loads a new game library from the path given in the
pair <br>
&emsp;&emsp; - `RESTART`, restart the current game, second pair argument is
ignored <br>
&emsp;&emsp; - `QUIT`, go back to menu second pair argument is ignored
You can find it in the [<Enum.hpp>](https://github.com/Ackfire/Arcade/blob/main/interfaces/Enum.hpp)

To finish, you need a `arcade::LibType` that is an enum, it is used to know if
the lib is a game, by using `GAME` or a graphical, by using `GRAPHICAL`. It is
found in
the [<Enum.hpp>](https://github.com/Ackfire/Arcade/blob/main/interfaces/Enum.hpp). <br>

### Graphics Libraries

To implement a new graphics library, you need to create a new class that
inherits from `IDisplay.hpp`:

```cpp
namespace arcade {

    class IDisplay
    {
        public:
        IDisplay() = default;
        IDisplay(arcade::Size size);
        IDisplay(const IDisplay &) = delete;
        IDisplay(IDisplay &&) = delete;
        IDisplay &operator=(const IDisplay &) = delete;
        IDisplay &operator=(IDisplay &&) = delete;
        virtual ~IDisplay() = default;

        virtual Size getSize() const = 0;
        virtual void setSize(arcade::Size size) = 0;

        virtual std::list<arcade::EVENT> pollEvents(std::list<arcade::EVENT> &events) = 0;

        virtual void draw(arcade::FrameBuffer &frameBuffer) = 0;

        virtual void clear() = 0;
        virtual void display() = 0;
    };
};// namespace arcade
```

You will also need a C symbol named to load the library and get its type
Like this:

```c++
extern "C" const arcade::LibType getType()
{
    return arcade::LibType::GRAPHICAL;
}

extern "C" std::unique_ptr<arcade::IDisplay> createLibrary(arcade::Size size)
{
    return std::make_unique<arcade::ncurses::DisplayNcurses>(size);
}
```

The library needs to implement the following methods:

Two constructors, one with no parameters and one with a `Size` parameter.
In the constructor, you need to initialize:

* The window
* The window size

```c++
IDisplay() = default;
IDisplay(arcade::Size size);
```

A destructor that needs to unload the memory used by the library.

```c++
virtual ~IDisplay() = default;
```

A getter that returns the current window size.

```c++
virtual Size getSize() const = 0;
```

A setter that changes the window size without clearing it.

```c++
virtual void setSize(arcade::Size size) = 0;
```

A method that returns a list of events that happened since the last call by
adding them to the list already given in parameter.

```c++
virtual std::list<arcade::EVENT> pollEvents(std::list<arcade::EVENT> &events) = 0;
```

A method that draws the frameBuffer on the window.

```c++
virtual void draw(arcade::FrameBuffer &frameBuffer) = 0;
```

A method that clears the window.

```c++
virtual void clear() = 0;
```

A method that displays what was drawn on the window by the draw method.

```c++
virtual void display() = 0;
```

<br>

You can find an example of implementation with this
link : [SFML graphic library implementation](https://github.com/Ackfire/Arcade/blob/main/libs/display/sfml/src/DisplaySfml.cpp)

<br>

### Game Libraries

To implement a new game library, you need to create a new class that inherits
from `IGame.hpp`:

```cpp
namespace arcade {
    class IGame
    {
        public:
        IGame() = default;
        IGame(const IGame &) = delete;
        IGame(IGame &&) = delete;
        IGame &operator=(const IGame &) = delete;
        IGame &operator=(IGame &&) = delete;
        virtual ~IGame() = default;

        virtual arcade::Size getSize() const = 0;

        virtual arcade::STATUS run(std::list<arcade::EVENT> &events) = 0;

        virtual arcade::FrameBuffer &getFrameBuffer() = 0;

        virtual std::pair<arcade::OPTIONS, std::string> option() = 0;
    };
};// namespace arcade
```

It needs to implement the following methods:

A constructor.
In it, you need to initialize:

* A frame buffer (every pixel needs to have their up at false)
* The game size

```c++
IGame() = default;
```

A destructor that unloads everything.

```c++
virtual ~IGame() = default;
```

A getter for the game size. <br>
The size cannot be changed.

```c++
virtual arcade::Size getSize() const = 0;
```

A method that runs the game.

```c++
virtual arcade::STATUS run(std::list<arcade::EVENT> &events) = 0;
```

Run a tick of the game. (Will be called 60 times per second)

A getter for the frame buffer.

```c++
virtual arcade::FrameBuffer &getFrameBuffer() = 0;
```

A method that returns the game options.

```c++
virtual std::pair<arcade::OPTIONS, std::string> option() = 0;
```

You can find an example of implementation with this
link : [Snake game library implementation](https://github.com/Ackfire/Arcade/blob/main/libs/games/snake/src/GameSnake.cpp)

You can find the dependency graph of the project with this image:

![Dependency graph](/doc/dependencyGraph.svg)

:+1: Thanks for reading this documentation. <br>
