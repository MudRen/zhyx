#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
	set_name(NOR + MAG "�����ۼ�" NOR, ({ "zijiao linjia", "zijiao", "linjia" }));
	set_weight(9000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", NOR + MAG "\nһ�������������������ۼף�ɢ�����������ǵĺ�â��\n" NOR
                            HIC "��Ч�м�������+ 50        ��Ч�Ṧ������+ 30\n" NOR
                            HIC "����Ч��������+ 30%       ����Ч���ȼ��� 200\n" NOR
                            HIC "�����ر�������+ 15%\n" NOR);

		set("material", "dragon");
                set("material_name", "�����롢����Ƥ����Խ����ѪȪ");
                set("can_summon", 1);
                set("summon_id", "zijiaojia");
                set("ctype", "����");
                set("summon_wear_msg", NOR + MAG "ɲ�Ǽ䣬��ر�ɫ������������������ʢ���������ܡ�\n"
                                       "ת�ۼ䣬������������һ����������$N" NOR + MAG "��Ϊһ�塣\n" NOR);
                set("summon_remove_msg", NOR + MAG "������Ϣ��������ɢ����ػָ���ƽ����\n" NOR);

		set("value", 3000000);
                set("armor_prop/armor", 200);
		set("armor_prop/dodge", 30);
                set("armor_prop/parry", 50);
                set("armor_prop/reduce_poison", 30);
                set("armor_prop/avoid_poison", 15);
                set("avoid_msg", NOR + MAG "һ����â�����������ۼ׽�����ȫ�����ա�\n" NOR);
                set("reduce_msg", HIR "һ����â�����������ۼ������˲��ֶ��ʡ�" NOR);
	}
	setup();
}

int query_autoload()
{
        return 1;
}