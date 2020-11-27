// Updated by Lonely

#include <room.h>
#include <ansi.h>
inherit ITEM;
inherit F_SSERVER; 

#include "way.h"

varargs void attack_begin(object me, object target, object room, object env, string dir);
// int do_waring(object me, object ob);

void create()
{
        set_name(HIW"���"NOR, ({"ling jian","ling"}) );   
        set_weight(10);
        set("no_get",1);
        set("no_steal",1);
        set("no_put",1);
        set("no_drop",1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("long",HIW"һö���ν�������ǲ���������\n"NOR);  
                set("material", "copper");
             }
        set("master","lonely");   
        set("owner","lonely");
        setup();
}


void init()
{
        object me = this_player(), ob = this_object();
        if (me->query("id") == ob->query("owner"))
        {
                add_action("do_escort", "yaliang");  
                add_action("do_move", "move");    
                add_action("do_train", "xunlian");    
                add_action("do_attack", "tuji");
                add_action("do_order", "order");   
                add_action("do_inquiry", "inquiry"); 
                add_action("do_yun", "yun");
                add_action("do_yun", "exert");
                
/*
                remove_call_out("do_waring");
                call_out("do_waring", 1, me, ob);
*/
        } 
}

/*
int do_waring(object me, object ob)
{
        if (! objectp(me) || ! objectp(ob))
                return 0;
        
        if (me->query("id") == ob->query("owner"))
        {
                add_action("do_escort", "yaliang");  
                add_action("do_move", "move");    
                add_action("do_train", "xunlian");    
                add_action("do_attack", "tuji");
                add_action("do_order", "order");   
                add_action("do_inquiry", "inquiry"); 
                add_action("do_yun", "yun");
                add_action("do_yun", "exert");
                
                remove_call_out("doing");
                call_out("do_waring", 1, me, ob);
          }
}               
*/
                
int do_yun(string arg)
{
        if (arg != "qi" && arg != "recover" && arg != "jing"
        &&  arg != "regenerate" && arg != "heal" && arg != "jingheal")
        {
                tell_object(this_player(),"��������һ��֮ͳ˧�ˣ�һ��һ������˼��\n");
                return 1;
        }
        return 0;
}

int do_escort()
{
        object me = this_player(), ob = this_object();

        if (! me->query_temp("jun_quest/escort"))
                return notify_fail("Ԫ˧��δ������Ѻ�����ݵ����񣬲�Ҫ�����ж���\n");  

        if (me->query_temp("jun_quest/move"))
                return notify_fail("�����Ѿ�������ȥ�ˣ�\n");   

        ob->start_move(me, ob);
        me->set("no_get", 1);
        me->set_temp("jun_quest/move", "forward");
        me->set_temp("jun_quest/last_move", "/quest/quest_jun/sying1"); 
        me->add_temp("jun_quest/reward", 10);

        message_vision(HIW "$Nһ���������ƣ���ȵ���Ԫ˧���"
                + "���̿�����ʦѺ�����ݣ��������󣡣�\n" NOR, me);     
        return 1;
}

void start_move(object me,object ob)
{
        call_out("move_me", 4, me, ob);
}

