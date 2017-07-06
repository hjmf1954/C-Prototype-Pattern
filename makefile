###############################################################################
# Makefile - HJM Frielink - 2009  - Be aware: UNIX makefiles uses TABS    -- ##
# Version information                                                     -- ##
# Version: 1.0.1.0 - 15 Mar 2009 - Introduction                           -- ##
# 1.0.1.1 - 19 Oct 2011 - iMac Version                                    -- ##
# 1.0.2.1 - 11 Oct 2015 - Added Comment and Doxygen                       -- ##
# 1.0.2.2 - 12 Oct 2015 - Added more rules and simplifications            -- ##
# 1.0.2.3 - 30 Oct 2015 - Implementation for stack                        -- ##
# 1.0.2.4 - 04 Jul 2017 - Implemenatation for Prototype pattern           -- ##
###############################################################################

# Just a snippet to stop executing under other make(1) commands
# that won't understand these lines
ifneq (,)
This makefile requires GNU Make.
endif

# The Makefile Settings for the compiler
CC = g++
CFLAGS = -g -O2
LDFLAGS =
LIBS =
OBJ_DIR = obj
TODAY= ` date +"%Y-%m-%d  %H:%M" `

## ===========================================================================
## Functions
define echo-hashline
	@echo "\n## #####################################################################"
endef

define echo-minus
	@echo "\n## ---------------------------------------------------------------------"
endef

define echo-equals
	@echo "\n## ====================================================================="
endef

# param $1 Methode-task-name
# param $2 Label
# param $3 Value
define echo-m
	$(call echo-minus)
	$(shell printf "\n## [%-12.12s] - %-12s: %s" $1 $2 $3)
endef

# The MakeFile Settings for the Application.
INCS =
OBJS = $(OBJ_DIR)/PrototypeDemo.o
EXEC = PrototypeDemo
DOXY = Doxyfile

# Common search path
vpath %.h ./headers

.PHONY: clean init

# Task All - the default task
all: init clean $(OBJS) $(EXEC) run doxygen

# Makefile Rules for Executables and objects (Implicit rule).
$(EXEC): $(OBJS)
	$(call echo-m, "Link", "Create", $(EXEC))
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $(EXEC)

# Makefile Build rule for file ending on .c (Pattern rule)
$(OBJ_DIR)/%.o : %.c
	$(call echo-m, "obj-c", "Compile", "$<")
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# Makefile Build rule for files ending on cpp (Pattern rule).
$(OBJ_DIR)/%.o : %.cpp
	$(call echo-m, "obj-cpp", "Compile", "$<")
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# Task Clean
clean: init
	$(call echo-m, "clean", "remove", "$(OBJ_DIR) $(EXEC)")
	@rm -f $(OBJS) $(EXEC)
	@rm -f $(OBJ_DIR)/*.o
	@touch -f $(DOXY)

# Init task
init: first
	$(call echo-m, "init", "mkdir", $(OBJ_DIR))
	@mkdir -p $(OBJ_DIR)

first:
	clear
	$(call echo-hashline)
	$(call echo-m, "first", "RunDate", $(TODAY))

# Task Compile
compile: clean $(OBJS)

# Task Run
run:  init $(OBJS) $(EXEC)
	$(call echo-m, run, "Exec", $(EXEC))
	./$(EXEC)

# Task Doxygen
doxygen: $(DOXY) PrototypeDemo.cpp
	@echo "[doxygen] - "
	doxygen $(DOXY)

# Versioning with Subversion performing the Update and the Commit.
# Please note the add function is not implemented.
svn: first
	$(call echo-m,"svn","action","up")
	@svn up
	$(call echo-m,"svn","action","commit")
	@svn ci -m "daily update"

# Shows the usage options for this makefile
help: usage

# Shows the usage options for this makefile
show: usage

# Shows the usage options for this makefile
usage:
	clear
	@echo "\nThis is a short usage snippet."
	@echo "\nThe following rules and targets are defined for this makefile:"
	@echo "\tall\t\tDefault task, running all targets."
	@echo "\tclean\t\tCleans the inter-results and touches all app-module-files."
	@echo "\compile\t\tCompiles the app-modules after cleaning (See clean)."
	@echo "\tdoxygen\t\tCreates the HTML Doxygen reports."
	@echo "\tinit\t\tInitialize the build by creating the directories".
	@echo "\trun\t\tRuns the build executable."
	@echo

# Makefile Individual dependencies for the Classes and C++ files.
$(OBJS)              		:  $(INCS) makefile
$(OBJ_DIR)/PrototypeDemo.o :  PrototypeDemo.cpp
