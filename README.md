# Pollo Mania: a C++ chicken game for the Windows console

You are a chicken running around a field, dodging rocks and spitting at them to stay alive. That's the game.

I made Pollo Mania between classes at university. It is a small C++ console game with characters drawn directly in the terminal, a score counter and increasingly crowded levels. The rocks get faster as your score grows, and later levels give your chicken double and triple shots.

## Play

Download or clone the repository and run the included `Juego11.exe` in Windows. Use a console window with at least 80 columns and 35 rows so the playing field fits.

From Command Prompt, in the repository folder:

```bat
Juego11.exe
```

The game text is in Spanish. Press Enter at the opening screen to start.

| Key | Action |
| --- | --- |
| Arrow keys | Move the chicken. |
| A | Spit and destroy rocks. |
| Space | Pause or resume. |
| Esc | End the game during play. |
| Enter | Continue from the opening and level screens. |

## A look at the code

Everything lives in [Juego11.cpp](Juego11.cpp). There are classes for the chicken, rocks, spit and a carrot, with the game loop handling movement, collisions, scores and levels. The carrot code is unfinished.

The source uses `windows.h`, `conio.h` and Windows console functions. To build it, use a Windows C++ compiler that supports those headers. For example, with MinGW-w64 available in Command Prompt:

```bat
g++ Juego11.cpp -o PolloMania.exe
PolloMania.exe
```

The code could use a tidy-up. There is no package structure, and everything shares one source file. Bugs... of course.

## Licence

Shared for educational and showcase purposes under [Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported](LICENSE.txt).
