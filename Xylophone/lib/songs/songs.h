#ifndef SONGS_H
#define SONG_H

#include <avr/pgmspace.h>
// kocka leze dirou
const uint16_t flashSongsTimeStamp1[] PROGMEM = {
    239, 306, 376, 440, 515, 533, 547, 571, 660, 677, 693, 697, 867, 1011, 1129, 1140, 1162, 1411, 1543, 1653, 1665, 1686, 1929, 1989, 2047, 2107, 2171, 2300, 2431, 2553, 2650, 2676, 2694, 2907, 2970, 3029, 3089, 3148, 3279, 3410, 3533, 3655, 3725, 0};

const uint8_t flashSongsNote1[] PROGMEM = {
    0, 1, 2, 3, 0, 2, 4, 2, 0, 2, 4, 2, 5, 5, 0, 2, 4, 5, 5, 0, 2, 4, 3, 3, 3, 3, 2, 2, 1, 1, 0, 2, 4, 3, 3, 3, 3, 2, 2, 1, 1, 0, 7, 0};
// ovcaci ctveraci
const uint16_t flashSongsTimeStamp2[] PROGMEM = {
    240, 328, 418, 633, 727, 819, 1035, 1080, 1128, 1174, 1223, 1311, 1418, 1462, 1514, 1566, 1616, 1702, 1794, 1893, 2110, 2115, 2141, 0};

const uint8_t flashSongsNote2[] PROGMEM = {
    0, 2, 4, 0, 2, 4, 2, 2, 1, 2, 3, 1, 2, 2, 1, 2, 3, 1, 2, 1, 0, 2, 4, 0};
// kohutik jaraby
const uint16_t flashSongsTimeStamp3[] PROGMEM = {
    583, 652, 721, 862, 995, 1055, 1115, 1174, 1230, 1360, 1487, 1549, 1605, 1665, 1725, 1836, 1953, 2016, 2072, 2134, 2196, 2313, 2417, 2477, 0};

const uint8_t flashSongsNote3[] PROGMEM = {
    0, 1, 2, 3, 3, 3, 3, 2, 1, 2, 2, 2, 2, 1, 0, 1, 1, 1, 1, 2, 1, 0, 0, 0, 0};

#include <avr/pgmspace.h>

#endif
