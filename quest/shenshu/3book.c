#include <ansi.h>
inherit ITEM;
void create()
{
    set_name("���������"NOR, ({ "book" }) );
            set("no_put", 1);
            set("value", 0);
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
	        
            set("unit", "��");
            set("material", "paper");
            set("long", "һ��������ϲ��ɵľ�ᣬ�������(chayue)����������\n");
          }

    setup();
}
void init()
{
   add_action("do_cha","chayue");
}
int do_cha()
{
	object me;
	int exp,pot,score;
	me =this_player();
	exp = 1000+random(900);
	             pot = exp/6;
             score = random(120)+20;
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
