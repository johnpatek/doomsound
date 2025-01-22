# Doomsound

C++ audio framework for DOOM.

## About

This project is comprised of two components:

1. `doomsound` - virtual soundcard driver and audio codec library for 
handling DOOM sound data.
2. `wadsnd` - interactive shell for playing music and sound effects 
from WAD files.

`wadsnd` is an optional component that links to `doomsound`. If another 
project only requires the soundcard and codec interfaces, it can be
skipped in the build process. It is disabled by default, as it is only
useful as a utility for manually testing the `doomsound` interface on 
a given system.
