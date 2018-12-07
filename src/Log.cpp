/*
 * Log.cpp
 *
 *  Created on: Dec 6, 2018
 *      Author: cy
 *
 *      https://blog.csdn.net/erlang_hell/article/details/52311786?utm_source=blogxgwz9
 *
 *      JD come across link error for v2s_mt_posix, there is a link to explain that: (2018-Nov-29)
 *
 *      https://stackoverflow.com/questions/23137637/linker-error-while-linking-boost-log-tutorial-undefined-references
 *
 *      https://www.boost.org/doc/libs/1_54_0/libs/log/doc/html/log/rationale/namespace_mangling.html
 */

#include "Log.h"

using namespace boost::log;








BOOST_LOG_ATTRIBUTE_KEYWORD(a_severity, "Severity", trivial::severity_level)







bool init_log_environment(std::string _cfg)
{
    if (!boost::filesystem::exists("./log/"))
    {
        boost::filesystem::create_directory("./log/");
    }
    add_common_attributes();

    register_simple_formatter_factory<trivial::severity_level, char>("Severity");
    register_simple_filter_factory<trivial::severity_level, char>("Severity");

    std::ifstream settings(_cfg);
    if(!settings.is_open()){
    	throw std::runtime_error("could not open logging configuration file");
    	exit(-2);
    }

    try
    {
        init_from_stream(settings);
    }
    catch (const std::exception& e)
    {
        std::cout << "init_logger is fail, read log config file fail. curse: " << e.what() << std::endl;
        exit(-2);
    }
    return true;
}



