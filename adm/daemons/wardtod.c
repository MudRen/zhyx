// ward.c ����ս�������Ƴ���
// Created by yuchang

#include <ansi.h>
inherit F_DBASE;

static object *total = ({ });
static object king = 0;
static int start_time = 0;

object *query_total()  { return total; }
object query_king() { return king; }

int ask_war(object me);
int start_war(object me);
int join_war(object ob);
int fail_war();
int check_out(object me);
int check_quit(object me);

void init_king(object me);
void init_player(object me);
void message_competition(string msg);
void auto_check();
void remove_enemy();
void give_bouns();
void restore_status(object me);

string *place = ({
        "/d/xiangyang/eastgate2",
        "/d/xiangyang/eastgate1",
        "/d/xiangyang/eastjie3",
        "/d/xiangyang/eastjie2",
        "/d/xiangyang/eastjie1",
        "/d/xiangyang/guangchang",
        "/d/xiangyang/westjie1", 
        "/d/xiangyang/westjie2",
        "/d/xiangyang/westjie3",
        "/d/xiangyang/westgate1",
        "/d/xiangyang/westgate2",
        "/d/bianliang/yidao1",
        "/d/bianliang/yidao2",
        "/d/bianliang/yidao3",
        "/d/bianliang/chengmen",
});

void create() 
{
        seteuid(ROOT_UID);
        set("channel_id", "����ս��"); 
        CHANNEL_D->do_channel(this_object(), "sys", "����ս���Ѿ�������"); 
}

int clean_up()
{
        return 1;
}

int ask_war(object me)
{
        if (me->query_condition("junquest_fail"))
                return notify_fail("�������Ǵ���֮�����Գ������������ѱ�����������ذɣ�\n");

        if (me->query_condition("junquest_song"))
                return notify_fail("�����Ѿ������������ˣ���������ĥ��ʲô������\n");
                                
        if (me->query("degree_jungong") < 8)
                return notify_fail("���˹ٵ�λ�����������һ��֮˧���ѷ������ģ���\n"); 

        if (objectp(king))
                return notify_fail("�����Ѿ���" + king->name(1) + "�ʾ������ˣ����˿���ǰȥ����\n");
                
        king = me;
        init_king(me);
        return 1;
}

void init_king(object me)
{ 
        int liangcao;
        string temp;
        object bingfu, kaijia;

        me->set("party/party_name", HIW "����" NOR);
        me->set("party/rank", HIW "����Ԫ˧" NOR);  
        me->set_temp("jun_quest/party", "song");        
        me->set("eff_qi", me->query("max_qi") + 1000 * me->query("degree_jungong"));
        me->set("qi", me->query("eff_qi"));
        me->set_temp("jun_quest/train", "infantry");
        me->apply_condition("junquest_song", 360);         
        // me->set_override("quit", (: call_other, __FILE__, "fail_war" :));
        
        liangcao = 1000;
        temp = sprintf("%d", liangcao);
        write_file("/quest/quest_jun/song/liangcao", temp, 1);
        
        if (! objectp(kaijia = present("kai jia", me)))
        {
                kaijia = new("/quest/quest_jun/song/obj/tiejia");
                kaijia->move(me);
        }
        if (! objectp(bingfu = present("bing fu", me)))
        {
                bingfu = new("/adm/npc/obj/bingfu");
                bingfu->set("owner", me->query("id"));
                bingfu->set("master", me->query("name"));
                bingfu->move(me);
                bingfu->check_me(me);
        }
        
        tell_object(me, HIC "\n���ˣ����п���֮���Ѿ���ʣ�޼���������Ӫ�������п�һս���˴�\n" +
                        "���������ص�Զ�������¹��Ҵ��ι��ˣ��������˾�����Ϊ��������\n" +
                        "���յ�ʤ�������س����������Ϊ��������ǧ�����������˽�����\n\n" NOR);      
        start_war(me);
}

