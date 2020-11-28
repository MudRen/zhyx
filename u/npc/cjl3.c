// by yuchang
inherit ROOM;
#include <ansi.h>
#include <room.h>
int do_press(string arg);
void init();


void create()
{
      set("short", "�ؽ�®");
      set("long",
"[1;32m������ǰ���ɽׯ�Ĳؽ�®\n"
"�ڳ��м���һ��޴�ĺ�ľ��������(shelf)\n"
);
   set("exits",([
           "south" : __DIR__"square",
]));


  set("item_desc", ([
     "shelf" : "����һֻ�������ľ���ƣ���������佣�ļ���,�ƺ������ó���(take sword)��\n",

  ]));
  set("aocangtian", 1);

  setup();
}

void init()
{
        add_action("do_press", "press");
      add_action("do_take", "take");
      add_action("do_quit","kill");
      add_action("do_steal","steal");
}
int do_press(string arg)
{
    string p;
            object me,obj;
             object ob;
             me = this_player();
              ob = this_object();
    p = sprintf("%d", this_player()->query("_passwd")); 
    if( !arg || arg == "" )
    {
        write("��Ϲ����\n");
        return 1;
    }
    if( arg == p )
    {
        message_vision("ֻ����һ��¡¡��������Զ������\n", this_player());
        message_vision("��¯�������˿�����¶��һ������һ�ѱ�������������ǰ��\n", this_player());
            obj = new ("/d/zhuanshi/obj/jiushi");
            obj->move(me);
             return 1;
      }
    else
    {
            message_vision("$Nһ���Ұ���ͻȻʯ��ķ�϶�����һ֧��������\n", this_player());
            this_player()->die();
            return 1;
        }
}

int do_steal(string arg)
{
        write(this_player()->query("name")+"����ҪΪ�˲���֮�£�\n");
        return 1;
}

int do_take(string arg)
{
       object me,obj;
        object ob;
       me = this_player();

        ob = this_object();
       if( !arg || arg!="sword" ) return notify_fail("��Ҫ��ʲô��\n");
          if (me->query("najian")) {
       tell_object(me,CYN "�˷��Ƶ���ӰͻȻ������һ������֮�С�\n\n");
       tell_object(me,HIR "�˷���һ�������������ϣ�С���ѣ���Ҫ�Ҷ���\n\n");
       tell_object(me,CYN "ֻ��һ��������ᣬ�˷��Ƶ���Ӱ�Ѿ������ˡ�\n" NOR);
       return 1;

}
      obj = new ("/d/ajszhuang/npc/obj/ling");
       obj->move(me);

       // mark the owner who take it
       obj->set("owner", me->query("id"));

       message_vision(HIC"$N�����ô���һ���������Ȼ��100��ѱ�������������һ���أ�\n"
             "ͻȻ��������ž����һ����ʲô���������㻳�\n" NOR, this_player());
       me->delete("najian");
       me->set("najian",1);
       me->start_busy(2);
       return 1;
}



