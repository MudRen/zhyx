#include <ansi.h>

inherit ITEM;

inherit F_NOCLONE;

void create()
{
	set_name( HIY "ת��֪ͨ" NOR, ({ "zhuanshi tongzhi" }));
	set_weight(100);
	set("long", NOR + HIW "����һ����ܰ��ǩ����֪ͨ�飬����д�ţ�\n\n"
		"      ��׼�����ת�����䣡��\n\n\n"
		"����֪ͨ��ȥ�ң�����BOSS�ݾͿ��Խ���ת�������ˣ�" NOR);
	set("unit", "��");
	set("value", 0);
	set("no_sell", "�ⶫ����Ҳ��Ǯ����һ��ȥ��");
	set("no_steal",1);
	set("no_put", 1);
	set("no_drop", 1);
        set("no_light", "�ⶫ����Ҳ���գ�����������"); 
	set("material", "paper");
        setup();
        check_clone();
}
