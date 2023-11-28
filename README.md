# DE2 project - Synthesizer
The student project operated within the Bachelor's program of [Digital Electronics 2](https://github.com/tomas-fryza/digital-electronics-2/tree/master/labs/09-project) at Brno University of Technology.
### Team members

* Marek Coufal (responsible for ...)
* Martin Ťavoda (responsible for ...)
* Miloslav Kužela (responsible for ...)
* Roman Vaněk (responsible for ...)

## Theoretical description and explanation

[Block diagram](https://app.diagrams.net/#G1r2vdGk2f0OClIlirRXJdd-qQVvmi0gxV)


## Hardware description of demo application

Insert descriptive text and schematic(s) of your implementation.

## Software description
Full software doxygen documentation available at [Xylophone DOC](https://marouncz.github.io/digital-electronics-2-project/).

Put flowchats of your algorithm(s) and direct links to source files in `src` or `lib` folders.

## Instructions

Write an instruction manual for your application, including photos and a link to a short app video.

## References

1. Write your text here.
2. ...

## TO-DO
1. Zeptat se Fryzy zda muzeme custom projekt
2. Rozvrhnout si práci
3.

## Contribution guide

Your code should be documented in doxygen supported syntax.
> **Note:** For full introduction doxygen documentation see [here](https://embeddedinventor.com/guide-to-configure-doxygen-to-document-c-source-code-for-beginners/).

Here is and example of a Doxygen type documentation for function xylophone:
```c
/**
 * @brief Plays a melody on a virtual xylophone.
 *
 * This function simulates playing a melody on a xylophone. It takes a sequence
 * of notes and produces sound accordingly. The function uses the XYZ algorithm
 * for optimal note generation.
 *
 * @param[in] melody An array of integers representing the notes of the melody.
 * @param[in] duration The duration of each note in milliseconds.
 * @param[out] sound_level The volume level of the xylophone sound (0-100).
 *
 * @return The total duration of the melody playback in milliseconds.
 *
 * @note Ensure that the xylophone is properly initialized before calling this function.
 * @warning This function may produce loud sounds; use caution when adjusting the sound level.
 * @see initialize_xylophone()
 *
 * Example usage:
 * @code
 *   int melody[] = {NOTE_C, NOTE_E, NOTE_G, NOTE_C};
 *   int duration = 500;
 *   int sound_level = 75;
 *   int total_duration = xylophone(melody, duration, sound_level);
 * @endcode
 */
int xylophone(const int melody[], int duration, int *sound_level);
```
