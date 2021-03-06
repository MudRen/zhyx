// party_questd.c
// edit by smallfish@lxtx

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

#define MIN_IDLE        30
#define MAX_MOVED       5
#define WAIT_TIME       300
//任务中的物品直接调用宗师任务的物品列表
#define QUEST_GOOD_OBJ(x)     ("/quest/questdg/quest/questdg" + x)
#define QUEST_BAD_OBJ(x)      ("/quest/questkh/quest/questkh" + x)

mapping *bang_zs = ({});

mapping bang_city_quest=([
        "bje": ({ }),
        "bjw": ({ }),
        "yz" : ({ }),
        "ca" : ({ }),
        "cd" : ({ }),
        "sz" : ({ }),
        "hz" : ({ }),
        "xy" : ({ }),
        "dl" : ({ }),
]);

string *need_send_msg=({
        "近日黑道联盟要有大举动，你好好准备准备！",
        "注意一下华山派弟子的举动！",
        "注意一下衡山派弟子的举动！",
        "注意一下少林派弟子的举动！",
        "注意一下段氏皇族弟子的举动！",
        "注意一下慕容世家的举动！",
        "注意一下关外胡家的举动！",
        "刺探一下胡不归最近在哪里。",
        "注意一下桃花岛弟子的举动！",
        "白道联盟的行动近日有点神秘，你好好观察。",
});

string *bad_msg1=({
        "name老是跟我们黑道作对，",
        "早就想宰掉name这个伪君子了，",
        "早就看name这个家伙不顺眼，",
        "name上次杀了我们一个黑道兄弟逃匿至今，",
        "name双手沾满了我们黑道兄弟的鲜血，",
        "自从name出卖了我们兄弟，一直躲着不露面，",
        "name违背道上的规矩，",
        "听说过name出卖兄弟的事情吧？",
        "记得去年name投奔白道的事情吧？",
        "name这个所谓正人君子杀害了我们很多弟兄，",
        "最近黑白道纷争又起，总盟主决定借name的人头来立威，",
        "最近黑道势力疲软，得借name的人头来鼓舞下士气，",
        "近来name对我们黑道总盟主出言不逊，",
        "name昨日竟然扬言要铲平我们黑道总舵，",
        "name这个小子所作所为丢尽了我们黑道的脸，",
        "总舵主的小老婆给name勾搭走了，",
});

string *bad_msg2=({
        "他最近潜伏在place一带，",
        "有弟兄最近在place发现了他的踪迹，",
        "昨日有人看到他在place出没，",
        "昨晚他曾在place的一家客店出现，",
        "今日清晨他从place北门混入城中，",
        "昨晚他就到达了place，可能还未溜走，",
        "place的一家客店最近来了一个神秘人物，",
        "有人乔装打扮出现在place，",
        "place来了个陌生人举止诡异，",
        "place又有弟兄给这个家伙欺负了，",
        "place黑道兄弟说前不久遇到一个家伙很象他，",
        "他最近很可能在place一带，",
        "他可能正前往place一带，",
        "他有一个好友在place，可能他会去躲他朋友那里，",
        "place有他一处秘密窝点，不知道他是否潜伏在那里，",
        "几乎所有地方都搜索过了，只剩下place还没全部搜索，",
});

string *bad_msg3=({
        "弟兄们赶快去把他宰了。",
        "弟兄们去看看，发现他就不要手下留情。",
        "不要让他再见到明天的太阳。",
        "总算有线索送他上西天了。",
        "用他的血来扬我们黑道的微风吧。",
        "弟兄们知道该怎么做了吧！",
        "找到他，杀无赦！",
        "只要找到他，格杀勿论！",
});

string *good_msg1=({
        "name作恶多端，",
        "早就想铲除name这个恶贼了，",
        "对name这恶魔我们白道人士过去太放纵了点，",
        "name上次杀了我们一个同道逃匿至今，",
        "name双手沾满了我们正道人士的鲜血，",
        "自从name出卖了他的兄弟，一直躲着不露面，",
        "name违背我们正派人士的行事准则，",
        "听说过name出卖兄弟的事情吧？",
        "记得去年name投奔魔教的事情吧？",
        "name这个色狼为祸江湖已久，",
        "最近黑白道纷争又起，不取了name的人头不足以弘扬正气，",
        "最近我们正派人士连连给黑道欺压，name的人头正好用来鼓舞士气，",
        "近来name对我们正派出言不逊，",
        "name昨日竟然扬言要铲平我们白道总部，",
        "name这个小子所作所为丢尽了我们正派人士的脸，",
        "name吃喝嫖赌，无恶不作，",
});

string *good_msg2=({
        "他最近潜伏在place一带，",
        "有弟兄最近在place发现了他的踪迹，",
        "昨日有人看到他在place出没，",
        "昨晚他曾在place的一家赌场出现，",
        "今日清晨他从place北门混入城中，",
        "昨晚他就到达了place，可能还未溜走，",
        "place的一家客店最近来了一个陌生人，",
        "有人乔装打扮出现在place，",
        "place来了个陌生人举止诡异，",
        "place又有弟兄给这个家伙欺负了，",
        "place有兄弟说前不久遇到一个家伙很象他，",
        "他最近很可能在place一带，",
        "他可能正前往place一带，",
        "他有一个小妾在place，可能他会躲在那里，",
        "place有他一处秘密窝点，不知道他是否潜伏在那里，",
        "几乎所有地方都搜索过了，只剩下place还没全部搜索，",
});

string *good_msg3=({
        "弟兄们赶快去把他铲除了。",
        "弟兄们去看看，发现他就不要手下留情。",
        "不要让他再为祸江湖了。",
        "总算有线索送他上西天了。",
        "用他的血来给邪门歪道一个警告。",
        "弟兄们知道该怎么做了吧！",
        "找到他，杀无赦！",
        "只要找到他，格杀勿论！",
});

string *search_msg=({
        "根据我们密探发现的线索，",
        "我们的间谍发回最新消息，",
        "通过四方打听，",
        "我们的兄弟连续三天三夜对他追查，",
        "根据四方得来的最新消息，",
        "有兄弟从丐帮套到了消息，",
        "有消息灵通人士透露，",
});

mapping levels = ([
//      combat_exp   skill_level
        10000      : 45,               // level 1
        16000      : 55,               // level 2
        27000      : 65,               // level 3
        41000      : 75,               // level 4
        60000      : 85,               // level 5
        84000      : 95,               // level 6
        120000     : 105,              // level 7
        150000     : 115,              // level 8
        190000     : 125,              // level 9
        240000     : 135,              // level 10
        300000     : 145,              // level 11
        370000     : 155,              // level 12
        440000     : 165,              // level 13
        530000     : 175,              // level 14
]);

nosave mapping city=([
        "bje":"北京东城",
        "bjw":"北京西城",
        "yz":"扬州城",
        "ca":"长安城",
        "cd":"成都城",
        "sz":"苏州城",
        "hz":"杭州城",
        "xy":"襄阳城",
        "dl":"大理一带",
]);

