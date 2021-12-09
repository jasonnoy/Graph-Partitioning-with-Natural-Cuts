/**
 * @file: base_def.h
 * @author: hb.zhao
 * @date: 2020/12/11 4:30 下午
 * @copyright: Huolala.cn
 */

#ifndef CPLUS_UTILS_BASE_DEF_H
#define CPLUS_UTILS_BASE_DEF_H

#include <cstdint>

namespace navi {

namespace base {

using uint8_t = ::std::uint8_t;
using int8_t = ::std::int8_t;
using uint16_t = ::std::uint16_t;
using int16_t = ::std::int16_t;
using uint32_t = ::std::uint32_t;
using int32_t = ::std::int32_t;
using uint64_t = ::std::uint64_t;
using int64_t = ::std::int64_t;
using bool_t = bool;

using topo_link_id_t = uint32_t;  // topo link id
using base_node_id_t = uint32_t;  // base node id
using topo_node_id_t = uint32_t;  // base node id
using base_link_id_t = uint32_t;  // base link id
using topo_turn_id_t = uint32_t;  // topo turn id
using siwei_link_id_t = ::uint64_t;      // SW link id

const double PI = 3.1415926535897932384626433832795;
const double EARTH_RADIUS = 6378137;
const double METERS_PER_DEGREE = (EARTH_RADIUS * PI / 180.0);
const double EQUAL_TOLERANCE = 1e-7;

enum log_level{//日志类型定义
        LOG_LEVEL_TRACE=0,//跟踪类型
        LOG_LEVEL_DEBUG=1,//了解系统运行状态
        LOG_LEVEL_INFO=2,//用来反馈系统的当前状态给最终用户
        LOG_LEVEL_WARN=3,//警告类型
        LOG_LEVEL_ERROR=4,//错误类型
        LOG_LEVEL_CRITICAL=5,//重大错误
        LOG_LEVEL_OFF=6,//关闭log
        LOG_LEVEL_PERF=7//系统的性能快照
};

enum data_source {            //图商的枚举
    DATA_SOURCE_NAVINFO = 0,  //四维图新
    DATA_SOURCE_HERE = 1      // here
};

} // base

} // navi

#endif //CPLUS_UTILS_BASE_DEF_H
