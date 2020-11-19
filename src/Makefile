.PHONY: all debug release objects_debug object_rel clean

OBJDIR := obj
OBJDIR_REL := $(OBJDIR)/Release
OBJDIR_DEBUG := $(OBJDIR)/Debug
OUTDIR := ../bin/

C_FLAGS := -std=c17 -O3
C_FLAGS_D := -std=c17 -O0 -ggdb3 -g -D DEBUG
L_FLAGS := -std=c17 -lSDL2 -lSDL2_image
L_FLAGS_D := -std=c17 -lSDL2 -lSDL2_image
SRC := $(wildcard io/*.c) $(wildcard config/*.c) $(wildcard vendor/*.c) $(wildcard *.c)
OBJS_DEBUG := $(addprefix $(OBJDIR_DEBUG)/,$(SRC:.c=.o))
OBJS_REL := $(addprefix $(OBJDIR_REL)/,$(SRC:.c=.o))

$(OBJDIR_DEBUG)/%.o : %.c
	gcc -c $(C_FLAGS_D) $(OUTPUT_OPTION) $<
$(OBJDIR_REL)/%.o : %.c
	gcc -c $(C_FLAGS) $(OUTPUT_OPTION) $<

debug: objects_debug
	gcc ${C_FLAGS_D} $(L_FLAGS_D) -D DEBUG $(wildcard $(OBJDIR)/Debug/*/*.o) $(wildcard $(OBJDIR)/Debug/*.o) -o $(OUTDIR)Debug/moosecasa-keypad

release: objects_rel
	gcc ${C_FLAGS} $(L_FLAGS) -g $(wildcard $(OBJDIR)/Release/*/*.o) $(wildcard $(OBJDIR)/Release/*.o) -o $(OUTDIR)Release/moosecasa-keypad

all: debug release

clean:
	rm -rf $(OBJDIR)
	rm $(OUTDIR)/Debug/moosecasa-keypad
	rm $(OUTDIR)/Release/moosecasa-keypad

objects_rel: $(OBJS_REL)
	
objects_debug: $(OBJS_DEBUG)

$(OBJS_DEBUG): | $(OBJDIR) $(OBJDIR_DEBUG)

$(OBJS_REL): | $(OBJDIR) $(OBJDIR_REL)

$(OBJS): | $(OBJDIR) $(OBJDIR_DEBUG) $(OBJDIR_REL)

$(OBJDIR):
	mkdir -p $(OBJDIR)	

$(OBJDIR_DEBUG):
	mkdir -p $(OBJDIR_DEBUG)
	mkdir -p ${OBJDIR_DEBUG}/io
	mkdir -p ${OBJDIR_DEBUG}/config
	mkdir -p ${OBJDIR_DEBUG}/vendor

$(OBJDIR_REL):
	mkdir -p $(OBJDIR_REL)
	mkdir -p $(OBJDIR_REL)/io
	mkdir -p $(OBJDIR_REL)/config
	mkdir -p $(OBJDIR_REL)/vendor

