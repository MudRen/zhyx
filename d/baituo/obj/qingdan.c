// qingdan.c
// more work needed to use this object to make poison

inherit ITEM;

void create()
{
	set_name("���ߵ�", ({ "qing dan", "qing" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
        	set("unit", "ֻ");
		set("long", "����һֻ��ӨӨ�����ߵ������Ʊ����ߵ��ࡻ"
			    "��ԭ�ϡ�\n");
		set("value", 100);
		set("only_do_effect", 1);
	}
	setup();
} 

int do_effect(object me)
{
        return notify_fail("����������\n");
}

