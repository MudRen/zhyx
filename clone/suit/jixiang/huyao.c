// huyao.c

#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
	set_name( HIW"���̻���"NOR, ({ "yunpan huyao", "huyao" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
                set("long", HIW"����һ�����ߺͲ�˿֯�ɵĻ�������״ǡ��һƬ���ơ�"NOR"
����ָ������ʮ
����װ����"HIC"[�������]"NOR" "HIR"����ս��"NOR" "YEL"���ƻ���"NOR" "HIG"���黤��"NOR" "HIY"�������"NOR" "HIW"���̻���"NOR"
����Ч����"HIG"��"NOR"\n");           
		set("value", 6000);
		set("material", "waist");
		set("armor_prop/armor", 20);
		set("shaolin",1);
	}
	setup();
}
