#Location and name of your application (i.e. in the bin/ folder, named game.exe
OUT = bin/game.exe

#Compiler (i.e. g++ for C++, or gcc for C)
CC = i586-mingw32msvc-g++

#Directory for includes (headers, etc.)
IDIR = jni

#Directory where the .o files will be placed
ODIR = obj_win

#Directory where the source files are located
SDIR = jni

#Path to includes (this example is on a Windows machine, begin each entry with -I)
LOCAL_C_INCLUDES = $(patsubst %, -I%, $(shell /usr/bin/find $(SDIR) -type d))
INC =  $(LOCAL_C_INCLUDES) -I/usr/i586-mingw32msvc/include/ -I/usr/i586-mingw32msvc/libpng/include -Iinclude

#Path to libs (again, standard setup for MinGW on Windows)
#begin each directory location with -L and each flag with -l
LIBS = -Llib -L/usr/i586-mingw32msvc/lib/ -L/usr/i586-mingw32msvc/libpng/lib -lpng -lmingw32 -lglee -lopengl32 -lglu32 -mwindows -lm -lole32 -lwinmm -lolepro32 -luuid -lz

SRC = $(shell find $(SDIR) -name '*.cpp')
SRC += $(shell find $(SDIR) -name '*.c')

#A list of your expected object files (typically, name one for each source file)
_OBJS = $(patsubst $(SDIR)%, %, $(patsubst %.cpp, %.o, $(SRC)))

OBJ_FOLDERS = $(patsubst $(SDIR)%, $(ODIR)%, $(shell /usr/bin/find $(SDIR) -type d))

#Only change stuff below this line  if you're aware of what you're doing
OBJS = $(patsubst %,$(ODIR)%,$(_OBJS))

CFLAGS := -O0 -g

#$(info Includes:)
#$(info $(INC))
#$(info Sources:)
#$(info $(SRC))
#$(info Objects:)
#$(info $(OBJS))

$(ODIR)/%.o: $(SDIR)/%.c
	mkdir -p $(OBJ_FOLDERS)
	$(CC) -c $(INC) -o $@ $< $(CFLAGS) 

$(ODIR)/%.o: $(SDIR)/%.cpp
	mkdir -p $(OBJ_FOLDERS)
	$(CC) -c $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
#	strip $(OUT)

clean:
	rm -f $(OBJS) $(OUT)

