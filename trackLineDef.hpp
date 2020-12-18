
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



#ifndef __TRACKLINEDEF_H__
#define __TRACKLINEDEF_H__


#include <cerrno>
#include <unistd.h>
#include <sys/types.h>

#include <QtCore>
#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif

#include "nvutility.h"
#include "nvutility.hpp"

#include "gsf.h"
#include "czmil.h"
#include "FilePOSOutput.h"
#include <lasreader.hpp>
#include <proj_api.h>
#include <ogr_spatialref.h>

#include "version.hpp"


#define MPS_TO_KNOTS 1.943844924


#define GCS_NAD83 4269
#define GCS_WGS_84 4326


//   WGS84 / UTM northern hemisphere: 326zz where zz is UTM zone number
//   WGS84 / UTM southern hemisphere: 327zz where zz is UTM zone number
//   US State Plane (NAD83): 269xx

#define PCS_NAD83_UTM_zone_3N 26903
#define PCS_NAD83_UTM_zone_23N 26923
#define PCS_WGS84_UTM_zone_1N 32601
#define PCS_WGS84_UTM_zone_60N 32660
#define PCS_WGS84_UTM_zone_1S 32701
#define PCS_WGS84_UTM_zone_60S 32760


//  Data types.

#define TRACKLINE_GSF        0
#define TRACKLINE_CSF        1
#define TRACKLINE_POS        2
#define TRACKLINE_LAS        3


typedef struct
{
  double              x;      //  position longitude (dec deg)
  double              y;      //  position latitude (dec deg)
  double              h;      //  heading (degrees)
  double              s;      //  speed in nautical miles per hour
  double              t;      //  time in seconds from 1900
  int32_t             f;      //  input file # (starting from 0)
  int32_t             p;      //  ping record_number (starting with 1)
} INFO;


typedef struct
{
  QGroupBox           *fbox;
  QProgressBar        *fbar;
} RUN_PROGRESS;


typedef struct
{
  double              heading[5];
  double              speed[5];
  uint8_t             las;
  QString             inputFilter;
  QString             input_dir;
  QString             output_dir;
  uint8_t             are;
  uint8_t             trk;
  NV_F64_XYMBR        mbr;
  char                progname[256];
  int32_t             window_x;
  int32_t             window_y;
  int32_t             window_width;
  int32_t             window_height;
  QString             wktString[10];    //  QStrings holding recently used WKT settings for LAS files
  QFont               font;             //  Font used for all ABE GUI applications
} OPTIONS;

typedef struct
{
  char                filename[1024];   //  Input filename
  char                wkt[8192];        //  Well-known Text
  uint8_t             input_wkt;        //  Flag set if user had to input WKT
  projPJ              pj_utm;           //  Proj.4 UTM projection
  projPJ              pj_latlon;        //  Proj.4 latlon projection
  uint8_t             projected;        //  Flag set if LAS file is projected
  QString             outputFile;       //  Output track file name
  QString             areFile;          //  Output area file name
} MISC;


void envin (OPTIONS *options);
void envout (OPTIONS *options);


#endif
