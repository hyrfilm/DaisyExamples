# Project Name
TARGET = main

# Source files
CPP_SOURCES = $(wildcard *.cpp)

DSP_LIB = ./DSP.a

# Library Locations
LIBDAISY_DIR = ../..

# Path to the DSP library
DSP_LIB = ./DSP.a

# Core location, and generic Makefile
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile


# Linker flags
LDFLAGS += -L DSP.a

# Ensure the build directory exists
$(shell mkdir -p build)

# Linking target
$(TARGET): $(OBJS) $(DSP_LIB)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to build object files
build/%.o: %.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Clean rule to remove generated files
clean:
	rm -f build/*.o build/*.d $(TARGET)
