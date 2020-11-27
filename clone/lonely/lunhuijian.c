#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIW "�ֻؽ�" NOR, ({ "lunhui jian", "lunhui", "jian" }));
        set_weight(4000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIW "������غ���ɢ���ŵ�����⡣\n" NOR);
                set("unit", "��");
                set("value", 40000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIW "һ����⻮�����ֻؽ�������$N" HIW "���С�\n" NOR);

                set("unwield_msg", HIW "���������$N" HIW "���е��ֻؽ�����Ȼ��û ��\n" NOR);
                set("stable", 100);
        }                                                                                                                    
        init_sword(100);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("sword") != "lunhui-jian" ||
            me->query_skill("lunhui-jian", 1) < 190)
                return damage_bonus / 2;

        if (random(5) == 1)
        {
               n = me->query_skill("sword");
               victim->receive_damage("qi", n * 3 / 5, me);
               victim->receive_wound("qi", n * 2 / 7, me);
               return HIW "$N" HIW "һ����ţ������ֻؽ���������ҫ��ʮ���޺������ۼ��ڽ���"
                      "һʱ���ӿ����������$n" HIW "��\n" NOR;
        }
        return damage_bonus;
}

