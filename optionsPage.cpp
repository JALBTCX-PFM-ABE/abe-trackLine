
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



#include "optionsPage.hpp"
#include "optionsPageHelp.hpp"

optionsPage::optionsPage (QWidget *parent, OPTIONS *op):
  QWizardPage (parent)
{
  options = op;


  setTitle (tr ("trackLine Options"));


  setPixmap (QWizard::WatermarkPixmap, QPixmap(":/icons/trackLineWatermark.png"));


  QVBoxLayout *vbox = new QVBoxLayout (this);
  vbox->setMargin (5);
  vbox->setSpacing (5);



  QGroupBox *lbox = new QGroupBox (tr ("Limits"), this);
  QHBoxLayout *lboxLayout = new QHBoxLayout;
  lbox->setLayout (lboxLayout);
  QVBoxLayout *lboxLeftLayout = new QVBoxLayout;
  QVBoxLayout *lboxRightLayout = new QVBoxLayout;
  lboxLayout->addLayout (lboxLeftLayout);
  lboxLayout->addLayout (lboxRightLayout);


  QGroupBox *gBox = new QGroupBox ("GSF", this);
  QHBoxLayout *gBoxLayout = new QHBoxLayout;
  gBox->setLayout (gBoxLayout);
  gBoxLayout->setSpacing (10);

  QGroupBox *ghBox = new QGroupBox (tr ("Heading"), this);
  QHBoxLayout *ghBoxLayout = new QHBoxLayout;
  ghBox->setLayout (ghBoxLayout);
  ghBoxLayout->setSpacing (10);

  headingGSF = new QDoubleSpinBox (this);
  headingGSF->setDecimals (1);
  headingGSF->setRange (1.0, 50.0);
  headingGSF->setSingleStep (10.0);
  headingGSF->setValue (options->heading[TRACKLINE_GSF]);
  headingGSF->setWrapping (true);
  headingGSF->setToolTip (tr ("Set the heading limit for GSF files (degrees)"));
  headingGSF->setWhatsThis (headingGSFText);
  ghBoxLayout->addWidget (headingGSF);
  gBoxLayout->addWidget (ghBox);


  QGroupBox *gsBox = new QGroupBox (tr ("Speed"), this);
  QHBoxLayout *gsBoxLayout = new QHBoxLayout;
  gsBox->setLayout (gsBoxLayout);
  gsBoxLayout->setSpacing (10);

  speedGSF = new QDoubleSpinBox (this);
  speedGSF->setDecimals (1);
  speedGSF->setRange (1.0, 50.0);
  speedGSF->setSingleStep (10.0);
  speedGSF->setValue (options->speed[TRACKLINE_GSF]);
  speedGSF->setWrapping (true);
  speedGSF->setToolTip (tr ("Set the speed limit for GSF files (knots)"));
  speedGSF->setWhatsThis (speedGSFText);
  gsBoxLayout->addWidget (speedGSF);
  gBoxLayout->addWidget (gsBox);


  lboxLeftLayout->addWidget (gBox);


  QGroupBox *pBox = new QGroupBox (tr ("POS/SBET/CSF/LAS"), this);
  QHBoxLayout *pBoxLayout = new QHBoxLayout;
  pBox->setLayout (pBoxLayout);
  pBoxLayout->setSpacing (10);

  QGroupBox *phBox = new QGroupBox (tr ("Heading"), this);
  QHBoxLayout *phBoxLayout = new QHBoxLayout;
  phBox->setLayout (phBoxLayout);
  phBoxLayout->setSpacing (10);

  headingPOS = new QDoubleSpinBox (this);
  headingPOS->setDecimals (1);
  headingPOS->setRange (1.0, 50.0);
  headingPOS->setSingleStep (10.0);
  headingPOS->setValue (options->heading[TRACKLINE_POS]);
  headingPOS->setWrapping (true);
  headingPOS->setToolTip (tr ("Set the heading limit for POS/SBET/CSF/LAS files (degrees)"));
  headingPOS->setWhatsThis (headingPOSText);
  phBoxLayout->addWidget (headingPOS);
  pBoxLayout->addWidget (phBox);


  QGroupBox *psBox = new QGroupBox (tr ("Speed"), this);
  QHBoxLayout *psBoxLayout = new QHBoxLayout;
  psBox->setLayout (psBoxLayout);
  psBoxLayout->setSpacing (10);

  speedPOS = new QDoubleSpinBox (this);
  speedPOS->setDecimals (1);
  speedPOS->setRange (50.0, 500.0);
  speedPOS->setSingleStep (10.0);
  speedPOS->setValue (options->speed[TRACKLINE_POS]);
  speedPOS->setWrapping (true);
  speedPOS->setToolTip (tr ("Set the speed limit for POS/SBET/CSF/LAS files (knots)"));
  speedPOS->setWhatsThis (speedPOSText);
  psBoxLayout->addWidget (speedPOS);
  pBoxLayout->addWidget (psBox);


  lboxRightLayout->addWidget (pBox);


  vbox->addWidget (lbox);


  readLASData = new QCheckBox (tr ("Read LAS data instead of header"), this);
  readLASData->setChecked (options->las);
  readLASData->setToolTip (tr ("Read all of the LAS data instead of just the header to compute the MBR"));
  readLASData->setWhatsThis (readLASDataText);
  vbox->addWidget (readLASData);


  registerField ("headingGSF", headingGSF, "value", "valueChanged");
  registerField ("speedGSF", speedGSF, "value", "valueChanged");
  registerField ("headingPOS", headingPOS, "value", "valueChanged");
  registerField ("speedPOS", speedPOS, "value", "valueChanged");
  registerField ("readLASData", readLASData);
}
