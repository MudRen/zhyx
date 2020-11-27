// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <armor.h>
#include <ansi.h>
inherit CLOTH;
inherit F_UNIQUE; 

void create()
{
        set_name(YEL"��⬼�"NOR, ({ "ruanwei jia", "jia" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG"����һ��������ļ��£�����ȥ���Ἣ����ȴ�������̣��������������һ�����֮����⬼ס�\n"NOR);
                set("material", "steel");
                set("unit", "��");
                set("value", 7000000);
                set("rigidity", 20000); 
                set("replica_ob", "/clone/cloth/ruanjia"); 
                set("wear_msg", HIY "$N����һ����⬼ס�\n" NOR);
                set("unequip_msg", HIY "$N����⬼�����������\n" NOR);
                set("armor_prop/armor", 260);
                set("armor_prop/armor_vs_force", 200);
        }
        setup();
}

mixed valid_damage(object me, object victim, int damage, object weapon)
{
        string result;
        if ( weapon )
                return damage*2/3;
        else {
                damage = damage/2;
                if (damage > 0)
                    me->receive_wound("qi", damage/4, victim);
                result = "ֻ��$N���һ����æ���֣������ѱ���⬼״̵���Ѫ���졣\n";
                result+= "( $N"+ COMBAT_D->eff_status_msg((int)me->query("qi")*100/(int)me->query("max_qi")) + " )\n";
                return ([ "result": result, "damage": damage+random(damage) ]);
        }
}
                

