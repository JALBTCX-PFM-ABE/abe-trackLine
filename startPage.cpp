
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



#include "startPage.hpp"
#include "startPageHelp.hpp"

startPage::startPage (QWidget *parent, OPTIONS *op):
  QWizardPage (parent)
{
  options = op;


  setPixmap (QWizard::WatermarkPixmap, QPixmap(":/icons/trackLineWatermark.png"));


  setTitle (tr ("Introduction"));

  setWhatsThis (tr ("See, it really works!"));

  QLabel *label = new QLabel (tr ("trackLine is a tool for building an ASCII decimated trackline file and a minimum bounding rectangle (MBR)"
                                  "area file from GSF, CSF, or POS/SBET data.  It can also create an MBR area file from LAS/LAZ files. "
                                  "The resulting files (.trk and/or .are) are viewable in areaCheck or as overlays in pfmView.  UTM LAS/LAZ files "
                                  "will be converted to latitude and longitude using the information in the LAS/LAZ header to determine "
                                  "conversion parameters.<br><br>"
                                  "<b>IMPORTANT NOTE: Only an area file will be created if only LAS/LAZ files are used as input. Also, the "
                                  "area file will have a 2% cushion added to the boundaries to make sure it covers all data.</b><br><br>"
                                  "Help is available by clicking on the Help button and then clicking on the item "
                                  "for which you want help.  Click <b>Next</b> to continue or <b>Cancel</b> to exit."));

  label->setWordWrap(true);


  QVBoxLayout *vbox = new QVBoxLayout (this);
  vbox->addWidget (label);
  vbox->addStretch (10);



  QGroupBox *oBox = new QGroupBox (tr ("trackline output file"), this);
  QHBoxLayout *oBoxLayout = new QHBoxLayout;
  oBox->setLayout (oBoxLayout);
  oBoxLayout->setSpacing (10);

  outputFile = new QLineEdit (this);
  outputFile->setWhatsThis (outputFileText);
  oBoxLayout->addWidget (outputFile, 10);

  QPushButton *output_file_browse = new QPushButton (tr ("Browse..."), this);
  output_file_browse->setWhatsThis (output_fileBrowseText);
  connect (output_file_browse, SIGNAL (clicked ()), this, SLOT (slotOutputFileBrowse ()));
  oBoxLayout->addWidget (output_file_browse, 1);


  vbox->addWidget (oBox);


  registerField ("outputFile*", outputFile);
}



void 
startPage::slotOutputFileBrowse ()
{
  QFileDialog fd (this, tr ("trackLine Output file"));
  fd.setViewMode (QFileDialog::List);


  //  Always add the current working directory and the last used directory to the sidebar URLs in case we're running from the command line.
  //  This function is in the nvutility library.

  setSidebarUrls (&fd, options->output_dir);


  QStringList filters;
  filters << tr ("trackLine file (*.trk)");


  fd.setNameFilters (filters);
  fd.setFileMode (QFileDialog::AnyFile);


  QStringList files;


  if (fd.exec () == QDialog::Accepted) 
    {
      files = fd.selectedFiles ();

      QString file = files.at (0);

      if (!file.isEmpty ())
        {
          outputFile->setText (file);
        }
    }

  options->output_dir = fd.directory ().absolutePath ();
}
