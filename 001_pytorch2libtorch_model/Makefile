GPU=1
CUDNN=1
DEBUG=1

ARCH= -gencode arch=compute_30,code=sm_30 \
      -gencode arch=compute_35,code=sm_35 \
      -gencode arch=compute_50,code=[sm_50,compute_50] \
      -gencode arch=compute_52,code=[sm_52,compute_52]
#      -gencode arch=compute_20,code=[sm_20,sm_21] \ This one is deprecated?

# This is what I use, uncomment if you know your arch and want to specify
# ARCH= -gencode arch=compute_52,code=compute_52

VPATH=.
EXEC=myapp
OBJDIR=./obj/

CC=gcc
CPP=g++
NVCC=nvcc 
AR=ar
ARFLAGS=rcs
OPTS=-Ofast
LDFLAGS= -lm -pthread 
CFLAGS=-Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC
COMMON= -D_GLIBCXX_USE_CXX11_ABI=0 -I/home/disk1/data/s_software/libtorch_92/libtorch/include -I/home/disk1/data/s_software/libtorch_92/libtorch/include/torch/csrc/api/include -std=c++11
LDFLAGS+= -L/home/disk1/data/s_software/libtorch_92/libtorch/lib -ltorch -lc10 -lc10_cuda -lcudart -lgomp /home/disk1/data/s_software/libtorch_92/libtorch/lib/libnvToolsExt.so


ifeq ($(DEBUG), 1) 
OPTS=-O0 -g
endif

CFLAGS+=$(OPTS)


COMMON+= -DGPU -I/usr/local/cuda/include/

ifeq ($(CUDNN), 1) 
COMMON+= -DCUDNN 
CFLAGS+= -DCUDNN
LDFLAGS+= -lcudnn
endif

OBJ=mytest.o 

ifeq ($(GPU), 1) 
LDFLAGS+= -lstdc++ 
OBJ+=
endif

OBJS = $(addprefix $(OBJDIR), $(OBJ))
DEPS = $(wildcard */*.h) Makefile 

all: obj $(EXEC)
#all: obj  results $(SLIB) $(ALIB) $(EXEC)


$(EXEC): $(OBJS) 
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(ALIB)

$(OBJDIR)%.o: %.cpp $(DEPS)
	$(CPP) $(COMMON) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: %.cu $(DEPS)
	$(NVCC) $(ARCH) $(COMMON) --compiler-options "$(CFLAGS)" -c $< -o $@

obj:
	mkdir -p obj

.PHONY: clean

clean:
	rm -rf $(OBJS) $(EXEC) $(EXECOBJ) $(OBJDIR)/*
