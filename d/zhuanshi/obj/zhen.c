
//������ (�����ξ����õĵ���)
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "������" NOR, ({ "huang liangzhen", "zhen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "��˵���������ͷ˯��(dream)���Խ����ξ���\n" NOR);
                set("unit", "��");
                set("value", 200000000);
                set("weight", 10);                
             }
        setup();
}

void init()
{
     add_action("have_dream", "dream");
}

int have_dream()
{
   object ob, me = this_player();

   if ( !environment(me)->query("sleep_room") )
   {
      write("���ﲻ��˯��������ô����ѽ��\n");
      return 1;
   }

   foreach (ob in deep_inventory(me)) 
   { 
      if (ob->is_character()) 
      {   
         write("�����ϴ��Ÿ��������ô����ѽ?\n"); 
         return 1;
      }
   }
   message_vision("\n$N��ͷ������һ�ɣ�������˯������\n\n", me);
   message_vision("˯��˯�ţ�$N�������Ȼ�����ƮƮ�ط����ˡ�\n\n", me);
   me->set_temp("dream_place", environment(me));
   me->move("/d/zhuanshi/sky/dream");
   message_vision(HIG"һ˲��$N��Ʈ�����ξ��\n\n"NOR, me);
   destruct(this_object());
   return 1;
}

int query_autoload() { return 1; }