// start war
int start_war(object me)
{
        object jiang, jiangjun, kehan, smen, mmen;
        int i;

        message("channel:rumor", MAG "������ʷ�ǡ�" +
                CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60)) +
                "�ɹſɺ�������֣������ɳ�\n " +
                "           " + "�����Ԫ˧" + me->query("name") + MAG + "(" + me->query("id") + MAG + ")" +
                MAG + "����ʦ���Ͽ���......\n" NOR,
                users());

        smen = get_object("/quest/quest_jun/syuanmen1");
        if (objectp(smen))
                smen->set("defence", 120);
                
        mmen = get_object("/quest/quest_jun/myuanmen1");
        if (objectp(mmen))
                mmen->set("defence", 120);

        // �����ɹž��� 
        kehan = new("/quest/quest_jun/meng/kehan");
        kehan->move("/quest/quest_jun/mying1");
        kehan->change_ob();
        jiang = new("/quest/quest_jun/meng/mengj");
        jiang->move("/quest/quest_jun/mying1");
        jiang->change_ob();

        for (i = 0; i < 4; i++)
        {              
                jiang = new("/quest/quest_jun/meng/mengj");
                jiang->move("/quest/quest_jun/mying");
                jiang->change_ob();
                jiang = new("/quest/quest_jun/meng/mengj");
                jiang->move("/quest/quest_jun/dhunya");
                jiang->change_ob();
        }
        

        if (me->query("degree_jungong") > 12)
        for (i = 0; i < 2; i++)
        {
                jiangjun = new("/quest/quest_jun/meng/mengj");
                jiangjun->move("/quest/quest_jun/myuanmen1");
                jiangjun->change_ob();
        }

        if (me->query("degree_jungong") > 10)
        for (i = 0; i < 2; i++)
        {
                jiang=new("/quest/quest_jun/meng/mengj");
                jiang->move("/quest/quest_jun/caoyuan");
                jiang->change_ob();
        }
        // �����ξ�
        for(i = 0; i < 4; i++)
        {
                jiang = new("/quest/quest_jun/song/songb");
                jiang->move("/quest/quest_jun/sying1");
                jiang->change_ob();
        } 
        start_time = time();
        set_heart_beat(1);
        return 1;
} 

// join in war
int join_war(object ob)
{
        if (ob->query("age") < 18)
                return notify_fail(RANK_D->query_respect(ob) + "���㻹С���Ժ�����Ϊ��Ч���ɣ�\n");

        if (ob->query("combat_exp") < 1000000)
                return notify_fail(RANK_D->query_respect(ob) + "��־�ɼΣ��������޸���֮����������ذɣ�\n");

        if (ob->query("degree_jungong") < 4)
                return notify_fail("���ľ���̫��΢�ˣ���ǰ������ûʲô�ð���\n");
            
        if (! objectp(king))
                return notify_fail("����ǰ��û��ս�£������Ժ������ɣ�\n");
                                 
        if (! arrayp(total))
                total = ({ ob });
        else
        if (member_array(ob, total) == -1)
                total += ({ ob });

        message("channel:rumor", MAG "������ս������־֮ʿ" +
                                 ob->name(1) + MAG "����ǰ�߼�����֧Ԯ�ξ������ɹž���֮�У�\n" NOR,
                                 users());
        init_player(ob);
        set_heart_beat(1);
        return 1;
}


// set player's override functions
void init_player(object me)
{
        me->set_temp("jun_quest/party", "song");
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));

        me->move("/quest/quest_jun/sying1");
        tell_object(me, HIY "�㶨��һ������ŷ����Լ��Ѿ�����" +
                            environment(me)->short() + HIY "��\n");
}

void heart_beat()
{
        if (sizeof(total) || (start_time && (time() - start_time) > 300))
                auto_check();
}
        
