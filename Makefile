############################################################################
#
# Top Makefile
#
# (c) Copyright 2019-2029
#
############################################################################

TOPDIR  = $(shell pwd)


#//1. ·������
#//1.1 �������VPATH(make�ڵ�ǰĿ¼�Ҳ���ʱ������ָ����Ŀ¼Ѱ��)
#//1.2 �ؼ���vapth��ʾ����vpath %.h ../headers��
#//1.3 "-I"��"--include-dir"��������ômake�ͻ������������ָ����Ŀ¼��ȥѰ��
VPATH  = $(TOPDIR)
VPATH += $(TOPDIR)/include


#//2. Ŀ���ļ�
#//2.1 ��Ƕ������1. wildcard ��ȡƥ��ģʽ�ļ���
#//              2. patsubst ģʽ�滻����(�﷨��$(patsubst PATTERN,REPLACEMENT,TEXT))
#//              3. foreach  ѭ��(�﷨��$(foreach VAR,LIST,TEXT))
FODIRS := $(abspath .soln)
FODIRS += $(abspath $(shell find .git/ -maxdepth 2 -type d))
DIRS = $(abspath $(shell find . -maxdepth 3 -type d))
DIRS := $(filter-out $(FODIRS), $(DIRS))
SRSC := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))
OBJS := $(patsubst %.cpp, %.o, $(SRSC))

#//3. ��������
CROSS = 
CC = $(CROSS)gcc  
CXX = $(CROSS)g++
RM = rm -rf
DEBUG = -g -O2
VERSION = 1.0.0.0  
TARGET = Foundation.$(VERSION)  

#����ѡ��
CFLAGS := -c

.PHONY: all target install uninstall clean distclean
$(TARGET) : $(OBJS)
	$(CXX) $^ -o $@ -lpthread
  
$(OBJS):%.o : %.cpp
	$(CXX) $(CFLAGS) $< -o $@
  
clean:
	$(RM) $(TARGET) $(OBJS) 





