nosave mapping static_npc = ([
        "bje"     : ([
                        "/d/beijing/caishi.c"  :  "ju min",
                        "/d/beijing/caishi.c"  :  "cai fan",
                        "/d/beijing/cagc_s.c"  :  "shuahou ren",
                        "/d/beijing/cagc_s.c"  :  "xian ren",
                        "/d/beijing/zhuang8.c"  :  "dizi",
                        "/d/beijing/chaoyang_dao1.c"  :  "tang zi",
                        "/d/beijing/chaoyang_dao2.c"  :  "tiao fu",
                        "/d/beijing/ximenkou.c"  :  "old man",
                        "/d/beijing/ximenkou.c"  :  "tang zi",
                        "/d/beijing/ximenkou.c"  :  "tiao fu",
                        "/d/beijing/tiepu.c"  :  "huoji",
                        "/d/beijing/tiepu.c"  :  "tie jiang",
                        "/d/beijing/yongdingdao.c"  :  "kid",
                        "/d/beijing/yongdingdao.c"  :  "tiao fu",
                        "/d/beijing/yongdingdao.c"  :  "tang zi",
                        "/d/beijing/guandao_1.c"  :  "tang zi",
                        "/d/beijing/qingmu_dating.c"  :  "chen jinnan",
                        "/d/beijing/road9.c"  :  "tangzi shou",
                        "/d/beijing/road4.c"  :  "jian ke",
                        "/d/beijing/road1.c"  :  "tiao fu",
                        "/d/beijing/road5.c"  :  "seng ren",
                        "/d/beijing/road2.c"  :  "tangzi shou",
                        "/d/beijing/road3.c"  :  "shu sheng",
                        "/d/beijing/road7.c"  :  "jianghu haoke",
                        "/d/beijing/qingmu_dayuan.c"  :  "xuan zhen",
                        "/d/beijing/di_dajie2.c"  :  "di pi",
                        "/d/beijing/di_dajie2.c"  :  "tiao fu",
                        "/d/beijing/di_donggc.c"  :  "kid",
                        "/d/beijing/di_donggc.c"  :  "shao fu",
                        "/d/beijing/di_donggc.c"  :  "liu mang",
                        "/d/beijing/dianmen.c"  :  "old man",
                        "/d/beijing/dianmen.c"  :  "kid",
                        "/d/beijing/di_xigc.c"  :  "hun hun",
                        "/d/beijing/di_xigc.c"  :  "xian ren",
                        "/d/beijing/dong_3.c"  :  "shu sheng",
                        "/d/beijing/di_4.c"  :  "boy",
                        "/d/beijing/di_1.c"  :  "you ren",
                        "/d/beijing/di_3.c"  :  "di pi",
                        "/d/beijing/di_1.c"  :  "kid",
                        "/d/beijing/di_3.c"  :  "tiao fu",
                        "/d/beijing/di_1.c"  :  "xiu cai",
                        "/d/beijing/cagc_e.c"  :  "shu sheng",
                        "/d/beijing/cagc_e.c"  :  "xian ren",
                        "/d/beijing/caroad_e2.c"  :  "old woman",
                        "/d/beijing/caroad_e1.c"  :  "girl",
                        "/d/beijing/caroad_e2.c"  :  "hun hun",
                        "/d/beijing/caroad_e1.c"  :  "ju min",
                        "/d/beijing/haigang.c"  :  "lao chuanfu",
                        "/d/beijing/tianqiao.c"  :  "boy",
                        "/d/beijing/tianqiao.c"  :  "old woman",
                        "/d/beijing/tianqiao.c"  :  "xiao fan",
                        "/d/beijing/tianqiao.c"  :  "xian ren",
                        "/d/beijing/tianqiao.c"  :  "maiyi ren",
                        "/d/beijing/gaosheng.c"  :  "cha ke",
                        "/d/beijing/gaosheng.c"  :  "cha boshi",
                        "/d/beijing/gaosheng.c"  :  "old man",
                        "/d/beijing/gaosheng.c"  :  "chapu huoji",
                        "/d/beijing/guozijian.c"  :  "shu sheng",
                        "/d/beijing/duchang.c"  :  "liu mang",
                        "/d/beijing/duchang.c"  :  "di pi",
                        "/d/beijing/duchang.c"  :  "du ke",
                        "/d/beijing/duchang.c"  :  "jianghu haoke",
                        "/d/beijing/fu_2.c"  :  "jianghu haoke",
                        "/d/beijing/fu_2.c"  :  "shao fu",
                        "/d/beijing/huichuntang.c"  :  "kid",
                        "/d/beijing/huichuntang.c"  :  "old man",
                        "/d/beijing/huichuntang.c"  :  "yaopu huoji",
                        "/d/beijing/huiying.c"  :  "xiao er",
                        "/d/beijing/huiyingup.c"  :  "qian erbai",
                        "/d/beijing/huiyingup.c"  :  "zhao min",
                        "/d/beijing/huiyingup.c"  :  "zhao yishang",
                        "/d/beijing/qiao.c"  :  "xiao fan",
                        "/d/beijing/kedian.c"  :  "chen laotou",
                        "/d/beijing/kedian.c"  :  "you ren",
                        "/d/beijing/niaoshi.c"  :  "xiu cai",
                        "/d/beijing/niaoshi.c"  :  "fujia dizi",
                        "/d/beijing/qingmu_fang3.c"  :  "fan gang",
                        "/d/beijing/qingmu_fang3.c"  :  "qi biaoqing",
                        "/d/beijing/qingmu_fang2.c"  :  "guan anji",
                        "/d/beijing/qingmu_fang3.c"  :  "feng jizhong",
                        "/d/beijing/qingmu_fang2.c"  :  "jia laoliu",
                        "/d/beijing/qingmu_fang2.c"  :  "qian laoben",
                        "/d/beijing/qingmu_fang1.c"  :  "xu tianchuan",
                        "/d/beijing/huangling.c"  :  "you ren",
                        "/d/beijing/minju_y.c"  :  "ju min",
                        "/d/beijing/tiananmen.c"  :  "kid",
                        "/d/beijing/tiananmen.c"  :  "maiyi ren",
                        "/d/beijing/tiananmen.c"  :  "old man",
                        "/d/beijing/tiantan.c"  :  "you ren",
                        "/d/beijing/tiantan_n.c"  :  "shao fu",
                        "/d/beijing/cagc_w.c"  :  "shao fu",
                        "/d/beijing/cagc_w.c"  :  "xiu cai",
                        "/d/beijing/cagc_w.c"  :  "girl",
                        "/d/beijing/caroad_w1.c"  :  "kid",
                        "/d/beijing/caroad_w2.c"  :  "shu sheng",
                        "/d/beijing/caroad_w2.c"  :  "fujia dizi",
                        "/d/beijing/caroad_w1.c"  :  "jianghu haoke",
                        "/d/beijing/caroad_w2.c"  :  "boy",
                        "/d/beijing/xi_2.c"  :  "man",
                        "/d/beijing/xi_2.c"  :  "shao fu",
                        "/d/beijing/xi_1.c"  :  "tiao fu",
                        "/d/beijing/xi_1.c"  :  "boy",
                        "/d/beijing/xi_2.c"  :  "xiao fan",
                        "/d/beijing/bei_1.c"  :  "you ren",
                        "/d/beijing/bei_3.c"  :  "girl",
                        "/d/beijing/bei_4.c"  :  "you ren",
                        "/d/beijing/shi_2.c"  :  "boy",
                        "/d/beijing/shi_1.c"  :  "liu mang",
                        "/d/beijing/huadian.c"  :  "shao nv",
                        "/d/beijing/road10.c"  :  "tiao fu",
                        "/d/beijing/zhuang9.c"  :  "san furen",
                        "/d/beijing/zhuang1.c"  :  "seng ren",
                        "/d/beijing/xiaotan.c"  :  "youke",
                        "/d/beijing/xiaotan.c"  :  "xiao er",
                        "/d/beijing/yancao.c"  :  "old man",
                        "/d/beijing/yangliu1.c"  :  "old woman",
                        "/d/beijing/liandan_yaoshi.c"  :  "yao chun",
                        "/d/beijing/yong_1.c"  :  "di pi",
                        "/d/beijing/yong_1.c"  :  "boy",
                    ]),
        "bjw"     : ([
                        "/d/beijing/caishi.c"  :  "ju min",
                        "/d/beijing/caishi.c"  :  "cai fan",
                        "/d/beijing/cagc_s.c"  :  "shuahou ren",
                        "/d/beijing/cagc_s.c"  :  "xian ren",
                        "/d/beijing/zhuang8.c"  :  "dizi",
                        "/d/beijing/chaoyang_dao1.c"  :  "tang zi",
                        "/d/beijing/chaoyang_dao2.c"  :  "tiao fu",
                        "/d/beijing/ximenkou.c"  :  "old man",
                        "/d/beijing/ximenkou.c"  :  "tang zi",
                        "/d/beijing/ximenkou.c"  :  "tiao fu",
                        "/d/beijing/tiepu.c"  :  "huoji",
                        "/d/beijing/tiepu.c"  :  "tie jiang",
                        "/d/beijing/yongdingdao.c"  :  "kid",
                        "/d/beijing/yongdingdao.c"  :  "tiao fu",
                        "/d/beijing/yongdingdao.c"  :  "tang zi",
                        "/d/beijing/guandao_1.c"  :  "tang zi",
                        "/d/beijing/qingmu_dating.c"  :  "chen jinnan",
                        "/d/beijing/road9.c"  :  "tangzi shou",
                        "/d/beijing/road4.c"  :  "jian ke",
                        "/d/beijing/road1.c"  :  "tiao fu",
                        "/d/beijing/road5.c"  :  "seng ren",
                        "/d/beijing/road2.c"  :  "tangzi shou",
                        "/d/beijing/road3.c"  :  "shu sheng",
                        "/d/beijing/road7.c"  :  "jianghu haoke",
                        "/d/beijing/qingmu_dayuan.c"  :  "xuan zhen",
                        "/d/beijing/di_dajie2.c"  :  "di pi",
                        "/d/beijing/di_dajie2.c"  :  "tiao fu",
                        "/d/beijing/di_donggc.c"  :  "kid",
                        "/d/beijing/di_donggc.c"  :  "shao fu",
                        "/d/beijing/di_donggc.c"  :  "liu mang",
                        "/d/beijing/dianmen.c"  :  "old man",
                        "/d/beijing/dianmen.c"  :  "kid",
                        "/d/beijing/di_xigc.c"  :  "hun hun",
                        "/d/beijing/di_xigc.c"  :  "xian ren",
                        "/d/beijing/dong_3.c"  :  "shu sheng",
                        "/d/beijing/di_4.c"  :  "boy",
                        "/d/beijing/di_1.c"  :  "you ren",
                        "/d/beijing/di_3.c"  :  "di pi",
                        "/d/beijing/di_1.c"  :  "kid",
                        "/d/beijing/di_3.c"  :  "tiao fu",
                        "/d/beijing/di_1.c"  :  "xiu cai",
                        "/d/beijing/cagc_e.c"  :  "shu sheng",
                        "/d/beijing/cagc_e.c"  :  "xian ren",
                        "/d/beijing/caroad_e2.c"  :  "old woman",
                        "/d/beijing/caroad_e1.c"  :  "girl",
                        "/d/beijing/caroad_e2.c"  :  "hun hun",
                        "/d/beijing/caroad_e1.c"  :  "ju min",
                        "/d/beijing/haigang.c"  :  "lao chuanfu",
                        "/d/beijing/tianqiao.c"  :  "boy",
                        "/d/beijing/tianqiao.c"  :  "old woman",
                        "/d/beijing/tianqiao.c"  :  "xiao fan",
                        "/d/beijing/tianqiao.c"  :  "xian ren",
                        "/d/beijing/tianqiao.c"  :  "maiyi ren",
                        "/d/beijing/gaosheng.c"  :  "cha ke",
                        "/d/beijing/gaosheng.c"  :  "cha boshi",
                        "/d/beijing/gaosheng.c"  :  "old man",
                        "/d/beijing/gaosheng.c"  :  "chapu huoji",
                        "/d/beijing/guozijian.c"  :  "shu sheng",
                        "/d/beijing/duchang.c"  :  "liu mang",
                        "/d/beijing/duchang.c"  :  "di pi",
                        "/d/beijing/duchang.c"  :  "du ke",
                        "/d/beijing/duchang.c"  :  "jianghu haoke",
                        "/d/beijing/fu_2.c"  :  "jianghu haoke",
                        "/d/beijing/fu_2.c"  :  "shao fu",
                        "/d/beijing/huichuntang.c"  :  "kid",
                        "/d/beijing/huichuntang.c"  :  "old man",
                        "/d/beijing/huichuntang.c"  :  "yaopu huoji",
                        "/d/beijing/huiying.c"  :  "xiao er",
                        "/d/beijing/huiyingup.c"  :  "qian erbai",
                        "/d/beijing/huiyingup.c"  :  "zhao min",
                        "/d/beijing/huiyingup.c"  :  "zhao yishang",
                        "/d/beijing/qiao.c"  :  "xiao fan",
                        "/d/beijing/kedian.c"  :  "chen laotou",
                        "/d/beijing/kedian.c"  :  "you ren",
                        "/d/beijing/niaoshi.c"  :  "xiu cai",
                        "/d/beijing/niaoshi.c"  :  "fujia dizi",
                        "/d/beijing/qingmu_fang3.c"  :  "fan gang",
                        "/d/beijing/qingmu_fang3.c"  :  "qi biaoqing",
                        "/d/beijing/qingmu_fang2.c"  :  "guan anji",
                        "/d/beijing/qingmu_fang3.c"  :  "feng jizhong",
                        "/d/beijing/qingmu_fang2.c"  :  "jia laoliu",
                        "/d/beijing/qingmu_fang2.c"  :  "qian laoben",
                        "/d/beijing/qingmu_fang1.c"  :  "xu tianchuan",
                        "/d/beijing/huangling.c"  :  "you ren",
                        "/d/beijing/minju_y.c"  :  "ju min",
                        "/d/beijing/tiananmen.c"  :  "kid",
                        "/d/beijing/tiananmen.c"  :  "maiyi ren",
                        "/d/beijing/tiananmen.c"  :  "old man",
                        "/d/beijing/tiantan.c"  :  "you ren",
                        "/d/beijing/tiantan_n.c"  :  "shao fu",
                        "/d/beijing/cagc_w.c"  :  "shao fu",
                        "/d/beijing/cagc_w.c"  :  "xiu cai",
                        "/d/beijing/cagc_w.c"  :  "girl",
                        "/d/beijing/caroad_w1.c"  :  "kid",
                        "/d/beijing/caroad_w2.c"  :  "shu sheng",
                        "/d/beijing/caroad_w2.c"  :  "fujia dizi",
                        "/d/beijing/caroad_w1.c"  :  "jianghu haoke",
                        "/d/beijing/caroad_w2.c"  :  "boy",
                        "/d/beijing/xi_2.c"  :  "man",
                        "/d/beijing/xi_2.c"  :  "shao fu",
                        "/d/beijing/xi_1.c"  :  "tiao fu",
                        "/d/beijing/xi_1.c"  :  "boy",
                        "/d/beijing/xi_2.c"  :  "xiao fan",
                        "/d/beijing/bei_1.c"  :  "you ren",
                        "/d/beijing/bei_3.c"  :  "girl",
                        "/d/beijing/bei_4.c"  :  "you ren",
                        "/d/beijing/shi_2.c"  :  "boy",
                        "/d/beijing/shi_1.c"  :  "liu mang",
                        "/d/beijing/huadian.c"  :  "shao nv",
                        "/d/beijing/road10.c"  :  "tiao fu",
                        "/d/beijing/zhuang9.c"  :  "san furen",
                        "/d/beijing/zhuang1.c"  :  "seng ren",
                        "/d/beijing/xiaotan.c"  :  "youke",
                        "/d/beijing/xiaotan.c"  :  "xiao er",
                        "/d/beijing/yancao.c"  :  "old man",
                        "/d/beijing/yangliu1.c"  :  "old woman",
                        "/d/beijing/liandan_yaoshi.c"  :  "yao chun",
                        "/d/beijing/yong_1.c"  :  "di pi",
                        "/d/beijing/yong_1.c"  :  "boy",
                    ]),
        "ca"      : ([
                        "/d/changan/baozipu"  :  "huo ji",
                        "/d/changan/baoxiangsi"  :  "monk",
                        "/d/changan/weapon-shop"  :  "murong hao",
                        "/d/changan/tea-shop"  :  "waiter",
                        "/d/changan/tea-shop"  :  "shuoshu laoren",
                        "/d/changan/miao"  :  "keeper",
                        "/d/changan/baodian"  :  "xiang ke",
                        "/d/changan/duchang"  :  "zhuang jia",
                        "/d/changan/fangzhangshi"  :  "huitong chanshi",
                        "/d/changan/guozijian"  :  "li boyuan",
                        "/d/changan/biaoju-dating"  :  "wang yuanba",
                        "/d/changan/huadian"  :  "maihua guniang",
                        "/d/changan/yaopu"  :  "shi jiugong",
                        "/d/changan/huiwenge"  :  "shu chi",
                        "/d/changan/mianguan"  :  "lao zhang",
                        "/d/changan/piandian"  :  "jing ming",
                        "/d/changan/piandian"  :  "jing xuan",
                        "/d/changan/xiaojia-pianting"  :  "yahuan",
                        "/d/changan/shoushi-dian"  :  "chen laoban",
                        "/d/changan/fruit-shop"  :  "zhang lanxiang",
                        "/d/changan/bank"  :  "tie gongji",
                        "/d/changan/tuchangguan"  :  "ji nu",
                        "/d/changan/jiulou"  :  "xiaoer",
                        "/d/changan/jiulou2"  :  "yang laoban",
                        "/d/changan/xiyuan"  :  "xi zi",
                        "/d/changan/dangpu"  :  "xiao wanxi",
                        "/d/changan/xiaojiuguan"  :  "ru hua",
                        "/d/changan/xunbufang"  :  "bu tou",
                        "/d/changan/kezhan"  :  "xiaoer",
                        "/d/changan/zahuopu"  :  "liu laoshi",
                        "/d/changan/zhubaohang"  :  "jin fuhuan",
                     ]),
        "yz"      :  ([
                        "/d/city/beidajie1"  :  "ouyang ke",
                        "/d/city/beimen"  :  "ma chaoxing",
                        "/d/city/dayuan"  :  "guan jia",
                        "/d/city/dayuan"  :  "jia ding",
                        "/d/city/dongxiang"  :  "hong niang",
                        "/d/city/houyuan"  :  "cui yuanwai",
                        "/d/city/xixiang"  :  "cui yingying",
                        "/d/city/garments"  :  "zeng rou",
                        "/d/city/chaguan"  :  "aqing sao",
                        "/d/city/datiepu"  :  "tie jiang",
                        "/d/city/dangpu"  :  "tang nan",
                        "/d/city/duchang"  :  "pang toutuo",
                        "/d/city/gzs"  :  "yao yueling",
                        "/d/city/lichunyuan"  :  "mao shiba",
                        "/d/city/lichunyuan"  :  "wei chunfang",
                        "/d/city/lichunyuan"  :  "kong kong",
                        "/d/city/lichunyuan2"  :  "gui gong",
                        "/d/city/neizhai"  :  "cheng yuhuan",
                        "/d/city/nandajie1"  :  "liumang tou",
                        "/d/city/nandajie2"  :  "tuobo seng",
                        "/d/city/nandajie1"  :  "xiao hunhun",
                        "/d/city/nandajie1"  :  "liu mang",
                        "/d/city/nanmen"  :  "shi song",
                        "/d/city/qianzhuang"  :  "qian yankai",
                        "/d/city/shuyuan"  :  "zhu xi",
                        "/d/city/pomiao"  :  "lu youjiao",
                        "/d/city/pomiao"  :  "peng youjing",
                        "/d/city/xidajie2"  :  "youfang daoren",
                        "/d/city/ximen"  :  "feng gongying",
                        "/d/city/ximenroad"  :  "boy",
                        "/d/city/yamen"  :  "ya yi",
                        "/d/city/wuguan"  :  "chen youde",
                        "/d/city/yaopu"  :  "ping yizhi",
                        "/d/city/zahuopu"  :  "Yang yongfu",
                        "/d/city/zuixianlou"  :  "xiao er",
                        "/d/city/zuixianlou2"  :  "xian laoban",
                        "/d/city/zuixianlou2"  :  "wang wu",
                        "/d/city/zuixianlou3"  :  "taogan xian",
                        "/d/city/zuixianlou3"  :  "taogen xian",
                        "/d/city/zuixianlou3"  :  "taoshi xian",
                        "/d/city/zuixianlou3"  :  "taohua xian",
                        "/d/city/zuixianlou3"  :  "taozhi xian",
                        "/d/city/zuixianlou3"  :  "taoye xian",
                     ]),
        "sz"      :  ([
                        "/d/suzhou/bailianchi"  :  "girl",
                        "/d/suzhou/baodaiqiao"  :  "seller",
                        "/d/suzhou/dangpu"  :  "wang heji",
                        "/d/suzhou/chaguan"  :  "girl",
                        "/d/suzhou/jiudian"  :  "xiao er",
                        "/d/suzhou/datiepu"  :  "tie jiang",
                        "/d/suzhou/dongdajie1"  :  "kid",
                        "/d/suzhou/hongniang-zhuang"  :  "meipo",
                        "/d/suzhou/hong-zoulang"  :  "xiao hongniang",
                        "/d/suzhou/hutong2"  :  "liu mang",
                        "/d/suzhou/hutong2"  :  "liumang tou",
                        "/d/suzhou/jubaozhai"  :  "sun baopi",
                        "/d/suzhou/kedian"  :  "xiao er",
                        "/d/suzhou/yaopu"  :  "yaopu huoji",
                        "/d/suzhou/liuyuan"  :  "girl",
                        "/d/suzhou/shijianshi"  :  "jian ke",
                        "/d/suzhou/shuchang"  :  "gongzi",
                        "/d/suzhou/shuyuan"  :  "lao fuzi",
                        "/d/suzhou/toumenshan"  :  "jian ke",
                        "/d/suzhou/wanjing"  :  "dao ke",
                        "/d/suzhou/wenmeige"  :  "bi nu",
                        "/d/suzhou/xiyuan"  :  "piao you",
                        "/d/suzhou/yanyutang"  :  "ya huan",
                        "/d/suzhou/yingbin-lou1"  :  "xiao er",
                        "/d/suzhou/zhenshi"  :  "seng ren",
                        "/d/suzhou/zhishuang"  :  "girl",
                     ]),
        "cd"      :    ([
                        "/d/city3/northroad3"  :  "jianghu haoke",
                        "/d/city3/northroad3"  :  "jian ke",
                        "/d/city3/bingqidian"  :  "tang huai",
                        "/d/city3/eastroad2"  :  "liumang tou",
                        "/d/city3/eastroad2"  :  "liu mang",
                        "/d/city3/eastroad1"  :  "xiao zei",
                        "/d/city3/yaodian"  :  "yaodian huoji",
                        "/d/city3/kedian"  :  "xiao er",
                        "/d/city3/chufang"  :  "chu niang",
                        "/d/city3/southroad3"  :  "dao ke",
                        "/d/city3/southroad3"  :  "jian ke",
                        "/d/city3/jiudian"  :  "tang",
                        "/d/city3/jiudian"  :  "xiao er",
                        "/d/city3/westroad1"  :  "seller",
                        "/d/city3/westroad1"  :  "liu mang",
                        "/d/city3/westroad2"  :  "tangzi shou",
                        "/d/city3/westroad3"  :  "jianghu haoke",
                     ]),
        "hz"      :  ([
                        "/d/hangzhou/dalu1"  :  "hong hua",
                        "/d/hangzhou/dalu1"  :  "tiao fu",
                        "/d/hangzhou/duanqiao"  :  "poor man",
                        "/d/hangzhou/faxisi"  :  "lao heshang",
                        "/d/hangzhou/yaodian"  :  "hu qingyu",
                        "/d/hangzhou/jujingyuan"  :  "hong hua",
                        "/d/hangzhou/jujingyuan"  :  "jian ke",
                        "/d/hangzhou/lingyinsi"  :  "lao heshang",
                        "/d/hangzhou/liuzhuang"  :  "guan jia",
                        "/d/hangzhou/liuzhuang"  :  "jia ding",
                        "/d/hangzhou/jiulou"  :  "xiao er",
                        "/d/hangzhou/maojiabu"  :  "old woman",
                        "/d/hangzhou/maojiabu"  :  "boy",
                        "/d/hangzhou/qiantang"  :  "jian ke",
                        "/d/hangzhou/road17"  :  "chu yuan",
                        "/d/hangzhou/road14"  :  "luo bing",
                        "/d/hangzhou/road6"  :  "liumang tou",
                        "/d/hangzhou/road12"  :  "qing bing",
                        "/d/hangzhou/road7"  :  "youfang daoren",
                        "/d/hangzhou/road6"  :  "liu mang",
                        "/d/hangzhou/road19"  :  "dao ke",
                        "/d/hangzhou/road12"  :  "li kexiu",
                        "/d/hangzhou/road14"  :  "wen tailai",
                        "/d/hangzhou/road5"  :  "tiao fu",
                        "/d/hangzhou/road2"  :  "xianghuo daoren",
                        "/d/hangzhou/road19"  :  "long jun",
                        "/d/hangzhou/road5"  :  "hong hua",
                        "/d/hangzhou/road16"  :  "bai zhen",
                        "/d/hangzhou/qingbomen"  :  "girl",
                        "/d/hangzhou/suti4"  :  "li yuanzhi",
                        "/d/hangzhou/suti7"  :  "shu sheng",
                        "/d/hangzhou/kedian"  :  "xiao er",
                        "/d/hangzhou/tiejiangpu"  :  "tiejiang",
                        "/d/hangzhou/tulu1"  :  "boy",
                        "/d/hangzhou/yuquan"  :  "youke",
                        "/d/hangzhou/yuquan"  :  "yue nv",
                     ]),
        "xy"      :  ([
                        "/d/xiangyang/tiejiangpu"  :  "tiejiang",
                        "/d/xiangyang/caodi4"  :  "cheng lingsu",
                        "/d/xiangyang/caodi1"  :  "tuo lei",
                        "/d/xiangyang/juyichufang"  :  "shaofan shifu",
                        "/d/xiangyang/jiekou2"  :  "kid",
                        "/d/xiangyang/jiekou2"  :  "seller",
                        "/d/xiangyang/juyiyuan"  :  "zhu ziliu",
                        "/d/xiangyang/dangpu"  :  "qiu hang",
                        "/d/xiangyang/biaoju"  :  "biao tou",
                        "/d/xiangyang/guofugate"  :  "Yelv qi",
                        "/d/xiangyang/guofugate"  :  "jia ding",
                        "/d/xiangyang/guofuhuayuan"  :  "huang rong",
                        "/d/xiangyang/guofuting"  :  "guo jing",
                        "/d/xiangyang/xiaorong2"  :  "boy",
                        "/d/xiangyang/xiaorong2"  :  "girl",
                        "/d/xiangyang/xiaorong1"  :  "kid",
                        "/d/xiangyang/juyihuayuan"  :  "guo fu",
                        "/d/xiangyang/jiedao"  :  "poor man",
                        "/d/xiangyang/nixianglou"  :  "xiao er",
                        "/d/xiangyang/mujiang"  :  "mu jiang",
                        "/d/xiangyang/southjie2"  :  "liu mang",
                        "/d/xiangyang/qianzhuang"  :  "huang zhen",
                        "/d/xiangyang/shudian"  :  "shudian laoban",
                        "/d/xiangyang/juyiwupin"  :  "wu xiuwen",
                        "/d/xiangyang/westjie1"  :  "poor man",
                        "/d/xiangyang/westjie2"  :  "wu santong",
                        "/d/xiangyang/kedian"  :  "wu dunru",
                        "/d/xiangyang/xinluofang"  :  "gaoli shang",
                        "/d/xiangyang/xuetang"  :  "lao xiansheng",
                        "/d/xiangyang/yaopu"  :  "yaopu huoji",
                     ]),
        "dl"      :  ([
                        "/d/dali/atoubu"  :  "lie ren",
                        "/d/dali/baiyiminju"  :  "oldman",
                        "/d/dali/baiyiminju"  :  "girl",
                        "/d/dali/banshan"  :  "kanzhu ren",
                        "/d/dali/bijishan"  :  "youke",
                        "/d/dali/biluoshan"  :  "nong fu",
                        "/d/dali/buxiongbu"  :  "shang fan",
                        "/d/dali/cangshanlu1"  :  "lie ren",
                        "/d/dali/chahua2"  :  "yanghua nu",
                        "/d/dali/chahua9"  :  "mu wanqing",
                        "/d/dali/changlang"  :  "duan wuwei",
                        "/d/dali/caopo"  :  "muyang ren",
                        "/d/dali/yanan1"  :  "cun fu",
                        "/d/dali/feilihusouth"  :  "yu fu",
                        "/d/dali/langan3"  :  "yangcan nu",
                        "/d/dali/langan2"  :  "kid",
                        "/d/dali/langan4"  :  "fangsha nu",
                        "/d/dali/dalangan2"  :  "lao jisi",
                        "/d/dali/gelucheng"  :  "muyang ren",
                        "/d/dali/road3"  :  "girl",
                        "/d/dali/guibingshi2"  :  "daizu shouling",
                        "/d/dali/hebian"  :  "shang fan",
                        "/d/dali/hexi"  :  "shang fan",
                        "/d/dali/jisidawu1"  :  "lao jisi",
                        "/d/dali/zhulou5"  :  "ji si",
                        "/d/dali/jianchuan"  :  "lie ren",
                        "/d/dali/jianchuan"  :  "pihuo shang",
                        "/d/dali/jinzhihe"  :  "seng ren",
                        "/d/dali/kedian"  :  "xiao er",
                        "/d/dali/shanjian"  :  "caisun ren",
                        "/d/dali/luwang"  :  "shang fan",
                        "/d/dali/minadian"  :  "shao nu",
                        "/d/dali/nianhuasi"  :  "po chen",
                        "/d/dali/nianhuasi"  :  "po yi",
                        "/d/dali/nongtian1"  :  "nong fu",
                        "/d/dali/paifang"  :  "hu yizhi",
                        "/d/dali/qingzhulin"  :  "caisun ren",
                        "/d/dali/qingxi"  :  "biao tou",
                        "/d/dali/yulin"  :  "lie ren",
                        "/d/dali/sanglin"  :  "caisang nu",
                        "/d/dali/sheguta"  :  "kid",
                        "/d/dali/stoneshop"  :  "shi jiang",
                        "/d/dali/shuitian"  :  "nong fu",
                        "/d/dali/taiheju"  :  "xiao er",
                        "/d/dali/tusifu"  :  "da tusi",
                        "/d/dali/tusifu"  :  "shi cong",
                        "/d/dali/wunong"  :  "shang fan",
                        "/d/dali/wuyiminju1"  :  "muyang nu",
                        "/d/dali/wuyiminju4"  :  "kid",
                        "/d/dali/wuyiminju2"  :  "lie ren",
                        "/d/dali/wuding"  :  "gu niang",
                        "/d/dali/xizhou"  :  "ke shang",
                        "/d/dali/xiaguan"  :  "shang fan",
                        "/d/dali/xiaguan"  :  "shang fan",
                        "/d/dali/garments"  :  "xue laoban",
                        "/d/dali/yangzong"  :  "shang fan",
                        "/d/dali/yangcanfang"  :  "yangcan nu",
                        "/d/dali/yaoshop"  :  "he hongyao",
                        "/d/dali/zhulou4"  :  "zu zhang",
                        "/d/dali/tusiyishi"  :  "da tusi",
                        "/d/dali/tusiyishi"  :  "zu touren",
                        "/d/dali/yixibu"  :  "shao nu",
                        "/d/dali/yujia"  :  "fu nu",
                        "/d/dali/yuxiashan"  :  "youke",
                        "/d/dali/yuxuguan"  :  "dao baifeng",
                        "/d/dali/yuxuguanqian"  :  "xiao daogu",
                        "/d/dali/zhenxiong"  :  "muyang nu",
                        "/d/dali/zhenxiong"  :  "shang fan",
                        "/d/dali/center"  :  "jianghu yiren",
                     ]),
]);

