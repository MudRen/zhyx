// tianling huwan.c
// ���黤�� [����]
// ����װ��
// by yuchang
#include <ansi.h>
#include <armor.h>

inherit WRISTS;

void create()
{
	set_name( HIG"���黤��"NOR, ({ "tianling huwan", "huwan" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "˫");
                set("long", HIG"����һ�����ʵĻ��󣬾�Ө��͸����������"NOR"
����ָ������ʮ��
����װ����"HIC"[�������]"NOR" "HIR"����ս��"NOR" "YEL"���ƻ���"NOR" "HIG"���黤��"NOR" "HIY"�������"NOR" "HIW"���̻���"NOR"
����Ч����"HIG"��������(hand)"NOR"\n");
		set("value", 6000);
		set("material", "wrists");
		set("wear_msg", RED"$N�ó�һ˫"HIG"���黤��"RED"�������ϣ���ʱ�е�����������ǿ��\n" NOR);
		set("armor_prop/hand", 5);
		set("armor_prop/armor", 25);
	}
	setup();
}