void move_me(object me, object ob)
{
        object owner, room, master;
        mapping move_way;
        string site, temp;
        int liangcao;
        
        owner = environment(ob);
        if (! owner || ! owner->is_character()
        ||  owner->query("id") != ob->query("owner"))
        {
                destruct(ob);
                return;
        }

        room = environment(owner);
        site = file_name(room);

        if (me->query_temp("jun_quest/move") == "forward")
        {
                move_way = forward_way;
                if (site == "/d/bianliang/chengmen")
                {
                        me->start_busy(10 + random(10));   
                        message_vision(HIY "$N����Ľ���������ڵ����˾�ʦ������"
                                + "$N�������������������̿�ʼ���о��ı���....\n" NOR, me);
                        me->set_temp("jun_quest/move", "backward");
                        move_way = backward_way;
                }
        } else 
        if (me->query_temp("jun_quest/move") == "backward")
        {
                move_way = backward_way;
                if (site == "/quest/quest_jun/sying1")
                {
                        message_vision(HIY "$N����Ľ���������ڵ�����������Ӫ��"
                                + "$N�����ݼ�ʱ֧Ԯ�˴���Ĳ���....\n" NOR, me);
                        me->delete_temp("jun_quest/escort");
                        me->delete_temp("jun_quest/move");  
                        me->delete_temp("jun_quest/last_move");
                        me->add_temp("jun_quest/reward", 20);
                        me->start_busy(5 + random(5));
                        me->delete("no_get");
                        master = find_player(ob->query("master"));
                        if (! master) 
                                master = find_living(ob->query("master"));
                        if (objectp(master) && environment(master) 
                        &&  master->query_condition("junquest_song"))
                        {
                                tell_object(master,
                                        HIY "Ѻ�����ݵľ����ˣ���Ĳ����������ˣ�\n" NOR);
                        }
                        temp = read_file("/quest/quest_jun/song/liangcao", 1, 1);
                        liangcao = atoi(temp) + 100 + random(100);
                        temp = sprintf("%d", liangcao);
                        write_file("/quest/quest_jun/song/liangcao", temp, 1);

                        remove_call_out("move_me");
                        return;
                }
        }
        if (! living(me) || me->is_fighting() || me->is_busy())
        {
                remove_call_out("move_me");
                call_out("move_me", 4, me, ob);
                return;
        }                    

        if (move_way[site])
        {
                me->set_temp("jun_quest/last_move", site);
                me->command("go " + move_way[site]);
        } else
        if (me->query_temp("jun_quest/last_move"))
                me->move(me->query_temp("jun_quest/last_move"));

        message_vision(YEL "$N�����Ž��������������ҹ���н���.....\n", me);
        me->start_busy(2 + random(2));
        remove_call_out("move_me");
        call_out("move_me", 4, me, ob);
        return;
}

int do_attack(string arg)
{
        object me = this_player(), obb, room, env;
        string *dirs, dir, who;
        mapping exits;
        int i;

        env = environment(me);  

        if (! arg) return notify_fail("��Ҫָ�Ӳ��ӳ�˭���������\n");

        if (me->query_temp("jun_quest/attack"))
                return notify_fail("��Ķ������������������Ҫ�ҷ������ˣ�\n"); 

        if (me->query_temp("jun_quest/group") < 1)
                return notify_fail("��Ķ����Ѿ���ʧ�������޷��������ˣ�\n"); 
 
        if (me->query_temp("jun_quest/train") == "infantry")
        {
                if (env->query("no_fight"))
                        return notify_fail("���ﲻ��ս������\n");

                if (objectp(obb = present(arg, env)))
                {
                        if (obb->query("is_quest") || obb->query("is_robber"))
                                return notify_fail("������������ǲ�Ҫ���������Ƿǵĺã�\n");

                        message_vision(HIW "$N���������������Ӫ���󣡶��鿪ʼ"
                                + "�ų�����ķ�����һƬ��˸�ĵ���\n�У�$Nָ�Ӷ��鷢��"
                                + "�˿��µĳ�棡\n" NOR, me);

                        me->set_temp("jun_quest/attack", 1);
                        call_out("attack_over", 10, me);
                        attack_begin(me, obb, room, env, ""); 
                        return 1;  
                } else
                        return notify_fail("�޷��ҵ�Ŀ�꣬����tuji sb ָ����Ķ��飡\n");
        } else
        if (me->query_temp("jun_quest/train") == "cavalry")
        {
                if (sscanf(arg, "%s on %s", who, dir) == 2)
                {
                        if (mapp(exits = env->query("exits")))
                        {
                                dirs = keys(exits);
                                for (i = 0; i < sizeof(dirs); i++)
                                if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED)
                                        dirs[i] = 0;
                                dirs -= ({ 0 });
                                if (mapp(exits) && exits[dir])
                                {
                                        if (! room = find_object(exits[dir]))
                                                room = load_object(exits[dir]);
                                        if (room)  
                                        {
                                                if (room->query("no_fight"))
                                                        return notify_fail("���ﲻ����˺ɱ����\n");

                                                if (! objectp(obb = present(who, room)))
                                                        return notify_fail(
                                                                "�޷��ҵ�Ŀ�꣬����tuji sb on <����> ָ����Ķ��飡��\n");

                                                if (obb->query("is_quest") || obb->query("is_robber"))
                                                        return notify_fail("������������ǲ�Ҫ���������Ƿǵĺã�\n");

                                                me->set_temp("jun_quest/attack", 1);
                                                call_out("attack_over", 10, me);    
                                                me->move(room);
                                                message_vision(
                                                        HIR "$N������һ֧�ξ������$n��ɱ������\n" NOR,
                                                        me, obb);
                                                attack_begin(me, obb, room, env, "");
                                                return 1;
                                        }
                                }
                        }
                } else
                        return notify_fail("����tuji sb on <����> ָ����Ķ��飡��\n");
        } else
        if (me->query_temp("jun_quest/train") == "archer")
        {
                if (sscanf(arg, "%s on %s", who, dir) == 2)
                {
                        if (mapp(exits = env->query("exits")))
                        {
                                dirs = keys(exits);
                                for (i = 0; i < sizeof(dirs); i++)
                                if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED)
                                        dirs[i] = 0;
                                dirs -= ({ 0 });
                                if (mapp(exits) && exits[dir])
                                {
                                        if (! room = find_object(exits[dir]))
                                                room = load_object(exits[dir]);
                                        if (room)  
                                        {
                                                if (room->query("no_fight"))
                                                        return notify_fail("���ﲻ����˺ɱ����\n");

                                                if (! objectp(obb = present(who, room)))
                                                        return notify_fail(
                                                                "�޷��ҵ�Ŀ�꣬����tuji sb on <����> ָ����Ķ��飡��\n");

                                                if (obb->query("is_quest") || obb->query("is_robber"))
                                                        return notify_fail("������������ǲ�Ҫ���������Ƿǵĺã�\n");

                                                message_vision(HIB "$N���������������Ӫ׼����һ������������"
                                                        + "�����������⡪���������\n$Nһ�����£������뷢��\n" NOR, me);  
                                                me->set_temp("jun_quest/attack", 1);
                                                call_out("attack_over", 10, me);    
                                                attack_begin(me, obb, room, env, dir);
                                                return 1;
                                        }
                                }
                        }
                } else
                        return notify_fail("����tuji sb on <����> ָ����Ķ��飡��\n");
        } else
                return notify_fail("��δ��һ��һ�䣬ָ�Ӹ�ʲôѽ��\n");
}

