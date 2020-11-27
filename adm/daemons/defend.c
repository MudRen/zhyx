// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// defendd.c

#include <ansi.h>
inherit F_DBASE;

#define CHECK_PERIOD    100 // 300s ���һ�� 
#define last_check      my["last_check"] 
#define now_fighting    my["now_fighting"] 
#define MIN_EXP         100000


int  filter_user(object me);
void send_enemy(int num, string family);
void move_enemy(object enemy, string family);
void remove_enemy();

mapping familys = ([
// ���� : ([ λ�� : string*, ���±��� : int, ʦ������ : string ]),
"�䵱��" : ([
        "place" : ({ "/d/wudang/shijie1", "/d/wudang/shibapan","/d/wudang/haohanpo", 
                     "/d/wudang/guangchang", "/d/wudang/tynroad", "/d/wudang/mozhenjing",
                     "/d/wudang/fuzhenguan", "/d/wudang/shiliang", "/d/wudang/yuzhengong",
                     "/d/wudang/zixiaogate", "/d/wudang/shijie2", "/d/wudang/wulaofeng",
                     "/d/wudang/shanlu2", "/d/wudang/shibapan", "/d/wudang/tygate1", 
                     "/d/wudang/shanlu4", "/d/wudang/shanlu3", "/d/wudang/tysroad", 
                     "/d/wudang/shanlu1", "/d/wudang/taiziyan", }),
        "generation" : 3,
	"master" : "/kungfu/class/wudang/zhang", 
	]),

"������" : ([
	"place" : ({ "/d/shaolin/xiaojing1", "/d/shaolin/xiaojing2", "/d/shaolin/shijie1",
	      	     "/d/shaolin/shijie2", "/d/shaolin/shijie3", "/d/shaolin/shijie4",
	       	     "/d/shaolin/guangchang1", "/d/shaolin/shijie5", "/d/shaolin/shijie6", 
                     "/d/shaolin/gulou", "/d/shaolin/smdian", 
                     "/d/shaolin/hsyuan2", "/d/shaolin/hsyuan3", "/d/shaolin/hsyuan1", }),
	"generation" : 37,
	"master" : "/kungfu/class/shaolin/xuan-tong", 
	]),

"ؤ��" : ([
        "place" : ({ "/d/city/ml1", "/d/city/ml2",
                     "/d/city/ml3", "/d/city/pomiao", 
                     "/d/gaibang/shoushe", "/d/gaibang/inhole",
                     "/d/city/ml4", "/d/gaibang/slandao1",
                     "/d/gaibang/slandao2", }),
	"generation" : 37,
	"master" : "/kungfu/class/gaibang/hong", 
	]),
	
"������" : ([
        "place" : ({ "/d/emei/qianfoan", "/d/emei/qingyinge", 
                     "/d/emei/yunufeng", "/d/emei/woyunan", 
                     "/d/emei/shierpan3", "/d/emei/qsjie1", 
                     "/d/emei/xiaolu1",
                     "/d/emei/wanxingan", }),
	"generation" : 37,
	"master" : "/kungfu/class/emei/miejue", 
	]),

"������" : ([
        "place" : ({ "/d/xingxiu/xxroad1", "/d/xingxiu/riyuedong", 
                     "/d/xingxiu/xxh6", "/d/xingxiu/xxh5", "/d/xingxiu/xxh4", 
		     "/d/xingxiu/xxh1", "/d/xingxiu/xxh2", "/d/xingxiu/xxh3", 
		     "/d/xingxiu/xxh4", "/d/xingxiu/shanjiao", }),
	"generation" : 3,
        "master" : "/kungfu/class/xingxiu/ding", 
	]),
	
"��ɽ��" : ([
	"place" : ({ "/d/huashan/yunu", "/d/huashan/square", 
                     "/d/huashan/zhenyue", "/d/huashan/pingxinshi",
                     "/d/huashan/yuquan", "/d/huashan/chaoyang", 
		     "/d/huashan/husun", "/d/huashan/shaluo", 
                     "/d/huashan/pingdi", "/d/huashan/canglong", }),
	"generation" : 14,
	"master" : "/kungfu/class/huashan/yue-buqun", 
	]),

"���ϻ���" : ([
        "place" : ({ "/d/dali/shilin1", "/d/dali/shilin2", "/d/dali/gudao",
                     "/d/dali/road3", "/d/dali/road4", "/d/dali/road5",
                     "/d/dali/dalinorth", "/d/dali/ershuiqiao", "/d/dali/gaolishan2", 
                     "/d/dali/shanlu1", "/d/dali/shanlu2",
                     "/d/dali/zoulang3", "/d/dali/zoulang4", "/d/dali/zoulang1",
                     "/d/dali/shilin1", "/d/dali/shilin2", "/d/dali/zoulang2", }),
	"generation" : 13,
	"master" : "/kungfu/class/duan/duanzm", 
	]),
	
"����" : ([
        "place" : ({ "/d/mingjiao/baota0", "/d/mingjiao/ljroad1", "/d/mingjiao/ljroad2", 
                     "/d/mingjiao/ljroad3", "/d/mingjiao/htping", "/d/mingjiao/shanlu1", 
                     "/d/mingjiao/shanlu2", "/d/mingjiao/shamo1", "/d/mingjiao/shanting", 
                     "/d/mingjiao/sshanlu4", "/d/mingjiao/tingtang", "/d/mingjiao/sshanlu2", 
                     "/d/mingjiao/tandi", "/d/mingjiao/wu1", "/d/mingjiao/xuanya3", 
                     "/d/mingjiao/xuanya1", "/d/mingjiao/xuanya2", "/d/mingjiao/xikou", }),
	"generation" : 35,
	"master" : "/kungfu/class/mingjiao/zhangwuji", 
	]),

"ѩɽ��" : ([
        "place" : ({ "/d/xueshan/shanjiao", "/d/xueshan/cangjing", "/d/xueshan/cangjingge"
                     "/d/xueshan/caoyuan", "/d/xueshan/cedian1", "/d/xueshan/cedian2", 
                     "/d/xueshan/chang", "/d/xueshan/chanshi", "/d/xueshan/dadian",  
                     "/d/xueshan/guangcha", "/d/xueshan/houmen", "/d/xueshan/dilao", 
                     "/d/xueshan/hubian1", "/d/xueshan/hubian2", "/d/xueshan/hubian3", 
                     "/d/xueshan/kufang", "/d/xueshan/midao", "/d/xueshan/mishi", }),
        "generation" : 3,
	"master" : "/kungfu/class/xueshan/jiumozhi", 
	]),

"ȫ���" : ([
        "place" : ({ "/d/quanzhen/cetang", "/d/quanzhen/huizhentang", "/d/quanzhen/shijianyan",
                     "/d/quanzhen/damen", "/d/quanzhen/guozhendian", "/d/quanzhen/xianzhentang",
                     "/d/quanzhen/datang1", "/d/quanzhen/datang2", "/d/quanzhen/datang3",
                     "/d/quanzhen/houtang1", "/d/quanzhen/houtang2", "/d/quanzhen/houtang3", 
                     "/d/quanzhen/houshan", "/d/quanzhen/xiaolu1", "/d/quanzhen/xiaolu2",}),
        "generation" : 6, 
        "master" : "/kungfu/class/quanzhen/wang",
        ]),

"��Ĺ��" : ([ 
        "place" : ({ "/d/gumu/liangong3", "/d/gumu/liangong2", "/d/gumu/liangong",
                     "/d/gumu/zhengting", "/d/gumu/houting", "/d/gumu/xiaoting",
                     "/d/gumu/qianting", "/d/gumu/xiaoting", "/d/gumu/mumen", 
                     "/d/gumu/mumen", "/d/gumu/caodi", "/d/gumu/caodi2", }),
        "generation" : 5, 
        "master" : "/kungfu/class/gumu/longnv",
        ]),

"���չ�" : ([
        "place" : ({ "/d/lingjiu/xianchou", "/d/lingjiu/dadao1", "/d/lingjiu/dadao2",
                     "/d/lingjiu/changl15", "/d/lingjiu/changl6", "/d/lingjiu/dating",
                     "/d/lingjiu/changl7", "/d/lingjiu/changl8", "/d/lingjiu/changl4",
                     "/d/lingjiu/changl3", "/d/lingjiu/daban", "/d/lingjiu/men2",
                     "/d/lingjiu/changl9", "/d/lingjiu/men1", "/d/lingjiu/changl1",
                     "/d/lingjiu/huayuan", "/d/lingjiu/xiaodao1", "/d/lingjiu/xiaodao2",}),
        "generation" : 5, 
        "master" : "/kungfu/class/lingjiu/xuzhu",
        ]), 

"ŷ������" : ([
        "place" : ({ "/d/baituo/houyuan", "/d/baituo/tuyuan", "/d/baituo/zhuyuan",
                     "/d/baituo/shoushe", "/d/baituo/menlang", "/d/baituo/huayuan",
                     "/d/baituo/damen", "/d/baituo/yuanzi", "/d/baituo/dating", 
                     "/d/baituo/liangong", "/d/baituo/ximen", "/d/baituo/guangchang",}), 
        "generation" : 3, 
        "master" : "/kungfu/class/ouyang/ouyangfeng", 
        ]), 

"�һ���" : ([
        "place" : ({ "/d/taohua/wofang", "/d/taohua/hyjuchu", "/d/taohua/changlang2", 
                     "/d/taohua/changlang", "/d/taohua/shuilong", "/d/taohua/jingshe",
                     "/d/taohua/haitan", "/d/taohua/tuqiu", "/d/taohua/zhulin",
                     "/d/taohua/road1", "/d/taohua/xiangzhong", "/d/taohua/taolin",
                     "/d/taohua/road2", "/d/taohua/road3", "/d/taohua/road4",}),
        "generation" : 10,
        "master" : "/kungfu/class/taohua/huang", 
        ]),

"Ѫ����" : ([
        "place" : ({ "/d/xuedao/sroad7", "/d/xuedao/sroad8", "/d/xuedao/shandong1", 
                     "/d/xuedao/wangyougu", "/d/xuedao/sroad9", "/d/xuedao/shandong2",
                     "/d/xuedao/shandong3", "/d/xuedao/syabi", "/d/xuedao/eyabi",}),
        "generation" : 3,
        "master" : "/kungfu/class/xuedao/laozu", 
        ]),

"�������" : ([
        "place" : ({ "/d/guanwai/caoguduo", "/d/guanwai/baihe", "/d/guanwai/xiaoyuan", 
                     "/d/guanwai/milin1", "/d/guanwai/xiaowu", "d/guanwai/houyuan",
                     "/d/guanwai/liangonge", "/d/guanwai/liangong", "/d/guanwai/jingxiu",}),
        "generation" : 4,
        "master" : "/kungfu/class/guanwai/hufei", 
        ]),

"������" : ([
        "place" : ({ "/d/shenlong/zoulang", "/d/shenlong/zhulin", "/d/shenlong/jushi", 
                     "/d/shenlong/road2", "/d/shenlong/road", "/d/shenlong/kongdi",
                     "/d/shenlong/xiaowu", "/d/shenlong/caodi", "/d/shenlong/haitan",}),
        "generation" : 3,
        "master" : "/kungfu/class/shenlong/hong", 
        ]),

"Ľ������" : ([
        "place" : ({ "/d/yanziwu/shuwu", "/d/yanziwu/lanyue", "/d/yanziwu/shuwu", 
                     "/d/yanziwu/zuijing", "/d/yanziwu/canheju", "/d/yanziwu/qiushuan",
                     "/d/yanziwu/huayuan", "/d/yanziwu/jiashan", "/d/yanziwu/jiashan",
                     "/d/yanziwu/longfeng", "/d/yanziwu/yimen", "/d/yanziwu/dannuo",
                     "/d/yanziwu/cuixia", "/d/yanziwu/chuantang", "/d/yanziwu/lixiang",}),
        "generation" : 8,
        "master" : "/kungfu/class/yanziwu/murongbo", 
        ]),

"��ң��" : ([
        "place" : ({ "/d/xiaoyao/mubanlu", "/d/xiaoyao/liangong", "/d/xiaoyao/xiaodao4", 
                     "/d/xiaoyao/muwu1", "/d/xiaoyao/xiaodao5", "/d/xiaoyao/qingcaop",
                     "/d/xiaoyao/muwu2", "/d/xiaoyao/xiaodao3", "/d/xiaoyao/xiaodao1",
                     "/d/xiaoyao/xiaodao2", "/d/xiaoyao/wuchang2", "/d/xiaoyao/bingqif",}),
        "generation" : 10,
        "master" : "/kungfu/class/xiaoyao/suxingh", 
        ]),

"��ɽ����" : ([ 
        "place" : ({ "/d/huashan/jzroad1", "d/village/hsroad2", "/d/huashan/jzroad1", 
                     "/d/huashan/jzroad2", "/d/huashan/jzroad3", "/d/huashan/jzroad4",  
                     "/d/huashan/jzroad5", "/d/huashan/jzroad6", "/d/huashan/shangu",}),  
        "generation" : 3, 
        "master" : "/kungfu/class/huashan/feng-buping", 
   ]),
]);

