#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "ningxue_shenzhao"; }

string chinese_name() { return "��Ѫ֮��"; }

string update_msg_others()
{
       return HIR "$N" HIR "ֻ����Ϣ���ͣ����ۡ���һ�����һ�����Ѫ��\n" NOR;
}

string update_msg_self()
{
        return HIR "��ֻ����Ϣ���ͣ�ȫ��ѪҺ�������Ŀ�ʼ����������\n" NOR;
}

string die_msg_others()
{
        return HIW "$N" HIW "ֻ��ȫ��ѪҺ˲��ֹͣ��������"
               "��ͷ���������Ľ���˱���ֱͦͦ�ĵ�����ȥ��\n" NOR;
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
        return "��Ѫ֮���������ܾ���ĥ����";
}

int dispel(object me, object ob, mapping cnd)
{
        if ((me->query_skill("xixing-dafa", 1) > 1000 && 
             me->query_skill_mapped("force") == "xixing-dafa") ||
             (me->query_skill("huagong-dafa", 1) > 1000 &&
              me->query_skill_mapped("force") == "huagong-dafa") || 
             (me->query_skill("beiming-shengong", 1) > 1000 &&
              me->query_skill_mapped("force") == "beiming-shengong"))
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
