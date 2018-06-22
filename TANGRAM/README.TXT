The Tangram Program
--- ------- -------

Please see Chapter 13 for a description of this program as well as
instructions for running it.


Installing Tangram
---------- -------

The Tangram program consists of these files:
     Tangram.exe
     Canvas.dll
     Canvas_C.tlb
     GdiWrld.dll
     GLWrld.dll
     Model.dll
     Model.exe
     Model_C.tlb
     Proxy.dll
     World_C.tlb
On Windows 95, parts of the program require these OpenGL files:
     GLU32.dll
     OpenGL32.dll
To register the components you can use this file:
     Register.bat

1. If desired, copy the necessary files to a folder on your hard
   drive.  (The main Setup program for this companion CD copies them
   to a folder whose default name is \InsideCOM\Tangram.)  You don't
   have to copy over the \Source subfolder, which contains the source
   code.

2. Run Register.bat to register the various components.  This file
   uses the program Regsvr32.exe.  If you don't already have a copy of
   Regsvr32.exe on your system, you can find a copy in the \Comp_Cat
   folder on this companion CD.

3. Double click the icon for Tangram.exe to run the program.


Building Tangram
-------- -------

All of the source code is contained in the \Source subfolder.  The
files are set up to be compiled with Microsoft Visual C++ 5.0.

1. To compile, Tangram requires
   * the Microsoft Foundation Class Library (MFC),
   * the Standard Template Library (STL), and
   * the OpenGL Library.
   The first two come with Microsoft Visual C++ 5.0.  A copy of the
   OpenGL Library may be found in the \OpenGL95 folder on this
   companion CD.

2. The following directories must be on the include path for Tangram
   to compile:
	Tangram\Common
	Tangram\Idl
	Tangram\Share

3. Instead of having each component build all the IDL files it uses,
   each IDL file is built only once.  The other components then share
   the resulting files. This implies a required order to build the
   components in. It is best to build the components in the following
   order:
	Canvas
	Model
	GdiWorld
	GLWorld 
	Tangram
   The real requirement is that Model be built before GdiWorld/GLWorld.


Have fun!
