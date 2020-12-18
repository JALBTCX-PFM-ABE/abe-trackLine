
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



#include "trackLine.hpp"
#include "trackLineHelp.hpp"

trackLine::trackLine (int *argc __attribute__ ((unused)), char **argv, QWidget *parent)
  : QWizard (parent, 0)
{
  void set_defaults (OPTIONS *options);


  QResource::registerResource ("/icons.rcc");


  strcpy (options.progname, argv[0]);


  //  Set the main icon

  setWindowIcon (QIcon (":/icons/trackLineWatermark.png"));


  set_defaults (&options);


  envin (&options);


  // Set the application font

  QApplication::setFont (options.font);


  //  Set the window size and location from the defaults

  this->resize (options.window_width, options.window_height);
  this->move (options.window_x, options.window_y);


  setWizardStyle (QWizard::ClassicStyle);


  setOption (HaveHelpButton, true);
  setOption (ExtendedWatermarkPixmap, false);

  connect (this, SIGNAL (helpRequested ()), this, SLOT (slotHelpClicked ()));


  setPage (0, new startPage (this, &options));
  setPage (1, new optionsPage (this, &options));
  setPage (2, new inputPage (this, &options, &inputFiles));
  setPage (3, new runPage (this, &progress, &trackList));


  setButtonText (QWizard::CustomButton1, tr ("&Run"));
  setOption (QWizard::HaveCustomButton1, true);
  button (QWizard::CustomButton1)->setToolTip (tr ("Run the trackline generation process"));
  button (QWizard::CustomButton1)->setWhatsThis (runText);
  connect (this, SIGNAL (customButtonClicked (int)), this, SLOT (slotCustomButtonClicked (int)));

  setStartId (0);
}


void trackLine::initializePage (int id)
{
  button (QWizard::HelpButton)->setIcon (QIcon (":/icons/contextHelp.png"));
  button (QWizard::CustomButton1)->setEnabled (false);

  switch (id)
    {
    case 0:
      break;

    case 1:
      break;

    case 2:
      break;

    case 3:
      button (QWizard::CustomButton1)->setEnabled (true);
      break;
    }
}



void trackLine::cleanupPage (int id)
{
  switch (id)
    {
    case 0:
      break;

    case 1:
      break;

    case 2:
      break;

    case 3:
      break;
    }
}



void 
trackLine::slotHelpClicked ()
{
  QWhatsThis::enterWhatsThisMode ();
}



