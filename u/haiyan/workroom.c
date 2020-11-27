// workroom.c 
// Modified by Haiyan 

#include <ansi.h>
#include <room.h> 
inherit ROOM; 

void create() 
{ 
   set("short", "����"); 
   set("long", @LONG
�����������ͱ��ϵ�һ��ɽ������������ӿ�Ĵ󺣡���̫ƽ��
��ʱ����һ��С����ܳ�ˮ�棬����һ˫���۾������������������
һ������(desk)�����������ӡ�������һյ̨�ƣ����������棬һ��
�����ƾɲ����ıʼǱ��� 
LONG); 
   set("exits", ([ 
           "out"      : "/u/smallfish/workroom",  
           "down"     : "/d/wizard/guest_room", 
      ])); 
   set("objects", ([  
       __DIR__"mishu" : 1,  
      ]));  
//   set("no_fight", 1); 
   set("no_steal", 1); 
   set("no_sleep_room", 1); 
   set("item_desc", ([  
       "desk": "���������ƺ������ƿ�(move)��\n",  
      ]));  
   setup(); 
} 

void init()  
{ 
     add_action("do_move", "move");  
     add_action("do_jingao","jg");
}  
      
void close_path()  
{  
     if (! query("exits/enter")) return;  
     message("vision","�������Զ����˻�������ס��ͨ����\n",  
             this_object());  
             delete("exits/enter");  
}  

int do_move(string arg)  
{  
    if (! arg || arg != "desk" )
       return notify_fail("��Ҫ�ƿ�ʲô��\n");  
    else  
    {  
       write("��������ƿ���¶����һ��ͨ����\n");  
       if (! query("exits/enter"))  
       {  
          set("exits/enter", __DIR__ "hy_houyuan");  
          call_out("close_path", 5);  
       }
       return 1;
    }
}

int valid_leave(object ob, string dir) 
{
    ob = this_player();
    switch(dir)
    {
      case "out":
        if (!wizardp(ob))
           return  notify_fail("������ס������������Ǵ󺣣���������������\n");
           return ::valid_leave(ob,dir);
           break;
      case "enter":
        if ((string)ob->query("id") != "haiyan") 
        { 
          if (! ob->query_temp("desk_open") && dir == "enter")  
             return notify_fail("������ס������������Ǻ�������ң���Ҫ�ҹ䣡\n");
          else 
          { 
             ob->delete_temp("desk_open"); 
             return ::valid_leave(ob, dir);  
          } 
        } 
        else  return ::valid_leave(ob, dir);
        break;
      default:
        return ::valid_leave(ob, dir); 
        break;
     }
}

int do_jingao(string arg)
{
     object ob, me = this_player();
     if (wizardp(me))
     {
         if (! arg)   return notify_fail("��Ҫ����˭��\n"); 
         ob = find_player(arg); 
         if (! ob)    return notify_fail("û�������ҡ�\n"); 
         if (ob == me)   return notify_fail("����... �����Ƿ��ˣ�\n"); 

         message("vision", HIR "�����ؾ��桿" + ob->name() + "(" + ob->query("id") + ")" + 
                 "��������Υ����RULES�������Ծ��档�����ٷ����������ʮ�˲������\n" NOR, 
                 all_interactive()); 
     }
     else   tell_object(me, "����Ȩʹ��������\n");
     return 1;
}

