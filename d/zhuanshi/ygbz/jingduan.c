// yuchang
#include <ansi.h>
inherit ROOM;

void check_mingzhu();

void create()
{
        set("short", "�ȵ�����");
        set("long", @LONG 
�����ǵ�����(men)�����и��ֻ������������Ƕ��
�Ŀ��������������(zhu)������䲻ǿ�������������
���������,�Ų���ڹ⻬�Ļ���ʯ��(wall)�ƺ�������
ذ��һ��Ķ���Ӳ�̳�һ���֡� 
LONG); 
        set("item_desc", ([ 
          "men" : "���ȸ��ŵĸֻ��ƺ�������(pull huan)����!\n",   
          "zhu" : "ҹ�����ƺ�������(pick)����!\n", 
          "wall" : HIB"��������ɲŮ������һ�Ρ�!\n"NOR,
        ]));
        set("exits", ([
                "south" : __DIR__"langdao",
        ]));        
        setup();
}

void init()
{
    add_action("do_pick", "pick");
    add_action("do_pull", "pull");
    add_action("do_zhuan", "zhuan");
}

int do_pick(string arg)
{
        object zhu, me = this_player();
        if ( !arg || arg != "zhu" ) 
             return notify_fail("����Ҫ(pick zhu)��\n");
      
        if ( me->query("reborn_start/ygbz/mingzhu") < 4)
        {           
           message_vision(HIG"$N������һ��ҹ���顣\n"NOR, me);
           zhu = new(__DIR__"obj/zhu");
           zhu->move(me);  
           me->add("reborn_start/ygbz/mingzhu",1);
           message("vision", HBRED HIB"�����ش��š�" + me->query("name") +
                            "���������͵����һ��ҹ����!\n"NOR, users());
           check_mingzhu();
           return 1;
        } else
       return notify_fail("ҹ�����Ѿ�����������!\n");
}

void check_mingzhu()
{
    object me;
    me = this_player();

   if( me->query("reborn_start/ygbz/mingzhu") >= 4 )
   {
      message_vision(HIC"\nͻȻ$N�Ľŵ��³���һ������$N������ȥ��\n\n"NOR, me);

      message("vision", HBRED HIW"�����ش��š�" + me->query("name") + 
              "��Ϊ̫̰���ù���ҹ���飬�������߳�������!\n"NOR, users());
      me->unconcious();
      me->move("/d/changan/bei-chengmen");
   }
}

int do_pull(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg != "huan" ) return notify_fail("����Ҫ��(huan)��\n");
           
        message_vision(HIB"$Nһ�ѽ��Ż����ᣬ¶�����Ÿֻ��ĸ�����\n"NOR, me); 

        write(HIC"\n�Ż��ƺ�����������ת��������ת�ıߺ���? \n\n"NOR);
        me->set_temp("lamen", 1);
        return 1;
       
}

int do_zhuan(string dir)
{
    object me;        
    me = this_player();

    if (!me->query_temp("lamen")) 
       return 0;

    if ( !dir || dir != "left" && dir != "right") 
        return notify_fail("��Ҫ(zhuan left ���� right)��\n");
     
   if ( dir == "left" ) 
   {
       message_vision(HIC"$N���Ż�����ת��һת��\n"NOR, me); 
       add("zhuanmen", 1); 
   }

   if( dir=="right" ) 
   {
       message_vision(HIC"$N���Ż�����ת��һת��\n"NOR, me); 
       add("zhuanmen", -1); 
       if (query("zhuanmen") < -4 ) 
          set("zhuanmen", 1);
   } 

   if( query("zhuanmen") > 3  &&  !query("exits/enter") ) 
   {
        tell_room(this_object(), HIR"ֻ����������һ�������������"
                       "�������Ĵ��ˡ�\n");
        set("exits/enter", __DIR__"langdao2");
        delete("zhuanmen");
        me->delete_temp("lamen");
        remove_call_out("close");
        call_out("close", 8, this_object());
   }
   return 1;
}

void close(object room)
{
      tell_room(room, HIW"ͻȻ�������ǵ������������ֺ�����!\n"NOR);
      room->delete("exits/enter");
}
