/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*             Copyright (C)1998-2019, WWIV Software Services             */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/*                                                                        */
/**************************************************************************/
// Always declare wwiv_windows.h first to avoid collisions on defines.
#include "core/wwiv_windows.h"
#include "bbs/remote_io.h"

#include <string>

#include "core/scope_exit.h"
#include "core/strings.h"
#include "core/wwivport.h"
#include "bbs/remote_socket_io.h"
#include "bbs/ssh.h"

// static
std::string RemoteIO::error_text_;

const std::string RemoteIO::GetLastErrorText() {
#if defined ( _WIN32 )
  char* error_text;
  wwiv::core::ScopeExit on_exit([&error_text] {LocalFree(error_text);});
  
  FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER |
    FORMAT_MESSAGE_FROM_SYSTEM |
    FORMAT_MESSAGE_IGNORE_INSERTS,
    nullptr,
    GetLastError(),
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
    (LPTSTR) &error_text,
    0,
    nullptr
  );
  error_text_.assign(error_text);
#else
  return wwiv::strings::StringPrintf("errno: %d", errno);
#endif
  return error_text_;
}