varargs void attack_begin(object me, object target, object room, object env, string dir)
{
        object bow;
        int i;
        
        for(i = 0; i < me->query_temp("jun_quest/group"); i++)
        {
                if (objectp(target)
                &&  (me->query_temp("jun_quest/train") == "cavalry" 
                ||  me->query_temp("jun_quest/train") == "infantry"))  
                {
                        message_vision(HIR "$Nָ�ӵ�����ɱ���׶���"
                                + "��������㳯$n�����˹�������\n" NOR, me, target);  
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
                        me->add_temp("jun_quest/reward", 4);
                } else
                if (objectp(target)
                &&  me->query_temp("jun_quest/train") == "archer")
                {
                        bow = me->query_temp("weapon");
                        if (bow && bow->query("is_bow"))
                                bow->do_shoot(target->query("id"), me, bow, room, dir, 1);  
                        me->add_temp("jun_quest/reward", 4);
                } 
                else break;
        }

        if (me->query_temp("jun_quest/train") == "cavalry")
        {
                message_vision(HIW "һ���ɱ����$N�������ξ�������"
                        + "һ����ʧ�ˣ�\n" NOR, me);
                me->move(env);
        }                         

        return;
}

void attack_over(object me)
{
        if (objectp(me))
        {
                message_vision(HIW "$N��������һ�ӣ���������һ��������"
                        + "��ʼ����׼��������һ�ֵĹ�������\n" NOR, me); 
                me->delete_temp("jun_quest/attack");
        }
        return;
}      

int do_train()
{
        object me = this_player(), weapon;

        if (! me->query_temp("jun_quest/train"))
                return notify_fail("Ԫ˧��û������ѵ������ɣ�\n");

        if (! environment(me) || 
            file_name(environment(me)) != "/quest/quest_jun/sying1")
                return notify_fail("����뵽Ԫ˧���������ſ���ѵ�����飡\n");

        if (me->query_temp("jun_quest/train_begin"))
                return notify_fail("�㲻������ѵ�������𣿣�\n");

        message_vision(HIW "$N�ӹ��������������"
                + "ĩ��������ĩ������ǰȥ��Ӫѵ�����飡��\n" NOR, me);

        if (me->query_temp("jun_quest/train") == "cavalry")
                me->move("/quest/quest_jun/sying3");
        else
        if (me->query_temp("jun_quest/train") == "infantry")
                me->move("/quest/quest_jun/sying2");
        else
        if (me->query_temp("jun_quest/train") == "archer")
        {
                weapon = me->query_temp("weapon");
                if (weapon) weapon->unequip();
                me->command("wield bow");
                me->move("/quest/quest_jun/sying4");
        } else
        return notify_fail("������ʲô�������ж��������۴���\n");

        me->set_temp("jun_quest/train_begin", 1);
        call_out("train_begin", 2, me);
        call_out("check_me", 2, me);
        return 1;
}


