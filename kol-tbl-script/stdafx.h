// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include "typedef.hpp"
#include "struct.hpp"
#include "io/FileBase.h"
#include "io/FileReader.h"
#include "io/FileWriter.h"
#include "sqlite\sqlite3.h"


#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <io.h>
#include <fcntl.h>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/algorithm/string.hpp>
#include <boost\unordered_map.hpp>
#include <boost/optional.hpp>
#include <boost/format.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/bind.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "sqlitedb.hpp"
#include "ci_string.hpp"

extern sqlitedb * g_pDB;
