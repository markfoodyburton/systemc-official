/*****************************************************************************

  Licensed to Accellera Systems Initiative Inc. (Accellera) under one or
  more contributor license agreements.  See the NOTICE file distributed
  with this work for additional information regarding copyright ownership.
  Accellera licenses this file to you under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with the
  License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
  implied.  See the License for the specific language governing
  permissions and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  test01.cpp --

  Original Author: Mark Burton, Qualcomm Innovation Center, Inc. 2024

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#include "systemc.h"



SC_MODULE( mod_a )
{


    sc_observer_event e1;
 

    void driver() {
        wait (10, sc_core::SC_MS);std::cout << "sc_time now " << sc_core::sc_time_stamp()<<std::endl;
        wait (15, sc_core::SC_MS);std::cout << "sc_time now " << sc_core::sc_time_stamp()<<std::endl;
        wait (10, sc_core::SC_MS);std::cout << "sc_time now " << sc_core::sc_time_stamp()<<std::endl;
        wait (30, sc_core::SC_MS);std::cout << "sc_time now " << sc_core::sc_time_stamp()<<std::endl;
        wait (10, sc_core::SC_MS);std::cout << "sc_time now " << sc_core::sc_time_stamp()<<std::endl;
      }

    void write( const char* msg )
    {
        cout <<"simulation time" << ":" << sc_time_stamp()
             << " " << msg << endl;
     
    }

    void observer()
    {
      write( "Observer" );
      e1.notify(10, SC_MS );
    }

   
    SC_CTOR( mod_a )
    {
        
        SC_THREAD(driver);
        SC_METHOD( observer );
        sensitive << e1;
                 
    }
};


int
sc_main( int, char*[] )
{
    mod_a a( "a" );
    sc_start(100,SC_MS);

    return 0;
}

