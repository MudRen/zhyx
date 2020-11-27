// group_questd.c
// edit by smallfish

inherit F_DBASE;

// #pragma optimize
// #pragma save_binary

#include <ansi.h>
#include <command.h>
#include <npc/name.h>
#include <npc/chinese.c>
#include <npc/japanese.c>
#include <npc/european.c>
#include <npc/masia.c>
#include <npc/indian.c>

#define IDLE 3600
#define MAX_MOVED       5

mapping levels = ([
//      combat_exp   skill_level
        200000      : 100,               // level 1
        200000      : 100,               // level 2
        200000      : 100,               // level 3
        800000      : 125,               // level 4
        800000      : 125,               // level 5
        800000      : 125,               // level 6
        1000000     : 150,               // level 7
        1000000     : 150,               // level 8
        1000000     : 150,               // level 9
        2500000     : 250,               // level 10
        2500000     : 250,               // level 11
        2500000     : 250,               // level 12
        5000000     : 350,               // level 13
        5000000     : 350,               // level 14
        9000000     : 450,               // level 15
        15000000    : 500,               // level 16
        17000000    : 550,               // level 17
]);

mapping family = ([
        "������"   : ({ "/d/shaolin/zoulang1","/d/shaolin/hsyuan1",
                       "/d/shaolin/luohan1","/d/shaolin/luohan5",
                       "/d/shaolin/guangchang4","/d/shaolin/zoulang8",
                       "/d/shaolin/wuchang2","/d/shaolin/banruo2",
                       "/d/shaolin/bagua2","/d/shaolin/zhulin4", }),
        "�䵱��"   : ({ "/d/wudang/wdroad1","/d/wudang/gyroad1",
                       "/d/wudang/jindian","/d/wudang/shanlu4",
                       "/d/wudang/wuyaling","/d/wudang/zixiaogate",
                       "/d/wudang/taizipo", }),
        "ȫ���"   : ({ "/d/quanzhen/shanlu4","/d/quanzhen/shijie7",
                       "/d/quanzhen/houshan","/d/quanzhen/datang3", }),
        "��ɽ��"   : ({ "/d/huashan/buwei1","/d/huashan/qunxianguan",
                       "/d/huashan/songling1", }),
        "ѩɽ��"   : ({ "/d/xueshan/hubian1","/d/xueshan/chang",}),
        "���չ�"   : ({ "/d/lingjiu/changl1","/d/lingjiu/liangong",
                       "/d/lingjiu/huayuan","/d/lingjiu/changl6",}),
        "������"   : ({ "/d/emei/jinding","/d/emei/woyunan",
                       "/d/emei/hcazhengdian","/d/emei/xiaolu1", }),
        "�һ���"   : ({ "/d/taohua/road1","/d/taohua/daojufang", }),
        "������"   : ({ "/d/shenlong/damen","/d/shenlong/wuchang", }),
        "��Ĺ��"   : ({ "/d/gumu/zhenting","/d/gumu/qianting", }),
        "������"   : ({ "/d/xingxiu/xxh1","/d/xingxiu/xxh2", }),
        "��ң��"   : ({ "/d/xiaoyao/qingcaop","/d/xiaoyao/xiaodao4", }),
        "Ѫ����"   : ({ "/d/xuedao/shandong2","/d/xuedao/syabi", }),
        "Ľ������" : ({ "/d/yanziwu/shuwu","/d/yanziwu/yimen", }),
        "�������" : ({ "/d/guanwai/xiaowu","/d/guanwai/xiaoyuan",}),
        "���ϻ���" : ({ "/d/dali/neitang","/d/dali/chahua7",
                       "/d/dali/chahua3","/d/dali/wfdating", }),
        "ŷ������" : ({ "/d/baituo/dating","/d/baituo/huayuan",
                       "/d/baituo/houyuan", }),
]);

