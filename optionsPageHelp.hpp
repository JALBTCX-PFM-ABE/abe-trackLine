
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



QString headingGSFText = 
  optionsPage::tr ("Enter the heading change limit, in degrees, for GSF files.  If the heading of the input data changes "
                   "by this amount then a new vertex will be added to the output trackline file.  The normal default is 3.0 "
                   "degrees.");

QString speedGSFText = 
  optionsPage::tr ("Enter the speed change limit, in knots, for GSF files.  If the speed of the input data exceeds "
                   "this value then a new vertex will be added to the output trackline file.  The normal default is 20.0 "
                   "knots.");

QString headingPOSText = 
  optionsPage::tr ("Enter the heading change limit, in degrees, for POS/SBET/CSF/LAS files.  If the heading of the input data changes "
                   "by this amount then a new vertex will be added to the output trackline file.  The normal default is 5.0 "
                   "degrees.");

QString speedPOSText = 
  optionsPage::tr ("Enter the speed change limit, in knots, for POS/SBET/CSF/LAS files.  If the speed of the input data exceeds "
                   "this value then a new vertex will be added to the output trackline file.  The normal default is 240.0 "
                   "knots.");

QString readLASDataText = 
  optionsPage::tr ("If you check this box it will cause trackLine to read all of the data in the LAS files to recompute the "
                   "minimum and maximum bounds of the file prior to comparing it to the cumulative minimums and maximums.  Normally "
                   "you don't need to do this because the minimums and maximums in the LAS header are correct.  This option is much "
                   "slower than just using the values in the header but it is occasionally necessary due to incorrect values in the "
                   "file headers.");
