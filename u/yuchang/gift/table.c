#include <ansi.h>
#define LAST_PAR "sorry"
#define THIS_PAR "sorrysf"
inherit ITEM;
void create()
{
    set_name("�輸", ({ "table"}));
    set_weight(5000000);
    if( clonep() )
        set_default_object(__FILE__);
    else {
        set("unit", "��");
        set("no_get","����輸�Ǵ�������õģ������˼���ߣ�");
        set("long","һ��С������Ĳ輸����������˴�ҵ������ҿ�������(pick gift)����");
        set("value", 0);
        set("material", "stone");
    }
}
void init()
{
    add_action("do_pick", "pick");
}
 
int do_pick(string arg)
{
       object me,obj;
       me = this_player();
       if( !arg || arg!="gift" ) return notify_fail("��Ҫ��ʲô��\n");


       if (me->query(THIS_PAR + "_pick")) {
tell_object(me,CYN "�˷���ͻȻ������һ������֮�С�\n\n");	
tell_object(me,HIR "�������������һ�ã�ÿ��ֻ��һ�������Ŷ~��\n\n");
tell_object(me,CYN "ֻ��һ��������ᣬ�˷����Ѿ������ˡ�\n" NOR)	;
       return 1;
       }
      obj = new (__DIR__"gift");
       obj->move(me);
       message_vision("$N��ʯ��������һ���������\n",me );
//ÿ�μ���������ϴεĲ������������ӱ����õĲ����� 
       me->delete(LAST_PAR + "_pick");
       me->set(THIS_PAR + "_pick",1);
       me->start_busy(2);
       return 1;
}