static mapping place = ([
        "��������": ({
                        "/d/beijing/cagc_e","/d/beijing/caroad_e1",
                        "/d/beijing/caroad_e2","/d/beijing/zahuo",
                        "/d/beijing/yancao","/d/beijing/xingchang",
                        "/d/beijing/wang_4","/d/beijing/chaoyang_dao1",
                        "/d/beijing/chaoyang_dao2","/d/beijing/chaoyangmen",
                        "/d/beijing/wang_6","/d/beijing/wang_8",
                        "/d/beijing/xiyuan","/d/beijing/xiyuanup",
                        "/d/beijing/wang_10","/d/beijing/wang_9",
                        "/d/beijing/wang_1","/d/beijing/wang_3",
                        "/d/beijing/wang_5","/d/beijing/wang_7",
                        "/d/beijing/wang_8","/d/beijing/quanjude",
                        "/d/beijing/quanjudeup","/d/beijing/dong_1",
                        "/d/beijing/dong_3","/d/beijing/dongchang_men",
                        "/d/beijing/dongchang","/d/beijing/xiaochang",
                        "/d/beijing/weifu_men","/d/beijing/weifu_zoulang1",
                        "/d/beijing/weifu_dayuan","/d/beijing/weifu_zoulang2",
                        "/d/beijing/weifu_dating","/d/beijing/weifu_shufang",
                        "/d/beijing/dong_2","/d/beijing/guozijian",
                        "/d/beijing/wang_2",
                     }),
        "��������" : ({
                        "/d/beijing/niaoshi","/d/beijing/xi_1",
                        "/d/beijing/caroad_w1","/d/beijing/yangliu1",
                        "/d/beijing/yangliu2","/d/beijing/yangliu3",
                        "/d/beijing/qingmu_men","/d/beijing/qingmu_dayuan",
                        "/d/beijing/qingmu_fang3","/d/beijing/qingmu_fang1",
                        "/d/beijing/caroad_w1","/d/beijing/caroad_w2",
                        "/d/beijing/cagc_w","/d/beijing/tiananmen",
                        "/d/beijing/cagc_s","/d/beijing/tianqiao",
                        "/d/beijing/yong_1","/d/beijing/duchang",
                        "/d/beijing/huiying","/d/beijing/huiyingup",
                        "/d/beijing/yong_2","/d/beijing/tiepu",
                        "/d/beijing/yong_3","/d/beijing/fu_2",
                        "/d/beijing/fukedian","/d/beijing/kediandayuan",
                        "/d/beijing/hai_men","/d/beijing/hai_dayuan",
                        "/d/beijing/hai_fang","/d/beijing/hai_huating",
                        "/d/beijing/hai_dating","/d/beijing/hai_houyuan",
                        "/d/beijing/mianguan","/d/beijing/fu_1",
                        "/d/beijing/tiantan_n","/d/beijing/tiantan",
                        "/d/beijing/yongdingdao","/d/beijing/yongdingmen",
                        "/d/beijing/qiao","/d/beijing/hgmen_s",
                        "/d/beijing/gaosheng","/d/beijing/xi_2",
                        "/d/beijing/huichuntang","/d/beijing/bei_2",
                        "/d/beijing/kangfu_men","/d/beijing/kangfu_dayuan",
                        "/d/beijing/kangfu_zoulang1","/d/beijing/kangfu_dating",
                        "/d/beijing/kangfu_zoulang2","/d/beijing/kangfu_xifang",
                        "/d/beijing/kangfu_dongfang","/d/beijing/kangfu_shufang",
                        "/d/beijing/bei_2","/d/beijing/bei_4",
                        "/d/beijing/di_1","/d/beijing/di_3",
                        "/d/beijing/di_4","/d/beijing/aofu_men",
                        "/d/beijing/aofu_zoulang1","/d/beijing/aofu_dayuan",
                        "/d/beijing/aofu_dating","/d/beijing/aofu_zoulang2",
                        "/d/beijing/aofu_houyuan","/d/beijing/aofu_zoulang3",
                        "/d/beijing/aofu_shufang","/d/beijing/aofu_naofang",
                        "/d/beijing/caishi","/d/beijing/ximenkou",
                        "/d/beijing/shi_1","/d/beijing/guandao_1",
                        "/d/beijing/guandao_2","/d/beijing/huangling",
                        "/d/beijing/shi_3","/d/beijing/di_xigc",
                        "/d/beijing/di_2","/d/beijing/dianmen",
                        "/d/beijing/di_dajie1","/d/beijing/di_5",
                        "/d/beijing/di_dajie2","/d/beijing/di_anmen",
                        "/d/beijing/qingmu_dating",
                     }),
        "���ݳ�"   : ({
                        "/d/city/zuixianlou2","/d/city/zuixianlou3",
                        "/d/city/zuixianlou","/d/city/beidajie2",
                        "/d/city/beimen","/d/city/beidajie1",
                        "/d/city/qianzhuang","/d/city/guangchang",
                        "/d/city/xidajie1","/d/city/yamen",
                        "/d/city/xidajie2","/d/city/wuguan",
                        "/d/city/ximen","/d/city/dongdajie1",
                        "/d/city/zahuopu","/d/city/dongdajie2",
                        "/d/city/yaopu","/d/city/datiepu",
                        "/d/city/dongmen",
                     }),
	 "������"   : ({
                        "/d/changan/huanggong","/d/changan/bridge1",
                        "/d/changan/baihu2","/d/changan/beian-dadao",
                        "/d/changan/beian-daokou","/d/changan/bingying1",
                        "/d/changan/bingying2","/d/changan/bei-chengmen",
                        "/d/changan/qixiang3","/d/changan/qixiang2",
                        "/d/changan/tea-shop","/d/changan/fruit-shop",
                        "/d/changan/qixiang1","/d/changan/jiulou",
                        "/d/changan/jiulou2","/d/changan/yongtai-beikou",
                        "/d/changan/zhubaohang","/d/changan/yongtai-dadao1",
                        "/d/changan/yongtai-dadao2","/d/changan/yongtai-dadao3",
                        "/d/changan/huiwenge","/d/changan/xian-daokou",
                        "/d/changan/xi-chengmen","/d/changan/bingying3",
                        "/d/changan/yongtai-dadao4","/d/changan/miao",
                        "/d/changan/yongtai-dadao5","/d/changan/yongtai-nankou",
                        "/d/changan/baozipu","/d/changan/huarui1",
                        "/d/changan/nanan-daokou","/d/changan/huarui2",
                        "/d/changan/mianguan","/d/changan/huarui3",
                        "/d/changan/huadian","/d/changan/bingying5",
                        "/d/changan/bingying4","/d/changan/nan-chengmen",
                        "/d/changan/huarui4","/d/changan/xiaojinghu",
                        "/d/changan/huarui4","/d/changan/huarui5",
                        "/d/changan/zahuopu","/d/changan/huarui5",
                        "/d/changan/huarui6","/d/changan/tuchangguan",
                        "/d/changan/liande-nankou","/d/changan/xiaojiuguan",
                        "/d/changan/liande-dadao5","/d/changan/xiaojia-qianyuan",
                        "/d/changan/liande-dadao4","/d/changan/dongan-daokou",
                        "/d/changan/dong-chengmen","/d/changan/bingying6",
                        "/d/changan/liande-dadao3","/d/changan/liande-dadao2",
                        "/d/changan/liande-dadao1","/d/changan/liande-beikou",
                        "/d/changan/xiyuan","/d/changan/qixiang6",
                        "/d/changan/yaopu","/d/changan/weapon-shop",
                        "/d/changan/qixiang5","/d/changan/shoushi-dian",
                        "/d/changan/biaoju-damen","/d/changan/qixiang4",
                        "/d/changan/bank","/d/changan/qunyulou",
                        "/d/changan/baihu1","/d/changan/fufeng1",
                        "/d/changan/fufeng2","/d/changan/fufeng3",
                        "/d/changan/fufeng4","/d/changan/xian-dadao",
                        "/d/changan/fufeng5","/d/changan/qinglong1",
                        "/d/changan/baoxiangsi","/d/changan/qinglong2",
                        "/d/changan/bridge2","/d/changan/qinglong2",
                        "/d/changan/nanan-dadao","/d/changan/qinglong3",
                        "/d/changan/yamen","/d/changan/fengxu5",
                        "/d/changan/fengxu4","/d/changan/lingyange",
                        "/d/changan/fengxu3","/d/changan/fengxu2",
                        "/d/changan/dongan-dadao","/d/changan/fengxu1",
                        "/d/changan/baihu3","/d/changan/guozijian",
                     }),
        "�ɶ���"   : ({
                        "/d/city3/guangchang","/d/city3/tidugate",
                        "/d/city3/shuduroad2","/d/city3/shuduroad1",
                        "/d/city3/eastroad2","/d/city3/eastroad1",
                        "/d/city3/northroad3","/d/city3/northroad2",
                        "/d/city3/northgate","/d/city3/northroad1",
                        "/d/city3/bingqidian","/d/city3/westroad3",
                        "/d/city3/yaodian","/d/city3/westroad2",
                        "/d/city3/westgate","/d/city3/westroad1",
                        "/d/city3/qingyanggong","/d/city3/southroad3",
                        "/d/city3/wuhoucigate","/d/city3/liubeidian",
                        "/d/city3/wuhouci","/d/city3/southroad2",
                        "/d/city3/southgate","/d/city3/tiduroad",
                        "/d/city3/southroad1","/d/city3/eastroad3",
                        "/d/city3/wangjianglou","/d/city3/eastroad2",
                        "/d/city3/eastroad1","/d/city3/jiudian",
                        "/d/city3/wuguan",
                     }),
        "���ݳ�"   : ({
                        "/d/suzhou/beimen","/d/suzhou/beidajie2",
                        "/d/suzhou/zijinan","/d/suzhou/jiudian",
                        "/d/suzhou/beidajie1","/d/suzhou/xiyuan",
                        "/d/suzhou/canlangting","/d/suzhou/dongdajie1",
                        "/d/suzhou/hutong1","/d/suzhou/leitai",
                        "/d/suzhou/hutong2","/d/suzhou/hutong3",
                        "/d/suzhou/dongdajie2","/d/suzhou/dongmen",
                        "/d/suzhou/yaopu","/d/suzhou/datiepu",
                        "/d/suzhou/baodaiqiao","/d/suzhou/nandajie1",
                        "/d/suzhou/jubaozhai","/d/suzhou/shizilin",
                        "/d/suzhou/yanyutang","/d/suzhou/zhenquting",
                        "/d/suzhou/wenmeige","/d/suzhou/lixuetang",
                        "/d/suzhou/zhipoxuan","/d/suzhou/shuyuan",
                        "/d/suzhou/chaguan","/d/suzhou/nandajie2",
                        "/d/suzhou/liuyuan","/d/suzhou/hehuating",
                        "/d/suzhou/gumujiaohe","/d/suzhou/chitang",
                        "/d/suzhou/nanmen","/d/suzhou/tingyu",
                        "/d/suzhou/xidajie1","/d/suzhou/bingying",
                        "/d/suzhou/yunhematou","/d/suzhou/xidajie2",
                        "/d/suzhou/xuanmiao","/d/suzhou/shuchang",
                        "/d/suzhou/ximen",
                     }),
        "���ݳ�"   : ({
                        "/d/hangzhou/suti2", "/d/hangzhou/jujingyuan",
                        "/d/hangzhou/liuzhuang", "/d/hangzhou/road19",
                        "/d/hangzhou/huangniling", "/d/hangzhou/qinglindong",
                        "/d/hangzhou/road5","/d/hangzhou/liuhe2",
                        "/d/hangzhou/dadao1","/d/hangzhou/xilingqiao",
                        "/d/hangzhou/road9","/d/hangzhou/baoshishan",
                        "/d/hangzhou/yuelang","/d/hangzhou/liuzhuang1",
                        "/d/hangzhou/huagang","/d/hangzhou/hupaoquan",
                        "/d/hangzhou/yuhuangsd","/d/hangzhou/yuhuangshan",
                        "/d/hangzhou/shanlu6","/d/hangzhou/shanlu7",
                        "/d/hangzhou/yuhuangsj","/d/hangzhou/road18",
                        "/d/hangzhou/road20","/d/hangzhou/suti7",
                        "/d/hangzhou/suti7","/d/hangzhou/suti6",
                        "/d/hangzhou/suti5","/d/hangzhou/suti4",
                        "/d/hangzhou/suti3","/d/hangzhou/suti2",
                        "/d/hangzhou/road7","/d/hangzhou/road8",
                        "/d/hangzhou/road9","/d/hangzhou/road10",
                        "/d/hangzhou/road11","/d/hangzhou/road12",
                        "/d/hangzhou/road13","/d/hangzhou/road14",
                        "/d/hangzhou/road15","/d/hangzhou/road16",
                        "/d/hangzhou/xizhaoshan","/d/hangzhou/road17",
                        "/d/hangzhou/road18","/d/hangzhou/qingbomen",
                        "/d/hangzhou/jujingyuan","/d/hangzhou/liulangqiao",
                        "/d/hangzhou/qiantang","/d/hangzhou/liuheta",
                        "/d/hangzhou/yuquan","/d/hangzhou/dadao1",
                        "/d/hangzhou/dadao2","/d/hangzhou/dalu1",
                        "/d/hangzhou/liuzhuang2","/d/hangzhou/liuzhuang",
                        "/d/hangzhou/road1", "/d/hangzhou/road2",
                        "/d/hangzhou/road4", "/d/hangzhou/road3",
                        "/d/hangzhou/hongchunqiao","/d/hangzhou/jiulou",
                        "/d/hangzhou/duanqiao","/d/hangzhou/baiti",
                        "/d/hangzhou/pinghuqiuyue","/d/hangzhou/fangheting",
                        "/d/hangzhou/gushan","/d/hangzhou/gushanpingtai",
                        "/d/meizhuang/shijie","/d/meizhuang/xiaolu",
                        "/d/meizhuang/gate","/d/hangzhou/shanlu8",
                        "/d/hangzhou/chufang","/d/hangzhou/tiejiangpu",
                        "/d/hangzhou/yaodian","/d/hangzhou/jingcisi",
                        "/d/hangzhou/jingci","/d/hangzhou/shanlu1",
                        "/d/hangzhou/shanlu2","/d/hangzhou/shanlu3",
                        "/d/hangzhou/fajingsi","/d/hangzhou/fajinsi",
                        "/d/hangzhou/faxisi","/d/hangzhou/shanlu4",
                        "/d/hangzhou/shanlu5","/d/hangzhou/shanlu6",
                        "/d/hangzhou/shanlu7","/d/hangzhou/tulu1",
                        "/d/hangzhou/yanxiadong","/d/hangzhou/maojiabu",
                        "/d/hangzhou/maojiabu","/d/hangzhou/huangniling",
                        "/d/hangzhou/shuiledong","/d/hangzhou/manjuelong",
                     }),
        "������"   : ({
                        "/d/xiangyang/westjie2", "/d/xiangyang/southjie2",
                        "/d/xiangyang/xiaorong1", "/d/xiangyang/zhonglie",
                        "/d/xiangyang/guangchang", "/d/xiangyang/dingzi",
                        "/d/xiangyang/westgate2","/d/xiangyang/northgate1",
                        "/d/xiangyang/eastgate1","/d/xiangyang/southgate2",
                        "/d/xiangyang/walls2","/d/xiangyang/walle3",
                        "/d/xiangyang/walln4","/d/xiangyang/juyilang",
                        "/d/xiangyang/northgate2","/d/xiangyang/northjie",
                        "/d/xiangyang/bingying1","/d/xiangyang/chaguan",
                        "/d/xiangyang/northroad2","/d/xiangyang/xiaorong2",
                        "/d/xiangyang/xiaorong1","/d/xiangyang/jiekou2",
                        "/d/xiangyang/eastroad2","/d/xiangyang/eastroad1",
                        "/d/xiangyang/biaoju","/d/xiangyang/eastjie2",
                        "/d/xiangyang/eastjie3","/d/xiangyang/bingying2",
                        "/d/xiangyang/eastgate2","/d/xiangyang/walle1",
                        "/d/xiangyang/walle5","/d/xiangyang/walle7",
                        "/d/xiangyang/walle2","/d/xiangyang/walle4",
                        "/d/xiangyang/walle6","/d/xiangyang/walle8",
                        "/d/xiangyang/mujiang","/d/xiangyang/eastjie2",
                        "/d/xiangyang/eastjie3","/d/xiangyang/jiedao",
                        "/d/xiangyang/minju2","/d/xiangyang/eastjie1",
                        "/d/xiangyang/jiangjungate","/d/xiangyang/yaopu",
                        "/d/xiangyang/anfugate","/d/xiangyang/anfupailou",
                        "/d/xiangyang/southjie1","/d/xiangyang/southjie2",
                        "/d/xiangyang/southjie3","/d/xiangyang/xuetang",
                        "/d/xiangyang/qianzhuang","/d/xiangyang/southgate1",
                        "/d/xiangyang/nixianglou","/d/xiangyang/duchang",
                        "/d/xiangyang/tiejiangpu","/d/xiangyang/bingying3",
                        "/d/xiangyang/walls1","/d/xiangyang/walls3",
                        "/d/xiangyang/walls5","/d/xiangyang/walls7",
                        "/d/xiangyang/walls4","/d/xiangyang/walls6",
                        "/d/xiangyang/walls8","/d/xiangyang/westjie1",
                        "/d/xiangyang/westjie2","/d/xiangyang/westjie3",
                        "/d/xiangyang/guofugate","/d/xiangyang/guofuyuan",
                        "/d/xiangyang/guofuting","/d/xiangyang/guofuhuayuan",
                        "/d/xiangyang/guofukefang","/d/xiangyang/guofuwoshi",
                        "/d/xiangyang/guofushufang","/d/xiangyang/dangpu",
                        "/d/xiangyang/juyiyuan","/d/xiangyang/juyilianwu2",
                        "/d/xiangyang/juyilianwu1","/d/xiangyang/juyilang",
                        "/d/xiangyang/juyihuayuan","/d/xiangyang/juyimale",
                        "/d/xiangyang/juyifemale","/d/xiangyang/juyichufang",
                        "/d/xiangyang/juyiwupin","/d/xiangyang/dajiaochang",
                        "/d/xiangyang/bingying4","/d/xiangyang/westgate1",
                        "/d/xiangyang/wallw1","/d/xiangyang/wallw2",
                        "/d/xiangyang/wallw3","/d/xiangyang/wallw4",
                        "/d/xiangyang/wallw5","/d/xiangyang/wallw6",
                        "/d/xiangyang/wallw7","/d/xiangyang/wallw8",
                        "/d/xiangyang/westroad1","/d/xiangyang/westroad2",
                        "/d/xiangyang/shudian","/d/xiangyang/hutong1",
                        "/d/xiangyang/hutong2","/d/xiangyang/xinluofang",
                        "/d/xiangyang/jiekou1","/d/xiangyang/northgate2",
                        "/d/xiangyang/walln1","/d/xiangyang/walln2",
                        "/d/xiangyang/walln3","/d/xiangyang/walln5",
                        "/d/xiangyang/walln6","/d/xiangyang/walln7",
                        "/d/xiangyang/walln8",
                     }),
        "����һ��" : ({
                        "/d/dali/northgate", "/d/dali/southgate",
                        "/d/dali/shanlu2", "/d/dali/buxiongbu",
                        "/d/dali/jinzhihe", "/d/dali/xiaodao1",
                        "/d/dali/tianweijing", "/d/dali/wuding",
                        "/d/dali/luwang", "/d/dali/gudao",
                        "/d/dali/biluoxueshan", "/d/dali/zhenxiong",
                        "/d/dali/yixibu", "/d/dali/cangshanzhong",
                        "/d/dali/wumeng", "/d/dali/hongsheng",
                        "/d/dali/tusifu","/d/dali/tusimentang",
                        "/d/dali/tusiyishi","/d/dali/dahejiewest",
                        "/d/dali/dahejieeast","/d/dali/baiyiziguan",
                        "/d/dali/baiyiminju","/d/dali/center",
                        "/d/dali/taihejiekou","/d/dali/sheguta",
                        "/d/dali/qingchi","/d/dali/taiheeast",
                        "/d/dali/stoneshop","/d/dali/garments",
                        "/d/dali/yaoshop","/d/dali/paifang",
                        "/d/dali/yujie","/d/dali/gongmen",
                        "/d/dali/qiandian","/d/dali/yuhuayuan",
                        "/d/dali/hualang","/d/dali/yushanfang",
                        "/d/dali/piandian","/d/dali/chahuashan1",
                        "/d/dali/chahuashan2","/d/dali/chahuashan3",
                        "/d/dali/chahuashan4","/d/dali/chahuashan5",
                        "/d/dali/chahuashan6","/d/dali/dadieshui",
                        "/d/dali/qingxi","/d/dali/xiaodao1",
                        "/d/dali/hudiequan","/d/dali/yuxuguanqian",
                     }),
]);

