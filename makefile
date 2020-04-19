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

COMPILE_TIME_OPT := -DMYVAR=4

final: setup ${CUDA_OBJ} dlink ${HOST_OBJ}
	${CC_HOST} -fPIC -shared ${HOST_OBJ} ${CUDA_OBJ} ${DLINK_OBJ} ${LINKS} -o ${LIB_TARGET}

${HOST_OBJ}: ${OBJ_DIR}/%.o : $(dir ${HOST_SOURCE_FILES})%.cpp
	${CC_HOST} ${INCL} ${COMPILE_TIME_OPT} -c $< -o $@

dlink:
	${CC_CUDA} ${INCL} -Xcompiler -fPIC -rdc=true -dlink ${COMPILE_TIME_OPT} ${CUDA_OBJ} -o ${DLINK_OBJ} -lcudadevrt

${CUDA_OBJ}: ${OBJ_DIR}/%.o : $(dir ${CUDA_SOURCE_FILES})%.cu
	${CC_CUDA} -x cu -rdc=true -Xcompiler -fPIC ${COMPILE_TIME_OPT} -dc $< -o $@

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
