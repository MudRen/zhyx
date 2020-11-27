#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "bingcan_duzhang"; }

string chinese_name() { return "���Ϻ���"; }

string update_msg_others()
{
       return HIW "$N" HIW "�Һ�һ������ɫ���࣬ȫ���ֳ�һ�㺮������ס�Ĳ�����\n" NOR;
}

string update_msg_self()
{
        return HIW "��ֻ���������ģ�ȫ�����Ҫ����һ�㡣\n" NOR;
}

string die_msg_others()
{
        return HIW "$N" HIW "����һ��Ӳ�ĵ���һ�㣬ͻȻ"
               "�䡰�顱��һ�������һ�صı��顣\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] * 1;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] * 2;
}

string die_reason()
{
        return "���Ϻ�����������������";
}


int dispel(object me, object ob, mapping cnd)
{
        if ((me->query_skill("jiuyang-shengong", 1) > 1000 && 
             me->query_skill_mapped("force") == "jiuyang-shengong") ||
             (me->query_skill("freezing-force", 1) > 200 &&
              me->query_skill_mapped("force") == "freezing-force") || 
             (me->query_skill("yijinjing", 1) > 1000 &&
              me->query_skill_mapped("force") == "yijinjing"))
        {
               me->add_temp("apply/dispel-poison", 1000);
               me->set_temp("add_dispel", 1); 
               call_out("clear_dispel", 2, me);
        }

        return ::dispel(me, ob, cnd);

}


void clear_dispel(object me)
{
       if (me->query_temp("apply/dispel-poison") && 
           me->query_temp("add_dispel"))
       {
                me->delete_temp("add_dispel");
                me->add_temp("apply/dispel-poison", -1000);
                return;
       }
               
}