TARGET = learn1
OBJDIR := obj
DEPDIR := dep
$(shell mkdir -p $(OBJDIR) >/dev/null)
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

SRCS := $(shell ls *.cpp 2>/dev/null) $(shell ls *.c 2>/dev/null) 

CFLAGS += -std=gnu99
CXXFLAGS += -std=c++11 -I. -O3 -pthread

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

$(TARGET): $(patsubst %.cpp,$(OBJDIR)/%.o,$(wildcard *.cpp)) $(patsubst %.c,$(OBJDIR)/%.o,$(wildcard *.c)) $(OBJDIR)/resource_file.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJDIR)/*.o -lrt -lboost_thread -lboost_system

$(OBJDIR)/%.o : %.c $(DEPDIR)/%.d
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(OBJDIR)/%.o : %.cpp $(DEPDIR)/%.d
	$(COMPILE.cc) $(OUTPUT_OPTION) $<	
	$(POSTCOMPILE)

$(OBJDIR)/resource_file.o:	
	ld -r -b binary -o $(OBJDIR)/resource_file.o resource_file.txt 	
	
$(DEPDIR)/%.d: ;

include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

.PHONY : clean
clean:
	-rm -r $(DEPDIR)	
	-rm -r $(OBJDIR)
	-rm $(TARGET)

	
	