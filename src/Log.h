/*
 * Log.h
 *
 *  Created on: Dec 6, 2018
 *      Author: cy
 */

#ifndef LOG_H_
#define LOG_H_

/* JD:   2018Nov30
 *
 * Need to define the macro so that correct library will be linked to application.
 * Otherwise you need to configure the application to use static Boost library.
 *
 * https://www.boost.org/doc/libs/1_68_0/libs/log/doc/html/log/installation/config.html
 *
 * https://www.boost.org/doc/libs/1_68_0/more/getting_started/unix-variants.html#link-your-program-to-a-boost-library
 */

#ifndef BOOST_ALL_DYN_LINK
#define BOOST_ALL_DYN_LINK
#endif


#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/utility/setup/filter_parser.hpp>
#include <boost/log/sources/severity_logger.hpp>





bool init_log_environment(std::string _cfg);



#endif /* LOG_H_ */
