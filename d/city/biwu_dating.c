#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"�������"NOR);
    set("long", @LONG
����һ�����Ĵ󷿼䣬����ǽ����һ���޴����̨(leitai)��
��̨��һ�鲼���ڵ�������ʵʵ������һ��Ũ���ɱ����Ȼ�Ӳ�
����ɢ�������������ڿ����ֱ���������ġ��ڶ���ǽ�ϣ�����
��ŵ���һ������(dabian)��
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);
    set("biwu_room",1);

    set("item_desc",([
            "leitai" : "һ�����ķ����Ĵ���̨���������(jump)��ȥ��\n",
    ]));

    set("objects",([
            "/adm/npc/broadcaster" : 1,
    ]));

    set("exits", ([
        "south"  : __DIR__"biwu_road",
    ]));

    set("no_clean_up", 0);
    setup();
}

void init()
{
    add_action("do_no","get");
    add_action("do_no","put");
    add_action("do_no","drop");
    add_action("do_no","summon");
    add_action("do_no","eat");
    add_action("do_no","drink");
    add_action("do_no","guard");
    add_action("do_jump","jump");
    add_action("do_look","look");
}

int do_no()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"�����������ʲô��\n");
    return 1;
}

int do_look(string arg)
{
    string msg;
    int i;
    mapping paiming;

    if (arg != "dabian") return 0;
    paiming = BIWU_D->get_list();
    msg = HIC "      *          ��       ��       ��       ��          *\n"NOR;
    msg += HIC "-------------------------------------------------------------\n";
    msg += "\n";
    for (i = 0;i < sizeof(paiming);i++)
{
            msg += HIY + "   �����µ�" + chinese_number(i+1) + "�� " + NOR + paiming[i]["title"] + "\n";
            msg += "\n";
}
    msg += HIC "-------------------------------------------------------------\n";
    write(msg);
    return 1;
}

int do_jump(string arg)
{
    int status;
    object me;
    me = this_player();

    if (arg != "leitai")
    {
            tell_object(me,"��Ҫ������������\n");
            return 1;
    }

    if (wizardp(me))
    {
            tell_object(me,"������ʦ�����ͱ����������ʲô��һ�ڶ��ˣ�\n");
            return 1;
    }

    if (me->query("last_biwu_time") &&
        time() - me->query("last_biwu_time") < 300)
    {
            tell_object(me,"��ողŴ���ޣ�����Ϣһ��ɣ�����Ӻ��ٴ�\n");
            return 1;
    }

    if (me->query("combat_exp") < 5000000)
    {
            tell_object(me,"��ʹ������һ�£�����°���������̨��Ե���۵���ȥ������\n");
            return 1;
    }

    status = BIWU_D->get_status();
    if (status == 2) return notify_fail("��̨���Ѿ������ˣ���͵ȵȰɣ�\n");
    if (status == 3) return notify_fail("���ڻ�û�����޵�ʱ�䣬�㼱ɶ��\n");

    if (me->query("combat_exp") > 10000000)
            message_vision(HIW"$N����һ������һͦ���Ѿ���ȻƮ����̨��\n"NOR,me);
    else
            message_vision(HIW"$N��ס��̨һ�ǣ�һʹ������׾����������̨��\n"NOR,me);

    BIWU_D->start_biwu(me);
    return 1;
}

int valid_leave(object me, string dir)
{
	if (BIWU_D->get_status() == 2 && BIWU_D->get_enemy() == me)
	        return notify_fail("�㻹����̨�ϣ������뿪��\n");
	return ::valid_leave(me, dir);
}
