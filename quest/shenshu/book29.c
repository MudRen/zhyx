#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIR"��������"NOR, ({ "jqcjiang" }) );
    set_weight(1);
            set("no_put", 1);
            set("value", 0);
    if( clonep() )
            set_default_object(__FILE__);
    else {
	       
            set("no_put", 1);
            set("value", 0);
            set("unit", "��");
            set("material", "paper");
            set("long", "����֮һ,����������������ܣ�Ӣ�ۺú�����ɽ�续����(hebing)��\n");
          }

    setup();
}
void init()
{
    add_action("do_hebing","hebing");
}
int do_hebing()
{
	object me,newbook,ob;
	me = this_player();
	newbook =new(__DIR__"shang");
 //if (!present("lghjie", me)
 //||!present("heros",me)
 //||!present("jsruhua",me))
    if (!(ob = present("lghjie", me)) ||
        !(ob = present("heros", me)) ||
        !(ob = present("jsruhua", me)))	
        tell_object(me,"�����û��.\n");
  else{ 
        if( ob->query("ownmake"))
	return notify_fail("�������мٻ��ɡ�\n");
        if(userp(ob))
	return notify_fail("�������мٻ��ɡ�\n");
        if( ob->is_character() || ob->is_corpse() )
	return notify_fail("�������мٻ��ɡ�\n");

    if(!ob->query("dynamic_quest"))
	return notify_fail("�������мٻ��ɡ�\n");

      message_vision("$N�Ѵӻ��з������������,Ӣ�ۺú�����ɽ�续,�����еĽ��������ϲ�����һ����\n", me);
	newbook->move(me);
	destruct(present("lghjie",me));
	destruct(present("heros",me));
	destruct(present("jsruhua",me));
	destruct(this_object());}
return 1;
}
