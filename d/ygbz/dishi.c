// yuchang
#include <ansi.h>
inherit ROOM;
int do_zhuan(string arg);
int do_an(string arg);
void create()
{
        set("short", "����");
        set("long", @LONG
���Ǹ���Լ��ʮ���������ε��ң���������������� 
���ҶԵط���ǽ������һյ�͵ƣ�����ȥ�е�������

LONG
        );
        set("exits", ([
                      ]));
        set("no_clean_up", 0);
        setup();
}
void init()
{
        add_action("do_zhuan", "zhuan");
        add_action("do_an", "an");
}
int do_zhuan(string arg)
{
        object me;
        me = this_player();
      if( !arg || arg=="" ) return notify_fail("��Ҫתʲô����!\n");
            if( arg=="deng" ) {
             write(
           "��ת��ת�͵ƣ���Ȼ����ת��,��������԰���ȥ����!\n");
             this_player()->set_temp("tiwall", 1);
             return 1;
       }
}
int do_an(string arg)
{
        object me;
        object room; 
        me = this_player();
      if( !arg || arg=="" ) return notify_fail("��Ҫ��ʲô����!\n");
  if( arg=="deng" ) {
        if (me->query_temp("tiwall") ) {
            message("vision", me->name() + "���Ű��͵ư���һ��,
����ǽ�ڷ����ˡ����������죬������ռ���ⴥ����\n",
                    environment(me), ({me}) ); 
 message("vision","����ǽ��ͻȻ����һ�����ڣ�¶��������һ��ͨ������
�ڡ� \n",
                    environment(me), ({me}) );
           if(!( room = find_object("/d/ygbz/dishi")) )
                  room = load_object("/d/ygbz/dishi"); 
        if(objectp(room)) 
            { 
  me->move(__DIR__"changlang");
message("channel:chat", HBRED"�����ء�"+me->query("name")+"�ɹ�����������ܵ�!\n"NOR,users());
}
                            this_player()->delete_temp("tiwall");
            return 1;
        }
}
        else {
            write("���밴ʲô����?!\n");
     return 1;
        }
}
