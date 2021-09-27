#ifndef  __SW_BASETYPES_H_
#define  __SW_BASETYPES_H_

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
enum road_level_t
{
    // 作业中
    RL_WORKINGONIT = 0,
    //高速公路
    RL_HIGHWAY = 1,
    //城市快速路
    RL_CITYHIGHWAY = 2,
    //国道
    RL_COUNTRYWAY = 3,
    //省道
    RL_PROVINCEWAY = 4,
    //县道
    RL_TOWNWAY = 6,
    //乡镇村道
    RL_VILLAGEWAY = 7,
    //其他道路
    RL_OTHERWAY = 8,
    //非引导道路
    RL_NOTGUIDEWAY = 9,
    //步行道路
    RL_WALKWAY = 10,
    //人渡
    RL_FORDWAY = 11,
    //轮渡
    RL_FERRYWAY = 13,
    //自行车专用道
    RL_CYCLEWAY = 14
};

/** 道路属性 */
enum road_type_t
{
    //未调查
    RT_NOINVESTIGATE = 0,
    //无属性
    RT_NOTYPE = 1,
    //其他
    RT_OTHERS = 2,
    // IC
    RT_IC = 10,
    // JCT
    RT_JCT = 11,
    // SA
    RT_SA = 12,
    // PA
    RT_PA = 13,
    //全封闭道路
    RT_CLOSEDWAY = 14,
    //匝道
    RT_RAMP = 15,
    //跨线天桥
    RT_LINEJUMPRUNWAY = 16,
    //跨线地道
    RT_CROSSLINETUNNEL = 17,
    //私道
    RT_BYLANE = 18,
    //步行街
    RT_WALKSTREET = 20,
    //过街天桥
    RT_OVERPASS = 21,
    //公交专用道
    RT_BUSWAY = 22,
    //自行车道
    RT_CYCLEWAY = 23,
    //跨线立交桥
    RT_CROSSLINEOVERPASS = 24,
    //桥
    RT_BRIDGE = 30,
    //隧道
    RT_TUNNEL = 31,
    //立交桥
    RT_FLYOVER = 32,
    //环岛
    RT_RINGWAY = 33,
    //辅路
    RT_SLAVEWAY = 34,
    //调头口
    RT_FORUTURN = 35,
    // POI连接路
    RT_POILINKWAY = 36,
    //提前右转
    RT_FORRIGHT = 37,
    //提前左转
    RT_FORLEFT = 38,
    //主辅路出入口
    RT_FORENTEREXITMAIN = 39,
    //交叉点内link
    RT_CROSSLINK = 50,
    //未定义交通区域
    RT_UNDEFINEDAREA = 51,
    //区域内道路
    RT_INAREA = 52,
    //停车场出入口连接路
    RT_FORENTEREXITPARKING = 53,
    //虚拟链接路
    RT_VIRTUALLINKWAY = 54,
    //风景线路
    RT_SCENIC = 60,
    //停车位引导路
    RT_PARKINGWAY = 80,
    //上下线分离
    RT_SEPERATEWAY = 81,
    //移动式桥
    RT_TRAVELLINGBRIDGE = 82,
    // 车辆测试路段
    RT_TESTWAY = 83,
    // 驾照考试路段
    RT_DRIVINGTEST = 84,
    // 借道左转
    RT_LEFTBYWAY = 85
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
    PV_MINI_VAN = 2,                  //微型货车
    PV_LIGHT_TRUCK = 3,               //轻型货车
    PV_MEDIUM_TRUCK = 4,              //中型货车
    PV_HEAVY_TRUCK = 5,               //重型货车
    PV_FULLY_MOUNTED_TRACTOR = 6,     //全挂牵引车
    PV_SEMITRAILER_TRACTOR = 7,       //半挂牵引车
    PV_SEMITRAILER = 8,               //半挂车
    PV_TRAILER = 9,                   //全挂车
    PV_SPECIAL_PURPOSE_VEHICLE = 10,  //专用汽车
    PV_OTHER_TRUCKS = 11              //其他货车
};

