CXX=clang++
CPPFLAGS=-g -std=c++11
LDFLAGS=-g
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system

SRCS=level_view.cpp ToolUtils.cpp BlobboGame.cpp TUIFrontend.cpp SFMLFrontend.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: level_view

level_view: $(OBJS)
	$(CXX) $(LDFLAGS) -o level_view $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS) level_view

dist-clean: clean
	$(RM) *~ .dependtool

include .depend
