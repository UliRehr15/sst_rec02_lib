# sst_rec02_lib

sstRec02Lib - Library for working with records

This lib based on idea "STASH" from bruce eckels book "thinking in c++".

I take this idea as base for small record management system.

This library should be build with QT 5 and qt creator 3.0.

Structure of coding projects should be:

.. [libs] <BR>
   [sstRec02Lib]<BR>
   [Doxygen_ouput]

September 2015, Hanover, Germany, Uli Rehr

Versions <BR>
20150915: 2.0 Inertial check in from sstRec01 Version 1.6
          Rename class, Rename class files <BR>
          Remove first read/write interface <BR>
20150920: 2.1 extend i/o functions with writeRec (at position) <BR>
          Test folder checked in <BR>
20150923: 2.2 Changed record indexing from 0..n-1 to 1..n <BR>
20151001: 2.3 Added vector memory for buffering reading / writing <BR>
20151009: 2.4 Added additional cargo packet system for every record <BR>
          Define one or more cargo systems for every table record <BR>
          Store inside cargo packet more data, which are not user record data <BR>
          Set user record data as one system cargo packet <BR>
20151016: 2.5 Added system cargo packet for every record <BR>
          record new/changed date/time stamp available
          Delete/Mark functions added.
