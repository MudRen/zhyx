// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// killer.c

#include <ansi.h>
inherit CLASS_D("generate") + "/chinese";

void create()
{
        
        mapping my;

        ::create();
        set("gender", "����" );
        set("age", 30 + random(30));
        set_name(BLU "������" NOR, ({"figure", "mengmian ren", "ren"}));
        set("long", "�����ͷ�ϴ�������ͷ�֣��˳�׼����ʲ�ỵ�¡�\n");
        set("attitude", "friendly");
        set("scale", 150);
        set("chat_chance_combat", 120);
        set_temp("apply/armor", 300);
        set_temp("apply/damage", 200);

}

void set_from_me(object me, int scale)
{
        int sk_lvl;
        string *ks;
        int i;
        int exp;
        object ob = this_object();
        
        exp = me->query("combat_exp");
        set("combat_exp", exp);
        
        exp /= 100;
        sk_lvl = to_int(pow(to_float(exp), 1.0 / 3)) * 10 + 1; 
        
        if (! ob->query_skills())
                return;
        ks = keys(ob->query_skills());
        for (i = 0; i < sizeof(ks); i++)
                ob->set_skill(ks[i], sk_lvl);               
}

void init()
{
        object me = this_player(); 
        
        ::init();
        if (interactive(me) && visible(me) && 
            ! is_fighting()) 
        {
                set_from_me(me, 100);
                kill_ob(me);
        }
}

void kill_ob(object ob)
{
        if (! is_busy())
                exert_function("powerup");

        message_vision(HIB "$n��$N���ȵ�: ��ʲô����˴󵨣�"+
                           "�����ô�����ɽׯ����\n" NOR, ob, this_object());
        ::kill_ob(ob);
}

void unconcious()
{
        message_vision(HIR "$N���һ������������Ȼ��ذ�ͻȻ����$N���˽�ȥ�����ˡ�\n",
                       this_object());
        destruct(this_object());
        return ;
}

