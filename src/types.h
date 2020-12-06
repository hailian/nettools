/**
    *
    all types
    made by hailian 
    2020-12-05
    *
**/

#ifndef __hailian_types_h__
#define __hailian_types_h__

#include <boost/function.hpp>

namespace hl{
    class UdpSession;
    typedef boost::shared_ptr<UdpSession > UdpSession_ptr;

}
typedef boost::function<void(hl::UdpSession_ptr ,char *, size_t)> MessageCallback;

#endif