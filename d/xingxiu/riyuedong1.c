#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���²ප");
        set("long", @LONG
�������������ܶ����ڵ����¶��ප��ֻ�����һƬ��Ψ
��ǰ����Զ����Щ����ߡ�ǽ������ԼԼ�ɼ�������һЩ
��ֵ����֡�
LONG);
        set("exits", ([
             "out" : __DIR__"xxh1",
        ]));

        setup();
        //replace_program(ROOM);
}

void init()
{
        add_action("do_mianbi", "mianbi");
}

int do_mianbi(string arg)
{
        object me;
        int cost;

        me = this_player();
        if (me->is_busy())
                return notify_fail("����æ������ͷ��������˵��\n");

        if (me->is_fighting())
                return notify_fail("��ߴ��һ����ڣ�������ġ�\n");

        if (me->query("jing") < me->query("max_jing") * 7 / 10)
                return notify_fail("�����ڵľ��������޷���ڡ�\n");

        if (me->query_skill("poison", 1) < 250)
                return notify_fail("��Ի����������̫ǳ����ڻ�ò���ʲô������\n");

        if (! arg || ! sscanf(arg, "%d", cost))
                return notify_fail("��Ҫ������Ǳ�ܽ�����ڣ�\n");

        if (cost >= me->query("potential") - me->query("learned_points"))
                return notify_fail("������û����ô���Ǳ�ܣ�\n");

        if (cost < 100)
                return notify_fail("������Ҫ��һ�ٵ�Ǳ�ܲ�������������\n");

        message_vision(HIC "\n$N" HIC "����һ���ط�������������"
                       "ʼר���о�ʯ�������صĻ���������\n\n" NOR, me);

        me->set_temp("pending/mianbi", 1);
        me->set_temp("potential_cost", cost);
        me->set_short_desc("�����ڵ���ר����ڡ�");
        me->start_busy((:call_other, __FILE__, "mianbi" :),
                       (:call_other, __FILE__, "halt_mianbi" :));
        return 1;
}

int mianbi(object me)
{
        int cost;

        cost = me->query_temp("potential_cost");
        if (cost > 0)
        {
                cost = random(cost) + 1;
                if (cost > 3) cost = 3;
        } else
                cost = 0;

        me->improve_skill("poison", me->query_int() / 5 +
                          random(me->query_skill("poison", 1) * cost));
        me->add("learned_points", cost);
        if (me->add_temp("potential_cost", -cost) > 0)
                return 1;

        me->set_temp("pending/mianbi", 0);
        me->set_short_desc(0);
        message_vision(HIG "$N" HIG "�����ϣ�¶��һ˿а����վ��������\n" NOR, me);
        return 0;
}

int halt_mianbi(object me)
{
        tell_object(me, HIY "��ͻȻ��Ȼ����վ��������\n" NOR);
        tell_room(environment(me), HIY + me->name() + HIY "ͻȻ��Ȼ����"
                                   "��վ��������\n" NOR, me);
        me->set_temp("pending/mianbi", 0);
        me->delete_temp("potential_cost");
        me->set_short_desc(0);
        return 1;
}



