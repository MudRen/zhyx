// jinyun huxin.c
// ���ƻ��� [����]
// ����װ��
// by keinxin@sj2 2003.2                                                                         

#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
	set_name( YEL"���ƻ���"NOR, ({ "jinyun huxin", "huxin" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
                set("long", YEL"����һ���˿֯�ɵĻ��ģ���ֵ���ǡ�"NOR"
����ָ������ʮ
����װ����"HIC"[�������]"NOR" "HIR"����ս��"NOR" "YEL"���ƻ���"NOR" "HIG"���黤��"NOR" "HIY"�������"NOR" "HIW"���̻���"NOR"
����Ч����"HIG"�ӿ쾭������(force)"NOR"\n");
		set("value", 60000);
		set("material", "gold");
		set("armor_prop/force", 5);
		set("armor_prop/armor", 30);
		
	}
	setup();
}
