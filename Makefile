# Directories and files
ROOT_DIR:=.
BUILD_DIR:=${ROOT_DIR}/build
BUILD_BIN_DIR:=${BUILD_DIR}/bin
BUILD_ART_DIR:=${BUILD_DIR}/artifacts
BUILD_RESULT:=${BUILD_BIN_DIR}/Mandelbrot

# Install parameters
INSTALL_ADDRESS:=10.43.0.1
INSTALL_USER:=student
INSTALL_PASSWORD:=student

# Compiler subflags
SYSROOT:=../../sysroot
TARGET:=arm-linux-gnueabihf

# Libraries
LIBRARIES:=../../libpynq
LIBRARIES_ARCHIVE_FILES:=$(foreach library,$(LIBRARIES),$(wildcard $(library)/lib/*.a))
LIBRARIES_INCLUDE_FLAGS:=$(foreach library,$(LIBRARIES),-I$(library)/include)

# Compiler and Linker flags
CFLAGS:=--sysroot=${SYSROOT} --target=${TARGET} ${LIBRARIES_INCLUDE_FLAGS}
LDFLAGS:=--sysroot=${SYSROOT} --target=${TARGET} -fuse-ld=lld -lm -O0 -g3 -ggdb

# File dependencies
SOURCES:=$(wildcard src/*.c)
OBJECTS:=$(SOURCES:.c=.o)
ARTIFACTS:=$(foreach obj,$(OBJECTS),${BUILD_ART_DIR}/$(notdir $(obj)))

# Rules
all: make_directories ${BUILD_RESULT}

${BUILD_RESULT}: ${ARTIFACTS}
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) $(LIBRARIES_ARCHIVE_FILES) -o $@ -v

${BUILD_ART_DIR}/%.o: src/%.c
	$(CC) -c -o $@ $^ ${CFLAGS}

install:
	if ! [ -x "$$(command -v sshpass)" ]; \
	then \
		echo "sshpass is not installed. Install with brew install sshpass" && \
		exit 1; \
	else \
		sshpass -p $(INSTALL_PASSWORD) scp $(BUILD_RESULT) $(INSTALL_USER)@$(INSTALL_ADDRESS):./$(notdir $(BUILD_RESULT)); \
	fi

make_directories:
	mkdir -p ${BUILD_BIN_DIR}
	mkdir -p ${BUILD_ART_DIR}

clean:
	rm -rf $(BUILD_BIN_DIR)
	rm -rf $(BUILD_ART_DIR)