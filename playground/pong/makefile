# 头文件文件夹
INCDIR := include
# 源代码文件夹
SRCDIR := src
# 编译输出文件夹
BUILDDIR := build
# 可执行文件名
TARGET := game

# 编译器
CXX := g++
# 编译器选项
CXXFLAGS := -std=c++11 -Wall -Wextra -O2 -I$(INCDIR)
# 链接器选项
LDFLAGS := -L/usr/local/Cellar/sdl2/2.28.1/lib
# 需要链接的库
LDLIBS := -lSDL2-2.0.0

# 所有源文件
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
# 所有对象文件
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
# 所有依赖文件
DEPS := $(OBJECTS:.o=.d)

# 默认目标
all: $(TARGET)

# 链接可执行文件
$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	@mkdir -p $(@D)
	$(CXX) $^ -o $(TARGET) $(LDFLAGS) $(LDLIBS)

# 编译源文件为对象文件
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "Compiling $<..."
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -MMD -MP $< -o $@

# 包含所有依赖文件
-include $(DEPS)

# 清理编译生成的文件
clean:
	@echo "Cleaning..."
	$(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean
