// bishou.c ذ��

#include <weapon.h>
#include <ansi.h>

inherit SWORD;
inherit F_NOCLONE;

void create()
{
	set_name(HIR "ذ��" NOR, ({ "bishou","bi shou" }));
	set_weight(3000);
	set("unit", "��");
	set("long", "ϸ����ذ�ף�������ī���ް�����\n");
	set("value", 50000);
        set("no_sell", 1);
	set("material", "steel");
	set("wield_msg", "$N��ৡ���һ�����һ��$n�������У�ֻ��һ�ɺ������������\n");
	set("unwield_msg", "$N�����е�$n��ؽ��ʣ�ֻ���͵�һ�����졣\n");
	init_sword(110);
	setup();
        set("startroom", "/d/city2/aobai9");
        check_clone();
}