// �����б�
string *zps = ({
        "�䵱��", "��ɽ����", "ȫ���", "��Ĺ��", "���չ�", "�һ���", "�������", "���ϻ���", 
        "������", "ؤ��", "������", "��ң��", "����","��ɽ����",
});

// а���б�
string *xps = ({
        "������", "Ѫ����", "ѩɽ��", "ŷ������", "������", "Ľ������",
});

void create() 
{
        mapping my; 

        seteuid(getuid()); 
        set("channel_id", "����������"); 

        CHANNEL_D->do_channel(this_object(), "sys", "�����������Ѿ�������"); 

        set_heart_beat(100); 
        my = query_entire_dbase(); 

        now_fighting = ([]);
        last_check = time(); 
}

void heart_beat() 
{
        mapping my; 
        int i, num; 
        object *users;
        string *family, family_name;

        my = query_entire_dbase(); 

        if ((time() - last_check) < CHECK_PERIOD) 
                return;

        // remove_enemy();
        
        family = keys(familys);

        for (i = 0; i < sizeof(family); i++)
        {
                family_name = family[i];

                users = filter_array(users(), (: interactive($1) && 
                                                 $1->query("family/family_name") == $(family_name) 
                                                 && mapp($1->query_temp("swjob/allow")) :));
                num = sizeof(users) * (1 + random(2));
                if (! num) continue;

                // CHANNEL_D->do_channel(this_object(), "sys", "���������� "+ num +"��"); 
                send_enemy(num, family_name);
        }

        last_check  = time(); 
}