void train_begin(object me)
{
        object room, master, ob;
        string temp;
        int liangcao;
         
        ob = this_object();
        master = find_player(ob->query("master"));
        if (! master) master = find_living(ob->query("master"));

        if (! me->query_temp("jun_quest/train"))
        {
                remove_call_out("train_begin");
                me->delete_temp("jun_quest/train_begin");
                tell_object(me, "Ԫ˧��û�з��ɸ���ѵ����������\n");
                return;
        }

        temp = read_file("/quest/quest_jun/song/liangcao", 1, 1);
        liangcao = atoi(temp);
        if (liangcao <= 10)
        {
                remove_call_out("train_begin");
                me->delete_temp("jun_quest/train_begin");
                tell_object(me,"���ݲ��㣬����ѵ��������ֹ��\n");

                if (objectp(master) && environment(master)
                &&  master->query_condition("junquest_song"))
                {
                        tell_object(master,
                                HIY "���ݲ��㣬��Ķ��鱻����ֹ��ѵ����\n" NOR);
                }                                    
                return;
        }

        if (me->query_temp("jun_quest/group") > me->query("degree_jungong"))
        {
                remove_call_out("train_begin");
                me->delete_temp("jun_quest/train_begin");
                tell_object(me,"��������������㣬ѵ�����˸�����Ķ����ˣ�\n");

                if (objectp(master) && environment(master)
                &&  master->query_condition("junquest_song"))
                {
                        tell_object(master, HIY "����ѵ����һӪ�ľ��񲿶��ˣ�\n" NOR);
                }                                    
                return;
        }

        room = environment(me);
        if (! room || ! room->query("train")
        ||  room->query("train") != me->query_temp("jun_quest/train"))
        {
                remove_call_out("train_begin");
                me->delete_temp("jun_quest/train_begin");  
                tell_object(me, "���㵽ָ���ı�Ӫ����ѵ�����飡\n"); 
                return;
        }

        if (random(me->query("degree_jungong")) > 1)
        {
                message_vision(HIW "$N����������һ�ӣ����鿪ʼ���ᣬ"
                        + "��ʼ�����Ų�ͬ�����Σ�����ɢ����\n��ʱ��Ȼ���򣬷�"
                        + "ʱ�Ӷ����ң�����$N���������ñ�֮������������\n" NOR, me);
                me->add("eff_qi", 200);
        } else
                message_vision(HIY "$N����������һ�ӣ����Ƕ�������Һ��ģ�"
                        + "��������$N��ָ�ӵ�ǲ��\n$Nֱ���ô����ӵ��ۣ�����\n" NOR, me);

        liangcao -= 2;
        temp = sprintf("%d", liangcao);
        write_file("/quest/quest_jun/song/liangcao", temp, 1);
        remove_call_out("train_begin");
        call_out("train_begin", 10, me);

        return;
}

