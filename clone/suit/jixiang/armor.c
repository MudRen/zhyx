// jixiang armor.c
// ����ս�� [����]
// ����װ��
// by yuchang
#include <ansi.h>
#include <armor.h>

inherit CLOTH;


void create()
{
	set_name( HIR"����ս��"NOR, ({ "longfeng zhanjia", "zhanjia" }) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIR"����һ��ͨ��͸���ս�ס��������һ��һ�"NOR"
����ָ����һ����ʮ
����Ч����"HIG"��ǿ����(parry)"NOR"\n");
		set("value", 100000);
		set("material", "cloth");
		set("wear_msg", RED"ֻ��$N����һ��"HIR"����ս��"RED"�������ϣ�һ��һ���ͼ���������ԡ�\n" NOR);
		set("armor_prop/parry", 20);
		set("armor_prop/armor", 140);		
	}
	setup();
}

