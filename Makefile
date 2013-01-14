# Basic makefile for creating the static library
# Extended from https://github.com/AleksMK/AVR-Makefile
# /TODO Extend to create for multiple arches

# make all = Make software
# make clean = Clean out built project files.
# make archive = Creates the static library
# make filename.s = Just compile filename.c into the assembler code only
# To rebuild project do "make clean" then "make all".

# Microcontroller Type
MCU=atmega328

# Target file name (without extension).
TARGET = libmicro-avr
TARGETDIR = /usr/local/

############# Don't need to change below here for most purposes (Elliot)

# Optimization level, can be [0, 1, 2, 3, s]. 0 turns off optimization.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

# List C source files here. (C dependencies are automatically generated.)
SRC = 

# List Assembler source files here.
# Make them always end in a capital .S. Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
ASRC =


# List any extra directories to look for include files here.
# Each directory must be seperated by a space.
EXTRAINCDIRS = ./include


# Optional compiler flags.
# -g: generate debugging information (for GDB, or for COFF conversion)
# -O*: optimization level
# -f...: tuning, see gcc manual and avr-libc documentation
# -Wall...: warning level
# -Wa,...: tell GCC to pass this to the assembler.
# -ahlms: create assembler listing
CFLAGS = -g -O$(OPT) \
-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
-Wall -Wstrict-prototypes \
-Wa,-adhlns=$(<:.c=.lst) \
$(patsubst %,-I%,$(EXTRAINCDIRS))


# Set a "language standard" compiler flag.
# Unremark just one line below to set the language standard to use.
# gnu99 = C99 + GNU extensions. See GCC manual for more information.
#CFLAGS += -std=c89
#CFLAGS += -std=gnu89
#CFLAGS += -std=c99
CFLAGS += -std=gnu99



# Optional assembler flags.
# -Wa,...: tell GCC to pass this to the assembler.
# -ahlms: create listing
# -gstabs: have the assembler create line number information; note that
# for use in COFF files, additional information about filenames
# and function names needs to be present in the assembler source
# files -- see avr-libc docs [FIXME: not yet described there]
ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs


# Define programs and commands.
SHELL = bash
CC = /usr/local/avr/bin/avr-gcc
AR = /usr/local/avr/bin/avr-ar

REMOVE = rm -f
COPY = cp -f

# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = -------- end --------
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_ARCHIVING = Creating Archive:
MSG_INSTALLING = Installing:
MSG_CLEANING = Cleaning project:


# Define all object files.
OBJ = $(SRC:.c=.o) $(ASRC:.S=.o)

# Define all listing files.
LST = $(ASRC:.S=.lst) $(SRC:.c=.lst)

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)
ALL_AR = rcs


# Default target: make program!
all: begin archive finish end


# Display compiler version information.
gccversion :
	@echo $(CC) --version


# Compile: create object files from C source files.
%.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(ALL_CFLAGS) $< -o $@


# Compile: create assembler files from C source files.
%.s : %.c
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
%.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(ALL_ASFLAGS) $< -o $@

# Archive: Generate the archive from the object files
archive: $(OBJ)
	@echo
	@echo $(MSG_ARCHIVING) $<
	$(AR) $(ALL_AR) lib/$(TARGET).a $(OBJ)

# Install the static library and the include files
install : archive
	@echo
	@echo $(MSG_INSTALLING) $<
	$(COPY) lib/*.a $(TARGETDIR)lib
	mkdir -p $(TARGETDIR)include/libmicro-avr/
	$(COPY) include/*.h $(TARGETDIR)include/libmicro-avr/

# Target: clean project.
clean: begin clean_list finish end

clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).eep
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).cof
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).a90
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lnk
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(TARGET).a
	$(REMOVE) $(OBJ)
	$(REMOVE) $(LST)
	$(REMOVE) $(SRC:.c=.s)
	$(REMOVE) $(SRC:.c=.d)
	$(REMOVE) *~

# Automatically generate C source code dependencies.
# (Code originally taken from the GNU make user manual and modified
# (See README.txt Credits).)
#
# Note that this will work with sh (bash) and sed that is shipped with WinAVR
# (see the SHELL variable defined above).
# This may not work with other shells or other seds.
#
%.d: %.c
	set -e; $(CC) -MM $(ALL_CFLAGS) $< \
	| sed 's,\(.*\)\.o[ :]*,\1.o \1.d : ,g' > $@; \
	[ -s $@ ] || rm -f $@

	
	# Remove the '-' if you want to see the dependency files generated.
	-include $(SRC:.c=.d)



# Listing of phony targets.
.PHONY : all begin finish end sizebefore sizeafter gccversion coff extcoff \
clean clean_list program