// check all the players who join the war
void auto_check()
{
        object ob;
        string room, site;
        object *lost;
        int i;

        lost = ({ });
        
        if (! objectp(king))
        {
                set_heart_beat(0);
                fail_war();
                return;
        }
        
        room = base_name(environment(king));
        site = file_name(environment(king));
        if (! sscanf(room, "/quest/quest_jun/%*s") &&
            member_array(site, place) == -1 && time() - start_time > 300)
        {
                message_competition("��˵" + king->name(1) +
                                    "��ս�����������ӣ������ξ������죬" +
                                    "���Ļ�ɢ�����ɹž���ȫ�߻��ܣ�\n");
                set_heart_beat(0);
                fail_war();
                return;
        }
        
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                        // ����Ƿ�����ս��
                        room = base_name(environment(total[i]));
                        site = file_name(environment(total[i]));
                        if (! sscanf(room, "/quest/quest_jun/%*s") &&
                            member_array(site, place) == -1)
                        {
                                message_competition("��˵" + total[i]->name(1) +
                                                    "�ľ�����ս�����������ӣ��ξ�" +
                                                    "���Ŀ�ʼ��ɢ��ս�����½���\n");
                                // not in war room
                                restore_status(total[i]);
                                total[i] = 0;
                                continue;
                        }
                        // �������ľ��ӣ�ѹ��û�д����ĳ��⣩
                        if (! total[i]->query_temp("jun_quest/escort") &&
                            total[i]->query_temp("jun_quest/train") && 
                            total[i]->query("combat_exp") < 20000000 && 
                            site != "/quest/quest_jun/sying2" &&
                            site != "/quest/quest_jun/sying3" &&
                            site != "/quest/quest_jun/sying1" &&
                            site != "/quest/quest_jun/sying" && 
                            site != "/quest/quest_jun/syuanmen1" && 
                            site != "/quest/quest_jun/sying4")
                        {
                            if (total[i]->query("qi") < total[i]->query("max_qi"))
                                // total[i]->query_temp("jun_quest/group") < 1)
                                	lost += ({ total[i] });
                        }
                }
        }
        
        total -= ({ 0 });

        // kickout the players who lost 
        foreach (ob in lost)
                check_out(ob);

        lost = ({ });
        return;
}

int check_out(object me)
{
        object ob;
        mapping my;
        string msg;
        string room;

        tell_object(me, HIR "\n����Ż��ң��ӻ�Ԫ˧��Ӫ���ּ��пʣ��ѵ������״̬��\n" NOR);
        if (ob = me->query_last_damage_from())
        {
                msg = "��˵" + me->name(1) + "�ľ��ӱ�" + ob->name(1) + "�ľ���ɱ��ȫ����û��һ���ӻش�Ӫ��";
        } else
                msg = "��˵" + me->name(1) + "�ľ���ȫ����û��һ���ӻ��ξ���Ӫ��";
        message_competition(msg);

        me->move("/quest/quest_jun/sying1"); 
        message("vision", "һ����Ӱٿ�Ĵ��˹������漴���ǡ�ž����"
                "һ�����ͼ�" + me->name() +"ˤ���˵��ϣ�һ��������"
                "������ӡ�\n", environment(me), ({ me }));
        tell_object(me, "�������У�����ñ���������������"
                    "���ص�ˤ���˵��ϡ�\n");
        if (! living(me))
                me->revive();
        return 1;
}

// overide function of quit
int check_quit(object me)
{       
        message_competition("��˵" + me->name(1) +
                            "��ս�����������ӣ������ˡ�");
        restore_status(me);

        if (arrayp(total))
                total -= ({ me });
                
        tell_object(me, "��һ�����ӳ���ս����������������㳡��\n");

        // continue run quit function
        me->move("/d/city/guangchang");
        message("vision", "ֻ��" + me->name() + "������ŵ����˹�����\n",
                environment(me), ({ me }));
        return 1;
}

