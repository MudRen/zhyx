 // nezha.c
 //��߸��̫��
 //PLZW 2003-11-29

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("��߸��̫��", ({ "ne zha", "ne", "zha" , "nezha"}) );
        set("title", HIM "����ͯ��" NOR);
        set("gender", "����");
        set("age", 16);
        set("long", "����һ�������ɰ���С���ӣ�ȴ����͸�����������ʡ�\n");
        set("combat_exp", 10000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 25000);
        set("neili", 25000);
        set("max_jing", 25000);
        set("jing", 25000);
        set("max_qi", 30000);
        set("qi", 30000);
        set("jingli", 25000);
        set("max_jingli", 25000);

        set("str", 120);
        set("int", 45);
        set("con", 120);
        set("dex", 120);

        set_skill("unarmed", 1500);
        set_skill("sword", 1500);
        set_skill("parry", 1500);
        set_skill("dodge", 1500);
        set_skill("force", 1500);

        set("jiali", 400);

        set_temp("apply/attack", 400);
        set_temp("apply/unarmed_damage", 500);
        set_temp("apply/armor", 1000);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set("born_time", time());
                keep_heart_beat();
        }

        setup();
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

 		message_vision(HIW "$N" HIW "���һ���������ͷ���ۻ��������е�Ǭ��Ȧ����Ϯ����\n" NOR,	this_object(), ob);
        ::fight_ob(ob);
        if (! is_killing(ob->query("id")))
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$Nɨ��$nһ�ۣ�û����$n��\n",
                       this_object(), ob);
        return 0;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
		me->set("neili", me->query("max_neili"));
        switch(random(8))
        {
        	case 7:
		        ob->receive_wound("qi", 400 + random(400), me);
        		return HIY "$N"HIY"����"HIR"������"HIY"������ֹ�âѣĿ���ˣ�һ�������ӳ�����ؾ�\n"
        					"ʧɫ�ʣ� Ѹ�����׵Ļ���$n" HIY"�����˱��޿ɱܣ�\n" NOR;
        		break;
        	case 6:
        	    ob->receive_wound("qi", 300 + random(300), me);
				return HIC "$N"HIC"����"HIG"Ǭ��Ȧ"HIC"����������â��$nϮ����$n��������¼�����Ѫ��\n" NOR;
        		break;
        	default:
        	    ob->receive_wound("qi", 200 + random(200), me);
        		return HIR "$N" HIR "���л���ǹ��������������棬��$n�����������������ҽ�������\n" NOR;
        		break;
        }
        	
}

void unconcious()
{
        die();
}

void die()
{
        object ob;
        switch(random(3))
        {
            case 2:
                ob = new("/clone/gift/fenghuolun");
                break;
            default:
                ob = new("/clone/gift/huntianling");
                break;
        }
        command("chat ѽ���벻������Ҳ����������ģ�");
        message_sort(HIR "$N" HIR "��һ����Ѫ�����ƶ�ȥ��ֻ��������һ��"
                     "���죬$N" HIR "������һ" + ob->query("unit") +
                     ob->name() + HIR "��\n", this_object());
        ob->move(environment());
        destruct(this_object());
}

void random_move()
{
        if (time() - query("born_time") > 1800)
        {
                message_vision("$N����ææ�����ˡ�\n", this_object());
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "��˵" + name() + HIM "������������׽����ͥ���Ⱥ���۷��䡣\n" NOR);
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}

