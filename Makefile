# Compile and linking options
# Enable -pg for profiling
INCLUDE =

NORMALPARAMS = -O3
DEBUGPARAMS = -g -Wall
LINKPARAMS =
NAME = datastructs

#####################################################################################
GCC = gcc
SOURCES = main.c array_list.c test_array_list.c
				  
# Dependencies (recompile if they change)
DEPS = array_list.h array_list_p.h test_array_list.h

# Normal object-files, and their directory
ODIR = objs
OBJS = $(SOURCES:%.c=$(ODIR)/%.o)

# Debug object-files, and their directory
DBGODIR = dbgobjs
DBGOBJS = $(SOURCES:%.c=$(DBGODIR)/%.o)

############# Normal ('make') compile case ##################

$(ODIR)/%.o : %.c $(DEPS)
	$(GCC) $(NORMALPARAMS) $(INCLUDE) -c $<  -o $@

normal: $(ODIR) $(OBJS)
	@ $(GCC) $(OBJS) -o $(NAME) $(LINKPARAMS)

$(ODIR):
	mkdir $(ODIR)

############# Debugging ('make dbg') compile case ###########
$(DBGODIR)/%.o : %.c $(DEPS)
	$(GCC) $(DEBUGPARAMS) $(INCLUDE) -c $<  -o $@

dbg: $(DBGODIR) $(DBGOBJS)
	@ $(GCC) $(DBGOBJS) -o $(NAME) $(LINKPARAMS)

$(DBGODIR):
	mkdir $(DBGODIR)

############# Cleanup ('make clean') command ################
.PHONY: clean
clean:
	rm -f $(ODIR)/*
	rm -f $(DBGODIR)/*
