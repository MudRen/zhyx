// wangyuyan 2002.4.29
#include <ansi.h>
inherit ITEM;
void create()
{
    set_name( HIG "������" NOR, ({ "bingqipu" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("material", "paper");
            set("long", "���ظ��ֱ�����һ�����飬������������ķ���Ҳ̫���ˣ���Ĳ��󻰡�\n");
          }
    setup();
}
/*
void init()
{

if(environment()==this_player())
add_action("do_open","open");
}
int do_open(string arg)
{
object gold;
if(arg != "bingqipu" && arg != "������") return 0;
if(query("opened"))
return notify_fail("����С�����ȡ���һ���������棬�������ǿյģ�\n");
gold = new("/questobj/obj/paper");
gold->set_amount(1);
gold->move(this_player());
set("opened",1);
return notify_fail("����С�����ȡ���һ���������棬�������ó�һ��ֽ��\n");
}
*/