void send_enemy(int num, string family)
{
        object enemy, master;
        string enemy_fam;
        int i;
        mapping my = query_entire_dbase(); 

        // ����Ҫ����������ɻ���������а������а���ϳ�
        if (member_array(family, xps) != -1 
        ||  member_array(family, zps) == -1 && member_array(family, xps) == -1)
                enemy_fam = zps[random(sizeof(zps))];
        // ������������ϳ�
        else 
                enemy_fam = xps[random(sizeof(xps))];

        for (i = 0; i < num; i++)
        {
                enemy = new("/clone/npc/enemy");
                // enemy->create_family(enemy_fam, familys[enemy_fam]["generation"] + (-1 + random(2)), "����");
                enemy->set("is_attacking", family);
                enemy->set_temp("quest_ob", 1);
                enemy->set("long", "������ǰ������" + query("is_attacking") ? query("is_attacking") : "�������" +
                                   "��һ��" + query("family/family_name") ? query("family/family_name") : "δ֪����" + "���ӡ�\n");                
                move_enemy(enemy, family);
        }

        // now_fighting ��ʽ���������� : ������
        now_fighting[family] = enemy_fam;
        /*
        if (! find_object(familys[family]["master"])) 
                master = load_object(familys[family]["master"]);
        else 
                master = find_object(familys[family]["master"]);

        CHANNEL_D->do_channel(master, "chat", sprintf("��˵%s��һ����Ӵ��ɱ�����ɣ��������Ʋ��", enemy_fam)); 
        */
        return;
}

