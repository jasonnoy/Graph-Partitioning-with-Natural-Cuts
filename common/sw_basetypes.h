/**
 * @file: sw_basetype.h
 * @author: black.li@huolala.cn
 * @date: 2020/12/7 19:22
 * @copyright: Huolala.cn
 */

#ifndef CPLUS_UTILS_SW_BASETYPE_H
#define CPLUS_UTILS_SW_BASETYPE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

namespace navi
{
namespace base
{
const uint32_t SW_MAX_SUB_NODE_NUM = 35;   //复合路口最大子点数目
const uint32_t SW_MAX_PASS_LINK_NUM = 32;  //最大的passlink数目

const uint32_t SW_MAX_ROAD_PROP_NUM = 8;     //最大道路属性数目
const uint32_t SW_MAX_NAME_LEN = 128;        //名字字符最大长度
const uint32_t SW_MAX_ADMIN_NAME_LEN = 512;  //三级行政区划名字字符最大长度

//四维数据34位足够，here数据需要64位，但是目前没用，所以截断为34
const uint32_t HLL_ID_MAX_LEN = 34;  // HLL ID最大长度
const uint32_t PR_MANO_DESC_MAX_LEN = 2560; //pr_mano_info_t中的限行描述最大长度

typedef uint32_t cr_id_t;                   //定义条件交规ID类型
const cr_id_t INVALID_CR_ID = (cr_id_t)-1;  //非法的cr_id作为初始化的值

const int32_t INVALID_GEO_POINT = -360 * 100000;

const uint32_t LON_LAT_COEFF = 100000;  // hll longitude latitude to wgs84;

// details as:https://huolala.feishu.cn/docs/doccn0TdemYbHkpZ82DyYAdLZ6e#
const uint32_t INVALID_CR_INFO_WEIGHT_RESTRICT = 0;
const uint32_t INVALID_CR_INFO_AXCNT_RESTRICT = 0;
const uint32_t INVALID_CR_INFO_AXLOAD_RESTRICT = 0;
const uint32_t INVALID_CR_INFO_HIGH_RESTRICT = 0;
const uint32_t INVALID_CR_INFO_LENGTH_RESTRICT = 0;
const uint32_t INVALID_CR_INFO_WIDTH_RESTRICT = 0;
const uint32_t INVALID_CR_INFO_SPEED_RESTRICT = 0;

const uint32_t INVALID_PERIOD_INFO_TIME_TRAMP = -1;  //时间段结构中无效的时间戳
const int16_t INVALID_PERIOD_INFO_MINUTE = -1;       //时间段结构中无效的分钟信息
const int8_t INVALID_PERIOD_INFO_WEEK = 0;          //时间段结构中无限的周信息
const int8_t INVALID_PERIOD_INFO_TYPE = 0;           //时间段结构中有效规制信息的初始值

/** 路线规划等级 */
enum class road_function_class_t : uint8_t
{
    /// 1
    CN_RPC_1 = 1,
    /// 2
    CN_RPC_2 = 2,
    /// 3
    CN_RPC_3 = 3,
    /// 4
    CN_RPC_4 = 4,
    /// 5
    CN_RPC_5 = 5
};

/** 道路等级 */
enum road_level_t {
    RL_NULL = -1,       //原始数据为NULL
    RL_WORKINGONIT = 0, // 作业中
    RL_HIGHWAY = 1,     //高速公路
    RL_CITYHIGHWAY = 2, //城市快速路
    RL_COUNTRYWAY = 3,  //国道
    RL_PROVINCEWAY = 4, //省道
    RL_TOWNWAY = 6,     //县道
    RL_VILLAGEWAY = 7,  //乡镇村道
    RL_OTHERWAY = 8,    //其他道路
    RL_NOTGUIDEWAY = 9, //非引导道路
    RL_WALKWAY = 10,    //步行道路
    RL_FORDWAY = 11,    //人渡
    RL_FERRYWAY = 13,   //轮渡
    RL_CYCLEWAY = 14    //自行车专用道
};

/** 道路属性 */
enum road_type_t {
    // 国内21Q3版本数据删除值域"24 跨线立交桥"。
    RT_NOINVESTIGATE = 0,        //未调查
    RT_NOTYPE = 1,               //无属性
    RT_OTHERS = 2,               //其他
    RT_IC = 10,                  //IC
    RT_JCT = 11,                 //JCT
    RT_SA = 12,                  //服务区(SA)
    RT_PA = 13,                  //停车区(PA)
    RT_CLOSEDWAY = 14,           //全封闭道路
    RT_RAMP = 15,                //匝道
    RT_LINEJUMPRUNWAY = 16,      //跨线天桥
    RT_CROSSLINETUNNEL = 17,     //跨线地道
    RT_BYLANE = 18,              //私道
    RT_WALKSTREET = 20,          //步行街
    RT_OVERPASS = 21,            //过街天桥
    RT_BUSWAY = 22,              //公交专用道
    RT_CYCLEWAY = 23,            //自行车道
    RT_BRIDGE = 30,              //桥
    RT_TUNNEL = 31,              //隧道
    RT_FLYOVER = 32,             //立交桥
    RT_RINGWAY = 33,             //环岛
    RT_SLAVEWAY = 34,            //辅路
    RT_FORUTURN = 35,            //调头口
    RT_POILINKWAY = 36,          //POI连接路
    RT_FORRIGHT = 37,            //提前右转
    RT_FORLEFT = 38,             //提前左转
    RT_FORENTEREXITMAIN = 39,    //主辅路出入口
    RT_CROSSLINK = 50,           //交叉点内link
    RT_UNDEFINEDAREA = 51,       //未定义交通区域
    RT_INAREA = 52,              //区域内道路
    RT_FORENTEREXITPARKING = 53, //停车场出入口连接路
    RT_VIRTUALLINKWAY = 54,      //车导虚拟链接路
    RT_SCENIC = 60,              //风景路线
    RT_PARKINGWAY = 80,          //停车位引导道路
    RT_SEPERATEWAY = 81,         //上下线分离
    RT_TRAVELLINGBRIDGE = 82,    //移动式桥
    RT_TESTWAY = 83,             //车辆测试路段
    RT_DRIVINGTEST = 84,         //驾照考试路段
    RT_LEFTBYWAY = 85,           //借道左转
    RT_TRUCK_LANE = 86           //卡车专用道
};

/** 道路通行车辆类型 */
enum road_vehicle_t
{
    //客车
    RV_AUTO = 0,
    //配送卡车
    RV_DELIVERYTRUCK = 1,
    //运输卡车
    RV_TRANSPORTTRUCK = 2,
    //步行者
    RV_WALKER = 3,
    //自行车
    RV_BICYCLE = 4,
    //摩托车
    RV_MOTOR = 5,
    //机动脚踏两用车
    RV_MOTORBICYCLE = 6,
    //急救车
    RV_EMERVEH = 7,
    //出租车
    RV_TAXIS = 8,
    //公交车
    RV_BUS = 9,
    //工程车
    RV_CONSTRUCTIONTRUCK = 10,
    //本地车辆
    RV_LOCALVEHICLE = 11,
    //自用车辆
    RV_SELFVEHICLE = 12,
    //多人乘坐车辆
    RV_CARPOOL = 13,
    //军车
    RV_MILITARYVEHICLE = 14,
    //有拖车的车
    RV_TRAILER = 15,
    //私营公共汽车
    RV_SELFBUS = 16,
    //农用车
    RV_AGRIMOTOR = 17,
    //载有易爆品的车辆
    RV_EXPLOSIVEVEHICLE = 18,
    //载有水污染品的车辆
    RV_WATERPOLLUTION = 19,
    //载有其它危险品的车辆
    RV_OTHERDANGER = 20,
    //电车
    RV_TRAM = 21,
    //轻轨
    RV_LIGHTRAIL = 22,
    //校车
    RV_SCHOOLBUS = 23,
    //四轮驱动车
    RV_FOURVEHICLE = 24,
    //装有防雪链的车
    RV_SNOWVEHICLE = 25,
    //邮政车
    RV_POSTALCAR = 26,
    //槽罐车
    RV_TANKCAR = 27,
    //残疾人车
    RV_DISABLEDCAR = 28,
    //预留1
    RV_RESERVE1 = 29,
    //预留2
    RV_RESERVE2 = 30,
    //预留3
    RV_RESERVE3 = 31
};

/** 道路宽度 */
enum road_width_t
{
    RW_VERYNARROW = 0,  //<=3.0m
    RW_NARROW = 1,      // 3.0-5.5m
    RW_NORMAL = 2,      // 5.5-13.0m
    RW_BROAD = 3        //>13m
};

/** 坡度类型 */
enum slope_type_t
{
    ST_NOINVESTIGATE = 0,  //未调查
    ST_HORIZONTAL = 1,     //水平
    ST_UP = 2,             //上坡
    ST_DOWN = 3            //下坡
};

/** cross_flag 路口节点类型 */
enum cross_flag_t
{
    NOT_ROAD_NODE = 0,  //不是路口的点
    SUB_NODE = 1,       //复合路口子点
    SIMPLE_NODE = 2,    //简单路口
    COMPLEX_NODE = 3,   //复杂路口

};

/** link 通行方向 */
enum link_direction_t
{
    LD_UNINVESTIGATED = 0,  //未调查(默认双向)
    LD_BIDIRECTIONAL = 1,   //双向通行
    LD_FORWARD = 2,         //顺方向
    LD_BACKWARD = 3         //逆方向
};

/** 道路是否收费 */
enum link_toll_t {
    LT_UNINVESTIGATED = 0,  //未调查
    LT_TOLL = 1,            //收费
    LT_FREE = 2,            //免费
    LT_FREE_SEGMENT = 3     //收费道路免费区间
};

/** 点限速 限速条件 */
enum ps_dependent_t
{
    PD_NONE = 0,        //无
    PD_RAIN = 1,        //雨天
    PD_SNOW = 2,        //雪天
    PD_FOG = 3,         //雾天
    PD_SCHOOL = 6,      //学校
    PD_TIME = 10,       //时间限制
    PD_SEASON = 12,     //季节时段
    PD_DANGEROUS = 31,  //危险品
    PD_TRAILER = 32,    //拖挂车
    PD_WEIGHT = 33,     //总重量
    PD_AXLE = 34        //总轴数
};

/** 车牌限行中的车辆类型枚举 */
enum pr_vehicle_t
{
    PV_PASSENGER_CAR = 1,             //客车
    PV_MINI_VAN = 2,                  //微型货车
    PV_LIGHT_TRUCK = 3,               //轻型货车
    PV_MEDIUM_TRUCK = 4,              //中型货车
    PV_HEAVY_TRUCK = 5,               //重型货车
    PV_FULLY_MOUNTED_TRACTOR = 6,     //全挂牵引车
    PV_SEMITRAILER_TRACTOR = 7,       //半挂牵引车
    PV_SEMITRAILER = 8,               //半挂车
    PV_TRAILER = 9,                   //全挂车
    PV_PANEL_VAN = 10,                //厢式货车
    PV_LOW_SPEED_TRUCK = 11,          //低速货车
    PV_PICK_UP_TRUCK = 12,            //皮卡车
    PV_ENCLOSED_TRUCK = 13,           //封闭式货车
    PV_DUMP_TRUCK = 14,               //自卸货车
    PV_TANK_TRUCK = 15,               //罐式货车
    PV_FLATBED_CARGO_TRUCK = 16,      //平板货车
    PV_TAILGATE_TRUCK = 17,           //栏板货车
    PV_BARN_TRUCK = 18,               //仓栅式货车
    PV_MIDDLE_AXLE_TRAILER = 19,      //中置轴挂车
    PV_CONTAINER_TRUCK = 20,          //集装箱车
    PV_DANGEROUS_CHEMICAL_TRANSPORT_VEHICLE = 21, //危化品运输车
    PV_UNKNOW = 22
};

/** 车牌限行中的排除车辆类型枚举 */
enum pr_spec_vt_t : int32_t {
    PSV_PANEL_VAN = 1,             //厢式货车
    PSV_PICK_UP_TRUCK = 2,         //皮卡车
    PSV_ENCLOSED_TRUCK = 3,        //封闭式货车
    PSV_DUMP_TRUCK = 4,            //自卸货车
    PSV_LOW_SPEED_TRUCK = 5,       //低速货车
    PSV_FULLY_MOUNTED_TRACTOR = 6, //全挂牵引车
    PSV_SEMITRAILER_TRACTOR = 7,   //半挂牵引车
    PSV_SEMITRAILER = 8,           //半挂车
    PSV_TRAILER = 9,               //全挂车
    PSV_MIDDLE_AXLE_TRAILER = 10   //中置轴挂车
};

/** 车牌限行中的本地/外地车牌类型枚举 */
enum pr_attr_t {
    PA_NONLOCAL_WITH_PASS = 1,          //外地车（有通行证）
    PA_NONLOCAL_WITHOUT_PASS = 2,       //外地车（无通行证）
    PA_LOCAL_WITH_PASS = 3,             //本地车（有通行证）
    PA_LOCAL_WITHOUT_PASS = 4,          //本地车（无通行证）
    PA_LOCAL_LIMIT = 5,                 //受限本地车（如沪 C）
    PA_NOT_HONGKONG = 6,                //非香港车牌（含粤牌）
    PA_NOT_MACAO = 7,                   //非澳门车牌（含粤牌）
    PA_LOCAL_TEM_LICENSING_LIMIT = 8,   //临牌限行（本地）
    PA_NONLOCAL_TEM_LICENSING_LIMIT = 9 //临牌限行（外地）
};

/** 车牌限行中的车牌尾号类型枚举 */
enum pr_tail_char_t
{
    PT_0 = 0,                 //限行尾号0
    PT_1 = 1,                 //限行尾号1
    PT_2 = 2,                 //限行尾号2
    PT_3 = 3,                 //限行尾号3
    PT_4 = 4,                 //限行尾号4
    PT_5 = 5,                 //限行尾号5
    PT_6 = 6,                 //限行尾号6
    PT_7 = 7,                 //限行尾号7
    PT_8 = 8,                 //限行尾号8
    PT_9 = 9,                 //限行尾号9
    PT_ALL_ALPHABET = 10,     //全部英文字母
    PT_SINGLE_ALPHABET = 11,  //排序号为奇数的英文字母
    PT_EVEN_ALPHABET = 12,    //排序号为偶数的英文字母
};

/** 车牌限行中的车牌颜色类型枚举 */
enum pr_platecolor_t
{
    PC_BLUE = 1,         //蓝牌
    PC_YELLOW = 2,       //黄牌
    PC_BLACK = 3,        //黑牌
    PC_WHITE = 4,        //白牌
    PC_GREEN = 5,        //绿牌
    PC_YELLOW_GREEN = 6, //黄绿牌
    PC_UNKNOW
};

/** 车牌限行中的能源类型枚举 */
enum pr_enegry_t
{
    PE_DIESEL_OIL = 1,       //柴油
    PE_OIL_ELECTRICITY = 2,  //油电
    PE_ELECTRICITY = 3,      //纯电
    PE_GASOLINE = 4,         //汽油
    PE_UNKNOW
};

/** 车牌限行中的油气排放标准类型枚举 */
enum pr_emis_stand_t
{
    PS_NOT_LIMIT = 0,  //未限制
    PS_LEVEL_1 = 1,    //国 I
    PS_LEVEL_2 = 2,    //国 II
    PS_LEVEL_3 = 3,    //国 III
    PS_LEVEL_4 = 4,    //国 IV
    PS_LEVEL_5 = 5,    //国 V
};

/** 车牌限行中的时间类型枚举 */
enum pr_datetype_t
{
    PD_CONTINUOUS = 1,        //连续时间
    PD_MONDAY = 2,            //星期一
    PD_TUESDAY = 3,           //星期二
    PD_WEDNESDAY = 4,         //星期三
    PD_THURSDAY = 5,          //星期四
    PD_FRIDAY = 6,            //星期五
    PD_SATURDAY = 7,          //星期六
    PD_SUNDAY = 8,            //星期天
    PD_SINGLE_DAY = 9,        //单日
    PD_EVEN_DAY = 10,         //双日
    PD_DATE_END_0 = 11,       //日期以 0 结尾
    PD_DATE_END_1 = 12,       //日期以 1 结尾
    PD_DATE_END_2 = 13,       //日期以 2 结尾
    PD_DATE_END_3 = 14,       //日期以 3 结尾
    PD_DATE_END_4 = 15,       //日期以 4 结尾
    PD_DATE_END_5 = 16,       //日期以 5 结尾
    PD_DATE_END_6 = 17,       //日期以 6 结尾
    PD_DATE_END_7 = 18,       //日期以 7 结尾
    PD_DATE_END_8 = 19,       //日期以 8 结尾
    PD_DATE_END_9 = 20,       //日期以 9 结尾
    PD_WORKINGDAY = 21,       //工作日
    PD_WEEKEND = 22,          //双休日
    PD_WEEKEND_SINGLE = 23,   //双休日单号
    PD_WEEKEND_EVEN = 24,     //双休日双号
    PD_HOLIDAY = 25,          //节假日
    PD_HOLIDAY_SINGLE = 26,   //节假日单号
    PD_HOLIDAY_EVEN = 27,     //节假日双号
    PD_WINTER_VOCATION = 28,  //寒假
    PD_SUMMER_VOCATION = 29,  //暑假
    PD_SPRING = 30,           //春季
    PD_SUMMER = 31,           //夏季
    PD_AUTUMN = 32,           //秋季
    PD_WINTER = 33            //东季
};

/** 车牌限行中的排除时间类型枚举 */
enum pr_spec_flag_t
{
    PF_SATURDAY = 1,         //星期六
    PF_SUNDAY = 2,           //星期天
    PF_HOLIDAY = 3,          //节假日
    PF_SPECIAL_DATE = 4,     //特定日期，如：31 号
    PF_WINTER_VOCATION = 5,  //寒假
    PF_SUMMER_VOCATION = 6,  //暑假
    PF_SPRING = 7,           //春季
    PF_SUMMER = 8,           //夏季
    PF_AUTUMN = 9,           //秋季
    PF_WINTER = 10           //东季
};

/*
 * NOTICE:
 * 四维编译输出的所有文件格式均为对应的结构体数组，相应的数组下标也称为base [xxx] id
 * 例如node结构数组的下标为base node id, link结构的数组下标为base link id
 * 这些base [xxx] id在整个导航内部中会作为默认ID取代siwei id来使用
 */

struct geo_point_t
{
    int32_t longitude;  //经度,  NTU 单位为1/100000度
    int32_t latitude;   //纬度,  NTU 单位为1/100000度
    bool operator == (const geo_point_t& geo_point)
    {
        return abs(geo_point.longitude - longitude) <= 1
               && abs(geo_point.latitude - latitude) <= 1;
    }
    geo_point_t() : longitude(INVALID_GEO_POINT), latitude(INVALID_GEO_POINT)
    {
    }
    geo_point_t(int32_t other_longitude, int32_t other_latitude) : longitude(other_longitude), latitude(other_latitude)
    {
    }
};

/** 行政区名称信息 */
struct admin_info_t
{
    uint8_t admin_name[SW_MAX_NAME_LEN];             //行政区名称
    uint8_t full_admin_name[SW_MAX_ADMIN_NAME_LEN];  //三级行政区名称