void check_me(object me)
{
        object *ob, obb, env, room;
        string *dirs, dir;
        mapping exits;
        int group, num, i, g;

        if (! objectp(me)) return;

        group = (me->query("eff_qi") - me->query("max_qi")) / 2000; 
        me->set("qi", me->query("eff_qi"));
        
        num = group - me->query_temp("jun_quest/group");
        
        g = (int)me->query_temp("jun_quest/group");
        g = 0 - g;
    
        if (num > 0 && me->query_temp("jun_quest/train"))
        {
                tell_object(me, HIR "��Ķ��龫�������ˣ�\n" NOR);
                me->add_temp("jun_quest/group", num);
        }

        if (num < 0 && ! me->query_temp("jun_quest/train_begin"))
        {
                if (num < g) num = g;
                tell_object(me, HIW "����ʧ��" HIR + chinese_number(-num)
                        + HIW"Ӫ��ʿ����\n"NOR);
                me->add_temp("jun_quest/group", num);
        }

        if (group <= 1 && !me->query_temp("jun_quest/train_begin"))
        {
                me->set_temp("jun_quest/group", 0);
        }

        env = environment(me);

        if (! me->query_temp("jun_quest/attack")
        &&  me->query_temp("jun_quest/train") == "cavalry")
        {
                if (mapp(exits = env->query("exits")))
                {
                        dirs = keys(exits);
                        for (i = 0; i < sizeof(dirs); i++)
                        if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED)
                                dirs[i] = 0;
                        dirs -= ({ 0 });

                        if (mapp(exits))
                        {
                                dir = dirs[random(sizeof(dirs))];
                                if (! room = find_object(exits[dir]))
                                        room = load_object(exits[dir]);
                                if (room)  
                                {
                                        ob = all_inventory(room);
                                        if (sizeof(ob) > 0)
                                        {
                                                for (i = 0; i < sizeof(ob); i++)
                                                {
                                                        obb = ob[i]; 
                                                        if (obb->query_temp("jun_quest/party") == "meng")
                                                        {
                                                                me->set_temp("jun_quest/attack", 1);
                                                                call_out("attack_over", 10, me);    
                                                                me->move(room);
                                                                message_vision(
                                                                        HIR "$N������һ֧�ξ������$n��ɱ������\n" NOR,
                                                                        me, obb);
                                                                attack_begin(me, obb, room, env, "");
                                                                break;
                                                        }
                                                }
                                        }
                                }
                        }
                } 
        } else
        if (! me->query_temp("jun_quest/attack")
        &&  me->query_temp("jun_quest/train") == "infantry")
        {
                ob = all_inventory(env);   
                if (sizeof(ob) > 0)
                {
                        for (i = 0; i < sizeof(ob); i++)
                        {
                                obb = ob[i]; 
                                if (obb->query_temp("jun_quest/party") == "meng")
                                {
                                        message_vision(HIW "$N���������������Ӫ���󣡶��鿪ʼ�ų�����"
                                                + "�ķ�����һƬ��˸�ĵ���\n�У�$Nָ�Ӷ��鷢���˿��µĳ�棡\n" NOR, me);
                                        me->set_temp("jun_quest/attack", 1);
                                        call_out("attack_over", 10, me);
                                        attack_begin(me, obb, room, env, "");   
                                        break;
                                }
                        }
                }
        } else
        if (! me->query_temp("jun_quest/attack")
        &&  me->query_temp("jun_quest/train") == "archer" 
        &&  me->query("qi") > me->query_temp("jun_quest/group") * 200
        &&  me->query("jing") > me->query_temp("jun_quest/group") * 100)
        {
                if (mapp(exits = env->query("exits")))
                {
                        dirs = keys(exits);
                        for (i = 0; i < sizeof(dirs); i++)
                        if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED)
                                dirs[i] = 0;
                        dirs -= ({ 0 });

                        if (mapp(exits))
                        {
                                dir = dirs[random(sizeof(dirs))];
                                if (! room = find_object(exits[dir]))
                                        room = load_object(exits[dir]);
                                if (room)  
                                {
                                        ob = all_inventory(room);
                                        if (sizeof(ob) > 0)
                                        {
                                                for(i = 0; i < sizeof(ob); i++)
                                                {
                                                        obb = ob[i]; 
                                                        if (obb->query_temp("jun_quest/party") == "meng")
                                                        {
                                                                if (! me->query_temp("weapon")) 
                                                                        me->command("wield bow");
                                                                message_vision(HIB "$N���������������Ӫ׼����һ������������"
                                                                        + "�����������⡪���������\n$Nһ�����£������뷢��\n" NOR,
                                                                        me);  
                                                                me->set_temp("jun_quest/attack", 1);
                                                                call_out("attack_over", 10, me);    
                                                                attack_begin(me, obb, room, env, dir);
                                                                break;
                                                        }
                                                }
                                        }
                                }
                        }
                } 
        }

        if (file_name(env) == "/quest/quest_jun/myuanmen1" && ! me->is_busy()
        &&  me->query_temp("jun_quest/party") == "song")
                me->command("break");
        remove_call_out("check_me");
        call_out("check_me", 1, me);
        return;
}