void 
trackLine::slotCustomButtonClicked (int id __attribute__ ((unused)))
{
  options.heading[TRACKLINE_GSF] = field ("headingGSF").toDouble ();
  options.speed[TRACKLINE_GSF] = field ("speedGSF").toDouble ();
  options.heading[TRACKLINE_POS] = options.heading[TRACKLINE_CSF] = field ("headingPOS").toDouble ();
  options.speed[TRACKLINE_POS] = options.speed[TRACKLINE_CSF] = field ("speedPOS").toDouble ();
  options.las = field ("readLASData").toBool ();


  misc.outputFile = field ("outputFile").toString ();


  int32_t points = 0;
  int32_t track_points = 0;

  start_heading = 0.0;


  //  Get the files from the QTextEdit box on the inputPage.

  QTextCursor inputCursor = inputFiles->textCursor ();

  inputCursor.setPosition (0);


  QStringList sort_files;

  sort_files.clear ();

  do
    {
      sort_files << inputCursor.block ().text ();
    } while (inputCursor.movePosition (QTextCursor::NextBlock));


  //  Sort so we can remove dupes.

  sort_files.sort ();


  //  Remove dupes and place into input_files.

  QString name, prev_name = "";
  input_files.clear ();

  for (int32_t i = 0 ; i < sort_files.size () ; i++)
    {
      name = sort_files.at (i);

      if (name != prev_name)
        {
          input_files.append (name);
          prev_name = name;
        }
    }


  button (QWizard::BackButton)->setEnabled (false);
  button (QWizard::CustomButton1)->setEnabled (false);
  QApplication::setOverrideCursor (Qt::WaitCursor);


  int32_t                   gsf_handle = -1, csf_handle = -1, hour, min, ping, eof, percent = 0, old_percent = -1;
  float                     sec;
  double                    lat, lon;
  uint8_t                   first = NVTrue, got_data;
  INFO                      data, prev_data, last_data = {0.0, 0.0, 0.0, 0.0, 0.0, 0, 0};
  FILE                      *fp = NULL, *ofp = NULL;
  gsfDataID                 gsf_id;
  gsfRecords                gsf_rec;
  POS_OUTPUT_T              pos;
  CZMIL_CSF_Header          csf_header;
  CZMIL_CSF_Data            csf_record;
  LASreadOpener             lasreadopener;
  LASheader                 *lasheader;
  LASreader                 *lasreader;
  QListWidgetItem           *cur;
  QString                   tmpString;
  extern int32_t            gsfError;


  //  Set some defaults

  misc.pj_utm = NULL;
  misc.pj_latlon = NULL;
  misc.input_wkt = NVFalse;
  misc.projected = NVFalse;


  //  Add the extension if needed.

  if (!misc.outputFile.endsWith (".trk")) misc.outputFile.append (".trk");


  if ((ofp = fopen (misc.outputFile.toLatin1 (), "w")) == NULL)
    {
      QMessageBox::critical (this, "trackLine", tr ("Unable to open output file %1!").arg (misc.outputFile));
      exit (-1);
    }


  //  Save the output directory.  It might have been input manually instead of browsed.

  options.output_dir = QFileInfo (misc.outputFile).absoluteDir ().absolutePath ();


  int32_t file_count = input_files.size ();


  options.are = NVFalse;
  options.trk = NVFalse;
  options.mbr.min_x = 999.0;
  options.mbr.min_y = 999.0;
  options.mbr.max_x = -999.0;
  options.mbr.max_y = -999.0;


  for (int32_t i = 0 ; i < file_count ; i++)
    {
      strcpy (misc.filename, input_files.at (i).toLatin1 ());


      progress.fbar->reset ();
      progress.fbar->setRange (0, 100);
      tmpString = QString (tr ("Processing file %1 of %2 - %3").arg (i + 1).arg (file_count).arg (QFileInfo (misc.filename).fileName ()));
      progress.fbox->setTitle (tmpString);
      qApp->processEvents ();


      progress.fbar->setWhatsThis (tr ("Progress of input file processing"));


      first = NVTrue;
      ping = 0;


      //  Open the input files and read the data.

      if (!input_files.at (i).endsWith (".las") && !input_files.at (i).endsWith (".laz")) fprintf (ofp, "FILE %03d = %s\n", i, misc.filename);

      got_data = NVFalse;

      type = TRACKLINE_GSF;
      if (strstr (misc.filename, ".csf")) type = TRACKLINE_CSF;
      if (strstr (misc.filename, ".pos") || strstr (misc.filename, ".out") || strstr (misc.filename, ".POS") || strstr (misc.filename, ".OUT"))
        type = TRACKLINE_POS;
      if (strstr (misc.filename, ".las") || strstr (misc.filename, ".laz")) type = TRACKLINE_LAS;


      switch (type)
	{
        case TRACKLINE_GSF:

          if (!gsfOpen (misc.filename, GSF_READONLY_INDEX, &gsf_handle))
            {
              time_t tv_sec;
              long tv_nsec;

              int32_t records = gsfIndexTime (gsf_handle, GSF_RECORD_SWATH_BATHYMETRY_PING, -1, &tv_sec, &tv_nsec);

              for (int32_t j = 0 ; j < records ; j++)
                {
                  gsf_id.recordID = GSF_RECORD_SWATH_BATHYMETRY_PING;
                  gsf_id.record_number = j + 1;
                  if (gsfRead (gsf_handle, GSF_RECORD_SWATH_BATHYMETRY_PING, &gsf_id, &gsf_rec, NULL, 0) < 0) break;

                  if (!(gsf_rec.mb_ping.ping_flags & GSF_IGNORE_PING) && gsf_rec.mb_ping.longitude != 0.0 && gsf_rec.mb_ping.latitude != 0.0 &&
                      fabs (gsf_rec.mb_ping.longitude) <= 180.0 && fabs (gsf_rec.mb_ping.latitude) <= 90.0)
                    {
                      ping++;

                      got_data = NVTrue;

                      points++;

                      data.f = i;
                      data.t = (double) gsf_rec.mb_ping.ping_time.tv_sec + (double) gsf_rec.mb_ping.ping_time.tv_nsec / 1000000000.0;
                      data.p = ping;
                      data.y = gsf_rec.mb_ping.latitude;
                      data.x = gsf_rec.mb_ping.longitude;
                      data.h = gsf_rec.mb_ping.heading;


                      //  Compute the MBR just in case we have some LAS files.

                      options.mbr.min_x = qMin (options.mbr.min_x, data.x);
                      options.mbr.min_y = qMin (options.mbr.min_y, data.y);
                      options.mbr.max_x = qMax (options.mbr.max_x, data.x);
                      options.mbr.max_y = qMax (options.mbr.max_y, data.y);
                      options.trk = NVTrue;


                      last_data = data;


                      if (first)
                        {
                          data.s = 0.0;

                          hour = (int) data.t / 3600;
                          min = ((int) data.t % 3600) / 60;
                          sec = fmod (data.t, 60.0) * 60.0;


                          //  Save the last good heading since we want to compare it against the current heading.  Conversely, we want to compare
                          //  speeds using two adjacent points.

                          start_heading = data.h;

                          fprintf (ofp, "+,%d,%d,%.9f,%.9f,%f,%f,XXXX,XXX,%02d,%02d,%f\n", data.f, data.p, data.y, data.x, data.h, data.s, hour, min, sec);
                          first = NVFalse;

                          track_points++;
                        }
                      else if (changepos (&data, &prev_data))
                        {
                          hour = (int) data.t / 3600;
                          min = ((int) data.t % 3600) / 60;
                          sec = fmod (data.t, 60.0) * 60.0;


                          //  Save the last good heading since we want to compare it against the current heading.  Conversely, we want to compare
                          //  speeds using two adjacent points.

                          start_heading = data.h;

                          fprintf (ofp, "+,%d,%d,%.9f,%.9f,%f,%f,XXXX,XXX,%02d,%02d,%f\n", data.f, data.p, data.y, data.x, data.h, data.s, hour, min, sec);

                          track_points++;
                        }

                      prev_data = data;


                      percent = (int32_t) roundf (((float) (j) / records) * 100.0);
                      if (percent - old_percent >= 5 || old_percent > percent)
                        {
                          progress.fbar->setValue (percent);
                          old_percent = percent;

                          qApp->processEvents ();
                        }
                    }
                }

              if (got_data)
                {
                  hour = (int) last_data.t / 3600;
                  min = ((int) last_data.t % 3600) / 60;
                  sec = fmod (last_data.t, 60.0) * 60.0;

                  fprintf (ofp, "+,%d,%d,%.9f,%.9f,%f,%f,XXXX,XXX,%02d,%02d,%f\n", last_data.f, last_data.p, last_data.y, last_data.x, last_data.h,
                           last_data.s, hour, min, sec);

                  track_points++;
                }

              gsfClose (gsf_handle);

              progress.fbar->setValue (100);
              qApp->processEvents ();
            }
          else
            {
              cur = new QListWidgetItem (QString (gsfStringError ()));
              trackList->addItem (cur);
              trackList->setCurrentItem (cur);
              trackList->scrollToItem (cur);

              if (gsfError != GSF_FOPEN_ERROR) gsfClose (gsf_handle);
            }

          break;


        case TRACKLINE_CSF:

          if ((csf_handle = czmil_open_csf_file (misc.filename, &csf_header, CZMIL_READONLY_SEQUENTIAL)) < 0)
            {
              cur = new QListWidgetItem (QString (czmil_strerror ()));
              trackList->addItem (cur);
              trackList->setCurrentItem (cur);
              trackList->scrollToItem (cur);
            }
          else
            {
	      for (int32_t j = 0 ; j < csf_header.number_of_records ; j++)
		{
		  if (czmil_read_csf_record (csf_handle, j, &csf_record) < 0)
		    {
		      cur = new QListWidgetItem (QString (czmil_strerror ()));
		      trackList->addItem (cur);
		      trackList->setCurrentItem (cur);
		      trackList->scrollToItem (cur);
		      break;
		    }


		  got_data = NVTrue;

		  points++;

		  data.f = i;
		  data.t = (double) csf_record.timestamp / 1000000.0;
		  data.p = j;
		  data.y = csf_record.latitude;
		  data.x = csf_record.longitude;
		  data.h = csf_record.heading;


                  //  Compute the MBR just in case we have some LAS files.

                  options.mbr.min_x = qMin (options.mbr.min_x, data.x);
                  options.mbr.min_y = qMin (options.mbr.min_y, data.y);
                  options.mbr.max_x = qMax (options.mbr.max_x, data.x);
                  options.mbr.max_y = qMax (options.mbr.max_y, data.y);
                  options.trk = NVTrue;


		  last_data = data;

		  if (first)
		    {
		      data.s = 0.0;

		      hour = (int) data.t / 3600;
		      min = ((int) data.t % 3600) / 60;
		      sec = fmod (data.t, 60.0) * 60.0;


		      //  Save the last good heading since we want to compare it against the current heading.  Conversely, we want to compare
		      //  speeds using two adjacent points.

		      start_heading = data.h;

		      fprintf (ofp, "+,%d,%d,%.9f,%.9f,%f,%f,XXXX,XXX,%02d,%02d,%f\n", data.f, data.p, data.y, data.x, data.h, data.s, hour, min, sec);
		      first = NVFalse;

		      track_points++;
		    }
		  else if (changepos (&data, &prev_data))
		    {
		      hour = (int) data.t / 3600;
		      min = ((int) data.t % 3600) / 60;
		      sec = fmod (data.t, 60.0) * 60.0;


		      //  Save the last good heading since we want to compare it against the current heading.  Conversely, we want to compare
		      //  speeds using two adjacent points.

		      start_heading = data.h;

		      fprintf (ofp, "+,%d,%d,%.9f,%.9f,%f,%f,XXXX,XXX,%02d,%02d,%f\n", data.f, data.p, data.y, data.x, data.h, data.s, hour, min, sec);

		      track_points++;
		    }


		  prev_data = data;


		  //  We don't want to eat up all of the free time on the system with a progress bar.

		  percent = (int32_t) roundf (((float) (j) / csf_header.number_of_records) * 100.0);
		  if (percent - old_percent >= 5 || old_percent > percent)
		    {
		      progress.fbar->setValue (percent);
		      old_percent = percent;

		      qApp->processEvents ();
		    }
		}


	      if (got_data)
		{
		  hour = (int) last_data.t / 3600;
		  min = ((int) last_data.t % 3600) / 60;
		  sec = fmod (last_data.t, 60.0) * 60.0;

		  fprintf (ofp, "+,%d,%d,%.9f,%.9f,%f,%f,XXXX,XXX,%02d,%02d,%f\n", last_data.f, last_data.p, last_data.y, last_data.x, last_data.h,
			   last_data.s, hour, min, sec);

		  track_points++;
		}

	      czmil_close_csf_file (csf_handle);
	    }

          progress.fbar->setValue (100);
          qApp->processEvents ();

          break;


	case TRACKLINE_LAS:

          //  Open the LAS file and read the header.

          lasreadopener.set_file_name (misc.filename);
          lasreader = lasreadopener.open ();

          if (!lasreader)
            {
              tmpString.sprintf ("%s %s %s %d - Can't open LAS file %s\n", options.progname, __FILE__, __FUNCTION__, __LINE__, misc.filename);
              cur = new QListWidgetItem (tmpString);
              trackList->addItem (cur);
              trackList->setCurrentItem (cur);
              trackList->scrollToItem (cur);
            }
          else
            {
              lasheader = &lasreader->header;


              //  Check to see if we can figure out what the hell kind of coordinate system the LAS file is using.
              //  If the user input WKT for a previous file we're going to use that for all subsequent files.

              if (!misc.input_wkt) LAS_WKT (this, &options, &misc, lasheader);


              //  We'll start out with what the header says (it isn't always correct).

              NV_F64_XYMBR las_mbr;

              las_mbr.min_x = lasheader->min_x;
              las_mbr.min_y = lasheader->min_y;
              las_mbr.max_x = lasheader->max_x;
              las_mbr.max_y = lasheader->max_y;

              if (misc.projected)
                {
                  double ux, uy;

                  ux = las_mbr.min_x;
                  uy = las_mbr.min_y;
                  pj_transform (misc.pj_utm, misc.pj_latlon, 1, 1, &ux, &uy, NULL);
                  ux *= NV_RAD_TO_DEG;
                  uy *= NV_RAD_TO_DEG;

                  las_mbr.min_x = ux;
                  las_mbr.min_y = uy;


                  ux = las_mbr.max_x;
                  uy = las_mbr.max_y;
                  pj_transform (misc.pj_utm, misc.pj_latlon, 1, 1, &ux, &uy, NULL);
                  ux *= NV_RAD_TO_DEG;
                  uy *= NV_RAD_TO_DEG;

                  las_mbr.max_x = ux;
                  las_mbr.max_y = uy;
                }


              //  If the file is kosher we will either just use the MBR from the header or we will read all of the data (in some
              //  cases the header limits are incorrect.

              if (options.las)
                {
                  for (int32_t j = 0 ; j < (int32_t) lasheader->number_of_point_records ; j++)
                    {
                      if (!lasreader->read_point ())
                        {
                          tmpString.sprintf ("Error reading point record %d in %s : %s %s %s %d\n", j, misc.filename, options.progname, __FILE__,
                                             __FUNCTION__, __LINE__);
                          cur = new QListWidgetItem (tmpString);
                          trackList->addItem (cur);
                          trackList->setCurrentItem (cur);
                          trackList->scrollToItem (cur);

                          lasreader->close ();
                          continue;
                        }


                      //  We don't want to eat up all of the free time on the system with a progress bar.

                      percent = NINT (((float) j / (float) lasheader->number_of_point_records) * 100.0);
                      if (percent - old_percent >= 5 || old_percent > percent)
                        {
                          progress.fbar->setValue (percent);
                          old_percent = percent;

                          qApp->processEvents ();
                        }


                      lat = lon = 0.0;

                      if (misc.projected)
                        {
                          double ux, uy;

                          ux = lasreader->point.get_x ();
                          uy = lasreader->point.get_y ();
                          pj_transform (misc.pj_utm, misc.pj_latlon, 1, 1, &ux, &uy, NULL);
                          ux *= NV_RAD_TO_DEG;
                          uy *= NV_RAD_TO_DEG;

                          lon = ux;
                          lat = uy;
                        }
                      else
                        {
                          lon = lasreader->point.get_x ();
                          lat = lasreader->point.get_y ();
                        }

                      options.mbr.min_x = qMin (options.mbr.min_x, lon);
                      options.mbr.min_y = qMin (options.mbr.min_y, lat);
                      options.mbr.max_x = qMax (options.mbr.max_x, lon);
                      options.mbr.max_y = qMax (options.mbr.max_y, lat);
                    }
                }
              else
                {
                  options.mbr.min_x = qMin (options.mbr.min_x, las_mbr.min_x);
                  options.mbr.min_y = qMin (options.mbr.min_y, las_mbr.min_y);
                  options.mbr.max_x = qMax (options.mbr.max_x, las_mbr.max_x);
                  options.mbr.max_y = qMax (options.mbr.max_y, las_mbr.max_y);
                }

              options.are = NVTrue;

              lasreader->close ();
            }

          progress.fbar->setValue (100);
          qApp->processEvents ();

	  break;


	case TRACKLINE_POS:

	  if ((fp = open_pos_file (misc.filename)) != NULL)
	    {
              fseek (fp, 0, SEEK_END);
              eof = ftell (fp);
              fseek (fp, 0, SEEK_SET);


              //  Set the progress bar.


	      while (!pos_read_record (fp, &pos))
		{
		  ping++;

		  got_data = NVTrue;

		  points++;

		  data.f = i;
		  data.t = pos.gps_time;
		  data.p = ping;
		  data.y = pos.latitude * NV_RAD_TO_DEG;
		  data.x = pos.longitude * NV_RAD_TO_DEG;
		  data.h = (pos.platform_heading - pos.wander_angle) * NV_RAD_TO_DEG;


                  //  Compute the MBR just in case we have some LAS files.

                  options.mbr.min_x = qMin (options.mbr.min_x, data.x);
                  options.mbr.min_y = qMin (options.mbr.min_y, data.y);
                  options.mbr.max_x = qMax (options.mbr.max_x, data.x);
                  options.mbr.max_y = qMax (options.mbr.max_y, data.y);
                  options.trk = NVTrue;


                  last_data = data;


		  if (first)
		    {
                      data.s = 0.0;

                      hour = (int) data.t / 3600;
                      min = ((int) data.t % 3600) / 60;
                      sec = fmod (data.t, 60.0) * 60.0;


                      //  Save the last good heading since we want to compare it against the current heading.  Conversely, we want to compare
                      //  speeds using two adjacent points.

                      start_heading = data.h;

                      fprintf (ofp, "+,%d,%d,%.9f,%.9f,%f,%f,XXXX,XXX,%02d,%02d,%f\n", data.f, data.p, data.y, data.x, data.h, data.s, hour, min, sec);
		      first = NVFalse;

                      track_points++;
		    }
		  else if (changepos (&data, &prev_data))
		    {
                      hour = (int) data.t / 3600;
                      min = ((int) data.t % 3600) / 60;
                      sec = fmod (data.t, 60.0) * 60.0;


                      //  Save the last good heading since we want to compare it against the current heading.  Conversely, we want to compare
                      //  speeds using two adjacent points.

                      start_heading = data.h;

                      fprintf (ofp, "+,%d,%d,%.9f,%.9f,%f,%f,XXXX,XXX,%02d,%02d,%f\n", data.f, data.p, data.y, data.x, data.h, data.s, hour, min, sec);

                      track_points++;
		    }

                  prev_data = data;


                  //  We don't want to eat up all of the free time on the system with a progress bar.

                  percent = (int32_t) roundf (((float) (ftell (fp)) / eof) * 100.0);
                  if (percent - old_percent >= 5 || old_percent > percent)
                    {
                      progress.fbar->setValue (percent);
                      old_percent = percent;

                      qApp->processEvents ();
                    }
		}


              if (got_data)
                {
                  hour = (int) last_data.t / 3600;
                  min = ((int) last_data.t % 3600) / 60;
                  sec = fmod (last_data.t, 60.0) * 60.0;

                  fprintf (ofp, "+,%d,%d,%.9f,%.9f,%f,%f,XXXX,XXX,%02d,%02d,%f\n", last_data.f, last_data.p, last_data.y, last_data.x, last_data.h,
                           last_data.s, hour, min, sec);

                  track_points++;
                }

              fclose (fp);

              progress.fbar->setValue (100);
              qApp->processEvents ();
	    }
	  break;
	}


      cur = new QListWidgetItem (tr ("Completed processing file %1 of %2 - %3").arg (i + 1).arg (file_count).arg (QFileInfo (misc.filename).fileName ()));
      trackList->addItem (cur);
      trackList->setCurrentItem (cur);
      trackList->scrollToItem (cur);
    }


  fclose (ofp);


  misc.areFile = misc.outputFile;
  misc.areFile.replace (".trk", ".are");

  char file[2][1024];
  strcpy (file[1], misc.areFile.toLatin1 ());


  //  If we opened a .trk file but we only had LAS files (in other words, it's empty) let's rename the .trk file instead
  //  of creating an empty .trk file and an areafile.

  if (!options.trk)
    {
      strcpy (file[0], misc.outputFile.toLatin1 ());
      if (rename (file[0], file[1]))
        {
          fprintf (stderr, "%s %s %s %d - %s - %s\n", options.progname, __FILE__, __FUNCTION__, __LINE__, file[1], strerror (errno));
          exit (-1);
        }
    }


  if ((ofp = fopen (file[1], "w")) == NULL)
    {
      QMessageBox::critical (this, "trackLine", tr ("Unable to open output file %1!").arg (misc.areFile));
      exit (-1);
    }


  //  Add 5% to the bounds.

  double cushion_x = (options.mbr.max_x - options.mbr.min_x) * 0.05;
  double cushion_y = (options.mbr.max_y - options.mbr.min_y) * 0.05;

  options.mbr.min_x -= cushion_x;
  options.mbr.min_y -= cushion_y;
  options.mbr.max_x += cushion_x;
  options.mbr.max_y += cushion_y;

  fprintf (ofp, "%.11f, %.11f\n", options.mbr.min_y, options.mbr.min_x);
  fprintf (ofp, "%.11f, %.11f\n", options.mbr.min_y, options.mbr.max_x);
  fprintf (ofp, "%.11f, %.11f\n", options.mbr.max_y, options.mbr.max_x);
  fprintf (ofp, "%.11f, %.11f\n", options.mbr.max_y, options.mbr.min_x);

  fclose (ofp);


  cur = new QListWidgetItem (tr ("\n\nCreated minimum bounding rectangle area file %1 from input points/LAS bounding rectangles.\n\n").arg (misc.areFile));
  trackList->addItem (cur);
  trackList->setCurrentItem (cur);
  trackList->scrollToItem (cur);


  if (options.trk)
    {
      cur = new QListWidgetItem (tr ("\n\nDetermined %1 trackline points from %2 positions.\n\n").arg (track_points).arg (points));
      trackList->addItem (cur);
      trackList->setCurrentItem (cur);
      trackList->scrollToItem (cur);
    }


  //  Use frame geometry to get the absolute x and y.

  QRect tmp = this->frameGeometry ();
  options.window_x = tmp.x ();
  options.window_y = tmp.y ();


  //  Use geometry to get the width and height.

  tmp = this->geometry ();
  options.window_width = tmp.width ();
  options.window_height = tmp.height ();


  //  Save the options to the QSettings file.

  envout (&options);


  QApplication::restoreOverrideCursor ();
  button (QWizard::FinishButton)->setEnabled (true);
}