    admin_info_t()
    {
        memset(admin_name, 0, SW_MAX_NAME_LEN);
        memset(full_admin_name, 0, SW_MAX_ADMIN_NAME_LEN);
    }
};

/** 时间段结构 */
struct period_info_t {
    uint32_t start_time_tramp;  //开始时间戳,对应原来的年月日,若年不存在,则为2000年
    uint32_t end_time_tramp;    //结束时间戳,对应原来的年月日,若年不存在,则为2000年
    int16_t start_minute;       //开始的分钟信息,对应原来的时分,时*60转化为分
    int16_t end_minute;         //结束的分钟信息,对应原来的时分,时*60转化为分
    //上述四个为两组,必定成对出现
    int8_t week;                //周信息,对应原来的周,二进制七位为六五四三二一日(例如周一的二进制为0000010)
    int8_t type;                //有效规制信息,用来判断是否有效,二进制五位为年月日分周(例如年的二进制位10000)
    period_info_t() {
        start_time_tramp = INVALID_PERIOD_INFO_TIME_TRAMP;
        end_time_tramp = INVALID_PERIOD_INFO_TIME_TRAMP;
        start_minute = INVALID_PERIOD_INFO_MINUTE;
        end_minute = INVALID_PERIOD_INFO_MINUTE;
        week = INVALID_PERIOD_INFO_WEEK;
        type = INVALID_PERIOD_INFO_TYPE;
    }
};

/** 点信息 */
struct node_info_all_t
{
    uint64_t sw_node_id;                        // sw node ID
    uint32_t main_node_id;                      //路口主点base node ID,路口标识为1,2,3时有效
    uint32_t sub_node_id[SW_MAX_SUB_NODE_NUM];  //路口子点base node ID列表
    uint8_t cross_flag;     // 0:不是路口的节点;1,复合路口子点; 2,单一路口;3,复合路口主点
    uint8_t light_flag;     // 0:无红绿灯;1:有红绿灯
    uint8_t sub_node_num;   //路口标识为复合路口主节点时有效,标识子点个数
    uint8_t toll_flag;      //是否收费,综合了C表中的信息
    geo_point_t geo_point;  //几何信息
    uint8_t hll_node_id[HLL_ID_MAX_LEN];  // HLL node ID

