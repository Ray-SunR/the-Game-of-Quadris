OBJDIR=obj
SRCDIR=src
BINDIR=bin
TSTDIR=test
INCDIR=lib
INCLUDE=-I${INCDIR}    
CXX=g++
CXXFLAGS=-I${INCDIR} -g -Wall -c
SOURCES=${wildcard ${SRCDIR}/*.cpp}
OBJECTS=${patsubst ${SRCDIR}/%.cpp, ${OBJDIR}/%.o,${SOURCES}}
EXEC=quadris

$(EXEC) : $(OBJECTS)
	$(CXX) -g -lX11 $(INCLUDE) $(OBJDIR)/*.o -o $(EXEC)

${OBJDIR}/%.o : $(addprefix $(SRCDIR)/, %.cpp)
	$(CXX) ${CXXFLAGS} $< -o $@

.PHONY : clean
clean:
	rm -f $(OBJDIR)/*.o  $(BINDIR)/* $(EXEC) > /dev/null  2>&1
