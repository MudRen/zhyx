#include <ansi.h>

inherit ITEM;

inherit F_NOCLONE;

void create()
{
	set_name( HIW "��Ʊ" NOR, ({ "men piao" }));
	set_weight(100);
	set("long", NOR + HIW "����һ����ܰ��ǩ���ı�����Ʊ������д�ţ�\n\n"
		"      ��׼�����ת�����䣡��\n\n\n"
		"��֪ͨ�齻���۹�ƽ�ӣݾͿ��Խ��б����ˣ�" NOR);
	set("unit", "��");
	set("value", 0);
	set("no_sell", "�ⶫ����Ҳ��Ǯ����һ��ȥ��");
	set("material", "paper");
        setup();
//        check_clone();
}
