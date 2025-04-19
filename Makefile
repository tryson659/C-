# 定义编译器
CXX = g++

# 编译选项
CXXFLAGS = -Wall -g

# 查找所有.cpp文件并生成.o文件列表
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

# 最终生成的可执行文件名
EXEC = reactor

# 默认规则
all: $(EXEC)

# 生成可执行文件的规则
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 编译.cpp文件为.o文件的规则
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的目标文件和可执行文件
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean