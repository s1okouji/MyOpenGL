WORKDIR=G:\\git\\MyOpenGL
ENV=Debug
BUILDDIR=$(WORKDIR)\\build\\
INCLUDE=$(INCLUDE);$(WORKDIR)\\include

all:
	cl /Fo"$(BUILDDIR)$(ENV)\\" /I"$(INCLUDE)" /EHsc /c src/main.cpp 
	LINK /LIBPATH:"G:\git\MyOpenGL\libs\lib\Release\x64" /LIBPATH:"G:\git\MyOpenGL\libs\lib-vc2022" /OUT:"$(BUILDDIR)$(ENV)\main.exe" glew32.lib glfw3dll.lib opengl32.lib "$(BUILDDIR)$(ENV)\main.obj"