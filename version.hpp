
/*********************************************************************************************

    This is public domain software that was developed by or for the U.S. Naval Oceanographic
    Office and/or the U.S. Army Corps of Engineers.

    This is a work of the U.S. Government. In accordance with 17 USC 105, copyright protection
    is not available for any work of the U.S. Government.

    Neither the United States Government, nor any employees of the United States Government,
    nor the author, makes any warranty, express or implied, without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, or assumes any liability or
    responsibility for the accuracy, completeness, or usefulness of any information,
    apparatus, product, or process disclosed, or represents that its use would not infringe
    privately-owned rights. Reference herein to any specific commercial products, process,
    or service by trade name, trademark, manufacturer, or otherwise, does not necessarily
    constitute or imply its endorsement, recommendation, or favoring by the United States
    Government. The views and opinions of authors expressed herein do not necessarily state
    or reflect those of the United States Government, and shall not be used for advertising
    or product endorsement purposes.
*********************************************************************************************/


/****************************************  IMPORTANT NOTE  **********************************

    Comments in this file that start with / * ! or / / ! are being used by Doxygen to
    document the software.  Dashes in these comment blocks are used to create bullet lists.
    The lack of blank lines after a block of dash preceeded comments means that the next
    block of dash preceeded comments is a new, indented bullet list.  I've tried to keep the
    Doxygen formatting to a minimum but there are some other items (like <br> and <pre>)
    that need to be left alone.  If you see a comment that starts with / * ! or / / ! and
    there is something that looks a bit weird it is probably due to some arcane Doxygen
    syntax.  Be very careful modifying blocks of Doxygen comments.

*****************************************  IMPORTANT NOTE  **********************************/




#ifndef VERSION

#define     VERSION     "PFM Software - trackLine V2.15 - 09/26/17"

#endif