string *nations = ({ "�ձ�", "����", "����", "�ձ�", "�ձ�",
                     "�ձ�", "Ӣ����", "������", "������", "������",
                     "����ʱ"});

string *foreigner = ({ "Ӷ����", "̽�ն�", "���Ծ�", "�����Ż�", "���ܷ�" });

string *chinese = ({ "�ڷ�կ", "��ͷ��", "ɽ������", "ɽ������", "��������",
                     "������ǿ��", "̫��ɽ����", "���շ�ë��", "��Į���" });

int all_enemy = 0;
object *all_killer = ({});

void add_killer(object killer);
void be_killed(int num);
int query_enemy();
object *query_killer();
object create_npc(string nation, int lvl);
void init_npc_skill(object ob, int lvl);
void start_quest(int num);
varargs void place_npc(object ob,string arg,string the_type,int lvl,string pp);
void random_move(object ob);
int not_wizard(object ob);

void add_killer(object killer)
{
        if (!objectp(killer) || !userp(killer))
                return;

        if (member_array(killer,all_killer) == -1)
                all_killer += ({ killer });

        return;
}


void be_killed(int num)
{
        all_enemy -= num;
        return;
}

int query_enemy()
{
        return all_enemy;
}

object *query_killer()
{
        return all_killer;
}

