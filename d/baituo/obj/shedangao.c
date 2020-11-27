// shedangao.c

inherit ITEM;

void create()
{
	set_name("�ߵ���", ({"shedan gao", "gao"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "�������Ʒ���ߵ��ࡻ��\n");
		set("value", 100);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (me->query("eff_jing") >= me->query("max_jing"))
		return notify_fail("�����ڳԡ��ߵ��ࡻ����Ч�ã�\n");

	me->receive_curing("jing", 30);
	message_vision("$N����һ���ߵ��࣬�پ�һ�ɺƵ�����ֱӿ������"
		       "�������̺�ת��\n", me);
	destruct(this_object());
	return 1;
}
