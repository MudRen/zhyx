// quanshen armor.c
// ȭ��ս�� [ȭ��]
// ����װ��
// by yuchang
#include <ansi.h>
#include <armor.h>

inherit CLOTH;


void create()
{
	set_name( HIG"ȭ��ս��"NOR, ({ "quanshen zhanjia", "zhanjia" }) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIR"����һ��ͨ��͸���ս�ס��������һ��һ�"NOR"
����ָ����һ����ʮ
����װ����"HIG"[ȭ��װ��]"NOR" "HIG"ȭ��ս��"NOR" "YEL"���ƻ���"NOR" "HIG"���黤��"NOR" "HIY"�������"NOR" "HIW"���̻���"NOR"
����Ч����"HIG"��ǿ����(parry)"NOR"\n");
		set("value", 100000);
		set("material", "cloth");
		set("wear_msg", RED"ֻ��$N����һ��"HIR"����ս��"RED"�������ϣ�һ��һ���ͼ���������ԡ�\n" NOR);
		set("armor_prop/parry", 6);
		set("armor_prop/armor", 140);
		set("power",10);
	}
	setup();
}