    node_info_all_t()
    {
        sw_node_id = 0;
        main_node_id = 0;
        memset(sub_node_id, 0, SW_MAX_SUB_NODE_NUM * sizeof(uint32_t));
        cross_flag = 0;
        light_flag = 0;
        sub_node_num = 0;
        toll_flag = 0;
        memset(hll_node_id, 0, HLL_ID_MAX_LEN);
    }
};
//目前只有topo编译中使用完整node
#ifdef TOPO
typedef node_info_all_t node_info_t;
#else
struct node_info_t
{
    geo_point_t geo_point;  //几何信息

    node_info_t()
    {
    }
};
#endif
/** 线信息 */
struct link_info_t
{
    /** 基础属性 */
    uint64_t sw_link_id;                     // sw link ID
    uint32_t start_node_id;                  //画线方向起点 base node ID
    uint32_t end_node_id;                    //画线方向终点 base node ID
    road_type_t kind[SW_MAX_ROAD_PROP_NUM];  //道路属性列表
    uint8_t kind_num;                        //属性数目
    road_level_t road_level;                 //道路等级
    uint8_t direction;   //通行方向:0未调查;1双向;2顺方向单向通行;3逆方向单向通行
    road_width_t width;  //道路宽度
    uint8_t toll;        //是否收费
    uint8_t inner_link;  //是否是复合节点内的内部link
    uint8_t path_class;  //功能等级
    uint8_t speed_class;  //速度等级，目前沿用四维的等级列表
    uint32_t length;           //路段长度，单位m
    uint32_t vehicles;         //可通行车辆，用位表示
    uint32_t geo_num;          //形状点个数
    uint32_t geo_start_index;  //形状点起始索引

