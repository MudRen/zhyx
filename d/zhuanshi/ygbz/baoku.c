//  /2002/3/15/yuchang
#include <ansi.h>  
inherit ROOM;
void create()
{
        set("short", "С����");
        set("long", @LONG  
����һ���������ܷ���ң��Ҷ��ĽǾ���ͨ���ڣ����� 
ƽ�ŷ��ù�ʮ�������װ�������챦������(xiang),��ǽ��
��ʮ�������ܣ��������֣�����������ֻ����ͨ��ɫ����ȫ
�������ⷢù����ȥ����Ҳû����Ҫ��
LONG); 
        set("item_desc", ([ 
          "xiang" : "����������н�Ʊ����Ҫ��(na)������?\n",      
        ]));
        set("exits", ([
                "out" : __DIR__"langdao6",
        ]));
        setup();
}
void init()
{
      add_action("do_na", "na"); 
      add_action("do_fan", "fan"); 
}

void check_tishi()
{
    object room;
    message("vision", HIR"$N���ý�Ʊ��ʱ��ͻȻ������׵İ��ƺ����Է�!��\n",
            this_object() );
}

int do_na(string arg)
{
        int i;
        object tg, me = this_player();

        if ( !arg || arg != "cash" ) 
           return notify_fail("��������������Ľ�Ʊ(cash)��?\n");

      
        if ( me->query("reborn_start/ygbz/cash") )
        { 
            message_vision("$N����ȥ��������Ľ�Ʊ��"
                           "��������Ѿ������ù���\n", me);       
            return 1;
        }
 
       message_vision(HIY"$N������������һ����Ʊ�ŵ�����!\n"NOR, me);
       for( i = 0; i < 5; i++ )
       {
          tg = new("/clone/money/cash");
          tg->move(me);
       }   
       me->set("reborn_start/ygbz/cash", 1);

       message("vision", HBRED HIW"�����ش��š�" + me->query("name") +
                "���������͵����һ����Ʊ!\n"NOR,users()); 

       tell_object(me, BLINK HIB"\n�����ý�Ʊ��ʱ��"
                       "ͻȻ������׵İ��ƺ����Է�(fan)!��\n\n"NOR);

       return 1;       
}

int do_fan(string arg)
{
    object me; 
      
    me = this_player();
    if( !arg || arg != "xiang" ) 
        return notify_fail("����Ҫ��(xiang)��\n");

   message_vision(HIY"$N����׵ĸ���һ��������������������һ�����!��\n"NOR, me);
  
   set("exits/down", __DIR__"baoku2");
   call_out("close", 5);
   return 1;
}
        
void close()
{
     tell_room(this_object(), HIG"ͻȻ�������ǵ�����������ֺ�����!\n"NOR);
     delete("exits/down");
}

