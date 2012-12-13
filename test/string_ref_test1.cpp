/* 
   Copyright (c) Marshall Clow 2012-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#include <iostream>
#include <algorithm>
#include <string>

#include <boost/algorithm/string_ref.hpp>


#include <boost/test/included/test_exec_monitor.hpp>

typedef boost::string_ref string_ref;

//  Should be equal
void interop ( const std::string &str, string_ref ref ) {
//  BOOST_CHECK ( str == ref );
    BOOST_CHECK ( str.size () == ref.size ());
    BOOST_CHECK ( std::equal ( str.begin (),  str.end (),  ref.begin ()));
    BOOST_CHECK ( std::equal ( str.rbegin (), str.rend (), ref.rbegin ()));
    }

//  make sure that substrings work just like strings
void test_substr ( const std::string &str ) {
    const size_t sz = str.size ();
    string_ref ref ( str );
    
//  Substrings at the end
    for ( size_t i = 0; i <= sz; ++ i )
        interop ( str.substr ( i ), ref.substr ( i ));
        
//  Substrings at the beginning
    for ( size_t i = 0; i <= sz; ++ i )
        interop ( str.substr ( 0, i ), ref.substr ( 0, i ));
        
//  All possible substrings
    for ( size_t i = 0; i < sz; ++i )
        for ( size_t j = i; j < sz; ++j )
            interop ( str.substr ( i, j ), ref.substr ( i, j ));    
    }

//  make sure that removing prefixes and suffixes work just like strings
void test_remove ( const std::string &str ) {
    const size_t sz = str.size ();
    std::string work;
    string_ref ref;
    
    for ( size_t i = 1; i <= sz; ++i ) {
      work = str;
      ref  = str;     
      while ( ref.size () >= i ) {
          interop ( work, ref );
          work.erase ( 0, i );
          ref.remove_prefix (i);
          }
      }
    
    for ( size_t i = 1; i < sz; ++ i ) {
      work = str;
      ref  = str;     
      while ( ref.size () >= i ) {
          interop ( work, ref );
          work.erase ( work.size () - i, i );
          ref.remove_suffix (i);
          }
      }
    }

const char *test_strings [] = {
    "",
    "1",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "0123456789",
    NULL
    };
    
int test_main( int , char* [] ) {

    const char **p = &test_strings[0];
    
    while ( *p != NULL ) {
        interop ( *p, *p );
        test_substr ( *p );
    test_remove ( *p );
    
        p++;
        }

    return 0;
    }