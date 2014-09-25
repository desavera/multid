include $(WAVEDIR)/make/defs

MULTIDDIR = .

#DEBUGFLAG =
#DEBUGFLAG = -g3
DEBUGFLAG = -O3 -ffast-math -DERROR_CHECKING

CPPFLAGS = $(MULTIDINC) $(GRAPHINC) $(GUIINC) $(WUTILINC)
PRINTSRC += multid.doc BUGS TODO
TARSRC += multid.doc BUGS TODO

LIBSRC = Space.cc Map.cc CompositeMap.cc \
	GeomObj.cc GeomObjList.cc Attributes.cc \
	Bond.cc BoundingBox.cc MultiPoint.cc \
	Point.cc Arrow.cc \
	Polygon.cc MultiPolygon.cc \
	Polyline.cc MultiPolyline.cc \
	Scene.cc View2d.cc View3d.cc \
	SourceScene.cc Pairing.cc \
	TargetViewList.cc TargetView.cc TargetView2d.cc TargetView3d.cc \
	Plot2d.cc Plot3d.cc Proj2dMap.cc Proj3dMap.cc \
	SliderView.cc

LIBOBJ = $(LIBSRC:%.cc=%.o)
LIBARC = $(OBJDIR)/libmultid.a
DEPENDOBJ = $(LIBSRC:%.cc=$(OBJDIR)/%.d)

all: $(LIBARC)

ifneq ($(RPHOSTTYPE),mingw32)
$(LIBARC): $(LIBARC)($(LIBOBJ))
else
$(LIBARC): $(LIBOBJ)
	ar -ruv $(LIBARC) $(LIBOBJ)
endif
	$(RANLIB) $(LIBARC)

.PRECIOUS: $(LIBARC)

include $(WAVEDIR)/make/rules
ifneq ($(RPHOSTTYPE),mingw32)
-include $(DEPENDOBJ)
endif
