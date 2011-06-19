# Makefile para C/C++
# Version 3
# 
# Carlos Pantelides
# Basado en  
# Copyleft 2004 - Leandro Lucarella, Bajo licencia GPL [http://www.gnu.org/]
# 

#################
# CONFIGURACION #
#################

# Nombre del ejecutable.
target = run

# modo = c89, c99, c++98
modo = c99

# Enumeracion de los archivos a compilar, main.$extension por default

# Descomentar si usa funciones de math.h
#math = si

# Descomentar si usa pthreads
#pthreads = si

# Descomentar si usa gthreads
#gthreads = si

# Descomentar si es un programa GTK+
#gtk = si

# Descomentar si es un programa gtkmm
#gtkmm = si

# Descomentar si se quiere ver como se invoca al compilador
verbose = si

# Descomentar para generar codigo compatible con gdb
debug = si

# Descomentar si usa shared memory
#shared_memory = si

# Descomentar para compilar estaticamente
# static = si

# Opciones para el linker
# LDFLAGS =


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

# flags y libs de GTK+
ifdef gtkmm
  CFLAGS += $(shell pkg-config --cflags gtkmm-2.4)
  LDFLAGS += $(shell pkg-config --libs gtkmm-2.4)
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

# libs de pthreads
ifdef pthreads
  LDFLAGS += -lpthread -pthread
endif

# static
ifdef static
  LDFLAGS += -static
endif

# flags de C para C++
CXXFLAGS += $(CFLAGS)

# seleccion de standard y extension de archivos
ifeq ($(modo),c++98)
  CXXFLAGS += -std=c++98
  extension = cpp
  LD = $(CXX)
else
  CFLAGS += -std=$(modo)
  LD = $(CC)
  extension = c
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

o_files = $(patsubst %.$(extension),%.o,$(fuentes))

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