    /** 货车属性 */
    uint16_t forward_res_high;     //顺方向限高 单位cm
    uint16_t forward_res_width;    //顺方向限宽 单位cm
    uint16_t forward_res_spdlmt;   //顺方向货车限速 单位 100m/h
    uint32_t forward_res_weigh;    //顺方向限重 单位kg
    uint32_t forward_res_axload;   //顺方向限轴重 单位kg
    uint16_t backward_res_high;    //逆方向限高 单位cm
    uint16_t backward_res_width;   //逆方向限宽 单位cm
    uint16_t backward_res_spdlmt;  //逆方向货车限速 单位 100m/h
    uint32_t backward_res_weigh;   //逆方向限重 单位kg
    uint32_t backward_res_axload;  //逆方向限轴重 单位kg

    int32_t s_angle;  //起点方位角(0-360度,起点为四维snode)
    int32_t e_angle;  //终点方位角(0-360度,终点为四维enode)

    /** 车牌限行信息 */
    uint32_t plate_res_index;  // 车牌限行信息起始索引
    uint16_t plate_res_num;    // 车牌限行信息个数

    uint8_t hll_link_id[HLL_ID_MAX_LEN];  // HLL link ID

    link_info_t()
    {
        sw_link_id = 0;
        start_node_id = 0;
        end_node_id = 0;
        memset(kind, 0, SW_MAX_ROAD_PROP_NUM * sizeof(road_type_t));
        kind_num = 0;
        road_level = road_level_t::RL_WORKINGONIT;
        direction = 0;
        width = road_width_t::RW_VERYNARROW;
        toll = 0;
        inner_link = 0;
        path_class = 0;
        speed_class = 0;
        vehicles = 0;
        length = 0;
        vehicles = 0;
        geo_num = 0;
        geo_start_index = 0;
        forward_res_high = INVALID_CR_INFO_HIGH_RESTRICT;
        forward_res_width = INVALID_CR_INFO_WIDTH_RESTRICT;
        forward_res_spdlmt = INVALID_CR_INFO_SPEED_RESTRICT;
        forward_res_weigh = INVALID_CR_INFO_WEIGHT_RESTRICT;
        forward_res_axload = INVALID_CR_INFO_WEIGHT_RESTRICT;
        backward_res_high = INVALID_CR_INFO_HIGH_RESTRICT;
        backward_res_width = INVALID_CR_INFO_WIDTH_RESTRICT;
        backward_res_spdlmt = INVALID_CR_INFO_SPEED_RESTRICT;
        backward_res_weigh = INVALID_CR_INFO_WEIGHT_RESTRICT;
        backward_res_axload = INVALID_CR_INFO_WEIGHT_RESTRICT;
        s_angle = 0;
        e_angle = 0;
        plate_res_index = 0;
        plate_res_num = 0;
        memset(hll_link_id, 0, HLL_ID_MAX_LEN);
    }
};

/** 线信息 */
struct link_info_all_t
{
    /** 基础属性 */
    uint64_t sw_link_id;                     // sw link ID
    uint32_t start_node_id;                  //画线方向起点 base node ID
    uint32_t end_node_id;                    //画线方向终点 base node ID
    road_type_t kind[SW_MAX_ROAD_PROP_NUM];  //道路属性列表
    uint8_t kind_num;                        //属性数目
    road_level_t road_level;                 //道路等级
    uint8_t direction;         //通行方向:0未调查;1双向;2顺方向单向通行;3逆方向单向通行
    road_width_t width;        //道路宽度
    uint8_t toll;              //是否收费
    uint8_t inner_link;        //是否是复合节点内的内部link
    uint8_t path_class;        //功能等级
    uint8_t const_st;          //供用信息
    uint8_t through;           //是否可以穿行
    uint8_t special;           //特殊交通类型
    uint8_t uf_lag;            //城市标识
    uint8_t lane_num_s2e;      // S2E的车道数
    uint8_t lane_num_e2s;      // E2S的车道数
    uint8_t lane_num;          //车道数
    uint8_t detail_city;       //详细开发区域
    uint8_t speed_class;       //速度等级，目前沿用四维的等级列表
    uint16_t spd_lmt_s2e;      //起点到终点速度限制
    uint16_t spd_lmt_e2s;      //终点到起点速度限制
    uint32_t admin_code_l;     //左侧行政区编码
    uint32_t admin_code_r;     //右侧行政区编码
    uint32_t length;           //路段长度，单位m
    uint32_t vehicles;         //可通行车辆，用位表示
    uint32_t geo_num;          //形状点个数
    uint32_t geo_start_index;  //形状点起始索引

