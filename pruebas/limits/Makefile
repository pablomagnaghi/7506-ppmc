# Makefile para C/C++
# Un ejecutable en multiples carpetas
# Testing con setup, run y cleanup
#
# Version 12 
# 
# Carlos Pantelides 2009, 2010, 2011
# Basado en  
# Copyleft 2004 - Leandro Lucarella, Bajo licencia GPL [http://www.gnu.org/]
# 

#################
# CONFIGURACION #
#################

# Nombre del ejecutable.
target = run

# modo = c89, c99, c++98, c++0x
modo = c++98

# Descomentar si se quiere ver como se invoca al compilador
verbose = si

# Descomentar para generar codigo compatible con gdb
debug = si

# Agregar object files
#o_files  = 
#o_files += ../tp/FileReader.o
#o_files += ../tp/FileWriter.o

# Descomentar para compilar estaticamente
#static = si

# Opciones para el linker
# LDFLAGS =

# Descomentar si usa funciones de math.h
#math = si

# Descomentar si usa pthreads
#pthreads = si

# Descomentar si usa gthreads
#gthreads = si

# Descomentar si usa GTK+
#gtk = si

# Descomentar si usa gtkmm
#gtkmm = si

# Descomentar si usa OpenGL
#gl = si

# Descomentar si usa OpenGL Utility
#glu = si

# Descomentar si usa GLUT
#glut = si

# Descomentar si usa SDL
#sdl = si

# Descomentar si usa libid3
#id3 = si

# Descomentar si usa libpng
#png = si

# Descomentar si usa gd
#gd = si

# Descomentar si usa fam
#fam = si

# Descomentar si usa extractor
#extractor = si

# Descomentar si usa shared memory
#shared_memory = s

# Descomentar si usa xerces-c
#xercesc = si

#####################
# FIN CONFIGURACION #
#####################

# Opciones para el compilador C/C++ en modo ansi.
CFLAGS = -Wall -pedantic -pedantic-errors

ifdef debug
  # Para valgrind o debug
  CFLAGS += -ggdb -DDEBUG -fno-inline
else
  # Para que explote lo mas posible
  CFLAGS += -O3 -DNDEBUG
endif

# shared memory
ifdef shared_memory
  LDFLAGS += -lrt
endif

# flags y libs de GTK+
ifdef gtk
  CFLAGS += $(shell pkg-config --cflags gtk+-2.0)
  LDFLAGS += $(shell pkg-config --libs gtk+-2.0)
endif

# flags y libs de GTKmm
ifdef gtkmm
  CFLAGS += $(shell pkg-config --cflags gtkmm-2.4)
  LDFLAGS += $(shell pkg-config --libs gtkmm-2.4)
endif

# flags y libs de gd
ifdef gd
  CFLAGS += $(gdlib-config --cflags)
  LDFLAGS += $(gdlib-config --libs)
endif

# libs de extractor
ifdef extractor
#  CFLAGS += $(shell pkg-config --cflags libextractor)
  LDFLAGS += $(shell pkg-config --libs libextractor)
endif

# flags y libs de gthreads
ifdef gthreads
  CFLAGS += $(shell pkg-config --cflags gthread-2.0)
  LDFLAGS += $(shell pkg-config --libs gthread-2.0)
endif

# libs de libm
ifdef math
  LDFLAGS += -lm
endif

# libs y flags de sdl
# @todo normalizar image, gfx
# @todo normalizar png y ver relacion con libpng
ifdef sdl
CFLAGS += $(shell sdl-config --cflags)
CXXFLAGS += $(shell sdl-config --cflags)
LDFLAGS += $(shell sdl-config --libs)
LDFLAGS += -lSDL_image
#LDFLAGS += -lSDL_gfx
LDFLAGS += -lpng
endif

#libs de OpenGL
ifdef gl
LDFLAGS += -lGL 
endif

#libs de OpenGL Utilities
ifdef glu
LDFLAGS += -lGLU
endif

#libs de GLUT
ifdef glut
LDFLAGS += -lglut
endif

# flags y libs de libng
ifdef png
  CFLAGS += $(shell pkg-config --cflags libpng)
  LDFLAGS += $(shell pkg-config --libs libpng)
endif

# libs de id3
ifdef id3
  LDFLAGS += -lid3
endif

# libs de pthreads
ifdef pthreads
  LDFLAGS += -lpthread -pthread
endif

# libs de fam
ifdef fam
  LDFLAGS += -lfam
endif

# static
ifdef static
  LDFLAGS += -static
endif

# xerces-c
ifdef xercesc
  LDFLAGS += -l xerces-c
endif

# flags de C para C++
CXXFLAGS += $(CFLAGS)

# seleccion de standard y extension de archivos
ifeq ($(modo),c++98)
  CXXFLAGS += -std=c++98
  extension = cpp
  LD = $(CXX)
else
  ifeq ($(modo),c++0x)
    CXXFLAGS += -std=c++0x
    extension = cpp
    LD = $(CXX)
  else
    CFLAGS += -std=$(modo)
    LD = $(CC)
    extension = c
  endif
endif

# Si no especifica archivos, tomo todos.
fuentes ?= $(wildcard *.$(extension))

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)
ifdef verbose
  RM := $(RM) -v
else
  CC =  @echo "  CC  $@"; $(occ)
  CXX = @echo "  CXX $@"; $(ocxx)
  RM =  @echo "  CLEAN"; $(orm)
  LD =  @echo "  LD  $@"; $(old)
endif

##########
# REGLAS #
##########

.PHONY: all clean

all: $(target)

o_files += $(patsubst %.$(extension),%.o,$(fuentes))

%.deps: %.$(extension)
	@set -e; rm -f $@; \
		$(old) -MM -MG -MP $(CXXFLAGS) $(CFLAGS) $< -MF $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

-include $(o_files:.o=.deps)

$(target): $(o_files)
	@if [ -z "$(o_files)" ]; \
	then \
		echo "No hay archivos de entrada, recuerde que la extensión debe ser '.$(extension)'."; \
		false; \
	fi >&2
	$(LD) $(LDFLAGS) $(o_files) $(LOADLIBS) $(LDLIBS) -o $(target)

clean:
	$(RM) $(o_files) $(o_files:.o=.deps) $(target)

test: all
	@./test/setup.sh 
	@./test/run.sh && echo "Testing OK"
	@./test/cleanup.sh