void ready_to_start()
{
        remove_call_out("start_quest");
        call_out("start_quest", IDLE, random(6));
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "������");
        CHANNEL_D->do_channel( this_object(), "task", "Ⱥ������ϵͳ�Ѿ�������");
        ready_to_start();
}

int clean_up()
{
        return 1;
}

object create_npc(string nation, int lvl)
{
        object ob;

        switch (nation)
        {
        case "�й�":
                ob = new(CLASS_D("generate") + "/quest_chinese");
                NPC_D->generate_cn_name(ob);
                break;
        case "�ձ�":
                ob = new(CLASS_D("generate") + "/quest_japanese");
                NPC_D->generate_jp_name(ob);
                break;
        case "Ӣ����":
        case "������":
        case "������":
        case "������":
        case "����ʱ":
        case "����":
                ob = new(CLASS_D("generate") + "/quest_european");
                generate_e_name(ob);
                break;
        case "����":
                ob = new(CLASS_D("generate") + "/quest_indian");
                generate_in_name(ob);
                break;
        }
        if (lvl >= 7)
                ob->set("auto_perform",1);
        ob->set("nation", nation);
        init_npc_skill(ob, lvl);

        return ob;
}

// set the the level of the npc's skill
void init_npc_skill(object ob, int lvl)
{
        int sk_lvl;
        string *ks;
        int i;
        int exp;
        mixed my;

        if (lvl < 1) lvl = 1;
        if (lvl >= sizeof(levels)) lvl = sizeof(levels) - 1;

        exp = sort_array(keys(levels), 1)[lvl - 1];
      	 my = ob->query_entire_dbase();
        ob->set("combat_exp", exp);
        sk_lvl = levels[exp];
        my["jing"] = my["eff_jing"] = my["max_jing"] = sk_lvl * 5;
        my["qi"] = my["eff_qi"] = my["max_qi"] = sk_lvl * 10;
        my["jingli"] = my["max_jingli"] = sk_lvl * 3;
        my["neili"] = my["max_neili"] = sk_lvl * 5;
        if (! ob->query_skills())
                return;
        ks = keys(ob->query_skills());
        for (i = 0; i < sizeof(ks); i++)
                ob->set_skill(ks[i], sk_lvl);
}

