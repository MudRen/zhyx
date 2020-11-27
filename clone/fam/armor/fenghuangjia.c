#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
	set_name(HIR "�������" NOR, ({ "fenghuang pifeng", "fenghuang", "pifeng" }));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIR"\nһ���÷����ë֯�ɵ����磬��ϡ���䡣\n" NOR
                            HIC "��Ч�м�������+ 20        ��Ч�Ṧ������+ 30\n" NOR
                            HIC "����Ч��������+ 15%       ����Ч���ȼ���  70\n" NOR
                            HIC "�����ر�������+ 15%\n" NOR);

		set("material", "phoenix");
                set("material_name", "��ȸ��ë����ȸ֮�ǡ���ȸ����������");
                set("can_summon", 1);
                set("summon_id", "fenghuangjia");
                set("ctype", "����");
                set("summon_wear_msg", HIR "ɲ�Ǽ䣬һ�ɻ���ӵ������������ֱ����ʣ�\n"
                                       "ת�ۼ䣬���潥������һֻ���ˣ���$N" HIR "��Ϊһ�塣\n" NOR);
                set("summon_remove_msg", HIR "ֻ����һ����˻��һֻ�޴�Ļ�����ʧ����ʡ�\n" NOR);

		set("value", 4500000);
                set("armor_prop/armor", 50);
		set("armor_prop/dodge", 30);
                set("armor_prop/parry", 20);
                set("armor_prop/reduce_poison", 15);
                set("armor_prop/avoid_poison", 15);
	}
	setup();
}

int query_autoload()
{
        return 1;
}