void move_enemy(object enemy, string family)
{
        string *places = familys[family]["place"];
        string place = places[random(sizeof(places))];
        object room;

        if (objectp(room = environment(enemy)))
        {
                tell_room(room, enemy->name() + "һ����Ͳ����ˡ�\n");
        }
        // CHANNEL_D->do_channel(this_object(), "sys", sprintf("%s : %O", enemy->short(), place)); 
        enemy->move(place);
        
        tell_room(place, "ֻ��һ��" + enemy->query("family/family_name") + "���Ӳ�֪ʲôʱ�����˳�����\n");

        return;
}

int ask_quest(object ob, object me)
{
        string *places, place;

        string *msg_now = 
        ({
                "������ų�����������", "��������ƺ���̫ƽ��", 
                "�������ʱ�е��˽���", "��������ƺ��ܲ�����", 
                "��˵�Ϳ�Ҫ�е��˽���", "�����˶Ա��Ż�������",
        });
        string *msg_do =
        ({
                "�Ͽ쵽�Ĵ�Ѳ��Ѳ��", "ע�����ܶ�Ҫȥ���", 
                "ɽ��ɽ�¶���ϸ����", "�ڱ���Ҫ���ú�����",
                "����Ҫ�ط����÷���", "�÷�ֹ���˹���ɽ��",
        });
        string *msg_place =
        ({
                "��Ȼ˵����ɽ��ˮ�㣬����", "Ҳ��һ����Ҫλ�ã�����",
                "�ô�Ҳ�Ǹ���Ҫ�ؿ������", "�Ͼ��������Ҫ�أ���ô",
                "�����е������˹�������", "���µ��˹���������", 
        });

        if (! me->query("family/family_name"))
        {
                ob->command("haha" + me->query("id"));
                message_sort(HIC "$N" HIC "��$n" HIC "������" + RANK_D->query_respect(me) +
                             "�������ɣ�����Ҫʲô�����أ���\n\n" NOR,ob,me);
                tell_object(me, HIW "�㻹���Ȱݸ�ʦ����Ҫ����ɡ�\n" NOR);
                return 1;
        }

        if (ob->query("family/family_name") != me->query("family/family_name"))
        {
                ob->command("?" + me->query("id"));
                message_sort(HIC "$N" HIC "����üͷ��$n" HIC "��������λ" +
                             me->query("family/family_name") +"��"+ RANK_D->query_respect(me) +
                             "���������Ҵ����˰ɣ���\n\n" NOR, ob, me);
                tell_object(me, HIW "�ⲻ�����Լ������ɣ��㲻Ӧ������λʦ��Ҫ����ѽ��\n" NOR);
                return 1;
        }

        if (me->query("combat_exp") < MIN_EXP)
        {
                ob->command("sigh");
                message_sort(HIC "$N" HIC "��$n" HIC "�����������㻹�ǵ�ˮƽ��Щ������������񲻳١���\n\n" NOR, ob, me);
                tell_object(me, HIW "���������� " +MIN_EXP+" �㾭��ֵ��������\n" NOR);
                return 1;
        }

        if (me->query_temp("swjob/allow") && ! wizardp(me))
        {
                ob->command("yi");
                message_sort(HIC "$N" HIC "�ɻ�ض�$n" HIC "�������㲻���Ѿ��������������ô����ô�������ң���\n\n" NOR, ob, me);
                tell_object(me, HIW "��ȥ����׼�����ػ�������ɰɡ�\n" NOR);
                return 1;
        } else 
        {
                places = familys[me->query("family/family_name")]["place"];
                place = places[random(sizeof(places))];
                place = place->query("short");
                send_enemy(4, me->query("family/family_name"));

                command("nod" + me->query("id"));
                message_sort(HIC "$N" HIC "����ض�$n" HIC "�������ðɣ�" + msg_now[random(sizeof(msg_now))] +
                             "����Ҫע��" + msg_do[random(sizeof(msg_do))] + "����\n\n" NOR, ob, me);
                               
                tell_object(me, HIW + ob->name() + HIW "���ĸ����㣺��" + place + HIW"����ط�" +
                                msg_place[random(sizeof(msg_place))]+ "����ö�ע��ע�⡣��\n" NOR);

                me->set_temp("swjob/allow", 1);
                me->apply_condition("swjob", 10 + random(5));
                return 1;
        }
}

