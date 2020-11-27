// sp.c

#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
      me->affect_by("ss_poison",  
          ([ "level" : 400, "id"    : "rcwiz", "duration" : 60 ]));

      me->affect_by("poison",  
          ([ "level" : 400, "id"    : "rcwiz", "duration" : 60 ]));

      me->affect_by("fire_poison",  
          ([ "level" : 400, "id"    : "rcwiz", "duration" : 60 ]));

      me->affect_by("xuanming_poison",  
          ([ "level" : 400, "id"    : "rcwiz", "duration" : 60 ]));

      return 1;
}

int help (object me)
{
        write(@HELP
ָ���ʽ: sp <class> <info>

��Ȩ������վ��ĳЩ�����ʹ��Ȩ�ޡ�info ���Ϊ�ջ��� clear ��
��ʾȡ�������ʹ��Ȩ�ޡ�
HELP );
        return 1;
}
