#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIW"��ӹȫ���²�"NOR, ({ "jin bookb" }) );
            set("no_put", 1);
            set("value", 0);
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
	        
            set("shenshu",1);
            set("unit", "��");
            set("no_put", 1);
            set("material", "paper");
            set("long", "һ��������ϲ��ɵľ�ᣬ�������(chayue)����������\n");
          }

    setup();
}
void init()
{
   add_action("do_cha","chayue");
}
int do_cha(string arg)
{
	object me;
	int exp,pot,score;
	me =this_player();
 	if (!id(arg))
	return notify_fail("��Ҫ��ʲô��\n");

	exp = 2100+random(1000);
	             pot = exp/3;
             score = random(200)+100;
             me->add("combat_exp",exp);
             me->add("potential",pot);
             me->add("score",score);
     	      message_vision("$N��ϸ�ز�����һ��"+this_object()->query("name")+"��\n", me);
tell_object(me,"�㱻�����ˣ�\n" +
             chinese_number(exp) + "��ʵս����\n"+
             chinese_number(pot) + "��Ǳ��\n" +
            chinese_number(score)+"�㽭������\n");
	destruct(this_object());
return 1;
}
