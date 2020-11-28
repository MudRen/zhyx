// yuan.c ��Ԫ��

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "��Ԫ��" NOR; }

int perform(object me, string skill)
{
        mapping my;

        if (time() - me->query("special/yuan") < 86400)
                return notify_fail("��Ԫ��һ��ֻ��ʩչһ�Σ�\n");

        message_vision(HIC "$N" HIC "ʩչ����Ԫ�󷨣�����ͻ���澭�������ָ�����״̬��\n" NOR, me);
       
        me->set("special/yuan", time());
        
        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"];
        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
        my["qi"]     = my["eff_qi"]     = my["max_qi"];
        my["neili"]  = my["max_neili"] * 2;
        my["food"]   = me->max_food_capacity();
        my["water"]  = me->max_water_capacity();

        me->clear_condition();

        me->save();

        return 1;
}


