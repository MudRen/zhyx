// havedream.c ת��������ξ���ָ��
#include <ansi.h>
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me)
{
   object ob;
   if ( !me->query("reborn")) return 0;

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
   return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : havedream
 
����İ���Үʶ���򿪺����ָ�����������ʱ�����ξ���
Ҫ���ξ������Ļ���������(wake)ָ�
 
HELP );
        return 1;
}
