# Makefile

include ../AVBase/config.mak

# DEBUG can be set to YES to include debugging info, or NO otherwise
# DEBUG          := YES

# PROFILE can be set to YES to include profiling info, or NO otherwise
PROFILE        := NO

PRJECTNAME 		:=librecord_jni
GROUPNAME		:=MediaMuxer
#****************************************************************************

OUTPUT_OBJDIR	:=${OUTPUT_OBJDIR}${GROUPNAME}/${PRJECTNAME}/

ifeq (YES, ${DEBUG})
   CFLAGS       := ${DEBUG_CFLAGS} -I../AVBase/${GROUPNAME}
   CXXFLAGS     := ${DEBUG_CXXFLAGS} -I../AVBase/${GROUPNAME}
   LDFLAGS      := ${DEBUG_LDFLAGS} -L../AVBase/${GROUPNAME}/bin/android/AVBase/debug/
   OUTPUT_BINDIR := ${OUTPUT_BINDIR}/debug/
   OUTPUT	:= ${OUTPUT_BINDIR}${PRJECTNAME}.so
   OUTPUT_OBJDIR := ${OUTPUT_OBJDIR}debug
else
   CFLAGS       := ${RELEASE_CFLAGS} -I../AVBase/${GROUPNAME}
   CXXFLAGS     := ${RELEASE_CXXFLAGS} -I../AVBase/${GROUPNAME} -I../AVBase/ffmpeg
   LDFLAGS      := ${RELEASE_LDFLAGS} -L../AVBase/${GROUPNAME}/bin/android/AVBase/release/ -L../AVBase/ffmpeg/output/android/lib/
   OUTPUT_BINDIR := ${OUTPUT_BINDIR}/release/111
   OUTPUT	:= ${OUTPUT_BINDIR}${PRJECTNAME}.so
   OUTPUT_OBJDIR := ${OUTPUT_OBJDIR}release
endif

ifeq (YES, ${PROFILE})
   CFLAGS   := ${CFLAGS} -pg -O3
   CXXFLAGS := ${CXXFLAGS} -pg -O3
   LDFLAGS  := ${LDFLAGS} -pg
endif

LIBS := -lMediaMuxer -llog -lstlport_static -lstdc++
#****************************************************************************
# Include paths
#****************************************************************************

INCS := -I./ -I./include

#****************************************************************************
# Static library paths
#****************************************************************************

LIBDIR := -L../AVBase/${GROUPNAME}/bin/android/AVBase/release/

#****************************************************************************
# Makefile code common to all platforms
#****************************************************************************

CFLAGS   := ${CFLAGS}   ${DEFS}
CXXFLAGS := ${CXXFLAGS} ${DEFS}

#****************************************************************************
# Targets of the build
#****************************************************************************

all: ${OUTPUT}
	if [ ! -d "${OUTPUT_OBJDIR}" ] ; then mkdir "${OUTPUT_OBJDIR}" -p -v; fi
	mv ${OBJS} ${OUTPUT_OBJDIR} -v 			
	mv ${OBJSD} ${OUTPUT_OBJDIR} -v 	
	
#****************************************************************************
# Source files
#****************************************************************************

SRCS := record_jni.cpp

# Add on the sources for libraries
SRCS := ${SRCS}

OBJS := $(addsuffix .o,$(basename ${SRCS}))
OBJSD := $(addsuffix .d,$(basename ${SRCS}))

#****************************************************************************
# Output
#****************************************************************************

${OUTPUT}: ${OBJS}
	if [ ! -d "${OUTPUT_BINDIR}" ] ; then mkdir "${OUTPUT_BINDIR}" -p -v; fi
	${LD} ${LDFLAGS} ${OBJS} ${LIBDIR} ${LIBS} ${EXTRA_LIBS} -o $@ 

#****************************************************************************
# common rules
#****************************************************************************

# Rules for compiling source files to object files
%.o : %.cpp
	${CXX} -c ${CXXFLAGS} ${INCS} $< -o $@

%.o : %.c
	${CC} -c ${CFLAGS} ${INCS} $< -o $@

dist:
	bash makedistlinux

clean:
	rm -f core ${OBJS} ${OUTPUT}
	rm -f core ${OUTPUT_OBJDIR}/*.o

depend:
	#makedepend ${INCS} ${SRCS}
