Before attempting to build IEMime, first run setenv.bat to be
sure the ActiveX SDK include, bin, and lib directories are included
in your environment (in front of VC++ and the Win32 SDK)

IEMime depends on the FrameWrk sample, which must be built first. To
build a debug version of the framework library, use the command line
   nmake 
from the FrameWrk directory. To build a retail version of the framework, 
use the command line
   nmake nodebug=1
from the FrameWrk directory. Debug and retail libraries are placed in
the ..\Lib subdirectory.

After building the FrameWrk library you can build the IEMime control
by moving to the IEMime directory and entering the command
   nmake
to build a debug version, or 
   nmake nodebug=1
to build a retail version.

The IEMime sample will be automatically registered as part of the
build process.

IEMime demonstrates the custom mime type registration.
The custom mime types also have to be registered using IE.

IEMime downloads the specified URL and displays the MIME type
of the URL.

IEMime also shows the usage of RegisterFormatEnumerator() and
RegisterMediaTypes() API functions.