/*! <pre>

    Version 1.00
    Jan C. Depner
    04/19/11

    First version.


    Version 1.01
    Jan C. Depner
    06/27/11

    Save all directories used by the QFileDialogs.  Add current working directory to the sidebar for all QFileDialogs.


    Version 1.02
    Jan C. Depner
    07/22/11

    Using setSidebarUrls function from nvutility to make sure that current working directory (.) and
    last used directory are in the sidebar URL list of QFileDialogs.


    Version 1.03
    Jan C. Depner
    08/18/11

    Fixed speed limits for airborne files in optionsPage.cpp.


    Version 1.04
    Jan C. Depner
    11/30/11

    Converted .xpm icons to .png icons.


    Version 1.05
    Jan C. Depner
    07/13/12

    Added support for CZMIL SBET File (CSF) format.


    Version 1.06
    Jan C. Depner (PFM Software)
    12/09/13

    Switched to using .ini file in $HOME (Linux) or $USERPROFILE (Windows) in the ABE.config directory.  Now
    the applications qsettings will not end up in unknown places like ~/.config/navo.navy.mil/blah_blah_blah on
    Linux or, in the registry (shudder) on Windows.


    Version 1.07
    Jan C. Depner (PFM Software)
    01/06/14

    Fixed an obvious screwup in inputPage.cpp where I was re-using the loop counters.
    Scoping in C++ saved my bacon but it was just too damn confusing.


    Version 1.08
    Jan C. Depner (PFM Software)
    01/19/14

    Switched to CZMIL_READONLY_SEQUENTIAL for CPF files in order to, hopefully, speed up reads.


    Version 1.09
    Jan C. Depner (PFM Software)
    03/01/14

    Removed include of hmpsparm.h (not used).


    Version 1.10
    Jan C. Depner (PFM Software)
    03/17/14

    Removed WLF support.  Top o' the mornin' to ye!


    Version 1.11
    Jan C. Depner (PFM Software)
    05/07/14

    Replaced RAD_TO_DEG with NV_RAD_TO_DEG.


    Version 1.12
    Jan C. Depner (PFM Software)
    07/01/14

    - Replaced all of the old, borrowed icons with new, public domain icons.  Mostly from the Tango set
      but a few from flavour-extended and 32pxmania.


    Version 1.20
    Jan C. Depner (PFM Software)
    07/11/14

    - Added ability to create a minimum bounding rectangle from LAS header bounding boxes and points from
      other data types.  It will now output both a .trk file and a .are file.


    Version 1.21
    Jan C. Depner (PFM Software)
    07/17/14

    - No longer uses liblas.  Now uses libslas (my own API for LAS).


    Version 1.22
    Jan C. Depner (PFM Software)
    07/23/14

    - Switched from using the old NV_INT64 and NV_U_INT32 type definitions to the C99 standard stdint.h and
      inttypes.h sized data types (e.g. int64_t and uint32_t).


    Version 1.23
    Jan C. Depner (PFM Software)
    07/29/14

    - Fixed errors discovered by cppcheck.


    Version 1.24
    Jan C. Depner (PFM Software)
    02/13/15

    - To give better feedback to shelling programs in the case of errors I've added the program name to all
      output to stderr.


    Version 2.00
    Jan C. Depner (PFM Software)
    03/13/15

    - Replaced my libslas with rapidlasso GmbH LASlib and LASzip.


    Version 2.01
    Jan C. Depner (PFM Software)
    03/14/15

    - Since AHAB Hawkeye has switched to LAS format I have removed support for the old Hawkeye I binary format.


    Version 2.02
    Jan C. Depner (PFM Software)
    03/19/15

    - For LAS files, some people neglect to put in the GeographicTypeGeoKey just assuming that it's WGS_84.
      If we don't find the key we'll do the same.


    Version 2.03
    Jan C. Depner (PFM Software)
    03/23/15

    - Now reads the LAS files since the header is not always correct.


    Version 2.04
    Jan C. Depner (PFM Software)
    03/30/15

    - Now handles uppercase LAS and LAZ file extensions for Windows afflicted files that have been transferred
      to operating systems that UnDeRsTaNd ThE DiFfErEnCe between upper and lowercase characters.
    - Reading all of the data for a LAS/LAZ file is now optional with the default being to not read the data and
      just use the header.


    Version 2.05
    Jan C. Depner (PFM Software)
    03/31/15

    - Fixed name filter for GSF files so that it wouldn't find files that don't end in .dNN where NN is numeric.
      This prevents us from seeing, for example, ESRI shape .dbf files in the GSF name list.


    Version 2.06
    Jan C. Depner (PFM Software)
    06/27/15

    - Corrected double free problem if error encountered writing to output file.
    - Fixed PROJ4 init problem.


    Version 2.07
    Jan C. Depner (PFM Software)
    07/04/15

    - Fixed LAS read file option.


    Version 2.08
    Jan C. Depner (PFM Software)
    07/09/15

    - Now handles Riegl LAS files that don't have GeographicTypeGeoKey and ProjectedCSTypeGeoKey defined in
      the GeoKeyDirectoryTag (34735) required VLR.


    Version 2.09
    Jan C. Depner (PFM Software)
    10/28/15

    - Changed the MBR buffer to 5% instead of 2%.


    Version 2.10
    Jan C. Depner (PFM Software)
    05/01/16

    - Added ability to read Well-known Text (WKT) from LAS 1.4 files.
    - Now asks for Well-known Text for any LAS file that it can't handle (missing 34735, no WKT, etc.).


    Version 2.11
    Jan C. Depner (PFM Software)
    05/09/16

    - Now reads the LAS 1.4 WKT properly (I hope).


    Version 2.12
    Jan C. Depner (PFM Software)
    05/12/16

    - Yet another LAS hack - some people don't put in the GeographicTypeGeoKey and just depend on the
      ProjectedCSTypeGeoKey to tell them what datum they're using.


    Version 2.13
    Jan C. Depner (PFM Software)
    08/27/16

    - Now uses the same font as all other ABE GUI apps.  Font can only be changed in pfmView Preferences.


    Version 2.14
    Jan C. Depner (PFM Software)
    10/15/16

    - Just a little clean-up of a couple of proj.4 strings.


    Version 2.16
    Jan C. Depner (PFM Software)
    09/26/17

    - A bunch of changes to support doing translations in the future.  There is a generic
      trackLine_xx.ts file that can be run through Qt's "linguist" to translate to another language.

</pre>*/
