// This program is a part of NT mudlib

#include <ansi.h>
inherit NPC;

void create()
{
	set_name(HIC "�������" NOR, ({ "eguidao fo", "eguidao", "fo" }) );
	set("gender", "����");
	set("title", HIW "������ػ���" NOR);
	set("age", 200);
	set("long", HIC "���������еĶ�����ķ�\n\n" NOR);

        set("age", 50);
        set("str", 91);
        set("int", 39);
        set("con", 50);
        set("dex", 62);

        set("max_qi", 10000000);
        set("max_jing", 10000000);
        set("max_jingli", 10000000);
        set("jingli", 10000000);
        set("max_neili", 12000000);
        set("neili", 12000000);
        set("jiali", 55000);
        set("combat_exp", 2000000000);
        set("level", 100);
        set("score", 1200000);

        set_skill("force", 2700);
        set_skill("parry", 2700);
        set_skill("dodge", 2700);
        set_skill("sword", 2700);
        set_skill("unarmed", 2700);
        set_skill("pixie-jian", 2700);
        set_skill("literate", 2700);
        set_skill("martial-cognize", 2700);
        set_skill("kuihua-mogong", 2700);

        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("unarmed", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");
        map_skill("parry", "kuihua-mogong");

        prepare_skill("unarmed", "kuihua-mogong");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "sword.bian" :),
                (: perform_action, "sword.tian" :),
                (: perform_action, "sword.qiong" :),
                (: perform_action, "sword.zhenwu" :),
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "unarmed.bian" :),
                (: perform_action, "unarmed.tian" :),
                (: perform_action, "unarmed.qiong" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                
        }) );

        set_temp("apply/attack", 5000);
        set_temp("apply/armor", 10000);
        set_temp("apply/damage", 50000);
        set_temp("apply/unarmed_damage", 50000);
        set_temp("apply/add_xuruo", 90);
        set_temp("apply/reduce_xuruo", 100);
        set_temp("apply/add_damage", 100);
        set_temp("apply/reduce_damage", 60);
        set_temp("apply/reduce_busy", 30);
        set_temp("apply/add_busy", 10);

        set("auto_perform", 1);
        // set("bonus", 100000);

        setup();

        carry_object("/clone/weapon/green_sword")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int accept_fight(object ob) 
{
     competition_with(ob);
     return -1; 
}
   
void fight_ob(object ob)
{
	if (is_fighting(ob))
		return;

        message_vision(HIW "$N" HIW "���һ����һ�����������"
                       "���������ƻá�\n" NOR, this_object(), ob);
                                                      
        ::fight_ob(ob);
}

/*
varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}
*/

mixed hit_ob(object me, object ob, int damage_bouns)
{
        int damage;
        
        damage = 60000 + random(60000);
        damage -= ob->query_temp("apply/reduce_cold");
        if (damage < 0) damage = 0;
        ob->receive_wound("qi", damage, me);
        me->set("neili", me->query("max_neili"));
        return HIB "$N" HIB "һ�����ȣ�����ʱ��������ԩ�꣬һ�����ް�����\n" NOR;
}

void win()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision(HIB "$N���˿�$n���ٺ�Ц��������֪����򲻰�����ζ��ʲô��"
                       "����ζ��������������������\n" NOR,
                       this_object(), ob);
                       
        call_out("ob_die", 1, ob);  
        ::win();
}

void ob_die(object me)
{
        me->move("/clone/misc/void");   
        me->set_temp("die_reason", "�������������ɱ����");
        me->die();       
}

void lost()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision( HIB "$N��ѽһ������$nŭ���������������ң��´ο�û����ô�����ˣ���\n" NOR,
                        this_object(), ob );
        message_vision( HIB "$N˵������һ�ӣ�һ��ǿ���Χ�㣬�㷢�����������޵\n" NOR, 
                        this_object(), ob );
                     
        ob->move("/clone/misc/void");   
                
        ::lost();
}

int accept_kill(object ob)
{
        return 0;
}

int accept_hit(object ob)
{
        return 0;
}
