// longsword.c ����
#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIW"С����"HIY"ħ��"NOR, ({ "boss sword", "sword", "jian" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "�����Ϲ�����֮�ף�ӵ�����������������˵"
                                "ӵ�д˽��߿ɳ۳��ˡ�ħ�������磬�Ʋ��ɵ���\n"
                                 NOR);
                set("value", 200);
                set("material", "steel");
                 set("wield_msg", HIY "$N" HIY "һ���������������������£�ӵ��һ��������\n"
                                 "�����񽣣�ɲ�Ǽ�˽�����һ�����ǻ���������$N" HIY "���С�\n" NOR);                               
                set("unwield_msg", HIY "$N" HIY "����һת�����ѹ��ʡ�\n" NOR);
               
               
        }
        init_sword(1000);
        setup();
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;
        
        switch (random(3))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(20 + random(20));
                return HIY "$N" HIY "���������е�ħ��������ʹ����ж�����ֱ�Ƶ�"
                           "$n" HIY "�������ˡ�\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return HIR "$N" HIR "��ת����ħ������Ȼ�䣬������⻮��$n" HIR "��$n" HIR
                           "������䣬ȴ���н���\n" NOR;

        }
        return damage_bonus;
}