void start_quest(int num)
{
        string *kp;
        string p,arg,title,pp;
        string startroom;
        object pos,*all_user,ob;
        string the_nation,the_enemy;
        mapping fam_map,party_map;
        int i,all,lvl;

        ready_to_start();

        fam_map = ([]);
        party_map = ([]);

        switch (num)
        {
                case 0:
                case 1:
                case 2:
                        CHANNEL_D->do_channel( this_object(), "task", "Ⱥ������ϵͳ��ʼ���������������");
                        arg = "�������";
                        kp = keys(place);
                        p = kp[random(sizeof(kp))];
                        all_user = users();
                        all_user = filter_array(all_user,(: $1->query("combat_exp") > 200000 :));
                        all_user = filter_array(all_user,(: not_wizard :));
                        all = sizeof(users())/2;
                        if (all<10) return;			//���̫�٣���ֹ���ν��̡�
                        if (all>60) all = 60;
                        all_enemy = all;
                        all_killer = ({});
                        the_nation = nations[random(sizeof(nations))];
                        title = HIW + the_nation + NOR + " " + HIY +
                                foreigner[random(sizeof(foreigner))] +NOR;
                        for (i = 0;i < all;i ++)
                        {
                                lvl = random(15) + 1;
                                ob = create_npc(the_nation,lvl);
                                place_npc(ob,arg,p,lvl);
                                ob->set("title",title);
                                ob->random_move();
                                ob->random_move();
                                ob->random_move();
                                ob->random_move();
                        }
                        message("story",HIR "��������֡�" NOR+WHT "��˵һ������" + NOR + HIY +
                                  the_nation + NOR + WHT +
                                  "���������������й���\n" NOR,users() );
                        message("story",HIR "��������֡�" NOR+WHT "����ǰ�����±��棬����������Ŀǰ��" +
                                  NOR + HIY + p + NOR + WHT + "��ûƵ����\n" NOR,users() );
                        message("story",HIR "��������֡�" NOR+WHT "��λͬ�����������Ž���������������" +
                                  "����������ɱ�У��������ַ������л��ĵ��˺ݺݵĴ����\n" NOR,users() );
                        break;
                case 3:
                        CHANNEL_D->do_channel( this_object(), "task", "Ⱥ������ϵͳ��ʼ����������������");
                        arg = "����";
                        kp = keys(family);
                        for (i = 0;i < sizeof (kp);i ++)
                        {
                                p = kp[i];
                                all_user = users();
                                all_user = filter_array(all_user,(: $1->query("family/family_name") == $2 :),p);
                                all_user = filter_array(all_user,(: not_wizard :));
                                if (!sizeof(all_user)) continue;	//������û���������
                                fam_map += ([ p:sizeof(all_user) ]);
                        }
                        if (!sizeof(fam_map)) return;		//MUD��û�������κ�һ�����ɵ����
                        kp = keys(fam_map);
                        p = kp[random(sizeof(kp))];
                        all = fam_map[p];
                        if (all < 5) all = 5;
                        if (all > 20) all = 30 - random(10);
                        all_enemy = all;
                        all_killer = ({});
                        the_nation = "�й�";
                        the_enemy = chinese[random(sizeof(chinese))];
                        title = HIY + p + NOR + HIW + "���" + NOR + " " + HIY +
                                the_enemy + NOR;
                        for (i = 0;i < all;i ++)
                        {
                                lvl = random(15) + 1;
                                ob = create_npc(the_nation,lvl);
                                place_npc(ob,arg,p,lvl);
                                ob->set("title",title);
                                ob->random_move();
                                ob->random_move();
                                ob->random_move();
                                ob->random_move();
                        }
                        message("story",HIR "���������֡�" NOR+WHT "��˵" + NOR + HIY +
                                  the_enemy + NOR + WHT +
                                  "��������³����ڽ���������Я����������һ��Ҫ�Ҳ�����ӣ�\n" NOR,users() );
                        message("story",HIR "���������֡�" NOR+WHT "������Щ��˽��©���Ŀڷ磬��������ǳ���" +
                                  NOR + HIY + p + NOR + WHT + "���ģ�\n" NOR ,users());
                        message("story",HIR "���������֡�" NOR+WHT "ʿ��ɱ�����裬" + NOR + HIY + p + NOR + WHT +
                                  "����һ���ж�������������ͳͳ����ϼң�\n" NOR,users());
                        break;
                default:
                        CHANNEL_D->do_channel( this_object(), "task", "Ⱥ������ϵͳ��ʼ����������������");
                        arg = "����";
                        all_user = users();
                        all_user = filter_array(all_user,(: $1->query("party") :));
                        all_user = filter_array(all_user,(: not_wizard :));
                        for (i = 0;i < sizeof (all_user);i ++)
                        {
                                p = all_user[i]->query("party/party_name");
                                if (!stringp(p)) continue;
                                if (!party_map[p])
                                        party_map[p] = 1;
                                else
                                        party_map[p] += 1;
                        }
                        kp = keys(party_map);
                        for (i = 0;i < sizeof(kp);i++)
                                if (party_map[kp[i]] < 3)
                                        map_delete(party_map,kp[i]);
                        if (!sizeof(party_map)) return;
                        kp = keys(party_map);
                        p = kp[random(sizeof(kp))];
                        all = party_map[p] * 2;
                        if (all < 10) all = 20 - random(11);
                        if (all > 20) all = 30 - random(10);
                        all_enemy = all;
                        all_killer = ({});
                        the_nation = "�й�";
                        the_enemy = chinese[random(sizeof(chinese))];
                        title = HIY + p + NOR + HIW + "���" + NOR + " " + HIY +
                                the_enemy + NOR;
                        kp = keys(place);
                        pp = kp[random(sizeof(kp))];
                        for (i = 0;i < all;i ++)
                        {
                                lvl = random(15) + 1;
                                ob = create_npc(the_nation,lvl);
                                place_npc(ob,arg,p,lvl,pp);
                                ob->set("title",title);
                                ob->random_move();
                                ob->random_move();
                                ob->random_move();
                                ob->random_move();
                        }
                        message("story",HIR "���������ơ�" NOR+WHT "��˵" + NOR + HIY + the_enemy + NOR + WHT +
                                  "��������³����ڽ���������Я����������һ��Ҫ�Ҳ�����ӣ�\n" NOR,users() );
                        message("story",HIR "���������ơ�" NOR+WHT "���������˼�����������" + NOR + HIY + pp + NOR + WHT +
                                  "���ᣬ�������ڣ�Ŀ��һ�е����ӣ�\n" NOR,users() );
                        message("story",HIR "���������ơ�" NOR+WHT "������Щ��˽��©���Ŀڷ磬������δ�ע��Ҫ��ƽ" +
                                  NOR + HIY + p + NOR + WHT + "��\n" NOR,users() );
                        message("story",HIR "���������ơ�" NOR+WHT "�������д�����������С��" + NOR + HIY + p +
                                  NOR + WHT + "�ѵ�������������ǲ��ɣ�\n" NOR ,users() );
                        break;
        }
}

