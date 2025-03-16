CC        = gcc
CFLAGS    = -Wall -Werror -std=c99
CPPFLAGS  = -Isrc/core/include
LDFLAGS   = -L$(LIB_DIR) -Wl,-rpath,$(abspath $(LIB_DIR))

BUILD_DIR = build
BIN_DIR   = $(BUILD_DIR)/bin
LIB_DIR   = $(BUILD_DIR)/lib
OBJ_DIR   = $(BUILD_DIR)/obj

SRC_DIR   = src
CORE_DIR  = $(SRC_DIR)/core
BOOKS_DIR = $(SRC_DIR)/books
KR_DIR    = $(BOOKS_DIR)/kr

KR_CHAP_DIRS := $(notdir $(wildcard $(KR_DIR)/*))
KR_CHAP_SRCS := $(foreach chap,$(KR_CHAP_DIRS),$(wildcard $(KR_DIR)/$(chap)/*.c))
KR_CHAP_OBJS := $(foreach f,$(patsubst %.c,%.o,$(notdir $(KR_CHAP_SRCS))),$(OBJ_DIR)/$(f))
KR_CHAP_BINS := $(patsubst $(OBJ_DIR)/ex-%.o,$(BIN_DIR)/kr-%,$(KR_CHAP_OBJS))

CORE_CATS := $(filter-out include,$(notdir $(wildcard $(CORE_DIR)/*)))
CORE_SRCS := $(foreach cat,$(CORE_CATS),$(wildcard $(CORE_DIR)/$(cat)/*.c))
CORE_OBJS := $(foreach f,$(patsubst %.c,%.o,$(notdir $(CORE_SRCS))),$(OBJ_DIR)/$(f))
CORE_LIBS := $(patsubst $(OBJ_DIR)/%.o,$(LIB_DIR)/lib%.so,$(CORE_OBJS))


define get_libs_to_link
$(eval SRC_FILE := $(wildcard $(KR_DIR)/*/ex-$(1).c))\
  $(strip\
    $(if $(SRC_FILE),\
      $(foreach cat,$(CORE_CATS),\
        $(shell grep -q "#include.*kr_$(cat)" $(SRC_FILE) &>/dev/null && echo -lkr_$(cat))
      )))
endef


# Make sure that target build directories exist
$(shell mkdir -p $(BIN_DIR) $(LIB_DIR) $(OBJ_DIR))

all: $(CORE_LIBS) $(KR_CHAP_BINS)

$(LIB_DIR)/lib%.so: $(OBJ_DIR)/%.o
	@echo [LD] $@
	@$(CC) -shared -o $@ $<

$(OBJ_DIR)/%.o: $(CORE_DIR)/*/%.c
	@echo [CC] $@
	@$(CC) $(CFLAGS) $(CPPFLAGS) -fPIC -c -o $@ $<

$(BIN_DIR)/kr-%: $(OBJ_DIR)/ex-%.o
	@echo [LD] $@
	$(CC) $(LDFLAGS) -o $@ $< $(call get_libs_to_link,$*) 

$(OBJ_DIR)/ex-%.o: $(KR_DIR)/*/ex-%.c
	@echo [CC] $@
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean

