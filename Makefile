CXX = c++

OBJDIR = obj
SRCDIR = src
INCDIR = inc

OUTFILE = chip8

OBJS = $(addsuffix .o, $(addprefix $(OBJDIR)/, \
	  main video \
	  ) )

WARN = -Wall -Wextra -pedantic
CPPFLAGS = -std=c++14 -I$(INCDIR) -c -g $(WARN)
LDFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all:	$(OUTFILE)


$(OUTFILE):	$(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o:	$(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $< -o $@

clean:	
	@rm -f $(OBJS) $(EXE)
