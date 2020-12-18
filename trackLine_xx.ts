<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1">
<context>
    <name>LAS_WKT</name>
    <message>
        <location filename="LAS_WKT.cpp" line="175"/>
        <location filename="LAS_WKT.cpp" line="431"/>
        <source>%1 %2 %3 %4 - Error initializing UTM projection!</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="185"/>
        <location filename="LAS_WKT.cpp" line="448"/>
        <source>%1 %2 %3 %4 - Error initializing latlon projection!</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="468"/>
        <location filename="LAS_WKT.cpp" line="693"/>
        <location filename="LAS_WKT.cpp" line="729"/>
        <source>%1 Well-known Text</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="486"/>
        <source>The LAS file &lt;b&gt;%1&lt;/b&gt; is version 1.4.  The &lt;b&gt;global_encoding&lt;/b&gt; field of the LAS header indicates that there is a Coordinate System Well-known Text (WKT) record in the file however, it appears to be missing.  This means that the LAS file does not meet the LAS 1.4 specification.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="495"/>
        <source>The LAS file &lt;b&gt;%1&lt;/b&gt; is version 1.4.  The &lt;b&gt;global_encoding&lt;/b&gt; field of the LAS header indicates that there is not a Coordinate System Well-known Text (WKT) record in the file.  Since the Point Data Record Format for this file is greater than 5, the use of the WKT record is required.  This LAS file does not meet the LAS 1.4 specification.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="505"/>
        <source>The LAS file &lt;b&gt;%1&lt;/b&gt; is version 1.%2.  There are no Variable Length Records (VLR) defined for this file.  According to the LAS 1.%2 specification, a 34735 (GeoKeyDirectoryTag) VLR is required.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="514"/>
        <source>The LAS file &lt;b&gt;%1&lt;/b&gt; has a 34735 Variable Length Record (VLR) but the &lt;b&gt;GTModelTypeGeoKey&lt;/b&gt; isn&apos;t &lt;b&gt;ModelTypeProjected&lt;/b&gt; or &lt;b&gt;ModelTypeGeographic&lt;/b&gt;.  &lt;b&gt;%2&lt;/b&gt; only handles those two types.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="522"/>
        <source>The LAS file &lt;b&gt;%1&lt;/b&gt; is version 1.%2.  The required 34735 (GeoKeyDirectoryTag) Variable Length Record (VLR) is missing.  According to the LAS 1.%2 specification, a 34735 (GeoKeyDirectoryTag) VLR is required</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="530"/>
        <source>The LAS file &lt;b&gt;%1&lt;/b&gt; has a 34735 Variable Length Record (VLR) with the &lt;b&gt;GTModelTypeGeoKey&lt;/b&gt; set to &lt;b&gt;ModelTypeProjected&lt;/b&gt;.  &lt;b&gt;%2&lt;/b&gt; has determined that the &lt;b&gt;Geographic CS Type&lt;/b&gt; is not &lt;b&gt;GCS_NAD83&lt;/b&gt; (4269) or &lt;b&gt;GCS_WGS_84&lt;/b&gt; (4326).  &lt;b&gt;%2&lt;/b&gt; only handles those two types.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="536"/>
        <source>&lt;br&gt;&lt;br&gt;Due to the above listed condition &lt;b&gt;%1&lt;/b&gt; is unable to convert positions for the input LAS data to latitude and longitude.  If you would like to know why the positions are being converted to latitude and longitude you can read &lt;a href=&quot;http://pfmabe.software/a-note-about-utm-vs-latlon/&quot;&gt;this article&lt;/a&gt; on pfmabe.software.&lt;br&gt;&lt;br&gt;This dialog will allow you to enter Well-known Text (WKT) to be used to convert the positions.  WKT for many different areas is available on &lt;a href=&quot;http://spatialreference.org/&quot;&gt;spatialreference.org&lt;/a&gt; (for example, &lt;a href=&quot;http://spatialreference.org/ref/epsg/2451/&quot;&gt;EPSG:2451&lt;/a&gt;).  Only GEOGCS or PROJCS WKT is supported.&lt;br&gt;&lt;br&gt;Simply copy the &lt;b&gt;OGC WKT&lt;/b&gt; that best matches the data in the above LAS file and paste it into the text box below.&lt;br&gt;&lt;br&gt;Do not be overly concerned about whether the WKT is exactly correct for your data.  The Area-Based Editor (ABE) is only used to modify status (e.g. &lt;b&gt;Withheld&lt;/b&gt;, &lt;b&gt;Synthetic&lt;/b&gt;, &lt;b&gt;Key-point&lt;/b&gt;) and/or classification (e.g. &lt;b&gt;Low Vegetation&lt;/b&gt;, &lt;b&gt;Building&lt;/b&gt;, &lt;b&gt;Road Surface&lt;/b&gt;) in the LAS files (when unloaded from ABE).  The positions in the LAS files are not modified.  Because of this, the absolute accuracy of the positions in ABE is not really important.  It is much more important that the positions are accurate relative to each other and fairly accurate in relation to the globe (in order to use Google Earth for external reference).&lt;br&gt;&lt;br&gt;If the data in the LAS file is projected, &lt;b&gt;%1&lt;/b&gt; will convert the input positions to WGS84 latitude and longitude.&lt;br&gt;&lt;br&gt;It is assumed that all LAS files being read for the current run are from the same general area and the WKT used for this file will be used for all subsequent files.&lt;br&gt;&lt;br&gt;If you do not enter WKT data and click the &lt;b&gt;Close&lt;/b&gt; button, &lt;b&gt;%1&lt;/b&gt; will be terminated.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="556"/>
        <source>Click &lt;b&gt;Help&lt;/b&gt; button then click here for an even more verbose explanation</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="572"/>
        <location filename="LAS_WKT.cpp" line="573"/>
        <source>Select a previously used WKT string (hover to see WKT in tool tip)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="617"/>
        <source>Enter the Well-known Text (WKT) for the LAS input file</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="618"/>
        <source>Enter the Well-known Text (WKT) coordinate system definition for the LAS input file</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="619"/>
        <source>Well-known Text (WKT)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="629"/>
        <source>Enter What&apos;s This mode for help</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="635"/>
        <source>Close</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="636"/>
        <source>Discard WKT text, close this dialog, and exit the program</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="640"/>
        <source>Accept</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="641"/>
        <source>Accept the WKT text that has been entered, close this dialog, and process the files</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="693"/>
        <source>The WKT data entered does not appear to be correct and/or supported.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKT.cpp" line="729"/>
        <source>The WKT text input field is empty.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="LAS_WKTHelp.hpp" line="41"/>
        <source>&lt;b&gt;&lt;/b&gt;So, the problem with many LAS files is that the coordinate system is not defined properly.  Even though the LAS specification requires a 34735 (GeoKeyDirectoryTag) Variable Length Record (VLR) many people don&apos;t put one in.  If you&apos;re using LAS 1.4 and you use point data formats above 5 you are required to insert a Well-known Text (WKT) VLR or Extended VLR (eVLR).  Apparently many people think this is a waste of time.  I find that rather interesting, especially with projected data.  For example, I recently saw some data from a LiDAR system in use in Japan that was in LAS 1.4 format using point data format 6.  This requires a WKT VLR or eVLR but there wasn&apos;t one in the file.  The global_encoding field was set to indicate that there was a 34735 VLR. That is an error.  There wasn&apos;t even a 34735 VLR anyway.  Since the file appeared to be UTM what we had was a whole bunch of measurements (northing and easting, presumably in meters) from nowhere (or possibly OZ).&lt;br&gt;&lt;br&gt;Even when people insert the 34735 record they often leave out important information.  For instance, I&apos;ve seen files that proudly proclaim that they are NAD83 UTM but then they don&apos;t put the zone information into the record.  Once again, meters (we hope) from nowhere.&lt;br&gt;&lt;br&gt;Another pet peeve of mine - why do people use any vertical measurement other than meters (or metres if you will)?  Measuring things based on the length of some king&apos;s body parts seems a bit old school.  Wait until you&apos;ve finished processing the data before you convert it to cubits or fathoms or furlongs or feet or yards for the great unwashed masses to gaze upon.  ABE assumes that the input elevations are in meters.  If the data in your LAS file isn&apos;t in meters it doesn&apos;t really matter.  Just look at the pretty numbers and say to yourself &lt;b&gt;&apos;self, that number is really feet even though it says meters&apos;&lt;/b&gt;.  If you&apos;re building PFMs from LAS files I wouldn&apos;t recommend trying to extract (pfmExtract or pfmGeotiff) the data (meaning X, Y, and Z, not validity and/or classification).&lt;br&gt;&lt;br&gt;Now, on to the fun stuff, if you&apos;re not familiar with WKT you can look it up on the interwebs.  To quote Wikipedia &lt;b&gt;&apos;Well-known text (WKT) is a text markup language for representing vector geometry objects on a map, spatial reference systems of spatial objects and transformations between spatial reference systems&apos;&lt;/b&gt;. The world has moved past the GeoKeyDirectoryTag and is moving to WKT. Since this program uses the GDAL/OGR library it only supports projected (PROJCS) or geographic (GEOGCS) coordinate systems.  That&apos;s probably fine since that&apos;s what most people use (the other possibility being (GEOCCS) geocentric).&lt;br&gt;&lt;br&gt;This program will try to decipher the crazy quilt LAS oordinate system information but it won&apos;t try very hard.  If you are using geographic data it will probably make it through fine (unless you&apos;ve completely hosed or forgotten your 34735).  Projected data is much more complicated. In any event, if the program can&apos;t figure it out it will ask you for a WKT describing the coordinate system for your data.  You can find a bunch of WKT over on &lt;a href=&quot;http://spatialreference.org/&quot;&gt;spatialreference.org&lt;/a&gt;.&lt;br&gt;&lt;br&gt;Once you&apos;ve entered one or more WKT definitions the program will try to keep track of the 10 most recently used ones. These will be available in any of the ABE programs that have LAS inputs.  Hopefully you&apos;ll be using the same few for quite a while before you have to change to another area and/or coordinate system.  To see what each recent WKT string looks like just open the combo box on the bottom left and let the cursor hover over each entry.  The tool tip will be the full text of the WKT in human readable form.&lt;br&gt;&lt;br&gt;&lt;b&gt;IMPORTANT NOTE: In the pfmLoad or pfmLoader program, if you input LAS files and have to input WKT to load them, the program will keep track of the WKT and will use it again if you append to the existing PFM.&lt;/b&gt;&lt;br&gt;&lt;br&gt;Jan Depner, 3 May, 2016</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>inputPage</name>
    <message>
        <location filename="inputPage.cpp" line="48"/>
        <source>Input Data Files</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPage.cpp" line="63"/>
        <source>Files</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPage.cpp" line="69"/>
        <location filename="inputPage.cpp" line="119"/>
        <source>Browse</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPage.cpp" line="70"/>
        <source>Add input files to the list</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPage.cpp" line="77"/>
        <source>Directories</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPage.cpp" line="83"/>
        <source>Directory file mask</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPage.cpp" line="90"/>
        <source>Set the file mask for the directory Browse button</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPage.cpp" line="120"/>
        <source>Add input directory contents to the list</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPage.cpp" line="132"/>
        <source>Input file list</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPage.cpp" line="155"/>
        <source>trackLine Input files</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPage.cpp" line="215"/>
        <source>trackLine Input directories, mask = %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPageHelp.hpp" line="40"/>
        <source>&lt;br&gt;&lt;br&gt;The following file formats are accepted by the trackLine program:&lt;br&gt;&lt;br&gt;&lt;ul&gt;&lt;li&gt;GSF (any extension but usually .dNN where NN represents a 2 digit number)&lt;/li&gt;&lt;li&gt;CZMIL CSF (extension .csf)&lt;/li&gt;&lt;li&gt;CHARTS POS/SBET (extension .pos, .out, .POS, .OUT)&lt;/li&gt;&lt;li&gt;LAS (extension .las - reading LAS files will cause the creation of an area file instead of a track file.)&lt;/li&gt;&lt;ul&gt;</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPageHelp.hpp" line="49"/>
        <source>This button allows you to select multiple input files.  You may use this button as many times as needed to define all of the desired input files.  This may also be used in conjunction with the &lt;b&gt;Browse Directories&lt;/b&gt; button.  All selected files are added to the &lt;b&gt;Input files&lt;/b&gt; list.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPageHelp.hpp" line="54"/>
        <source>This button allows you to select multiple input files by specifiying a top level directory.  Using the &lt;b&gt;Directory file mask&lt;/b&gt; field as the filter, all files below the selected directory will be searched for matching files.  These files will be added to the &lt;b&gt;Input files&lt;/b&gt; list.  This may also be used in conjunction with the &lt;b&gt;Browse Files&lt;/b&gt; button.  You may use this button as many times as needed to define all of the desired input files.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPageHelp.hpp" line="61"/>
        <source>This is the file search filter for the &lt;b&gt;Browse Directories&lt;/b&gt; button.  You may select a filter from the existing list or type in your own special filter.  This filter is used in searching directory trees when using the &lt;b&gt;Browse Directories&lt;/b&gt; button.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="inputPageHelp.hpp" line="66"/>
        <source>This is a list of all files that will be input to trackLine program.  You may edit the list or even add files by hand (although why anyone would do this is beyond me).  There is limited text editor functionality available for this list.  Right click to get a menu of functions including undo, redo, cut, paste, and others.  If you make a mistake and add duplicate files using the &lt;b&gt;Browse Directories&lt;/b&gt; button or even the &lt;b&gt;Browse Files&lt;/b&gt; button, fear not.  The input file list is sorted and duplicates are culled out before the trackline generation process is started.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>optionsPage</name>
    <message>
        <location filename="optionsPage.cpp" line="48"/>
        <source>trackLine Options</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPage.cpp" line="60"/>
        <source>Limits</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPage.cpp" line="74"/>
        <location filename="optionsPage.cpp" line="116"/>
        <source>Heading</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPage.cpp" line="85"/>
        <source>Set the heading limit for GSF files (degrees)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPage.cpp" line="91"/>
        <location filename="optionsPage.cpp" line="133"/>
        <source>Speed</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPage.cpp" line="102"/>
        <source>Set the speed limit for GSF files (knots)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPage.cpp" line="111"/>
        <source>POS/SBET/CSF/LAS</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPage.cpp" line="127"/>
        <source>Set the heading limit for POS/SBET/CSF/LAS files (degrees)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPage.cpp" line="144"/>
        <source>Set the speed limit for POS/SBET/CSF/LAS files (knots)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPage.cpp" line="156"/>
        <source>Read LAS data instead of header</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPage.cpp" line="158"/>
        <source>Read all of the LAS data instead of just the header to compute the MBR</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPageHelp.hpp" line="40"/>
        <source>Enter the heading change limit, in degrees, for GSF files.  If the heading of the input data changes by this amount then a new vertex will be added to the output trackline file.  The normal default is 3.0 degrees.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPageHelp.hpp" line="45"/>
        <source>Enter the speed change limit, in knots, for GSF files.  If the speed of the input data exceeds this value then a new vertex will be added to the output trackline file.  The normal default is 20.0 knots.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPageHelp.hpp" line="50"/>
        <source>Enter the heading change limit, in degrees, for POS/SBET/CSF/LAS files.  If the heading of the input data changes by this amount then a new vertex will be added to the output trackline file.  The normal default is 5.0 degrees.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPageHelp.hpp" line="55"/>
        <source>Enter the speed change limit, in knots, for POS/SBET/CSF/LAS files.  If the speed of the input data exceeds this value then a new vertex will be added to the output trackline file.  The normal default is 240.0 knots.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="optionsPageHelp.hpp" line="60"/>
        <source>If you check this box it will cause trackLine to read all of the data in the LAS files to recompute the minimum and maximum bounds of the file prior to comparing it to the cumulative minimums and maximums.  Normally you don&apos;t need to do this because the minimums and maximums in the LAS header are correct.  This option is much slower than just using the values in the header but it is occasionally necessary due to incorrect values in the file headers.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>runPage</name>
    <message>
        <location filename="runPage.cpp" line="48"/>
        <source>Build trackline file</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="runPage.cpp" line="59"/>
        <source>Input file processing progress</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="runPage.cpp" line="67"/>
        <source>Progress of input file loading</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="runPage.cpp" line="74"/>
        <source>Process status</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="runPageHelp.hpp" line="40"/>
        <source>Click this button to start the trackline generation process.  Once you click this button you will not be able to interrupt the process (short of killing it from the operating system).</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="runPageHelp.hpp" line="44"/>
        <source>This area will display information about the trackline file being generated.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>startPage</name>
    <message>
        <location filename="startPage.cpp" line="51"/>
        <source>Introduction</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="startPage.cpp" line="53"/>
        <source>See, it really works!</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="startPage.cpp" line="55"/>
        <source>trackLine is a tool for building an ASCII decimated trackline file and a minimum bounding rectangle (MBR)area file from GSF, CSF, or POS/SBET data.  It can also create an MBR area file from LAS/LAZ files. The resulting files (.trk and/or .are) are viewable in areaCheck or as overlays in pfmView.  UTM LAS/LAZ files will be converted to latitude and longitude using the information in the LAS/LAZ header to determine conversion parameters.&lt;br&gt;&lt;br&gt;&lt;b&gt;IMPORTANT NOTE: Only an area file will be created if only LAS/LAZ files are used as input. Also, the area file will have a 2% cushion added to the boundaries to make sure it covers all data.&lt;/b&gt;&lt;br&gt;&lt;br&gt;Help is available by clicking on the Help button and then clicking on the item for which you want help.  Click &lt;b&gt;Next&lt;/b&gt; to continue or &lt;b&gt;Cancel&lt;/b&gt; to exit.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="startPage.cpp" line="74"/>
        <source>trackline output file</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="startPage.cpp" line="83"/>
        <source>Browse...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="startPage.cpp" line="100"/>
        <source>trackLine Output file</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="startPage.cpp" line="111"/>
        <source>trackLine file (*.trk)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="startPageHelp.hpp" line="40"/>
        <source>This is the output file name.  If the name doesn&apos;t have a .trk extension one will be appended.  You may use the &lt;b&gt;Browse&lt;/b&gt; button to select an existing trackline (.trk) file to be overwritten.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="startPageHelp.hpp" line="44"/>
        <source>Use this button to select an existing trackline (.trk) file to overwrite.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>trackLine</name>
    <message>
        <location filename="trackLine.cpp" line="91"/>
        <source>&amp;Run</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="trackLine.cpp" line="93"/>
        <source>Run the trackline generation process</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="trackLine.cpp" line="250"/>
        <location filename="trackLine.cpp" line="834"/>
        <source>Unable to open output file %1!</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="trackLine.cpp" line="278"/>
        <source>Processing file %1 of %2 - %3</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="trackLine.cpp" line="283"/>
        <source>Progress of input file processing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="trackLine.cpp" line="801"/>
        <source>Completed processing file %1 of %2 - %3</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="trackLine.cpp" line="857"/>
        <source>

