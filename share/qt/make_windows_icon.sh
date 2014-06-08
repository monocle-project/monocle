#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/monocle.png
ICON_DST=../../src/qt/res/icons/monocle.ico
convert ${ICON_SRC} -resize 16x16 monocle-16.png
convert ${ICON_SRC} -resize 32x32 monocle-32.png
convert ${ICON_SRC} -resize 48x48 monocle-48.png
convert monocle-16.png monocle-32.png monocle-48.png ${ICON_DST}

