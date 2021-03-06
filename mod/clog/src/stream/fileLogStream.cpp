#include "fileLogStream.hpp"

namespace wrd {

    WRD_DEF_ME(fileLogStream)
    typedef std::string string;

    me::fileLogStream() {}
    me::fileLogStream(const string& new_path) : stream(), _path(new_path) {}

    const char* me::getName() const { return "fileLogStream"; }

    wbool me::setPath(const string& new_path) {
        rel();
        _path = new_path;
        return false;
    }

    const string& me::getPath() const { return _path; }

    wbool me::dump(const char* message) {
        if(!isInit()) return true;
        if(super::dump(message)) return true;

        _file.open(_path.c_str(), std::fstream::out | std::fstream::app);
        _file << message << "\n";
        _file.close();
        return false;
    }

}
