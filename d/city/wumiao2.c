#include <ansi.h>
#include <localtime.h>

inherit ROOM;

#define TIME "/cmds/usr/time"
#define GIFT "/clone/fam/max/naobaijin"
// ũ������
nosave mapping *lunar_day = ({
    (["month" :  1, "day" :  1, "name" : RED"����"NOR]),
    (["month" :  1, "day" :  2, "name" : HIG"����(����)"NOR]),
    (["month" :  1, "day" :  3, "name" : HIY"����(����)"NOR]),
    (["month" :  1, "day" : 15, "name" : RED"Ԫ����"NOR]),
    (["month" :  5, "day" :  5, "name" : GRN"�����"NOR]),
    (["month" :  7, "day" :  7, "name" : CYN"��Ϧ���ɽ�"NOR]),
    (["month" :  8, "day" : 15, "name" : CYN"�����"NOR]),
    (["month" :  9, "day" :  9, "name" : MAG"������"NOR]),
    (["month" : 12, "day" :  8, "name" : BLU"���˽�"NOR]),
    (["month" : 12, "day" : 23, "name" : RED"С��"NOR]),
    (["month" : 12, "day" : 30, "name" : RED"��Ϧ"NOR]),
});
// ��������
nosave mapping *solar_day = ({
    (["month" :  1, "day" :  1, "name" : RED"Ԫ��"NOR]),
    (["month" :  4, "day" :  5, "name" : CYN"������"NOR]),
    (["month" :  5, "day" :  1, "name" : WHT"�����Ͷ���"NOR]),
    (["month" : 10, "day" :  1, "name" : RED"�й������"NOR]),
});

void create()
{
    set("short", "�����¥");
    set("long", @LONG
������������Ķ�¥�����﹩�������ɵĳ������ƺ�����
���ܣ�����������������Ӣ����������˵���׻�����Ĵ�ͳ
�ڼ�����������(pray)��õ�ף����
LONG);
    set("no_fight", 1);
    set("no_steal", 1);
    set("no_beg", 1);
    set("no_sleep_room", 1);

    set("exits", ([
        "down" : __DIR__"wumiao",
    ]));

    set("objects", ([
        "/u/sanben/xquest/npc/zixu" : 1,
    ]));
    setup();
}

void init()
{
    add_action("do_pray", "pray");
}

int do_pray(string arg)
{
    object me = this_player();
    int exp, pot, wday, day, month, year, *date, exp0, exp1;
    string festival;

    date = localtime(time());
    year = date[LT_YEAR];
    month = date[LT_MON] + 1;
    day = date[LT_MDAY];
    wday = date[LT_WDAY];

    exp = me->query("combat_exp");
    exp0 = me->query("experience");
    exp1 = me->query("learned_experience");

    festival = "festival/" + year + "/" + month;

    if (me->is_busy())
    {
        return notify_fail("��������æ���أ�û��������������\n");
    }

    message_vision(HIG "$N" HIG "��������ǰ�����������Ŀ���������ͷ��Ȼ��ĬĬ�����š�\n" NOR, me);

    if (me->query(festival) == day)
    {
        tell_object(me, HIR "����������Ѿ���ף�����ˣ������������ɣ���\n" NOR);
    }
    else
    {
        int i = 1;
        int lunar_m, lunar_d;
        // ȡ��ũ������
        sscanf(TIME->to_lunar(year + " " + month + " " + day), "%*d-%d-%d", lunar_m, lunar_d);
        // ���˽����ӱ�
        if (time() - me->query("birthday") < 7 * 24 * 60 * 60)
        {
            i *= 2;
            tell_object(me, HBGRN "��ע���˺� 7 ���ڽ����ӱ�^_^\n" NOR);
        }
        // ��ĩ�ӱ�(�޵���)
        if (!wday || wday == 6)
        {
            tell_object(me, HIM "��������ĩ�������ӱ�^_^\n" NOR);
            i *= 2;
        }
        //�ڼ��ռӱ�
        foreach (mapping m in solar_day)
        {
            if (m["month"] < month)
            {
                continue;
            }
            if (m["month"] > month)
            {
                break;
            }
            if (month == m["month"] && day == m["day"])
            {
                tell_object(me, "������" + m["name"] + "�������ӱ�^_^\n");
                i *= 2;
                break;
            }
        }
        foreach (mapping m in lunar_day)
        {
            if (m["month"] < lunar_m)
            {
                continue;
            }
            if (m["month"] > lunar_m)
            {
                break;
            }
            if (lunar_m == m["month"] && lunar_d == m["day"])
            {
                tell_object(me, "������" + m["name"] + "�������ӱ�^_^\n");
                i *= 2;

                if (exp >= 100000)
                {
                    object gift = new (GIFT);
                    gift->move(me);
                    tell_object(me, "��õ���������" + gift->short() + "^_^\n");
                }

                break;
            }
        }
        // ���ӻ���
        me->add("state/jifen", i);
        // ��¼������
        me->add("state/pray", 1);

        // Ǳ������5K
        pot = exp / 100;
        if (pot < 5000)
            pot = 5000;

        // ��ĩ˫��������5��
        pot *= i;
        if (pot > 50000)
            pot = 50000;

        pot = me->improve_potential(pot);
        if (me->query("skybook/guard/death") < i)
            me->set("skybook/guard/death", i);
        me->set(festival, day);
        message_vision(HIW "$N�����" + chinese_number(pot) + "��Ǳ�ܽ�����" + chinese_number(i) + "����֡�\n" NOR, me);
        me->start_busy(3);
    }

    return 1;
}
