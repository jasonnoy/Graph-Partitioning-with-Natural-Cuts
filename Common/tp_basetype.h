/**
 * @file: tp_basetype.h
 * @author: black.li@huolala.cn
 * @date: 2020/12/8 20:59
 * @copyright: Huolala.cn
 */

#ifndef CPLUS_UTILS_TP_BASETYPE_H
#define CPLUS_UTILS_TP_BASETYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include "sw_basetype.h"
#include "base_def.h"
namespace navi {

namespace base {

const uint32_t TP_MAX_TRANS_LINK_NUM = 17;  //一个topo link最多对应的原始link数量
const double TP_TURN_LINK_RATIO = 1.01;     //topo link和topo turn的数量比值(经验值)
const uint32_t TP_MAX_PLATERES_NUM = 5;        //一个topo link最多对应面状限行数量

enum turn_type_t {
    NULL_ACT = 1,       //直行
    TURN_FRIGHT = 2,    //右前
    TURN_RIGHT = 3,     //右转
    TURN_BRIGHT = 4,    //右后
    TURN_ROUND = 5,     //调头
    TURN_BLEFT = 6,     //左后
    TURN_LEFT = 7,      //左转
    TURN_FLEFT = 8      //左前
};

enum class tp_link_type_t : uint8_t {
    ORIGIN_LINK = 0,            //不包含转向信息的原始link
    COMPLEX_NODE_LINK = 1,      //包含转向信息的复合路口topo link
    SIMPLE_NODE_LINK = 2,       //包含转向信息的简单路口topo link
    TRAFFIC_RULE_LINK = 3,      //包含交规(或分时段交规)的topo link
    MERGED_LINK = 4,            //前向合并后的topo link
    MC_RULE_INSERTED_LINK = 5   //因跨路口交规而插入的link
};

/** topo node结构 */
struct topo_node_t {
    uint32_t base_node_id;      //对应的base node id
};

/** topo turn结构 */
struct topo_turn_t {
    uint8_t cross_flag;         //0:不是路口的节点;1,复合路口; 2,单一路口;
    uint8_t light_flag;         //0:无红绿灯;1:有红绿灯
    uint16_t node_link_num;     //结点关联的base link数量
    turn_type_t turn_type;      //转向类型
    uint8_t in_is_reverse;      //进入link通行方向是否与画线方向相反(仅对双向路生效)
    uint8_t out_is_reverse;     //退出link通行方向是否与画线方向相反(仅对双向路生效)
    uint32_t in_link_id;        //进入base link id
    uint32_t out_link_id;       //退出base link id
    uint32_t cross_length;      //路口交叉点内link长度(m)
};

/** topo 交规结构 */
struct topo_traffic_rule_t {
    uint32_t from_truck_rule;   //是否来自于货车交规(0:否;1:是)
    cr_id_t cr_id;              //条件限制ID(无条件限制时默认是INVALID_CR_ID)

    topo_traffic_rule_t() {
        from_truck_rule = 0;
        cr_id = INVALID_CR_ID;
    }

    bool operator == (const topo_traffic_rule_t &other) const {
        return (cr_id == other.cr_id) && (from_truck_rule == other.from_truck_rule);
    }

    bool operator < (const topo_traffic_rule_t &other) const {
        if (cr_id < other.cr_id) {
            return true;
        }
        else if (cr_id == other.cr_id &&
                from_truck_rule < other.from_truck_rule) {
            return true;
        }

        return false;
    }
};

/** topo link结构 */
struct topo_link_t {
    tp_link_type_t tp_link_type;        //拓扑link类型
    uint16_t topo_turn_num;     //拓扑转向数量
    uint16_t base_link_num;     //topo link对应的原始link数量
    uint32_t topo_traffic_rule_idx;     //在topo_traffic_rule_t结构数组中的索引
    uint32_t topo_traffic_rule_num;     //topo交规数量
    uint32_t tp_snode_id;       //起点topo node id
    uint32_t tp_enode_id;       //终点topo node id
    uint32_t outlink_id;        //topo link的退出base link id
    uint32_t topo_turn_idx;     //在topo_turn_t结构数组中的索引
    uint8_t* is_reverse;  //topo link是否与画线方向相反(仅对双向路生效)
    uint32_t* base_link;  //topo link对应的原始link ID序列
    uint32_t plateres_index[TP_MAX_PLATERES_NUM];    //面状限行数据起始索引
    uint32_t plateres_num[TP_MAX_PLATERES_NUM];      //面状限行数据个数

    topo_link_t(tp_link_type_t type, uint16_t turn_num, uint16_t link_num, uint32_t traf_idx,
                uint32_t traf_num, uint32_t snode_id, uint32_t enode_id, uint32_t olink_id,
                uint32_t tp_turn_idx, uint8_t* reverse, uint32_t* link, const uint32_t* pla_idx, const uint32_t* pla_num)
                : tp_link_type(type), topo_turn_num(turn_num), base_link_num(link_num), topo_traffic_rule_idx(traf_idx),
                  topo_traffic_rule_num(traf_num), tp_snode_id(snode_id), tp_enode_id(enode_id), outlink_id(olink_id),
                  topo_turn_idx(tp_turn_idx), is_reverse(reverse), base_link(link)
    {
        memcpy(plateres_index, pla_idx, sizeof(plateres_index));
        memcpy(plateres_num, pla_num, sizeof(plateres_num));
    }
    topo_link_t()
    {
        tp_link_type = tp_link_type_t::ORIGIN_LINK;
        topo_turn_num = 0;
        base_link_num = 0;
        topo_traffic_rule_idx = 0;
        topo_traffic_rule_num = 0;
        tp_snode_id = 0;
        tp_enode_id = 0;
        outlink_id = 0;
        topo_turn_idx = 0;
        is_reverse = nullptr;
        base_link = nullptr;
        memset(plateres_index, 0, sizeof(plateres_index));
        memset(plateres_num, 0, sizeof(plateres_num));
    }
};
struct topo_link_head_t
{
    uint32_t total_topo_link;
    uint32_t max_vecte_id;
    uint32_t total_base_link;
    std::vector<topo_link_t> topo_link_vec;
    std::vector<uint32_t> base_link_vec;
    std::vector<uint8_t> reverse_flag_vec;
};

struct plateres_link_info_t
{
    uint32_t from_link_id;      // 限行fromlinkid
    uint32_t to_link_id;        // 限行tolinkid
    uint32_t plateres_index;    // 限行数据索引
    uint32_t plateres_num;      // 限行数据个数
    uint32_t sur_id;            // 限行面索引
    plateres_link_info_t(uint32_t flink_id = 0, uint32_t tlink_id = 0, uint32_t plares_index = 0, uint32_t plares_num = 0, uint32_t id = 0) 
        : from_link_id(flink_id),to_link_id(tlink_id),plateres_index(plares_index),plateres_num(plares_num),sur_id(id) {}        
};

struct edge_weight_t
{
    uint32_t s_node_ = -1;
    uint32_t e_node_ = -1;
    uint32_t weight_ = -1;
    edge_weight_t() = default;
    edge_weight_t(uint32_t s_node,uint32_t e_node,uint32_t weight)
    {
        s_node_ = s_node;
        e_node_ = e_node;
        weight_ = weight;
    }
};

struct topo_link_head_ch_t
{
    uint32_t total_topo_link;
    uint32_t max_vertex_id;
    edge_weight_t topo_link_weight;

};

} //end base

} //end navi

#endif //CPLUS_UTILS_TP_BASETYPE_H