int32_t 
trackLine::heading_change (INFO *data)
{
  double              heading1 = start_heading, heading2 = data->h;


  //  Check for northerly heading and adjust if necessary

  if (heading1 > (360 - options.heading[type]) && heading2 < options.heading[type]) heading2 += 360;
  if (heading2 > (360 - options.heading[type]) && heading1 < options.heading[type]) heading1 += 360;

  return (fabs (heading1 - heading2) >= options.heading[type]);
}



uint8_t 
trackLine::changepos (INFO *data, INFO *prev_data)
{
  double              dist;
  double              az;
  uint8_t             change;


  change = NVFalse;


  //  Heading change greater than options.heading[type].

  if (heading_change (data))
    {
      change = NVTrue;
    }


  //  Time change greater than one minute.

  else if (data->t - prev_data->t > 60.0)
    {
      change = NVTrue;
    }


  //  Speed greater than options.speed[type].

  else
    {
      invgp (NV_A0, NV_B0, prev_data->y, prev_data->x, data->y, data->x, &dist, &az);

      if (data->t != prev_data->t)
	{
	  data->s = dist / (data->t - prev_data->t) * MPS_TO_KNOTS;

	  if (data->s > options.speed[type])
	    {
	      change = NVTrue;
	    }
	}
    }

  return (change);
}
