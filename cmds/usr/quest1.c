#include <ansi.h>
inherit F_CLEAN_UP;
int time_period(int timep, object me);
int main(object me, string arg)
{
        int mark;
        mapping quest;
        string *site;

        site=({"��������","��������","��ȸ����","�׻�����"});
        if(!(quest =  me->query("guo_shoucheng")))
        return notify_fail(
               HIW"�㲢û�������κο�����������һ����\n"NOR);

        mark = me->query_temp("guo_shoucheng/mark_shadi");

        if( mark && mark < 5 )
             write(HIW"\n�����ڵ�������ȥЭ��"HIR+site[mark-1]
                     +HIW"���ξ���������������֣�\n"NOR);
         
        else
          if( me->query_temp("guo_shoucheng/mark_jianlou") )
             write(HIW"\n�����ڵ�������ȥЭ����������"HIR"���Ǽ�¥"
                    +HIW"���ξ������ξѻ���������ֵ�����\n"NOR);
        else
             write(
HIW"\n===============================================================\n"NOR
+HIR"            ��ĿǰΪֹ����ͨ���������񹲻���ˣ�\n"NOR
+HIW+chinese_number(quest["reward_exp"])+NOR
+HIR"��ʵս�����"NOR+HIW+chinese_number(quest["reward_potential"])+NOR
+HIR"��Ǳ�ܽ�����\n"NOR
+HIR"            ���Ѿ���������"HIY
+chinese_number(quest["reward"])+HIR"�ߣ�\n"NOR+
HIW"===============================================================\n"NOR);

       return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : quest5  ���ָ�������ʾ�����Ѿ�����������������
HELP
        );
        return 1;
}

