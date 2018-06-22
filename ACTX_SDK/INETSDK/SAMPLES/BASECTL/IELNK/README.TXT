To build IELnk, the FrameWrk sample must first be built. First run
\inetsdk\setenv.bat to be sure the ActiveX SDK include, bin, and lib
directories are included (first) in your environment. Run the 'nmake'
to build a debug version (built to the Debug subdirectory) or
'nmake nodebug=1' to build a retail (nodebug) directory into the
Retail subdirectory.

After building the FrameWrk library you can build the IELNK 
control by running 'nmake' or 'nmake nodebug=1'.

IElnk demonstrates the usage of Simple Hyperlink Navigation
API. 

It shows the usage of the following API functions.
HlinkSimpleNavigateToString();
HlinkSimpleNavigateToMoniker();
HlinkGoBack();
HlinkGoForward();
HlinkNavigateString();
HlinkNavigateMoniker();

It demonstrates creating the URL moniker.  And also the way to
mark a control as safe for scripting and initializing.

The sample contains demo HTML page ielnkdem.htm which demonstrates
the usage of the control. It uses VBSCRIPT to handle events.

ielnkjv.htm is a JScript version of  ielnkdem.htm. It 
demonstrates defining functions in JScript and button 
event handling.

