

SRCDIR=./src

CXX = g++

CCFILES += \
	$(SRCDIR)/IVisual.c 

HFILES +=  \
	$(SRCDIR)/IVisual.h

LD_FLAGS   =
LD_LIBS    =

OBJS       += $(patsubst %.c,$(SRCDIR)/%.c.o,$(notdir $(CCFILES)))   #(1) rm $(CCFILES) dir info (2) add .o

CFLAGS     = -shared -fPIC -g -O2 -m64 -msse -msse2 -Wall  -fno-access-control \
	                           -DHAVE_POSIX_MEMALIGN -Wno-sign-compare -Wno-unused-local-typedefs -Winit-self \
                                   -DHAVE_EXECINFO_H=1 -rdynamic -DHAVE_CXXABI_H  \
                                   -Wno-unused-result -Wno-unused-variable -fpermissive


#EXECUTABLE = feat2image
OUTPUT      =  shared
SHARED      =  libvisual.so

all: desc $(OBJS) $(CCFILES)
	$(CXX) -o $(SHARED) $(CFLAGS) $(OBJS) $(LD_FLAGS) 
	@rm -rf $(OUTPUT)
	@mkdir -p $(OUTPUT)
	@mv $(SHARED) $(OUTPUT)
	mkdir -p $(OUTPUT)/include
	cp $(SRCDIR)/IVisual.h $(OUTPUT)/include
desc:
	@echo "-------------------desc---------------------------"
	@echo "OBJS => "$(OBJS) 
	@echo "-----------------end desc-------------------------"

$(OBJS): $(CCFILES) $(HFILES)
	$(CXX) $(CFLAGS) -I$(SRCDIR) -o $@ -c $*

clean:
	@rm -f $(OBJS) $(SHARED)
	@rm -rf $(OUTPUT)