nosave mapping place = ([
        "北京东城": ({
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
        "北京西城" : ({
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
        "扬州城"   : ({
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
         "长安城"   : ({
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
        "成都城"   : ({
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
        "苏州城"   : ({
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
        "杭州城"   : ({
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
        "襄阳城"   : ({
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
        "大理一带" : ({
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

varargs mixed query_city_quest(string arg,string bh);
varargs mixed query_zhuisha_quest(string type,string bh);
void ready_to_start();
object create_npc(mixed me);
void init_npc_skill(object ob, int lvl);
void start_quest();
int get_bianhao(string arg);
varargs void place_npc(object ob, string *not_place);
void random_move(object ob);
int not_wizard(object ob);
int check_level(object ob);
string check_difficult(int lvl);
string check_reward(int lvl);
string bad_zhuisha_msg(string name,string place,string difficult);
string good_zhuisha_msg(string name,string place,string difficult);
void heart_beat();
void check_xuncheng();
void check_city_quest();
int is_the_bang(mapping arg,string type);
varargs mixed create_quest(string the_city,string bang_type,object player);
varargs void delete_city_quest(string arg,string type,string bh);

//查询指定城市的任务列表，使用参数bh则返回编号为bh的任务
varargs mixed query_city_quest(string arg,string type,string bh)
{
        int i;
        mapping *bang_quest;

        if (!arg) return bang_city_quest;

        bang_quest = bang_city_quest[arg];

        if (type)
                bang_quest = filter_array(bang_quest,(: is_the_bang($1,$2) :),type);

        if (bh)
        {
                for (i = 0;i < sizeof(bang_quest);i++)
                        if (bang_quest[i]["id"] == bh)
                                return bang_quest[i];
                return 0;
        }

        return bang_quest;
}

//查询追杀任务列表，使用参数BH为返回编号为bh的任务
varargs mixed query_zhuisha_quest(string type,string bh)
{
        int i;
        mapping *bang_quest = ({});
        bang_quest = bang_zs;

        if (type)
                bang_quest = filter_array(bang_quest,(: is_the_bang($1,$2) :),type);

        if (!bh) return bang_quest;

        for (i = 0;i < sizeof(bang_quest);i++)
                if (bang_quest[i]["id"] == bh)
                        return bang_quest[i];

        return 0;
}

//用于产生帮派特定任务，该任务是以帮派通知的形式发送给玩家
//特殊任务分为两种
//第一种，只发送给一个玩家，只能该玩家去完成
//第二种，发送给所有的玩家，谁抢先完成谁得到奖励
void ready_to_start()
{
        int num;
        object *all_user;
        remove_call_out("start_quest");
        all_user = users();
        all_user = filter_array(all_user,(: interactive($1) &&
                                !wizardp($1) &&
                                $1->query("combat_exp") >= $2 &&
                                $1->query("combat_exp") <= $3 &&
                                environment($1) &&
                                !$1->is_ghost() &&
                                !$1->in_prison() &&
                                ($1->query("bang_good") || $1->query("bang_bad")) :),10000,600000);

        num = 300 - sizeof(all_user);	//符合条件的玩家越多，则特殊任务产生速度越高
        if (num < MIN_IDLE) num = MIN_IDLE;
        call_out("start_quest", num);
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "任务精灵");
        CHANNEL_D->do_channel( this_object(), "task", "帮会任务系统已经启动。");
        ready_to_start();
        set_heart_beat(2);
}

int clean_up()
{
        return 1;
}

object create_npc(mixed me)
{
        int lvl,exp;
        object ob;

        ob = new(CLASS_D("generate") + "/player_npc");
        NPC_D->generate_cn_name(ob);

        if (objectp(me))
                ob->set_from_me(me,0);
        else
                init_npc_skill(ob,random(sizeof(levels))+1);
        lvl = check_level(ob);
        if (lvl < 1) lvl = 1;
        if (lvl >= sizeof(levels)) lvl = sizeof(levels) - 1;
        exp = sort_array(keys(levels), 1)[lvl - 1];
        ob->set("lvl",lvl);
        ob->set("bonus",levels[exp]*3/2);
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
        my["jing"] = my["eff_jing"] = my["max_jing"] = sk_lvl * 3;
        my["qi"] = my["eff_qi"] = my["max_qi"] = sk_lvl * 6;
        my["jingli"] = my["max_jingli"] = sk_lvl * 2;
        my["neili"] = my["max_neili"] = sk_lvl * 4;
        if (! ob->query_skills())
                return;
        ks = keys(ob->query_skills());
        for (i = 0; i < sizeof(ks); i++)
                ob->set_skill(ks[i], sk_lvl);
}

void start_quest()
{
        object *all_user,ob;
        string the_nation,the_enemy;
        mapping bang_quest;
        int i,num;

        ready_to_start();
        all_user = users();
        //再次确定泥巴中符合条件的玩家数目
        all_user = filter_array(all_user,(: interactive($1) &&
                                !wizardp($1) &&
                                $1->query("combat_exp") >= $2 &&
                                $1->query("combat_exp") <= $3 &&
                                environment($1) &&
                                !$1->is_ghost() &&
                                !$1->in_prison() &&
                                ($1->query("bang_good") || $1->query("bang_bad")) :),10000,600000);

        num = sizeof(all_user);
        //如果没有这类玩家，就中止任务进程
        if (!num) return;
        CHANNEL_D->do_channel( this_object(), "task", "帮会任务系统开始产生追杀任务。");

        ob = create_npc(1);
        bang_quest = ([]);
        place_npc(ob);
        random_move(ob);
        random_move(ob);
        random_move(ob);

        bang_quest["type"]="追杀";
        bang_quest["ob"]=ob;
        bang_quest["bonus"]=ob->query("bonus")*2;
        bang_quest["name"]=ob->name();
        bang_quest["place"]=ob->query("place");
        bang_quest["difficult"]=check_difficult(ob->query("lvl"));
        bang_quest["reward"]=check_reward(ob->query("lvl"));

        if (random(2))	//黑道追杀
        {
                ob->set("shen", ob->query("combat_exp") / 2000);
                bang_quest["bang_type"]="bad";
                bang_quest["msg"]=bad_zhuisha_msg(bang_quest["name"],bang_quest["place"],bang_quest["difficult"]);
                all_user = filter_array(all_user,(: $1->query("bang_bad") :));
                if (sizeof(all_user))
                        for (i = 0;i < sizeof(all_user);i++)
                        {
                                tell_object(all_user[i],HIB"迎面急步过来一位〖"+all_user[i]->query("bang_bad/name")+


                                            "〗兄弟朝你急急忙忙地说：“黑道同盟发下追杀令了！\n"NOR+
                                            bang_quest["msg"] + "”\n");
                                tell_object(all_user[i],"说完又是一抱拳道：“兄弟还有要务在身，先行告辞！\n");
                        }
                else destruct(ob);
        }
        else		//白道追杀
        {
                ob->set("shen", -ob->query("combat_exp") / 2000);
                bang_quest["bang_type"]="good";
                bang_quest["msg"]=good_zhuisha_msg(bang_quest["name"],bang_quest["place"],bang_quest["difficult"]);
                all_user = filter_array(all_user,(: $1->query("bang_good") :));
                if (sizeof(all_user))
                        for (i = 0;i < sizeof(all_user);i++)
                        {
                                tell_object(all_user[i],HIW"迎面奔来一位〖"+all_user[i]->query("bang_good/name")+


                                            "〗弟兄朝你猛招手并擦着满脸的汗水悄声道：“白道联盟"+
                                            "发下通缉令啦！\n"NOR+
                                            bang_quest["msg"] + "”\n");
                                tell_object(all_user[i],"说完又是一抱拳道：“在下还有要务在身，先行告辞！\n");
                        }
                else destruct(ob);
        }
        if (ob)
        {
                //每个任务都必须有自己的流水号，使用get_bianhao()函数来获取统一的流水号
                bang_quest["num"]=get_bianhao("zhuisha");
                bang_quest["id"]="zs"+(string)bang_quest["num"];
                bang_zs += ({ bang_quest });
                ob->set("bang_quest",bang_quest);
        }
        return;
}

int get_bianhao(string arg)
{
        int i,have_it,bh;
        have_it = 0;
        bh = 1;
        switch(arg)
        {
                case "zhuisha":
                        for (;;)
                        {
                                if (!sizeof(bang_zs)) break;
                                for (i = 0;i < sizeof(bang_zs);i++)
                                        if (bang_zs[i]["num"] == bh)
                                                have_it = 1;
                                if (have_it)
                                {
                                        have_it = 0;
                                        bh++;
                                        continue;
                                } else break;
                        }
                        break;
                default:
                        for (;;)
                        {
                                if (!sizeof(bang_city_quest[arg])) break;
                                for (i = 0;i < sizeof(bang_city_quest[arg]);i++)
                                        if (bang_city_quest[arg][i]["num"] == bh)
                                                have_it = 1;
                                if (have_it)
                                {
                                        have_it = 0;
                                        bh++;
                                        continue;
                                } else break;
                        }
                        break;
        }
        return bh;
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

// place npc
varargs void place_npc(object ob, string *not_place)
{
        string *kp;
        string p;
        string startroom;
        object pos;

        kp = keys(place);
        if (arrayp(not_place))
                kp -= not_place;
        for (;;)
        {
                p = kp[random(sizeof(kp))];
                startroom = place[p][random(sizeof(place[p]))];
                if (! objectp(pos = get_object(startroom)))
                {
                        log_file("log", sprintf("error to place npc to %s:%s\n",
                                                p, startroom));
                        continue;
                }
                break;
        }

        ob->move(pos);
        ob->set("place", p);
        ob->set("startroom", startroom);
        ob->set_temp("moved", ({ }));
        message_vision("$N走了过来。\n", ob);
}

int check_level(object ob)
{
        int *exp;
        int i;

        exp = sort_array(keys(levels), 1);
        for (i = 0; i < sizeof(exp); i++)
                if (ob->query("combat_exp") < exp[i]) break;
        return i;
}

string check_difficult(int lvl)
{
        string difficult;

        switch(lvl)
        {
                case 1:
                case 2:
                        difficult = "很容易";
                        break;
                case 3:
                case 4:
                        difficult = "容易";
                        break;
                case 5:
                case 6:
                        difficult = "较容易";
                        break;
                case 7:
                case 8:
                        difficult = "中等";
                        break;
                case 9:
                case 10:
                        difficult = "较困难";
                        break;
                case 11:
                case 12:
                        difficult = "困难";
                        break;
                default:
                        difficult = "很困难";
                        break;
        }
        return difficult;
}

string check_reward(int lvl)
{
        string reward;

        switch(lvl)
        {
                case 1:
                case 2:
                        reward = "很少";
                        break;
                case 3:
                case 4:
                        reward = "少";
                        break;
                case 5:
                case 6:
                        reward = "较少";
                        break;
                case 7:
                case 8:
                        reward = "中等";
                        break;
                case 9:
                case 10:
                        reward = "较高";
                        break;
                case 11:
                case 12:
                        reward = "高";
                        break;
                default:
                        reward = "很高";
                        break;
        }
        return reward;
}

string bad_zhuisha_msg(string name,string place,string difficult)
{
        string msg1,msg2,msg3,msg4,msg5;
        msg1 = replace_string(bad_msg1[random(sizeof(bad_msg1))],"name",name);
        msg2 = search_msg[random(sizeof(search_msg))];
        msg3 = replace_string(bad_msg2[random(sizeof(bad_msg2))],"place",place);
        msg4 = bad_msg3[random(sizeof(bad_msg3))];
        msg5 = "这个任务难度据其他兄弟说是" + difficult + "，这是你立功的机会啊！";
        return msg1 + msg2 + "\n" + msg3 + msg4 + "\n" + msg5;
}

string good_zhuisha_msg(string name,string place,string difficult)
{
        string msg1,msg2,msg3,msg4,msg5;
        msg1 = replace_string(good_msg1[random(sizeof(good_msg1))],"name",name);
        msg2 = search_msg[random(sizeof(search_msg))];
        msg3 = replace_string(good_msg2[random(sizeof(good_msg2))],"place",place);
        msg4 = good_msg3[random(sizeof(good_msg3))];
        msg5 = "这个任务难度据其他同道说是" + difficult + "，你自己看着办！";
        return msg1 + msg2 + "\n" + msg3 + msg4 + "\n" + msg5;
}

void heart_beat()
{
        int i;

        //检查追杀任务，如果目标已经不在，就从追杀任务列表中去除
        if (sizeof(bang_zs))
                for (i = 0;i < sizeof(bang_zs);i++)
                        if (!objectp(bang_zs[i]["ob"]))
                                bang_zs[i] = 0;
        bang_zs -= ({ 0 });

        //检查巡城任务
        remove_call_out("check_xuncheng");
        call_out("check_xuncheng",0);

        //检查各个城市的任务
        remove_call_out("check_city_quest");
        call_out("check_city_quest",0);

        set_heart_beat(2);
}

void check_xuncheng()
{
        int i,j,xc_num,bonus,have_it = 0;
        string *city_id,*xc_map,*all_map,the_place,data;
        string bang_id;
        mapping *bang_quest,xc_quest;
        string date;

        date = NATURE_D->game_time();
        sscanf(date, "%s日%*s刻", date);

        city_id = keys(city);
        for (i=0;i < sizeof(city_id);i++)
        {
                bang_quest = bang_city_quest[city_id[i]];

                //如果天数还没有变化，并且巡城任务已经存在，就不处理
                if (sizeof(bang_quest))
                {
                        for (j = 0;j<sizeof(bang_quest);j++)
                                if (bang_quest[j]["id"] == "xc")
                                        //如果存在巡城任务，则看日期，如果日期变化了则删除旧任务
                                        if (bang_quest[j]["date"] == date)
                                                have_it = 1;
                                        else
                                                bang_quest[j] = 0;
                        if (have_it) return;
                }
                bang_quest -= ({ 0 });

                xc_map=({});
                all_map=place[city[city_id[i]]];

                //巡城的奖励根据城市包括的地方大小来确定。
                bonus = sizeof(all_map);
                if (bonus<40) bonus=40;
                if (bonus>70) bonus=70;

                //从该城市地图中随机选择10到20个地点作为巡城任务
                xc_num=10+random(10);
                bonus += xc_num;
                bonus += random(bonus)*2;

                for (j=0;j<xc_num;j++)
                {
                        the_place = all_map[random(sizeof(all_map))];
                        xc_map += ({ the_place });
                        all_map -= ({ the_place });
                }

                xc_quest = ([]);

                xc_quest["id"]="xc";
                xc_quest["time"]=time();
                xc_quest["name"]="巡" + city[city_id[i]];
                xc_quest["type"]="巡城";
                xc_quest["bang_type"]="bad";
                xc_quest["bonus"]=bonus;
                xc_quest["enable"]=1;
                xc_quest["place"]=xc_map;
                xc_quest["date"]=date;
                xc_quest["difficult"]="容易";
                xc_quest["reward"]="较高";
                xc_quest["msg"] = "你需要巡逻以下地区：\n";
                for (j=0;j<sizeof(xc_quest["place"]);j++)
                        xc_quest["msg"] += get_object(xc_quest["place"][j])->short() + "\n";
                bang_quest += ({ xc_quest });
                bang_city_quest[city_id[i]] = bang_quest;
        }
        return;
}

void check_city_quest()
{
        int i,j,new_num;
        string *city_id;
        mapping *bang_quest,*bang_quest_good,*bang_quest_bad;
        mixed new_quest;

        city_id = keys(city);
        for (i = 0;i < sizeof(city_id);i++)
        {
                bang_quest = bang_city_quest[city_id[i]];

                bang_quest -= ({ 0 });

               //检查任务状况，清除旧任务
                if (sizeof(bang_quest))
                        for (j=0;j<sizeof(bang_quest);j++)
                                if (time() - bang_quest[j]["time"] > WAIT_TIME ||
                                    (bang_quest[j]["type"] == "铲除外敌" && !objectp(bang_quest[j]["ob"])) ||
                                    (bang_quest[j]["type"] == "调解纠纷" && !objectp(bang_quest[j]["ob"])))
                                {
                                        if ((bang_quest[j]["type"] == "铲除外敌" || bang_quest[j]["type"] == "调解纠纷") &&
                                            objectp(bang_quest[j]["ob"]))
                                                bang_quest[j]["ob"]->destruct_me();
                                        bang_quest[j]=0;
                                }

                bang_quest -= ({ 0 });

                //检查正派任务是否充足
                bang_quest_good = filter_array(bang_quest,(: is_the_bang($1,"good") :));

                //清除五分钟之内没人做的任务，统计任务的数量
                if (sizeof(bang_quest_good))
                        new_num = 20 - sizeof(bang_quest_good);
                else new_num = 20;

                //让任务保持在20个左右，追杀任务不算在内
                if (new_num > 0)
                        for (j = 0;j < new_num;j++)
                        {
                                new_quest = create_quest(city_id[i],"good");
                                {
                                        bang_quest += ({ new_quest });
                                        //重新设置城市任务列表
                                        bang_city_quest[city_id[i]] = bang_quest;
                                }
                        }

                //检查黑道任务是否充足
                bang_quest_bad = filter_array(bang_quest,(: is_the_bang($1,"bad") :));

                //清除五分钟之内没人做的任务，统计任务的数量
                if (sizeof(bang_quest_bad))
                        new_num = 20 - sizeof(bang_quest_bad);
                else new_num = 20;

                //让任务保持在20个左右，追杀任务不算在内
                if (new_num > 0)
                        for (j = 0;j < new_num;j++)
                        {
                                new_quest = create_quest(city_id[i],"bad");
                                if (mapp(new_quest))
                                {
                                        bang_quest += ({ new_quest });
                                        //重新设置城市任务列表
                                        bang_city_quest[city_id[i]] = bang_quest;
                                }
                        }

        }
        return;
}

int is_the_bang(mapping arg,string type)
{
        if (arg["bang_type"] == type)
                return 1;

        return 0;
}

varargs mixed create_quest(string the_city,string bang_type,object player)
{
        string room,*env_rooms,obj_name,*all_city,other_city;
        mapping new_quest,obj_mapp;
        mapping all_static_npc;
        object the_room,the_npc,env,npc,jiufen_npc;
        int i,j,control,bh;

        control = 0;		//用这个变量来控制循环
        if (bang_type == "good")
        {
                switch(random(4))
                {
                        case 0:
                                all_static_npc = static_npc[the_city];
                                env_rooms = keys(all_static_npc);
                                for (;;)
                                {
                                        if (control > 50) break;	//循环超过50就中断
                                        room = env_rooms[random(sizeof(env_rooms))];
                                        env = get_object(room);
                                        if (!env)
                                                log_file("static/party_quest",sprintf("门派任务错误记录：%s\n",room));
                                        else if (! objectp(npc = present(all_static_npc[room], env)) ||
                                                        npc->query("shen") < 0)
                                        {
                                                control ++;
                                                continue;
                                        } else break;
                                }
                                if (objectp(npc))
                                {
                                        new_quest = ([]);
                                        new_quest["target"]=base_name(npc);
                                        new_quest["bang_type"]="good";
                                        new_quest["time"]=time();
                                        new_quest["num"]=get_bianhao(the_city);
                                        new_quest["id"]=the_city+(string)new_quest["num"];
                                        new_quest["type"] = "寻找物品";
                                        switch(random(3))
                                        {
                                                case 0:
                                                        obj_mapp = QUEST_GOOD_OBJ("0xun")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 50;
                                                        new_quest["difficult"] = "容易";
                                                        new_quest["reward"] = "少";
                                                        break;
                                                case 2:
                                                        obj_mapp = QUEST_GOOD_OBJ("1xun")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 80;
                                                        new_quest["difficult"] = "中等";
                                                        new_quest["reward"] = "中等";
                                                        break;
                                                case 1:
                                                        obj_mapp = QUEST_GOOD_OBJ("2xun")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 110;
                                                        new_quest["difficult"] = "困难";
                                                        new_quest["reward"] = "高";
                                                        break;
                                        }
                                        new_quest["name"]="帮" + room->short() + "的" + npc->name() +
                                                          "找到" + new_quest["obj_name"];
                                        new_quest["msg"]=room->short() + "的" + npc->name() +
                                                          "需要" + new_quest["obj_name"] +
                                                          "，你去把它找到并送过去。";
                                        return new_quest;
                                } else return 0;
                                break;
                        case 1:
                                if (objectp(player))
                                        npc = create_npc(player);
                                else
                                        npc = create_npc(1);

                                env_rooms = place[city[the_city]];
                                room = env_rooms[random(sizeof(env_rooms))];
                                env = get_object(room);
                                if (!env)
                                        log_file("static/party_quest",sprintf("门派任务错误记录：%s\n",room));
                                npc->move(env);
                                npc->set("place", env->short());
                                npc->set("startroom", room);
                                npc->set_temp("moved", ({ }));
                                message_vision("$N走了过来。\n", npc);
                                random_move(npc);
                                random_move(npc);
                                random_move(npc);
                                npc->set("shen", -npc->query("combat_exp") / 2000);

                                new_quest = ([]);

                                new_quest["type"]="铲除外敌";
                                new_quest["ob"]=npc;
                                new_quest["time"]=time();
                                new_quest["bang_type"]="good";
                                new_quest["num"]=get_bianhao(the_city);
                                new_quest["id"]=the_city+(string)new_quest["num"];
                                new_quest["bonus"]=npc->query("bonus");
                                new_quest["name"]="铲除来我们" + city[the_city] +
                                                  "作恶的" + npc->name();
                                new_quest["place"]=npc->query("place");
                                new_quest["difficult"]=check_difficult(npc->query("lvl"));
                                new_quest["reward"]=check_reward(npc->query("lvl"));
                                new_quest["msg"]=npc->name() + "危害江湖日久，今日来到了我们" +
                                                 city[the_city] + "地界，不知道意图何为。\n想来不是" +
                                                 "来干什么好事的，根据最新消息他在" + new_quest["place"] +
                                                 "附近出现。\n找到他，把他给铲除了！";
                                return new_quest;
                                break;
                        case 2:
                                all_city = keys(city);
                                all_city -= ({ the_city });
                                other_city = all_city[random(sizeof(all_city))];
                                all_static_npc = static_npc[other_city];
                                env_rooms = keys(all_static_npc);
                                for (;;)
                                {
                                        if (control > 50) break;	//循环超过50就中断
                                        room = env_rooms[random(sizeof(env_rooms))];
                                        env = get_object(room);
                                        if (!env)
                                                log_file("static/party_quest",sprintf("门派任务错误记录：%s\n",room));
                                        else if (! objectp(npc = present(all_static_npc[room], env)) ||
                                                        npc->query("shen") < 0)
                                        {
                                                control ++;
                                                continue;
                                        } else break;
                                }
                                if (objectp(npc))
                                {
                                        new_quest = ([]);
                                        new_quest["target"]=base_name(npc);
                                        new_quest["bang_type"]="good";
                                        new_quest["time"]=time();
                                        new_quest["num"]=get_bianhao(the_city);
                                        new_quest["id"]=the_city+(string)new_quest["num"];
                                        new_quest["type"] = "寻找物品";
                                        switch(random(3))
                                        {
                                                case 0:
                                                        obj_mapp = QUEST_GOOD_OBJ("0xun")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 50;
                                                        new_quest["difficult"] = "容易";
                                                        new_quest["reward"] = "少";
                                                        break;
                                                case 2:
                                                        obj_mapp = QUEST_GOOD_OBJ("1xun")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 90;
                                                        new_quest["difficult"] = "中等";
                                                        new_quest["reward"] = "中等";
                                                        break;
                                                case 1:
                                                        obj_mapp = QUEST_GOOD_OBJ("2xun")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 130;
                                                        new_quest["difficult"] = "困难";
                                                        new_quest["reward"] = "高";
                                                        break;
                                        }

                                        new_quest["name"]="帮" + city[other_city]+ room->short() +
                                                          "的" + npc->name() +
                                                          "找到" + new_quest["obj_name"];

                                        new_quest["msg"]=city[other_city] + room->short() +
                                                          "的" + npc->name() +
                                                          "需要" + new_quest["obj_name"] +
                                                          "，你去把它找到并送过去。";
                                        return new_quest;
                                } else return 0;
                                break;
                        case 3:
                                all_static_npc = static_npc[the_city];
                                env_rooms = keys(all_static_npc);
                                for (;;)
                                {
                                        if (control > 50) break;	//循环超过50就中断
                                        room = env_rooms[random(sizeof(env_rooms))];
                                        env = get_object(room);
                                        if (!env)
                                                log_file("static/party_quest",sprintf("门派任务错误记录：%s\n",room));
                                        else if (! objectp(npc = present(all_static_npc[room], env)) ||
                                                        npc->query("shen") < 0)
                                        {
                                                control ++;
                                                continue;
                                        } else break;
                                }
                                if (objectp(npc))
                                {
                                        new_quest = ([]);
                                        new_quest["bang_type"]="good";
                                        new_quest["time"]=time();
                                        new_quest["num"]=get_bianhao(the_city);
                                        new_quest["id"]=the_city+(string)new_quest["num"];
                                        new_quest["type"] = "调解纠纷";
                                        switch(random(3))
                                        {
                                                case 0:
                                                        obj_mapp = QUEST_GOOD_OBJ("0xun")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 60;
                                                        new_quest["difficult"] = "容易";
                                                        new_quest["reward"] = "少";
                                                        break;
                                                case 2:
                                                        obj_mapp = QUEST_GOOD_OBJ("1xun")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 100;
                                                        new_quest["difficult"] = "中等";
                                                        new_quest["reward"] = "中等";
                                                        break;
                                                case 1:
                                                        obj_mapp = QUEST_GOOD_OBJ("2xun")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 140;
                                                        new_quest["difficult"] = "困难";
                                                        new_quest["reward"] = "高";
                                                        break;
                                        }
                                        jiufen_npc = new(CLASS_D("generate") + "/jiufen_npc");
                                        NPC_D->generate_cn_name(jiufen_npc);
                                        jiufen_npc->move(env);
                                        message_vision("$N走了过来，看见$n，又喜又怒：原来你躲在这里啊！\n",jiufen_npc,npc);
                                        jiufen_npc->set_leader(npc);
                                        jiufen_npc->set_jiufen_object(npc);
                                        jiufen_npc->set_quest_ob(new_quest["obj_name"]);
                                        jiufen_npc->set("inquiry/纠纷", "TNND," + npc->name() +
                                                    "去年从我这里拿走了" + new_quest["obj_name"] +
                                                    "到现在还没有还给我！");
                                        new_quest["ob"]=jiufen_npc;
                                        new_quest["name"]="帮" + room->short() + "的" + npc->name() +
                                                          "调解纠纷";
                                        new_quest["msg"]=room->short() + "的" + npc->name() +
                                                          "和" + jiufen_npc->name() + "发生了纠纷，你去" +
                                                          "给他们调解一下吧。";
                                        return new_quest;
                                } else return 0;
                                break;
                }
        } else
        {
                switch(random(4))
                {
                        case 0:
                                all_static_npc = static_npc[the_city];
                                env_rooms = keys(all_static_npc);
                                for (;;)
                                {
                                        if (control > 50) break;	//循环超过50就中断
                                        room = env_rooms[random(sizeof(env_rooms))];
                                        env = get_object(room);
                                        if (!env)
                                                log_file("static/party_quest",sprintf("门派任务错误记录：%s\n",room));
                                        else if (! objectp(npc = present(all_static_npc[room], env)) ||
                                                        npc->query("shen") > 0)
                                        {
                                                control ++;
                                                continue;
                                        } else break;
                                }
                                if (objectp(npc))
                                {
                                        new_quest = ([]);
                                        new_quest["target"]=base_name(npc);
                                        new_quest["bang_type"]="bad";
                                        new_quest["time"]=time();
                                        new_quest["num"]=get_bianhao(the_city);
                                        new_quest["id"]=the_city+(string)new_quest["num"];
                                        new_quest["type"] = "寻找物品";
                                        switch(random(3))
                                        {
                                                case 0:
                                                        obj_mapp = QUEST_BAD_OBJ("0xun")->query_questkh();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 50;
                                                        new_quest["difficult"] = "容易";
                                                        new_quest["reward"] = "少";
                                                        break;
                                                case 2:
                                                        obj_mapp = QUEST_BAD_OBJ("1xun")->query_questkh();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 80;
                                                        new_quest["difficult"] = "中等";
                                                        new_quest["reward"] = "中等";
                                                        break;
                                                case 1:
                                                        obj_mapp = QUEST_BAD_OBJ("2xun")->query_questkh();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 110;
                                                        new_quest["difficult"] = "困难";
                                                        new_quest["reward"] = "高";
                                                        break;
                                        }
                                        new_quest["name"]="帮" + room->short() + "的" + npc->name() +
                                                          "找到" + new_quest["obj_name"];
                                        new_quest["msg"]=room->short() + "的" + npc->name() +
                                                          "需要" + new_quest["obj_name"] +
                                                          "，你去把它找到并送过去。";
                                        return new_quest;
                                } else return 0;
                                break;
                        case 1:
                                if (objectp(player))
                                        npc = create_npc(player);
                                else
                                        npc = create_npc(1);

                                env_rooms = place[city[the_city]];
                                room = env_rooms[random(sizeof(env_rooms))];
                                env = get_object(room);
                                if (!env)
                                        log_file("static/party_quest",sprintf("门派任务错误记录：%s\n",room));
                                npc->move(env);
                                npc->set("place", env->short());
                                npc->set("startroom", room);
                                npc->set_temp("moved", ({ }));
                                message_vision("$N走了过来。\n", npc);
                                random_move(npc);
                                random_move(npc);
                                random_move(npc);
                                npc->set("shen", npc->query("combat_exp") / 2000);

                                new_quest = ([]);

                                new_quest["type"]="铲除外敌";
                                new_quest["ob"]=npc;
                                new_quest["time"]=time();
                                new_quest["bang_type"]="bad";
                                new_quest["num"]=get_bianhao(the_city);
                                new_quest["id"]=the_city+(string)new_quest["num"];
                                new_quest["bonus"]=npc->query("bonus");
                                new_quest["name"]="铲除来我们" + city[the_city] +
                                                  "挑衅的" + npc->name();
                                new_quest["place"]=npc->query("place");
                                new_quest["difficult"]=check_difficult(npc->query("lvl"));
                                new_quest["reward"]=check_reward(npc->query("lvl"));
                                new_quest["msg"]=npc->name() + "素然自命正派人士，老是跟我们黑道弟兄"+
                                                 "作对，今日来到了我们" + city[the_city] +
                                                 "地界。\n看他趾高气扬的样子，来者不善！"+
                                                 "根据最新消息，他在" + new_quest["place"] +
                                                 "附近出现。\n找到他，把他给宰了！";
                                return new_quest;
                                break;
                        case 2:
                                all_city = keys(city);
                                all_city -= ({ the_city });
                                other_city = all_city[random(sizeof(all_city))];
                                all_static_npc = static_npc[other_city];
                                env_rooms = keys(all_static_npc);
                                for (;;)
                                {
                                        if (control > 50) break;	//循环超过50就中断
                                        room = env_rooms[random(sizeof(env_rooms))];
                                        env = get_object(room);
                                        if (!env)
                                                log_file("static/party_quest",sprintf("门派任务错误记录：%s\n",room));
                                        else if (! objectp(npc = present(all_static_npc[room], env)) ||
                                                        npc->query("shen") > 0)
                                        {
                                                control ++;
                                                continue;
                                        } else break;
                                }
                                if (objectp(npc))
                                {
                                        new_quest = ([]);
                                        new_quest["bonus"]=60;
                                        new_quest["difficult"]="容易";
                                        new_quest["reward"]="少";
                                        new_quest["target"]=base_name(npc);
                                        new_quest["bang_type"]="bad";
                                        new_quest["time"]=time();
                                        new_quest["num"]=get_bianhao(the_city);
                                        new_quest["id"]=the_city+(string)new_quest["num"];
                                        new_quest["type"] = "传口信";
                                        new_quest["send_msg"] = need_send_msg[random(sizeof(need_send_msg ))];
                                        new_quest["name"]="向" + city[other_city]+ room->short() +
                                                          "的" + npc->name() +
                                                          "传一个口信";

                                        new_quest["msg"]=city[other_city] + room->short() +
                                                          "的" + npc->name() +
                                                          "也是我们黑道的兄弟，现在需要你传个口信给" +
                                                          ((npc->query("gender")=="女性")?"她":"他") +
                                                          "。\n内容是：" + new_quest["send_msg"];
                                        return new_quest;
                                } else return 0;
                                break;
                        case 3:
                                all_static_npc = static_npc[the_city];
                                env_rooms = keys(all_static_npc);
                                for (;;)
                                {
                                        if (control > 50) break;	//循环超过50就中断
                                        room = env_rooms[random(sizeof(env_rooms))];
                                        env = get_object(room);
                                        if (!env)
                                                log_file("static/party_quest",sprintf("门派任务错误记录：%s\n",room));
                                        else if (! objectp(npc = present(all_static_npc[room], env)) ||
                                                        npc->query("shen") > 0)
                                        {
                                                control ++;
                                                continue;
                                        } else break;
                                }
                                if (objectp(npc))
                                {
                                        new_quest = ([]);
                                        new_quest["bang_type"]="bad";
                                        new_quest["time"]=time();
                                        new_quest["num"]=get_bianhao(the_city);
                                        new_quest["id"]=the_city+(string)new_quest["num"];
                                        new_quest["type"] = "调解纠纷";
                                        switch(random(3))
                                        {
                                                case 0:
                                                        obj_mapp = QUEST_GOOD_OBJ("0xun")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 60;
                                                        new_quest["difficult"] = "容易";
                                                        new_quest["reward"] = "少";
                                                        break;
                                                case 2:
                                                        obj_mapp = QUEST_GOOD_OBJ("1xun")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 90;
                                                        new_quest["difficult"] = "中等";
                                                        new_quest["reward"] = "中等";
                                                        break;
                                                case 1:
                                                        obj_mapp = QUEST_GOOD_OBJ("2xun")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 130;
                                                        new_quest["difficult"] = "困难";
                                                        new_quest["reward"] = "高";
                                                        break;
                                        }
                                        jiufen_npc = new(CLASS_D("generate") + "/jiufen_npc");
                                        NPC_D->generate_cn_name(jiufen_npc);
                                        jiufen_npc->move(env);
                                        message_vision("$N走了过来，看见$n，又喜又怒：原来你躲在这里啊！\n",jiufen_npc,npc);
                                        jiufen_npc->set_leader(npc);
                                        jiufen_npc->set_jiufen_object(npc);
                                        jiufen_npc->set_quest_ob(new_quest["obj_name"]);
                                        jiufen_npc->set("inquiry/纠纷", "气死我了," + npc->name() +
                                                    "去年从我这里拿走了" + new_quest["obj_name"] +
                                                    "到现在还没有还给我！");
                                        new_quest["ob"]=jiufen_npc;
                                        new_quest["name"]="帮" + room->short() + "的" + npc->name() +
                                                          "调解纠纷";
                                        new_quest["msg"]=room->short() + "的" + npc->name() +
                                                          "和" + jiufen_npc->name() + "发生了纠纷，你去" +
                                                          "给他们调解一下吧。";
                                        return new_quest;
                                } else return 0;
                                break;
                }
        }
        return 0;
}

//本函数用于查找地点列表的错误
void check_all_place()
{
        int i,j;
        string *all_city,*the_place;
        object env;

        all_city = keys(city);
        for (i = 0;i < sizeof(all_city);i++)
        {
                the_place = place[city[all_city[i]]];
                for (j = 0;j<sizeof(the_place);j++)
                        if (!objectp(env = get_object(the_place[j])))
                                log_file("static/party_quest",sprintf("门派任务错误记录：%s\n",the_place[j]));
        }
}

varargs void delete_city_quest(string arg,string type,string bh)
{
        int i;
        mapping *bang_quest;
        if (!arg)
        {
                bang_city_quest = ([]);
                return;
        }
        bang_quest = bang_city_quest[arg];

        if (!sizeof(bang_quest)) return;

        if (bh)
        {
                if (bh == "xc")
                {
                        for (i = 0;i < sizeof(bang_quest);i++)
                                if (bang_quest[i]["id"] == "xc")
                                        bang_quest[i]["enable"] = 0;
                } else
                {
                        for (i = 0;i < sizeof(bang_quest);i++)
                                if (bang_quest[i]["id"] == bh)
                                        bang_quest[i] = 0;
                }
        } else if (type)
        {
                for (i = 0;i < sizeof(bang_quest);i++)
                        if (bang_quest[i]["bang_type"] == type)
                                if (bang_quest[i]["id"] == "xc")
                                        bang_quest[i]["enable"] = 0;
                                else
                                        bang_quest[i] = 0;
        } else bang_quest = ({});
        bang_quest -= ({ 0 });
        bang_city_quest[arg] = bang_quest;
        return;
}
