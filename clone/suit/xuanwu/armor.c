//update by xiner
#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
	set_name( BLK"����"HIW"ս��"NOR, ({ "xuanwu armor","armor","jia" }) );
	set_weight(1500);
	if( clonep() )
	set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIW"һ��Ͷ���������â��ս�ס�"NOR"
��װЧ����"HIW"������װӵ����ǿ�ķ���������"NOR"\n");
		set("value", 150000);
		set("material", "feather");
		set("armor_prop/armor", 200 + random(100));
		set("armor_prop/dodge", 20 + random(50));
                set("armor_prop/parry", 20 + random(50));
		set("warm_cloth", 1);
		set("no_sell", 1 );
		set("no_steal", 1 );
	}
	setup();
}

int query_autoload()
{
	return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;

        if (random(5)==1 )
        {
		result = ([ "damage": -damage ]);               
		result += (["msg" : HIB "$N" HIB "һ�й�����$n" HIB "ŭ��һ���������ۼ׹�â��˸����Ӳ��$N" HIB "���ж�����δ�ˡ�\n" NOR]);
		return result;
        }
}