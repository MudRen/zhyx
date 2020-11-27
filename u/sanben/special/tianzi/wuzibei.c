// ���ֱ�
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIY "���ֱ�" NOR, ({ "wuzi bei", "bei" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "ʯ���������һ�֣����Ǿ�˵�������ӿ��Դ����汮��\n"
                            "(mianbi)��һ�ż�Ϊ�����Ľ�����\n" NOR);
                set("unit", "��");               
                set("no_sell",1);
                set("weight", 10000);
                set("no_get",1);                
             }
        setup();
}

void init()
{
        add_action("do_mianbi", "mianbi");
        add_action("do_canwu", "canwu");
}

int do_mianbi()
{
        object me;
        int s_skill,t_skill;

        me = this_player();

        if ( ! me->query("special_skill/emperor") )
        return 0;
        write(HIW"ֻ�����ֱ�������ԼԼ�ֳ�һЩ���轣����Ӱ��\n"NOR);    

        s_skill = (int)me->query_skill("sword", 1);
        t_skill = (int)me->query_skill("tianzi-jian", 1);

        if (s_skill < t_skill)
        {
                message_vision("$N�Ի����������˽�̫�ͣ���"
                               "���������ֱ��ϵ����ݡ�\n", me);
                return 1; 
        }

        if (me->query("jing")< 90)
        {
                message_vision("$N̫���ˣ������޷��������ֱ��ϵ����ݡ�\n",me);
                return 1; 
        }

        if (t_skill >= 180)
        {
                message_vision("$N�������ֱ��ϵ�����̫��ǳ�ˡ�\n", me);
                return 1;
        }

        message_vision("$N��������ֱ�������˼�����ã�������"
                       "������������\n", me);
        me->improve_skill("tianzi-jian", 1 + random(me->query("int")));
        me->receive_damage("jing", 75);
        return 1;
}

int do_canwu(string arg)
{
    object me = this_player();
    

    if ( ! me->query("special_skill/emperor") )
        return 0;    
  
    if (me->is_busy())
          return notify_fail("��������æ���ء�\n");

    if (me->is_fighting())
          return notify_fail("�㻹���ȴ������˵�ɣ�\n");

    if ( ! arg || ( arg != "���ӽ���" && arg != "��������"
         && arg != "���޳���") )
          return notify_fail("��Ҫ���ʲô���У���ʽΪ(canwu ����)��\n");

    if ( arg == "���ӽ���" 
        && me->query("can_perform/tianzi-jian/jiangshi"))
          return notify_fail("�����㲻���Ѿ�������\n");

    if ( arg == "���޳���" 
        && me->query("can_perform/tianzi-jian/jiuzhou"))
          return notify_fail("�����㲻���Ѿ�������\n");
  
    if ( arg == "��������" 
        && me->query("can_perform/tianzi-jian/junlin"))
          return notify_fail("�����㲻���Ѿ�������\n");

    if ((int)me->query("jing") < 100)
          return notify_fail("��ľ����޷����У��޷������У�\n");
 
    me->receive_damage("jing", 90);

    me->start_busy(2 + random(4));

    if (random(5) == 1 && arg == "���ӽ���" )
    {
        me->add("tianzi-jian/jiangshi/count", 1);

        if (me->query("tianzi-jian/jiangshi/count") >= 10)
        {
            write(HIM "��Ȼ�䣬�����л�Ȼ��ͨ���������ǡ�\n" NOR);
            write(HIC "������ͨ���˾�ѧ�����ӽ�������\n" NOR);

            me->set("can_perform/tianzi-jian/jiangshi", 1);
            me->delete("tianzi-jian/jiangshi/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("tianzi-jian"))
                    me->improve_skill("tianzi-jian", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);
            return 1;
        }

        write(HIC "��ԡ����ӽ��������������µ���ʶ������������಻��֮����\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }


    if (random(10) == 1 && arg == "���޳���" )
    {
        me->add("tianzi-jian/jiuzhou/count", 1);

        if (me->query("tianzi-jian/jiuzhou/count") >= 10)
        {
            write(HIM "��Ȼ�䣬�����л�Ȼ��ͨ���������ǡ�\n" NOR);
            write(HIC "������ͨ���˾�ѧ�����ӽ�������\n" NOR);

            me->set("can_perform/tianzi-jian/jiuzhou", 1);
            me->delete("tianzi-jian/jiuzhou/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("tianzi-jian"))
                    me->improve_skill("tianzi-jian", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);
            return 1;
        }

        write(HIC "��ԡ����޳��������������µ���ʶ������������಻��֮����\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }

    if (random(15) == 1 && arg == "��������")
    {
        me->add("tianzi-jian/junlin/count", 1);

        if (me->query("tianzi-jian/junlin/count") >= 20)
        {
            write(HIM "��Ȼ�䣬�����л�Ȼ��ͨ���������ǡ�\n" NOR);
            write(HIC "������ͨ���˾�ѧ���������¡���\n" NOR);

            me->set("can_perform/tianzi-jian/junlin", 1);
            me->delete("tianzi-jian/junlin/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("tianzi-jian"))
                    me->improve_skill("tianzi-jian", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);

            return 1;
        }

        write(HIC "��ԡ��������¡����������µ���ʶ������������಻��֮����\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }
        return notify_fail("����ͼ�����ֱ�������йء�" + arg + "�������ݣ�\n"
                           "�������ûʲôЧ������������������\n");

}