    /** 货车属性 */
    uint16_t forward_res_high;     //顺方向限高 单位cm
    uint16_t forward_res_width;    //顺方向限宽 单位cm
    uint16_t forward_res_spdlmt;   //顺方向货车限速 单位 100m/h
    uint32_t forward_res_weigh;    //顺方向限重 单位kg
    uint32_t forward_res_axload;   //顺方向限轴重 单位kg
    uint16_t backward_res_high;    //逆方向限高 单位cm
    uint16_t backward_res_width;   //逆方向限宽 单位cm
    uint16_t backward_res_spdlmt;  //逆方向货车限速 单位 100m/h
    uint32_t backward_res_weigh;   //逆方向限重 单位kg
    uint32_t backward_res_axload;  //逆方向限轴重 单位kg

    /** 车牌限行信息 */
    uint32_t plate_res_index;  // 车牌限行信息起始索引
    uint16_t plate_res_num;    // 车牌限行信息个数

    /** 综合其他表得到的信息*/
    uint8_t road_name[SW_MAX_NAME_LEN];  //路段名称
    uint16_t admin_l_name_len;           // 左行政区名称长度（字节长度）
    uint16_t admin_r_name_len;           // 右行政区名称长度（字节长度）
    uint32_t admin_l_name_index;         // 左行政区名称起始索引
    uint32_t admin_r_name_index;         // 右行政区名称起始索引