int fail_war()
{       
        int i;

        remove_enemy();
        message_competition("��˵�ξ������˾��ӻ����ˣ������ɳ�ʹ�߸����ͣ�\n");
        
        if (objectp(king))
        {
                restore_status(king);
                king->apply_condition("junquest_fail", 50);
        }
                
        if (arrayp(total) && sizeof(total))
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                        restore_status(total[i]);
                }               
        }
        set_heart_beat(0);
        king = 0;
        total = ({ });
        start_time = 0;
}

void remove_enemy()
{
        object *enemys;
        int j;

        if (arrayp(enemys = children("/quest/quest_jun/meng/kehan")))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                        }
                        tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name() +
                                  "ͻȻ������Ц������������Ӳ����ˣ�\n");
                        destruct(enemys[j]);
                }
        }                       
        if (arrayp(enemys = children("/quest/quest_jun/meng/mengj")))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name() +
                                          "ͻȻ������Ц������Ѹ�ٹ������У�����սȦ������Ӳ����ˡ�\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name() +
                                          "ͻȻ��ɫ��ϲ������ææ��������Ӳ����ˡ�\n");
                        }
                        destruct(enemys[j]);
                }
        }
        if (arrayp(enemys = children("/quest/quest_jun/meng/mengb")))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name() +
                                        "ͻȻ������Ц������Ѹ�ٹ������У�����սȦ������Ӳ����ˡ�\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name()
                                                  + "ͻȻ��ɫ��ϲ������ææ��������Ӳ����ˡ�\n");
                        }
                        destruct(enemys[j]);
                }
        }
        
        if (arrayp(enemys = children("/quest/quest_jun/song/songb")))
        {
                for (j = 0; j < sizeof(enemys); j++)
                {
                        if (enemys[j]->is_fighting())
                        {
                                enemys[j]->remove_all_killer();
                                tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name()
                                                  + "ͻȻ��ɫһ�䣬Ѹ�ٹ������У�����սȦ������Ӳ����ˡ�\n");
                        }
                        else {
                                tell_room(environment(enemys[j]), HIW "ֻ��" + enemys[j]->name()
                                                  + "��ֵһ�㣬ͻȻ��ɫ��䣬����ææ��������Ӳ����ˡ�\n");
                        }
                        destruct(enemys[j]);
                }
        }
        return;
}

// send message out
void message_competition(string msg)
{
        CHANNEL_D->do_channel(this_object(), "rumor", msg);
}

// remove overide function
void restore_status(object me)
{
        object bingfu, lingjian, zhanma, kaijia;
        
        if (objectp(bingfu = present("bing fu", me)))
                destruct(bingfu);
                        
        if (objectp(lingjian = present("ling jian", me)))
                destruct(lingjian);
        
        if (objectp(zhanma = present("zhan ma", me)))
                destruct(zhanma);
                
        if (objectp(zhanma = present("shizi ma", me)))
                destruct(zhanma);
                
        if (objectp(kaijia = present("kai jia", me)))
                destruct(kaijia);

        me->delete_override("quit");
        me->delete_temp("jun_quest");
        me->delete("party");
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->receive_damage("qi", 0);
        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("eff_qi"));
        me->clear_condition();

}