Created minimum bounding rectangle area file %1 from input points/LAS bounding rectangles.

</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="trackLine.cpp" line="865"/>
        <source>

Determined %1 trackline points from %2 positions.

</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="trackLineHelp.hpp" line="40"/>
        <source>Pressing this button will begin the gridding process.  The gridding process is not actually a part of this program but is an external program called &lt;b&gt;chrtr&lt;/b&gt; or &lt;b&gt;chrtr2&lt;/b&gt;.  Instead of running the process from this GUI you may save the parameters that you have input by using the &lt;b&gt;Save&lt;/b&gt; button.  You may then run the program from the command line by entering &lt;b&gt;chrtr FILENAME.chp&lt;/b&gt; or &lt;b&gt;chrtr2 FILENAME.chp&lt;/b&gt; where FILENAME.chp is the name of the parameter file that you saved.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="trackLineHelp.hpp" line="47"/>
        <source>Pressing this button will allow you to save the parameters that you have input to this GUI in a parameter file so that you may run the actual gridding program (&lt;b&gt;chrtr&lt;/b&gt; or &lt;b&gt;chrtr2&lt;/b&gt;) from the command line at a later time.  You may enter a new filename or select a preexisting .chp file.  If you enter a new filename you do not have to add the .chp extension as one will be added for you.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
</TS>
