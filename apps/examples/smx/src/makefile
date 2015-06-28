TOPDIR := ${shell pwd | sed -e 's/ /\\ /g'}/../../../../nuttx
include ${TOPDIR}/.config
include ${TOPDIR}/tools/Config.mk
include ${TOPDIR}/arch/arm/src/armv7-m/Toolchain.defs
C++ = ${CROSSDEV}c++
CFLAGS = -std=c++11 -fpermissive
INCLUDES = -I${TOPDIR}/include -I${TOPDIR}/arch/arm/src/sam34/ -I${TOPDIR}/../apps/examples/smx/src/libs

smxengine.o: smxengine.cpp

%.o: 	%.cpp
	@echo ${TOPDIR}
	@echo ${CROSSDEV}
	${C++} -o $@ $^ ${CFLAGS} ${INCLUDES}