    uint16_t full_admin_l_name_len;    // 左侧三级行政区名称长度（字节长度）
    uint16_t full_admin_r_name_len;    // 右侧三级行政区名称长度（字节长度）
    uint32_t full_admin_l_name_index;  // 左侧三级行政区名称起始索引
    uint32_t full_admin_r_name_index;  // 右侧三级行政区名称起始索引

    int32_t s_angle;  //起点方位角(0-360度,起点为四维snode)
    int32_t e_angle;  //终点方位角(0-360度,终点为四维enode)

    uint8_t elevated;  //是否为高架路 (0不是;1是)

    uint8_t hll_link_id[HLL_ID_MAX_LEN];  // HLL link ID

    link_info_all_t() {
        sw_link_id = 0;
        start_node_id = 0;
        end_node_id = 0;
        memset(kind, 0, SW_MAX_ROAD_PROP_NUM * sizeof(road_type_t));
        kind_num = 0;
        road_level = road_level_t::RL_WORKINGONIT;
        direction = 0;
        width = road_width_t::RW_VERYNARROW;
        toll = 0;
        inner_link = 0;
        path_class = 0;
        const_st = 0;
        through = 0;
        special = 0;
        uf_lag = 0;
        lane_num_s2e = 0;
        lane_num_e2s = 0;
        lane_num = 0;
        detail_city = 0;
        speed_class = 0;
        spd_lmt_s2e = 0;
        spd_lmt_e2s = 0;
        admin_code_l = 0;
        admin_code_r = 0;
        length = 0;
        vehicles = 0;
        geo_num = 0;
        geo_start_index = 0;
        forward_res_high = INVALID_CR_INFO_HIGH_RESTRICT;
        forward_res_width = INVALID_CR_INFO_WIDTH_RESTRICT;
        forward_res_spdlmt = INVALID_CR_INFO_SPEED_RESTRICT;
        forward_res_weigh = INVALID_CR_INFO_WEIGHT_RESTRICT;
        forward_res_axload = INVALID_CR_INFO_WEIGHT_RESTRICT;
        backward_res_high = INVALID_CR_INFO_HIGH_RESTRICT;
        backward_res_width = INVALID_CR_INFO_WIDTH_RESTRICT;
        backward_res_spdlmt = INVALID_CR_INFO_SPEED_RESTRICT;
        backward_res_weigh = INVALID_CR_INFO_WEIGHT_RESTRICT;
        backward_res_axload = INVALID_CR_INFO_WEIGHT_RESTRICT;
        plate_res_index = 0;
        plate_res_num = 0;
        memset(road_name, 0, SW_MAX_NAME_LEN);
        admin_l_name_len = 0;
        admin_r_name_len = 0;
        admin_l_name_index = 0;
        admin_r_name_index = 0;
        full_admin_l_name_len = 0;
        full_admin_r_name_len = 0;
        full_admin_l_name_index = 0;
        full_admin_r_name_index = 0;
        s_angle = 0;
        e_angle = 0;
        elevated = 0;
        memset(hll_link_id, 0, HLL_ID_MAX_LEN);
    }
};

/** 交规信息 */
struct traffic_rule_info_t
{
    uint32_t node_id;                          // base node ID
    uint32_t inlink_id;                        //进入base link ID
    uint32_t outlink_id;                       //退出base link ID
    cr_id_t cr_id;                             //条件限制ID
    uint32_t from_truck_rule;                  //该条交规是否来自于货车交规表(0:否;1:是)
    uint32_t pass_link_num;                    //禁止的中间路段数目
    uint32_t pass_link[SW_MAX_PASS_LINK_NUM];  //禁止的中间路段base link ID
    uint8_t hll_rule_id[HLL_ID_MAX_LEN];       // 货拉拉RULE ID

    traffic_rule_info_t()
    {
        node_id = 0;
        inlink_id = 0;
        outlink_id = 0;
        cr_id = INVALID_CR_ID;
        from_truck_rule = 0;
        pass_link_num = 0;
        memset(pass_link, 0, SW_MAX_PASS_LINK_NUM * sizeof(uint32_t));
        memset(hll_rule_id, 0, HLL_ID_MAX_LEN);
    }
};

/** 条件交规信息 */
struct cr_info_t
{
    //通用条件限制
    uint16_t vp_dir;         //方向:0未调查;1双向;2顺方向;3逆方向
    uint8_t vehcl_type[36];  //限制车辆类型 例如：道路不允许客车和自行车通行，则车辆类型表达为
                             // 10001000000000000000000000000000000
    period_info_t period[11];  //具体限制时间
    uint8_t period_num;       //具体限制时间个数

    //货车条件限制
    //限高和限宽是或的关系,违反一项即不允许通行
    //时间段、限重、轴重、轴数、拖挂车限制、本外埠限制之间是且的关系，均违反时不允许通行，只违反部分时，是允许通行的
    uint32_t res_high;    //限高 单位cm
    uint32_t res_width;   //限宽 单位cm
    uint32_t res_weight;  //车辆限重 单位kg
    uint32_t res_axload;  //轴重限制 单位kg
    int32_t res_axcnt;  //轴数限制 (负数表示限制该数值及以下轴数的车辆;正数表示限制该数值及以上轴数的车辆)
    uint8_t res_trail;      //拖挂车限制(0:不单独限制拖挂车;1:单独限制拖挂车)
    uint8_t res_out;        //外埠限制(0:不应用;1:仅限制外埠车辆;2:仅限制本埠车辆)
    uint8_t truck_type[3];  //卡车类型.3位0/1表示否/是.从右向左,第1位轻微型;第2位中型;第3位重型.空表示适用于所有类型卡车

    uint8_t hll_rule_id[HLL_ID_MAX_LEN];  // 货拉拉RULE ID