void give_bouns()
{                         
        int reward, pot, exp, jungong, i;
        object me, bingfu;
        object ob;

        remove_enemy();

        if (! objectp(king))
        {
                if (arrayp(total) && sizeof(total) > 0)
                {
                        for (i = 0; i < sizeof(total); i++)
                        {
                                if (! objectp(total[i]))
                                        continue;
                                restore_status(total[i]);
                        }
                }
                set_heart_beat(0);
                king = 0;
                total = ({ });  
                start_time = 0;
                return;
        }
        
        reward = king->query_temp("jun_quest/reward");

        message("channel:rumor", MAG "�����ξ��ǡ�" + 
                CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60)) +
                "......\n" NOR,
                users());
                
        reward += 20;                  
        if (reward > 200) reward = 200;
        exp = (reward / 2 + random(reward / 2)) * king->query("degree_jungong") * 400; 
        pot = exp / 2; 
        jungong = exp / 5000;
        king->add("guo_shoucheng/reward_exp", exp);
        king->add("guo_shoucheng/reward_potential", pot);
        king->add("guo_shoucheng/reward", jungong);
        king->add("combat_exp", exp);
        king->add("potential", pot);
        king->add("experience", 500 + random(500)); 
        king->add("balance", 1000000);
        if (random(2)) ob = new("/clone/fam/gift/int3");
        else ob = new("/clone/fam/gift/con3");
        ob->move(king, 1);
        if (random(2)) ob = new("/clone/fam/etc/lv7a");
        else ob = new("/clone/fam/gift/dex3");
        ob->move(king, 1);
        if (random(2)) ob = new("/clone/fam/gift/str3");
        else ob = new("/clone/fam/item/stone5");
        ob->move(king, 1);
        
        message("channel:rumor", HIY "�����ξ��ǡ�����������ʵ�گԻ��\n" +
                "            " + king->name(1) + HIY "�����й����ͻƽ������������ƥ����Ůʮ����" +
                "�Ǿ��� " HIR + chinese_number(jungong) +
                HIY " �ߣ��մˣ�\n\n" NOR,
                users());                              

        tell_object(king, HIW "�򿹽��й��������� " + HIR + chinese_number(jungong) +
                          HIW " �߾�����" + HIR + chinese_number(exp) +
                          HIW " �㾭��� " + HIR + chinese_number(pot) +
                          HIW " ��Ǳ�ܺ�һЩʵս��ά������\n" NOR);
               
        restore_status(king);
        king->move("/d/city/guangchang");
        message("vision", "ֻ��" + king->name() + "���˹�����\n",
                environment(king), ({ king }));


        if (arrayp(total) && sizeof(total) > 0)
        {
                for (i = 0; i < sizeof(total); i++)
                {
                        if (! objectp(total[i]))
                                continue;
                        
                        tell_object(total[i], HIR "��������ˣ�׼����ʦ�س��ɣ�\n" NOR);

                        reward = total[i]->query_temp("jun_quest/reward"); 
                        if (reward < 2)
                        {
                                restore_status(total[i]);
                                continue;
                        }
                        if (reward > 200) reward = 200;       
                        exp = (reward / 2 + random(reward / 2)) * total[i]->query("degree_jungong") * 300;
                        pot = exp / 3;
                        jungong = exp / 5000;
                
                        total[i]->add("guo_shoucheng/reward_exp", exp);
                        total[i]->add("guo_shoucheng/reward_potential", pot);
                        total[i]->add("guo_shoucheng/reward", jungong);
                        total[i]->add("combat_exp", exp);
                        total[i]->add("potential", pot);
                        total[i]->add("experience", 500 + random(250)); 
                        total[i]->add("balance", 500000);  
                        if (random(2)) ob = new("/clone/fam/gift/int3");
                        else ob = new("/clone/fam/gift/con3");
                        ob->move(total[i], 1);
                        if (random(2)) ob = new("/clone/fam/etc/lv7a");
                        else ob = new("/clone/fam/gift/dex3");
                        ob->move(total[i], 1);
                        if (random(2)) ob = new("/clone/fam/gift/str3");
                        else ob = new("/clone/fam/item/stone5");
                        ob->move(total[i], 1);
                
                        tell_object(total[i], HIW "�򿹽��й��������� " + HIR + chinese_number(jungong) +
                                              HIW " �߾����� " + HIR + chinese_number(exp) +
                                              HIW " �㾭��� " + HIR + chinese_number(pot) + 
                                              HIW " ��Ǳ�ܺ�һЩʵս��ά������\n" NOR);  
                
                        restore_status(total[i]);
                        total[i]->move("/d/city/guangchang");
                        message("vision", "ֻ��" + total[i]->name() + "���˹�����\n",
                                environment(total[i]), ({ total[i] }));
                }
        }   

        set_heart_beat(0);        
        king = 0;
        total = ({ }); 
        start_time = 0;
        return;
}

