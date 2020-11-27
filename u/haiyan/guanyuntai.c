// guanyuntai.c ����̨
// Modified by haiyan

#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "����̨");
        set("long", @LONG
�������䵱ɽ������Ĺ���̨��������ȥ��ֻ���ƺ�ӿ��������
���硣������΢΢һ��������˼���о���������в���(canwu)����
���Ƶı仯����̫��ȭ���ƺ����а�����
LONG );
        set("no_fight", "1"); 
        set("no_steal", "1"); 
        set("no_sleep_room","1"); 
        set("exits", ([
                "westdown" : __DIR__"jinding",
        ]));
        setup();
}

void init()
{
        add_action("do_canwu", "canwu");
}

int do_canwu(string arg)
{
        object me;
        int cost, quanli, lvl;

        me = this_player();
        quanli = me->query("taiji_quanli", 1);
        lvl = me->query_skill("taiji-quan", 1); 
        if (me->is_busy())
                return notify_fail("�����ڻ�æ�ţ���������������̫��ȭ��\n");

        if (me->query("jing") < me->query("max_jing") * 7 / 10)
                return notify_fail("�����ڵľ����������޷����в���\n");

        if (lvl < 200)
                return notify_fail("���̫�����򻹲����ң������������˷�ʱ���ˡ�\n");

        if (! arg || ! sscanf(arg, "%d", cost))
                return notify_fail("��Ҫ������Ǳ��������̫��ȭ��\n");

        if (cost >= me->query("potential") - me->query("learned_points"))
                return notify_fail("������û����ô���Ǳ�ܣ�\n");

        if (lvl >= 200 && lvl < 300 && quanli == 1)
                return notify_fail("���ϴβ������̫��ȭ��δ���͸������Ҫ������ɡ�\n");

        if (lvl >= 300 && lvl < 400 && quanli == 2)
                return notify_fail("���ϴβ������̫��ȭ��δ���͸������Ҫ������ɡ�\n");

        if (lvl >= 400 && lvl < 500 && quanli == 3)
                return notify_fail("���ϴβ������̫��ȭ��δ���͸������Ҫ������ɡ�\n");

        if (lvl >= 500 && quanli == 4)
                return notify_fail("���Ѿ�����������̫��ȭ�������ٲ����ˡ�\n");

        if (cost < 100)
                return notify_fail("����̫��ȭ��������Ҫһ�ٵ�Ǳ�ܲ�������������\n");

        message_vision("$N��ϥ������������������ǧ���򻯵����ƣ���ʼǱ������"
                       "̫��ȭ��\n", me);

        me->set_temp("potential_cost", cost);
        me->set_short_desc("�����ڵ�������˼��");
        me->start_busy((:call_other, __FILE__, "canwu" :),
                       (:call_other, __FILE__, "halt_canwu" :));
        return 1;
}

int canwu(object me)
{
        int cost, hint;

        cost = me->query_temp("potential_cost");
        if (cost > 0)
             cost = random(2) + 1;
        else
             cost = 0;

        me->add("learned_points", cost);
        switch (random(30)) 
        { 
            case 0: 
                    write("�����������Ų��Ϲ��������ƣ��ƺ��뵽��Щʲô��\n"); 
                    break; 

            case 1: 
                    write("��ĬĬ˼������̫������˸յĵ����ƺ�����ͨ�˵�ʲô��\n"); 
                    break; 

            case 2: 
                    write("�㿴�����²�ס�����İ��ƣ��ƺ��뵽��Щ���ࡱ�ĵ���\n"); 
                    break; 

            case 3: 
                    write("��˫��Ȧ�����ƺ�����ͨ��̫��ȭ���һЩ���ء�\n"); 
                    break; 
        }

        if (me->add_temp("potential_cost", -cost) <= 0)
        {
            message_vision(HIM "$N������ϣ����öԸ���һ���̫��ȭ������ƶ��Ƕ���\n"NOR, me);
            me->set_short_desc(0);
            return 0;
        }

        if ((random(30000)) < me->query_int())
        {
             me->add("taiji_quanli", 1);
             if (me->query("taiji_quanli",1) < 4)
                 message_vision(HIY "$N" HIY "������ϣ��ƺ������Ƶı仯������˸�"
                                "���̫��ȭ��������¶΢Ц��\n" NOR, me);
             else
             {
                 message_vision(HIY "$N" HIY "������ϣ����е�ʱ��Ȼ����̫��ȭ������仯"
                                "����Ȼ���أ�����ס������Ц����\n\n" NOR, me); 
                 write(HIC "���Ѿ����ײ������̫��ȭ��\n\n" NOR); 
             }
             if (me->can_improve_skill("taiji-quan"))
                  me->improve_skill("taiji-quan", 200000);
             me->set_short_desc(0);
             return 0;
        }
        return 1;
}

int halt_canwu(object me)
{
        tell_object(me, "����ֹ�˲���\n"); 
        message_vision("$N��̾һ��������վ��������\n", me); 
        me->add("potential", (me->query("learned_points") - me->query("potential")) / 5); 
        me->delete_temp("potential_cost");
        me->set_short_desc(0);
        return 1;
}