    cr_info_t()
    {
        vp_dir = 0;
        period_num = 0;
        memset(vehcl_type, 0, 36);
        res_high = INVALID_CR_INFO_HIGH_RESTRICT;
        res_width = INVALID_CR_INFO_WIDTH_RESTRICT;
        res_weight = INVALID_CR_INFO_WEIGHT_RESTRICT;
        res_axload = INVALID_CR_INFO_WEIGHT_RESTRICT;
        res_axcnt = INVALID_CR_INFO_AXCNT_RESTRICT;
        res_trail = 0;
        res_out = 0;
        memset(truck_type, 0, 3);
        memset(hll_rule_id, 0, HLL_ID_MAX_LEN);
    }
};

/** 坡度信息 */
struct slope_info_t
{
    uint32_t node_id;     // base Node ID
    uint32_t outlink_id;  //退出base link ID
    slope_type_t slope;   //坡度

    slope_info_t()
    {
        node_id = 0;
        outlink_id = 0;
        slope = slope_type_t::ST_NOINVESTIGATE;
    }
};

/** 大门信息(只取passage=0,即:紧急车辆进入) */
struct gate_info_t
{
    uint32_t inlink_id = 0;  //进入base link ID
    uint32_t outlink_id = 0;  //退出base link ID
    uint32_t node_id = 0;     // base node ID
    gate_info_t(){}
    gate_info_t(const uint32_t in_id, const uint32_t out_id, const uint32_t n_id):inlink_id(in_id),outlink_id(out_id),node_id(n_id){}
};

/** 叉口信息 */
struct fork_info_t
{
    uint32_t inlink_id;
    uint32_t outlink_id;
    uint8_t type;  // 5:叉口

    fork_info_t()
    {
        inlink_id = 0;
        outlink_id = 0;
        type = 0;
    }
};

/** 顺行信息 */
struct direct_info_t
{
    uint32_t inlink_id;
    uint32_t outlink_id;
    uint8_t type;  // 2:顺行
    uint8_t flag;  // 0-未验证; 1-实地顺行; 2-理论顺行

    direct_info_t()
    {
        inlink_id = 0;
        outlink_id = 0;
        type = 0;
        flag = 0;
    }
};

/** poi信息 */
struct poi_info_t
{
    uint8_t side;                   // POI与引导link的位置关系
    uint16_t kind;                  //种类代码
    uint32_t link_id;               //引导线号
    uint64_t poi_id;                // POI标识
    geo_point_t geo_point;          //经纬度
    uint8_t name[SW_MAX_NAME_LEN];  // poi的名称,需要从Fname中查找

    poi_info_t()
    {
        side = 0;
        kind = 0;
        link_id = 0;
        memset(name, 0, SW_MAX_NAME_LEN);
    }
};

/** 危险标志牌 */
struct trfc_sign_info_t
{
    uint32_t inlink_id = 0;          //进入线base ID
    uint32_t node_id = 0;            //节点base ID
    uint8_t type = 0;                //标牌类型
    uint32_t valid_dist = 0;         //有效距离
    uint32_t pre_dist = 0;           //提前预告距离
    uint64_t cr_id = INVALID_CR_ID;  //条件限制号码
};

/** IC(出口名称) */
struct ic_info_t
{
    uint64_t id;                               // IC序号
    uint32_t node_id;                          //进入base node点号
    uint32_t inlink_id;                        //进入base link ID
    uint32_t outlink_id;                       //退出base link ID
    uint32_t pass_link_num;                    //通过线ID数量
    uint32_t pass_link[SW_MAX_PASS_LINK_NUM];  //通过线base link ID
    geo_point_t geo_point;                     //经纬度位置信息
    uint8_t name[SW_MAX_NAME_LEN];             // IC 名称,从Fname中查找

    ic_info_t()
    {
        id = 0;
        node_id = 0;
        inlink_id = 0;
        outlink_id = 0;
        pass_link_num = 0;
        memset(pass_link, 0, SW_MAX_PASS_LINK_NUM * sizeof(uint32_t));
        memset(name, 0, SW_MAX_NAME_LEN);
    }
};

/** 方面名称 */
struct dr_info_t
{
    uint64_t id;                               // DR序号
    uint32_t node_id;                          //进入base node点号
    uint32_t inlink_id;                        //进入base link线号
    uint32_t outlink_id;                       //退出base link线号
    uint32_t pass_link_num;                    //通过线ID数量
    uint32_t pass_link[SW_MAX_PASS_LINK_NUM];  //通过线base link ID
    uint8_t type;                              //方面类型
    geo_point_t geo_point;                     //经纬度位置信息
    uint8_t name[SW_MAX_NAME_LEN];             // DR 名称,从Fname中查找

    dr_info_t()
    {
        id = 0;
        node_id = 0;
        inlink_id = 0;
        outlink_id = 0;
        pass_link_num = 0;
        memset(pass_link, 0, SW_MAX_PASS_LINK_NUM * sizeof(uint32_t));
        type = 0;
        memset(name, 0, SW_MAX_NAME_LEN);
    }
};

/** 摄像头 */
struct camera_info_t
{
    uint8_t kind;           //类型
    uint8_t kind_up;        //类型大分类.1:限速电子眼;4:区间测速电子眼;7:违章电子眼
    uint8_t speed_limit;    //限速值
    uint8_t location;       //方位.1:正前方;2:左方;3:右方
    uint8_t road_type;      //主辅路.1:主路;2:辅路
    uint8_t level;          //高度.1:高架桥上;2:高架桥下
    uint8_t direction;      //作用方向.2:顺方向;3:逆方向
    uint8_t from_truck;     //是否是货车电子眼(0:否;1:是)
    uint16_t angle;         //照射方向
    uint32_t link_id;       // base link ID
    geo_point_t geo_point;  //经纬度位置信息
    uint8_t hll_camera_id[HLL_ID_MAX_LEN];  // 货拉拉RULE ID

