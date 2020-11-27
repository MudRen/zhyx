#include <weapon.h>
#include <ansi.h>

inherit SWORD;

string do_wield();
string do_unwield();

void create()
{

        set_name(HIY "��������" NOR, ({ "canyang baojian", "canyang",  
                                        "sword" })); 
        set_weight(2500);
        if (clonep())
                set_default_object(__FILE__);
        else {

                set("long", HIY " 
�˽�����ߣ�ϸ������ͨ�巺����⡣�����������Ͽ̲���ͼ 
�ƣ�����֮�ϻ�����������������Ĺ�׭���ƺ�����ѧ�йء�\n" NOR); 
                set("unit", "��");
                set("value", 800000);
                set("no_sell", "����Ҳ�������Ҷ�������!");
                set("no_put", "�ⶫ����װ����ȥ!");
                set("material", "steel");
                set("wield_msg", (: do_wield :));
                set("unwield_msg", CYN "$N" CYN "һ����ߣ������е�" 
                                       "�����������뽣�ʡ�\n" NOR); 
                set("stable", 100);
        }
        init_sword(140);
        setup();
}

string do_wield()
{
        object me = this_player();

        // �������ϴ�ı��̵���(biyan-dao)�߲��ܵ�������
        if (me->query_skill("biyan-dao") < 1000 && me->query_skill("poison") < 1200)
        {
                me->affect_by("ningxue_shenzhao", ([
                        "level" : 150,
                        "id"    : "wu laoda",
                        "duration" : 5 + random(5)
                ]));
        	remove_call_out("poison");
        	call_out("poison", 6, me);
                return CYN "$N" CYN "���������Х����ʱ��" 
                                       "âһ����һ������ƿջ���������$N" 
                                       CYN "�Ƽ䡣\n\n" NOR;
        } else
        if (me->query_skill("biyan-dao") < 1000 && me->query_skill("poison") > 1800)
        {
                return CYN "$N" CYN "���������Х����ʱ��" 
                                       "âһ����һ������ƿջ���������$N" 
                                       CYN "�Ƽ䡣\n\n" NOR;
        } else
        if (me->query_skill("biyan-dao") < 1000 && me->query_skill("poison") > 1200)
        {
                me->affect_by("ningxue_shenzhao", ([
                        "level" : 100,
                        "id"    : "wu laoda",
                        "duration" : 3 + random(3)
                ]));
        	remove_call_out("poison");
        	call_out("poison", 18, me);
                return CYN "$N" CYN "���������Х����ʱ��" 
                                       "âһ����һ������ƿջ���������$N" 
                                       CYN "�Ƽ䡣\n\n" NOR;
        } else
        {
                return CYN "$N" CYN "���������Х����ʱ��" 
                                       "âһ����һ������ƿջ���������$N" 
                                       CYN "�Ƽ䡣\n" NOR;
        }
}

void poison(object me)
{
        object weapon;

        if (objectp(weapon = me->query_temp("weapon"))
           && weapon->query("id") == "canyang baojian"
           && me->query_skill("poison") < 1800)
	{
	        message_vision(HIB "\n$N" HIB "���ֲ��ɵ�һ����ԭ������������"
                               "��綾�����뼡����\n" NOR, me);
                me->affect_by("ningxue_shenzhao", ([
                        "level" : 300,
                        "id"    : "wu laoda",
                        "duration" : 10 + random(10)
                ]));
	       	remove_call_out("poison");
       		call_out("poison", 12, me);
	}
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill("blade") < 150)
                return damage_bonus / 2;

        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("blade") / 10 + 2);
                return GRN "$N" GRN "��������������ն������һ������â��$n"
                       GRN "ֻ��һ�������˱Ƕ��������Ҵ��⣬��\n�����������"
                       "�мܶ�ʱɢ�ҡ�\n" NOR;
        case 1:
                n = me->query_skill("blade");
                victim->affect_by("ningxue_shenzhao", ([
                        "level" : me->query("jiali") + random(me->query("jiali")),
                        "id"    : me->query("id"),
                        "duration" : n / 70 + random(n / 30)
                ]));
                return GRN "$N" GRN "��������������ն������һ������â��$n"
                       GRN "ֻ��һ�������˱Ƕ�����΢һ���죬��\nʱ����������"
                       "������\n" NOR;
        }
        return damage_bonus;
}
