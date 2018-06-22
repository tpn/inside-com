Component Categories Manager
--------- ---------- -------

Before installing the Component Categories Manager, please read the
license agreement in the first section of the file Redist.txt.  Part of
that agreement refers to rights described in the file License.txt.  You
must agree to these licensing conditions in order to use the software.

Some details on the self-extracting intallers:

•CCDIST.EXE installs COMCAT.DLL and REGSVR32.EXE into %windir%/system 
 or %systemroot%/system32 and calls regsvr32 on COMCAT.DLL. COMCAT 
 creates the HKEY_CLASSES_ROOT\Component Categories key and creates 
 entries for the five "legacy" categories. If COMCAT.DLL is in use, it 
 will be replaced upon the next reboot (reboot not enforced). 

•CCDIST35.EXE installs COMCAT.DLL into %systemroot$/system32 (NT 3.51
 only) and directly registers COMCAT.DLL/COMCAT35.DLL (no
 regsvr32.exe).  If the DLL is in use, the installation will fail
 without notification.

•Both EXEs have a quiet mode (CCDIST /q), that enables Win'95 logo
 compliance.

•COMCAT.DLL depends on OLE32.DLL (String->GUID/CoTaskMemXXX),
 KERNEL32.DLL (misc), USER32.DLL (wsprintf) and ADVAPI32.DLL
 (registry). 

Important: MS Apps and ISVs must run CCDIST.EXE/CCDIST35.EXE from 
their setup program to install COMCAT.DLL to avoid setup/versioning 
problems. 
