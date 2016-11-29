# Makefile author: Joseph Anderson <jtanderson@ratiocaeli.com> 
# This is where you specify the necessary source files 
# Program packages and files 
# - The packages should be the path inside your src directory. eg: package1 package2/package3 
PACKAGES = Puzzle PuzzleSolver
# Java compiler 
JAVAC = javac 
#JVM = 1.8 
# Directory for compiled binaries 
# - trailing slash is important! 
BIN = ./bin/
# Directory of source files 
# - trailing slash is important! 
SRC = ./src/
# Java compiler flags 
#JAVAFLAGS = -g -d $(BIN) -cp $(SRC) -target $(JVM) 
JAVAFLAGS = -g -d $(BIN) -cp $(SRC)

# Creating a .class file 
COMPILE = $(JAVAC) $(JAVAFLAGS) 
EMPTY:=

# $(subst $(a), $(b), $(str)) - sostituisce a str tutte le occorrenze di a con b
JAVA_FILES = $(subst $(SRC), $(EMPTY), $(wildcard $(SRC)*.java))

#$(warning $(JAVA_FILES))

ifdef PACKAGES 
	PACKAGEDIRS = $(addprefix $(SRC), $(PACKAGES)) 
	PACKAGEFILES = $(subst $(SRC), $(EMPTY), $(foreach DIR, $(PACKAGEDIRS), $(wildcard $(DIR)/*.java))) 
	ALL_FILES = $(PACKAGEFILES) $(JAVA_FILES) 
else 
	ALL_FILES = $(wildcard $(SRC).java) 
	ALL_FILES = $(JAVA_FILES) 
endif 
# One of these should be the "main" class listed in Runfile 
# ALL_FILES contiene tutti elementi del tipo Package/File.java
#$(warning $(ALL_FILES))


CLASS_FILES = $(subst $(SRC), $(BIN), $(ALL_FILES:.java=.class)) 
CLASS_FILES = $(ALL_FILES:.java=.class)


# CLASS_FILES contiene tutti elementi del tipo Package/File.class
#$(warning $(CLASS_FILES))

#$(warning -------------)
#$(warning $(addprefix $(BIN), $(CLASS_FILES)))

#$(warning $(addprefix $(SRC), $(ALL_FILES)))

# The first target is the one that is executed when you invoke 
# "make". 
all: $(addprefix $(BIN), $(CLASS_FILES)) 
$(BIN)%.class: $(SRC)%.java 
	$(COMPILE) $< 

$(warning per eseguire spostarsi nella directory bin ed eseguire java PuzzleSolver.PuzzleSolver )

clean : 
	rm -rf $(BIN)* 