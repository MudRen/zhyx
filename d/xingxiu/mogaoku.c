inherit ROOM;

void create()
{
        set("short", "Ī�߿�");
        set("long", @LONG
����ǽ���ϻ�����������صĻ��棬����Ů���죬����
�������á����л��кܶ����;��顣�㱻��Щ�������Ļ�֮
�������ˡ�
LONG );
        set("exits", ([
                "out" : __DIR__"yueerquan",
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_think", "think");
}

int do_think()
{
        object ob;
        int c_skill;
        ob = this_player();

        c_skill = (int)ob->query_skill("training", 1);
        if (ob->query_skill("literate", 1) < 100)
        {
                write("����Ļ�֪ʶ̫�ͣ��޷�����ʯ�����ݡ�\n", ob);
                return 1;
        }

        if (! ob->can_improve_skill("training"))
        {
                write("���ʵս���鲻�㣬�޷�����ʯ�����ݡ�\n");
                return 1;
        }

        if (ob->query("jing") < 40)
        {
                write("�㾫�����ܼ��У������޷�����ʯ�����ݡ�\n");
                return 1;
        }

        if (c_skill > 229)
        {
                write("�����ʯ������̫��ǳ�ˡ�\n");
                return 1;
        }

        message_vision("$N�����ʯ��������˼�����ã��ԡ�Ԧ������"
                        "��������\n", ob);
        ob->improve_skill("training", 1 + random(ob->query("int")));
        ob->receive_damage("jing", 35);
        return 1;
}

