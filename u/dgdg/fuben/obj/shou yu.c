


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "����" NOR, ({ "shou yu","shou","yu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\n����һ����ʦ���ͣ�����д�š�׼����족���֣�ƾ�����Ϳ��Գ���Զ�������ҡ�\n" NOR);
                set("unit", "��");
                set("value", 1);
                set("no_sell", 1);
                set("no_steal",1);
                set("no_put", 1); 
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
                     "�����е����������Ļ��ɻұ�һ��紵����!\n");  
          destruct(this_object());  
          return 1;  
      } 