// ��ʱ���ˣ����ߵ���
void remove_enemy()
{
        object *enemys;
        int i;
        mapping my = query_entire_dbase();

        if (arrayp(enemys = children("/clone/npc/enemy")))
        {
                for (i = 0; i < sizeof(enemys); i++)
                {
                        if (enemys[i]->is_fighting())
                        {
                                enemys[i]->remove_all_killer();
                                tell_room(environment(enemys[i]), HIW "ֻ��" + enemys[i]->name() +
                                          "ͻȻ��ɫһ�䣬Ѹ�ٹ������У�����սȦת�����ˡ�\n");
                        }
                        else {
                                tell_room(environment(enemys[i]), HIW "ֻ��" + enemys[i]->name() +
                                          "��ָһ�㣬ͻȻ��ɫ��䣬����ææ�������ˡ�\n");
                        }
                        destruct(enemys[i]);
                }
        }
        now_fighting = ([]);
        return; 
}

// ����͵�Ҫ����

int ask_reward(object ob, object me)
{
        int killed, exp, pot, con;

        if (! me->query("family/family_name"))
        {
                ob->command("haha" + me->query("id"));
                message_vision(HIC "$N" HIC "��$n" HIC "������" + RANK_D->query_respect(me) 
                                +"�������ɣ�����Ҫʲô�����أ���\n\n" NOR,ob,me);
                tell_object(me, HIW "�㻹���Ȱݸ�ʦ����Ҫ����ɡ�\n" NOR);
                return 1;
        }

        if (ob->query("family/family_name") != me->query("family/family_name"))
        {
                ob->command("?" + me->query("id"));
                message_vision(HIC "$N" HIC "����üͷ��$n" HIC "��������λ" +
                               me->query("family/family_name") + "��" + RANK_D->query_respect(me) +
                               "���������Ҵ����˰ɣ���\n" NOR,ob,me);
                tell_object(me, HIW "�ⲻ�����Լ������ɣ��㲻Ӧ������λʦ��Ҫ����ѽ��\n" NOR);
                return 1;
        }

        if (! me->query_temp("swjob/allow"))
        {
                ob->command("sigh");
                message_vision(HIC "$N" HIC "�ɻ�ض�$n" HIC "�������㶼��������������񣬾���Ҫ��������\n" NOR, ob, me);
                tell_object(me, HIW "���ܵ���Ҫ������ɡ�\n" NOR);
                return 1;
        }

        if (! me->query_temp("swjob/finish"))
        {
                ob->command("sigh");
                message_vision(HIC "$N" HIC "�ɻ�ض�$n" HIC "�������㻹û�������أ�����Ҫ��������\n" NOR, ob, me);
                tell_object(me, HIW "�����������Ҫ�����ɡ�\n" NOR);
                return 1;
        } else 
        {
                if (! me->query_temp("swjob/killed"))
                {
                        ob->command("hmm");
                        message_vision(HIC "$N" HIC "���ͷ��$n" HIC "�������ðɣ����������湦δ�����Ͳ����㽱���ˡ���\n" NOR, ob, me);
                        me->delete_temp("swjob");
                        return 1;
                } else 
                {
                        killed = (int)me->query_temp("swjob/killed");
                        ob->command("nod");

                        exp = killed * 100 + random(200);
                        exp = exp / 2 + random(exp / 2);
                        pot = exp / 3 + random(20);
                        con = pot;

                        message_vision(HIC "$N" HIC "���ͷ��$n" HIC "�������ã����������ɹ���ɱ��" +
                                       chinese_number(killed) + "�����ˣ������Ǹ����һ�㽱������\n" NOR, ob, me);
                        tell_object(me, HIW "���������õ���" + chinese_number(exp) + "�㾭��ֵ��" +
                                        chinese_number(pot) + "��Ǳ��ֵ�Ľ�����������ɹ�������ˡ�\n" NOR);
                        me->delete_temp("swjob/allow");
                        me->delete_temp("swjob/killed");
                        me->delete_temp("swjob/finish");
                        me->add("combat_exp", exp);
                        me->add("potential", pot);
                        me->add("contribution", con);
                return 1; 
            }
    }
}
