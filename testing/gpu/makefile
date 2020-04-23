ifndef ISHARC
ISHARC := -I../../include
LSHARC := -L../../lib -lsharc
endif

CC_HOST := g++
CUR_DIR := $(shell pwd)
CASE_NAME := $(notdir ${CUR_DIR})
MAINCC := ${CASE_NAME}.cc
EXE := ./sharctest_${CASE_NAME}
main:
	${CC_HOST} ${ISHARC} ${MAINCC} ${LSHARC} -o ${EXE}

clean:
	-rm ${EXE}

test: clean main
	./${EXE}
