


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "ͨ��֤" NOR, ({ "tongxing zheng","zheng" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\n����һ�Ž�Ƶ����ƣ�����д�š�ͨ��֤�����֣�ƾ�����ƿ��Գ�����ũ����\n" NOR);
                set("unit", "��");
                set("value", 50000000);
                set("no_sell", 1);
                set("no_steal",1);
                set("no_put", 1); 
                set("no_drop", 1);
                set("weight", 10);
                set("no_light", "�ⶫ����Ҳ���գ�С�ĳ���Ŷ��"); 
                set("material", "paper");                 
             }
        setup();
}
      void init() 
      { 
              if( this_player() == environment() ) 
              { 
                      remove_call_out("destroy");  
                      call_out("destroy", 300);  
              } 
      } 
      int destroy()  
      {  
          tell_room(environment(this_object()),   
                     "ͻȻ�䣬�����һ������������е�ͨ��֤���˸�����!\n");  
          destruct(this_object());  
          return 1;  
      } 