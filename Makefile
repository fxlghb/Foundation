############################################################################
#
# Top Makefile
#
# (c) Copyright 2019-2029
#
############################################################################

TOPDIR  = $(shell pwd)


#//1. 路径搜索
#//1.1 特殊变量VPATH(make在当前目录找不到时，到其指定的目录寻找)
#//1.2 关键字vapth（示例：vpath %.h ../headers）
#//1.3 "-I"或"--include-dir"参数，那么make就会在这个参数所指定的目录下去寻找
VPATH  = $(TOPDIR)
VPATH += $(TOPDIR)/include


#//2. 目标文件
#//2.1 内嵌函数：1. wildcard 获取匹配模式文件名
#//              2. patsubst 模式替换函数(语法：$(patsubst PATTERN,REPLACEMENT,TEXT))
#//              3. foreach  循环(语法：$(foreach VAR,LIST,TEXT))
FODIRS := $(abspath .soln)
FODIRS += $(abspath $(shell find .git/ -maxdepth 2 -type d))
DIRS = $(abspath $(shell find . -maxdepth 3 -type d))
DIRS := $(filter-out $(FODIRS), $(DIRS))
SRSC := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))
OBJS := $(patsubst %.cpp, %.o, $(SRSC))

#//3. 编译链接
CROSS = 
CC = $(CROSS)gcc  
CXX = $(CROSS)g++
RM = rm -rf
DEBUG = -g -O2
VERSION = 1.0.0.0  
TARGET = Foundation.$(VERSION)  

#编译选项
CFLAGS := -c

.PHONY: all target install uninstall clean distclean
$(TARGET) : $(OBJS)
	$(CXX) $^ -o $@ -lpthread
  
$(OBJS):%.o : %.cpp
	$(CXX) $(CFLAGS) $< -o $@
  
clean:
	$(RM) $(TARGET) $(OBJS) 





















