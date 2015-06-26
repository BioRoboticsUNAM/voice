voice
==========

A festival-based port of the SP-GEN in C++ for linux using the uRobotics
These softwares are all part of the work developed at the Bio-Robotics Laboratory at UNAM, and are used in our service robots.

### Supported commands:
say "Text to say"
read "path/to/file/with/text_to_read"

### Prerrequisites:
voice requires NCurses, EST, Festival, Speech-tools, PortAudio, LibSndFile

for installing, run:

# apt-get install libestools2.1 libestools2.1-dev libncurses5-dev festival festival-dev speech-tools
# apt-get install libportaudio2 portaudio19-dev libsndfile1-dev

PortAudio may refuse to install. In those cases download and build source. Install in /usr
If PortAudio is installed in another location different from /usr/lib, symlinks may be required

Notice that the default [crappy] voice installed by Festival is hard to understand. It is adviced to install 3rd party voices.
