//-------------------------------------------------------------------------
// Readme.txt
//-------------------------------------------------------------------------
// Objvw: A sample that illustrates using IE's Automation and scripting interfaces
// froma contained control
//-------------------------------------------------------------------------
// (C) Copyright 1992-1996 by Microsoft Corporation.  All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//-------------------------------------------------------------------------

PURPOSE
=======
This sample provides the following things:

   - illustrates accessing IE's Automation model and scripting model from within a 
     contained control.  Most of this code is available in wintree.cpp particularily in
     the method EnumerateFrames.

   - illustrates enumerating all controls (and java applets)in a page and sub pages.  
     The code that actually enumerates the controls is in wintree.cpp in the method
     EnumerateControls.

   - Illustrates getting a control's ID or NAME that was specfied in the OBJECT tag

   - illustrates using the ProgressChange event to identify when pages have been 
     completely loaded.  Currently there is no event from IE that indicates "all pages
     that make up this page are loaded".  The alternative that is used here is to sink
     the DWebBrowserEvents::ProgressChange event.  Every time this is passed a -1, a sub 
     page is completely loaded.  The algorithm works by completely building the control
     tree each time this occurs so that the last time it occurs the tree is complete 
     and accurate.

   - provides a generic class to sink events.  This is encapsulated in evtsink.cpp and 
     evtsink.h.  See "SINKING EVENTS" later in this document for more information.

   - Illustrates marking the control "Safe for scripting" and "Safe for Initializing" 
     using component categories.  This is illustrated in the helper files cathelp.cpp, 
     cathelp.h and in the frame work override RegisterData found in objvw.cpp.


FILES SUPPLIED
==============
	PROGRAM FILES
	Appsink.cpp, Appsink.h
	-- Implements the DWebBrowserEvents event sinking used to determine when all
	   the pages are loaded
	Cathelp.cpp, Cathelp.h
	-- Implement registering the OBJVW control as safe for scripting and safe 
	   for initializing so we don't get IE's security dialog
	Dispids.h
	-- Contain dispids for OBJVW's Automation properties, methods and events
	Dwinvers.h
	-- OBJVW version information
	Evtsink.cpp, Evtsink.h 
	-- Base class that implements generic event sinking.  See "SINKING EVENTS" below
	   for a complete description
	Gen.h
	-- Header containing generic definitions
	Guids.cpp
	-- Contains header files that define guids so that INITGUID can be defined in 
	   one place
	Localobj.h
	-- Contains frame work definitions for the objects found in OBJVW.ocx
	Objvw.cpp
	-- Implements non control specific frame work overrides such as DLL 
	   initialization, registration, and licensing
	Objvw.def
	-- Project definition file
	Makefile
	-- SDK command line makefile for project
	Objvw.mak
	-- VC 4.1 make file
	Objvw.mdp
	-- VC 4.1 project workspace file
	Objvw.odl
	-- Object definition language file for OBJVW's Automation methods, properties 
	   and events
	Objvw.rc
	-- Resource file
	Objvwctl.bmp
	-- Bitmap for control
	Objvwctl.cpp Objvwctl.h
	-- Control specific frame work overrides.  The interesting code appears primarily
	   in AfterCreateWindow when the event sink is created and initialized
	Resource.h
	-- Contains resource definitions for the control
	Test.htm, foo.htm, foo1.htm, hlsimple.doc
	-- Sample HTML files with embedded frames for testing
	Treeui.cpp, Treeui.h
	-- Contains actual treeview control code to build visual tree
	Wintree.cpp, Wintree.h
	-- Contains internal tree building code and most of the code required to interact
	   with IE's Automation and scripting model.