    camera_info_t()
    {
        kind = 0;
        kind_up = 0;
        speed_limit = 0;
        location = 0;
        road_type = 0;
        level = 0;
        direction = 0;
        from_truck = 0;
        angle = 0;
        link_id = 0;
        memset(hll_camera_id, 0, HLL_ID_MAX_LEN);
    }
};

/** 点限速 */
struct point_speed_t
{
    uint32_t link_id = 0;                                   // 关联link
    uint32_t alink_id = 0;                                  // 实际起作用的link
    uint32_t speed_limit = INVALID_CR_INFO_SPEED_RESTRICT;  // 最高限速值 单位：0.1km/h
    ps_dependent_t depend = ps_dependent_t::PD_NONE;        // 限速条件
    uint8_t direction = 0;                                  // 0-未调查; 2-顺方向; 3-逆方向
    uint8_t type = 0;                                       // 0-普通; 3-特定条件
    uint8_t speed_flag = 0;                                 // 限速标志：0-限速开始; 1-限速解除
};

/** 车牌限行的条件限行信息 */
struct pr_mano_info_t
{
    uint32_t admin_code = 0;                               //行政区编码
    pr_vehicle_t vehicle_type[22];                         //车辆类型
    uint32_t vehicle_type_num = 0;                         //车辆类型个数
    uint8_t local_plate[100];                              //本地受限车牌
    pr_attr_t attr_type[10];                               //本外地规则限制
    uint32_t attr_type_num = 0;                            //本外地规则限制个数
    uint8_t temp_plate = 0;                                //临牌转换
    uint8_t temp_p_num = 0;                                //临牌对应数字
    uint8_t char_switch = 0;                               //字母转换
    uint8_t char_to_num = 0;                               //字母对应数字
    pr_tail_char_t tail_char[16];                          //限行尾号
    uint32_t tail_char_num = 0;                            //限行尾号个数
    pr_platecolor_t plate_color[8];                        //车牌颜色
    uint32_t plate_color_num = 0;                          //车牌颜色个数
    pr_enegry_t energy_type[4];                            //能源类型
    uint32_t energy_type_num = 0;                          //能源类型个数
    pr_emis_stand_t emis_stand[8];                         //油气排放标准
    uint32_t emis_stand_num = 0;                           //油气排放标准个数
    int16_t res_length = INVALID_CR_INFO_LENGTH_RESTRICT;  //车长限制 单位：cm
    int16_t res_width = INVALID_CR_INFO_WIDTH_RESTRICT;    //车宽限制 单位：cm
    int16_t res_hight = INVALID_CR_INFO_HIGH_RESTRICT;     //车高限制 单位：cm
    int32_t res_mload = INVALID_CR_INFO_WEIGHT_RESTRICT;   //车载限重 单位：kg
    int32_t res_axload = INVALID_CR_INFO_WEIGHT_RESTRICT;  //限制轴重 单位：kg
    int16_t res_axcnt = INVALID_CR_INFO_AXCNT_RESTRICT;    //限制轴数
    time_t start_date;                                     //开始时间
    time_t end_date;                                       //结束时间
    pr_datetype_t date_type[36];                           //限行时间类型
    uint32_t date_type_num = 0;                            //限行时间类型个数
    period_info_t time[5];                                 //时间
    uint8_t time_num = 0;                                  //时间个数
    pr_spec_flag_t spec_flag[12];                          //排除日期
    uint32_t spec_flag_num = 0;                            //排除日期个数
    uint8_t spec_plate[104];                               //排除不限行车牌号
    uint8_t description[PR_MANO_DESC_MAX_LEN];             //文字描述

    pr_mano_info_t()
    {
        memset(vehicle_type, 0, 22 * sizeof(pr_vehicle_t));
        memset(local_plate, 0, 100);
        memset(attr_type, 0, 10 * sizeof(pr_attr_t));
        memset(tail_char, 0, 16 * sizeof(pr_tail_char_t));
        memset(plate_color, 0, 8 * sizeof(pr_platecolor_t));
        memset(energy_type, 0, 4 * sizeof(pr_enegry_t));
        memset(emis_stand, 0, 8 * sizeof(pr_emis_stand_t));
        start_date = 0;
        end_date = 0;
        memset(date_type, 0, 36 * sizeof(pr_datetype_t));
        memset(spec_flag, 0, 12 * sizeof(pr_spec_flag_t));
        memset(spec_plate, 0, 104);
        memset(description, 0, PR_MANO_DESC_MAX_LEN);
    }
};

/** 车牌限行的节假日信息 */
struct pr_holiday_t
{
    uint8_t spec_flag;    // 3-节假日; 4-特定日期（如每月31号）
    int32_t year;
    int32_t mon;
    int32_t day;

    pr_holiday_t()
    {
        spec_flag = 0;
        year = 0;
        mon = 0;
        day = 0;
    }
};

/** 面状限行信息 */
struct plateres_surface_info_t
{
    uint8_t hll_surface_id[HLL_ID_MAX_LEN]; // 限行面ID
    uint32_t plateres_index;    // 限行信息起始id
    uint16_t plateres_num;      // 限行信息个数
    uint32_t surface_link_index;    // 限行link起始id 
    uint32_t surface_link_num;      // 限行link个数
    uint32_t point_index;           // 限行面顶点起始id
    uint32_t point_num;             // 限行面顶点个数
};

/** 面状限行link信息 */
struct plateres_surface_linkid_t
{
    uint32_t link_id;    // 限行linkid
};


/** 货车禁停路段 */
struct np_road_t
{
    uint32_t link_id;     // 关联的base link ID
    uint16_t direction;   // 方向：0:无方向标识(默认值); 1:双方向; 2:顺方向; 3:逆方向
    uint8_t period[150];  // 时间段

    np_road_t()
    {
        link_id = 0;
        direction = 0;
        memset(period, 0, 150);
    }
};

// record navi metadata
struct navi_metadata_t
{
    ::std::string version;

    navi_metadata_t()
    {
        version = "";
    }
};

}  // namespace base

}  // namespace navi

#endif  // CPLUS_UTILS_SW_BASETYPE_H
