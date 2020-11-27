#include <room.h>
#include <ansi.h>
inherit ROOM;

void random_exit(object room);

void create()
{
        set("short", "�����");
        set("long", @LONG
����������һ�����ǽ�Ͽ�������(relievo)��
��Щ�������͸߹ţ��ֹ�ϸ�¾��ţ����̾����Ӵ���
�������ѽ⣬���Ķ���Щ�������ޡ������ʶ��㣬
�������ϵ����޾���һ��Ҳû�������������֮����
LONG);
       set("item_desc", ([       
"relievo" : "�㷢�ָ����е㰼͹��ƽ����������Ŀ��Ĳ�죬
�ػᵱ��ʯ�ƺ��Թ�ȥ,�㲻���밴��(press)����!\n",  
       ]));              
       set("exits", ([
                "west" :__DIR__"migong2",                                           
       ]));             
      setup();
} 
void init()
{  
     add_action("do_press", "press");
     add_action("do_pull", "pull"); 
     add_action("do_turn", "turn");
}

 int do_press(string arg)
{
     object me = this_player();

     if( !arg || arg != "relievo" ) 
         return notify_fail("���ǲ����밴����(press relievo)��\n");
                            
       
     message_vision(HIC"$N�Ѹ����������ﰴ��һ��!\n"NOR, me);
     add("press",1);  

    if (query("press") == 6)
    {
       message_vision(HIC"$N��ΰ��º�ͻȻ�п鸡��͹�˳���!\n\n"NOR, me);
       tell_object(me, HIW"�㲻������(pull relievo)��\n\n"NOR);       
       set("can_pull", 1);
       remove_call_out("on_del");
       call_out("on_del", 10, me);
    }

    if (query("press") > 6 )
   {
       message_vision(HIG"$N����ͷ��,���������˻�ȥ!\n"NOR, me);       
       delete("press");
       delete("can_pull");
   }
   return 1;
}

void on_del(object me)
{
    object ob = this_object();
    ob->delete("press");
    tell_room(ob, HIW"͹��ĸ���������������ȥ��\n\n"NOR);
    ob->delete("can_pull");    
}

int do_pull(string arg)
{
        object me;
        me = this_player(); 

        if(!query("can_pull")) return 0;   

        if( !arg || arg != "relievo" ) 
            return notify_fail("����Ҫ������(pull relievo)��\n");
          
        message_vision(HIB"$Nһ�ѽ���������������\n\n"NOR, me);
        tell_object(HIG"��ͻȻ���ָ����ƺ�����������ת����ת�ıߺ���? \n\n"NOR);
         
        delete("can_pull");
        set("can_turn", 1);
        return 1;      
}

int do_turn(string dir)
{
    object me; 
    object room;
    
    me = this_player();

    if ( ! query("can_turn")) return 0;

    if (!dir || dir != "right" && dir != "left") 
        return notify_fail("��Ҫ���ĸ�����ת������(right����left)��\n");
    
    if (dir == "left") 
    {
       message_vision(HIC"$N�Ѹ�������ת��һת��\n"NOR, me); 
       add("turn", 1);        
    }
    if ( dir == "right") 
   {
       message_vision(HIC"$N�Ѹ�������ת��һת��\n"NOR, me); 
       if (query("turn") > 5) 
       {          
          message_vision(HIC"$N���ת���󣬸�������ԭλ��"
                             "������ǰ˿�����졣\n"NOR, me);                        
          delete("can_turn");      
                        
          if (!objectp (room = find_object(__DIR__"migong5")))
              room = load_object(__DIR__"migong5") ;

          random_exit(room);

          message_vision("�������������һЩ���أ�$N�е�Ť�����𵴡�\n",me );

          tell_room(room, HIB"ͻȻ������־Ÿ��󶴣�"
                    "��֪���ĸ���ͨ���ܵ���\n\n"NOR);
 
          message("vision", HIW"�����㹬���š�" + me->query("name") + 
                   "�ɹ����˾��㹬�ܵ���!\n"NOR,users());
          remove_call_out("close");
          call_out("close", 180);
        }
    }
    return 1;        
}

void close()
{ 
     int i;
     object room;

     if( room = find_object(__DIR__"migong5") ) 
     {
       for(i = 1; i < 10; i++)     
          room->delete("exits/" + i);       
          tell_room(room,HIG"ͻȻ�������ǵ���������������ʧ��!\n"NOR);
     }
}

void random_exit(object room)
{  //���ﻹ�øģ���ô��ƻ��������˵ģ�������
   /*  int i;
     int *a = ({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
     int x = random(9) + 1;
     for(i = 1; i < 10;       
     room->set("exits/" + x , __DIR__"lev1/dong01");
                a -= ({x});
                
     for( i = 0; i < 8;i++)
         room->set("exits/"+a[i], "/d/city/wumiao");    */  
                        
                        //return x;//����ֵΪͨ���ܵ��������ֵ
                        return;
}