BUILDING THE SAMPLE
===================
	- Make sure you have either VC4.1 or VC4.2b for intel platforms, or VC4.0b for
	  RISC platforms (ppc, mips, alpha)

	- Build the basectl framewrk sample.  To do this make sure your include and
          lib paths are set correctly as in the readme.txt file available with the
          ActiveX SDK.  cd to \inetsdk\samples\basectl\framewrk and type "nmake".  This 
          will build the debug library ctlfwd32.lib and place it in 
	  \inetsdk\samples\basectl\lib.  To build the release version type 
	  "nmake BLDTYPE=Retail nodebug=1"; this will generate the library ctlfwr32.lib
	  in the same directory.

	- Use either the supplied command line make file or the supplied VC IDE project
	  file to build and register the control.  


RUNNING THE SAMPLE
==================
	- You can use the sample html file test.htm included to run the sample or you
	  can use your own html file and include the OBJVW control by means of the 
	  OBJECT tag.  In the control's window a treeview control will appear that 
	  contains the root document name and its destination.  If you are using the test
	  file this should be "Frame 0, file://test.htm".  If the name property of the 
	  window is set then that will appear instead of "Frame 0".  If you double click
	  this, it will expand to show the controls in the curretn level plus all the 
	  frames of the current level.  Here is what it looks like for the test page:

	  Frame0,file://test.htm
	    Frame1, file://foo.htm
	    Frame2, http://www.microsoft.com/ie/most/howto/java.htm
	    ObjVwCtl Object,linktrck
	    Democtl Control,Demo1
	    Democtl Control,Demo2
	
	  The first two lines under the main line are for the frames of the main
	  document.  If these frames have controls or sub frames, they will be parent
	  nodes with that infromation available when they are expanded.  If the frame's
	  name property is available, that will show up instead of "FrameX" where X is 
	  the number of the frame.  The last 3 lines indicate all of the controls in the
	  main page.  The test on the right is obtained from the registry and is the 
	  default value for the control's classid. The text on the right is the ID or
	  NAME from the control's object tag if available.  There are certain situations
	  where this information will not be available, see the LIMITATIONS section 
	  below for more details.


SINKING EVENTS
==============
Evtsink.cpp and Evtsink.h can be derived from and implement a generic event sinking class.  The code in appsink.cpp and appsink.h illustrate this but here are the general 
steps necessary to use CEvtSink.

	- Make your own event sink class inherit from CEvtSink

	- Implement your event handler functions for each event you want to sink.  I
	  implement these as static member functions for my derived event sink class 
	  CAppSink.  Regardless of how these are implemented they must all accept 3
	  parameters.  A pointer to some user defined data passed in when the event
	  was mapped, an array of VARIANTARG structures representing the arguments to the
	  event function, and a cound of arguments.

	- Inside your class' initialization function, call CEvtSink::Create with the
	  IID of the event interface and an IUnknown pointer on the object you want to
	  sink events for.  You can use IID_NULL for the first parameter to sink the 
	  default source event.

	- Also inside the creation function, call CEvtSink::MapEvent for each event on 
	  the event interface you want to sink.  MapEvent takes a non case sensitive 
	  event name a pointer to an event handler function that will be called when the 
	  event fires, and a pointer to some user-defined data.

	- Call CEvtSink::ConnectEvents to start waiting for event notifications.

	- When you are through sinking events call CEvtSink::DisconnectEvents


LIMITATIONS
===========
The following are known problems and limitations of the sample:
	
	- The ActiveX object that wraps java applets does not implement IOleObject, or 
	  IProvideClassInfo.  This results in no real information being displayed for an
	  applet.  Currently the string  "No Class Info, " is displayed.  This will be
	  addressed in a future version of this sample.

	- There is no event in the internet explorer model that indicates "all pages 
	  that are included by this page are completely loaded".  In addition, the
	  ProgressChange event is not sent for documents that are not HTML documents.	  
    	  This results in having to rebuild the control tree every time a page is loaded.
	
	- The user interface is not very intuitive.  It is difficult to distinguish
	  between a child control and a frame especially if the frame has no contained
	  controls or frames.  This will be addressed in a futuer version of this sample.


//--- EOF -----------------------------------------------------------------
