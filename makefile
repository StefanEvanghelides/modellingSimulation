# Metadata
DIR = .
TARGET = $(DIR)/RUN

# Compiler specs
CC = g++
CFLAGS = -Wall -Werror -std=c++2a
RM = rm -f

# Type of project = C++
SOURCES_EXTENSION = cc
OBJECTS_EXTENSION = o
HEADERS_EXTENSION = h

# Sources and headers
IH = main.ih
#SOURCES := $(wildcard $(DIR)/*.$(SOURCES_EXTENSION)) 
SOURCES := $(shell find $(DIR) -name '*.$(SOURCES_EXTENSION)')
HEADERS := $(wildcard $(DIR)/*.$(HEADERS_EXTENSION))
OBJECTS := $(SOURCES:.$(SOURCES_EXTENSION)=.$(OBJECTS_EXTENSION))

# Command line arguments.
# Use: make run ARGS='arg1 arg2 arg3...'
ARGS = $(filter-out $@,$(MAKECMDGOALS))

# Compile sources into objects
%.$(OBJECTS_EXTENSION): %.$(SOURCES_EXTENSION) $(IH) $(HEADERS)
	$(CC) -c $< -o $@ $(CFLAGS)

# Link objects and create executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(CFLAGS)
	$(RM) $(OBJECTS)

# Run the executable (+ command line arguments)
run: $(TARGET)
	$(TARGET) $(ARGS)

# Clean the executable and object files
clean: $(OBJECTS)
	$(RM) $(TARGET) $(OBJECTS)


