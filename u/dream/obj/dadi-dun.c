// dadi-dun.c
// by dream

#include <armor.h>
#include <ansi.h>

inherit DUNPAI;

void create()
{
        set_name(HIR "���֮��ʯ��" NOR, ({ "dadi dun", "dun" }));
        set("long", "����һ��Զ��������������ʯ�ܣ����������������������������\n");
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "dunpai");
                set("unit", "��");
                set("armor_prop/armor", 200);
                set("wear_msg", HIR "ֻ��һ��Ѫ��Ĵ��֮��ʯ��ƾ�ճ�����$N�����ϣ�������Ȼ����������\n" NOR);
        }
        setup();
}
mixed valid_damage(object me, object victim, int damage, object weapon)
{
        string result;
        if ( weapon )
                return damage*5/6;
        else {
                damage = damage/10;
                if (damage > 0)
                    me->receive_wound("qi", damage/10, victim);
                result = HIR"ֻ��$N���һ����æ���ˣ���ϧ�ѱ����֮��ʯ����������������������Ŀ�����Ѫ��\n" NOR;
                result+= "( $N"+ COMBAT_D->eff_status_msg((int)me->query("qi")*100/(int)me->query("max_qi")) + " )\n";
                return ([ "result": result, "damage": damage+random(damage) ]);
        }
}

