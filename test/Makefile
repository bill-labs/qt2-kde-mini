# Test Makefile for qt2-kde-mini

QTDIR ?= /opt/qt2
MOC = $(QTDIR)/bin/moc

CXX = g++
CXXFLAGS = -O2 -Wall -D_UNIXWARE -I$(QTDIR)/include -I../include
LDFLAGS = -L$(QTDIR)/lib -L.. -lqt -lqt2kdemini

TARGET = test-basic

SOURCES = test-basic.cpp
MOC_SOURCES = test-basic.moc
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.moc: %.cpp
	$(MOC) $< -o $@

test-basic.o: test-basic.moc

clean:
	rm -f $(OBJECTS) $(MOC_SOURCES) $(TARGET)

.PHONY: all clean