/** 车牌限行中的本地/外地车牌类型枚举 */
enum pr_attr_t
{
    PA_NONLOCAL_WITH_PASS = 1,           //外地车（有通行证）
    PA_NONLOCAL_WITHOUT_PASS = 2,        //外地车（无通行证）
    PA_LOCAL_WITH_PASS = 3,              //本地车（有通行证）
    PA_LOCAL_WITHOUT_PASS = 4,           //本地车（无通行证）
    PA_LOCAL_LIMIT = 5,                  //受限本地车（如沪 C）
    PA_NOT_HONGKONG = 6,                 //非香港车牌（含粤牌）
    PA_NOT_MACAO = 7,                    //非澳门车牌（含粤牌）
    PA_LOCAL_TEM_LICENSING_LIMIT = 8,    //临牌限行（本地）
    PA_NONLOCAL_TEM_LICENSING_LIMIT = 9  //临牌限行（外地）
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
    PC_YELLOW_GREEN = 6  //黄绿牌
};

/** 车牌限行中的能源类型枚举 */
enum pr_enegry_t
{
    PE_DIESEL_OIL = 1,       //柴油
    PE_OIL_ELECTRICITY = 2,  //油电
    PE_ELECTRICITY = 3,      //纯电
    PE_GASOLINE = 4,         //汽油
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

const uint32_t SW_MAX_SUB_NODE_NUM = 32;   //复合路口最大子点数目
const uint32_t SW_MAX_PASS_LINK_NUM = 32;  //最大的passlink数目

const uint32_t SW_MAX_ROAD_PROP_NUM = 8;     //最大道路属性数目
const uint32_t SW_MAX_NAME_LEN = 128;        //名字字符最大长度
const uint32_t SW_MAX_ADMIN_NAME_LEN = 512;  //三级行政区划名字字符最大长度

const uint32_t HLL_ID_MAX_LEN = 34;  // HLL ID最大长度

typedef uint32_t cr_id_t;                   //定义条件交规ID类型
const cr_id_t INVALID_CR_ID = (cr_id_t)-1;  //非法的cr_id作为初始化的值

const int32_t INVALID_GEO_POINT = -360 * 100000;

const uint32_t INVALID_CR_INFO_WEIGHT_RESTRICT = 0;
const uint32_t INVALID_CR_INFO_AXCNT_RESTRICT = 0;
const uint32_t INVALID_CR_INFO_HIGH_RESTRICT = 0;
const uint32_t INVALID_CR_INFO_LENGTH_RESTRICT = 0;
const uint32_t INVALID_CR_INFO_WIDTH_RESTRICT = 0;
const uint32_t INVALID_CR_INFO_SPEED_RESTRICT = 0;

struct geo_point_t {
    int32_t longitude;  //经度,  NTU 单位为1/100000度
    int32_t latitude;   //纬度,  NTU 单位为1/100000度
    bool operator==(const geo_point_t& geo_point) {
        return abs(geo_point.longitude - longitude) <= 1 && 
        abs(geo_point.latitude - latitude) <= 1;
    }
    geo_point_t() : longitude(INVALID_GEO_POINT), latitude(INVALID_GEO_POINT) {}
    geo_point_t(int32_t lon, int32_t lat) : longitude(lon), latitude(lat) {}
};


struct node_info_t {
    uint64_t sw_node_id;                        // sw node ID
    uint32_t main_node_id;                      //路口主点base node ID,路口标识为1,2,3时有效
    uint32_t sub_node_id[SW_MAX_SUB_NODE_NUM];  //路口子点base node ID列表
    uint8_t cross_flag;     // 0:不是路口的节点;1,复合路口子点; 2,单一路口;3,复合路口主点
    uint8_t light_flag;     // 0:无红绿灯;1:有红绿灯
    uint8_t sub_node_num;   //路口标识为复合路口主节点时有效,标识子点个数
    uint8_t toll_flag;      //是否收费,综合了C表中的信息
    geo_point_t geo_point;  //几何信息
    uint8_t hll_node_id[HLL_ID_MAX_LEN];  // HLL node ID

    node_info_t() {
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

struct link_info_t {
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

    uint8_t hll_link_id[HLL_ID_MAX_LEN];  // HLL link ID

    link_info_t() {
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
        length = 0;
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
        memset(hll_link_id, 0, HLL_ID_MAX_LEN);
    }

    bool is_inner() {
        return inner_link != 0;
    }
};

#endif