
CC = g++
EXE_POSTFIX = .exe

CFLAGS_DEBUG = -Wall -I..
CFLAGS_RELEASE = -Wall -I.. -O2
LINKFLAGS_DEBUG = 
LINKFLAGS_RELEASE = -s

LIBRARIES_PTC_DEBUG = ../../OpenPTC/library/cygnus/ptc.lib  -lgdi32 -luser32
LIBRARIES_PTC_RELEASE = ../../OpenPTC/library/cygnus/ptc.lib  -lgdi32 -luser32
LINK_PTC_DEBUG = -Wl,--subsystem,console
LINK_PTC_RELEASE = -Wl,--subsystem,console
CFLAGS_PTC_DEBUG = -I../../OpenPTC/source
CFLAGS_PTC_RELEASE = -I../../OpenPTC/source

LIBRARIES_GLUT_DEBUG = 
LIBRARIES_GLUT_RELEASE = 
LINK_GLUT_DEBUG =
LINK_GLUT_RELEASE = 
CFLAGS_GLUT_DEBUG = -I../../glut-3.7/include
CFLAGS_GLUT_RELEASE = 
