# What is this?
This is an Expression 2 CPU for the game Garry's Mod using Wiremod.

It implements a custom ISA "defined" in doc.txt.

The script itself is in cpu.txt

You can look at gen.cpp to get an idea on how to generate some assembly code.

randomnumbergen.txt contains the hex-encoded assembly code for a program which generates two random numbers and writes them to the addresses 65536 and 65537 respectively. Connect a "Data - Port" to the "DEV"-Wirelink and then hook up an Oscilloscope. X->Port0. Y->Port1.
