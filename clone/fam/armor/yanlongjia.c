#include <ansi.h>
#include <armor.h>

inherit ARMOR;

// �����Ʒ��ͨ���������ɱ������npc����
// ����2�� + ����10�� + ����2�� + ����1�� + ����֮ͫ2�� = �����}��

void create()
{
	set_name(HIY "�����}��" NOR, ({ "yanlong shengjia", "yanlong", "shengjia" }));
	set_weight(6000);
	if (clonep())set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIY "\nһ�������������������}�ף�ɢ��������Ĺ�â��\n" NOR
                            HIG "��Ч�м�������+ 50        ��Ч�Ṧ������+ 30\n" NOR
                            HIG "����Ч��������+ 25%       ����Ч���ȼ��� 180\n" NOR
                            HIG "�����ر�������+ 20%\n" NOR);
		set("value", 2000000);
		set("material", "dragon");

                set("material_name", "���롢���ۡ����ǡ��������֮ͫ");
                set("can_summon", 1);
                set("summon_id", "yanlongjia");
                set("ctype", "����");
                set("summon_wear_msg", HIY "ɲ�Ǽ䣬��պ���������������һ�������ڿն�����\n"
                                "�����ػ�Ϊһ�����̣���$N" HIY 
                                "��Ϊһ�塣\n" NOR);
                set("summon_remove_msg", HIY "���꽥Ϣ��һ�������ۿն�����ʧ����ʡ�\n" NOR);
                set("armor_prop/armor", 180);
		set("armor_prop/dodge", 30);
                set("armor_prop/parry", 50);
                set("armor_prop/reduce_poison", 25); // ���30%����Ч��
                set("armor_prop/avoid_poison", 20); // ���20%�ر�Ч��
                set("avoid_msg", HIG "ɲ�Ǽ䣬" HIY "�����}��" HIG "ɢ����"
                                             "һ������Ĺ�â��������ȫ�����ա�\n" NOR);
                set("reduce_msg", HIR "ɲ�Ǽ䣬" HIY "�����}��" HIR "ɢ����"
                                             "һ������Ĺ�â�������˲��ֶ��ʡ�\n" NOR);

	}
	setup();
}

int query_autoload()
{
        return 1;
}
