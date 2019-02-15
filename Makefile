############################################################################
#
# Top Makefile
#
# (c) Copyright 2019-2029
#
############################################################################

TARGET := test
 
CC := g++ 
 
#ע��ÿ�к��治Ҫ�пո񣬷�����㵽Ŀ¼�����棬��������
SRC_DIR = ./
BUILD_DIR = tmp
OBJ_DIR = $(BUILD_DIR)/obj
DEPS_DIR  = $(BUILD_DIR)/deps
 
#�����������ͷ�ļ�·��
INC_DIR = \
	-I./include \
	
#������ӱ������
CC_FLAGS := $(INC_DIR) -g -std=c++11
LNK_FLAGS := \
	-L/usr/local/lib 
 
#����ݹ����3����Ŀ¼
DIRS := $(shell find $(SRC_DIR) -maxdepth 3 -type d)
 
#��ÿ����Ŀ¼��ӵ�����·��
VPATH = $(DIRS)
 
#����src_dir���������Ŀ¼������cpp�ļ�
SOURCES   = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))  
OBJS   = $(addprefix $(OBJ_DIR)/,$(patsubst %.cpp,%.o,$(notdir $(SOURCES))))  
DEPS  = $(addprefix $(DEPS_DIR)/, $(patsubst %.cpp,%.d,$(notdir $(SOURCES))))  
$(TARGET):$(OBJS)
	@$(CC) $^ $(LNK_FLAGS) -o $@ -lpthread
	
#����֮ǰҪ����OBJĿ¼��ȷ��Ŀ¼����
$(OBJ_DIR)/%.o:%.cpp
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi;
	$(CC) -c $(CC_FLAGS) -o $@ $<

	
#����֮ǰҪ����DEPSĿ¼��ȷ��Ŀ¼����
#ǰ���@��ʾ���������ִ�д�ӡ
$(DEPS_DIR)/%.d:%.cpp
	@if [ ! -d $(DEPS_DIR) ]; then mkdir -p $(DEPS_DIR); fi;\
	set -e; rm -f $@;\
	$(CC) -MM $(CC_FLAGS) $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,$(OBJ_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f $@.$$$$
#ǰ���-��ʾ���Դ���
-include $(DEPS)


.PHONY : clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)




