#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
	set_name(HIW "��ս��" NOR, ({ "shenhu zhanjia", "shenhu", "zhanjia" }));
	set_weight(6000);
	if (clonep())set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIW "\nһ��Ͷ���������â��ս�ף�����ؼ�ļ�Ʒ��\n" NOR
                            HIG "��Ч�м�������+ 70        ��Ч�Ṧ������+ 10\n" NOR
                            HIG "����Ч��������+ 20%       ����Ч���ȼ��� 220\n" NOR
                            HIG "�����ر�������+ 20%\n" NOR);
		set("value", 2000000);
		set("material", "tiger");

                set("material_name", "�׻��ǡ��׻���׻�Ƥ������ͨ����");
                set("can_summon", 1);
                set("summon_id", "shenhujia");
                set("ctype", "����");
                set("summon_wear_msg", HIW "ɲ�Ǽ䣬��������ɽ����������ʴ�һ���׹�\n"
                                       "��������������$N" HIW "��Ϊһ�塣\n" NOR);
                set("summon_remove_msg", HIW "���꽥Ϣ��һֻ�׻��ڿն�����ʧ����ʡ�\n" NOR);
                set("armor_prop/armor", 350);
		set("armor_prop/dodge", 10);
                set("armor_prop/parry", 70);
                set("armor_prop/reduce_poison", 20); // ���30%����Ч��
                set("armor_prop/avoid_poison", 20); // ���20%�ر�Ч��

	}
	setup();
}

int query_autoload()
{
        return 1;
}
