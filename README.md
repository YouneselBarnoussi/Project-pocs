# Project-pocs

Proof of concepts for a game project. Each folder in this repository needs to be run seperatly.
Each project will have a small explanation on how to run it.

## Vcpkg

First, follow the quick start/installation in the [vcpkg readme](https://github.com/microsoft/vcpkg/blob/master/README.md)

After the installation is complete run `vcpkg install` in a terminal in the project folder.

Now the project can be build and ran, the output show the version of the three packages installed.

## Conan

First, follow the setup process over at their [docs](https://docs.conan.io/en/latest/installation.html)

Conan has an extension for CLion, this makes it a lot easier and you wouldn't have to run the build/install commands in the terminal yourself.
For more information check: https://blog.jetbrains.com/clion/2019/05/getting-started-with-the-conan-clion-plugin/

If you don't use CLion or want to use the extension, execute this command in a terminal in the rood folder of your project.
`conan install . -if=./YOUR_BUILD_FOLDER -pr=default` Replace 'YOUR_BUILD_FOLDER' with the folder you build the project in.


After that the project can be build and executed.

The output should show a MD5 hash of the text 'Hello world'.

## SDL2

To execute this project, you'll need SDL2.dll on a place your operating system can find it.

The DLL's can be found in `SDL2-2.0.16\lib\x64` for 64 bit or `SDL2-2.0.16\lib\x86` for 32 bit.

Once that is done the project can be build and executed

The output is a green screen that dissapears after 3 seconds.

## SDL2 With input

To execute this project, you'll need SDL2.dll on a place your operating system can find it.

The DLL's can be found in `SDL2-2.0.16\lib\x64` for 64 bit or `SDL2-2.0.16\lib\x86` for 32 bit.

Once that is done the project can be build and executed

The output is a blue screen that can handle input. Press the `ESC` key to quit the program or the `F11` key to toggle fullscreen.

# SFML

There is no setup required to build or run this project.

# Box2D with SDL2

To execute this project, you'll need SDL2.dll on a place your operating system can find it.

The DLL's can be found in `SDL2-2.0.16\lib\x64` for 64 bit or `SDL2-2.0.16\lib\x86` for 32 bit.

Once that is done the project can be build and executed.

This project shows a square that can be moved by arrow keys and bounces of the walls. Press the `S` key to slow the square down or hold the `P` key to pause the square.

