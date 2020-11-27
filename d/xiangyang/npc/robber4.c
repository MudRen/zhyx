// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit NPC;

int get_level(int exp);
void seek_ob(object me);

void create()
{                            
        set_name("�ɹż���",({ "menggu jianshou","jianshou" }) );
        set("gender", "����" );
        set("long","����һ���ɹ�����֣�������ؼ����������ǵ������\n");

        set("int", 30);
        set("str", 30+random(10));
        set("con", 20+random(5));
        set("dex", 20+random(5));
        set("age", 20+random(30));
        set("per", 15+random(15));

        set("combat_exp", 1000000);
        set("max_qi",3000);
        set("qi",query("max_qi"));
        set("max_jing",2000);
        set("jing",query("max_jing"));
        set("max_neili",5000);
        set("neili",query("max_neili"));
        set("max_jingli",4000);
        set("jingli",query("max_neili"));

        set_skill("arrow", 100);
        set_skill("lianzhu-arrow", 100); 
        map_skill("arrow", "lianzhu-arrow");
        
        set("chat_chance",10);
        set("chat_msg", ({
                (: random_move :),   
        }) );

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}                                           

void change_ob(object me)
{
        int level, exp;
        int lvl;

        exp = (me->query("combat_exp") /(random(3) + 4)) * 4;
        level = get_level(exp);
        level = level / 3 + random(level / 3);
        
        if (me->query_skill("arrow", 1) > level)
        level = me->query_skill("arrow", 1);
        level = level / 2 + (random(21)-10) * level / 100;

        set_skill("arrow", level);
        set_skill("lianzhu-arrow", level); 
        set_skill("xuedao-daofa", level);
        set_skill("cuff", level);
        set_skill("yujiamu-quan", level);
        set_skill("dodge", level);
        set_skill("blade", level);
        set_skill("parry", level);
        set_skill("hand", level);
        set_skill("dashou-yin", level);
        set_skill("shenkong-xing", level);
        set_skill("longxiang", level);

        map_skill("force", "longxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");
        map_skill("cuff", "yujiamu-quan");        
        map_skill("arrow", "lianzhu-arrow");

        set("combat_exp", exp);
        set("max_qi", me->query("max_qi") / 10);
        if (query("max_qi") < 400) 
                set("max_qi", 400);
        set("eff_qi", query("max_qi")); 
        set("qi", query("max_qi"));
        set("max_jing", me->query("max_jing") / 10);
        if (query("max_jing") < 200) 
                set("max_jing", 200);   
        set("eff_jing", query("max_jing")); 
        set("jing", query("max_jing"));
        set("max_neili", me->query("max_neili") / 10);
        set("neili", query("max_neili"));
        set("max_jingli", query("max_neili"));
        set("jingli", query("max_neili"));
        set("killer", me->query("id"));
        lvl = (query("str") + level / 10) / 10 - 1;
        if (lvl > 8) lvl = 8;
        carry_object("/quest/zhuzao/weapon/bow/bow" + lvl)->wield();
        call_out("seek_ob", 2, this_object());
        return;
}

int get_level(int exp)
{
        int level = 0;
        do {
                level++;
        } 
        while (level * level * level < (exp * 10));
        if (level > 60)
                return level - 60;
        else 
                return 60;
}

void seek_ob(object me)
{
        int step, i, num;
        string site_name;
        object bow, killer, room;

        killer = find_player(me->query("killer"));
        command("yun powerup");   

        if (! killer || ! environment(killer))
        {
                remove_call_out("seek_ob");  
                destruct(me);
                return;
        }

        room = environment(killer);
        
        if (! me->query("where")
        ||  ! killer->query_condition("jobjianlou_limit")
        ||  ! room->query("site")
        ||  room->query("site") != killer->query_temp("guo_shoucheng/where"))
        {
                remove_call_out("seek_ob");
                destruct(me);
                return;
        }

        if (! killer->is_net_dead())
        {
                bow = me->query_temp("weapon");
                step = environment(me)->query("step");

                if (living(me) && bow->query("is_bow") && step <= bow->query("dam") / 200)
                {
                        num = me->query_skill("lianzhu-arrow", 1) / 100 + 1;
                        if (random(10) > 2) num = 1;
                        if (me->query("qi") > num * 400 && me->query("jing") > num * 100)
                        {
                                tell_object(all_inventory(room),
                                        HIB "�����һ�����ҵ�Σ����"HIR"����"HIW+chinese_number(step)+"����"HIB"�⴫����\n"NOR);  
                                for (i = 0; i < num; i++)
                                        bow->do_shoot(me->query("killer"), me, bow, room, "west", step);
                                if (num > 4) num = 4;
                                if (! me->is_busy())
                                        me->start_busy(num * 2);
                        } else
                                tell_object(all_inventory(room),
                                        HIB"����ú���������"HIR"����"HIW+chinese_number(step)+"����"HIB"�⳯����߿�����һ�ۣ�\n"NOR);
                }
        }
        remove_call_out("seek_ob"); 
        call_out("seek_ob", 5, me);  
        return;
}

void die()
{
        object ob;
            
        if (! objectp(ob = query_last_damage_from()))
                return;

        if (userp(ob) &&
            ob->query_temp("gou_shoucheng/mark_jianlou") &&
            ob->query_temp("guo_shoucheng/start_job") == 1)
        {
 
                if (query("killer") == ob->query("id"))
                        ob->add_temp("guo_shoucheng/killed_mgb", query_str() / 5);
                else
                        ob->add_temp("guo_shoucheng/killed_mgb", 1);
                tell_object(ob, RED "һ���ɹŹ�������ɥ�����������֮�£�\n" NOR);
        }
        destruct(this_object());
        return;
}

