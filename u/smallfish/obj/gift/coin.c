// coin.c

#include <weapon.h>
#include <ansi.h>

inherit MONEY;
inherit F_EQUIP;

void create()
{
        set_name(HIY "ͭ��" NOR, ({"coin", "coins", "coin_money" }));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("money_id", "coin");
                set("long", "������ͨ�е�λ��С�Ļ��ң�ԼҪһ�ٸ�ͭ���ֵ��һ�����ӡ�\n");
                set("unit", "��");
                set("base_value", 1);
                set("base_unit", "��");
                set("base_weight", 30);

                set("weapon_prop/damage", 10);
                set("flag", 2);
                set("wield_msg", "$N�����ȡ��һ��$n�����ף��������С�\n");
                set("unwield_msg", "$N�����е�$n�Żض��\n");
                set("skill_type", "throwing");
                if( !query("actions") ) {
                    set("actions", (: call_other,WEAPON_D, "query_action" :));
                    set("verbs", ({ "throw" }) );
                }
        }
        set_amount(1);
}