varargs void place_npc(object ob,string arg,string the_type,int lvl,string pp)
{
        string *kp,option;
        string p,startroom;
        object pos;

        switch (arg)
        {
                case "�������":
                        ob->set("my_type",arg);
                        startroom = place[the_type][random(sizeof(place[the_type]))];
                        if (! objectp(pos = get_object(startroom)))
                                log_file("log", sprintf("error to place npc to %s:%s\n",
                                                        the_type, startroom));
                        ob->set("place", the_type);
                        break;
                case "����":
                        ob->set("my_type",arg);
                        ob->set("����",the_type);
                        startroom = family[the_type][random(sizeof(family[the_type]))];
                        if (! objectp(pos = get_object(startroom)))
                                log_file("log", sprintf("error to place npc to %s:%s\n",
                                                        the_type, startroom));
                        ob->set("place", the_type);
                        break;
                case "����":
                        ob->set("my_type",arg);
                        ob->set("����",the_type);
                        startroom = place[pp][random(sizeof(place[pp]))];
                        if (! objectp(pos = get_object(startroom)))
                                log_file("log", sprintf("error to place npc to %s:%s\n",
                                                        the_type, startroom));
                        ob->set("place", pp);
                        break;

        }

        switch (lvl)
        {
                case 1:
                case 2:
                case 3:
                        ob->set("nickname","С���");
                        ob->set("bonus",150);
                        break;
                case 4:
                case 5:
                case 6:
                        ob->set("nickname","��ͨ��Ա");
                        ob->set("bonus",200);
                        break;
                case 7:
                case 8:
                case 9:
                        ob->set("nickname","СͷĿ");
                        ob->set("bonus",300);
                        break;
                case 10:
                case 11:
                case 12:
                        ob->set("nickname","��ͷĿ");
                        ob->set("bonus",500);
                        break;
                case 13:
                case 14:
                        ob->set("nickname","����");
                        ob->set("bonus",800);
                        break;
                case 15:
                case 16:
                        ob->set("nickname","������");
                        ob->set("bonus",1000);
                        break;
                default:
                        ob->set("nickname","������");
                        ob->set("bonus",1500);
                        break;
        }

        ob->move(pos);
        ob->set("startroom", startroom);
        ob->set_temp("moved", ({ }));
        message_vision("$N���˹�����\n", ob);
}

// random move
void random_move(object ob)
{
        mapping exits;
        string *moved;
        string dir;
        string *dirs;
        int i;

        moved = ob->query_temp("moved");
        if (! moved) moved = ({ });
        if (sizeof(moved) >= MAX_MOVED)
        {
                // out of range, move back
                dir = GO_CMD->query_reverse(moved[sizeof(moved) - 1]);
        } else
        {
                exits = environment(ob)->query("exits");
                dirs = keys(exits);
                for (i = 0; i < 12; i++)
                {
                	if (! sizeof(dirs))
                		return;
                        dir = dirs[random(sizeof(dirs))];
                        if (stringp(GO_CMD->query_reverse(dir)) &&
                            ! exits[dir]->query("no_fight"))
                                break;
                        dirs -= ({ dir });
                }
        }

        if (sizeof(moved) &&
            GO_CMD->query_reverse(dir) == moved[sizeof(moved) - 1])
        {
                // move back
                moved = moved[0..<2];
        } else
                moved += ({ dir });
        ob->set_temp("moved", moved);

        GO_CMD->main(ob, dir);
}

int not_wizard(object ob)
{
        if (wizardp(ob)) return 0;
        return 1;
}