int do_order(string arg)
{
        object me = this_player(), ob, ling, obb;
        string who, what, dir;
        int i, n, flag;
        mapping jiang;

        if (! arg || sscanf(arg, "%s to %s", who, what) != 2)
                return notify_fail("���� order sb to do sth. ���������\n");

        if (! objectp(ob = present(who,environment(me))))
                return notify_fail("����û������Ե��ȵ��������죡\n");

        if (ob->query_temp("jun_quest/party") != "song")
                return notify_fail("�Է������ξ�����ι�����ȣ���\n");

        if (! ob->query_temp("jun_quest/train")) 
                return notify_fail("��֧������δѵ����죬�ѿ����ã�\n");

        if (ob == me)
                return notify_fail("�Լ������Լ����㲻���۰��㣿��\n");

        if (ob->query("degree_jungong") > me->query("degree_jungong"))
                return notify_fail("�Է����α���ߣ����������˼ң�\n");

        switch(what)
        {
        case "follow":
                message_vision(HIY "$N��һ��˼��������ҵ����������$n��"
                        + "��ͳ�����ӭս�ɹŴ����\n�����뼴�̵�������Э����ս��\n" NOR, me, ob);
                message_vision(HIW "$N����Ӧ����ĩ��������ԸΪ����ЧȮ��֮�ͣ�\n" NOR, ob);
                ob->set_leader(me);
                break;

        case "guard":
                message_vision(HIY "$N��ϸ�鿴�����ܵĵ��Σ�������ҵ����������$n���"
                        + "�˴�������Ҫ��\n�����ѹ��������뽫���ڴ˴����Զ��أ�\n" NOR, me, ob);
                message_vision(HIW "$N����Ӧ����ĩ������������һ��һ�䣬����ʧ��أ�\n" NOR, ob);
                ob->set_leader(0);
                break;

        case "stop":
                if (ob->query_temp("jun_quest/escort"))
                        return notify_fail("�Է��Ѿ����о����ˣ��޷��������ӣ���\n");
                message_vision(HIY "$N��ϸ�鿴�����ܵĵ��Σ�������ҵ����������$n���"
                                + "����ֹͣ�����н�����\n" NOR, me, ob);
                message_vision(HIW "$N����Ӧ����ĩ����������\n" NOR, ob);
                ob->command("move stop");
                break;

        default:
                if (sscanf(what, "move %s", dir) == 1 
                &&  environment(me)->query("exits/" + dir))
                {
                        if (ob->query_temp("jun_quest/escort"))
                                return notify_fail("�Է��Ѿ����о����ˣ��޷��������ӣ���\n");

                        message_vision(HIY "$N��ϸ�鿴�����ܵĵ��Σ�������ҵ����������$n���"
                                + "�������첿��\n�����н����������󣡣�\n" NOR, me, ob);
                        message_vision(HIW"$N����Ӧ����ĩ����������\n" NOR, ob);
                        ob->set_leader(0);
                        ob->command("move " + dir);
                } else   
                if (environment(me)->query("exits/" + what))   
                {
                        ob->set_leader(0);
                        ob->command("go " + what);
                } else
                        return notify_fail("��Ϊһ��֮ͳ�죬�벻Ҫ������ľ�Ȩ��\n");
                 break;
        }
        return 1;
}                         

int do_inquiry()
{
        object me = this_player();
        string temp, str;
        int liangcao;  
                                                                    
        str = HIY "��Ŀǰͳ��������£�\n" NOR;
        str += me->short(1) + "\n" NOR;
        str += HIW "         Ŀǰͳ����                        " + HIR
                + chinese_number(me->query_temp("jun_quest/group")) + "Ӫ\n";

        temp = read_file("/quest/quest_jun/song/liangcao", 1, 1);
        liangcao = atoi(temp);
        str += HIM "Ŀǰ���л�������" + chinese_number(liangcao) + "��\n" NOR; 
        write(str);
        return 1;
}  


int do_move(string dir)
{
        object me = this_player();

        if (! dir || dir == "stop")
        {
                remove_call_out("move_on");
                write("�����н���ֹ��\n");
                return 1;
        }

        if (environment(me)->query("exits/" + dir))
        {
                call_out("move_on", 2, me, dir);
                write("���ӿ�ʼ�н���\n");
                return 1;
        } else
                write("�޷��ƶ���û��ָ������ĳ��ڣ�\n");
        return 1;
}

void move_on(object me,string dir)
{
        if (! environment(me)->query("exits/" + dir))
        {
                remove_call_out("move_on");
                write("�޷��ƶ���û��ָ������ĳ��ڣ�\n");
                return;
        }

        if (me->is_fighting() || me->query_temp("jun_quest/attack"))
        {
                remove_call_out("move_on");
                call_out("move_on", 4, me, dir);
                return;
        } else
        if (me->command("go " + dir))
        {
                remove_call_out("move_on");
                call_out("move_on", 4, me, dir);
                return;
        } else
        {
                remove_call_out("move_on");
                write("�޷��ƶ����н���ֹ��\n");
                return;
        }
}

void owner_is_killed() { destruct(this_object()); }

