#include <ansi.h>
inherit ROOM;

int sos(int,int);
void fresh(object ob);

void create()
{
        set("short", "�ĳ�");
        set("long", @LONG
�����ǽ��ж�Ұ��ȭ�Ծ��ķ��䣬���ܵĶķ��ﴫ����ߺ���
���ĶĲ���������ĳ���ģ���㲻�Ϻܴ󣬵��ĵ�����ȴ����
ȫ������Ҳ�ǳ��ܵ��������ǽ�Ϲ���һ������(paizi)��
LONG);
        set("item_desc", ([
                "paizi" : WHT "\n\n        ������������������������������\n"
                              "        ��                          ��\n"
                              "        ��         " NOR + HIW "��ս����" NOR + WHT "         ��\n"
                              "        ��                          ��\n"
                              "        ��      Ұ��ȭ���С�ʯͷ��  ��\n"
                              "        ��  ��������������������ʽ  ��\n"
                              "        ��  ����ʯͷ���Ƽ���������  ��\n"
                              "        ��  ���Ʋ���������ʯͷ��    ��\n"
                              "        ��  ��Һ;�����ÿ�θ���һ  ��\n"
                              "        ��  �У�������ȡʤ��������  ��\n"
                              "        ��  ���䣬������ƽ�֡�      ��\n"
                              "        ��                          ��\n"
                              "        ��  " NOR + HIW "��ս" NOR + WHT "��                  ��\n"
                              "        ��                          ��\n"
                              "        ��      " NOR + HIY "shi(ʯ)" NOR + WHT "             ��\n"
                              "        �� " NOR + HIY "box  jian(��)" NOR + HIY "  ���� ����" NOR + WHT " ��\n"
                              "        ��      " NOR + HIY "bu(��)   " NOR + WHT "           ��\n"
                              "        ��                          ��\n"
                              "        ������������������������������\n\n\n" NOR,
        ]));
        set("exits", ([
                "north" : __DIR__"duchang",
        ]));
        set("objects", ([
                "/u/xiner/npc/xiami" : 1,
                "/u/xiner/npc/zhuang" : 1,
        ]));
        set("no_fight", 1);
        set("coor/x",-9);
	set("coor/y",-10);
	set("coor/z",0);
	setup();
}

void init()
{
        add_action("do_box", "box");
}

int do_box(string arg)
{
        int wager, skill, lpoint, tpoint;
        string wtype1, wtype2, status;
        object mtype, me;
        mapping lrn;

        int min, max;
        min = 10000;
        max = 500000;

        me = this_player();

        if (me->query_temp("casino/mark"))
                return notify_fail(CYN "ׯ�ҽе������������ڻ�û�ֵ����ء�\n" NOR);

        if (! arg || sscanf(arg, "%s %d %s", wtype1, wager, wtype2) != 3)
                return notify_fail(CYN "ׯ�Ҽ�Ц��������������������Ұ��ȭ�ģ�\n" NOR);

        mtype = present(wtype2 + "_money", me);

        if (! mtype)
		return notify_fail("������û�����ֻ��ҡ�\n");

        if (wager < 1)
		return notify_fail("��Ҫѹ���ٰ���\n");

        if ((int)mtype->query_amount() < wager)
                return notify_fail("������û����ô��" + mtype->query("name") + "��\n");

        if (wager > 50)
		return notify_fail(CYN "ׯ��̾����С�����飡�������\n" NOR);

        if (wager * (mtype->query("base_value")) < min
           || wager * (mtype->query("base_value")) > max)
        	return notify_fail("��Ķ�עӦ����һ���ƽ����ƽ���ʮ����\n");

        if ((wtype1 != "shi") && (wtype1 != "jian") && (wtype1 != "bu") )
                return notify_fail("��׼������ʯͷ�������������ǡ�������\n");

        me->set_temp("gamb_t",(me->query_temp("gamb_t") +1));

        if (me->query_temp("gamb_t") > 50)
        {
                call_out("fresh", 600, me);
                me->set_temp("casino/mark", 1);
                return notify_fail(CYN "ׯ�ҽе�����λ" + RANK_D->query_respect(me) +
                                   CYN "���������ô�ã�Ҳ�û����˰ɣ�\n" NOR);
        }

        message_vision("\nСϺ�׺ȵ���׼�����˰ɣ�\nһ����������", me);

	switch(random(3))
	{
	case 1:	//npc�� ʯͷ
		message_vision(HIW "\nСϺ�׺ȵ�����ʯͷ����\n" NOR, me);
		if (wtype1 == "shi")
			 status = "equal";
		else if (wtype1 == "jian")
			 status = "lose";
		else if (wtype1 == "bu")
			 status = "win";
		break;

	case 2:	//npc�� ����
		message_vision(HIW "\nСϺ�׺ȵ�������������\n" NOR, me);
		if (wtype1 == "shi")
			 status = "win";
		else if (wtype1 == "jian")
			 status = "equal";
		else if (wtype1 == "bu")
			 status = "lose";
		break;

	default ://npc�� ��
		message_vision(HIW "\nСϺ�׺ȵ�����������\n" NOR, me);
		if (wtype1 == "shi")
			 status = "lose";
		else if (wtype1 == "jian")
			 status = "win";
		else if (wtype1 == "bu")
			 status = "equal";
		break;
	}

        if ( status == "equal")
	{
        	message_vision(me->query("name") + "��ִ�ƽ��ϵͳ����һ"+ mtype->query("base_unit") + mtype->query("name") + "��\n", me);
                mtype->set_amount((int)mtype->query_amount() - 1);
                mtype->move(me, 1);
        } else
        if ( status == "lose")
	{
        	message_vision(me->query("name") + "����" + chinese_number(wager) +
                               mtype->query("base_unit") + mtype->query("name") +
                               "��\n", me);
                mtype->set_amount((int)mtype->query_amount() - wager);
                mtype->move(me, 1);
        } else
	{
       		message_vision(me->query("name") + "Ӯ��" + chinese_number(wager) +
                               mtype->query("base_unit") + mtype->query("name") +
                               "��\n", me);
                mtype->set_amount((int)mtype->query_amount() + wager);
                mtype->move(me, 1);
		if (me->query_skill("yeqiu-quan") < 180 && random(9)==1)
		{
	        	message_vision("$Nͨ����ֱ��Զ�Ұ��ȭ����������\n", me);
			me->improve_skill("yeqiu-quan", 10000);
		}
        }
        return 1;
}

void fresh(object ob)
{
	if (! objectp(ob)) return;
        ob->delete_temp("gamb_t");
        ob->delete_temp("casino/mark");
}

int sos(int lower, int upper)
{
        int x,y;
        x = 0;

        while (lower <= upper)
        {
                y = lower * lower;
                x += y;
                lower++;
        }
        return x;
}
