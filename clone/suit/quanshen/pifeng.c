// jinjin pifeng.c
// ������� [����]
// ����װ��
// by yuchang                                                                        

#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
	set_name( HIY"�������"NOR, ({ "jinjin pifeng", "pifeng" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
                set("long", HIY"����һ����˿֯�ɵ����磬��ֵ���ǡ�"NOR"
����ָ������ʮ
����װ����"HIC"[�������]"NOR" "HIR"����ս��"NOR" "YEL"���ƻ���"NOR" "HIG"���黤��"NOR" "HIY"�������"NOR" "HIW"���̻���"NOR"
����Ч����"HIG"��"NOR"\n");
		set("value", 60000);
		set("material", "silk");
		set("armor_prop/armor", 30);
		
	}
	setup();
}
