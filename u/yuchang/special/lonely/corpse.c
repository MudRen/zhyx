// corpse.c ��Ӣ�۵�ʬ��(��������������壩

inherit ITEM;

void create()
{
	set_name("���õ�ʬ��", ({ "corpse" }));
	set_weight(5000);
	set_max_encumbrance(1000000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ�߸��õ�ʬ�壬�ƺ����ﴧ��ʲô������\n");	
              set("no_sell",1);
	       set("value", 1000);
	}
}

int is_container() { return 1; }
