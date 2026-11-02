# qt2-kde-mini - Minimal KDE compatibility library for Qt2
# Simplified KDE classes for porting KDE2 games to pure Qt2

# Installation paths
PREFIX ?= /opt/gnux
DESTDIR ?=
LIBDIR ?= $(PREFIX)/lib
INCLUDEDIR ?= $(PREFIX)/include/qt2kdemini
DATADIR ?= $(PREFIX)/share/qt2-kde-mini

# Qt2 paths - use QTDIR from environment or default
QTDIR ?= $(PREFIX)/qt2
MOC = $(QTDIR)/bin/moc

# Compiler flags
CXX = g++
CXXFLAGS = -O3 -fomit-frame-pointer -fPIC -Wall -D_UNIXWARE -DPREFIX=\"$(PREFIX)\" -DDATADIR=\"$(DATADIR)\" -I$(QTDIR)/include -Iinclude
LDFLAGS = -shared -L$(QTDIR)/lib -lqt

# Output
TARGET = libqt2kdemini.so.1.0.0
SONAME = libqt2kdemini.so.1
LINK = libqt2kdemini.so

# Source files
SOURCES = src/kglobal.cpp \
          src/kcmdlineargs.cpp \
          src/kapp.cpp \
          src/kconfig.cpp \
          src/kmainwindow.cpp \
          src/kaction.cpp \
          src/kactioncollection.cpp \
          src/kaccel.cpp \
          src/kdialogbase.cpp \
          src/kurllabel.cpp \
          src/knuminput.cpp \
          src/kcolorbtn.cpp \
          src/kstdaction.cpp \
          src/kstdgameaction.cpp \
          src/kseparator.cpp \
          src/khelpmenu.cpp

# Moc files for Q_OBJECT classes
MOC_SOURCES = src/moc_kapp.cpp \
              src/moc_kmainwindow.cpp \
              src/moc_kmenubar.cpp \
              src/moc_ktoolbar.cpp \
              src/moc_kstatusbar.cpp \
              src/moc_kaccel.cpp \
              src/moc_kaction.cpp \
              src/moc_kactioncollection.cpp \
              src/moc_kxmlguifactory.cpp \
              src/moc_kdialogbase.cpp \
              src/moc_kurllabel.cpp \
              src/moc_knuminput.cpp \
              src/moc_kcolorbtn.cpp \
              src/moc_kseparator.cpp \
              src/moc_khelpmenu.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o) $(MOC_SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build shared library
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -Wl,-soname,$(SONAME) -o $@ $(OBJECTS)
	ln -sf $(TARGET) $(SONAME)
	ln -sf $(SONAME) $(LINK)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# MOC generation
src/moc_%.cpp: include/%.h
	$(MOC) $< -o $@

# Clean
clean:
	rm -f $(OBJECTS) $(MOC_SOURCES) $(TARGET) $(SONAME) $(LINK)
	rm -f src/*.o src/moc_*.cpp

# Install (optional)
install: $(TARGET)
	-mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(TARGET) $(DESTDIR)$(LIBDIR)/
	chmod 755 $(DESTDIR)$(LIBDIR)/$(TARGET)
	rm -f $(DESTDIR)$(LIBDIR)/$(SONAME) $(DESTDIR)$(LIBDIR)/$(LINK)
	ln -s $(TARGET) $(DESTDIR)$(LIBDIR)/$(SONAME)
	ln -s $(SONAME) $(DESTDIR)$(LIBDIR)/$(LINK)
	-mkdir -p $(DESTDIR)$(INCLUDEDIR)
	-cp include/*.h $(DESTDIR)$(INCLUDEDIR)/
	-chmod 644 $(DESTDIR)$(INCLUDEDIR)/*.h
	-mkdir -p $(DESTDIR)$(DATADIR)/icons
	-cp icons/*.png $(DESTDIR)$(DATADIR)/icons/
	-chmod 644 $(DESTDIR)$(DATADIR)/icons/*.png

.PHONY: all clean install
