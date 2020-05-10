LIB_TITLE := sharc

CC_HOST := g++
CC_CUDA := nvcc

BASE_DIR    := $(shell pwd)
OBJ_DIR     := ${BASE_DIR}/obj
LIB_DIR     := ${BASE_DIR}/lib
HDR_DIR     := ${BASE_DIR}/include

LIB_TARGET := ${LIB_DIR}/lib${LIB_TITLE}.a

HOST_SOURCE := ${BASE_DIR}/src/host
CUDA_SOURCE := ${BASE_DIR}/src/cuda

HOST_SOURCE_FILES := $(wildcard ${HOST_SOURCE}/*.cpp)
CUDA_SOURCE_FILES := $(wildcard ${CUDA_SOURCE}/*.cu)
HOST_HEADER_FILES := $(wildcard ${HOST_SOURCE}/*.h)
CUDA_HEADER_FILES := $(wildcard ${CUDA_SOURCE}/*.h)
HEADER_FILES := ${HOST_HEADER_FILES} ${CUDA_HEADER_FILES}
HOST_OBJ  := $(patsubst ${HOST_SOURCE}/%.cpp,${OBJ_DIR}/%.o,${HOST_SOURCE_FILES})
CUDA_OBJ  := $(patsubst ${CUDA_SOURCE}/%.cu,${OBJ_DIR}/%.o,${CUDA_SOURCE_FILES})
DLINK_OBJ := ${OBJ_DIR}/sharc_cuda_dlink.o

INCL := -I${HDR_DIR}
INCL += -I/usr/local/cuda/include



LINKS := -lz
LINKS += -L/usr/local/cuda/lib64 -lcudadevrt -lcudart

COMPILE_TIME_OPT := -DBLOCK_SIZE=32
COMPILE_TIME_OPT += -DGEOM_PRECISION=1

export ISHARC=-I${HDR_DIR} ${INCL}
export LSHARC=-L${LIB_DIR} -l${LIB_TITLE} ${LINKS}

final: setup ${CUDA_OBJ} dlink ${HOST_OBJ}
	${CC_HOST} -fPIC -shared ${HOST_OBJ} ${CUDA_OBJ} ${DLINK_OBJ} ${LINKS} -o ${LIB_TARGET}

${HOST_OBJ}: ${OBJ_DIR}/%.o : ${HOST_SOURCE}/%.cpp
	${CC_HOST} -fPIC ${INCL} ${COMPILE_TIME_OPT} -c $< -o $@

dlink:
	${CC_CUDA} ${INCL} -Xcompiler -fPIC -rdc=true -dlink ${COMPILE_TIME_OPT} ${CUDA_OBJ} -o ${DLINK_OBJ} -lcudadevrt

${CUDA_OBJ}: ${OBJ_DIR}/%.o : ${CUDA_SOURCE}/%.cu
	${CC_CUDA} -x cu -rdc=true -Xcompiler -fPIC ${INCL} ${COMPILE_TIME_OPT} -dc $< -o $@

setup:
	-rm -r ${HDR_DIR}
	mkdir -p ${HDR_DIR}
	for hdr in ${HEADER_FILES} ; do \
		ln -s $${hdr} -t ${HDR_DIR};\
	done
	mkdir -p ${OBJ_DIR}
	mkdir -p ${LIB_DIR}

clean:
	-rm -r ${HDR_DIR}
	-rm -r ${OBJ_DIR}
	-rm -r ${LIB_DIR}
	for fldr in testing/* ; do \
        ${MAKE} -C $${fldr} -f makefile clean || exit 1; \
    done

test: clean final
	for fldr in testing/* ; do \
        ${MAKE} -C $${fldr} -f makefile -s test || exit 1; \
    done
