// yuchang
#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "�ص��ն�");
        set("long", @LONG 
��������ʯ���ɵ��ص��������ɶ��칤�����겻֪
���ö�����������!�����һʯͻ��,�ƺ����԰�(an)
һ��!
LONG);
        set("exits", ([
                "north" : __DIR__"tongdao4",
        ]));        
        setup();
}

void init()
{
        add_action("do_an", "an");
}

int do_an(string dir)
{
    object me; 
    object room;       

    me = this_player();

    if ( !dir || dir != "right" && dir != "left")
    { 
       if ( me->query_temp("tongguo" ))      
          return notify_fail(HIM"��Ҫ(an right)����(an left)?\n");
       else
          return notify_fail(HIM"����Ҫ(an right)��?\n");
    }


   if( dir == "right" ) 
   {
      message_vision("$N�������ұ�ʯ�ڵ��Ǹ���ť��\n", me);
      if (me->query_temp("tongguo"))
      {
            message_vision("�����������ҷ�һ�ڰ���ȥ���ֳ�һ������!\n", me);
            me->delete_temp("tongguo");
            set("exits/enter", __DIR__"langdao");
            remove_call_out("close");
            call_out("close", 5);   
            return 1;        
       } else      
       return 0;
  }
  if( dir == "left" ) 
  {
      message_vision(HIW"\n$N��͹����赵���ť�����°�,"
                     "�������������졣\n\n"NOR, me);
      message_vision(HIW"\n$N����һ��ͨ����Ȼ�ƶ�������"
                     "���������»��С�\n\n"NOR, me);

      remove_call_out("on_wang"); 
      call_out("on_wang", 1, me);
      return 1;
  }
}

void on_wang(object me)
{
    object room; 
    
    message_vision(HIB"$N�Ľ��������ӣ����䡹��һ�����ͨ���ڸ������ʮ���ᣬ"
             "\n��֪ײ������ط������ɷֹ��\n"NOR, me);
    message_vision(HIB"��ȴû��ͨ��ɷͣ�ĺ��˵���"
             "��ǿ�͵ĳ���ײ����ãã�ڰ�����һ�ռ䣬\n"NOR, me);
    message_vision(HIB"����������µ�������������"
             "�ֱ�һͷ�Խ�һ����������Ķ����ڡ�\n\n"NOR, me);

    me->move(__DIR__"wang");

    remove_call_out("on_wang2"); 
    call_out("on_wang2", 1, me);
}

        
void on_wang2(object me)
{
    tell_object(me, HIR"�������ٵ��£������������飬��ͷת��"
                        "��֪�˼������\n"NOR);
    tell_object(me, HIR"���ج����δ��ᣬ���Ӻ����¶飬"
             "���������ᣬ����������������գ�\n"NOR);
    tell_object(me, HIR"��������һ�̣��պð���������ʵ����������\n\n"NOR);
    me->unconcious();
}

void close()
{
      message_vision(HIG"ͻȻ�������ǵ�������ǽ���ֺ�����!\n\m"NOR,
                     this_object());
      delete("exits/enter");
}
