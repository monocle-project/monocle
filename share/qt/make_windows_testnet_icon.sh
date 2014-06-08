#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/monocle_testnet.png
ICON_DST=../../src/qt/res/icons/monocle_testnet.ico
convert ${ICON_SRC} -resize 16x16 monocle_testnet-16.png
convert ${ICON_SRC} -resize 32x32 monocle_testnet-32.png
convert ${ICON_SRC} -resize 48x48 monocle_testnet-48.png
convert monocle_testnet-16.png monocle_testnet-32.png monocle_testnet-48.png ${ICON_DST}

